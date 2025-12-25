# SA-MP SDK

<div align="center">

![C++](https://img.shields.io/badge/C%2B%2B-17%2B-00599C?style=for-the-badge&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-blue?style=for-the-badge&logo=windows&logoColor=white)
![Architecture](https://img.shields.io/badge/Architecture-x86%20(32--bit)-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**A modern, header-only, high-level C++ SDK for developing SA-MP plugins and modules.**

</div>

## Languages

- Português: [README](../../)
- Deutsch: [README](../Deutsch/README.md)
- Español: [README](../Espanol/README.md)
- Français: [README](../Francais/README.md)
- Italiano: [README](../Italiano/README.md)
- Polski: [README](../Polski/README.md)
- Русский: [README](../Русский/README.md)
- Svenska: [README](../Svenska/README.md)
- Türkçe: [README](../Turkce/README.md)

## Table of Contents

- [SA-MP SDK](#sa-mp-sdk)
  - [Languages](#languages)
  - [Table of Contents](#table-of-contents)
  - [1. Introduction and Design Philosophy](#1-introduction-and-design-philosophy)
    - [The Problem with the Standard SA-MP C API](#the-problem-with-the-standard-sa-mp-c-api)
    - [The SA-MP SDK Solution: Abstraction with Safety and Performance](#the-sa-mp-sdk-solution-abstraction-with-safety-and-performance)
    - [Header-Only Model: Advantages and Implications](#header-only-model-advantages-and-implications)
  - [2. Configuration and Environment](#2-configuration-and-environment)
    - [Build Requirements](#build-requirements)
    - [Recommended File Structure](#recommended-file-structure)
    - [Essential Configuration Macros](#essential-configuration-macros)
      - [`SAMP_SDK_IMPLEMENTATION`](#samp_sdk_implementation)
      - [`SAMP_SDK_WANT_AMX_EVENTS`](#samp_sdk_want_amx_events)
      - [`SAMP_SDK_WANT_PROCESS_TICK`](#samp_sdk_want_process_tick)
    - [SA-MP Definitions and Constants (`samp_defs.hpp`)](#sa-mp-definitions-and-constants-samp_defshpp)
  - [3. Comprehensive API Usage Guide](#3-comprehensive-api-usage-guide)
    - [3.1. The Plugin Life Cycle](#31-the-plugin-life-cycle)
      - [`bool OnLoad()`](#bool-onload)
      - [`void OnUnload()`](#void-onunload)
      - [`unsigned int GetSupportFlags()`](#unsigned-int-getsupportflags)
      - [`void OnAmxLoad(AMX* amx)`](#void-onamxloadamx-amx)
      - [`void OnAmxUnload(AMX* amx)`](#void-onamxunloadamx-amx)
      - [`void OnProcessTick()`](#void-onprocesstick)
    - [3.2. Exporting Plugin Functions](#32-exporting-plugin-functions)
      - [Exporting for MSVC (Visual Studio) with `Export_Plugin`](#exporting-for-msvc-visual-studio-with-export_plugin)
      - [Exporting for GCC / Clang with `SAMP_SDK_EXPORT`](#exporting-for-gcc--clang-with-samp_sdk_export)
    - [3.3. `Plugin_Public`: Intercepting Pawn Events](#33-plugin_public-intercepting-pawn-events)
      - [Syntax and Declaration](#syntax-and-declaration)
      - [Automatic Parameter Marshalling](#automatic-parameter-marshalling)
      - [Control Flow: `PLUGIN_PUBLIC_CONTINUE` vs `PLUGIN_PUBLIC_STOP`](#control-flow-plugin_public_continue-vs-plugin_public_stop)
      - [Ghost Callbacks](#ghost-callbacks)
    - [3.4. `Plugin_Native`: Creating Native Functions in C++](#34-plugin_native-creating-native-functions-in-c)
      - [Syntax and Fixed Signature](#syntax-and-fixed-signature)
      - [Automatic Native Registration](#automatic-native-registration)
      - [Parameter Extraction: `Register_Parameters` vs. `Native_Params`](#parameter-extraction-register_parameters-vs-native_params)
        - [`Register_Parameters(...)`](#register_parameters)
        - [`Native_Params` (Full API: `Get`, `Get_REF`, `Set_REF`)](#native_params-full-api-get-get_ref-set_ref)
          - [`p.Count()`](#pcount)
          - [`p.Get<T>(size_t index)`](#pgettsize_t-index)
          - [`p.Get_REF<T>(size_t index, T& out_value)`](#pget_reftsize_t-index-t-out_value)
          - [`p.Get_REF<T>(size_t index)` (C++17+)](#pget_reftsize_t-index-c17)
          - [`p.Set_REF<T>(size_t index, T value)`](#pset_reftsize_t-index-t-value)
      - [Returning Values](#returning-values)
    - [3.5. `Plugin_Native_Hook`: Intercepting Existing SA-MP Natives](#35-plugin_native_hook-intercepting-existing-sa-mp-natives)
      - [Syntax and Fixed Signature](#syntax-and-fixed-signature-1)
      - [Registration and Hook Activation](#registration-and-hook-activation)
      - [Calling the Original Native (Hook Chain): `Call_Original_Native`](#calling-the-original-native-hook-chain-call_original_native)
      - [Complete Example of `Plugin_Native_Hook`](#complete-example-of-plugin_native_hook)
    - [3.6. `Pawn_*` Macros: Calling Pawn Functions from C++](#36-pawn_-macros-calling-pawn-functions-from-c)
      - [`Pawn_Native(NativeName, ...)`](#pawn_nativenativename-)
      - [`Pawn_Public(PublicName, ...)`](#pawn_publicpublicname-)
      - [`Pawn(FunctionName, ...)`](#pawnfunctionname-)
      - [Syntax and Conventions](#syntax-and-conventions)
      - [Input Parameter Marshalling](#input-parameter-marshalling)
      - [Output Parameter Marshalling (References: `int&`, `float&`, `std::string&`)](#output-parameter-marshalling-references-int-float-stdstring)
      - [The `Callback_Result` Object: Complete Analysis](#the-callback_result-object-complete-analysis)
    - [3.7. `Plugin_Module`: Dynamic Module Management](#37-plugin_module-dynamic-module-management)
      - [Syntax and Purpose](#syntax-and-purpose)
      - [Module Life Cycle](#module-life-cycle)
      - [Benefits of Modularization](#benefits-of-modularization)
    - [3.8. `Plugin_Call`: Calling Internal Plugin Natives](#38-plugin_call-calling-internal-plugin-natives)
      - [Syntax and Performance Advantages](#syntax-and-performance-advantages)
    - [3.9. SDK Utility Functions](#39-sdk-utility-functions)
      - [`Samp_SDK::Log(const char* format, ...)`](#samp_sdklogconst-char-format-)
      - [`std::string Plugin_Format(const char* format, ...)` (Recommended)](#stdstring-plugin_formatconst-char-format--recommended)
      - [`std::string Samp_SDK::Format(const char* format, ...)` (Implementation Detail)](#stdstring-samp_sdkformatconst-char-format--implementation-detail)
      - [`std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`](#stdstring-samp_sdkget_stringamx-amx-cell-amx_addr)
  - [4. Compilation and Deploy](#4-compilation-and-deploy)
    - [Architecture and Platform Requirements](#architecture-and-platform-requirements)
    - [Build Command Examples](#build-command-examples)
      - [**MSVC (Visual Studio)**](#msvc-visual-studio)
      - [**GCC / Clang (Linux)**](#gcc--clang-linux)
      - [**GCC / Clang (MinGW on Windows)**](#gcc--clang-mingw-on-windows)
    - [Distribution Considerations](#distribution-considerations)
  - [License](#license)
    - [Terms and Conditions of Use](#terms-and-conditions-of-use)
      - [1. Granted Permissions](#1-granted-permissions)
      - [2. Mandatory Conditions](#2-mandatory-conditions)
      - [3. Copyright](#3-copyright)
      - [4. Disclaimer of Warranties and Limitation of Liability](#4-disclaimer-of-warranties-and-limitation-of-liability)

## 1. Introduction and Design Philosophy

### The Problem with the Standard SA-MP C API

The SA-MP plugin API is a C programming interface. While functional and fundamental, it presents the inherent challenges of low-level programming:
- **Manual Memory Management:** Functions like `amx_Allot` and `amx_Release` require the developer to explicitly allocate and deallocate memory on the AMX heap. This is a common source of memory leaks and runtime failures.
- **Weak Typing and Manual Conversions:** Parameters are passed as an array of `cell`s, forcing explicit (and often unsafe) conversions between `cell`, `int`, `float`, and `char*`.
- **Verbosity and Boilerplate:** Extracting multiple parameters from a `cell* params` array, handling string sizes, and managing the AMX stack for C++ to Pawn callbacks requires repetitive code.
- **Interface Fragility:** The lack of compile-time verification (type safety) means that errors in parameter passing or types may go unnoticed until execution, causing crashes or undefined behavior.

### The SA-MP SDK Solution: Abstraction with Safety and Performance

The SA-MP SDK addresses these issues by providing a powerful abstraction layer in C++:
- **RAII (Resource Acquisition Is Initialization):** Automatic memory management in AMX. `Amx_Scoped_Memory` ensures allocated memory is released.
- **Type Safety:** Automatic and safe conversion of parameters between C++ and Pawn. You handle `int`, `float`, `std::string` directly.
- **Concise and Idiomatic Syntax:** Macros and templates provide a clean API that resembles modern C++ more than the traditional C API.
- **Robust Interception:** An advanced hooking engine allows transparent interception of Pawn callbacks (`Plugin_Public`), creation of new natives (`Plugin_Native`), and **hooking and chaining of existing SA-MP native functions (`Plugin_Native_Hook`)**.
- **High Performance:** Extensive use of compile-time hashing (FNV1a), function caching, and `thread_local` optimizations to minimize abstraction overhead.

### Header-Only Model: Advantages and Implications

The SDK is composed exclusively of header files (`.hpp`, `.h`).
- **Advantages:**
   - **Simplified Integration:** There are no libraries to build, link, or distribute. Just include the headers.
   - **Compiler Optimizations:** The compiler has full visibility of the SDK code and your plugin, allowing for aggressive inlining and link-time optimizations, which can result in faster binaries.
- **Implications:**
   - **Compile Time:** For very large projects, compilation may take longer due to repeated inclusion of SDK code. This is mitigated by include guards and the "include only what is necessary" nature of C++.
   - **Implementation Macros:** The need for the `SAMP_SDK_IMPLEMENTATION` macro is a consequence of the header-only model to avoid symbol redefinitions.

## 2. Configuration and Environment

### Build Requirements

- **C++ Compiler:** Compatible with C++17 or higher.
   - GCC (version 8+)
   - Clang (version 5+)
   - MSVC (Visual Studio 2017+)
- **Architecture:** **x86 (32-bit)**. SA-MP operates exclusively on this architecture. The SDK includes checks in `platform.hpp` that will emit compile errors if the incorrect architecture is detected.
- **Operating System:** Windows or Linux.

### Recommended File Structure

For clarity and organization, it is common to organize the SDK in a `samp-sdk` subfolder.

```
my_plugin/
├── samp-sdk/
│   ├── // Other SDK files
│   └── samp_sdk.hpp // The main header to be included
│
├── src/
│   ├── main.cpp // Where SAMP_SDK_IMPLEMENTATION is defined
│   └── my_custom_logic.cpp // Optional, to organize code
│
└── CMakeLists.txt (or .vcxproj, Makefile)
```

### Essential Configuration Macros

Always define these macros *before* including `samp_sdk.hpp`.

#### `SAMP_SDK_IMPLEMENTATION`

- **Purpose:** Signals the compiler that this `.cpp` file should generate the implementations of plugin export functions (`Supports`, `Load`, `Unload`, `AmxLoad`, `AmxUnload`, `ProcessTick`). **The SDK handles the export of these functions automatically, eliminating the need for `.def` files (on Windows) or `__attribute__((visibility("default")))` declarations (on Linux) for these functions.**
- **Technical Impact:** Without this macro, the linker will not find the necessary exports, and the SA-MP server will fail to load your plugin.
- **Fundamental Rule:** **Define this macro in ONLY ONE `.cpp` file in your entire project.** Defining it in more than one file will cause a "duplicate symbol" linker error.

```cpp
// main.cpp
#define SAMP_SDK_IMPLEMENTATION // The macro makes the SDK automatically export the necessary functions.
#include "samp-sdk/samp_sdk.hpp"

// ... your plugin code ...
```

#### `SAMP_SDK_WANT_AMX_EVENTS`

- **Purpose:** Enables Pawn script lifecycle callbacks (`OnAmxLoad`, `OnAmxUnload`) and the functionality to create new C++ natives (`Plugin_Native`).
- **Features Enabled:**
   - Callbacks `OnAmxLoad(AMX* amx)` and `OnAmxUnload(AMX* amx)`.
   - Declaration and registration of new C++ natives using `Plugin_Native`.
   - The `Plugin_Call` macro to invoke natives created with `Plugin_Native` within your own plugin.
- **Technical Impact:** When this macro is defined, the SDK automatically collects all your `Plugin_Native`s. In the `Supports()` function, the `SUPPORTS_AMX_NATIVES` flag is automatically added if there are any `Plugin_Native`s in your project.
- **Flexibility:** **You can define this macro in multiple `.cpp` files**. The SDK's static registration system will consolidate all natives from different compilation units into a single global list.

```cpp
// my_natives.cpp (can be a separate file from main.cpp)
#define SAMP_SDK_WANT_AMX_EVENTS // Only to enable Plugin_Native and OnAmxLoad/OnAmxUnload callbacks
#include "samp-sdk/samp_sdk.hpp"

Plugin_Native(MyCustomNative, AMX* amx, cell* params) {
    // ...
    return 0;
}
```

#### `SAMP_SDK_WANT_PROCESS_TICK`

- **Purpose:** Enables the `OnProcessTick()` callback, which is invoked regularly by the server.
- **Technical Impact:** Automatically adds the `SUPPORTS_PROCESS_TICK` flag in the `Supports()` function.

```cpp
// main.cpp
#define SAMP_SDK_IMPLEMENTATION
#define SAMP_SDK_WANT_PROCESS_TICK
#include "samp-sdk/samp_sdk.hpp"

void OnProcessTick() {
    // Logic executed every server "tick" (e.g., 20ms)
    // Be careful with heavy operations here!
}
```

### SA-MP Definitions and Constants (`samp_defs.hpp`)

This file provides all known SA-MP constants and limits, such as `MAX_PLAYERS`, `INVALID_PLAYER_ID`, `PLAYER_STATE_ONFOOT`, `WEAPON_DEAGLE`, `DIALOG_STYLE_LIST`, etc. It is automatically included by `samp_sdk.hpp` and should be used to ensure code compatibility and readability.

## 3. Comprehensive API Usage Guide

### 3.1. The Plugin Life Cycle

The following functions are the entry and exit points for your plugin, automatically exported by the SDK.

#### `bool OnLoad()`

- **Description:** First function called by the SA-MP server after successfully loading your plugin into memory.
- **Usage:** Ideal for initializing any system, loading configurations, opening database connections, or loading modules (`Plugin_Module`).
- **Return:**
   - `true`: The plugin initialized successfully and loading continues.
   - `false`: The plugin failed to initialize. Loading will be aborted and the plugin will be unloaded.

```cpp
// main.cpp
bool OnLoad() {
    Samp_SDK::Log("Initializing MyPlugin v1.0...");

    // Example: Load a module (more details in section 3.6)
    if (!Plugin_Module("my_database_module", "plugins/db_connector", "Database Module loaded.")) {
        Samp_SDK::Log("ERROR: Failed to load database module!");

        return false; // Aborts loading of the main plugin
    }

    return true;
}
```

#### `void OnUnload()`

- **Description:** Last function called by the SA-MP server before unloading your plugin from memory.
- **Usage:** Ideal for cleaning up resources, closing connections, saving states, and ensuring no resources are leaked. The SDK manages the unloading of modules (`Plugin_Module`) automatically.

```cpp
// main.cpp
void OnUnload() {
    Samp_SDK::Log("MyPlugin unloaded. Releasing resources...");
    // No manual action is needed for modules loaded via Plugin_Module;
    // the SDK handles that.
}
```

#### `unsigned int GetSupportFlags()`

- **Description:** Informs the SA-MP server which features your plugin supports and wishes to use.
- **Usage:** **Always return `SUPPORTS_VERSION` (or `SAMP_PLUGIN_VERSION`).** The flags `SUPPORTS_AMX_NATIVES` and `SUPPORTS_PROCESS_TICK` are automatically added by the SDK if there are `Plugin_Native`s, and/or if the macro `SAMP_SDK_WANT_PROCESS_TICK` is defined, respectively. This simplifies maintenance and prevents errors.

```cpp
// main.cpp
unsigned int GetSupportFlags() {
    return SUPPORTS_VERSION; // The SDK adds the necessary flags automatically.
}
```

#### `void OnAmxLoad(AMX* amx)`

- **Requires:** `SAMP_SDK_WANT_AMX_EVENTS`
- **Description:** Called whenever a new Pawn script (a Gamemode or Filterscript) is loaded and initialized on the server.
- **Usage:** If you need specific logic for each AMX script, or to initialize script-specific data.

```cpp
// main.cpp (with SAMP_SDK_WANT_AMX_EVENTS defined)
void OnAmxLoad(AMX* amx) {
    // amx represents the new instance of the loaded script.
    Samp_SDK::Log("AMX Script loaded: %p", (void*)amx);
}
```

#### `void OnAmxUnload(AMX* amx)`

- **Requires:** `SAMP_SDK_WANT_AMX_EVENTS`
- **Description:** Called when a Pawn script is unloaded from the server.
- **Usage:** To clean up any specific resources you allocated or associated with that particular `AMX*`.

```cpp
// main.cpp (with SAMP_SDK_WANT_AMX_EVENTS defined)
void OnAmxUnload(AMX* amx) {
    Samp_SDK::Log("AMX Script unloaded: %p", (void*)amx);
}
```

#### `void OnProcessTick()`

- **Requires:** `SAMP_SDK_WANT_PROCESS_TICK`
- **Description:** Called repeatedly every server "tick" (usually 20 times per second, or every 50ms).
- **Usage:** For continuous background logic, timers, state updates that do not depend on player events, or data synchronization.
- **Caution:** Avoid blocking or computationally heavy operations here, as they can cause server lag.

```cpp
// main.cpp (with SAMP_SDK_WANT_PROCESS_TICK defined)
static int tick_count = 0;

void OnProcessTick() {
    tick_count++;

    if (tick_count % 200 == 0) // Every 10 seconds (20 ticks/sec * 10 sec = 200 ticks)
        Samp_SDK::Log("Server active for %d seconds.", tick_count / 20);
}
```

### 3.2. Exporting Plugin Functions

For the SA-MP server to call your plugin's functions (`Load`, `Supports`, etc.), they need to be "exported" from the DLL (Windows) or SO (Linux) file. The SDK automates the export of standard lifecycle functions, but also provides tools for you to export your own custom functions if you need interoperability with other programs.

The method for exporting functions varies by compiler.

#### Exporting for MSVC (Visual Studio) with `Export_Plugin`

On Windows with MSVC, the easiest way to export custom functions is using the `Export_Plugin` macro, defined in `exports.hpp`.

- **Syntax:** `Export_Plugin("Function", "Stack")`
- **`Function`**: The exact name of the function to be exported.
- **`Stack`**: The total amount of bytes the function parameters occupy on the stack. For the `__stdcall` convention (default for the SDK on Windows), the calculation is `4 * (Parameter Count)`.

```cpp
#include "samp-sdk/exports.hpp"

// Example: Exporting a custom function that could be called
// by another program or plugin that knows its signature.
const char* SAMP_SDK_CALL GetPluginVersion() {
    return "1.0.0";
}

Export_Plugin("GetPluginVersion", "0");
```

> [!WARNING]
> **Limitation of `Export_Plugin`**
> This macro works **only with the MSVC (Visual Studio) compiler**. It uses a Microsoft-specific `#pragma` directive that is ignored by other compilers like GCC and Clang.

#### Exporting for GCC / Clang with `SAMP_SDK_EXPORT`

For GCC and Clang (on Windows or Linux), exporting is managed by the `SAMP_SDK_EXPORT` macro, defined in `platform.hpp`. You simply place it before the function definition.

- **Mechanism:** On Linux, it adds `__attribute__((visibility("default")))`. On Windows with GCC/Clang, it adds `__attribute__((dllexport))`.
- **Usage:** The SDK already applies `SAMP_SDK_EXPORT` to all lifecycle functions (`Load`, `Unload`, etc.), so their export is fully automatic for these compilers. For your custom functions, just do the same.

```cpp
// For GCC/Clang, defining the function with SAMP_SDK_EXPORT is enough.
SAMP_SDK_EXPORT const char* SAMP_SDK_CALL GetPluginVersion() {
    return "1.0.0";
}
```

### 3.3. `Plugin_Public`: Intercepting Pawn Events

The `Plugin_Public` macro is the primary bridge for receiving Pawn callbacks in your C++ code.

#### Syntax and Declaration

- `Plugin_Public(PublicName, Type1 Param1, Type2 Param2, ...)`
- The C++ function name you declare **must be the same** as the Pawn callback (e.g., `OnPlayerConnect`).
- C++ parameter types (`int`, `float`, `std::string`) are automatically converted by the SDK.

```cpp
// Intercepts OnPlayerText(playerid, text[])
Plugin_Public(OnPlayerText, int playerid, std::string text) {
    Samp_SDK::Log("Player %d said: %s", playerid, text.c_str());
    
    return PLUGIN_PUBLIC_CONTINUE;
}
```

#### Automatic Parameter Marshalling

The SDK automatically handles reading the AMX `cell stack` and converting to specified C++ types:
- `int`: Converted directly from `cell`.
- `float`: Converted from `cell` using `amx::AMX_CTOF`.
- `std::string`: The SDK reads the string address in AMX, allocates a `std::string` in C++, and copies the content.

#### Control Flow: `PLUGIN_PUBLIC_CONTINUE` vs `PLUGIN_PUBLIC_STOP`

The value returned by your `Plugin_Public` function is crucial and determines the flow of callback execution:
- `return PLUGIN_PUBLIC_CONTINUE;` (value `1`): Indicates that callback execution should **continue**. If there are other plugins that also intercept this callback, they will be called (in reverse loading order). Then, the original `public` in the Pawn script will be invoked.
- `return PLUGIN_PUBLIC_STOP;` (value `0`): Indicates that callback execution should be **stopped**. No other plugin (with lower priority) or the original `public` in the Pawn script will be invoked for this event. This is ideal for implementing a system that "overwrites" or "blocks" standard SA-MP behavior.

```cpp
// main.cpp
Plugin_Public(OnPlayerCommandText, int playerid, std::string cmdtext) {
    if (cmdtext == "/freeze") {
        Pawn_Native(TogglePlayerControllable, playerid, 0); // Freeze the player
        Pawn_Native(SendClientMessage, playerid, -1, Plugin_Format("Player %d frozen.", playerid));

        return PLUGIN_PUBLIC_STOP; // Prevent the command from being processed by other scripts.
    }

    return PLUGIN_PUBLIC_CONTINUE; // Allow other commands to be processed.
}
```

#### Ghost Callbacks

An advanced feature of `Plugin_Public` is support for "Ghost Callbacks". This means you can intercept a Pawn callback even if it is **not present** in the gamemode or filterscript `.amx` file. The SDK "tricks" the server into calling your C++ hook anyway. This is useful for internal callbacks or for creating new features without relying on the presence of a `public` in the Pawn script.

```cpp
// You can define a callback that the Pawn script doesn't have, but your plugin will listen to it.
Plugin_Public(OnMyCustomInternalEvent, int data1, float data2) {
    Samp_SDK::Log("Custom internal event received: %d, %.2f", data1, data2);

    return PLUGIN_PUBLIC_CONTINUE;
}

// To "trigger" this event from another point in your C++ code:
// Pawn_Public(OnMyCustomInternalEvent, 123, 45.67f);
// The call will go to your Plugin_Public above, even if there is no OnMyCustomInternalEvent in Pawn.
```

### 3.4. `Plugin_Native`: Creating Native Functions in C++

`Plugin_Native` allows you to extend Pawn functionality with high-performance C++ code.

#### Syntax and Fixed Signature

- `Plugin_Native(NativeName, AMX* amx, cell* params)`
- The C++ function must have exactly this signature: `cell NativeName(AMX* amx, cell* params)`.
- `NativeName` is the name Pawn scripts will use.

```cpp
// Pawn: native GetPlayerPingAverage(playerid);
Plugin_Native(GetPlayerPingAverage, AMX* amx, cell* params) {
    // ... Implementation ...
    return 0;
}
```

#### Automatic Native Registration

> [!NOTE]
> You **do not** need to call `amx_Register` manually. The SDK detects all your `Plugin_Native`s (in any `.cpp` file that has included `samp_sdk.hpp` and defined `SAMP_SDK_WANT_AMX_EVENTS`) and registers them automatically in every loaded AMX script (`OnAmxLoad`).

#### Parameter Extraction: `Register_Parameters` vs. `Native_Params`

##### `Register_Parameters(...)`

- **Description:** Simpler helper to extract multiple parameters sequentially.
- **Usage:** `Register_Parameters(variable1, variable2, ...)`
- **Limitations:** For input parameters. Does not handle optional parameters or index access.
- **Supported Types:** `int`, `float`, `std::string`.

```cpp
// Pawn: native SetPlayerSkinAndMoney(playerid, skinid, money);
Plugin_Native(SetPlayerSkinAndMoney, AMX* amx, cell* params) {
    int playerid, skinid, money;
    Register_Parameters(playerid, skinid, money); // Extracts the 3 parameters
    
    Pawn_Native(SetPlayerSkin, playerid, skinid);
    Pawn_Native(GivePlayerMoney, playerid, money);
    
    return 1;
}
```

##### `Native_Params` (Full API: `Get`, `Get_REF`, `Set_REF`)

- **Description:** A wrapper class providing an object-oriented interface to access native parameters. More powerful for complex scenarios.
- **Construction:** `Native_Params p(amx, params);`

###### `p.Count()`

- **Description:** Returns the number of parameters passed to the native.
- **Usage:** Essential for handling optional parameters.

###### `p.Get<T>(size_t index)`

- **Description:** Extracts an input parameter by index and converts it to type `T`.
- **Supported Types:** `int`, `float`, `std::string`.

```cpp
// Pawn: native GetPlayerWeaponAmmo(playerid, weaponid = -1);
Plugin_Native(GetPlayerWeaponAmmo, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    
    int playerid = p.Get<int>(0);
    int weaponid = (p.Count() > 1) ? p.Get<int>(1) : Pawn_Native(GetPlayerWeapon, playerid);
    
    return Pawn_Native(GetPlayerAmmo, playerid, weaponid);
}
```

###### `p.Get_REF<T>(size_t index, T& out_value)`

- **Description:** Gets the value of a **reference** parameter (Pawn pointer) and stores it in `out_value`.
- **Usage:** To read values that were passed by reference from Pawn.
- **Return:** `true` if the AMX address is valid, `false` otherwise.

```cpp
// Pawn: native CheckPlayerStats(playerid, &Float:health, &money);
Plugin_Native(CheckPlayerStats, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    
    int playerid = p.Get<int>(0);
    float health = 0.0f;
    int money = 0;

    // Gets the values from the references (Pawn passed addresses)
    p.Get_REF(1, health); // Read value of Float:health
    p.Get_REF(2, money);  // Read value of money
    
    Samp_SDK::Log("Player %d, Health: %.1f, Money: %d", playerid, health, money);
    
    // Now, modify them
    health = 50.0f;
    money += 100;
    
    // And write them back to Pawn memory
    p.Set_REF(1, health);
    p.Set_REF(2, money);
    
    return 1;
}
```

###### `p.Get_REF<T>(size_t index)` (C++17+)

- **Description:** Returns a `std::optional<T>` to read a reference parameter. Safer for C++17 and above.

###### `p.Set_REF<T>(size_t index, T value)`

- **Description:** Writes a `T` value to a Pawn **reference** parameter (the address Pawn passed).
- **Usage:** To modify values that were passed by reference, allowing Pawn to see the change.
- **Return:** `true` if the write was successful, `false` otherwise.

#### Returning Values

- Your `Plugin_Native` function must return a `cell`.
- To return an `int` or `bool`, cast to `cell`.
- To return a `float`, use `amx::AMX_FTOC(my_float)`.

```cpp
// Return a bool
Plugin_Native(IsPlayerSpawned, AMX* amx, cell* params) {
    int playerid;
    Register_Parameters(playerid);

    return (Pawn_Native(GetPlayerState, playerid) == PLAYER_STATE_SPAWNED) ? 1 : 0;
}

// Return a float
Plugin_Native(GetPlayerMaxHealth, AMX* amx, cell* params) {
    return amx::AMX_FTOC(100.0f); // Return 100.0f
}
```

### 3.5. `Plugin_Native_Hook`: Intercepting Existing SA-MP Natives

The `Plugin_Native_Hook` macro allows you to intercept and modify the behavior of any existing SA-MP native function or other plugins' natives. This is a powerful mechanism to extend or alter standard server logic.

#### Syntax and Fixed Signature

- `Plugin_Native_Hook(NativeName, AMX* amx, cell* params)`
- The C++ function must have exactly this signature: `cell NativeName(AMX* amx, cell* params)`.
- `NativeName` must be the exact name of the native you want to hook (e.g., `SendClientMessage`, `SetPlayerPos`).

```cpp
// Intercepts the SendClientMessage native
Plugin_Native_Hook(SendClientMessage, AMX* amx, cell* params) {
    // ...
    return Call_Original_Native(SendClientMessage); // Important to call the original
}
```

#### Registration and Hook Activation

> [!NOTE]
> You **do not** need to call `amx_Register` manually or define `SAMP_SDK_WANT_AMX_EVENTS` specifically for `Plugin_Native_Hook`. The SDK automatically detects and registers your hooks. On the first run of an AMX script, the SDK replaces the native pointer in the table with a "trampoline" that redirects to your `Plugin_Native_Hook` function. This process ensures safe hook chaining for multiple plugins.

#### Calling the Original Native (Hook Chain): `Call_Original_Native`

Inside your `Plugin_Native_Hook` function, you **MUST** use the `Call_Original_Native(NativeName)` macro to invoke the original function (or the next hook in the chain). This is vital for:
- **Preserving Functionality:** If you don't call the original, the hooked native will simply stop working for other plugins or the server.
- **Hook Chaining:** Allows multiple plugins to hook the same native and have all hooks executed in sequence.
- **Return Handling:** You can inspect and even modify the return value of `Call_Original_Native` before returning it from your hook function.

```cpp
// Example: Blocking SendClientMessage if it contains a specific word
Plugin_Native_Hook(SendClientMessage, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    
    // Extract parameters for analysis
    int playerid = p.Get<int>(0);
    // int color = p.Get<int>(1); // We don't need color for this logic
    std::string message = p.Get_String(2); // Get the message string

    if (message.find("BADWORD") != std::string::npos) {
        Samp_SDK::Log("MESSAGE BLOCKED for playerid %d: %s", playerid, message.c_str());

        return 0; // Return 0 (false) to Pawn, indicating the message wasn't sent.
                  // And most importantly, we DO NOT call Call_Original_Native, blocking the message.
    }

    // If the message doesn't contain the forbidden word, we call the original native
    // and return its value, ensuring the message is sent normally
    // and other hooks (if any) are executed.
    return Call_Original_Native(SendClientMessage);
}
```

#### Complete Example of `Plugin_Native_Hook`

```cpp
#define SAMP_SDK_IMPLEMENTATION
// SAMP_SDK_WANT_AMX_EVENTS is not strictly necessary for hooks, but common for OnAmxLoad/Unload
// #define SAMP_SDK_WANT_AMX_EVENTS 
#include "samp-sdk/samp_sdk.hpp"

// Hook for CreateVehicle native
Plugin_Native_Hook(CreateVehicle, AMX* amx, cell* params) {
    Native_Params p(amx, params);

    // Extract parameters from CreateVehicle native for inspection
    int modelid = p.Get<int>(0);
    float x = p.Get<float>(1);
    float y = p.Get<float>(2);
    float z = p.Get<float>(3);
    float angle = p.Get<float>(4);
    int color1 = p.Get<int>(5);
    int color2 = p.Get<int>(6);
    int respawn_delay = p.Get<int>(7);
    bool addsiren = p.Get<bool>(8);

    Samp_SDK::Log("HOOK: CreateVehicle called! Model: %d, Pos: (%.2f, %.2f, %.2f)", modelid, x, y, z);

    // Example of how to *modify* an input parameter
    // If model is 400 (Landstalker), change it to 401 (Bravura)
    if (modelid == 400) {
        // We directly modify the 'params' array for the original call
        params[1] = static_cast<cell>(401); // Model is at position 0 of parameter array (params[1])
        Samp_SDK::Log("  -> Model 400 changed to 401 before creation.");
    }
    
    // Call the original native (or next hook in chain) with possibly modified parameters
    cell original_retval = Call_Original_Native(CreateVehicle);

    Samp_SDK::Log("HOOK: CreateVehicle returned: %d (Vehicle ID)", (int)original_retval);

    // You can modify the return value here before returning it to Pawn.
    // Example: if vehicle creation failed, return a custom invalid ID.
    if ((int)original_retval == INVALID_VEHICLE_ID) {
        Samp_SDK::Log("  -> Vehicle creation failed in original native.");

        return -1; // Return a different value to Pawn.
    }

    return original_retval; // Return the value the original native returned (or the modified one above).
}

unsigned int GetSupportFlags() {
    return SUPPORTS_VERSION; 
}

// Minimal implementations for lifecycle
bool OnLoad() {
    Samp_SDK::Log("Native Hook Example Plugin loaded!");
    return true;
}

void OnUnload() {
    Samp_SDK::Log("Native Hook Example Plugin unloaded!");
}

// These callbacks will only be present if SAMP_SDK_WANT_AMX_EVENTS is defined
/*void OnAmxLoad(AMX* amx) {
    Samp_SDK::Log("AMX Load detected: %p", (void*)amx);
}

void OnAmxUnload(AMX* amx) {
    Samp_SDK::Log("AMX Unload detected: %p", (void*)amx);
}*/
```
> [!WARNING]
> Direct manipulation of the `cell* params` array to change input parameters requires caution. Ensure you understand the order and type of parameters. For most use cases, `p.Get(...)` to inspect and `Call_Original_Native(...)` to continue the chain is sufficient. Modifying `params` directly should only be done if you know the parameter is a value and needs to be changed for the original call. For strings and arrays, modification is more complex and usually involves `amx::Set_String` to write to the existing address or reallocating, which can be easier to manage by calling the native via `Pawn_Native` with new values and returning `0` from your hook to cancel the original call.

### 3.6. `Pawn_*` Macros: Calling Pawn Functions from C++

These macros are the inverse of `Plugin_Public` and `Plugin_Native`: they allow your C++ code to invoke Pawn functions.

#### `Pawn_Native(NativeName, ...)`

- **Purpose:** The recommended way to call SA-MP native functions (or other plugins') from C++.
- **Mechanism:** Fetches the native pointer from the SDK's internal cache (populated by `Amx_Register_Detour`). If found, executes the native in an `Amx_Sandbox` environment (a fake, isolated AMX instance).
- **Performance:** Most efficient, as it avoids expensive `publics` lookup and interacts directly with the native pointer.

#### `Pawn_Public(PublicName, ...)`

- **Purpose:** Calls a specific public function in a Pawn script.
- **Mechanism:** Iterates through `AMX*` instances managed by `Amx_Manager`, searches for the `public` by name, and executes it.
- **Performance:** Less efficient than `Pawn_Native` due to lookup and real `amx_Exec`. Generally, `publics` are slower than `natives`.
- **Usage:** Ideal for invoking custom events in your Gamemode/Filterscripts that are not natives.

#### `Pawn(FunctionName, ...)`

- **Purpose:** A convenience macro that tries to guess if the function is a native or a public.
- **Mechanism:** First, tries to call as `Pawn_Native`. If that fails (native not found), tries to call as `Pawn_Public`.
- **Performance:** Can be slightly slower than `Pawn_Native` if the function is native, due to the double lookup attempt. For `publics`, performance is the same as `Pawn_Public`.
- **Usage:** For functions where you are unsure if they are native or public, or to avoid boilerplate of trying one then the other.

#### Syntax and Conventions

- **Function Name:** Always use the Pawn function name **directly, without quotes**. The SDK will convert it to a string internally.
- **Parameters:** Pass C++ parameters directly.

```cpp
// Correct:
Pawn_Native(SetPlayerPos, playerid, 100.0f, 200.0f, 300.0f); 

// Wrong (but technically would work due to hash, avoid):
Pawn_Native("SetPlayerPos", playerid, 100.0f, 200.0f, 300.0f); 
```

#### Input Parameter Marshalling

The SDK converts your C++ types to AMX `cell` format, managing memory as needed:
- `int`, `bool`, `long`, `enum` -> `cell`
- `float`, `double` -> `cell` (using `amx::AMX_FTOC`)
- `const char*`, `std::string`, `std::string_view` (C++17+) -> `cell` (allocates memory in AMX, copies string, and passes `amx_addr`)

```cpp
void Send_Formatted_Message(int playerid, const std::string& msg) {
    Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, msg);
}
```

#### Output Parameter Marshalling (References: `int&`, `float&`, `std::string&`)

This is a key feature for convenience and safety. For Pawn functions expecting a pointer (reference), the SDK automates the entire process of memory allocation/release and data copying.

- **How to use:** Just pass your variable by reference (`&`).
- **Mechanism:** The SDK allocates memory on the AMX heap, passes the AMX address to the Pawn function, waits for the Pawn function to fill that address, reads the value back, and frees AMX memory. All transparently.
- **With `std::string&`:** The SDK allocates a default buffer (256 cells) in AMX for the string.

```cpp
void Get_Player_Location(int playerid) {
    float x, y, z;
    int interiorid, worldid;
    std::string name;

    Pawn_Native(GetPlayerPos, playerid, x, y, z);
    Pawn_Native(GetPlayerInterior, playerid, interiorid);
    Pawn_Native(GetPlayerVirtualWorld, playerid, worldid);
    Pawn_Native(GetPlayerName, playerid, name, MAX_PLAYER_NAME);

    Samp_SDK::Log("Location of %s (ID:%d): Pos(%.2f, %.2f, %.2f) Interior:%d World:%d", name.c_str(), playerid, x, y, z, interiorid, worldid);
}
```

#### The `Callback_Result` Object: Complete Analysis

All `Pawn_*` calls return a `Callback_Result` object. This object is a safe wrapper for the Pawn call result.

- `Callback_Result() noexcept`: Default constructor, indicates failure (`success_ = false`).
- `Callback_Result(bool success, cell value) noexcept`: Constructor for success or failure with value.
- `explicit operator bool() const`: Allows using `if (result)` to check if the call succeeded.
- `operator cell() const`: Allows converting result to `cell` to get the value.
- `float As_Float() const`: Convenience to get result as `float`.
- `cell Value() const`: Returns raw `cell` value.
- `bool Success() const`: Returns `true` if Pawn call succeeded.
- `int Get_Amx_Error() const`: Returns AMX error code if call failed (0 for success).

```cpp
// Example: Getting a player's health.
// The native GetPlayerHealth(playerid, &Float:health) expects a playerid and a reference to health.
int playerid = 0; // Example player ID
float player_health = 0.0f;

// Call GetPlayerHealth, passing playerid and player_health by reference.
// The SDK will handle marshalling for the output parameter 'health'.
Callback_Result result = Pawn_Native(GetPlayerHealth, playerid, player_health);

if (result) { // Checks if call succeeded (operator bool)
    // The value returned by result.As_Float() or result (operator cell)
    // would be the return value of the *native*, not the output parameter.
    // The health value is already updated in 'player_health' due to output parameter marshalling.
    Samp_SDK::Log("Player %d has %.1f health.", playerid, player_health);
}
else {
    // Call failed, maybe player doesn't exist or native wasn't found.
    Samp_SDK::Log("Error getting health for player %d. AMX Code: %d", playerid, result.Get_Amx_Error());
}

// For natives that return a value AND use output parameters (less common, but possible),
// you would use both:
// Callback_Result other_result = Pawn_Native(SomeNative, param1, output_param, param2);
// if (other_result) {
//     cell returned_value = other_result;
//     // output_param is already updated
// }
```

### 3.7. `Plugin_Module`: Dynamic Module Management

The `Plugin_Module` macro allows your plugin to act as a "loader" for other plugins, creating a modular and extensible architecture. A module loaded this way is treated as a first-class plugin, with its own event life cycle managed by the host plugin.

#### Syntax and Purpose

- `Plugin_Module(const char* base_filename, const char* module_directory, const char* optional_success_message)`
- `base_filename`: The *base* name of the module file, **without extension** (e.g., for `my_module.dll` or `my_module.so`, use `"my_module"`). The SDK will automatically add the appropriate `.dll` or `.so` extension.
- `module_directory`: The directory path where the module file is located (e.g., `"plugins/my_custom_modules"`). **Do not include the filename here.** The SDK will concatenate the full path (`module_directory/base_filename.ext`).
- `optional_success_message`: An optional message to be logged to server console if the module loads successfully.

```cpp
// main.cpp, inside OnLoad()

// Loads module 'core_logic.dll' (or 'core_logic.so')
// located in server's 'modules/custom/' folder.
if (!Plugin_Module("core_logic", "modules/custom", "Core Logic Module loaded successfully!"))
    return (Samp_SDK::Log("FATAL ERROR: Failed to load 'core_logic' module!"), false);

// Loads module 'admin_system.dll' (or 'admin_system.so')
// located directly in server's 'plugins/' folder.
if (!Plugin_Module("admin_system", "plugins", "Admin Module activated."))
    Samp_SDK::Log("WARNING: Admin Module could not be loaded.");
```

#### Module Life Cycle

A module must export `Load`, `Unload`, and `Supports` functions, just like a normal plugin. The SDK manages the module life cycle as follows:

- **Loading:** When `Plugin_Module` is called, the SDK:
   1. Constructs full file path (e.g., `modules/custom/core_logic.dll`).
   2. Uses `Dynamic_Library` (`LoadLibrary`/`dlopen`) to load binary.
   3. **Gets pointers to ALL module lifecycle functions:**
      - **Mandatory:** `Load`, `Unload`, `Supports`. If any missing, module loading fails.
      - **Optional:** `AmxLoad`, `AmxUnload`, `ProcessTick`.
   4. Calls module's `Load` function, passing main plugin's `ppData`.
   5. If `Load` returns `true`, module is added to internal loaded modules list.

- **Event Forwarding:** The host plugin **automatically forwards** events to all loaded modules.
 > [!IMPORTANT]
 > For events to be forwarded correctly, the **host plugin** (calling `Plugin_Module`) must be configured to receive these events.
 > - For `AmxLoad` and `AmxUnload` to work in modules, host plugin must define `SAMP_SDK_WANT_AMX_EVENTS`.
 > - For `ProcessTick` to work in modules, host plugin must define `SAMP_SDK_WANT_PROCESS_TICK`.

- **Unloading:** During `OnUnload` of your main plugin, the SDK unloads all modules loaded via `Plugin_Module`. This is done in **reverse order** of loading (last loaded is first unloaded), which is crucial for dependency management and correct resource release.

#### Benefits of Modularization

- **Code Organization:** Break large plugins into smaller, manageable components, each in its own module file.
- **Reusability:** Create generic modules (e.g., a database module, advanced logging module) that can be used by different plugins, promoting code reuse.
- **Independent Components:** Create modules that are **fully event-driven and independent**. A module can have its own `Plugin_Native`s, intercept `Plugin_Public`s, and have its own `OnProcessTick` logic, operating as an autonomous plugin but loaded by a host.
- **Dynamic Updates:** In controlled scenarios, allows updating parts of your system (replacing a module `.dll` or `.so`) without recompiling and restarting the main plugin or entire server (though this requires strict version and compatibility management).

### 3.8. `Plugin_Call`: Calling Internal Plugin Natives

Use `Plugin_Call` to invoke a `Plugin_Native` defined **inside your own plugin**.

#### Syntax and Performance Advantages

- `Plugin_Call(NativeName, Param1, Param2, ...)`
- **Advantage:** Avoids overhead of searching native in AMX native array. The SDK keeps a direct map of name hashes to function pointers for its own natives, making this the fastest way to call them internally.
- **Requires:** `SAMP_SDK_WANT_AMX_EVENTS`.

```cpp
// main.cpp
Plugin_Native(InternalCheckPlayerLevel, AMX* amx, cell* params) {
    int playerid;
    Register_Parameters(playerid);

    // Logic to check level
    return (playerid % 2 == 0) ? 1 : 0; // Example: even level for even IDs
}

void Check_All_Players_Level() {
    for (int i = 0; i < MAX_PLAYERS; ++i) {
        if (Pawn_Native(IsPlayerConnected, i)) {
            if (Plugin_Call(InternalCheckPlayerLevel, i)) // Call your own native
                Samp_SDK::Log("Player %d is high level!", i);
        }
    }
}
```

### 3.9. SDK Utility Functions

#### `Samp_SDK::Log(const char* format, ...)`

- **Description:** Prints messages to server console and `server_log.txt`. A safe wrapper for `logprintf`.
- **Usage:** For debugging, status messages, and errors.
- **Mechanism:** Internally, the SDK gets `logprintf` pointer via `ppData[PLUGIN_DATA_LOGPRINTF]`. The function handles string formatting safely.

```cpp
// Anywhere in your plugin
Samp_SDK::Log("Plugin initialized with value %d and string '%s'.", 123, "test");
```

#### `std::string Plugin_Format(const char* format, ...)` (Recommended)

- **Description:** Formats a string safely (similar to `sprintf`) and returns a `std::string`. This is the **recommended and most idiomatic** way to format strings for use inside your plugin.
- **Usage:** Ideal for building formatted messages before passing to `Samp_SDK::Log`, `Pawn_Native(SendClientMessage, ...)`, or any other string need in your C++ code.
- **Mechanism:** Internally, `Plugin_Format` is a macro calling `Samp_SDK::Format`. It uses `vsnprintf` to determine exact formatted string size and allocates `std::string` with sufficient capacity, avoiding buffer overflows.

```cpp
int playerid = 0; // Example ID
int health = 50;
Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, Plugin_Format("Player %d, your current health is %d.", playerid, health));

// Can also be used for internal logs
Samp_SDK::Log(Plugin_Format("DEBUG: Processing status for ID %d", playerid));
```

#### `std::string Samp_SDK::Format(const char* format, ...)` (Implementation Detail)

- **Description:** The underlying implementation function for string formatting, located inside `Samp_SDK` namespace.
- **Usage:** Generally not called directly by user. The `Plugin_Format` macro is provided as convenience for this function, aligning with naming convention of other SDK macros (`Plugin_Public`, `Plugin_Native`). You would only call it directly if you wanted to avoid `Plugin_Format` macro for some specific reason.

```cpp
// Example of how Samp_SDK::Format works, but prefer Plugin_Format
std::string raw_status = Samp_SDK::Format("Internal use only: %d.", 42);
```

#### `std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`

- **Description:** Converts an AMX string address (`cell amx_addr`) into a C++ `std::string`.
- **Usage:** Mainly inside `Plugin_Native` and `Plugin_Native_Hook` when you need to access strings that aren't automatically converted by `Register_Parameters` or `Native_Params` (e.g., if Pawn parameter is `const` `string` and wasn't declared as `std::string` in your `Plugin_Native` or `Plugin_Public` for automatic Marshalling).

```cpp
Plugin_Native(PrintRawAmxString, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    cell amx_string_addr = p.Get<cell>(0); // Get string address in AMX

    std::string cpp_string = Samp_SDK::Get_String(amx, amx_string_addr);
    Samp_SDK::Log("String from AMX: %s", cpp_string.c_str());

    return 1;
}
```

## 4. Compilation and Deploy

### Architecture and Platform Requirements

- Your plugin **MUST** be compiled for **x86 (32-bit)** architecture.
- Supported Platforms: Windows (.dll) and Linux (.so).

### Build Command Examples

#### **MSVC (Visual Studio)**

1. Create a new "Dynamic-Link Library (DLL)" project.
2. In project settings, set "Solution Platform" to **x86**.
3. Ensure C++ Language Standard is at least C++17.

#### **GCC / Clang (Linux)**

```bash
# For a plugin named 'my_plugin.so' from 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -fPIC -Wall -Wextra -Wl,--no-undefined main.cpp -o my_plugin.so
```
- `-m32`: Compile for 32-bit.
- `-shared`: Create a shared library (`.so`).
- `-std=c++17`: Set C++ standard to C++17 (can be `c++20`, but C++17 is minimum).
- `-O2`: Optimization level 2.
- `-fPIC`: Generate Position Independent Code, required for shared libraries.
- `-Wall -Wextra`: Enable extra warnings to help catch errors.
- `-Wl,--no-undefined`: Prevent library creation if there are undefined symbols.

#### **GCC / Clang (MinGW on Windows)**

```bash
# For a plugin named 'my_plugin.dll' from 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -static-libstdc++ -static-libgcc -Wl,--no-undefined main.cpp -o my_plugin.dll
```
- `-static-libstdc++`: Links standard C++ library statically. Essential to avoid plugin depending on compiler-specific runtime DLLs that might not be present on user's system.
- `-static-libgcc`: Links GCC library statically.

### Distribution Considerations

- **Filename:** Your plugin must have `.dll` (Windows) or `.so` (Linux) extension. E.g., `my_plugin.dll`.
- **Location:** Place compiled file in `plugins/` folder of your SA-MP server.
- **server.cfg:** Add your plugin name (if Windows, without extension) to `plugins` line in `server.cfg`.
   ```
   plugins my_plugin (if Linux, my_plugin.so)
   ```

## License

Copyright © **AlderGrounds**

This software is licensed under the terms of the MIT License ("License"); you may use this software according to the conditions of the License. A copy of the License can be obtained at: [MIT License](https://opensource.org/licenses/MIT)

### Terms and Conditions of Use

#### 1. Granted Permissions

The present license grants, free of charge, to any person obtaining a copy of this software and associated documentation files, the following rights:
* To use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the software without restriction
* To permit persons to whom the software is furnished to do so, subject to the following conditions

#### 2. Mandatory Conditions

All copies or substantial portions of the software must include:
* The above copyright notice
* This permission notice
* The disclaimer notice below

#### 3. Copyright

The software and all associated documentation are protected by copyright laws. **AlderGrounds** retains ownership of the original copyright of the software.

#### 4. Disclaimer of Warranties and Limitation of Liability

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.

IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

---

For detailed information about the MIT License, visit: https://opensource.org/licenses/MIT