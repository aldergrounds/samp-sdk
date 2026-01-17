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

#include "../amx/amx_defs.h"
#include "../core/platform.hpp"

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