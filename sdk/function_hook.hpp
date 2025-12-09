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

#include <cstring>
#include <cstdint>
//
#include "platform.hpp"
#include "version.hpp"

#if defined(SAMP_SDK_WINDOWS)
    #include <windows.h>
#elif defined(SAMP_SDK_LINUX)
    #include <unistd.h>
    #include <sys/mman.h>
#endif

namespace Samp_SDK {
    namespace Detail {
        class X86_Detour {
            public:
                static const int JUMP_INSTRUCTION_SIZE = 5;

                X86_Detour() : target_func_(nullptr), detour_func_(nullptr), installed_(false) {
                    std::memset(original_bytes_, 0, JUMP_INSTRUCTION_SIZE);
                }

                bool Apply(void* target, void* detour) {
                    if (SAMP_SDK_UNLIKELY(installed_ || !target || !detour))
                        return false;

                    target_func_ = target;
                    detour_func_ = detour;

                    Unprotect_Memory(target_func_, JUMP_INSTRUCTION_SIZE);
                    std::memcpy(original_bytes_, target_func_, JUMP_INSTRUCTION_SIZE);

                    unsigned char jmp_instruction[JUMP_INSTRUCTION_SIZE];
                    jmp_instruction[0] = 0xE9;

                    uint32_t relative_address = static_cast<uint32_t>(
                        reinterpret_cast<uintptr_t>(detour_func_) - (reinterpret_cast<uintptr_t>(target_func_) + JUMP_INSTRUCTION_SIZE)
                    );
                    
                    std::memcpy(&jmp_instruction[1], &relative_address, sizeof(relative_address));
                    std::memcpy(target_func_, jmp_instruction, JUMP_INSTRUCTION_SIZE);

                    installed_ = true;

                    return true;
                }

                void Revert() {
                    if (SAMP_SDK_UNLIKELY(!installed_))
                        return;
                    
                    Unprotect_Memory(target_func_, JUMP_INSTRUCTION_SIZE);
                    std::memcpy(target_func_, original_bytes_, JUMP_INSTRUCTION_SIZE);
                    installed_ = false;
                }

                void Reapply() {
                    if (SAMP_SDK_UNLIKELY(installed_ || !target_func_ || !detour_func_))
                        return;

                    Unprotect_Memory(target_func_, JUMP_INSTRUCTION_SIZE);
                    unsigned char jmp_instruction[JUMP_INSTRUCTION_SIZE];
                    jmp_instruction[0] = 0xE9;

                    uint32_t relative_address = static_cast<uint32_t>(
                        reinterpret_cast<uintptr_t>(detour_func_) - (reinterpret_cast<uintptr_t>(target_func_) + JUMP_INSTRUCTION_SIZE)
                    );

                    std::memcpy(&jmp_instruction[1], &relative_address, sizeof(relative_address));
                    std::memcpy(target_func_, jmp_instruction, JUMP_INSTRUCTION_SIZE);

                    installed_ = true;
                }

#if defined(SAMP_SDK_CXX_MODERN)
                [[nodiscard]]
#endif
                bool Is_Applied() const {
                    return installed_;
                }

            private:
                static void Unprotect_Memory(void* address, size_t size) {
#if defined(SAMP_SDK_WINDOWS)
                    DWORD old_protect;
                    VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &old_protect);
#elif defined(SAMP_SDK_LINUX)
                    long pagesize = sysconf(_SC_PAGESIZE);
                    uintptr_t page_start = reinterpret_cast<uintptr_t>(address) & -pagesize;
                    mprotect(reinterpret_cast<void*>(page_start), size + (reinterpret_cast<uintptr_t>(address) - page_start), PROT_READ | PROT_WRITE | PROT_EXEC);
#endif
                }

                void* target_func_;
                void* detour_func_;
                unsigned char original_bytes_[JUMP_INSTRUCTION_SIZE];
                bool installed_;
        };

        template <typename FuncPtr>
        class Function_Hook {
            public:
                Function_Hook() : original_func_ptr_(nullptr), detour_func_ptr_(nullptr) {}
                
                ~Function_Hook() {
                    Uninstall();
                }
                
                Function_Hook(const Function_Hook&) = delete;
                Function_Hook& operator=(const Function_Hook&) = delete;
                
                Function_Hook(Function_Hook&&) = default;
                Function_Hook& operator=(Function_Hook&&) = default;


                bool Install(void* target, void* detour) {
                    if (detour_.Is_Applied())
                        return true;

                    original_func_ptr_ = reinterpret_cast<FuncPtr>(target);
                    detour_func_ptr_ = detour;

                    return detour_.Apply(target, detour);
                }

                void Uninstall() {
                    detour_.Revert();
                }

#if defined(SAMP_SDK_CXX_MODERN)
                [[nodiscard]]
#endif
                FuncPtr Get_Original() const {
                    return original_func_ptr_;
                }
                
                template<typename... Args>
                auto Call_Original(Args... args) -> decltype(Get_Original()(args...)) {
                    static thread_local int recursion_guard = 0;
                    
                    bool should_revert = (recursion_guard == 0);

                    if (should_revert)
                        detour_.Revert();
                    
                    recursion_guard++;
                    
                    struct Scope_Guard {
                        int& guard_ref;
                        X86_Detour* detour_ptr;
                        bool should_reapply;
                        
                        ~Scope_Guard() noexcept {
                            guard_ref--;

                            if (should_reapply && guard_ref == 0) {
                                try {
                                    detour_ptr->Reapply();
                                }
                                catch (...) {}
                            }
                        }
                    };
                    
                    Scope_Guard guard{recursion_guard, &detour_, should_revert};
                    
                    return Get_Original()(args...);
                }
                
            private:
                X86_Detour detour_;
                FuncPtr original_func_ptr_;
                void* detour_func_ptr_;
        };
    }
}