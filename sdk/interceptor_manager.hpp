/* ============================================================================== *
 * SA-MP SDK - A Modern C++ SDK for San Andreas Multiplayer Plugin Development    *
 * ============================================================================== *
 *                                                                                *
 * Copyright (c) 2025, AlderGrounds                                               *
 *                                                                                *
 * Developed by: Calasans                                                         *
 * Provided by: AlderGrounds                                                      *
 * License: MIT License                                                           *
 * Repository: https://github.com/aldergrounds/samp-sdk                           *
 *                                                                                *
 * ============================================================================== *
 *                                                                                *
 * This SDK provides a modern, high-level C++ abstraction layer over the native   *
 * SA-MP Plugin SDK. It is designed to simplify plugin development by offering    *
 * type-safe, object-oriented, and robust interfaces for interacting with the     *
 * SA-MP server and the Pawn scripting environment.                               *
 *                                                                                *
 * --- Core Architecture & Features ---                                           *
 *                                                                                *
 *  - Type-Safe C++ Interface:                                                    *
 *      > Write SA-MP natives and public callbacks as standard C++ functions.     *
 *      > Use C++ types like `int`, `float`, and `std::string` directly.          *
 *                                                                                *
 *  - Automatic Marshalling:                                                      *
 *      > The SDK automatically handles the complex conversion of data types      *
 *        (marshalling) between the C++ environment and the Pawn virtual          *
 *        machine.                                                                *
 *      > Transparently manages memory for strings and reference parameters.      *
 *                                                                                *
 *  - Powerful Hooking Engine:                                                    *
 *      > Seamlessly intercepts both Pawn public callbacks (with `Plugin_Public`) *
 *        and natives (with `Plugin_Native_Hook`).                                *
 *      > Allows multiple plugins built with the SDK to coexist and chain         *
 *        callbacks/hooks correctly without interfering with each other.          *
 *      > Supports "Ghost Callbacks" for hooking publics not present in the       *
 *        script.                                                                 *
 *                                                                                *
 *  - Simplified Pawn Interaction:                                                *
 *      > Call any Pawn native or public function from C++ with `Pawn(...)`.      *
 *      > The SDK automatically finds the target function (native or public).     *
 *      > Built-in utilities like `Pawn_Format` for easy string formatting.       *
 *                                                                                *
 *  - Dynamic Module System:                                                      *
 *      > Load other plugins/modules dynamically from a host plugin using         *
 *        `Plugin_Module`. Modules are automatically unloaded on plugin exit.     *
 *      > Enables building scalable and maintainable plugin architectures.        *
 *                                                                                *
 *  - Modern C++ Compatibility:                                                   *
 *      > Requires C++14 and automatically utilizes features up to C++20.         *
 *      > Encourages modern C++ practices for safer and more expressive code.     *
 *                                                                                *
 * ============================================================================== *
 *                                                                                *
 * Permission is hereby granted, free of charge, to any person obtaining a copy   *
 * of this software and associated documentation files (the "Software"), to       *
 * deal in the Software without restriction, including without limitation the     *
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or    *
 * sell copies of the Software, and to permit persons to whom the Software is     *
 * furnished to do so, subject to the following conditions:                       *
 *                                                                                *
 * The above copyright notice and this permission notice shall be included in     *
 * all copies or substantial portions of the Software.                            *
 *                                                                                *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING        *
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS   *
 * IN THE SOFTWARE.                                                               *
 *                                                                                *
 * ============================================================================== */

#pragma once

#include <string>
#include <mutex>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <vector>
#include <functional>
//
#include "amx_api.hpp"
#include "amx_defs.h"
#include "amx_manager.hpp"
#include "core.hpp"
#include "function_hook.hpp"
#include "hash.hpp"
#include "logger.hpp"
#include "native_hook_manager.hpp"
#include "public_dispatcher.hpp"
#include "version.hpp"
//
#if defined(SAMP_SDK_CXX_MODERN)
    #include <shared_mutex>
#endif

constexpr int PLUGIN_EXEC_GHOST_PUBLIC = -10;

namespace Samp_SDK {
    namespace Detail {
        int SAMP_SDK_CDECL Amx_Register_Detour(AMX* amx, const AMX_NATIVE_INFO* nativelist, int number);
        int SAMP_SDK_CDECL Amx_Exec_Detour(AMX* amx, cell* retval, int index);
        int SAMP_SDK_CDECL Amx_Init_Detour(AMX *amx, void *program);
        int SAMP_SDK_CDECL Amx_Cleanup_Detour(AMX *amx);
        int SAMP_SDK_CDECL Amx_Find_Public_Detour(AMX* amx, const char* name, int* index);
        
        inline Function_Hook<amx::Register_t>& Get_Amx_Register_Hook() {
            static Function_Hook<amx::Register_t> hook;

            return hook;
        }

        inline Function_Hook<amx::Exec_t>& Get_Amx_Exec_Hook() {
            static Function_Hook<amx::Exec_t> hook;

            return hook;
        }

        inline Function_Hook<amx::Init_t>& Get_Amx_Init_Hook() {
            static Function_Hook<amx::Init_t> hook;

            return hook;
        }

        inline Function_Hook<amx::Cleanup_t>& Get_Amx_Cleanup_Hook() {
            static Function_Hook<amx::Cleanup_t> hook;

            return hook;
        }

        inline Function_Hook<amx::Find_Public_t>& Get_Amx_Find_Public_Hook() {
            static Function_Hook<amx::Find_Public_t> hook;

            return hook;
        }

        inline std::function<bool(const std::string&, AMX*, cell&)>& Get_Public_Handler() {
            static std::function<bool(const std::string&, AMX*, cell&)> handler = nullptr;

            return handler;
        }

        inline std::function<bool(const std::string&)>& Get_Has_Public_Handler() {
            static std::function<bool(const std::string&)> handler = nullptr;

            return handler;
        }

        static thread_local std::unique_ptr<std::string> tl_public_name;

#if defined(SAMP_SDK_CXX_MODERN)
        using Shared_Mutex_Type = std::shared_mutex;
#elif defined(SAMP_SDK_CXX_14)
        using Shared_Mutex_Type = std::mutex;
#endif

        class Interceptor_Manager {
            public:
                static Interceptor_Manager& Instance() {
                    static Interceptor_Manager instance;

                    return instance;
                }

                void Activate() {
                    void* register_func = Core::Instance().Get_AMX_Export(PLUGIN_AMX_EXPORT_Register);
                    void* exec_func = Core::Instance().Get_AMX_Export(PLUGIN_AMX_EXPORT_Exec);
                    void* init_func = Core::Instance().Get_AMX_Export(PLUGIN_AMX_EXPORT_Init);
                    void* cleanup_func = Core::Instance().Get_AMX_Export(PLUGIN_AMX_EXPORT_Cleanup);
                    void* find_public_func = Core::Instance().Get_AMX_Export(PLUGIN_AMX_EXPORT_FindPublic);

                    if (SAMP_SDK_LIKELY(register_func && exec_func && init_func && cleanup_func && find_public_func)) {
                        Get_Amx_Init_Hook().Install(init_func, reinterpret_cast<void*>(Amx_Init_Detour));
                        Get_Amx_Cleanup_Hook().Install(cleanup_func, reinterpret_cast<void*>(Amx_Cleanup_Detour));
                        Get_Amx_Register_Hook().Install(register_func, reinterpret_cast<void*>(Amx_Register_Detour));
                        Get_Amx_Find_Public_Hook().Install(find_public_func, reinterpret_cast<void*>(Amx_Find_Public_Detour));
                        Get_Amx_Exec_Hook().Install(exec_func, reinterpret_cast<void*>(Amx_Exec_Detour));
                    }
                    else
                        Log("[SA-MP SDK] Fatal: Failed to activate core interceptors.");
                }

                void Deactivate() {
                    Get_Amx_Register_Hook().Uninstall();
                    Get_Amx_Exec_Hook().Uninstall();
                    Get_Amx_Init_Hook().Uninstall();
                    Get_Amx_Cleanup_Hook().Uninstall();
                    Get_Amx_Find_Public_Hook().Uninstall();
                }
                
                void Update_Native_Cache(const AMX_NATIVE_INFO* nativelist, int number) {
                    auto& cache_data = Get_Cache_Data();
                    std::lock_guard<Shared_Mutex_Type> lock(cache_data.mtx);

                    for (int i = 0; (number == -1 || i < number) && nativelist[i].name != nullptr; ++i) {
                        uint32_t hash = FNV1a_Hash(nativelist[i].name);

                        cache_data.native_cache[hash] = nativelist[i].func;
                        cache_data.native_name_cache[hash] = nativelist[i].name;
                    }
                }

                AMX_NATIVE Find_Cached_Native(uint32_t hash) {
                    auto& cache_data = Get_Cache_Data();
#if defined(SAMP_SDK_CXX_MODERN)
                    std::shared_lock<Shared_Mutex_Type> lock(cache_data.mtx);
#elif defined(SAMP_SDK_CXX_14)
                    std::lock_guard<Shared_Mutex_Type> lock(cache_data.mtx);
#endif

                    auto it = cache_data.native_cache.find(hash);
                    return (it != cache_data.native_cache.end()) ? it->second : nullptr;
                }

                const std::unordered_map<uint32_t, std::string>& Get_Native_Name_Cache() {
                    return Get_Cache_Data().native_name_cache;
                }

                void On_Amx_Patched(AMX* amx) {
                    std::lock_guard<Shared_Mutex_Type> lock(patched_amx_mutex_);
                    patched_amx_set_.insert(amx);
                }

                bool Is_Amx_Patched(AMX* amx) {
#if defined(SAMP_SDK_CXX_MODERN)
                    std::shared_lock<Shared_Mutex_Type> lock(patched_amx_mutex_);
#elif defined(SAMP_SDK_CXX_14)
                    std::lock_guard<Shared_Mutex_Type> lock(patched_amx_mutex_);
#endif
                    return patched_amx_set_.count(amx) > 0;
                }

                void On_Amx_Cleanup(AMX* amx) {
                    std::lock_guard<Shared_Mutex_Type> lock(patched_amx_mutex_);
                    patched_amx_set_.erase(amx);
                }

                void Set_Gamemode_Amx(AMX* amx) {
                    gamemode_amx_ = amx;
                }

                bool Is_Gamemode_Amx(AMX* amx) const {
                    return amx == gamemode_amx_;
                }

            private:
                Interceptor_Manager() : gamemode_amx_(nullptr) {}
                ~Interceptor_Manager() = default;

                struct Cache_Data {
                    std::unordered_map<uint32_t, AMX_NATIVE> native_cache;
                    std::unordered_map<uint32_t, std::string> native_name_cache;
                    Shared_Mutex_Type mtx;
                };

                static Cache_Data& Get_Cache_Data() {
                    static Cache_Data data;
                    return data;
                }

                AMX* gamemode_amx_;
                std::unordered_set<AMX*> patched_amx_set_;
                Shared_Mutex_Type patched_amx_mutex_;
        };

        inline int SAMP_SDK_CDECL Amx_Init_Detour(AMX *amx, void *program) {
            int result = Get_Amx_Init_Hook().Call_Original(amx, program);

            if (SAMP_SDK_LIKELY(result == static_cast<int>(Amx_Error::None)))
                Amx_Manager::Instance().Add_Amx(amx);
            
            return result;
        }

        inline int SAMP_SDK_CDECL Amx_Cleanup_Detour(AMX *amx) {
            Amx_Manager::Instance().Remove_Amx(amx);
            Interceptor_Manager::Instance().On_Amx_Cleanup(amx);

            return Get_Amx_Cleanup_Hook().Call_Original(amx);
        }

        inline int SAMP_SDK_CDECL Amx_Register_Detour(AMX* amx, const AMX_NATIVE_INFO* nativelist, int number) {
            auto& hook_manager = Native_Hook_Manager::Instance();
            std::vector<AMX_NATIVE_INFO> modified_list;
            int count = 0;

            for (const AMX_NATIVE_INFO* p = nativelist; (number == -1 || count < number) && p->name != nullptr; ++p, ++count)
                modified_list.push_back(*p);

            for (int i = 0; i < count; ++i) {
                uint32_t hash = FNV1a_Hash(modified_list[i].name);

                if (hook_manager.Find_Hook(hash)) {
                    if (auto trampoline = hook_manager.Get_Trampoline(hash))
                        modified_list[i].func = trampoline;
                }
            }

            Interceptor_Manager::Instance().Update_Native_Cache(modified_list.data(), count);

            return Get_Amx_Register_Hook().Call_Original(amx, nativelist, number);
        }

        inline int SAMP_SDK_CDECL Amx_Find_Public_Detour(AMX* amx, const char* name, int* index) {
            int error = Get_Amx_Find_Public_Hook().Call_Original(amx, name, index);

            if (Interceptor_Manager::Instance().Is_Gamemode_Amx(amx)) {
                tl_public_name = std::make_unique<std::string>(name);

                if (error != static_cast<int>(Amx_Error::None)) {
                    bool has_handler = Public_Dispatcher::Instance().Has_Handler(FNV1a_Hash(name));

                    if (!has_handler && Get_Has_Public_Handler())
                        has_handler = Get_Has_Public_Handler()(name);

                    if (has_handler)
                        return (*index = PLUGIN_EXEC_GHOST_PUBLIC, static_cast<int>(Amx_Error::None));
                }
            }

            return error;
        }
        
        inline int SAMP_SDK_CDECL Amx_Exec_Detour(AMX* amx, cell* retval, int index) {
            auto& manager = Interceptor_Manager::Instance();
            
            std::unique_ptr<std::string> public_name_ptr;

            if (index == AMX_EXEC_MAIN) {
                manager.Set_Gamemode_Amx(amx);
                public_name_ptr = std::make_unique<std::string>("OnGameModeInit");
            }
            else if (manager.Is_Gamemode_Amx(amx) && index != AMX_EXEC_CONT) {
                if (tl_public_name)
                    public_name_ptr = std::move(tl_public_name);
            }

            if (public_name_ptr) {
                if (Get_Public_Handler()) {
                    cell result = 1;
                    bool should_continue_pawn = Get_Public_Handler()(*public_name_ptr, amx, result);
                    
                    if (!should_continue_pawn) {
                        if (retval)
                            *retval = result;
                            
                        amx->stk += amx->paramcount * sizeof(cell);
                        amx->paramcount = 0;

                        return static_cast<int>(Amx_Error::None);
                    }
                }

                cell result = 1;
                bool should_continue = Public_Dispatcher::Instance().Dispatch(FNV1a_Hash(public_name_ptr->c_str()), amx, result);

                if (SAMP_SDK_UNLIKELY(!should_continue)) {
                    if (retval)
                        *retval = result;

                    if (*public_name_ptr == "OnPlayerCommandText") {
                        if (retval)
                            *retval = 1;
                    }

                    amx->stk += amx->paramcount * sizeof(cell);
                    amx->paramcount = 0;

                    return static_cast<int>(Amx_Error::None);
                }
            }
            
            int exec_result = Get_Amx_Exec_Hook().Call_Original(amx, retval, index);

            if (SAMP_SDK_UNLIKELY(!manager.Is_Amx_Patched(amx))) {
                auto& hook_manager = Native_Hook_Manager::Instance();
                auto& hooks_to_apply = hook_manager.Get_All_Hooks();

                if (!hooks_to_apply.empty()) {
                    AMX_HEADER* hdr = reinterpret_cast<AMX_HEADER*>(amx->base);
                    AMX_FUNCSTUBNT* natives = reinterpret_cast<AMX_FUNCSTUBNT*>(reinterpret_cast<unsigned char*>(hdr) + hdr->natives);

                    int num_natives;
                    amx::Num_Natives(amx, &num_natives);

                    for (auto& hook_to_apply : hooks_to_apply) {
                        uint32_t hook_hash = hook_to_apply.Get_Hash();

                        for (int i = 0; i < num_natives; ++i) {
                            const char* native_name = reinterpret_cast<const char*>(reinterpret_cast<unsigned char*>(hdr) + natives[i].nameofs);

                            if (FNV1a_Hash(native_name) == hook_hash) {
                                AMX_NATIVE current_func = reinterpret_cast<AMX_NATIVE>(natives[i].address);

                                hook_to_apply.Set_Next_In_Chain(current_func);

                                AMX_NATIVE trampoline = hook_manager.Get_Trampoline(hook_hash);

                                if (trampoline)
                                    natives[i].address = reinterpret_cast<ucell>(trampoline);
                                
                                break;
                            }
                        }
                    }
                }
                
                manager.On_Amx_Patched(amx);
            }
            
            return exec_result;
        }
    }
}