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

#include <cstdint>
//
#include "../core/platform.hpp"

namespace Samp_SDK {
    namespace Detail {
        constexpr uint32_t FNV_PRIME = 16777619u;
        constexpr uint32_t FNV_OFFSET_BASIS = 2166136261u;

        SAMP_SDK_FORCE_INLINE constexpr uint32_t FNV1a_Hash(const char* str) noexcept {
            uint32_t hash = FNV_OFFSET_BASIS;

            if (str) {
                while (*str) {
                    hash ^= static_cast<uint32_t>(*str++);
                    hash *= FNV_PRIME;
                }
            }

            return hash;
        }

        constexpr uint32_t FNV1a_Hash_Const(const char* str, uint32_t hash = FNV_OFFSET_BASIS) noexcept {
            return !*str ? hash : FNV1a_Hash_Const(str + 1, (hash ^ static_cast<uint32_t>(*str)) * FNV_PRIME);
        }
    }
}