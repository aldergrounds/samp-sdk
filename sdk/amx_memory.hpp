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

#include "amx_api.hpp"
#include "amx_defs.h"
#include "version.hpp"

namespace Samp_SDK {
    class Amx_Scoped_Memory {
        public:
            Amx_Scoped_Memory() : amx_(nullptr), amx_addr_(0), phys_addr_(nullptr) {}

            Amx_Scoped_Memory(AMX* amx, int cells) : amx_(amx), amx_addr_(0), phys_addr_(nullptr) {
                if (SAMP_SDK_UNLIKELY(amx::Allot(amx, cells, &amx_addr_, &phys_addr_) != static_cast<int>(Amx_Error::None))) {
                    amx_addr_ = 0;
                    phys_addr_ = nullptr;
                }
            }

            ~Amx_Scoped_Memory() {
                if (SAMP_SDK_LIKELY(amx_ != nullptr && amx_addr_ != 0))
                    amx::Release(amx_, amx_addr_);
            }

            Amx_Scoped_Memory(const Amx_Scoped_Memory&) = delete;
            Amx_Scoped_Memory& operator=(const Amx_Scoped_Memory&) = delete;

            Amx_Scoped_Memory(Amx_Scoped_Memory&& other) noexcept : amx_(other.amx_), amx_addr_(other.amx_addr_), phys_addr_(other.phys_addr_) {
                other.amx_ = nullptr;
                other.amx_addr_ = 0;
                other.phys_addr_ = nullptr;
            }

            Amx_Scoped_Memory& operator=(Amx_Scoped_Memory&& other) noexcept {
                if (this != &other) {
                    if (SAMP_SDK_LIKELY(amx_ != nullptr && amx_addr_ != 0))
                        amx::Release(amx_, amx_addr_);

                    amx_ = other.amx_;
                    amx_addr_ = other.amx_addr_;
                    phys_addr_ = other.phys_addr_;
                    other.amx_ = nullptr;
                    other.amx_addr_ = 0;
                    other.phys_addr_ = nullptr;
                }

                return *this;
            }

#if defined(SAMP_SDK_CXX_MODERN)
            [[nodiscard]]
#endif
            cell Get_Amx_Addr() const {
                return amx_addr_;
            }

#if defined(SAMP_SDK_CXX_MODERN)
            [[nodiscard]]
#endif
            cell* Get_Phys_Addr() const {
                return phys_addr_;
            }

#if defined(SAMP_SDK_CXX_MODERN)
            [[nodiscard]]
#endif
            bool Is_Valid() const {
                return phys_addr_ != nullptr;
            }

            explicit operator bool() const {
                return Is_Valid();
            }
            
        private:
            AMX* amx_;
            cell amx_addr_;
            cell* phys_addr_;
    };
}