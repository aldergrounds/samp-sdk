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

#include <string>
#include <vector>
#include <functional>
#include <unordered_map>
#include <tuple>
#include <utility>
//
#include "../amx/amx_defs.h"
#include "../amx/amx_helpers.hpp"
#include "../utils/hash.hpp"

namespace Samp_SDK {
    namespace Detail {
        namespace Public_Param_Reader {
            SAMP_SDK_FORCE_INLINE bool Get_Stack_Cell(AMX* amx, int index, cell& value) {
                AMX_HEADER* hdr = reinterpret_cast<AMX_HEADER*>(amx->base);
                unsigned char* data = (amx->data != nullptr) ? amx->data : amx->base + hdr->dat;
                cell* addr = reinterpret_cast<cell*>(data + amx->stk + (index * sizeof(cell)));

                if (reinterpret_cast<ucell>(addr) < reinterpret_cast<ucell>(data) || reinterpret_cast<ucell>(addr) >= reinterpret_cast<ucell>(data + amx->stp))
                    return false;

                value = *addr;

                return true;
            }

            inline void Get_Public_Params_Recursive(AMX*, int) {}

            template<typename First, typename... Rest>
            inline void Get_Public_Params_Recursive(AMX* amx, int index, First& first, Rest&... rest) {
                cell value;

                if (Get_Stack_Cell(amx, index, value)) {
                    if constexpr (std::is_same_v<decay_t<First>, std::string>)
                        first = Samp_SDK::Get_String(amx, value);
                    else if constexpr (std::is_floating_point_v<decay_t<First>>)
                        first = amx::AMX_CTOF(value);
                    else
                        first = static_cast<decay_t<First>>(value);
                }

                Get_Public_Params_Recursive(amx, index + 1, rest...);
            }

            template<typename... Args>
            inline bool Get_Public_Params(AMX* amx, Args&... args) {
                return (Get_Public_Params_Recursive(amx, 0, args...), true);
            }
        }

        template<typename F, typename Tuple, std::size_t... I>
        decltype(auto) apply_impl(F&& f, Tuple&& t, std::index_sequence<I...>) {
            return std::forward<F>(f)(std::get<I>(std::forward<Tuple>(t))...);
        }

        template<typename F, typename Tuple>
        decltype(auto) apply(F&& f, Tuple&& t) {
            return apply_impl(std::forward<F>(f), std::forward<Tuple>(t), std::make_index_sequence<std::tuple_size<typename std::remove_reference<Tuple>::type>::value>{});
        }

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

                        if (result == PUBLIC_STOP)
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

                std::apply([&](auto&... args) {
                    Public_Param_Reader::Get_Public_Params(amx, args...);
                }, params_tuple);
                
                return static_cast<cell>(std::apply(func_ptr, params_tuple));
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
