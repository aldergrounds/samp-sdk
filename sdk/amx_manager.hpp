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

#include <vector>
#include <mutex>
#include <atomic>
#include <algorithm>
//
#include "amx_api.hpp"
#include "amx_defs.h"
#include "version.hpp"
//
#if defined(SAMP_SDK_CXX_MODERN)
    #include <shared_mutex>
#endif

namespace Samp_SDK {
    class Amx_Manager {
        public:
            static Amx_Manager& Instance() {
                static Amx_Manager instance;

                return instance;
            }

            void Add_Amx(AMX* amx) {
                std::lock_guard<Mutex_Type> lock(mtx_);

                loaded_amx_.push_back(amx);
                generation_.fetch_add(1, std::memory_order_relaxed);
            }

            void Remove_Amx(AMX* amx) {
                std::lock_guard<Mutex_Type> lock(mtx_);

                auto it = std::find(loaded_amx_.begin(), loaded_amx_.end(), amx);

                if (it != loaded_amx_.end())
                    loaded_amx_.erase(it);
                
                generation_.fetch_add(1, std::memory_order_relaxed);
            }

            std::vector<AMX*> Get_Amx_Instances() {
#if defined(SAMP_SDK_CXX_MODERN)
                std::shared_lock<Mutex_Type> lock(mtx_);
#elif defined(SAMP_SDK_CXX_14)
                std::lock_guard<Mutex_Type> lock(mtx_);
#endif

                return loaded_amx_;
            }

            AMX* Find_Public(const char* name, int& index) {
#if defined(SAMP_SDK_CXX_MODERN)
                std::shared_lock<Mutex_Type> lock(mtx_);
#elif defined(SAMP_SDK_CXX_14)
                std::lock_guard<Mutex_Type> lock(mtx_);
#endif

                for (auto it = loaded_amx_.rbegin(); it != loaded_amx_.rend(); ++it) {
                    if (amx::Find_Public(*it, name, &index) == 0)
                        return *it;
                }

                return nullptr;
            }
            
            AMX* Get_Primary_Amx() {
#if defined(SAMP_SDK_CXX_MODERN)
                std::shared_lock<Mutex_Type> lock(mtx_);
#elif defined(SAMP_SDK_CXX_14)
                std::lock_guard<Mutex_Type> lock(mtx_);
#endif

                if (SAMP_SDK_UNLIKELY(loaded_amx_.empty()))
                    return nullptr;

                return loaded_amx_.back();
            }

            uint32_t Get_Generation() const {
                return generation_.load(std::memory_order_relaxed);
            }

        private:
            Amx_Manager() = default;
            ~Amx_Manager() = default;
            Amx_Manager(const Amx_Manager&) = delete;
            Amx_Manager& operator=(const Amx_Manager&) = delete;

#if defined(SAMP_SDK_CXX_MODERN)
            using Mutex_Type = std::shared_mutex;
#elif defined(SAMP_SDK_CXX_14)
            using Mutex_Type = std::mutex;
#endif

            std::vector<AMX*> loaded_amx_;
            Mutex_Type mtx_;
            std::atomic<uint32_t> generation_{0};
    };
}