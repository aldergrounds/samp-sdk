# SA-MP SDK

<div align="center">

![C++](https://img.shields.io/badge/C%2B%2B-17%2B-00599C?style=for-the-badge&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-blue?style=for-the-badge&logo=windows&logoColor=white)
![Architecture](https://img.shields.io/badge/Architecture-x86%20(32--bit)-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**Ett modernt, header-only och högnivå C++ SDK för utveckling av plugins och moduler för SA-MP.**

</div>

## Språk

- Português: [README](../../)
- Deutsch: [README](../Deutsch/README.md)
- English: [README](../English/README.md)
- Español: [README](../Espanol/README.md)
- Français: [README](../Francais/README.md)
- Italiano: [README](../Italiano/README.md)
- Polski: [README](../Polski/README.md)
- Русский: [README](../Русский/README.md)
- Türkçe: [README](../Turkce/README.md)

## Innehållsförteckning

- [SA-MP SDK](#sa-mp-sdk)
  - [Språk](#språk)
  - [Innehållsförteckning](#innehållsförteckning)
  - [1. Introduktion och Designfilosofi](#1-introduktion-och-designfilosofi)
    - [Problemet med SA-MPs Standard C API](#problemet-med-sa-mps-standard-c-api)
    - [SA-MP SDKs Lösning: Abstraktion med Säkerhet och Prestanda](#sa-mp-sdks-lösning-abstraktion-med-säkerhet-och-prestanda)
    - [Header-Only Modell: Fördelar och Implikationer](#header-only-modell-fördelar-och-implikationer)
  - [2. Konfiguration och Miljö](#2-konfiguration-och-miljö)
    - [Kompileringskrav](#kompileringskrav)
    - [Rekommenderad Filstruktur](#rekommenderad-filstruktur)
    - [Viktiga Konfigurationsmakron](#viktiga-konfigurationsmakron)
      - [`SAMP_SDK_IMPLEMENTATION`](#samp_sdk_implementation)
      - [`SAMP_SDK_WANT_AMX_EVENTS`](#samp_sdk_want_amx_events)
      - [`SAMP_SDK_WANT_PROCESS_TICK`](#samp_sdk_want_process_tick)
    - [SA-MP Definitioner och Konstanter (`samp_defs.hpp`)](#sa-mp-definitioner-och-konstanter-samp_defshpp)
  - [3. Omfattande API Användarguide](#3-omfattande-api-användarguide)
    - [3.1. Pluginets Livscykel](#31-pluginets-livscykel)
      - [`bool OnLoad()`](#bool-onload)
      - [`void OnUnload()`](#void-onunload)
      - [`unsigned int GetSupportFlags()`](#unsigned-int-getsupportflags)
      - [`void OnAmxLoad(AMX* amx)`](#void-onamxloadamx-amx)
      - [`void OnAmxUnload(AMX* amx)`](#void-onamxunloadamx-amx)
      - [`void OnProcessTick()`](#void-onprocesstick)
    - [3.2. Exportera Plugin-funktioner](#32-exportera-plugin-funktioner)
      - [Export för MSVC (Visual Studio) med `Export_Plugin`](#export-för-msvc-visual-studio-med-export_plugin)
      - [Export för GCC / Clang med `SAMP_SDK_EXPORT`](#export-för-gcc--clang-med-samp_sdk_export)
    - [3.3. `Plugin_Public`: Intercepting Pawn Events](#33-plugin_public-intercepting-pawn-events)
      - [Syntax och Deklaration](#syntax-och-deklaration)
      - [Automatisk Parameter-Marshalling](#automatisk-parameter-marshalling)
      - [Flödeskontroll: `PUBLIC_CONTINUE` vs `PUBLIC_STOP`](#flödeskontroll-public_continue-vs-public_stop)
      - [Ghost Callbacks](#ghost-callbacks)
    - [3.4. `Plugin_Native`: Skapa Native-funktioner i C++](#34-plugin_native-skapa-native-funktioner-i-c)
      - [Syntax och Fast Signatur](#syntax-och-fast-signatur)
      - [Automatisk Registrering av Natives](#automatisk-registrering-av-natives)
      - [Parameterutvinning: `Register_Parameters` vs. `Native_Params`](#parameterutvinning-register_parameters-vs-native_params)
        - [`Register_Parameters(...)`](#register_parameters)
        - [`Native_Params` (Full API: `Get`, `Get_REF`, `Set_REF`)](#native_params-full-api-get-get_ref-set_ref)
          - [`p.Count()`](#pcount)
          - [`p.Get<T>(size_t index)`](#pgettsize_t-index)
          - [`p.Get_REF<T>(size_t index, T& out_value)`](#pget_reftsize_t-index-t-out_value)
          - [`p.Get_REF<T>(size_t index)` (C++17+)](#pget_reftsize_t-index-c17)
          - [`p.Set_REF<T>(size_t index, T value)`](#pset_reftsize_t-index-t-value)
      - [Returvärden](#returvärden)
    - [3.5. `Plugin_Native_Hook`: Intercepting Existing SA-MP Natives](#35-plugin_native_hook-intercepting-existing-sa-mp-natives)
      - [Syntax och Fast Signatur](#syntax-och-fast-signatur-1)
      - [Registrering och Aktivering av Hook](#registrering-och-aktivering-av-hook)
      - [Anropa Original Native (Hook-kedja): `Call_Original_Native`](#anropa-original-native-hook-kedja-call_original_native)
      - [Fullständigt Exempel på `Plugin_Native_Hook`](#fullständigt-exempel-på-plugin_native_hook)
    - [3.6. `Pawn_*` Makron: Anropa Pawn-funktioner från C++](#36-pawn_-makron-anropa-pawn-funktioner-från-c)
      - [`Pawn_Native(NativeName, ...)`](#pawn_nativenativename-)
      - [`Pawn_Public(PublicName, ...)`](#pawn_publicpublicname-)
      - [`Pawn(FunctionName, ...)`](#pawnfunctionname-)
      - [Syntax och Konventioner](#syntax-och-konventioner)
      - [Marshalling av Input-parametrar](#marshalling-av-input-parametrar)
      - [Marshalling av Output-parametrar (Referenser: `int&`, `float&`, `std::string&`)](#marshalling-av-output-parametrar-referenser-int-float-stdstring)
      - [Objektet `Callback_Result`: Fullständig Analys](#objektet-callback_result-fullständig-analys)
    - [3.7. `Plugin_Module`: Hantering av Dynamiska Moduler](#37-plugin_module-hantering-av-dynamiska-moduler)
      - [Syntax och Syfte](#syntax-och-syfte)
      - [En Moduls Livscykel](#en-moduls-livscykel)
      - [Fördelar med Modularisering](#fördelar-med-modularisering)
    - [3.8. `Plugin_Call`: Anropa Pluginets Interna Natives](#38-plugin_call-anropa-pluginets-interna-natives)
      - [Syntax och Prestandafördelar](#syntax-och-prestandafördelar)
    - [3.9. SDK Verktygsfunktioner](#39-sdk-verktygsfunktioner)
      - [`Samp_SDK::Log(const char* format, ...)`](#samp_sdklogconst-char-format-)
      - [`std::string Plugin_Format(const char* format, ...)` (Rekommenderas)](#stdstring-plugin_formatconst-char-format--rekommenderas)
      - [`std::string Samp_SDK::Format(const char* format, ...)` (Implementeringsdetalj)](#stdstring-samp_sdkformatconst-char-format--implementeringsdetalj)
      - [`std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`](#stdstring-samp_sdkget_stringamx-amx-cell-amx_addr)
  - [4. Kompilering och Deploy](#4-kompilering-och-deploy)
    - [Krav på Arkitektur och Plattform](#krav-på-arkitektur-och-plattform)
    - [Exempel på Kompileringskommandon](#exempel-på-kompileringskommandon)
      - [**MSVC (Visual Studio)**](#msvc-visual-studio)
      - [**GCC / Clang (Linux)**](#gcc--clang-linux)
      - [**GCC / Clang (MinGW på Windows)**](#gcc--clang-mingw-på-windows)
    - [Överväganden för Distribution](#överväganden-för-distribution)
  - [Licens](#licens)
    - [Användarvillkor](#användarvillkor)
      - [1. Beviljade rättigheter](#1-beviljade-rättigheter)
      - [2. Obligatoriska villkor](#2-obligatoriska-villkor)
      - [3. Upphovsrätt](#3-upphovsrätt)
      - [4. Garantifriskrivning och ansvarsbegränsning](#4-garantifriskrivning-och-ansvarsbegränsning)

## 1. Introduktion och Designfilosofi

### Problemet med SA-MPs Standard C API

SA-MP plugin API är ett C-programmeringsgränssnitt. Även om det är funktionellt och grundläggande, presenterar det utmaningarna som är inneboende i lågnivåprogrammering:
- **Manuell Minneshantering:** Funktioner som `amx_Allot` och `amx_Release` kräver att utvecklaren explicit allokerar och frigör minne på AMX-heapen. Detta är en vanlig källa till minnesläckor och körtidsfel.
- **Svag Typning och Manuella Konverteringar:** Parametrar skickas som en array av `cell`s, vilket tvingar fram explicita (och ofta osäkra) konverteringar mellan `cell`, `int`, `float` och `char*`.
- **Verbositet och Boilerplate:** Att extrahera flera parametrar från en `cell* params`-array, hantera strängstorlekar och hantera AMX-stacken för C++ till Pawn-återanrop kräver repetitiv kod.
- **Gränssnittets Bräcklighet:** Bristen på kompileringstidsverifiering (type safety) innebär att fel i parameteröverföring eller typer kan gå obemärkta förbi fram till exekvering, vilket orsakar krascher eller odefinierade beteenden.

### SA-MP SDKs Lösning: Abstraktion med Säkerhet och Prestanda

SA-MP SDK tacklar dessa problem genom att tillhandahålla ett kraftfullt abstraktionslager i C++:
- **RAII (Resource Acquisition Is Initialization):** Automatisk minneshantering i AMX. `Amx_Scoped_Memory` säkerställer att allokerat minne frigörs.
- **Typsäkerhet:** Automatisk och säker konvertering av parametrar mellan C++ och Pawn. Du hanterar `int`, `float`, `std::string` direkt.
- **Koncis och Idiomatisk Syntax:** Makron och templates tillhandahåller ett rent API som mer liknar modern C++ än det traditionella C-API:et.
- **Robust Intercepting:** En avancerad hooking-motor möjliggör transparent intercepting av Pawn callbacks (`Plugin_Public`), skapande av nya natives (`Plugin_Native`), och **hooking och kedjning av befintliga SA-MP native-funktioner (`Plugin_Native_Hook`)**.
- **Hög Prestanda:** Omfattande användning av kompileringstids-hashing (FNV1a), funktionscaching och `thread_local`-optimeringar för att minimera overheaden av abstraktionerna.

### Header-Only Modell: Fördelar och Implikationer

SDK:n består uteslutande av header-filer (`.hpp`, `.h`).
- **Fördelar:**
   - **Förenklad Integration:** Inga bibliotek att bygga, länka eller distribuera. Inkludera bara headrarna.
   - **Kompileringsoptimeringar:** Kompilatorn har fullständig insyn i SDK:s kod och ditt plugins kod, vilket möjliggör aggressiv inlining och länkningstidsoptimeringar, vilket kan resultera i snabbare binärfiler.
- **Implikationer:**
   - **Kompileringstid:** För mycket stora projekt kan kompileringen ta längre tid på grund av upprepad inkludering av SDK-koden. Detta minskas genom inklusions-guards och C++:s "inkludera bara det som behövs"-natur.
   - **Implementeringsmakron:** Behovet av makrot `SAMP_SDK_IMPLEMENTATION` är en konsekvens av header-only-modellen för att undvika omdefinitioner av symboler.

## 2. Konfiguration och Miljö

### Kompileringskrav

- **C++-kompilator:** Kompatibel med C++17 eller senare.
  - GCC (version 8+)
  - Clang (version 5+)
  - MSVC (Visual Studio 2017+)
- **Arkitektur:** **x86 (32-bitars)**. SA-MP fungerar uteslutande på denna arkitektur. SDK:t innehåller kontroller i `platform.hpp` som kommer att generera kompileringsfel om fel arkitektur upptäcks.
- **Operativsystem:** Windows eller Linux.

### Rekommenderad Filstruktur

För tydlighet och organisation är det vanligt att organisera SDK:n i en undermapp `samp-sdk`.

```
my_plugin/
├── samp-sdk/
│   ├── // Andra SDK-filer
│   └── samp_sdk.hpp // Den huvudsakliga headern som ska inkluderas
│
├── src/
│   ├── main.cpp // Där SAMP_SDK_IMPLEMENTATION definieras
│   └── my_custom_logic.cpp // Valfritt, för att organisera kod
│
└── CMakeLists.txt (eller .vcxproj, Makefile)
```

### Viktiga Konfigurationsmakron

Definiera alltid dessa makron *innan* du inkluderar `samp_sdk.hpp`.

#### `SAMP_SDK_IMPLEMENTATION`

- **Syfte:** Signalera till kompilatorn att den här `.cpp`-filen ska generera implementeringarna av pluginets exportfunktioner (`Supports`, `Load`, `Unload`, `AmxLoad`, `AmxUnload`, `ProcessTick`). **SDK:n hanterar exporteringen av dessa funktioner automatiskt, vilket eliminerar behovet av `.def`-filer (på Windows) eller `__attribute__((visibility("default")))`-deklarationer (på Linux) för dessa funktioner.**
- **Teknisk påverkan:** Utan detta makro kommer länkaren inte att hitta de nödvändiga exporteringarna, och SA-MP-servern kommer inte att kunna ladda ditt plugin.
- **Grundläggande regel:** **Definiera detta makro i ENDAST EN `.cpp`-fil i hela ditt projekt.** Att definiera det i mer än en fil kommer att orsaka ett länkfel av typen "dubbel symbol".

```cpp
// main.cpp
#define SAMP_SDK_IMPLEMENTATION // Makrot gör att SDK:n exporterar de nödvändiga funktionerna automatiskt.
#include "samp-sdk/samp_sdk.hpp"

// ... din plugin-kod ...
```

#### `SAMP_SDK_WANT_AMX_EVENTS`

- **Syfte:** Aktiverar Pawn-skriptets livscykel-callbacks (`OnAmxLoad`, `OnAmxUnload`) och funktionaliteten att skapa nya C++-natives (`Plugin_Native`).
- **Aktiverade Funktioner:**
   - Callbacks `OnAmxLoad(AMX* amx)` och `OnAmxUnload(AMX* amx)`.
   - Deklaration och registrering av nya C++ natives med `Plugin_Native`.
   - Makrot `Plugin_Call` för att anropa natives skapade med `Plugin_Native` inom ditt eget plugin.
- **Teknisk påverkan:** När detta makro är definierat samlar SDK:n automatiskt in alla dina `Plugin_Native`s. I funktionen `Supports()` läggs flaggan `SUPPORTS_AMX_NATIVES` automatiskt till om det finns några `Plugin_Native`s i ditt projekt.
- **Flexibilitet:** **Du kan definiera detta makro i flera `.cpp`-filer.** SDK:ns statiska registreringssystem kommer att konsolidera alla natives från olika kompileringsenheter till en enda global lista.

```cpp
// my_natives.cpp (kan vara en separat fil från main.cpp)
#define SAMP_SDK_WANT_AMX_EVENTS // Endast för att aktivera Plugin_Native och OnAmxLoad/OnAmxUnload callbacks
#include "samp-sdk/samp_sdk.hpp"

Plugin_Native(MyCustomNative, AMX* amx, cell* params) {
    // ...
    return 0;
}
```

#### `SAMP_SDK_WANT_PROCESS_TICK`

- **Syfte:** Aktiverar `OnProcessTick()` callback, som anropas regelbundet av servern.
- **Teknisk påverkan:** Lägger automatiskt till flaggan `SUPPORTS_PROCESS_TICK` i funktionen `Supports()`.

```cpp
// main.cpp
#define SAMP_SDK_IMPLEMENTATION
#define SAMP_SDK_WANT_PROCESS_TICK
#include "samp-sdk/samp_sdk.hpp"

void OnProcessTick() {
    // Logik som körs vid varje "tick" på servern (t.ex. 20ms)
    // Var försiktig med tunga operationer här!
}
```

### SA-MP Definitioner och Konstanter (`samp_defs.hpp`)

Denna fil tillhandahåller alla kända SA-MP konstanter och gränser, som `MAX_PLAYERS`, `INVALID_PLAYER_ID`, `PLAYER_STATE_ONFOOT`, `WEAPON_DEAGLE`, `DIALOG_STYLE_LIST`, etc. Den inkluderas automatiskt av `samp_sdk.hpp` och bör användas för att säkerställa kompatibilitet och läsbarhet i koden.

## 3. Omfattande API Användarguide

### 3.1. Pluginets Livscykel

Följande funktioner är ingångs- och utgångspunkterna för ditt plugin, automatiskt exporterade av SDK:n.

#### `bool OnLoad()`

- **Beskrivning:** Första funktionen som anropas av SA-MP-servern efter att ditt plugin har laddats in i minnet.
- **Användning:** Idealisk för att initialisera system, ladda konfigurationer, öppna databasanslutningar eller ladda moduler (`Plugin_Module`).
- **Returvärde:**
   - `true`: Pluginet har initialiserats framgångsrikt och laddningen fortsätter.
   - `false`: Pluginet misslyckades med att initialisera. Laddningen avbryts och pluginet laddas ur.

```cpp
// main.cpp
bool OnLoad() {
    Samp_SDK::Log("Initialiserar MyPlugin v1.0...");

    // Exempel: Ladda en modul (mer detaljer i avsnitt 3.6)
    if (!Plugin_Module("my_database_module", "plugins/db_connector", "Databasmodulen laddad.")) {
        Samp_SDK::Log("FEL: Kunde inte ladda databasmodulen!");

        return false; // Avbryter laddningen av huvudpluginet
    }

    return true;
}
```

#### `void OnUnload()`

- **Beskrivning:** Sista funktionen som anropas av SA-MP-servern innan ditt plugin avlastas från minnet.
- **Användning:** Idealisk för att rensa upp resurser, stänga anslutningar, spara tillstånd och säkerställa att inga resurser läcker. SDK:n hanterar avlastning av moduler (`Plugin_Module`) automatiskt.

```cpp
// main.cpp
void OnUnload() {
    Samp_SDK::Log("MyPlugin avlastat. Frigör resurser...");
    // Ingen manuell åtgärd behövs för moduler laddade via Plugin_Module;
    // SDK:n hanterar detta.
}
```

#### `unsigned int GetSupportFlags()`

- **Beskrivning:** Informerar SA-MP-servern vilka funktioner ditt plugin stöder och vill använda.
- **Användning:** **Returnera alltid `SUPPORTS_VERSION` (eller `SAMP_PLUGIN_VERSION`).** Flaggorna `SUPPORTS_AMX_NATIVES` och `SUPPORTS_PROCESS_TICK` läggs till automatiskt av SDK:n om det finns `Plugin_Native`s, och/eller om makrot `SAMP_SDK_WANT_PROCESS_TICK` är definierat, respektive. Detta förenklar underhåll och förhindrar fel.

```cpp
// main.cpp
unsigned int GetSupportFlags() {
    return SUPPORTS_VERSION; // SDK:n lägger automatiskt till de nödvändiga flaggorna.
}
```

#### `void OnAmxLoad(AMX* amx)`

- **Kräver:** `SAMP_SDK_WANT_AMX_EVENTS`
- **Beskrivning:** Anropas varje gång ett nytt Pawn-skript (ett Gamemode eller Filterscript) laddas och initialiseras på servern.
- **Användning:** Om du behöver specifik logik för varje AMX-skript, eller initialisera specifika data per skript.

```cpp
// main.cpp (med SAMP_SDK_WANT_AMX_EVENTS definierat)
void OnAmxLoad(AMX* amx) {
    // amx representerar den nya laddade skriptinstansen.
    Samp_SDK::Log("AMX-skript laddat: %p", (void*)amx);
}
```

#### `void OnAmxUnload(AMX* amx)`

- **Kräver:** `SAMP_SDK_WANT_AMX_EVENTS`
- **Beskrivning:** Anropas när ett Pawn-skript avlastas från servern.
- **Användning:** För att rensa upp eventuella specifika resurser som du allokerade eller associerade med den specifika `AMX*`.

```cpp
// main.cpp (med SAMP_SDK_WANT_AMX_EVENTS definierat)
void OnAmxUnload(AMX* amx) {
    Samp_SDK::Log("AMX-skript avlastat: %p", (void*)amx);
}
```

#### `void OnProcessTick()`

- **Kräver:** `SAMP_SDK_WANT_PROCESS_TICK`
- **Beskrivning:** Anropas upprepade gånger vid varje "tick" på servern (vanligtvis 20 gånger per sekund, eller var 50:e ms).
- **Användning:** För kontinuerlig bakgrundslogik, timers, tillståndsuppdateringar som inte är beroende av spelarhändelser, eller datasynkronisering.
- **Varning:** Undvik blockerande eller beräkningsmässigt tunga operationer här, eftersom de kan orsaka lagg på servern.

```cpp
// main.cpp (med SAMP_SDK_WANT_PROCESS_TICK definierat)
static int tick_count = 0;

void OnProcessTick() {
    tick_count++;

    if (tick_count % 200 == 0) // Var 10:e sekund (20 ticks/sek * 10 sek = 200 ticks)
        Samp_SDK::Log("Server aktiv i %d sekunder.", tick_count / 20);
}
```

### 3.2. Exportera Plugin-funktioner

För att SA-MP-servern ska kunna anropa ditt plugins funktioner (`Load`, `Supports`, etc.) måste de "exporteras" från DLL-filen (Windows) eller SO-filen (Linux). SDK:n automatiserar exporten av standardlivscykelfunktioner, men tillhandahåller också verktyg för att du ska kunna exportera dina egna anpassade funktioner, om du behöver interoperabilitet med andra program.

Metoden för att exportera funktioner varierar beroende på kompilator.

#### Export för MSVC (Visual Studio) med `Export_Plugin`

På Windows med MSVC är det enklaste sättet att exportera anpassade funktioner att använda makrot `Export_Plugin`, som definieras i `exports.hpp`.

- **Syntax:** `Export_Plugin("Funktion", "Stack")`
- **`Funktion`**: Det exakta namnet på funktionen som ska exporteras.
- **`Stack`**: Det totala antalet bytes som funktionens parametrar upptar på stacken. För `__stdcall`-konventionen (SDK-standard på Windows) är beräkningen `4 * (Antal Parametrar)`.

```cpp
#include "samp-sdk/exports.hpp"

// Exempel: Exportera en anpassad funktion som skulle kunna anropas
// av ett annat program eller plugin som känner till dess signatur.
const char* SAMP_SDK_CALL GetPluginVersion() {
    return "1.0.0";
}

Export_Plugin("GetPluginVersion", "0");
```

> [!WARNING]
> **Begränsning av `Export_Plugin`**
> Detta makro fungerar **endast med MSVC-kompilatorn (Visual Studio)**. Det använder ett Microsoft-specifikt `#pragma`-direktiv som ignoreras av andra kompilatorer som GCC och Clang.

#### Export för GCC / Clang med `SAMP_SDK_EXPORT`

För GCC och Clang (på Windows eller Linux) hanteras exporten av makrot `SAMP_SDK_EXPORT`, som definieras i `platform.hpp`. Du placerar det helt enkelt före funktionsdefinitionen.

- **Mekanism:** På Linux lägger det till `__attribute__((visibility("default")))`. På Windows med GCC/Clang lägger det till `__attribute__((dllexport))`.
- **Användning:** SDK:n tillämpar redan `SAMP_SDK_EXPORT` på alla livscykelfunktioner (`Load`, `Unload`, etc.), så deras export är helt automatisk för dessa kompilatorer. För dina anpassade funktioner gör du helt enkelt samma sak.

```cpp
// För GCC/Clang räcker det med att definiera funktionen med SAMP_SDK_EXPORT.
SAMP_SDK_EXPORT const char* SAMP_SDK_CALL GetPluginVersion() {
    return "1.0.0";
}
```

### 3.3. `Plugin_Public`: Intercepting Pawn Events

Makrot `Plugin_Public` är den primära bryggan för att ta emot Pawn callbacks i din C++-kod.

#### Syntax och Deklaration

- `Plugin_Public(PublicName, Type1 Param1, Type2 Param2, ...)`
- C++-funktionens namn som du deklarerar **måste vara detsamma** som Pawn-callbackens (t.ex. `OnPlayerConnect`).
- C++-parametertyperna (`int`, `float`, `std::string`) konverteras automatiskt av SDK:n.

```cpp
// Intercepts OnPlayerText(playerid, text[])
Plugin_Public(OnPlayerText, int playerid, std::string text) {
    Samp_SDK::Log("Spelare %d sade: %s", playerid, text.c_str());

    return PUBLIC_CONTINUE;
}
```

#### Automatisk Parameter-Marshalling

SDK:n hanterar automatiskt läsning från AMX `cell stack` och konvertering till de angivna C++-typerna:
- `int`: Konverteras direkt från `cell`.
- `float`: Konverteras från `cell` med `amx::AMX_CTOF`.
- `std::string`: SDK:n läser strängens adress i AMX, allokerar en `std::string` i C++ och kopierar innehållet.

#### Flödeskontroll: `PUBLIC_CONTINUE` vs `PUBLIC_STOP`

Värdet som returneras av din `Plugin_Public`-funktion är avgörande och bestämmer flödet av callback-exekveringen:
- `return PUBLIC_CONTINUE;` (värde `1`): Indikerar att callback-exekveringen ska **fortsätta**. Om det finns andra plugins som också interceptar denna callback, kommer de att anropas (i omvänd laddningsordning). Därefter kommer den ursprungliga `public`-funktionen i Pawn-skriptet att anropas.
- `return PUBLIC_STOP;` (värde `0`): Indikerar att callback-exekveringen ska **avbrytas**. Inga andra plugins (med lägre prioritet) eller den ursprungliga `public`-funktionen i Pawn-skriptet kommer att anropas för denna händelse. Detta är idealiskt för att implementera ett system som "skriver över" eller "blockerar" ett standardbeteende i SA-MP.

```cpp
// main.cpp
Plugin_Public(OnPlayerCommandText, int playerid, std::string cmdtext) {
    if (cmdtext == "/freeze") {
        Pawn_Native(TogglePlayerControllable, playerid, 0); // Fryser spelaren
        Pawn_Native(SendClientMessage, playerid, -1, Plugin_Format("Spelare %d frusen.", playerid));

        return PUBLIC_STOP; // Förhindrar att kommandot bearbetas av andra skript.
    }

    return PUBLIC_CONTINUE; // Tillåter att andra kommandon bearbetas.
}
```

#### Ghost Callbacks

En avancerad funktion i `Plugin_Public` är stödet för "Ghost Callbacks". Detta innebär att du kan intercepta en Pawn callback även om den **inte finns** i gamemodets eller filterscriptets `.amx`-skript. SDK:n "lurar" servern att anropa din C++-hook ändå. Detta är användbart för interna callbacks eller för att skapa ny funktionalitet utan att vara beroende av att en `public` finns i Pawn-skriptet.

```cpp
// Du kan definiera en callback som Pawn-skriptet inte har, men ditt plugin kommer att lyssna på den.
Plugin_Public(OnMyCustomInternalEvent, int data1, float data2) {
    Samp_SDK::Log("Anpassad intern händelse mottagen: %d, %.2f", data1, data2);

    return PUBLIC_CONTINUE;
}

// För att "trigga" denna händelse från en annan del av din C++-kod:
// Pawn_Public(OnMyCustomInternalEvent, 123, 45.67f);
// Anropet går till din Plugin_Public ovan, även om det inte finns någon OnMyCustomInternalEvent i Pawn.
```

### 3.4. `Plugin_Native`: Skapa Native-funktioner i C++

`Plugin_Native` låter dig utöka Pawn-funktionaliteten med högpresterande C++-kod.

#### Syntax och Fast Signatur

- `Plugin_Native(NativeName, AMX* amx, cell* params)`
- C++-funktionen måste ha exakt denna signatur: `cell NativeName(AMX* amx, cell* params)`.
- `NativeName` är namnet som Pawn-skripten kommer att använda.

```cpp
// Pawn: native GetPlayerPingAverage(playerid);
Plugin_Native(GetPlayerPingAverage, AMX* amx, cell* params) {
    // ... Implementering ...
    return 0;
}
```

#### Automatisk Registrering av Natives

> [!NOTE]
> Du **behöver inte** anropa `amx_Register` manuellt. SDK:n upptäcker alla dina `Plugin_Native`s (i vilken `.cpp`-fil som helst som har inkluderat `samp_sdk.hpp` och definierat `SAMP_SDK_WANT_AMX_EVENTS`) och registrerar dem automatiskt i varje laddat AMX-skript (`OnAmxLoad`).

#### Parameterutvinning: `Register_Parameters` vs. `Native_Params`

##### `Register_Parameters(...)`

- **Beskrivning:** Enklare hjälpfunktion för att extrahera flera parametrar sekventiellt.
- **Användning:** `Register_Parameters(variable1, variable2, ...)`
- **Begränsningar:** För input-parametrar. Hanterar inte valfria parametrar eller indexerad åtkomst.
- **Typer som stöds:** `int`, `float`, `std::string`.

```cpp
// Pawn: native SetPlayerSkinAndMoney(playerid, skinid, money);
Plugin_Native(SetPlayerSkinAndMoney, AMX* amx, cell* params) {
    int playerid, skinid, money;
    Register_Parameters(playerid, skinid, money); // Extraherar de 3 parametrarna
    
    Pawn_Native(SetPlayerSkin, playerid, skinid);
    Pawn_Native(GivePlayerMoney, playerid, money);
    
    return 1;
}
```

##### `Native_Params` (Full API: `Get`, `Get_REF`, `Set_REF`)

- **Beskrivning:** En wrapper-klass som tillhandahåller ett objektorienterat gränssnitt för att komma åt parametrarna för en native. Kraftfullare för komplexa scenarier.
- **Konstruktion:** `Native_Params p(amx, params);`

###### `p.Count()`

- **Beskrivning:** Returnerar antalet parametrar som skickats till nativen.
- **Användning:** Viktigt för att hantera valfria parametrar.

###### `p.Get<T>(size_t index)`

- **Beskrivning:** Extraherar en input-parameter via index och konverterar den till typen `T`.
- **Typer som stöds:** `int`, `float`, `std::string`.

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

- **Beskrivning:** Hämtar värdet av en **referensparameter** (Pawn-pekare) och lagrar det i `out_value`.
- **Användning:** För att läsa värden som har skickats med referens från Pawn.
- **Returvärde:** `true` om AMX-adressen är giltig, `false` annars.

```cpp
// Pawn: native CheckPlayerStats(playerid, &Float:health, &money);
Plugin_Native(CheckPlayerStats, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    
    int playerid = p.Get<int>(0);
    float health = 0.0f;
    int money = 0;

    // Hämtar värden från referenserna (Pawn skickade adresser)
    p.Get_REF(1, health); // Läser värdet av Float:health
    p.Get_REF(2, money);   // Läser värdet av money
    
    Samp_SDK::Log("Spelare %d, Hälsa: %.1f, Pengar: %d", playerid, health, money);
    
    // Nu, modifiera dem
    health = 50.0f;
    money += 100;
    
    // Och skriv tillbaka dem till Pawn-minnet
    p.Set_REF(1, health);
    p.Set_REF(2, money);
    
    return 1;
}
```

###### `p.Get_REF<T>(size_t index)` (C++17+)

- **Beskrivning:** Returnerar en `std::optional<T>` för att läsa en referensparameter. Säkrare för C++17 och senare.

###### `p.Set_REF<T>(size_t index, T value)`

- **Beskrivning:** Skriver ett värde `T` till en Pawn **referensparameter** (adressen som Pawn skickade).
- **Användning:** För att modifiera värden som skickats via referens, så att Pawn ser ändringen.
- **Returvärde:** `true` om skrivningen lyckades, `false` annars.

#### Returvärden

- Din `Plugin_Native`-funktion måste returnera en `cell`.
- För att returnera en `int` eller `bool`, använd en cast till `cell`.
- För att returnera en `float`, använd `amx::AMX_FTOC(my_float)`.

```cpp
// Returnerar en bool
Plugin_Native(IsPlayerSpawned, AMX* amx, cell* params) {
    int playerid;
    Register_Parameters(playerid);

    return (Pawn_Native(GetPlayerState, playerid) == PLAYER_STATE_SPAWNED) ? 1 : 0;
}

// Returnerar en float
Plugin_Native(GetPlayerMaxHealth, AMX* amx, cell* params) {
    return amx::AMX_FTOC(100.0f); // Returnerar 100.0f
}
```

### 3.5. `Plugin_Native_Hook`: Intercepting Existing SA-MP Natives

Makrot `Plugin_Native_Hook` låter dig intercepta och modifiera beteendet hos vilken befintlig SA-MP native-funktion som helst, eller från andra plugins. Detta är en kraftfull mekanism för att utöka eller ändra serverns standardlogik.

#### Syntax och Fast Signatur

- `Plugin_Native_Hook(NativeName, AMX* amx, cell* params)`
- C++-funktionen måste ha exakt denna signatur: `cell NativeName(AMX* amx, cell* params)`.
- `NativeName` måste vara det exakta namnet på nativen som du vill hooka (t.ex. `SendClientMessage`, `SetPlayerPos`).

```cpp
// Intercepts the SendClientMessage native
Plugin_Native_Hook(SendClientMessage, AMX* amx, cell* params) {
    // ...
    return Call_Original_Native(SendClientMessage); // Viktigt att anropa originalet
}
```

#### Registrering och Aktivering av Hook

> [!NOTE]
> Du **behöver inte** anropa `amx_Register` manuellt eller definiera `SAMP_SDK_WANT_AMX_EVENTS` specifikt för `Plugin_Native_Hook`. SDK:n upptäcker och registrerar automatiskt dina hooks. Vid den första exekveringen av ett AMX-skript ersätter SDK:n native-pekaren i tabellen med en "trampoline" som omdirigerar till din `Plugin_Native_Hook`-funktion. Denna process säkerställer säker kedjning av hooks från flera plugins.

#### Anropa Original Native (Hook-kedja): `Call_Original_Native`

Inom din `Plugin_Native_Hook`-funktion **MÅSTE** du använda makrot `Call_Original_Native(NativeName)` för att anropa den ursprungliga funktionen (eller nästa hook i kedjan). Detta är avgörande för att:
- **Bevara Funktionaliteten:** Om du inte anropar originalet kommer den hookade nativen helt enkelt att sluta fungera för andra plugins eller för servern.
- **Hook-kedjning:** Tillåter att flera plugins hookar samma native och att alla hooks exekveras i en sekvens.
- **Returvärdeshantering:** Du kan inspektera och till och med modifiera returvärdet från `Call_Original_Native` innan du returnerar det från din hook-funktion.

```cpp
// Exempel: Blockera SendClientMessage om det innehåller ett specifikt ord
Plugin_Native_Hook(SendClientMessage, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    
    // Extraherar parametrarna för analys
    int playerid = p.Get<int>(0);
    // int color = p.Get<int>(1); // Vi behöver inte färgen för denna logik
    std::string message = p.Get_String(2); // Hämtar meddelandesträngen

    if (message.find("BADWORD") != std::string::npos) {
        Samp_SDK::Log("MEDDELANDE BLOCKERAT för playerid %d: %s", playerid, message.c_str());

        return 0; // Returnerar 0 (false) till Pawn, vilket indikerar att meddelandet inte skickades.
                  // Och viktigast av allt, vi anropar INTE Call_Original_Native, vilket blockerar meddelandet.
    }

    // Om meddelandet inte innehåller det förbjudna ordet, anropar vi original native-funktionen
    // och returnerar dess värde, vilket säkerställer att meddelandet skickas normalt
    // och att andra hooks (om de finns) exekveras.
    return Call_Original_Native(SendClientMessage);
}
```

#### Fullständigt Exempel på `Plugin_Native_Hook`

```cpp
#define SAMP_SDK_IMPLEMENTATION
// SAMP_SDK_WANT_AMX_EVENTS är inte strikt nödvändigt för hooks, men är vanligt för att ha OnAmxLoad/Unload
// #define SAMP_SDK_WANT_AMX_EVENTS 
#include "samp-sdk/samp_sdk.hpp"

// Hook för CreateVehicle native
Plugin_Native_Hook(CreateVehicle, AMX* amx, cell* params) {
    Native_Params p(amx, params);

    // Extraherar parametrarna från CreateVehicle native för inspektion
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

    // Exempel på hur man *modifierar* en input-parameter
    // Om modellen är 400 (Landstalker), ändrar vi den till 401 (Bravura)
    if (modelid == 400) {
        // Vi modifierar direkt 'params'-arrayen för det ursprungliga anropet
        params[1] = static_cast<cell>(401); // Modellen är på position 0 i parameterarrayen (params[1])
        Samp_SDK::Log("  -> Modell 400 ändrad till 401 före skapandet.");
    }
    
    // Vi anropar den ursprungliga nativen (eller nästa hook i kedjan) med de eventuellt modifierade parametrarna
    cell original_retval = Call_Original_Native(CreateVehicle);

    Samp_SDK::Log("HOOK: CreateVehicle returned: %d (fordons-ID)", (int)original_retval);

    // Du kan modifiera returvärdet här innan du returnerar det till Pawn.
    // Exempel: om fordonet misslyckades med att skapas, returnera ett anpassat ogiltigt ID.
    if ((int)original_retval == INVALID_VEHICLE_ID) {
        Samp_SDK::Log("  -> Fordonskapande misslyckades i den ursprungliga nativen.");

        return -1; // Returnerar ett annat värde till Pawn.
    }

    return original_retval; // Returnerar det värde som original nativen returnerade (eller det ovan modifierade).
}

unsigned int GetSupportFlags() {
    return SUPPORTS_VERSION; 
}

// Minimala implementeringar för livscykeln
bool OnLoad() {
    Samp_SDK::Log("Exempelplugin för Native Hook laddat!");
    return true;
}

void OnUnload() {
    Samp_SDK::Log("Exempelplugin för Native Hook avlastat!");
}

// Dessa callbacks finns endast om SAMP_SDK_WANT_AMX_EVENTS är definierat
/*void OnAmxLoad(AMX* amx) {
    Samp_SDK::Log("AMX Load detected: %p", (void*)amx);
}

void OnAmxUnload(AMX* amx) {
    Samp_SDK::Log("AMX Unload detected: %p", (void*)amx);
}*/
```
> [!WARNING]
> Direkt manipulation av `cell* params`-arrayen för att ändra input-parametrar kräver försiktighet. Se till att du förstår ordningen och typen av parametrar. För de flesta användningsfall är `p.Get(...)` för att inspektera och `Call_Original_Native(...)` för att fortsätta kedjan tillräckligt. Direkt ändring av `params` bör endast göras om du vet att parametern är ett värde och behöver modifieras för det ursprungliga anropet. För strängar och arrayer är modifieringen mer komplex och involverar vanligtvis `amx::Set_String` för att skriva till den befintliga adressen eller omallokera, vilket kan vara lättare att hantera genom att anropa nativen via `Pawn_Native` med de nya värdena och returnera `0` från din hook för att avbryta det ursprungliga anropet.

### 3.6. `Pawn_*` Makron: Anropa Pawn-funktioner från C++

Dessa makron är motsatsen till `Plugin_Public` och `Plugin_Native`: de låter din C++-kod anropa Pawn-funktioner.

#### `Pawn_Native(NativeName, ...)`

- **Syfte:** Det rekommenderade sättet att anropa SA-MP native-funktioner (eller från andra plugins) från C++.
- **Mekanism:** Söker efter native-pekaren i SDK:ns interna cache (fylld av `Amx_Register_Detour`). Om den hittas, exekverar den nativen i en `Amx_Sandbox`-miljö (en falsk och isolerad AMX-instans).
- **Prestanda:** Den mest effektiva, eftersom den undviker den dyra sökningen efter `publics` och interagerar direkt med native-pekaren.

#### `Pawn_Public(PublicName, ...)`

- **Syfte:** Anropar en specifik public-funktion i ett Pawn-skript.
- **Mekanism:** Går igenom de `AMX*`-instanser som hanteras av `Amx_Manager`, söker efter `public`-funktionen med namnet och exekverar den.
- **Prestanda:** Mindre effektiv än `Pawn_Native` på grund av sökningen och det faktiska `amx_Exec`. Generellt sett är `publics` långsammare än `natives`.
- **Användning:** Idealisk för att anropa anpassade händelser i dina Gamemode/Filterscripts som inte är natives.

#### `Pawn(FunctionName, ...)`

- **Syfte:** Ett bekvämlighetsmakro som försöker gissa om funktionen är en native eller en public.
- **Mekanism:** Försöker först anropa som `Pawn_Native`. Om det misslyckas (nativen hittas inte), försöker den anropa som `Pawn_Public`.
- **Prestanda:** Kan vara något långsammare än `Pawn_Native` om funktionen är en native, på grund av det dubbla sökförsöket. För `publics` är prestandan densamma som `Pawn_Public`.
- **Användning:** För funktioner där du inte är säker på om de är natives eller publics, eller för att undvika det upprepande kodandet med att försöka den ena och sedan den andra.

#### Syntax och Konventioner

- **Funktionsnamn:** Använd alltid Pawn-funktionens namn **direkt, utan citattecken**. SDK:n konverterar det till en sträng internt.
- **Parametrar:** Skicka C++-parametrarna direkt.

```cpp
// Rätt:
Pawn_Native(SetPlayerPos, playerid, 100.0f, 200.0f, 300.0f); 

// Fel (men skulle tekniskt sett fungera på grund av hashen, undvik):
Pawn_Native("SetPlayerPos", playerid, 100.0f, 200.0f, 300.0f); 
```

#### Marshalling av Input-parametrar

SDK:n konverterar dina C++-typer till AMX:s `cell`-format och hanterar minnet efter behov:
- `int`, `bool`, `long`, `enum` -> `cell`
- `float`, `double` -> `cell` (med `amx::AMX_FTOC`)
- `const char*`, `std::string`, `std::string_view` (C++17+) -> `cell` (allokerar minne i AMX, kopierar strängen och skickar `amx_addr`-adressen)

```cpp
void Send_Formatted_Message(int playerid, const std::string& msg) {
    Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, msg);
}
```

#### Marshalling av Output-parametrar (Referenser: `int&`, `float&`, `std::string&`)

Detta är en nyckelfunktion för bekvämlighet och säkerhet. För Pawn-funktioner som förväntar sig en pekare (referens), automatiserar SDK:n hela processen med minnesallokering/-frisättning och datakopiering.

- **Hur man använder:** Skicka helt enkelt din variabel med referens (`&`).
- **Mekanism:** SDK:n allokerar minne på AMX-heapen, skickar AMX-adressen till Pawn-funktionen, väntar på att Pawn-funktionen fyller denna adress, läser tillbaka värdet och frigör AMX-minnet. Allt transparent.
- **Med `std::string&`:** SDK:n allokerar en standardbuffer (256 celler) i AMX för strängen.

```cpp
void Get_Player_Location(int playerid) {
    float x, y, z;
    int interiorid, worldid;
    std::string name;

    Pawn_Native(GetPlayerPos, playerid, x, y, z);
    Pawn_Native(GetPlayerInterior, playerid, interiorid);
    Pawn_Native(GetPlayerVirtualWorld, playerid, worldid);
    Pawn_Native(GetPlayerName, playerid, name, MAX_PLAYER_NAME);

    Samp_SDK::Log("Plats för %s (ID:%d): Pos(%.2f, %.2f, %.2f) Interiör:%d Värld:%d", name.c_str(), playerid, x, y, z, interiorid, worldid);
}
```

#### Objektet `Callback_Result`: Fullständig Analys

Alla `Pawn_*`-anrop returnerar ett `Callback_Result`-objekt. Detta objekt är en säker wrapper för resultatet av Pawn-anropet.

- `Callback_Result() noexcept`: Standardkonstruktor, indikerar misslyckande (`success_ = false`).
- `Callback_Result(bool success, cell value) noexcept`: Konstruktor för framgång eller misslyckande med värde.
- `explicit operator bool() const`: Tillåter att använda `if (result)` för att kontrollera om anropet lyckades.
- `operator cell() const`: Tillåter att konvertera resultatet till `cell` för att få värdet.
- `float As_Float() const`: Bekvämlighetsfunktion för att få resultatet som `float`.
- `cell Value() const`: Returnerar det råa `cell`-värdet.
- `bool Success() const`: Returnerar `true` om Pawn-anropet lyckades.
- `int Get_Amx_Error() const`: Returnerar AMX-felkoden om anropet misslyckades (0 för framgång).

```cpp
// Exempel: Hämta en spelares hälsa.
// Nativen GetPlayerHealth(playerid, &Float:health) förväntar sig ett playerid och en referens till hälsan.
int playerid = 0; // Exempel på spelar-ID
float player_health = 0.0f;

// Vi anropar GetPlayerHealth och skickar playerid och player_health via referens.
// SDK:n tar hand om marshalling för output-parametern 'health'.
Callback_Result result = Pawn_Native(GetPlayerHealth, playerid, player_health);

if (result) { // Kontrollerar om anropet lyckades (operator bool)
    // Värdet som returneras av result.As_Float() eller result (operator cell)
    // skulle vara native-funktionens *returvärde*, inte output-parametern.
    // Hälsovärdet har redan uppdaterats i 'player_health' på grund av marshalling av output-parametern.
    Samp_SDK::Log("Spelare %d har %.1f hälsa.", playerid, player_health);
}
else {
    // Anropet misslyckades, kanske spelaren inte finns eller nativen hittades inte.
    Samp_SDK::Log("Fel vid hämtning av spelare %d:s hälsa. AMX-kod: %d", playerid, result.Get_Amx_Error());
}

// För natives som returnerar ett värde och använder output-parametrar (mindre vanligt, men möjligt),
// skulle du använda båda:
// Callback_Result other_result = Pawn_Native(SomeNative, param1, output_param, param2);
// if (other_result) {
//     cell returned_value = other_result;
//     // output_param är redan uppdaterad
// }
```

### 3.7. `Plugin_Module`: Hantering av Dynamiska Moduler

Makrot `Plugin_Module` tillåter ditt plugin att fungera som en "laddare" för andra plugins, vilket skapar en modulär och utbyggbar arkitektur. En modul som laddas på detta sätt behandlas som ett förstklassigt plugin, med sin egen livscykel av händelser som hanteras av värd-pluginet.

#### Syntax och Syfte

- `Plugin_Module(const char* base_filename, const char* module_directory, const char* optional_success_message)`
- `base_filename`: Basnamnet på modulfilen, **utan filändelse** (t.ex. för `my_module.dll` eller `my_module.so`, använd `"my_module"`). SDK:n lägger automatiskt till lämplig filändelse (`.dll` eller `.so`).
- `module_directory`: Sökvägen till katalogen där modulfilen finns (t.ex. `"plugins/my_custom_modules"`). **Inkludera inte filnamnet här.** SDK:n kommer att sammanfoga hela sökvägen (`module_directory/base_filename.ext`).
- `optional_success_message`: Ett valfritt meddelande som ska loggas i serverkonsolen om modulen laddas framgångsrikt.

```cpp
// main.cpp, inom OnLoad()

// Laddar modulen 'core_logic.dll' (eller 'core_logic.so')
// som finns i serverns 'modules/custom/'-mapp.
if (!Plugin_Module("core_logic", "modules/custom", "Core Logic-modulen laddad framgångsrikt!"))
    return (Samp_SDK::Log("FATALT FEL: Kunde inte ladda modulen 'core_logic'!"), false);

// Laddar modulen 'admin_system.dll' (eller 'admin_system.so')
// som finns direkt i serverns 'plugins/'-mapp.
if (!Plugin_Module("admin_system", "plugins", "Administrationsmodulen aktiverad."))
    Samp_SDK::Log("VARNING: Administrationsmodulen kunde inte laddas.");
```

#### En Moduls Livscykel

En modul måste exportera funktionerna `Load`, `Unload` och `Supports`, precis som ett vanligt plugin. SDK:n hanterar modulens livscykel på följande sätt:

- **Laddning:** När `Plugin_Module` anropas, gör SDK:n följande:
   1. Konstruerar den fullständiga filsökvägen (t.ex. `modules/custom/core_logic.dll`).
   2. Använder `Dynamic_Library` (`LoadLibrary`/`dlopen`) för att ladda binärfilen.
   3. **Hämtar pekare till ALLA modulens livscykelfunktioner:**
      - **Obligatoriska:** `Load`, `Unload`, `Supports`. Om någon saknas, misslyckas modulladdningen.
      - **Valfria:** `AmxLoad`, `AmxUnload`, `ProcessTick`.
   4. Anropar modulens `Load`-funktion och skickar `ppData` från huvudpluginet.
   5. Om `Load` returnerar `true`, läggs modulen till den interna listan över laddade moduler.

- **Vidarebefordran av händelser:** Värd-pluginet **vidarebefordrar automatiskt** händelserna till alla laddade moduler.
 > [!IMPORTANT]
 > För att händelserna ska vidarebefordras korrekt måste **värd-pluginet** (det som anropar `Plugin_Module`) vara konfigurerat för att ta emot dessa händelser.
 > - För att `AmxLoad` och `AmxUnload` ska fungera i modulerna måste värd-pluginet definiera makrot `SAMP_SDK_WANT_AMX_EVENTS`.
 > - För att `ProcessTick` ska fungera i modulerna måste värd-pluginet definiera makrot `SAMP_SDK_WANT_PROCESS_TICK`.

- **Avlastning:** Under `OnUnload` av ditt huvudplugin, avlastar SDK:n alla moduler som laddats via `Plugin_Module`. Detta görs i **omvänd ordning** från laddningen (den sist laddade avlastas först), vilket är avgörande för att hantera beroenden och säkerställa korrekt frigörande av resurser.

#### Fördelar med Modularisering

- **Kodorganisation:** Dela upp stora plugins i mindre, hanterbara komponenter, var och en i sin egen modulfil.
- **Återanvändbarhet:** Skapa generiska moduler (t.ex. en databasmodul, en avancerad loggsystemmodul) som kan användas av olika plugins, vilket främjar kodåteranvändning.
- **Oberoende Komponenter:** Skapa moduler som är **helt händelsestyrda och oberoende**. En modul kan ha sina egna `Plugin_Native`s, intercepta `Plugin_Public`s och ha sin egen `OnProcessTick`-logik, som fungerar som ett autonomt plugin men laddas av en värd.
- **Dynamiska Uppdateringar:** I kontrollerade scenarier möjliggör det uppdatering av delar av ditt system (genom att ersätta en modul `.dll` eller `.so`) utan att behöva kompilera om och starta om huvudpluginet eller hela servern (även om detta kräver noggrann versions- och kompatibilitetshantering).

### 3.8. `Plugin_Call`: Anropa Pluginets Interna Natives

Använd `Plugin_Call` för att anropa en `Plugin_Native` definierad **inom ditt eget plugin**.

#### Syntax och Prestandafördelar

- `Plugin_Call(NativeName, Param1, Param2, ...)`
- **Fördel:** Undviker överhänget med att söka efter nativen i AMX:s native-array. SDK:n upprätthåller en direkt mappning från namn-hashes till funktionspekare för sina egna natives, vilket gör detta till det snabbaste sättet att anropa dem internt.
- **Kräver:** `SAMP_SDK_WANT_AMX_EVENTS`.

```cpp
// main.cpp
Plugin_Native(InternalCheckPlayerLevel, AMX* amx, cell* params) {
    int playerid;
    Register_Parameters(playerid);

    // Logik för att kontrollera nivån
    return (playerid % 2 == 0) ? 1 : 0; // Exempel: jämn nivå för jämna ID:n
}

void Check_All_Players_Level() {
    for (int i = 0; i < MAX_PLAYERS; ++i) {
        if (Pawn_Native(IsPlayerConnected, i)) {
            if (Plugin_Call(InternalCheckPlayerLevel, i)) // Anropar din egen native
                Samp_SDK::Log("Spelare %d har en hög nivå!", i);
        }
    }
}
```

### 3.9. SDK Verktygsfunktioner

#### `Samp_SDK::Log(const char* format, ...)`

- **Beskrivning:** Skriver ut meddelanden till serverkonsolen och till filen `server_log.txt`. En säker wrapper för `logprintf`.
- **Användning:** För felsökning, statusmeddelanden och fel.
- **Mekanism:** Internt hämtar SDK:n pekaren till `logprintf` via `ppData[PLUGIN_DATA_LOGPRINTF]`. Funktionen hanterar strängformateringen på ett säkert sätt.

```cpp
// Var som helst i ditt plugin
Samp_SDK::Log("Pluginet har initialiserats med värde %d och strängen '%s'.", 123, "test");
```

#### `std::string Plugin_Format(const char* format, ...)` (Rekommenderas)

- **Beskrivning:** Formaterar en sträng på ett säkert sätt (liknande `sprintf`) och returnerar en `std::string`. Detta är det **rekommenderade och mest idiomatiska** sättet att formatera strängar för användning inom ditt plugin.
- **Användning:** Idealisk för att konstruera formaterade meddelanden innan de skickas till `Samp_SDK::Log`, `Pawn_Native(SendClientMessage, ...)`, eller för något annat strängbehov inom din C++-kod.
- **Mekanism:** Internt är `Plugin_Format` ett makro som anropar `Samp_SDK::Format`. Den använder `vsnprintf` för att bestämma den exakta storleken på den formaterade strängen och allokerar en `std::string` med tillräcklig kapacitet, vilket förhindrar buffertöverskridanden.

```cpp
int playerid = 0; // Exempel på ID
int health = 50;
Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, Plugin_Format("Spelare %d, din nuvarande hälsa är %d.", playerid, health));

// Kan även användas för interna loggar
Samp_SDK::Log(Plugin_Format("DEBUG: Bearbetar status för ID %d", playerid));
```

#### `std::string Samp_SDK::Format(const char* format, ...)` (Implementeringsdetalj)

- **Beskrivning:** Den underliggande implementeringsfunktionen för strängformatering, belägen inom `Samp_SDK`-namnrymden.
- **Användning:** Kallas vanligtvis inte direkt av användaren. Makrot `Plugin_Format` tillhandahålls som en bekvämlighet för denna funktion, i linje med namngivningskonventionen för andra SDK-makron (`Plugin_Public`, `Plugin_Native`). Du skulle endast anropa den direkt om du ville undvika makrot `Plugin_Format` av någon specifik anledning.

```cpp
// Exempel på hur Samp_SDK::Format fungerar, men föredra Plugin_Format
std::string raw_status = Samp_SDK::Format("Endast för internt bruk: %d.", 42);
```

#### `std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`

- **Beskrivning:** Konverterar en AMX-strängadress (`cell amx_addr`) till en C++ `std::string`.
- **Användning:** Främst inom `Plugin_Native` och `Plugin_Native_Hook` när du behöver komma åt strängar som inte automatiskt konverteras av `Register_Parameters` eller `Native_Params` (t.ex. om Pawn-parametern är en `const` `string` och inte har deklarerats som `std::string` i din `Plugin_Native` eller `Plugin_Public` för automatisk Marshalling).

```cpp
Plugin_Native(PrintRawAmxString, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    cell amx_string_addr = p.Get<cell>(0); // Hämtar strängadressen i AMX

    std::string cpp_string = Samp_SDK::Get_String(amx, amx_string_addr);
    Samp_SDK::Log("Sträng från AMX: %s", cpp_string.c_str());

    return 1;
}
```

## 4. Kompilering och Deploy

### Krav på Arkitektur och Plattform

- Ditt plugin **MÅSTE** kompileras för arkitekturen **x86 (32-bit)**.
- Plattformar som stöds: Windows (.dll) och Linux (.so).

### Exempel på Kompileringskommandon

#### **MSVC (Visual Studio)**

1. Skapa ett nytt projekt av typen "Dynamic-Link Library (DLL)".
2. I projektinställningarna, ställ in "Lösningsplattform" till **x86**.
3. Se till att C++ Language Standard är minst C++17.

#### **GCC / Clang (Linux)**

```bash
# För ett plugin som heter 'my_plugin.so' från 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -fPIC -Wall -Wextra -Wl,--no-undefined main.cpp -o my_plugin.so
```
- `-m32`: Kompilerar för 32-bit.
- `-shared`: Skapar ett delat bibliotek (`.so`).
- `-std=c++17`: Anger C++-standarden som C++17 (kan vara `c++20`, men C++17 är minimum).
- `-O2`: Optimeringsnivå 2.
- `-fPIC`: Genererar positionsberoende kod, nödvändigt för delade bibliotek.
- `-Wall -Wextra`: Aktiverar ytterligare varningar för att hjälpa till att hitta fel.
- `-Wl,--no-undefined`: Förhindrar att biblioteket skapas om det finns odefinierade symboler.

#### **GCC / Clang (MinGW på Windows)**

```bash
# För ett plugin som heter 'my_plugin.dll' från 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -static-libstdc++ -static-libgcc -Wl,--no-undefined main.cpp -o my_plugin.dll
```
- `-static-libstdc++`: Länkar standard C++-biblioteket statiskt. Viktigt för att undvika att ditt plugin är beroende av specifika kompilator-runtime DLL:er som kanske inte finns på användarens system.
- `-static-libgcc`: Länkar GCC-biblioteket statiskt.

### Överväganden för Distribution

- **Filnamn:** Ditt plugin ska ha filändelsen `.dll` (Windows) eller `.so` (Linux). Ex: `my_plugin.dll`.
- **Plats:** Placera den kompilerade filen i din SA-MP-servers `plugins/`-mapp.
- **server.cfg:** Lägg till namnet på ditt plugin (om Windows, utan filändelsen) till raden `plugins` i `server.cfg`.
   ```
   plugins my_plugin (om Linux, my_plugin.so)
   ```

## Licens

Copyright © **AlderGrounds**

Denna programvara är licensierad under villkoren i MIT-licensen ("Licensen"); du får använda denna programvara i enlighet med Licensens villkor. En kopia av Licensen kan erhållas på: [MIT License](https://opensource.org/licenses/MIT)

### Användarvillkor

#### 1. Beviljade rättigheter

Denna licens ger kostnadsfritt följande rättigheter till alla som erhåller en kopia av denna programvara och tillhörande dokumentationsfiler:
* Att använda, kopiera, modifiera, slå samman, publicera, distribuera, underlicensiera och/eller sälja kopior av programvaran utan begränsningar
* Att tillåta personer som programvaran tillhandahålls till att göra detsamma, under förutsättning att de följer nedanstående villkor

#### 2. Obligatoriska villkor

Alla kopior eller väsentliga delar av programvaran måste innehålla:
* Ovanstående upphovsrättsmeddelande
* Detta tillståndsmeddelande
* Nedanstående ansvarsfriskrivning

#### 3. Upphovsrätt

Programvaran och all tillhörande dokumentation skyddas av upphovsrättslagar. **AlderGrounds** behåller den ursprungliga upphovsrätten till programvaran.

#### 4. Garantifriskrivning och ansvarsbegränsning

PROGRAMVARAN TILLHANDAHÅLLS "I BEFINTLIGT SKICK", UTAN NÅGON GARANTI AV NÅGOT SLAG, UTTRYCKLIG ELLER UNDERFÖRSTÅDD, INKLUSIVE MEN INTE BEGRÄNSAT TILL GARANTIER FÖR SÄLJBARHET, LÄMPLIGHET FÖR ETT SÄRSKILT SYFTE OCH ICKE-INTRÅNG.

UNDER INGA OMSTÄNDIGHETER SKA FÖRFATTARNA ELLER UPPHOVSRÄTTSINNEHAVARNA VARA ANSVARIGA FÖR NÅGRA ANSPRÅK, SKADOR ELLER ANNAT ANSVAR, VARE SIG I EN AVTALSHANDLING, SKADESTÅNDSANSPRÅK ELLER PÅ ANNAT SÄTT, SOM UPPSTÅR FRÅN, UT ELLER I SAMBAND MED PROGRAMVARAN ELLER ANVÄNDNINGEN ELLER ANNAT HANDHAVANDE AV PROGRAMVARAN.

---

För detaljerad information om MIT-licensen, besök: https://opensource.org/licenses/MIT