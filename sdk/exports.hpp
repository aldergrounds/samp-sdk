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

#include "platform.hpp"

#if defined(SAMP_SDK_WINDOWS)
    #if defined(SAMP_SDK_COMPILER_MSVC)
        #define SAMP_SDK_EXPORT_PLUGIN(function_name, stack_size) \
            __pragma(comment(linker, "/EXPORT:" function_name "=_" function_name "@" stack_size))
    #elif defined(SAMP_SDK_COMPILER_GCC_OR_CLANG)
        #define SAMP_SDK_EXPORT_PLUGIN(function_name, stack_size)
    #endif
#elif defined(SAMP_SDK_LINUX)
    #define SAMP_SDK_EXPORT_PLUGIN(function_name, stack_size)
#endif

#define Export_Plugin(function_name, stack_size) \
    SAMP_SDK_EXPORT_PLUGIN(function_name, stack_size)
