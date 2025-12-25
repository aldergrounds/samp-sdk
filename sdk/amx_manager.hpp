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

#include <vector>
#include <mutex>
#include <atomic>
#include <algorithm>
#include <shared_mutex>
//
#include "amx_api.hpp"
#include "amx_defs.h"

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
                std::shared_lock<Mutex_Type> lock(mtx_);

                return loaded_amx_;
            }

            AMX* Find_Public(const char* name, int& index) {
                std::shared_lock<Mutex_Type> lock(mtx_);

                for (auto it = loaded_amx_.rbegin(); it != loaded_amx_.rend(); ++it) {
                    if (amx::Find_Public(*it, name, &index) == 0)
                        return *it;
                }

                return nullptr;
            }
            
            AMX* Get_Primary_Amx() {
                std::shared_lock<Mutex_Type> lock(mtx_);

                if (loaded_amx_.empty())
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

            using Mutex_Type = std::shared_mutex;

            std::vector<AMX*> loaded_amx_;
            Mutex_Type mtx_;
            std::atomic<uint32_t> generation_{0};
    };
}