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

#include "amx_defs.h"
#include "platform.hpp"

extern "C" {
    cell SAMP_SDK_CDECL Dispatch_Hook(int hook_id, AMX* amx, cell* params);
}

namespace Samp_SDK {
    namespace Detail {
        namespace Assembly {
#if defined(SAMP_SDK_COMPILER_MSVC)
            __declspec(naked) inline void Dispatch_Wrapper_Asm() {
                __asm {
                    push ecx
                    push edx

                    mov ecx, [esp + 12]
                    mov edx, [esp + 16]

                    push edx
                    push ecx
                    push eax

                    call Dispatch_Hook

                    add esp, 12

                    pop edx
                    pop ecx

                    ret
                }
            }
#elif defined(SAMP_SDK_COMPILER_GCC_OR_CLANG)
            extern "C" void Dispatch_Wrapper_Asm(void);
#if defined(SAMP_SDK_IMPLEMENTATION)
#if defined(SAMP_SDK_WINDOWS)
            __asm__(
                ".text\n"
                ".globl _Dispatch_Wrapper_Asm\n"
                "_Dispatch_Wrapper_Asm:\n"

                "    push %ecx\n"
                "    push %edx\n"

                "    mov 12(%esp), %ecx\n"
                "    mov 16(%esp), %edx\n"

                "    push %edx\n"
                "    push %ecx\n"
                "    push %eax\n"

                "    call _Dispatch_Hook\n"

                "    add $12, %esp\n"

                "    pop %edx\n"
                "    pop %ecx\n"

                "    ret\n"
            );
#elif defined(SAMP_SDK_LINUX)
            __asm__(
                ".section .text\n"
                ".globl Dispatch_Wrapper_Asm\n"
                ".type Dispatch_Wrapper_Asm, @function\n"
                "Dispatch_Wrapper_Asm:\n"

                "    push %ecx\n"
                "    push %edx\n"

                "    mov 12(%esp), %ecx\n"
                "    mov 16(%esp), %edx\n"

                "    push %edx\n"
                "    push %ecx\n"
                "    push %eax\n"

                "    call Dispatch_Hook\n"

                "    add $12, %esp\n"

                "    pop %edx\n"
                "    pop %ecx\n"

                "    ret\n"

                ".size Dispatch_Wrapper_Asm, . - Dispatch_Wrapper_Asm\n"
            );
#endif
#endif
#endif
        }
    }
}