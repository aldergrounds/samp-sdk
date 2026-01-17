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
#include <vector>
#include <memory>
#include <algorithm>
//
#include "dynamic_library.hpp"
#include "../utils/logger.hpp"
#include "../amx/amx_defs.h"

namespace Samp_SDK {
    namespace Detail {
        using Module_Load_t = bool (SAMP_SDK_CALL *)(void** ppPluginData);
        using Module_Unload_t = void (SAMP_SDK_CALL *)();
        using Module_Supports_t = unsigned int (SAMP_SDK_CALL *)();
        using Module_AmxLoad_t = void (SAMP_SDK_CALL *)(AMX *amx);
        using Module_AmxUnload_t = void (SAMP_SDK_CALL *)(AMX *amx);
        using Module_ProcessTick_t = void (SAMP_SDK_CALL *)();

        class Module {
            public:
                Module(const std::string& name) : name_(name) {}

                const std::string& Get_Name() const {
                    return name_;
                }

                bool Load(const std::string& path, void** ppData) {
                    if (!library_.Load(path))
                        return false;

                    auto load_func = library_.Get_Function<Module_Load_t>("Load");
                    auto unload_func = library_.Get_Function<Module_Unload_t>("Unload");
                    auto supports_func = library_.Get_Function<Module_Supports_t>("Supports");

                    if (!load_func || !unload_func || !supports_func) {
                        Log("[SAMP-SDK] Error: Module '%s' does not export required 'Load', 'Unload', and 'Supports' functions.", name_.c_str());
                        library_.Unload();

                        return false;
                    }

                    unload_func_ = unload_func;
                    supports_func_ = supports_func;

                    amx_load_func_ = library_.Get_Function<Module_AmxLoad_t>("AmxLoad");
                    amx_unload_func_ = library_.Get_Function<Module_AmxUnload_t>("AmxUnload");
                    process_tick_func_ = library_.Get_Function<Module_ProcessTick_t>("ProcessTick");
                    
                    if (!load_func(ppData)) {
                        Log("[SAMP-SDK] Error: Module '%s' failed to initialize (Load function returned false).", name_.c_str());
                        library_.Unload();

                        return false;
                    }

                    return true;
                }

                void Unload() {
                    if (library_.Is_Loaded() && unload_func_) {
                        unload_func_();
                        library_.Unload();
                    }
                }

                Module_AmxLoad_t Get_AmxLoad_Func() const {
                    return amx_load_func_;
                }

                Module_AmxUnload_t Get_AmxUnload_Func() const {
                    return amx_unload_func_;
                }
                
                Module_ProcessTick_t Get_ProcessTick_Func() const {
                    return process_tick_func_;
                }

            private:
                std::string name_;
                Dynamic_Library library_;
                Module_Unload_t unload_func_ = nullptr;
                Module_Supports_t supports_func_ = nullptr;
                Module_AmxLoad_t amx_load_func_ = nullptr;
                Module_AmxUnload_t amx_unload_func_ = nullptr;
                Module_ProcessTick_t process_tick_func_ = nullptr;
        };

        class Module_Manager {
            public:
                static Module_Manager& Instance() {
                    static Module_Manager instance;

                    return instance;
                }

                bool Load_Module(const std::string& name, const std::string& path, const std::string& success_msg, void** ppData) {
                    auto it = std::find_if(loaded_modules_.begin(), loaded_modules_.end(), [&](const auto& module_ptr) {
                        return module_ptr->Get_Name() == name;
                    });

                    if (it != loaded_modules_.end())
                        return (Log("[SAMP-SDK] Error: A module with the name '%s' is already loaded.", name.c_str()), false);
                    
                    std::string full_path = path;

                    if (!path.empty() && path.back() != '/' && path.back() != '\\')
                        full_path += '/';

                    full_path += name;

#if defined(SAMP_SDK_WINDOWS)
                    full_path += ".dll";
#elif defined(SAMP_SDK_LINUX)
                    full_path += ".so";
#endif

                    auto module = std::make_unique<Module>(name);

                    if (module->Load(full_path, ppData)) {
                        if (!success_msg.empty())
                            Log(success_msg.c_str());

                        loaded_modules_.push_back(std::move(module));
                        return true;
                    }
                    
                    return false;
                }

                void Unload_All_Modules() {
                    for (auto it = loaded_modules_.rbegin(); it != loaded_modules_.rend(); ++it)
                        (*it)->Unload();

                    loaded_modules_.clear();
                }
                
                void Forward_AmxLoad(AMX* amx) {
                    for (const auto& module : loaded_modules_) {
                        if (auto func = module->Get_AmxLoad_Func())
                            func(amx);
                    }
                }

                void Forward_AmxUnload(AMX* amx) {
                    for (auto it = loaded_modules_.rbegin(); it != loaded_modules_.rend(); ++it) {
                        if (auto func = (*it)->Get_AmxUnload_Func())
                            func(amx);
                    }
                }

                void Forward_ProcessTick() {
                    for (const auto& module : loaded_modules_) {
                        if (auto func = module->Get_ProcessTick_Func())
                            func();
                    }
                }
                
            private:
                Module_Manager() = default;
                std::vector<std::unique_ptr<Module>> loaded_modules_;
        };
    }
}