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

#include "plugin_defs.h"

namespace Samp_SDK {
    class Core {
        public:
            static Core& Instance() {
                static Core inst;
                
                return inst;
            }

            void Load(void** ppData) {
                pPluginData = ppData;
                pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
                logprintf_ptr = reinterpret_cast<LogPrintf_t>(ppData[PLUGIN_DATA_LOGPRINTF]);
            }

            [[nodiscard]] void* Get_AMX_Export(int index) const {
                if (!pAMXFunctions)
                    return nullptr;
            
                return static_cast<void**>(pAMXFunctions)[index];
            }

            [[nodiscard]] void** Get_Plugin_Data() const {
                return pPluginData;
            }

            void Log(const char* format) const {
                if (!logprintf_ptr)
                    return;
                
                logprintf_ptr(format);
            }
            
        private:
            Core() = default;
            ~Core() = default;
            Core(const Core&) = delete;
            Core& operator=(const Core&) = delete;

            using LogPrintf_t = void (*)(const char* format, ...);

            void** pPluginData = nullptr;
            void* pAMXFunctions = nullptr;
            LogPrintf_t logprintf_ptr = nullptr;
    };
}