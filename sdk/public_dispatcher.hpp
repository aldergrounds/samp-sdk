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
#include <vector>
#include <functional>
#include <unordered_map>
#include <tuple>
#include <utility>
//
#include "amx_defs.h"
#include "amx_helpers.hpp"
#include "hash.hpp"
#include "version.hpp"

constexpr cell PLUGIN_PUBLIC_CONTINUE = 1;
constexpr cell PLUGIN_PUBLIC_STOP = 0;

namespace Samp_SDK {
    namespace Detail {
        namespace Public_Param_Reader {
            SAMP_SDK_FORCE_INLINE bool Get_Stack_Cell(AMX* amx, int index, cell& value) {
                AMX_HEADER* hdr = reinterpret_cast<AMX_HEADER*>(amx->base);
                unsigned char* data = (amx->data != nullptr) ? amx->data : amx->base + hdr->dat;
                cell* addr = reinterpret_cast<cell*>(data + amx->stk + (index * sizeof(cell)));

                if (SAMP_SDK_UNLIKELY(reinterpret_cast<ucell>(addr) < reinterpret_cast<ucell>(data) || reinterpret_cast<ucell>(addr) >= reinterpret_cast<ucell>(data + amx->stp)))
                    return false;

                value = *addr;

                return true;
            }

            inline void Get_Public_Params_Recursive(AMX*, int) {}

            template<typename First, typename... Rest>
            inline void Get_Public_Params_Recursive(AMX* amx, int index, First& first, Rest&... rest) {
                cell value;

                if (Get_Stack_Cell(amx, index, value)) {
#if defined(SAMP_SDK_CXX_MODERN)
                    if constexpr (std::is_same_v<decay_t<First>, std::string>)
                        first = Samp_SDK::Get_String(amx, value);
                    else if constexpr (std::is_floating_point_v<decay_t<First>>)
                        first = amx::AMX_CTOF(value);
                    else
                        first = static_cast<decay_t<First>>(value);
#elif defined(SAMP_SDK_CXX_14)
                    Assign_Parameter_By_Type(amx, &value, first);
#endif
                }

                Get_Public_Params_Recursive(amx, index + 1, rest...);
            }

            template<typename... Args>
            inline bool Get_Public_Params(AMX* amx, Args&... args) {
                return (Get_Public_Params_Recursive(amx, 0, args...), true);
            }
        }

#if !defined(SAMP_SDK_CXX_MODERN)
        template<typename F, typename Tuple, std::size_t... I>
        decltype(auto) apply_impl(F&& f, Tuple&& t, std::index_sequence<I...>) {
            return std::forward<F>(f)(std::get<I>(std::forward<Tuple>(t))...);
        }

        template<typename F, typename Tuple>
        decltype(auto) apply(F&& f, Tuple&& t) {
            return apply_impl(std::forward<F>(f), std::forward<Tuple>(t), std::make_index_sequence<std::tuple_size<typename std::remove_reference<Tuple>::type>::value>{});
        }
#endif

        class Public_Dispatcher {
            public:
                using Amx_Handler_Func = std::function<cell(AMX*)>;

                static Public_Dispatcher& Instance() {
                    static Public_Dispatcher instance;

                    return instance;
                }

                void Register(uint32_t hash, Amx_Handler_Func handler) {
                    handlers_[hash].push_back(handler);
                }

                bool Has_Handler(uint32_t hash) const {
                    return handlers_.count(hash) > 0;
                }

                bool Dispatch(uint32_t hash, AMX* amx, cell& result) {
                    auto it = handlers_.find(hash);

                    if (it == handlers_.end())
                        return true;

                    for (auto rit = it->second.rbegin(); rit != it->second.rend(); ++rit) {
                        const auto& handler = *rit;
                        result = handler(amx);

                        if (SAMP_SDK_UNLIKELY(result == PLUGIN_PUBLIC_STOP))
                            return false;
                    }

                    return true;
                }

            private:
                Public_Dispatcher() = default;
                std::unordered_map<uint32_t, std::vector<Amx_Handler_Func>> handlers_;
        };

        template<typename T_Func, T_Func func_ptr>
        struct Public_Traits;

        template<typename Ret, typename... Args, Ret(SAMP_SDK_CALL *func_ptr)(Args...)>
        struct Public_Traits<Ret(SAMP_SDK_CALL *)(Args...), func_ptr> {
            static cell Wrapper(AMX* amx) {
                std::tuple<decay_t<Args>...> params_tuple;

#if defined(SAMP_SDK_CXX_MODERN)
                std::apply([&](auto&... args) {
                    Public_Param_Reader::Get_Public_Params(amx, args...);
                }, params_tuple);
                
                return static_cast<cell>(std::apply(func_ptr, params_tuple));
#elif defined(SAMP_SDK_CXX_14)
                apply([&](auto&... args) {
                    Public_Param_Reader::Get_Public_Params(amx, args...);
                }, params_tuple);
                
                return static_cast<cell>(apply(func_ptr, params_tuple));
#endif
            }
        };
        
        template<typename T_Func, T_Func func_ptr, uint32_t hash>
        class Public_Register {
            public:
                Public_Register() {
                    static bool registered = [&] {
                        return (Public_Dispatcher::Instance().Register(hash, &Public_Traits<T_Func, func_ptr>::Wrapper), true);
                    }();

                    (void)registered;
                }
        };
    }
}

#define PLUGIN_PUBLIC_REGISTRATION(name) \
    constexpr uint32_t hash_##name = Samp_SDK::Detail::FNV1a_Hash_Const(#name); \
    Samp_SDK::Detail::Public_Register<decltype(&name), &name, hash_##name> register_##name;
