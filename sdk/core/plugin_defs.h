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