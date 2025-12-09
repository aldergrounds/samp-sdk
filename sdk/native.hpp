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

#if defined(SAMP_SDK_WANT_AMX_EVENTS)

#include <string>
#include <vector>
#include <functional>
#include <mutex>
#include <unordered_map>
//
#include "amx_api.hpp"
#include "amx_defs.h"
#include "callbacks.hpp"
#include "platform.hpp"
#include "version.hpp"

namespace Samp_SDK {
    using Native_Handler = cell (SAMP_SDK_CDECL *)(AMX* amx, cell* params);

    class Native {
        public:
            Native(const char* name, Native_Handler func) : name_(name), handler_(func) {}

#if defined(SAMP_SDK_CXX_MODERN)
            [[nodiscard]]
#endif
            const std::string& Get_Name() const {
                return name_;
            }

#if defined(SAMP_SDK_CXX_MODERN)
            [[nodiscard]]
#endif
            Native_Handler Get_Handler() const {
                return handler_;
            }

        private:
            std::string name_;
            Native_Handler handler_;
    };
    
    namespace Detail {
        using Force_Inclusion_Func = void(*)();

        class Native_List_Holder {
            public:
                static Native_List_Holder& Instance() {
                    static Native_List_Holder instance;

                    return instance;
                }

                void Add(const char* name, Native_Handler func) {
                    std::lock_guard<std::mutex> lock(mtx_);
                    natives_.emplace_back(name, func);
                }

                void Add_Plugin_Native(uint32_t hash, Native_Handler func) {
                    std::lock_guard<std::mutex> lock(mtx_);
                    plugin_natives_[hash] = func;
                }

                Native_Handler Find_Plugin_Native(uint32_t hash) {
                    std::lock_guard<std::mutex> lock(mtx_);
                    auto it = plugin_natives_.find(hash);
                    
                    return (it != plugin_natives_.end()) ? it->second : nullptr;
                }

#if defined(SAMP_SDK_CXX_MODERN)
                [[nodiscard]]
#endif
                const std::vector<Native>& Get_Natives() const {
                    return natives_;
                }

                static void Dummy_Force_Inclusion_Func() {}

                void Add_Force_Inclusion_Func(Force_Inclusion_Func func) {
                    std::lock_guard<std::mutex> lock(mtx_);

                    if (std::find(force_inclusion_funcs_.begin(), force_inclusion_funcs_.end(), func) == force_inclusion_funcs_.end())
                        force_inclusion_funcs_.push_back(func);
                }

#if defined(SAMP_SDK_CXX_MODERN)
                [[nodiscard]]
#endif
                const std::vector<Force_Inclusion_Func>& Get_Force_Inclusion_Funcs() const {
                    return force_inclusion_funcs_;
                }

            private:
                Native_List_Holder() = default;
                std::vector<Native> natives_;
                std::vector<Force_Inclusion_Func> force_inclusion_funcs_;
                std::unordered_map<uint32_t, Native_Handler> plugin_natives_;
                std::mutex mtx_;
        };

        class Native_Register {
            public:
                Native_Register(const char* name, Native_Handler func) {
                    Native_List_Holder::Instance().Add(name, func);
                    Native_List_Holder::Instance().Add_Plugin_Native(FNV1a_Hash_Const(name), func);
                    Native_List_Holder::Instance().Add_Force_Inclusion_Func(&Native_List_Holder::Dummy_Force_Inclusion_Func);
                }
        };

        template<typename... Args>
        inline Callback_Result Plugin_Call_Impl(uint32_t native_hash, Args&&... args) {
            Native_Handler native_func = Native_List_Holder::Instance().Find_Plugin_Native(native_hash);

            if (SAMP_SDK_LIKELY(native_func != nullptr)) {
                static thread_local Amx_Sandbox sandbox;
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
    }

    class Native_Registry {
        public:
            Native_Registry() = default;
            
            explicit Native_Registry(const std::vector<Native>& natives) : natives_(natives) {
                if (natives_.empty())
                    return;

                amx_natives_info_.reserve(natives_.size() + 1);

                for (const auto& native : natives_)
                    amx_natives_info_.push_back({native.Get_Name().c_str(), (AMX_NATIVE)native.Get_Handler()});

                amx_natives_info_.push_back({nullptr, nullptr});
            }

            void Register_All(AMX* amx) const {
                if (SAMP_SDK_UNLIKELY(amx_natives_info_.empty()))
                    return;
                
                amx::Register(amx, amx_natives_info_.data(), -1);
            }

#if defined(SAMP_SDK_CXX_MODERN)
            [[nodiscard]]
#endif
            bool Is_Empty() const {
                return natives_.empty();
            }
            
        private:
            std::vector<Native> natives_;
            std::vector<AMX_NATIVE_INFO> amx_natives_info_;
    };
}

#endif