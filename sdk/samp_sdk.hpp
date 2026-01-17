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

#include "amx/amx_defs.h"
#include "amx/amx_api.hpp"
#include "amx/amx_memory.hpp"
#include "amx/amx_helpers.hpp"
#include "amx/amx_manager.hpp"

#include "core/platform.hpp"
#include "core/plugin_defs.h"
#include "core/exports.hpp"
#include "core/core.hpp"

#include "events/public_dispatcher.hpp"
#include "events/native.hpp"
#include "events/callbacks.hpp"

#include "hooks/assembly.hpp"
#include "hooks/function_hook.hpp"
#include "hooks/native_hook_manager.hpp"
#include "hooks/interceptor_manager.hpp"

#include "modules/dynamic_library.hpp"
#include "modules/module_manager.hpp"

#include "utils/hash.hpp"
#include "utils/logger.hpp"
#include "utils/samp_defs.hpp"

bool OnLoad();
void OnUnload();
unsigned int GetSupportFlags();

#if defined(SAMP_SDK_WANT_AMX_EVENTS)
void OnAmxLoad(AMX* amx);
void OnAmxUnload(AMX* amx);
#endif

#if defined(SAMP_SDK_WANT_PROCESS_TICK)
void OnProcessTick();
#endif

#if defined(SAMP_SDK_IMPLEMENTATION)

#if defined(SAMP_SDK_WINDOWS)
    Export_Plugin("Supports", "0");
    Export_Plugin("Load", "4");
    Export_Plugin("Unload", "0");

    #if defined(SAMP_SDK_WANT_AMX_EVENTS)
        Export_Plugin("AmxLoad", "4");
        Export_Plugin("AmxUnload", "4");
    #endif

    #if defined(SAMP_SDK_WANT_PROCESS_TICK)
        Export_Plugin("ProcessTick", "0");
    #endif
#endif

#if defined(SAMP_SDK_WANT_AMX_EVENTS)
namespace Samp_SDK {
    namespace Detail {
        inline Native_Registry Get_Registered_Natives() {
            return Native_Registry(Native_List_Holder::Instance().Get_Natives());
        }
    }
}
#else
void OnAmxLoad(AMX* amx) {
    (void)amx;
}

void OnAmxUnload(AMX* amx) {
    (void)amx;
}
#endif

#if !defined(SAMP_SDK_WANT_PROCESS_TICK)
void OnProcessTick() {}
#endif

SAMP_SDK_EXPORT unsigned int SAMP_SDK_CALL Supports() {
    unsigned int flags = GetSupportFlags();

#if defined(SAMP_SDK_WANT_AMX_EVENTS)
    flags |= SUPPORTS_AMX_NATIVES;
#endif
#if defined(SAMP_SDK_WANT_PROCESS_TICK)
    flags |= SUPPORTS_PROCESS_TICK;
#endif

    return flags;
}

SAMP_SDK_EXPORT bool SAMP_SDK_CALL Load(void** ppData) {
    Samp_SDK::Core::Instance().Load(ppData);
    Samp_SDK::Detail::Interceptor_Manager::Instance().Activate();

    return OnLoad();
}

SAMP_SDK_EXPORT void SAMP_SDK_CALL Unload() {
    OnUnload();

    Samp_SDK::Detail::Module_Manager::Instance().Unload_All_Modules();
    Samp_SDK::Detail::Interceptor_Manager::Instance().Deactivate();
}

#if defined(SAMP_SDK_WANT_AMX_EVENTS)
SAMP_SDK_EXPORT void SAMP_SDK_CALL AmxLoad(AMX* amx) {
    Samp_SDK::Detail::Get_Registered_Natives().Register_All(amx);

    OnAmxLoad(amx);

    Samp_SDK::Detail::Module_Manager::Instance().Forward_AmxLoad(amx);
}

SAMP_SDK_EXPORT void SAMP_SDK_CALL AmxUnload(AMX* amx) {
    Samp_SDK::Detail::Module_Manager::Instance().Forward_AmxUnload(amx);

    OnAmxUnload(amx);
}
#endif

#if defined(SAMP_SDK_WANT_PROCESS_TICK)
SAMP_SDK_EXPORT void SAMP_SDK_CALL ProcessTick() {
    OnProcessTick();

    Samp_SDK::Detail::Module_Manager::Instance().Forward_ProcessTick();
}
#endif

#endif

#define Plugin_Module(name, path, ...) \
    Samp_SDK::Detail::Module_Manager::Instance().Load_Module(name, path, ##__VA_ARGS__, Samp_SDK::Core::Instance().Get_Plugin_Data())

#define Plugin_Public(name, ...) \
    static cell SAMP_SDK_CALL name(__VA_ARGS__); \
    namespace { \
        PLUGIN_PUBLIC_REGISTRATION(name) \
    } \
    static cell SAMP_SDK_CALL name(__VA_ARGS__)

#define Plugin_Native_Hook(name, ...) \
    static cell SAMP_SDK_CDECL Hook_##name(__VA_ARGS__); \
    namespace { \
        PLUGIN_NATIVE_HOOK_REGISTRATION(name) \
    } \
    static cell SAMP_SDK_CDECL Hook_##name(__VA_ARGS__)

#if defined(SAMP_SDK_WANT_AMX_EVENTS)
    #define Plugin_Native(name, ...) \
        cell SAMP_SDK_CDECL name(__VA_ARGS__); \
        namespace { \
            ::Samp_SDK::Detail::Native_Register register_##name(#name, name); \
        } \
        cell SAMP_SDK_CDECL name(__VA_ARGS__)
    #define Plugin_Call(name, ...) Samp_SDK::Detail::Plugin_Call_Impl(Samp_SDK::Detail::FNV1a_Hash_Const(#name), ##__VA_ARGS__)
#endif

#define Pawn(name, ...) \
    Samp_SDK::Detail::Caller<Samp_SDK::Pawn_Call_Type::Automatic>::Call(Samp_SDK::Detail::FNV1a_Hash_Const(#name), #name, ##__VA_ARGS__)

#define Pawn_Native(name, ...) \
    Samp_SDK::Detail::Caller<Samp_SDK::Pawn_Call_Type::Native>::Call(Samp_SDK::Detail::FNV1a_Hash_Const(#name), #name, ##__VA_ARGS__)

#define Pawn_Public(name, ...) \
    Samp_SDK::Detail::Caller<Samp_SDK::Pawn_Call_Type::Public>::Call(Samp_SDK::Detail::FNV1a_Hash_Const(#name), #name, ##__VA_ARGS__)

#define Plugin_Format(...) \
    Samp_SDK::Format(__VA_ARGS__)

#define Register_Parameters(...) \
    Samp_SDK::Detail::Register_Parameters_Impl(amx, params, __VA_ARGS__)
