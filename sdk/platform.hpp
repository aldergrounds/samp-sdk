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

#if defined (__cplusplus)
    #define SAMP_SDK_EXTERN_C extern "C"
#else
    #define SAMP_SDK_EXTERN_C
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

#if (defined(SAMP_SDK_COMPILER_MSVC) && _MSVC_LANG >= 202002L) || (defined(__cplusplus) && __cplusplus >= 202002L)
    #define SAMP_SDK_LIKELY(x) (x) [[likely]]
    #define SAMP_SDK_UNLIKELY(x) (x) [[unlikely]]
#elif defined(SAMP_SDK_COMPILER_GCC_OR_CLANG)
    #define SAMP_SDK_LIKELY(x) __builtin_expect(!!(x), 1)
    #define SAMP_SDK_UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
    #define SAMP_SDK_LIKELY(x) (x)
    #define SAMP_SDK_UNLIKELY(x) (x)
#endif