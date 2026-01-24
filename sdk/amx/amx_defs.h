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
#include <cstring>
//
#include "../core/platform.hpp"

using cell = int32_t;
using ucell = uint32_t;

struct AMX;
struct AMX_HEADER;

using AMX_NATIVE = cell (SAMP_SDK_CDECL *)(AMX *amx, cell *params);
using AMX_CALLBACK = int (SAMP_SDK_CDECL *)(AMX *amx, cell index, cell *result, cell *params);
using AMX_DEBUG = int (SAMP_SDK_CDECL *)(AMX *amx);

#if defined(SAMP_SDK_COMPILER_MSVC)
    #pragma pack(push, 1)
    #define SAMP_SDK_PACKED
#elif defined(SAMP_SDK_COMPILER_GCC_OR_CLANG)
    #define SAMP_SDK_PACKED __attribute__((packed))
#else
    #define SAMP_SDK_PACKED
#endif

struct AMX_NATIVE_INFO {
    const char* name;
    AMX_NATIVE func;
} SAMP_SDK_PACKED;

struct AMX_FUNCSTUBNT {
    ucell address;
    uint32_t nameofs;
} SAMP_SDK_PACKED;

struct AMX {
    unsigned char *base;
    unsigned char *data;
    AMX_CALLBACK callback;
    AMX_DEBUG debug;
    cell cip;
    cell frm;
    cell hea;
    cell hlw;
    cell stk;
    cell stp;
    int flags;
    long usertags[4];
    void *userdata[4];
    int error;
    int paramcount;
    cell pri;
    cell alt;
    cell reset_stk;
    cell reset_hea;
    cell sysreq_d;
    int cur;
} SAMP_SDK_PACKED;

struct AMX_HEADER {
    int32_t size;
    uint16_t magic;
    char file_version;
    char amx_version;
    int16_t flags;
    int16_t defsize;
    int32_t cod;
    int32_t dat;
    int32_t hea;
    int32_t stp;
    int32_t cip;
    int32_t publics;
    int32_t natives;
    int32_t libraries;
    int32_t pubvars;
    int32_t tags;
    int32_t nametable;
} SAMP_SDK_PACKED;

#if defined(SAMP_SDK_COMPILER_MSVC)
    #pragma pack(pop)
#endif

#undef SAMP_SDK_PACKED

constexpr uint16_t AMX_MAGIC = 0xF1E0;
constexpr int AMX_EXEC_MAIN = -1;
constexpr int AMX_EXEC_CONT = -2;

enum class Amx_Error {
    None,
    Exit,
    Assert,
    StackErr,
    Bounds,
    MemAccess,
    InvInstr,
    StackLow,
    HeapLow,
    Callback,
    Native,
    Divide,
    Sleep,
    InvState,
    Memory = 16,
    Format,
    Version,
    NotFound,
    Index,
    Debug,
    Init,
    UserData,
    InitJit,
    Params,
    Domain,
    General,
};

constexpr auto AMX_FLAG_DEBUG = 0x02;
constexpr auto AMX_FLAG_COMPACT = 0x04;
constexpr auto AMX_FLAG_BYTEOPC = 0x08;
constexpr auto AMX_FLAG_NOCHECKS = 0x10;
constexpr auto AMX_FLAG_NTVREG = 0x1000;
constexpr auto AMX_FLAG_JITC = 0x2000;
constexpr auto AMX_FLAG_BROWSE = 0x4000;
constexpr auto AMX_FLAG_RELOC = 0x8000;

constexpr int MIN_AMX_VERSION = 8;
constexpr int MIN_FILE_VERSION = 2;

constexpr cell PUBLIC_CONTINUE = 1;
constexpr cell PUBLIC_STOP = 0;

namespace Samp_SDK {
    namespace amx {
        SAMP_SDK_FORCE_INLINE float AMX_CTOF(cell c) {
            static_assert(sizeof(float) == sizeof(cell), "[SA-MP SDK]: Size mismatch between float and cell.");
            float f;
            std::memcpy(&f, &c, sizeof(f));

            return f;
        }

        SAMP_SDK_FORCE_INLINE cell AMX_FTOC(float f) {
            static_assert(sizeof(cell) == sizeof(float), "[SA-MP SDK]: Size mismatch between cell and float.");
            cell c;
            std::memcpy(&c, &f, sizeof(c));
            
            return c;
        }
    }
}