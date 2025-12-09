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
#include <utility>
#include <vector>
#include <functional>
#include <type_traits>
#include <memory>
#include <cstring>
#include <unordered_map>
#include <unordered_set>
//
#include "amx_defs.h" 
#include "amx_helpers.hpp"
#include "amx_manager.hpp"
#include "amx_memory.hpp"
#include "hash.hpp"
#include "interceptor_manager.hpp"
#include "native_hook_manager.hpp"
#include "platform.hpp"
#include "version.hpp"

namespace Samp_SDK {
    enum class Pawn_Call_Type {
        Automatic,
        Native,
        Public
    };

    class Callback_Result {
        public:
            Callback_Result() noexcept : success_(false), value_(0), error_code_(0) {}
            Callback_Result(bool success, cell value) noexcept : success_(success), value_(value), error_code_(0) {}
            Callback_Result(bool success, cell value, int error_code) noexcept : success_(success), value_(value), error_code_(error_code) {}

            explicit operator bool() const noexcept {
                return success_;
            }

            operator cell() const noexcept {
                return value_;
            }

#if defined(SAMP_SDK_CXX_MODERN)
            [[nodiscard]]
#endif
            float As_Float() const noexcept {
                return amx::AMX_CTOF(value_);
            }

#if defined(SAMP_SDK_CXX_MODERN)
            [[nodiscard]]
#endif
            cell Value() const noexcept {
                return value_;
            }

#if defined(SAMP_SDK_CXX_MODERN)
            [[nodiscard]]
#endif
            bool Success() const noexcept {
                return success_;
            }

#if defined(SAMP_SDK_CXX_MODERN)
            [[nodiscard]]
#endif
            int Get_Amx_Error() const noexcept {
                return error_code_;
            }
            
        private:
            bool success_;
            cell value_;
            int error_code_;
    };

    namespace Detail {
        template <typename T>
        struct is_output_arg : std::integral_constant<bool, std::is_lvalue_reference<T>::value && !std::is_const<typename std::remove_reference<T>::type>::value> {};
        
#if defined(SAMP_SDK_CXX_MODERN)
        template<typename T>
        SAMP_SDK_FORCE_INLINE void Assign_From_Cell(AMX* amx, cell* phys_addr, T& out) {
            if constexpr (std::is_same_v<T, std::string>) {
                int len = 0;

                if (SAMP_SDK_LIKELY(amx::STR_Len(phys_addr, &len) == 0 && len > 0)) {
                    out.resize(len);
                    amx::Get_String(&out[0], phys_addr, len + 1);
                }
                else
                    out.clear();
            }
            else if constexpr (std::is_floating_point_v<T>)
                out = amx::AMX_CTOF(*phys_addr);
            else
                out = static_cast<T>(*phys_addr);
        }
#elif defined(SAMP_SDK_CXX_14)
        template<typename T>
        SAMP_SDK_FORCE_INLINE typename std::enable_if<std::is_floating_point<T>::value>::type
        Assign_From_Cell(AMX*, cell* phys_addr, T& out) {
            out = amx::AMX_CTOF(*phys_addr);
        }

        template<typename T>
        SAMP_SDK_FORCE_INLINE typename std::enable_if<!std::is_floating_point<T>::value && !std::is_same<T, std::string>::value>::type
        Assign_From_Cell(AMX*, cell* phys_addr, T& out) {
            out = static_cast<T>(*phys_addr);
        }

        SAMP_SDK_FORCE_INLINE void Assign_From_Cell(AMX* amx, cell* phys_addr, std::string& out) {
            int len = 0;

            if (SAMP_SDK_LIKELY(amx::STR_Len(phys_addr, &len) == 0 && len > 0)) {
                out.resize(len);
                amx::Get_String(&out[0], phys_addr, len + 1);
            }
            else
                out.clear();
        }
#endif

        struct Amx_Sandbox {
            AMX amx;
            AMX_HEADER amx_header;
            std::vector<unsigned char> heap;

            Amx_Sandbox(size_t heap_size = 64 * 1024) : heap(heap_size) {
                Reset();
            }

            void Reset() {
                std::memset(&amx, 0, sizeof(amx));
                std::memset(&amx_header, 0, sizeof(amx_header));
                amx_header.magic = AMX_MAGIC;
                amx_header.file_version = MIN_FILE_VERSION;
                amx_header.amx_version = MIN_AMX_VERSION;
                amx_header.dat = reinterpret_cast<ucell>(heap.data()) - reinterpret_cast<ucell>(&amx_header);
                amx.base = reinterpret_cast<unsigned char*>(&amx_header);
                amx.data = heap.data();
                amx.callback = amx::Callback;
                amx.stp = heap.size();
                amx.stk = heap.size();
                amx.hea = 0;
                amx.flags = AMX_FLAG_NTVREG | AMX_FLAG_RELOC;
            }
        };
        
        inline AMX_NATIVE Find_Native_Func(uint32_t hash) {
            if (Native_Hook_Manager::Instance().Find_Hook(hash)) {
                AMX* primary_amx = Amx_Manager::Instance().Get_Primary_Amx();

                if (primary_amx) {
                    AMX_HEADER* hdr = reinterpret_cast<AMX_HEADER*>(primary_amx->base);
                    AMX_FUNCSTUBNT* natives = reinterpret_cast<AMX_FUNCSTUBNT*>(reinterpret_cast<unsigned char*>(hdr) + hdr->natives);

                    int num_natives;
                    amx::Num_Natives(primary_amx, &num_natives);

                    for (int i = 0; i < num_natives; ++i) {
                        const char* native_name = reinterpret_cast<const char*>(reinterpret_cast<unsigned char*>(hdr) + natives[i].nameofs);
                        
                        if (FNV1a_Hash(native_name) == hash)
                            return reinterpret_cast<AMX_NATIVE>(natives[i].address);
                    }
                }
            }

            return Interceptor_Manager::Instance().Find_Cached_Native(hash);
        }

        namespace Parameter_Processor {
            using Scoped_Mem_Ptr = std::unique_ptr<Amx_Scoped_Memory>;

            SAMP_SDK_FORCE_INLINE cell Process_String_Argument(AMX* amx, std::vector<Scoped_Mem_Ptr>& buffers, const char* str) {
                size_t len = str ? std::strlen(str) : 0;
                buffers.push_back(std::make_unique<Amx_Scoped_Memory>(amx, len + 1));
                auto& mem = *buffers.back();

                if (SAMP_SDK_UNLIKELY(!mem.Is_Valid()))
                    return 0;

                amx::Set_String(mem.Get_Phys_Addr(), str ? str : "", len + 1);
                
                return mem.Get_Amx_Addr();
            }

#if defined(SAMP_SDK_CXX_MODERN)
            template<typename T>
            cell Process_Impl(AMX* amx, std::vector<Scoped_Mem_Ptr>& buffers, std::vector<std::function<void()>>& updaters, T&& p) {
                using Param_Type = decay_t<T>;

                if constexpr (is_output_arg<T&&>{}) {
                    size_t cells_to_allot = std::is_same_v<Param_Type, std::string> ? 256 : 1;
                    buffers.push_back(std::make_unique<Amx_Scoped_Memory>(amx, cells_to_allot));
                    auto& mem = *buffers.back();

                    if (SAMP_SDK_UNLIKELY(!mem.Is_Valid()))
                        return 0;
                    
                    updaters.emplace_back([amx, &p, phys_addr = mem.Get_Phys_Addr()]() {
                        Assign_From_Cell(amx, phys_addr, p);
                    });

                    return mem.Get_Amx_Addr();
                }
                else {
                    if constexpr (std::is_floating_point_v<Param_Type>)
                        return amx::AMX_FTOC(static_cast<float>(p));
                    else if constexpr (std::is_same_v<Param_Type, std::string>)
                        return Process_String_Argument(amx, buffers, p.c_str());
                    else if constexpr (std::is_pointer_v<Param_Type> && std::is_same_v<typename std::remove_cv<typename std::remove_pointer<Param_Type>::type>::type, char>)
                        return Process_String_Argument(amx, buffers, p);
                    else
                        return static_cast<cell>(p);
                }
            }
#elif defined(SAMP_SDK_CXX_14)
            template<typename T>
            cell Process_Impl(AMX* amx, std::vector<Scoped_Mem_Ptr>& buffers, std::vector<std::function<void()>>& updaters, T&& p, std::true_type) {
                using Param_Type = decay_t<T>;
                size_t cells_to_allot = std::is_same<Param_Type, std::string>::value ? 256 : 1;

                buffers.push_back(std::make_unique<Amx_Scoped_Memory>(amx, cells_to_allot));
                auto& mem = *buffers.back();

                if (SAMP_SDK_UNLIKELY(!mem.Is_Valid()))
                    return 0;

                updaters.emplace_back([amx, &p, phys_addr = mem.Get_Phys_Addr()]() {
                    Assign_From_Cell(amx, phys_addr, p);
                });

                return mem.Get_Amx_Addr();
            }

            template<typename T>
            typename std::enable_if<std::is_floating_point<decay_t<T>>::value, cell>::type
            Process_Impl(AMX*, std::vector<Scoped_Mem_Ptr>&, std::vector<std::function<void()>>&, T&& p, std::false_type) {
                return amx::AMX_FTOC(static_cast<float>(p));
            }

            template<typename T>
            typename std::enable_if<std::is_same<decay_t<T>, std::string>::value, cell>::type
            Process_Impl(AMX* amx, std::vector<Scoped_Mem_Ptr>& buffers, std::vector<std::function<void()>>&, T&& p, std::false_type) {
                return Process_String_Argument(amx, buffers, p.c_str());
            }

            template<typename T>
            typename std::enable_if<std::is_pointer<decay_t<T>>::value && std::is_same<typename std::remove_cv<typename std::remove_pointer<decay_t<T>>::type>::type, char>::value, cell>::type
            Process_Impl(AMX* amx, std::vector<Scoped_Mem_Ptr>& buffers, std::vector<std::function<void()>>&, T&& p, std::false_type) {
                return Process_String_Argument(amx, buffers, p);
            }
            
            template<typename T>
            typename std::enable_if<std::is_integral<decay_t<T>>::value || std::is_enum<decay_t<T>>::value, cell>::type
            Process_Impl(AMX*, std::vector<Scoped_Mem_Ptr>&, std::vector<std::function<void()>>&, T&& p, std::false_type) {
                return static_cast<cell>(p);
            }
#endif
            
            template<typename T>
            cell Process(AMX* amx, std::vector<Scoped_Mem_Ptr>& buffers, std::vector<std::function<void()>>& updaters, T&& p) {
#if defined(SAMP_SDK_CXX_MODERN)
                return Process_Impl(amx, buffers, updaters, std::forward<T>(p));
#elif defined(SAMP_SDK_CXX_14)
                return Process_Impl(amx, buffers, updaters, std::forward<T>(p), is_output_arg<T&&>{});
#endif
            }
        }
        
        struct Caller_Cache {
            std::unordered_map<uint32_t, std::pair<AMX*, int>> public_cache;
            std::unordered_set<uint32_t> failure_cache;
            uint32_t generation = static_cast<uint32_t>(-1);
        };
        
        template<Pawn_Call_Type Call_Type>
        struct Caller;

        namespace Shared_Caller_Logic {
            template<typename... Args>
            inline Callback_Result Call_Native(uint32_t func_hash, Args&&... args) {
                AMX_NATIVE native_func = Find_Native_Func(func_hash);

                if (SAMP_SDK_LIKELY(native_func != nullptr)) {
#if defined(__cpp_threadsafe_static_init) && __cpp_threadsafe_static_init >= 200806L
                    static thread_local Amx_Sandbox sandbox;
#else
                    static Amx_Sandbox sandbox;
#endif
                    sandbox.Reset();
                    AMX* amx_fake = &sandbox.amx;
                    
                    std::vector<std::unique_ptr<Amx_Scoped_Memory>> param_buffers;
                    std::vector<std::function<void()>> post_call_updaters;
                    std::vector<cell> params_vec(sizeof...(Args) + 1);
                    params_vec[0] = sizeof...(Args) * sizeof(cell);
                    
                    int current_param = 1;

                    (void)std::initializer_list<int> {
                        (params_vec[current_param++] = Parameter_Processor::Process(amx_fake, param_buffers, post_call_updaters, std::forward<Args>(args)), 0)...
                    };

                    cell retval = native_func(amx_fake, params_vec.data());

                    for (const auto& updater : post_call_updaters)
                        updater();

                    return Callback_Result(true, retval);
                }

                return Callback_Result();
            }

            template<typename... Args>
            inline Callback_Result Call_Public(uint32_t func_hash, const char* func_name_for_log, Args&&... args) {
#if defined(__cpp_threadsafe_static_init) && __cpp_threadsafe_static_init >= 200806L
                static thread_local Caller_Cache cache;
#else
                static Caller_Cache cache;
#endif
                auto& amx_manager = Amx_Manager::Instance();
                uint32_t current_generation = amx_manager.Get_Generation();

                if (cache.generation != current_generation) {
                    cache.public_cache.clear();
                    cache.failure_cache.clear();
                    cache.generation = current_generation;
                }

                if (SAMP_SDK_UNLIKELY(cache.failure_cache.count(func_hash)))
                    return Callback_Result();

                auto it = cache.public_cache.find(func_hash);
                AMX* amx = nullptr;
                int pub_index = -1;

                if (it != cache.public_cache.end()) {
                    amx = it->second.first;
                    pub_index = it->second.second;
                }
                else {
                    amx = amx_manager.Find_Public(func_name_for_log, pub_index);
                    cache.public_cache.emplace(func_hash, std::make_pair(amx, pub_index));
                }

                if (SAMP_SDK_LIKELY(amx)) {
                    cell hea_before = amx->hea, stk_before = amx->stk;
                    std::vector<std::unique_ptr<Amx_Scoped_Memory>> param_buffers;
                    std::vector<std::function<void()>> post_call_updaters;
                    
                    std::vector<cell> params_vec;
                    params_vec.reserve(sizeof...(Args));

                    (void)std::initializer_list<int>{
                        (params_vec.push_back(Parameter_Processor::Process(amx, param_buffers, post_call_updaters, std::forward<Args>(args))), 0)...
                    };

                    for (auto rit = params_vec.rbegin(); rit != params_vec.rend(); ++rit)
                        amx::Push(amx, *rit);
                    
                    cell retval = 0;
                    int error = amx::Exec(amx, &retval, pub_index);
                    amx->hea = hea_before;
                    amx->stk = stk_before;

                    if (SAMP_SDK_LIKELY(error == 0 || error == static_cast<int>(Amx_Error::Sleep))) {
                        for (const auto& updater : post_call_updaters)
                            updater();

                        return Callback_Result(true, retval);
                    }

                    return Callback_Result(false, 0, error);
                }
                
                cache.failure_cache.insert(func_hash);

                return Callback_Result();
            }
        }

        template<>
        struct Caller<Pawn_Call_Type::Native> {
            template<typename... Args>
            static inline Callback_Result Call(uint32_t func_hash, const char* func_name_for_log, Args&&... args) {
                (void)func_name_for_log;

                return Shared_Caller_Logic::Call_Native(func_hash, std::forward<Args>(args)...);
            }
        };

        template<>
        struct Caller<Pawn_Call_Type::Public> {
            template<typename... Args>
            static inline Callback_Result Call(uint32_t func_hash, const char* func_name_for_log, Args&&... args) {
                return Shared_Caller_Logic::Call_Public(func_hash, func_name_for_log, std::forward<Args>(args)...);
            }
        };

        template<>
        struct Caller<Pawn_Call_Type::Automatic> {
            template<typename... Args>
            static inline Callback_Result Call(uint32_t func_hash, const char* func_name_for_log, Args&&... args) {
                if (SAMP_SDK_LIKELY(Find_Native_Func(func_hash) != nullptr))
                    return Shared_Caller_Logic::Call_Native(func_hash, std::forward<Args>(args)...);

                return Shared_Caller_Logic::Call_Public(func_hash, func_name_for_log, std::forward<Args>(args)...);
            }
        };
    }
}