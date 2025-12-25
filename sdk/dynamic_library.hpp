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
//
#include "logger.hpp"
#include "platform.hpp"

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

                    if (!handle_)
                        Log("[SA-MP SDK] Error: Failed to load library '%s'. System error code: %lu", path.c_str(), GetLastError());
#elif defined(SAMP_SDK_LINUX)
                    handle_ = dlopen(path.c_str(), RTLD_NOW);

                    if (!handle_)
                        Log("[SA-MP SDK] Error: Failed to load library '%s'. System error: %s", path.c_str(), dlerror());
#endif
                    return handle_ != nullptr;
                }

                bool Unload() {
                    if (!handle_)
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

                template <typename T>
                [[nodiscard]] T Get_Function(const std::string& name) {
                    if (!handle_)
                        return nullptr;
                    
                    void* func_ptr = nullptr;
#if defined(SAMP_SDK_WINDOWS)
                    func_ptr = reinterpret_cast<void*>(GetProcAddress(reinterpret_cast<HMODULE>(handle_), name.c_str()));
#elif defined(SAMP_SDK_LINUX)
                    func_ptr = dlsym(handle_, name.c_str());
#endif
                    return reinterpret_cast<T>(func_ptr);
                }

                [[nodiscard]] bool Is_Loaded() const {
                    return handle_ != nullptr;
                }
                
            private:
                void* handle_ = nullptr;
        };
    }
}