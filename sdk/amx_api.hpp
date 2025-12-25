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

#include <utility>
#include <type_traits>
#include <cstdarg>
//
#include "amx_defs.h"
#include "core.hpp"
#include "logger.hpp"
#include "platform.hpp"
#include "plugin_defs.h"

namespace Samp_SDK {
    namespace amx {
        namespace Detail {
            template<typename T>
            T Amx_Call_Error_Handler() {
                if constexpr (std::is_pointer_v<T>)
                    return nullptr;
                else
                    return static_cast<T>(Amx_Error::General);
            }
        }

        template <typename Func, int Index, typename... Args>
        inline auto Call(Args... args) -> decltype(std::declval<Func>()(args...)) {
            using Return_Type = decltype(std::declval<Func>()(args...));
            auto func_ptr = reinterpret_cast<Func>(Core::Instance().Get_AMX_Export(Index));

            if (!func_ptr)
                return (Log("[SA-MP SDK] Fatal: Attempted to call AMX export at index %d, but pAMXFunctions was not loaded!", Index), Samp_SDK::amx::Detail::Amx_Call_Error_Handler<Return_Type>());

            return func_ptr(args...);
        }

        inline cell* Get_Addr_Safe(AMX* amx, int param_index_from_zero) {
            if (!amx)
                return nullptr;

            AMX_HEADER* hdr = reinterpret_cast<AMX_HEADER*>(amx->base);
            unsigned char* data = (amx->data != nullptr) ? amx->data : amx->base + hdr->dat;
            
            cell param_addr = amx->stk + ((param_index_from_zero + 1) * sizeof(cell));
            
            if (param_addr < amx->hea || param_addr >= amx->stp)
                return nullptr;

            cell* final_addr = reinterpret_cast<cell*>(data + *reinterpret_cast<cell*>(data + param_addr));
            
            uintptr_t data_start = reinterpret_cast<uintptr_t>(data);
            uintptr_t data_end = data_start + static_cast<uintptr_t>(amx->stp);
            uintptr_t final_ptr = reinterpret_cast<uintptr_t>(final_addr);
            
            if (final_ptr < data_start || final_ptr >= data_end)
                return nullptr;

            return final_addr;
        }

        using Align_16_t = uint16_t* (SAMP_SDK_CDECL *)(uint16_t* v);
        using Align_32_t = uint32_t* (SAMP_SDK_CDECL *)(uint32_t* v);
        using Align_64_t = uint64_t* (SAMP_SDK_CDECL *)(uint64_t* v);
        using Allot_t = int (SAMP_SDK_CDECL *)(AMX* amx, int cells, cell* amx_addr, cell** phys_addr);
        using Callback_t = int (SAMP_SDK_CDECL *)(AMX* amx, cell index, cell* result, cell* params);
        using Cleanup_t = int (SAMP_SDK_CDECL *)(AMX* amx);
        using Clone_t = int (SAMP_SDK_CDECL *)(AMX* amxClone, AMX* amxSource, void* data);
        using Exec_t = int (SAMP_SDK_CDECL *)(AMX* amx, cell* retval, int index);
        using Find_Native_t = int (SAMP_SDK_CDECL *)(AMX* amx, const char* name, int* index);
        using Find_Public_t = int (SAMP_SDK_CDECL *)(AMX* amx, const char* funcname, int* index);
        using Find_Pub_Var_t = int (SAMP_SDK_CDECL *)(AMX* amx, const char* varname, cell* amx_addr);
        using Find_Tag_Id_t = int (SAMP_SDK_CDECL *)(AMX* amx, cell tag_id, char* tagname);
        using Flags_t = int (SAMP_SDK_CDECL *)(AMX* amx, uint16_t* flags);
        using Get_Addr_t = int (SAMP_SDK_CDECL *)(AMX* amx, cell amx_addr, cell** phys_addr);
        using Get_Native_t = int (SAMP_SDK_CDECL *)(AMX* amx, int index, char* funcname);
        using Get_Public_t = int (SAMP_SDK_CDECL *)(AMX* amx, int index, char* funcname);
        using Get_Pub_Var_t = int (SAMP_SDK_CDECL *)(AMX* amx, int index, char* varname, cell* amx_addr);
        using Get_String_t = int (SAMP_SDK_CDECL *)(char* dest, const cell* source, int use_wchar, size_t size);
        using Get_Tag_t = int (SAMP_SDK_CDECL *)(AMX* amx, int index, char* tagname, cell* tag_id);
        using Get_User_Data_t = int (SAMP_SDK_CDECL *)(AMX* amx, long tag, void** ptr);
        using Init_t = int (SAMP_SDK_CDECL *)(AMX* amx, void* program);
        using Init_JIT_t = int (SAMP_SDK_CDECL *)(AMX* amx, void* reloc_table, void* native_code);
        using Mem_Info_t = int (SAMP_SDK_CDECL *)(AMX* amx, long* codesize, long* datasize, long* stackheap);
        using Name_Length_t = int (SAMP_SDK_CDECL *)(AMX* amx, int* length);
        using Native_Info_t = AMX_NATIVE_INFO* (SAMP_SDK_CDECL *)(const char* name, AMX_NATIVE func);
        using Num_Natives_t = int (SAMP_SDK_CDECL *)(AMX* amx, int* number);
        using Num_Publics_t = int (SAMP_SDK_CDECL *)(AMX* amx, int* number);
        using Num_Pub_Vars_t = int (SAMP_SDK_CDECL *)(AMX* amx, int* number);
        using Num_Tags_t = int (SAMP_SDK_CDECL *)(AMX* amx, int* number);
        using Push_t = int (SAMP_SDK_CDECL *)(AMX* amx, cell value);
        using Push_Array_t = int (SAMP_SDK_CDECL *)(AMX* amx, cell* amx_addr, cell** phys_addr, const cell array[], int numcells);
        using Push_String_t = int (SAMP_SDK_CDECL *)(AMX* amx, cell* amx_addr, cell** phys_addr, const char* string, int pack, int use_wchar);
        using Raise_Error_t = int (SAMP_SDK_CDECL *)(AMX* amx, int error);
        using Register_t = int (SAMP_SDK_CDECL *)(AMX* amx, const AMX_NATIVE_INFO* nativelist, int number);
        using Release_t = int (SAMP_SDK_CDECL *)(AMX* amx, cell amx_addr);
        using Set_Callback_t = int (SAMP_SDK_CDECL *)(AMX* amx, AMX_CALLBACK callback);
        using Set_Debug_Hook_t = int (SAMP_SDK_CDECL *)(AMX* amx, AMX_DEBUG debug);
        using Set_String_t = int (SAMP_SDK_CDECL *)(cell* dest, const char* source, int pack, int use_wchar, size_t size);
        using Set_User_Data_t = int (SAMP_SDK_CDECL *)(AMX* amx, long tag, void* ptr);
        using Str_Len_t = int (SAMP_SDK_CDECL *)(const cell* cstring, int* length);
        using UTF8_Check_t = int (SAMP_SDK_CDECL *)(const char* string, int* length);
        using UTF8_Get_t = int (SAMP_SDK_CDECL *)(const char* string, const char** endptr, cell* value);
        using UTF8_Len_t = int (SAMP_SDK_CDECL *)(const cell* cstr, int* length);
        using UTF8_Put_t = int (SAMP_SDK_CDECL *)(char* string, char** endptr, int maxchars, cell value);

        inline uint16_t* Align_16(uint16_t* v) { return Call<Align_16_t, PLUGIN_AMX_EXPORT_Align16>(v); }
        inline uint32_t* Align_32(uint32_t* v) { return Call<Align_32_t, PLUGIN_AMX_EXPORT_Align32>(v); }
        inline uint64_t* Align_64(uint64_t* v) { return Call<Align_64_t, PLUGIN_AMX_EXPORT_Align64>(v); }
        inline int Allot(AMX* amx, int cells, cell* amx_addr, cell** phys_addr) { return Call<Allot_t, PLUGIN_AMX_EXPORT_Allot>(amx, cells, amx_addr, phys_addr); }
        inline int Callback(AMX* amx, cell index, cell* result, cell* params) { return Call<Callback_t, PLUGIN_AMX_EXPORT_Callback>(amx, index, result, params); }
        inline int Cleanup(AMX* amx) { return Call<Cleanup_t, PLUGIN_AMX_EXPORT_Cleanup>(amx); }
        inline int Clone(AMX* amxClone, AMX* amxSource, void* data) { return Call<Clone_t, PLUGIN_AMX_EXPORT_Clone>(amxClone, amxSource, data); }
        inline int Exec(AMX* amx, cell* retval, int index) { return Call<Exec_t, PLUGIN_AMX_EXPORT_Exec>(amx, retval, index); }
        inline int Find_Native(AMX* amx, const char* name, int* index) { return Call<Find_Native_t, PLUGIN_AMX_EXPORT_FindNative>(amx, name, index); }
        inline int Find_Public(AMX* amx, const char* funcname, int* index) { return Call<Find_Public_t, PLUGIN_AMX_EXPORT_FindPublic>(amx, funcname, index); }
        inline int Find_Pub_Var(AMX* amx, const char* varname, cell* amx_addr) { return Call<Find_Pub_Var_t, PLUGIN_AMX_EXPORT_FindPubVar>(amx, varname, amx_addr); }
        inline int Find_Tag_Id(AMX* amx, cell tag_id, char* tagname) { return Call<Find_Tag_Id_t, PLUGIN_AMX_EXPORT_FindTagId>(amx, tag_id, tagname); }
        inline int Flags(AMX* amx, uint16_t* flags) { return Call<Flags_t, PLUGIN_AMX_EXPORT_Flags>(amx, flags); }
        inline int Get_Addr(AMX* amx, cell amx_addr, cell** phys_addr) { return Call<Get_Addr_t, PLUGIN_AMX_EXPORT_GetAddr>(amx, amx_addr, phys_addr); }
        inline int Get_Native(AMX* amx, int index, char* funcname) { return Call<Get_Native_t, PLUGIN_AMX_EXPORT_GetNative>(amx, index, funcname); }
        inline int Get_Public(AMX* amx, int index, char* funcname) { return Call<Get_Public_t, PLUGIN_AMX_EXPORT_GetPublic>(amx, index, funcname); }
        inline int Get_Pub_Var(AMX* amx, int index, char* varname, cell* amx_addr) { return Call<Get_Pub_Var_t, PLUGIN_AMX_EXPORT_GetPubVar>(amx, index, varname, amx_addr); }
        inline int Get_String(char* dest, const cell* source, size_t size) { return Call<Get_String_t, PLUGIN_AMX_EXPORT_GetString>(dest, source, 0, size); }
        inline int Get_Tag(AMX* amx, int index, char* tagname, cell* tag_id) { return Call<Get_Tag_t, PLUGIN_AMX_EXPORT_GetTag>(amx, index, tagname, tag_id); }
        inline int Get_User_Data(AMX* amx, long tag, void** ptr) { return Call<Get_User_Data_t, PLUGIN_AMX_EXPORT_GetUserData>(amx, tag, ptr); }
        inline int Init(AMX* amx, void* program) { return Call<Init_t, PLUGIN_AMX_EXPORT_Init>(amx, program); }
        inline int Init_JIT(AMX* amx, void* reloc_table, void* native_code) { return Call<Init_JIT_t, PLUGIN_AMX_EXPORT_InitJIT>(amx, reloc_table, native_code); }
        inline int Mem_Info(AMX* amx, long* codesize, long* datasize, long* stackheap) { return Call<Mem_Info_t, PLUGIN_AMX_EXPORT_MemInfo>(amx, codesize, datasize, stackheap); }
        inline int Name_Length(AMX* amx, int* length) { return Call<Name_Length_t, PLUGIN_AMX_EXPORT_NameLength>(amx, length); }
        inline AMX_NATIVE_INFO* Native_Info(const char* name, AMX_NATIVE func) { return Call<Native_Info_t, PLUGIN_AMX_EXPORT_NativeInfo>(name, func); }
        inline int Num_Natives(AMX* amx, int* number) { return Call<Num_Natives_t, PLUGIN_AMX_EXPORT_NumNatives>(amx, number); }
        inline int Num_Publics(AMX* amx, int* number) { return Call<Num_Publics_t, PLUGIN_AMX_EXPORT_NumPublics>(amx, number); }
        inline int Num_Pub_Vars(AMX* amx, int* number) { return Call<Num_Pub_Vars_t, PLUGIN_AMX_EXPORT_NumPubVars>(amx, number); }
        inline int Num_Tags(AMX* amx, int* number) { return Call<Num_Tags_t, PLUGIN_AMX_EXPORT_NumTags>(amx, number); }
        inline int Push(AMX* amx, cell value) { return Call<Push_t, PLUGIN_AMX_EXPORT_Push>(amx, value); }
        inline int Push_Array(AMX* amx, cell* amx_addr, cell** phys_addr, const cell array[], int numcells) { return Call<Push_Array_t, PLUGIN_AMX_EXPORT_PushArray>(amx, amx_addr, phys_addr, array, numcells); }
        inline int Push_String(AMX* amx, cell* amx_addr, cell** phys_addr, const char* string) { return Call<Push_String_t, PLUGIN_AMX_EXPORT_PushString>(amx, amx_addr, phys_addr, string, 0, 0); }
        inline int Raise_Error(AMX* amx, int error) { return Call<Raise_Error_t, PLUGIN_AMX_EXPORT_RaiseError>(amx, error); }
        inline int Register(AMX* amx, const AMX_NATIVE_INFO* nativelist, int number) { return Call<Register_t, PLUGIN_AMX_EXPORT_Register>(amx, nativelist, number); }
        inline int Release(AMX* amx, cell amx_addr) { return Call<Release_t, PLUGIN_AMX_EXPORT_Release>(amx, amx_addr); }
        inline int Set_Callback(AMX* amx, AMX_CALLBACK callback) { return Call<Set_Callback_t, PLUGIN_AMX_EXPORT_SetCallback>(amx, callback); }
        inline int Set_Debug_Hook(AMX* amx, AMX_DEBUG debug) { return Call<Set_Debug_Hook_t, PLUGIN_AMX_EXPORT_SetDebugHook>(amx, debug); }
        inline int Set_String(cell* dest, const char* source, size_t size) { return Call<Set_String_t, PLUGIN_AMX_EXPORT_SetString>(dest, source, 0, 0, size); }
        inline int Set_User_Data(AMX* amx, long tag, void* ptr) { return Call<Set_User_Data_t, PLUGIN_AMX_EXPORT_SetUserData>(amx, tag, ptr); }
        inline int STR_Len(const cell* cstring, int* length) { return Call<Str_Len_t, PLUGIN_AMX_EXPORT_StrLen>(cstring, length); }
        inline int UTF8_Check(const char* string, int* length) { return Call<UTF8_Check_t, PLUGIN_AMX_EXPORT_UTF8Check>(string, length); }
        inline int UTF8_Get(const char* string, const char** endptr, cell* value) { return Call<UTF8_Get_t, PLUGIN_AMX_EXPORT_UTF8Get>(string, endptr, value); }
        inline int UTF8_Len(const cell* cstr, int* length) { return Call<UTF8_Len_t, PLUGIN_AMX_EXPORT_UTF8Len>(cstr, length); }
        inline int UTF8_Put(char* string, char** endptr, int maxchars, cell value) { return Call<UTF8_Put_t, PLUGIN_AMX_EXPORT_UTF8Put>(string, endptr, maxchars, value); }
        inline int Register_Func(AMX* amx, const char* name, AMX_NATIVE func) { return Register(amx, Native_Info(name, func), 1); }
    }
}