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
#include <type_traits>
#include <cstdarg>
#include <cstdio>
#include <optional>
#include <string_view>
//
#include "amx_api.hpp"
#include "amx_defs.h"

template<class T> using decay_t = std::decay_t<T>;

namespace Samp_SDK {
    inline std::string Format(const char* format, ...) {
        va_list args;
        va_start(args, format);

        va_list args_copy;
        va_copy(args_copy, args);
        int size = std::vsnprintf(nullptr, 0, format, args_copy);
        va_end(args_copy);

        if (size < 0)
            return (va_end(args), "");

        std::string buffer(size, '\0');

        std::vsnprintf(&buffer[0], buffer.size() + 1, format, args);

        va_end(args);

        return buffer;
    }

    inline std::string Get_String(AMX* amx, cell amx_addr) {
        cell* phys_addr = nullptr;

        if (amx::Get_Addr(amx, amx_addr, &phys_addr) != 0)
            return "";
        
        int len = 0;

        if (amx::STR_Len(phys_addr, &len) != 0 || len <= 0)
            return "";

        std::string buffer(len, '\0');
        amx::Get_String(&buffer[0], phys_addr, len + 1);

        return buffer;
    }

    class Native_Params {
        public:
            Native_Params(AMX* amx, cell* params) : amx_(amx), params_(params) {}

            size_t Count() const {
                return (params_ && params_[0] > 0) ? static_cast<size_t>(params_[0] / sizeof(cell)) : 0;
            }

            template<typename T>
            T Get(size_t index) const {
                T value{};
                Get(index, value);

                return value;
            }

            bool Get(size_t index, std::string& out_value) const {
                if ((index + 1) > Count())
                    return false;

                out_value = Get_String(index);
                
                return true;
            }

            template<typename T>
            bool Get(size_t index, T& out_value) const {
                if ((index + 1) > Count())
                    return false;

                cell value = params_[index + 1];

                if constexpr (std::is_floating_point_v<T>)
                    out_value = amx::AMX_CTOF(value);
                else
                    out_value = static_cast<T>(value);
                
                return true;
            }

            std::string Get_String(size_t index) const {
                if ((index + 1) > Count())
                    return "";

                cell amx_addr = params_[index + 1];

                return Samp_SDK::Get_String(amx_, amx_addr);
            }

            template<typename T>
            bool Get_REF(size_t index, T& out_value) const {
                if ((index + 1) > Count())
                    return false;

                cell* phys_addr = nullptr;
                if (amx::Get_Addr(amx_, params_[index + 1], &phys_addr) != 0)
                    return false;

                if constexpr (std::is_floating_point_v<T>)
                    out_value = amx::AMX_CTOF(*phys_addr);
                else
                    out_value = static_cast<T>(*phys_addr);

                return true;
            }

            template<typename T>
            std::optional<T> Get_REF(size_t index) const {
                T value;

                if (Get_REF(index, value))
                    return value;

                return std::nullopt;
            }

            template<typename T>
            bool Set_REF(size_t index, T value) {
                if ((index + 1) > Count())
                    return false;

                cell* phys_addr = nullptr;
                if (amx::Get_Addr(amx_, params_[index + 1], &phys_addr) != 0)
                    return false;

                if constexpr (std::is_floating_point_v<T>)
                    *phys_addr = amx::AMX_FTOC(static_cast<float>(value));
                else
                    *phys_addr = static_cast<cell>(value);

                return true;
            }
            
        private:
            AMX* amx_;
            cell* params_;
    };

    namespace Detail {
        template <typename T>
        SAMP_SDK_FORCE_INLINE bool Push_AMX_Parameter(AMX* amx, T value) {
            if constexpr (std::is_floating_point_v<T>)
                return amx::Push(amx, amx::AMX_FTOC(static_cast<float>(value))) == 0;
            else
                return amx::Push(amx, static_cast<cell>(value)) == 0;
        }
        
        SAMP_SDK_FORCE_INLINE bool Push_AMX_Parameter(AMX* amx, const char* value) {
            cell dumm;

            return amx::Push_String(amx, &dumm, nullptr, value) == 0;
        }

        SAMP_SDK_FORCE_INLINE bool Push_AMX_Parameter(AMX* amx, const std::string& value) {
            return Push_AMX_Parameter(amx, value.c_str());
        }

        SAMP_SDK_FORCE_INLINE bool Push_AMX_Parameter(AMX* amx, std::string_view value) {
            return Push_AMX_Parameter(amx, std::string(value).c_str());
        }

        inline bool Push_AMX_Parameters(AMX* amx) {
            (void)amx;

            return true;
        }

        template<typename T, typename... Args>
        inline bool Push_AMX_Parameters(AMX *amx, T first, Args... rest) {
            if (!Push_AMX_Parameters(amx, rest...))
                return false;
            
            return Push_AMX_Parameter(amx, first);
        }
        
        template<typename T>
        inline void Assign_Parameter_By_Type(AMX* amx, cell* param_val, T& out) {
            if constexpr (std::is_same_v<T, std::string>)
                out = Samp_SDK::Get_String(amx, *param_val);
            else if constexpr (std::is_floating_point_v<T>)
                out = amx::AMX_CTOF(*param_val);
            else
                out = static_cast<T>(*param_val);
        }

        inline void Register_Parameters_Recursive(size_t, AMX*, cell*) {}

        template<typename First, typename... Rest>
        inline void Register_Parameters_Recursive(size_t index, AMX* amx, cell* params, First& first, Rest&... rest) {
            size_t param_count = (params && params[0] > 0) ? static_cast<size_t>(params[0] / sizeof(cell)) : 0;

            if (index < param_count)
                Assign_Parameter_By_Type(amx, &params[index + 1], first);
            
            Register_Parameters_Recursive(index + 1, amx, params, rest...);
        }

        template<typename... Args>
        inline void Register_Parameters_Impl(AMX* amx, cell* params, Args&... args) {
            Register_Parameters_Recursive(0, amx, params, args...);
        }
    }
}