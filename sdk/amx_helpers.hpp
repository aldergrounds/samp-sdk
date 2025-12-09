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
#include <type_traits>
#include <cstdarg>
#include <cstdio>
//
#include "amx_api.hpp"
#include "amx_defs.h"
#include "version.hpp"
//
#if defined(SAMP_SDK_CXX_MODERN)
    #include <optional>
    #include <string_view>
    
    template<class T> using decay_t = std::decay_t<T>;
#elif defined(SAMP_SDK_CXX_14)
    template<class T> using decay_t = typename std::decay<T>::type;
#endif

namespace Samp_SDK {
    inline std::string Format(const char* format, ...) {
        va_list args;
        va_start(args, format);

        va_list args_copy;
        va_copy(args_copy, args);
        int size = std::vsnprintf(nullptr, 0, format, args_copy);
        va_end(args_copy);

        if (SAMP_SDK_UNLIKELY(size < 0))
            return (va_end(args), "");

        std::string buffer(size, '\0');

        std::vsnprintf(&buffer[0], buffer.size() + 1, format, args);

        va_end(args);

        return buffer;
    }

    inline std::string Get_String(AMX* amx, cell amx_addr) {
        cell* phys_addr = nullptr;

        if (SAMP_SDK_UNLIKELY(amx::Get_Addr(amx, amx_addr, &phys_addr) != 0))
            return "";
        
        int len = 0;

        if (SAMP_SDK_UNLIKELY(amx::STR_Len(phys_addr, &len) != 0 || len <= 0))
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
                if (SAMP_SDK_UNLIKELY((index + 1) > Count()))
                    return false;

                out_value = Get_String(index);
                
                return true;
            }

#if defined(SAMP_SDK_CXX_MODERN)
            template<typename T>
            bool Get(size_t index, T& out_value) const {
                if (SAMP_SDK_UNLIKELY((index + 1) > Count()))
                    return false;

                cell value = params_[index + 1];

                if constexpr (std::is_floating_point_v<T>)
                    out_value = amx::AMX_CTOF(value);
                else
                    out_value = static_cast<T>(value);
                
                return true;
            }
#elif defined(SAMP_SDK_CXX_14)
            template<typename T>
            typename std::enable_if<std::is_floating_point<T>::value, bool>::type
            Get(size_t index, T& out_value) const {
                if (SAMP_SDK_UNLIKELY((index + 1) > Count()))
                    return false;

                cell value = params_[index + 1];
                out_value = static_cast<T>(amx::AMX_CTOF(value));

                return true;
            }

            template<typename T>
            typename std::enable_if<!std::is_floating_point<T>::value && !std::is_same<T, std::string>::value, bool>::type
            Get(size_t index, T& out_value) const {
                if (SAMP_SDK_UNLIKELY((index + 1) > Count()))
                    return false;

                cell value = params_[index + 1];
                out_value = static_cast<T>(value);

                return true;
            }
#endif

            std::string Get_String(size_t index) const {
                if (SAMP_SDK_UNLIKELY((index + 1) > Count()))
                    return "";

                cell amx_addr = params_[index + 1];

                return Samp_SDK::Get_String(amx_, amx_addr);
            }

            template<typename T>
            bool Get_REF(size_t index, T& out_value) const {
                if (SAMP_SDK_UNLIKELY((index + 1) > Count()))
                    return false;

                cell* phys_addr = nullptr;
                if (SAMP_SDK_UNLIKELY(amx::Get_Addr(amx_, params_[index + 1], &phys_addr) != 0))
                    return false;

#if defined(SAMP_SDK_CXX_MODERN)
                if constexpr (std::is_floating_point_v<T>)
                    out_value = amx::AMX_CTOF(*phys_addr);
                else
                    out_value = static_cast<T>(*phys_addr);
#elif defined(SAMP_SDK_CXX_14)
                if (std::is_floating_point<T>::value)
                    out_value = amx::AMX_CTOF(*phys_addr);
                else
                    out_value = static_cast<T>(*phys_addr);
#endif

                return true;
            }

#if defined(SAMP_SDK_CXX_MODERN)
            template<typename T>
            std::optional<T> Get_REF(size_t index) const {
                T value;

                if (Get_REF(index, value))
                    return value;

                return std::nullopt;
            }
#endif
            template<typename T>
            bool Set_REF(size_t index, T value) {
                if (SAMP_SDK_UNLIKELY((index + 1) > Count()))
                    return false;

                cell* phys_addr = nullptr;
                if (SAMP_SDK_UNLIKELY(amx::Get_Addr(amx_, params_[index + 1], &phys_addr) != 0))
                    return false;

#if defined(SAMP_SDK_CXX_MODERN)
                if constexpr (std::is_floating_point_v<T>)
                    *phys_addr = amx::AMX_FTOC(static_cast<float>(value));
                else
                    *phys_addr = static_cast<cell>(value);
#elif defined(SAMP_SDK_CXX_14)
                if (std::is_floating_point<T>::value)
                    *phys_addr = amx::AMX_FTOC(static_cast<float>(value));
                else
                    *phys_addr = static_cast<cell>(value);
#endif

                return true;
            }
            
        private:
            AMX* amx_;
            cell* params_;
    };

    namespace Detail {
#if defined(SAMP_SDK_CXX_MODERN)
        template <typename T>
        SAMP_SDK_FORCE_INLINE bool Push_AMX_Parameter(AMX* amx, T value) {
            if constexpr (std::is_floating_point_v<T>)
                return amx::Push(amx, amx::AMX_FTOC(static_cast<float>(value))) == 0;
            else
                return amx::Push(amx, static_cast<cell>(value)) == 0;
        }
#elif defined(SAMP_SDK_CXX_14)
        template <typename T>
        SAMP_SDK_FORCE_INLINE typename std::enable_if<std::is_floating_point<T>::value, bool>::type
        Push_AMX_Parameter(AMX* amx, T value) {
            return amx::Push(amx, amx::AMX_FTOC(static_cast<float>(value))) == 0;
        }

        template <typename T>
        SAMP_SDK_FORCE_INLINE typename std::enable_if<!std::is_floating_point<T>::value, bool>::type
        Push_AMX_Parameter(AMX* amx, T value) {
            return amx::Push(amx, static_cast<cell>(value)) == 0;
        }
#endif
        
        SAMP_SDK_FORCE_INLINE bool Push_AMX_Parameter(AMX* amx, const char* value) {
            cell dumm;

            return amx::Push_String(amx, &dumm, nullptr, value) == 0;
        }

        SAMP_SDK_FORCE_INLINE bool Push_AMX_Parameter(AMX* amx, const std::string& value) {
            return Push_AMX_Parameter(amx, value.c_str());
        }

#if defined(SAMP_SDK_CXX_MODERN)
        SAMP_SDK_FORCE_INLINE bool Push_AMX_Parameter(AMX* amx, std::string_view value) {
            return Push_AMX_Parameter(amx, std::string(value).c_str());
        }
#endif

        inline bool Push_AMX_Parameters(AMX* amx) {
            (void)amx;

            return true;
        }

        template<typename T, typename... Args>
        inline bool Push_AMX_Parameters(AMX *amx, T first, Args... rest) {
            if (SAMP_SDK_UNLIKELY(!Push_AMX_Parameters(amx, rest...)))
                return false;
            
            return Push_AMX_Parameter(amx, first);
        }
        
#if defined(SAMP_SDK_CXX_MODERN)
        template<typename T>
        inline void Assign_Parameter_By_Type(AMX* amx, cell* param_val, T& out) {
            if constexpr (std::is_same_v<T, std::string>)
                out = Samp_SDK::Get_String(amx, *param_val);
            else if constexpr (std::is_floating_point_v<T>)
                out = amx::AMX_CTOF(*param_val);
            else
                out = static_cast<T>(*param_val);
        }
#elif defined(SAMP_SDK_CXX_14)
        template<typename T>
        inline typename std::enable_if<!std::is_floating_point<T>::value && !std::is_same<T, std::string>::value>::type
        Assign_Parameter_By_Type(AMX* amx, cell* param_val, T& out) {
            (void)amx;
            out = static_cast<T>(*param_val);
        }
        
        template<typename T>
        inline typename std::enable_if<std::is_floating_point<T>::value>::type
        Assign_Parameter_By_Type(AMX* amx, cell* param_val, T& out) {
            (void)amx;
            out = amx::AMX_CTOF(*param_val);
        }

        inline void Assign_Parameter_By_Type(AMX* amx, cell* param_val, std::string& out) {
            out = Samp_SDK::Get_String(amx, *param_val);
        }
#endif

        inline void Register_Parameters_Recursive(size_t, AMX*, cell*) {}

        template<typename First, typename... Rest>
        inline void Register_Parameters_Recursive(size_t index, AMX* amx, cell* params, First& first, Rest&... rest) {
            size_t param_count = (params && params[0] > 0) ? static_cast<size_t>(params[0] / sizeof(cell)) : 0;

            if (SAMP_SDK_LIKELY(index < param_count))
                Assign_Parameter_By_Type(amx, &params[index + 1], first);
            
            Register_Parameters_Recursive(index + 1, amx, params, rest...);
        }

        template<typename... Args>
        inline void Register_Parameters_Impl(AMX* amx, cell* params, Args&... args) {
            Register_Parameters_Recursive(0, amx, params, args...);
        }
    }
}