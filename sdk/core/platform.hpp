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

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
    #define SAMP_SDK_WINDOWS
#elif defined(LINUX) || defined(__linux__)
    #define SAMP_SDK_LINUX
#else
    #error "Platform not supported. This SDK only supports Windows and Linux."
#endif

#if defined(_MSC_VER)
    #define SAMP_SDK_COMPILER_MSVC
#elif defined(__GNUC__) || defined(__clang__)
    #define SAMP_SDK_COMPILER_GCC_OR_CLANG
#else
    #error "Unsupported compiler. This SDK only supports MSVC (Visual Studio), GCC, and Clang."
#endif

#if !defined(_M_IX86) && !defined(__i386__)
    #if defined(SAMP_SDK_WINDOWS)
        #error "This plugin must be compiled for the x86 (32-bit) architecture on Windows. Please check your compiler settings."
    #elif defined(SAMP_SDK_LINUX)
        #error "This plugin must be compiled for the i386 (32-bit) architecture on Linux. Use the -m32 compiler flag."
    #endif
#endif

#if defined(__cplusplus)
    #if (defined(_MSVC_LANG) && _MSVC_LANG < 201703L) || (!defined(_MSVC_LANG) && __cplusplus < 201703L)
        #error "This SDK requires C++17 or later. Please update your compiler settings."
    #endif

    #define SAMP_SDK_EXTERN_C extern "C"
#else
    #error "This SDK requires a C++ compiler."
#endif

#if defined(SAMP_SDK_WINDOWS)
    #if defined(SAMP_SDK_COMPILER_GCC_OR_CLANG)
        #define SAMP_SDK_API __attribute__((dllexport))
    #else
        #define SAMP_SDK_API
    #endif

    #define SAMP_SDK_CALL __stdcall
    #define SAMP_SDK_EXPORT SAMP_SDK_EXTERN_C SAMP_SDK_API
#elif defined(SAMP_SDK_LINUX)
    #define SAMP_SDK_CALL
    #define SAMP_SDK_EXPORT SAMP_SDK_EXTERN_C __attribute__((visibility("default")))
#endif

#if defined(SAMP_SDK_COMPILER_MSVC)
    #define SAMP_SDK_CDECL __cdecl
#elif defined(SAMP_SDK_COMPILER_GCC_OR_CLANG)
    #define SAMP_SDK_CDECL __attribute__((cdecl))
#endif

#if defined(SAMP_SDK_COMPILER_GCC_OR_CLANG)
    #define SAMP_SDK_USED_BY_ASM __attribute__((used))
#else
    #define SAMP_SDK_USED_BY_ASM
#endif

#if defined(SAMP_SDK_COMPILER_MSVC)
    #define SAMP_SDK_FORCE_INLINE __forceinline
#elif defined(SAMP_SDK_COMPILER_GCC_OR_CLANG)
    #define SAMP_SDK_FORCE_INLINE __attribute__((always_inline)) inline
#endif