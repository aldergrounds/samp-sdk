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
//
#include "platform.hpp"
#include "logger.hpp"
#include "version.hpp"

#if defined(SAMP_SDK_WINDOWS)
    #include <windows.h>
#elif defined(SAMP_SDK_LINUX)
    #include <dlfcn.h>
#endif

namespace Samp_SDK {
    namespace Detail {
        class Dynamic_Library {
            public:
                Dynamic_Library() = default;

                bool Load(const std::string& path) {
#if defined(SAMP_SDK_WINDOWS)
                    handle_ = LoadLibraryA(path.c_str());

                    if (SAMP_SDK_UNLIKELY(!handle_))
                        Log("[SA-MP SDK] Error: Failed to load library '%s'. System error code: %lu", path.c_str(), GetLastError());
#elif defined(SAMP_SDK_LINUX)
                    handle_ = dlopen(path.c_str(), RTLD_NOW);

                    if (SAMP_SDK_UNLIKELY(!handle_))
                        Log("[SA-MP SDK] Error: Failed to load library '%s'. System error: %s", path.c_str(), dlerror());
#endif
                    return handle_ != nullptr;
                }

                bool Unload() {
                    if (SAMP_SDK_UNLIKELY(!handle_))
                        return true;

#if defined(SAMP_SDK_WINDOWS)
                    bool success = FreeLibrary(reinterpret_cast<HMODULE>(handle_)) != 0;
#elif defined(SAMP_SDK_LINUX)
                    bool success = dlclose(handle_) == 0;
#endif
                    if (success)
                        handle_ = nullptr;
                        
                    return success;
                }

#if defined(SAMP_SDK_CXX_MODERN)
                template <typename T>
                [[nodiscard]] T Get_Function(const std::string& name) {
#elif defined(SAMP_SDK_CXX_14)
                template <typename T>
                T Get_Function(const std::string& name) {
#endif
                    if (SAMP_SDK_UNLIKELY(!handle_))
                        return nullptr;
                    
                    void* func_ptr = nullptr;
#if defined(SAMP_SDK_WINDOWS)
                    func_ptr = reinterpret_cast<void*>(GetProcAddress(reinterpret_cast<HMODULE>(handle_), name.c_str()));
#elif defined(SAMP_SDK_LINUX)
                    func_ptr = dlsym(handle_, name.c_str());
#endif
                    return reinterpret_cast<T>(func_ptr);
                }

#if defined(SAMP_SDK_CXX_MODERN)
                [[nodiscard]]
#endif
                bool Is_Loaded() const {
                    return handle_ != nullptr;
                }
                
            private:
                void* handle_ = nullptr;
        };
    }
}