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

constexpr auto SAMP_PLUGIN_VERSION = 0x0200;

enum SUPPORTS_FLAGS {
    SUPPORTS_VERSION = SAMP_PLUGIN_VERSION,
    SUPPORTS_VERSION_MASK = 0xffff,
    SUPPORTS_AMX_NATIVES = 0x10000,
    SUPPORTS_PROCESS_TICK = 0x20000
};

enum PLUGIN_DATA_TYPE {
    PLUGIN_DATA_LOGPRINTF = 0x00,
    PLUGIN_DATA_AMX_EXPORTS = 0x10,
    PLUGIN_DATA_CALLPUBLIC_FS = 0x11,
    PLUGIN_DATA_CALLPUBLIC_GM = 0x12,
};

enum PLUGIN_AMX_EXPORT {
    PLUGIN_AMX_EXPORT_Align16,
    PLUGIN_AMX_EXPORT_Align32,
    PLUGIN_AMX_EXPORT_Align64,
    PLUGIN_AMX_EXPORT_Allot,
    PLUGIN_AMX_EXPORT_Callback,
    PLUGIN_AMX_EXPORT_Cleanup,
    PLUGIN_AMX_EXPORT_Clone,
    PLUGIN_AMX_EXPORT_Exec,
    PLUGIN_AMX_EXPORT_FindNative,
    PLUGIN_AMX_EXPORT_FindPublic,
    PLUGIN_AMX_EXPORT_FindPubVar,
    PLUGIN_AMX_EXPORT_FindTagId,
    PLUGIN_AMX_EXPORT_Flags,
    PLUGIN_AMX_EXPORT_GetAddr,
    PLUGIN_AMX_EXPORT_GetNative,
    PLUGIN_AMX_EXPORT_GetPublic,
    PLUGIN_AMX_EXPORT_GetPubVar,
    PLUGIN_AMX_EXPORT_GetString,
    PLUGIN_AMX_EXPORT_GetTag,
    PLUGIN_AMX_EXPORT_GetUserData,
    PLUGIN_AMX_EXPORT_Init,
    PLUGIN_AMX_EXPORT_InitJIT,
    PLUGIN_AMX_EXPORT_MemInfo,
    PLUGIN_AMX_EXPORT_NameLength,
    PLUGIN_AMX_EXPORT_NativeInfo,
    PLUGIN_AMX_EXPORT_NumNatives,
    PLUGIN_AMX_EXPORT_NumPublics,
    PLUGIN_AMX_EXPORT_NumPubVars,
    PLUGIN_AMX_EXPORT_NumTags,
    PLUGIN_AMX_EXPORT_Push,
    PLUGIN_AMX_EXPORT_PushArray,
    PLUGIN_AMX_EXPORT_PushString,
    PLUGIN_AMX_EXPORT_RaiseError,
    PLUGIN_AMX_EXPORT_Register,
    PLUGIN_AMX_EXPORT_Release,
    PLUGIN_AMX_EXPORT_SetCallback,
    PLUGIN_AMX_EXPORT_SetDebugHook,
    PLUGIN_AMX_EXPORT_SetString,
    PLUGIN_AMX_EXPORT_SetUserData,
    PLUGIN_AMX_EXPORT_StrLen,
    PLUGIN_AMX_EXPORT_UTF8Check,
    PLUGIN_AMX_EXPORT_UTF8Get,
    PLUGIN_AMX_EXPORT_UTF8Len,
    PLUGIN_AMX_EXPORT_UTF8Put,
};