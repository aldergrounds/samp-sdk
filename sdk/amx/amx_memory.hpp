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

#include "amx_api.hpp"
#include "amx_defs.h"

namespace Samp_SDK {
    class Amx_Scoped_Memory {
        public:
            Amx_Scoped_Memory() : amx_(nullptr), amx_addr_(0), phys_addr_(nullptr) {}

            Amx_Scoped_Memory(AMX* amx, int cells) : amx_(amx), amx_addr_(0), phys_addr_(nullptr) {
                if (amx::Allot(amx, cells, &amx_addr_, &phys_addr_) != static_cast<int>(Amx_Error::None)) {
                    amx_addr_ = 0;
                    phys_addr_ = nullptr;
                }
            }

            ~Amx_Scoped_Memory() {
                if (amx_ != nullptr && amx_addr_ != 0)
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
                    if (amx_ != nullptr && amx_addr_ != 0)
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

            [[nodiscard]] cell Get_Amx_Addr() const {
                return amx_addr_;
            }

            [[nodiscard]] cell* Get_Phys_Addr() const {
                return phys_addr_;
            }

            [[nodiscard]] bool Is_Valid() const {
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