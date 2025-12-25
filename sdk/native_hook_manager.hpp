/* ============================================================================ *
 * SA-MP SDK - A Modern C++ SDK for San Andreas Multiplayer Plugin Development  *
 * ================================= About ==================================== *
 *                                                                              *
 * This SDK provides a modern, high-level C++ abstraction layer over the native *
 * SA-MP Plugin SDK. It is designed to simplify plugin development by offering  *
 * type-safe, object-oriented, and robust interfaces for interacting with the   *
 * SA-MP server and the Pawn scripting environment.                             *
 *                                                                              *
 * =============================== Copyright ================================== *
 *                                                                              *
 * Copyright (c) 2025, AlderGrounds                                             *
 * All rights reserved.                                                         *
 *                                                                              *
 * Repository: https://github.com/aldergrounds/samp-sdk                         *
 *                                                                              *
 * ================================ License =================================== *
 *                                                                              *
 * Licensed under the MIT License (the "License"); you may not use this file    *
 * except in compliance with the License. You may obtain a copy of the License  *
 * at:                                                                          *
 *                                                                              *
 *     https://opensource.org/licenses/MIT                                      *
 *                                                                              *
 * Unless required by applicable law or agreed to in writing, software          *
 * distributed under the License is distributed on an "AS IS" BASIS,            *
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.     *
 * See the License for the specific language governing permissions and          *
 * limitations under the License.                                               *
 *                                                                              *
 * ============================================================================ */

#pragma once

#include <cstdint>
#include <utility>
#include <vector>
#include <functional>
#include <unordered_map>
#include <mutex>
#include <list>
#include <atomic>
#include <shared_mutex>
//
#include "amx_defs.h"
#include "assembly.hpp"
#include "hash.hpp"
#include "logger.hpp"

#if defined(SAMP_SDK_WINDOWS)
    #include <windows.h>
#elif defined(SAMP_SDK_LINUX)
    #include <unistd.h>
    #include <sys/mman.h>
#endif

namespace Samp_SDK {
    namespace Detail {
        using Shared_Mutex_Type = std::shared_mutex;
        template<typename Mutex>
        using Shared_Lock = std::shared_lock<Mutex>;
        template<typename Mutex>
        using Unique_Lock = std::lock_guard<Mutex>;

        class Native_Hook {
            public:
                using Handler_Func = std::function<cell(AMX*, cell*)>;
                Native_Hook(uint32_t hash, Handler_Func handler) : hash_(hash), user_handler_(std::move(handler)), next_in_chain_(nullptr) {}

                cell Dispatch(AMX* amx, cell* params) {
                    if (!user_handler_)
                        return Call_Original(amx, params);

                    return user_handler_(amx, params);
                }

                cell Call_Original(AMX* amx, cell* params) {
                    AMX_NATIVE next = next_in_chain_.load(std::memory_order_relaxed);

                    if (next != nullptr)
                        return next(amx, params);

                    Log("[SA-MP SDK] Error: Next function in chain for hook hash %u is null. The hook chain is broken.", hash_);

                    return 0;
                }

                void Set_Next_In_Chain(AMX_NATIVE next_func) {
                    next_in_chain_.store(next_func, std::memory_order_relaxed);
                }

                uint32_t Get_Hash() const {
                    return hash_;
                }

            private:
                uint32_t hash_;
                Handler_Func user_handler_;
                std::atomic<AMX_NATIVE> next_in_chain_;
        };

        class Trampoline_Allocator {
            public:
                static constexpr size_t TRAMPOLINE_SIZE = 10;
                static constexpr size_t TRAMPOLINE_ALIGNMENT = 16;
                static constexpr size_t ALLOCATION_SIZE = 4096;

                void* Allocate(int hook_id) {
                    std::lock_guard<std::mutex> lock(mtx_);

                    size_t aligned_offset = (current_offset_ + (TRAMPOLINE_ALIGNMENT - 1)) & ~(TRAMPOLINE_ALIGNMENT - 1);
                    
                    if (!current_block_ || aligned_offset + TRAMPOLINE_SIZE > ALLOCATION_SIZE)
                        Allocate_New_Block();
                    
                    if (!current_block_)
                        return (Log("[SA-MP SDK] Fatal: Failed to allocate executable memory for trampolines."), nullptr);

                    unsigned char* trampoline_addr = current_block_ + aligned_offset;
                    Generate_Trampoline_Code(trampoline_addr, hook_id);
                    current_offset_ = aligned_offset + TRAMPOLINE_SIZE;

                    return trampoline_addr;
                }

                ~Trampoline_Allocator() {
                    for (unsigned char* block : allocated_blocks_)
#if defined(SAMP_SDK_WINDOWS)
                        VirtualFree(block, 0, MEM_RELEASE);
#elif defined(SAMP_SDK_LINUX)
                        munmap(block, ALLOCATION_SIZE);
#endif
                }
                
            private:
                void Allocate_New_Block() {
#if defined(SAMP_SDK_WINDOWS)
                    current_block_ = static_cast<unsigned char*>(VirtualAlloc(nullptr, ALLOCATION_SIZE, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE));
#elif defined(SAMP_SDK_LINUX)
                    current_block_ = static_cast<unsigned char*>(mmap(nullptr, ALLOCATION_SIZE, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0));

                    if (current_block_ == MAP_FAILED)
                        current_block_ = nullptr;
#endif
                    current_offset_ = 0;

                    if (current_block_)
                        allocated_blocks_.push_back(current_block_);
                }

                inline void Generate_Trampoline_Code(unsigned char* memory, int hook_id) {
                    memory[0] = 0xB8;
                    *reinterpret_cast<uint32_t*>(&memory[1]) = static_cast<uint32_t>(hook_id);

                    memory[5] = 0xE9;

                    uintptr_t target = reinterpret_cast<uintptr_t>(&Assembly::Dispatch_Wrapper_Asm);
                    uintptr_t source = reinterpret_cast<uintptr_t>(memory) + 10;
                    uint32_t relative_offset = static_cast<uint32_t>(target - source);

                    *reinterpret_cast<uint32_t*>(&memory[6]) = relative_offset;
                }

                std::mutex mtx_;
                std::vector<unsigned char*> allocated_blocks_;
                unsigned char* current_block_ = nullptr;
                size_t current_offset_ = 0;
        };
        
        class Native_Hook_Manager {
            public:
                static Native_Hook_Manager& Instance() {
                    static Native_Hook_Manager instance;

                    return instance;
                }

                void Register_Hook(uint32_t hash, Native_Hook::Handler_Func handler) {
                    Unique_Lock<Shared_Mutex_Type> lock(mtx_);
                    hooks_.emplace_front(hash, handler);
                }
         
                [[nodiscard]] Native_Hook* Find_Hook(uint32_t hash) {
                    Shared_Lock<Shared_Mutex_Type> lock(mtx_);

                    for (auto& hook : hooks_) {
                        if (hook.Get_Hash() == hash)
                            return &hook;
                    }

                    return nullptr;
                }
           
                [[nodiscard]] std::list<Native_Hook>& Get_All_Hooks() {
                    return hooks_;
                }

                using Trampoline_Func = cell(SAMP_SDK_CDECL*)(AMX* amx, cell* params);

                [[nodiscard]] Trampoline_Func Get_Trampoline(uint32_t hash) {
                    {
                        Shared_Lock<Shared_Mutex_Type> lock(mtx_);
                        auto it = hash_to_trampoline_.find(hash);

                        if (it != hash_to_trampoline_.end())
                            return it->second;
                    }

                    Unique_Lock<Shared_Mutex_Type> lock(mtx_);
                    
                    auto it = hash_to_trampoline_.find(hash);

                    if (it != hash_to_trampoline_.end())
                        return it->second;

                    int new_hook_id = static_cast<int>(hook_id_to_hash_.size());
                    void* trampoline_addr = trampoline_allocator_.Allocate(new_hook_id);

                    if (!trampoline_addr)
                        return nullptr;

                    Trampoline_Func trampoline = reinterpret_cast<Trampoline_Func>(trampoline_addr);
                    hash_to_trampoline_[hash] = trampoline;
                    hook_id_to_hash_.push_back(hash);

                    return trampoline;
                }
               
                [[nodiscard]] uint32_t Get_Hash_From_Id(int hook_id) {
                    Shared_Lock<Shared_Mutex_Type> lock(mtx_);

                    if (hook_id >= 0 && static_cast<size_t>(hook_id) < hook_id_to_hash_.size())
                        return hook_id_to_hash_[hook_id];

                    return 0;
                }

            private:
                Native_Hook_Manager() = default;

                std::list<Native_Hook> hooks_;
                Shared_Mutex_Type mtx_;
                
                Trampoline_Allocator trampoline_allocator_;
                std::unordered_map<uint32_t, Trampoline_Func> hash_to_trampoline_;
                std::vector<uint32_t> hook_id_to_hash_;
        };
        
    }
}

extern "C" {
    inline cell SAMP_SDK_CDECL SAMP_SDK_USED_BY_ASM Dispatch_Hook(int hook_id, AMX* amx, cell* params) {
        auto& instance = Samp_SDK::Detail::Native_Hook_Manager::Instance();
        uint32_t hash = instance.Get_Hash_From_Id(hook_id);
        
        if (hash == 0)
            return (Samp_SDK::Log("[SA-MP SDK] Fatal: Trampoline called with invalid hook_id %d.", hook_id), 0);

        Samp_SDK::Detail::Native_Hook* hook = instance.Find_Hook(hash);

        if (hook)
            return hook->Dispatch(amx, params);

        Samp_SDK::Log("[SA-MP SDK] Fatal: Trampoline for hash %u (id %d) called but no hook found.", hash, hook_id);

        return 0;
    }
}

#define Call_Original_Native(name) \
    ([](AMX* amx, cell* params) -> cell { \
        constexpr uint32_t hash = Samp_SDK::Detail::FNV1a_Hash_Const(#name); \
        auto* hook = Samp_SDK::Detail::Native_Hook_Manager::Instance().Find_Hook(hash); \
        \
        if (hook) \
            return hook->Call_Original(amx, params); \
        \
        Samp_SDK::Log("[SA-MP SDK] Error: Could not call original native '%s', no hook found.", #name); \
        \
        return 0; \
    })(amx, params)

#define PLUGIN_NATIVE_HOOK_REGISTRATION(name) \
    class Native_Hook_Register_##name { \
        public: \
            Native_Hook_Register_##name() { \
                constexpr uint32_t hash = Samp_SDK::Detail::FNV1a_Hash_Const(#name); \
                Samp_SDK::Detail::Native_Hook_Manager::Instance().Register_Hook(hash, &Hook_##name); \
            } \
    }; \
    static Native_Hook_Register_##name register_hook_##name;
