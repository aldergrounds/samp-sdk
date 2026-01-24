# SA-MP SDK

<div align="center">

![C++](https://img.shields.io/badge/C%2B%2B-17%2B-00599C?style=for-the-badge&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-blue?style=for-the-badge&logo=windows&logoColor=white)
![Architecture](https://img.shields.io/badge/Architecture-x86%20(32--bit)-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**Ein modernes, Header-Only und High-Level C++ SDK für die Entwicklung von Plugins und Modulen für SA-MP.**

</div>

## Sprachen

- Português: [README](../../)
- English: [README](../English/README.md)
- Español: [README](../Espanol/README.md)
- Français: [README](../Francais/README.md)
- Italiano: [README](../Italiano/README.md)
- Polski: [README](../Polski/README.md)
- Русский: [README](../Русский/README.md)
- Svenska: [README](../Svenska/README.md)
- Türkçe: [README](../Turkce/README.md)

## Inhaltsverzeichnis

- [SA-MP SDK](#sa-mp-sdk)
  - [Sprachen](#sprachen)
  - [Inhaltsverzeichnis](#inhaltsverzeichnis)
  - [1. Einführung und Designphilosophie](#1-einführung-und-designphilosophie)
    - [Das Problem mit der Standard C API von SA-MP](#das-problem-mit-der-standard-c-api-von-sa-mp)
    - [Die Lösung des SA-MP SDK: Abstraktion mit Sicherheit und Performance](#die-lösung-des-sa-mp-sdk-abstraktion-mit-sicherheit-und-performance)
    - [Header-Only Modell: Vorteile und Implikationen](#header-only-modell-vorteile-und-implikationen)
  - [2. Konfiguration und Umgebung](#2-konfiguration-und-umgebung)
    - [Kompilierungsanforderungen](#kompilierungsanforderungen)
    - [Empfohlene Dateistruktur](#empfohlene-dateistruktur)
    - [Wesentliche Konfigurationsmakros](#wesentliche-konfigurationsmakros)
      - [`SAMP_SDK_IMPLEMENTATION`](#samp_sdk_implementation)
      - [`SAMP_SDK_WANT_AMX_EVENTS`](#samp_sdk_want_amx_events)
      - [`SAMP_SDK_WANT_PROCESS_TICK`](#samp_sdk_want_process_tick)
    - [SA-MP Definitionen und Konstanten (`samp_defs.hpp`)](#sa-mp-definitionen-und-konstanten-samp_defshpp)
  - [3. Umfassende API-Nutzungsanleitung](#3-umfassende-api-nutzungsanleitung)
    - [3.1. Der Plugin-Lebenszyklus](#31-der-plugin-lebenszyklus)
      - [`bool OnLoad()`](#bool-onload)
      - [`void OnUnload()`](#void-onunload)
      - [`unsigned int GetSupportFlags()`](#unsigned-int-getsupportflags)
      - [`void OnAmxLoad(AMX* amx)`](#void-onamxloadamx-amx)
      - [`void OnAmxUnload(AMX* amx)`](#void-onamxunloadamx-amx)
      - [`void OnProcessTick()`](#void-onprocesstick)
    - [3.2. Exportieren von Plugin-Funktionen](#32-exportieren-von-plugin-funktionen)
      - [Export für MSVC (Visual Studio) mit `Export_Plugin`](#export-für-msvc-visual-studio-mit-export_plugin)
      - [Export für GCC / Clang mit `SAMP_SDK_EXPORT`](#export-für-gcc--clang-mit-samp_sdk_export)
    - [3.3. `Plugin_Public`: Abfangen von Pawn-Events](#33-plugin_public-abfangen-von-pawn-events)
      - [Syntax und Deklaration](#syntax-und-deklaration)
      - [Automatische Parameter-Marshalling](#automatische-parameter-marshalling)
      - [Flusskontrolle: `PUBLIC_CONTINUE` vs `PUBLIC_STOP`](#flusskontrolle-public_continue-vs-public_stop)
      - [Ghost Callbacks](#ghost-callbacks)
    - [3.4. `Plugin_Native`: Erstellen von nativen C++-Funktionen](#34-plugin_native-erstellen-von-nativen-c-funktionen)
      - [Syntax und feste Signatur](#syntax-und-feste-signatur)
      - [Automatische Native-Registrierung](#automatische-native-registrierung)
      - [Parameter-Extraktion: `Register_Parameters` vs. `Native_Params`](#parameter-extraktion-register_parameters-vs-native_params)
        - [`Register_Parameters(...)`](#register_parameters)
        - [`Native_Params` (Vollständige API: `Get`, `Get_REF`, `Set_REF`)](#native_params-vollständige-api-get-get_ref-set_ref)
          - [`p.Count()`](#pcount)
          - [`p.Get<T>(size_t index)`](#pgettsize_t-index)
          - [`p.Get_REF<T>(size_t index, T& out_value)`](#pget_reftsize_t-index-t-out_value)
          - [`p.Get_REF<T>(size_t index)` (C++17+)](#pget_reftsize_t-index-c17)
          - [`p.Set_REF<T>(size_t index, T value)`](#pset_reftsize_t-index-t-value)
      - [Rückgabewerte](#rückgabewerte)
    - [3.5. `Plugin_Native_Hook`: Abfangen von vorhandenen SA-MP-Natives](#35-plugin_native_hook-abfangen-von-vorhandenen-sa-mp-natives)
      - [Syntax und feste Signatur](#syntax-und-feste-signatur-1)
      - [Hook-Registrierung und -Aktivierung](#hook-registrierung-und--aktivierung)
      - [Aufruf der originalen Native (Hook-Kette): `Call_Original_Native`](#aufruf-der-originalen-native-hook-kette-call_original_native)
      - [Vollständiges Beispiel für `Plugin_Native_Hook`](#vollständiges-beispiel-für-plugin_native_hook)
    - [3.6. `Pawn_*` Makros: Aufrufen von Pawn-Funktionen aus C++](#36-pawn_-makros-aufrufen-von-pawn-funktionen-aus-c)
      - [`Pawn_Native(NativeName, ...)`](#pawn_nativenativename-)
      - [`Pawn_Public(PublicName, ...)`](#pawn_publicpublicname-)
      - [`Pawn(FunctionName, ...)`](#pawnfunctionname-)
      - [Syntax und Konventionen](#syntax-und-konventionen)
      - [Marshalling von Eingabeparametern](#marshalling-von-eingabeparametern)
      - [Marshalling von Ausgabeparametern (Referenzen: `int&`, `float&`, `std::string&`)](#marshalling-von-ausgabeparametern-referenzen-int-float-stdstring)
      - [Das `Callback_Result`-Objekt: Vollständige Analyse](#das-callback_result-objekt-vollständige-analyse)
    - [3.7. `Plugin_Module`: Dynamische Modulverwaltung](#37-plugin_module-dynamische-modulverwaltung)
      - [Syntax und Zweck](#syntax-und-zweck)
      - [Lebenszyklus eines Moduls](#lebenszyklus-eines-moduls)
      - [Vorteile der Modularisierung](#vorteile-der-modularisierung)
    - [3.8. `Plugin_Call`: Aufrufen interner Plugin-Natives](#38-plugin_call-aufrufen-interner-plugin-natives)
      - [Syntax und Performance-Vorteile](#syntax-und-performance-vorteile)
    - [3.9. SDK-Utility-Funktionen](#39-sdk-utility-funktionen)
      - [`Samp_SDK::Log(const char* format, ...)`](#samp_sdklogconst-char-format-)
      - [`std::string Plugin_Format(const char* format, ...)` (Empfohlen)](#stdstring-plugin_formatconst-char-format--empfohlen)
      - [`std::string Samp_SDK::Format(const char* format, ...)` (Implementierungsdetail)](#stdstring-samp_sdkformatconst-char-format--implementierungsdetail)
      - [`std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`](#stdstring-samp_sdkget_stringamx-amx-cell-amx_addr)
  - [4. Kompilierung und Bereitstellung](#4-kompilierung-und-bereitstellung)
    - [Architektur- und Plattformanforderungen](#architektur--und-plattformanforderungen)
    - [Beispiele für Kompilierungsbefehle](#beispiele-für-kompilierungsbefehle)
      - [**MSVC (Visual Studio)**](#msvc-visual-studio)
      - [**GCC / Clang (Linux)**](#gcc--clang-linux)
      - [**GCC / Clang (MinGW unter Windows)**](#gcc--clang-mingw-unter-windows)
    - [Überlegungen zur Verteilung](#überlegungen-zur-verteilung)
  - [Lizenz](#lizenz)
    - [Nutzungsbedingungen](#nutzungsbedingungen)
      - [1. Gewährte Berechtigungen](#1-gewährte-berechtigungen)
      - [2. Verpflichtende Bedingungen](#2-verpflichtende-bedingungen)
      - [3. Urheberrecht](#3-urheberrecht)
      - [4. Gewährleistungsausschluss und Haftungsbeschränkung](#4-gewährleistungsausschluss-und-haftungsbeschränkung)

## 1. Einführung und Designphilosophie

### Das Problem mit der Standard C API von SA-MP

Die SA-MP Plugin API ist eine C-Programmierschnittstelle. Obwohl funktional und fundamental, stellt sie die Herausforderungen der Low-Level-Programmierung dar:
- **Manuelle Speicherverwaltung:** Funktionen wie `amx_Allot` und `amx_Release` erfordern, dass der Entwickler den Speicher im AMX-Heap explizit zuweist und freigibt. Dies ist eine häufige Ursache für Speicherlecks und Laufzeitfehler.
- **Schwache Typisierung und manuelle Konvertierungen:** Parameter werden als `cell`-Array übergeben, was explizite (und oft unsichere) Konvertierungen zwischen `cell`, `int`, `float` und `char*` erzwingt.
- **Redundanz und Boilerplate:** Das Extrahieren mehrerer Parameter aus einem `cell* params`-Array, das Verwalten von Stringlängen und das Verwalten des AMX-Stacks für C++ zu Pawn-Rückrufen erfordert sich wiederholenden Code.
- **Fragilität der Schnittstelle:** Das Fehlen einer Kompilierzeitprüfung (Typsicherheit) bedeutet, dass Fehler bei der Parameterübergabe oder bei Typen bis zur Ausführung unbemerkt bleiben können, was zu Abstürzen oder undefiniertem Verhalten führt.

### Die Lösung des SA-MP SDK: Abstraktion mit Sicherheit und Performance

Das SA-MP SDK begegnet diesen Problemen, indem es eine leistungsstarke Abstraktionsebene in C++ bereitstellt:
- **RAII (Resource Acquisition Is Initialization):** Automatische Speicherverwaltung in der AMX. `Amx_Scoped_Memory` stellt sicher, dass der zugewiesene Speicher freigegeben wird.
- **Typsicherheit:** Automatische und sichere Konvertierung von Parametern zwischen C++ und Pawn. Sie arbeiten direkt mit `int`, `float`, `std::string`.
- **Prägnante und idiomatisches Syntax:** Makros und Templates bieten eine saubere API, die dem modernen C++ ähnlicher ist als der traditionellen C-API.
- **Robuste Abfangung:** Ein fortschrittlicher Hooking-Engine ermöglicht das transparente Abfangen von Pawn-Rückrufen (`Plugin_Public`), die Erstellung neuer Natives (`Plugin_Native`) und **das Hooking und Verkettung von vorhandenen SA-MP Natives (`Plugin_Native_Hook`)**.
- **Hohe Performance:** Umfangreiche Nutzung von Kompilierzeit-Hashing (FNV1a), Funktions-Caching und `thread_local`-Optimierungen, um den Overhead der Abstraktionen zu minimieren.

### Header-Only Modell: Vorteile und Implikationen

Das SDK besteht ausschließlich aus Header-Dateien (`.hpp`, `.h`).
- **Vorteile:**
   - **Vereinfachte Integration:** Es gibt keine Bibliotheken zum Erstellen, Verknüpfen oder Verteilen. Einfach die Header einbinden.
   - **Compileroptimierungen:** Der Compiler hat vollständigen Einblick in den SDK-Code und Ihr Plugin, was aggressives Inlining und Link-Time-Optimierungen ermöglicht, was zu schnelleren Binärdateien führen kann.
- **Implikationen:**
   - **Kompilierzeit:** Bei sehr großen Projekten kann die Kompilierung aufgrund der wiederholten Einbindung des SDK-Codes länger dauern. Dies wird durch Include-Guards und die "include nur das, was nötig ist"-Natur von C++ gemildert.
   - **Implementierungsmakros:** Die Notwendigkeit des Makros `SAMP_SDK_IMPLEMENTATION` ist eine Folge des Header-Only-Modells, um Symbol-Neudefinitionen zu vermeiden.

## 2. Konfiguration und Umgebung

### Kompilierungsanforderungen

- **C++-Compiler:** Kompatibel mit C++17 oder höher.
   - GCC (Version 8+)
   - Clang (Version 5+)
   - MSVC (Visual Studio 2017+)
- **Architektur:** **x86 (32-bit)**. SA-MP läuft ausschließlich auf dieser Architektur. Das SDK enthält Überprüfungen in `platform.hpp`, die Kompilierungsfehler auslösen, wenn die falsche Architektur erkannt wird.
- **Betriebssystem:** Windows oder Linux.

### Empfohlene Dateistruktur

Zur Klarheit und Organisation ist es üblich, das SDK in einem Unterordner `samp-sdk` zu organisieren.

```
my_plugin/
├── samp-sdk/
│   ├── // Other SDK files
│   └── samp_sdk.hpp // The main header to include
│
├── src/
│   ├── main.cpp // Where SAMP_SDK_IMPLEMENTATION is defined
│   └── my_custom_logic.cpp // Optional, to organize code
│
└── CMakeLists.txt (or .vcxproj, Makefile)
```

### Wesentliche Konfigurationsmakros

Definieren Sie diese Makros immer *bevor* Sie `samp_sdk.hpp` inkludieren.

#### `SAMP_SDK_IMPLEMENTATION`

- **Zweck:** Signalisiert dem Compiler, dass diese `.cpp`-Datei die Implementierungen der Plugin-Exportfunktionen (`Supports`, `Load`, `Unload`, `AmxLoad`, `AmxUnload`, `ProcessTick`) generieren soll. **Das SDK übernimmt das automatische Exportieren dieser Funktionen, wodurch die Notwendigkeit von `.def`-Dateien (unter Windows) oder `__attribute__((visibility("default")))`-Deklarationen (unter Linux) für diese Funktionen entfällt.**
- **Technischer Einfluss:** Ohne dieses Makro findet der Linker die erforderlichen Exporte nicht, und der SA-MP-Server kann Ihr Plugin nicht laden.
- **Grundregel:** **Definieren Sie dieses Makro in NUR EINER `.cpp`-Datei in Ihrem gesamten Projekt.** Das Definieren in mehreren Dateien führt zu einem "duplizierten Symbol"-Linkerfehler.

```cpp
// main.cpp
#define SAMP_SDK_IMPLEMENTATION // The macro makes the SDK export the necessary functions automatically.
#include "samp-sdk/samp_sdk.hpp"

// ... your plugin code ...
```

#### `SAMP_SDK_WANT_AMX_EVENTS`

- **Zweck:** Aktiviert die Pawn-Script-Lebenszyklus-Callbacks (`OnAmxLoad`, `OnAmxUnload`) und die Funktionalität, neue Natives in C++ zu erstellen (`Plugin_Native`).
- **Aktivierte Funktionalitäten:**
   - Callbacks `OnAmxLoad(AMX* amx)` und `OnAmxUnload(AMX* amx)`.
   - Deklaration und Registrierung neuer C++-Natives mit `Plugin_Native`.
   - Das Makro `Plugin_Call` zum Aufrufen von mit `Plugin_Native` erstellten Natives innerhalb Ihres eigenen Plugins.
- **Technischer Einfluss:** Wenn dieses Makro definiert ist, sammelt das SDK automatisch alle Ihre `Plugin_Native`s. In der Funktion `Supports()` wird das Flag `SUPPORTS_AMX_NATIVES` automatisch hinzugefügt, wenn in Ihrem Projekt `Plugin_Native`s vorhanden sind.
- **Flexibilität:** **Sie können dieses Makro in mehreren `.cpp`-Dateien definieren.** Das statische Registrierungssystem des SDK konsolidiert alle Natives aus verschiedenen Kompilierungseinheiten in einer einzigen globalen Liste.

```cpp
// my_natives.cpp (can be a separate file from main.cpp)
#define SAMP_SDK_WANT_AMX_EVENTS // Only to enable Plugin_Native and the OnAmxLoad/OnAmxUnload callbacks
#include "samp-sdk/samp_sdk.hpp"

Plugin_Native(MyCustomNative, AMX* amx, cell* params) {
    // ...
    return 0;
}
```

#### `SAMP_SDK_WANT_PROCESS_TICK`

- **Zweck:** Aktiviert den Callback `OnProcessTick()`, der regelmäßig vom Server aufgerufen wird.
- **Technischer Einfluss:** Fügt das Flag `SUPPORTS_PROCESS_TICK` automatisch der Funktion `Supports()` hinzu.

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

### SA-MP Definitionen und Konstanten (`samp_defs.hpp`)

Diese Datei stellt alle bekannten SA-MP-Konstanten und -Grenzwerte bereit, wie z.B. `MAX_PLAYERS`, `INVALID_PLAYER_ID`, `PLAYER_STATE_ONFOOT`, `WEAPON_DEAGLE`, `DIALOG_STYLE_LIST` usw. Sie wird automatisch von `samp_sdk.hpp` eingebunden und sollte verwendet werden, um die Kompatibilität und Lesbarkeit des Codes zu gewährleisten.

## 3. Umfassende API-Nutzungsanleitung

### 3.1. Der Plugin-Lebenszyklus

Die folgenden Funktionen sind die Einstiegs- und Ausstiegspunkte Ihres Plugins, die vom SDK automatisch exportiert werden.

#### `bool OnLoad()`

- **Beschreibung:** Erste Funktion, die vom SA-MP-Server nach erfolgreichem Laden Ihres Plugins in den Speicher aufgerufen wird.
- **Verwendung:** Ideal zum Initialisieren von Systemen, Laden von Konfigurationen, Öffnen von Datenbankverbindungen oder Laden von Modulen (`Plugin_Module`).
- **Rückgabe:**
   - `true`: Das Plugin wurde erfolgreich initialisiert und der Ladevorgang wird fortgesetzt.
   - `false`: Das Plugin konnte nicht initialisiert werden. Der Ladevorgang wird abgebrochen und das Plugin entladen.

```cpp
// main.cpp
bool OnLoad() {
    Samp_SDK::Log("Initializing MyPlugin v1.0...");

    // Example: Load a module (more details in section 3.6)
    if (!Plugin_Module("my_database_module", "plugins/db_connector", "Database Module loaded.")) {
        Samp_SDK::Log("ERROR: Failed to load database module!");

        return false; // Aborts the main plugin loading
    }

    return true;
}
```

#### `void OnUnload()`

- **Beschreibung:** Letzte Funktion, die vom SA-MP-Server vor dem Entladen Ihres Plugins aus dem Speicher aufgerufen wird.
- **Verwendung:** Ideal zum Bereinigen von Ressourcen, Schließen von Verbindungen, Speichern von Zuständen und Sicherstellen, dass keine Ressourcen verloren gehen. Das SDK verwaltet das Entladen von Modulen (`Plugin_Module`) automatisch.

```cpp
// main.cpp
void OnUnload() {
    Samp_SDK::Log("MyPlugin unloaded. Releasing resources...");
    // No manual action is needed for modules loaded via Plugin_Module;
    // the SDK handles this.
}
```

#### `unsigned int GetSupportFlags()`

- **Beschreibung:** Informiert den SA-MP-Server, welche Funktionen Ihr Plugin unterstützt und verwenden möchte.
- **Verwendung:** **Geben Sie immer `SUPPORTS_VERSION` (oder `SAMP_PLUGIN_VERSION`) zurück.** Die Flags `SUPPORTS_AMX_NATIVES` und `SUPPORTS_PROCESS_TICK` werden vom SDK automatisch hinzugefügt, wenn `Plugin_Native`s vorhanden sind und/oder wenn das Makro `SAMP_SDK_WANT_PROCESS_TICK` definiert ist. Dies vereinfacht die Wartung und vermeidet Fehler.

```cpp
// main.cpp
unsigned int GetSupportFlags() {
    return SUPPORTS_VERSION; // The SDK adds the necessary flags automatically.
}
```

#### `void OnAmxLoad(AMX* amx)`

- **Erfordert:** `SAMP_SDK_WANT_AMX_EVENTS`
- **Beschreibung:** Wird immer aufgerufen, wenn ein neues Pawn-Skript (ein Gamemode oder Filterscript) auf dem Server geladen und initialisiert wird.
- **Verwendung:** Wenn Sie spezifische Logik für jedes AMX-Skript benötigen oder skriptspezifische Daten initialisieren möchten.

```cpp
// main.cpp (with SAMP_SDK_WANT_AMX_EVENTS defined)
void OnAmxLoad(AMX* amx) {
    // amx represents the new loaded script instance.
    Samp_SDK::Log("AMX script loaded: %p", (void*)amx);
}
```

#### `void OnAmxUnload(AMX* amx)`

- **Erfordert:** `SAMP_SDK_WANT_AMX_EVENTS`
- **Beschreibung:** Wird aufgerufen, wenn ein Pawn-Skript vom Server entladen wird.
- **Verwendung:** Zum Bereinigen von spezifischen Ressourcen, die Sie diesem bestimmten `AMX*` zugewiesen oder zugeordnet haben.

```cpp
// main.cpp (with SAMP_SDK_WANT_AMX_EVENTS defined)
void OnAmxUnload(AMX* amx) {
    Samp_SDK::Log("AMX script unloaded: %p", (void*)amx);
}
```

#### `void OnProcessTick()`

- **Erfordert:** `SAMP_SDK_WANT_PROCESS_TICK`
- **Beschreibung:** Wird wiederholt bei jedem "Tick" des Servers aufgerufen (normalerweise 20 Mal pro Sekunde, oder alle 50 ms).
- **Verwendung:** Für kontinuierliche Hintergrundlogik, Timer, Statusaktualisierungen, die nicht von Spielerereignissen abhängen, oder Datensynchronisation.
- **Vorsicht:** Vermeiden Sie hier blockierende oder rechenintensive Operationen, da diese den Server verlangsamen können.

```cpp
// main.cpp (with SAMP_SDK_WANT_PROCESS_TICK defined)
static int tick_count = 0;

void OnProcessTick() {
    tick_count++;

    if (tick_count % 200 == 0) // Every 10 seconds (20 ticks/sec * 10 sec = 200 ticks)
        Samp_SDK::Log("Server active for %d seconds.", tick_count / 20);
}
```

### 3.2. Exportieren von Plugin-Funktionen

Damit der SA-MP-Server die Funktionen Ihres Plugins (`Load`, `Supports`, etc.) aufrufen kann, müssen sie aus der DLL-Datei (Windows) oder SO-Datei (Linux) "exportiert" werden. Das SDK automatisiert den Export der Standard-Lebenszyklus-Funktionen, bietet aber auch Tools, mit denen Sie Ihre eigenen benutzerdefinierten Funktionen exportieren können, falls Sie Interoperabilität mit anderen Programmen benötigen.

Die Methode zum Exportieren von Funktionen variiert je nach Compiler.

#### Export für MSVC (Visual Studio) mit `Export_Plugin`

Unter Windows mit MSVC ist der einfachste Weg, benutzerdefinierte Funktionen zu exportieren, das Makro `Export_Plugin` zu verwenden, das in `exports.hpp` definiert ist.

- **Syntax:** `Export_Plugin("Funktion", "Stapel")`
- **`Funktion`**: Der genaue Name der zu exportierenden Funktion.
- **`Stapel`**: Die Gesamtanzahl der Bytes, die die Parameter der Funktion auf dem Stack belegen. Für die `__stdcall`-Konvention (Standard des SDK unter Windows) lautet die Berechnung `4 * (Anzahl der Parameter)`.

```cpp
#include "samp-sdk/exports.hpp"

// Beispiel: Exportieren einer benutzerdefinierten Funktion, die von
// einem anderen Programm oder Plugin aufgerufen werden könnte, das ihre Signatur kennt.
const char* SAMP_SDK_CALL GetPluginVersion() {
    return "1.0.0";
}

Export_Plugin("GetPluginVersion", "0");
```

> [!WARNING]
> **Einschränkung von `Export_Plugin`**
> Dieses Makro funktioniert **nur mit dem MSVC-Compiler (Visual Studio)**. Es verwendet eine Microsoft-spezifische `#pragma`-Direktive, die von anderen Compilern wie GCC und Clang ignoriert wird.

#### Export für GCC / Clang mit `SAMP_SDK_EXPORT`

Für GCC und Clang (unter Windows oder Linux) wird der Export durch das Makro `SAMP_SDK_EXPORT` verwaltet, das in `platform.hpp` definiert ist. Sie platzieren es einfach vor der Funktionsdefinition.

- **Mechanismus:** Unter Linux fügt es `__attribute__((visibility("default")))` hinzu. Unter Windows mit GCC/Clang fügt es `__attribute__((dllexport))` hinzu.
- **Verwendung:** Das SDK wendet `SAMP_SDK_EXPORT` bereits auf alle Lebenszyklus-Funktionen (`Load`, `Unload`, etc.) an, sodass deren Export für diese Compiler vollständig automatisch erfolgt. Für Ihre benutzerdefinierten Funktionen machen Sie einfach dasselbe.

```cpp
// Für GCC/Clang reicht die Definition der Funktion mit SAMP_SDK_EXPORT aus.
SAMP_SDK_EXPORT const char* SAMP_SDK_CALL GetPluginVersion() {
    return "1.0.0";
}
```

### 3.3. `Plugin_Public`: Abfangen von Pawn-Events

Das Makro `Plugin_Public` ist die primäre Brücke, um Pawn-Callbacks in Ihrem C++-Code zu empfangen.

#### Syntax und Deklaration

- `Plugin_Public(PublicName, Type1 Param1, Type2 Param2, ...)`
- Der Name der von Ihnen deklarierten C++-Funktion **muss identisch sein** mit dem Pawn-Callback (z.B. `OnPlayerConnect`).
- Die C++-Parametertypen (`int`, `float`, `std::string`) werden vom SDK automatisch konvertiert.

```cpp
// Intercepts OnPlayerText(playerid, text[])
Plugin_Public(OnPlayerText, int playerid, std::string text) {
    Samp_SDK::Log("Player %d said: %s", playerid, text.c_str());

    return PUBLIC_CONTINUE;
}
```

#### Automatische Parameter-Marshalling

Das SDK übernimmt automatisch das Lesen des `cell stack` der AMX und die Konvertierung in die angegebenen C++-Typen:
- `int`: Direkt von `cell` konvertiert.
- `float`: Von `cell` mit `amx::AMX_CTOF` konvertiert.
- `std::string`: Das SDK liest die Stringadresse in der AMX, weist einen `std::string` in C++ zu und kopiert den Inhalt.

#### Flusskontrolle: `PUBLIC_CONTINUE` vs `PUBLIC_STOP`

Der von Ihrer `Plugin_Public`-Funktion zurückgegebene Wert ist entscheidend und bestimmt den Ausführungsfluss des Callbacks:
- `return PUBLIC_CONTINUE;` (Wert `1`): Zeigt an, dass die Ausführung des Callbacks **fortgesetzt** werden soll. Wenn andere Plugins diesen Callback ebenfalls abfangen, werden sie aufgerufen (in umgekehrter Ladereihenfolge). Anschließend wird die ursprüngliche `public` im Pawn-Skript aufgerufen.
- `return PUBLIC_STOP;` (Wert `0`): Zeigt an, dass die Ausführung des Callbacks **unterbrochen** werden soll. Kein weiteres Plugin (mit geringerer Priorität) oder die ursprüngliche `public` im Pawn-Skript wird für dieses Ereignis aufgerufen. Dies ist ideal, um ein System zu implementieren, das ein Standardverhalten von SA-MP "überschreibt" oder "blockiert".

```cpp
// main.cpp
Plugin_Public(OnPlayerCommandText, int playerid, std::string cmdtext) {
    if (cmdtext == "/freeze") {
        Pawn_Native(TogglePlayerControllable, playerid, 0); // Freezes the player
        Pawn_Native(SendClientMessage, playerid, -1, Plugin_Format("Player %d frozen.", playerid));

        return PUBLIC_STOP; // Prevents the command from being processed by other scripts.
    }

    return PUBLIC_CONTINUE; // Allows other commands to be processed.
}
```

#### Ghost Callbacks

Eine erweiterte Funktion von `Plugin_Public` ist die Unterstützung von "Ghost Callbacks". Dies bedeutet, dass Sie einen Pawn-Callback abfangen können, selbst wenn er **nicht** im `.amx`-Skript des Gamemodes oder Filterscripts vorhanden ist. Das SDK "täuscht" den Server, damit er Ihren C++-Hook trotzdem aufruft. Dies ist nützlich für interne Callbacks oder um neue Funktionen zu erstellen, ohne von der Anwesenheit einer `public` im Pawn-Skript abzuhängen.

```cpp
// You can define a callback that the Pawn script doesn't have, but your plugin will hear it.
Plugin_Public(OnMyCustomInternalEvent, int data1, float data2) {
    Samp_SDK::Log("Custom internal event received: %d, %.2f", data1, data2);

    return PUBLIC_CONTINUE;
}

// To "trigger" this event from another point in your C++ code:
// Pawn_Public(OnMyCustomInternalEvent, 123, 45.67f);
// The call will go to your Plugin_Public above, even if there is no OnMyCustomInternalEvent in Pawn.
```

### 3.4. `Plugin_Native`: Erstellen von nativen C++-Funktionen

`Plugin_Native` ermöglicht es Ihnen, die Funktionalität von Pawn mit hochperformantem C++-Code zu erweitern.

#### Syntax und feste Signatur

- `Plugin_Native(NativeName, AMX* amx, cell* params)`
- Die C++-Funktion muss genau diese Signatur haben: `cell NativeName(AMX* amx, cell* params)`.
- `NativeName` ist der Name, den die Pawn-Skripte verwenden werden.

```cpp
// Pawn: native GetPlayerPingAverage(playerid);
Plugin_Native(GetPlayerPingAverage, AMX* amx, cell* params) {
    // ... Implementation ...
    return 0;
}
```

#### Automatische Native-Registrierung

> [!NOTE]
> Sie müssen `amx_Register` **nicht** manuell aufrufen. Das SDK erkennt alle Ihre `Plugin_Native`s (in jeder `.cpp`-Datei, die `samp_sdk.hpp` eingebunden und `SAMP_SDK_WANT_AMX_EVENTS` definiert hat) und registriert sie automatisch in jedem geladenen AMX-Skript (`OnAmxLoad`).

#### Parameter-Extraktion: `Register_Parameters` vs. `Native_Params`

##### `Register_Parameters(...)`

- **Beschreibung:** Einfacherer Helfer zum sequenziellen Extrahieren mehrerer Parameter.
- **Verwendung:** `Register_Parameters(variable1, variable2, ...)`
- **Einschränkungen:** Für Eingabeparameter. Behandelt keine optionalen Parameter oder den Zugriff per Index.
- **Unterstützte Typen:** `int`, `float`, `std::string`.

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

##### `Native_Params` (Vollständige API: `Get`, `Get_REF`, `Set_REF`)

- **Beschreibung:** Eine Wrapper-Klasse, die eine objektorientierte Schnittstelle für den Zugriff auf die Parameter einer Native bereitstellt. Leistungsfähiger für komplexe Szenarien.
- **Konstruktion:** `Native_Params p(amx, params);`

###### `p.Count()`

- **Beschreibung:** Gibt die Anzahl der an die Native übergebenen Parameter zurück.
- **Verwendung:** Wesentlich für den Umgang mit optionalen Parametern.

###### `p.Get<T>(size_t index)`

- **Beschreibung:** Extrahiert einen Eingabeparameter per Index und konvertiert ihn in den Typ `T`.
- **Unterstützte Typen:** `int`, `float`, `std::string`.

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

- **Beschreibung:** Ruft den Wert eines **Referenzparameters** (Pawn-Zeiger) ab und speichert ihn in `out_value`.
- **Verwendung:** Zum Lesen von Werten, die als Referenz von Pawn übergeben wurden.
- **Rückgabe:** `true`, wenn die AMX-Adresse gültig ist, `false` sonst.

```cpp
// Pawn: native CheckPlayerStats(playerid, &Float:health, &money);
Plugin_Native(CheckPlayerStats, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    
    int playerid = p.Get<int>(0);
    float health = 0.0f;
    int money = 0;

    // Gets the values of the references (Pawn passed addresses)
    p.Get_REF(1, health); // Reads the value of Float:health
    p.Get_REF(2, money);   // Reads the value of money
    
    Samp_SDK::Log("Player %d, Health: %.1f, Money: %d", playerid, health, money);
    
    // Now, modify them
    health = 50.0f;
    money += 100;
    
    // And writes them back to Pawn's memory
    p.Set_REF(1, health);
    p.Set_REF(2, money);
    
    return 1;
}
```

###### `p.Get_REF<T>(size_t index)` (C++17+)

- **Beschreibung:** Gibt ein `std::optional<T>` zurück, um einen Referenzparameter zu lesen. Sicherer für C++17 und höher.

###### `p.Set_REF<T>(size_t index, T value)`

- **Beschreibung:** Schreibt einen Wert `T` in einen Pawn-**Referenzparameter** (die Adresse, die Pawn übergeben hat).
- **Verwendung:** Zum Ändern von Werten, die als Referenz übergeben wurden, sodass Pawn die Änderung sieht.
- **Rückgabe:** `true`, wenn das Schreiben erfolgreich war, `false` sonst.

#### Rückgabewerte

- Ihre `Plugin_Native`-Funktion muss eine `cell` zurückgeben.
- Um einen `int` oder `bool` zurückzugeben, verwenden Sie einen Cast zu `cell`.
- Um einen `float` zurückzugeben, verwenden Sie `amx::AMX_FTOC(my_float)`.

```cpp
// Returns a bool
Plugin_Native(IsPlayerSpawned, AMX* amx, cell* params) {
    int playerid;
    Register_Parameters(playerid);

    return (Pawn_Native(GetPlayerState, playerid) == PLAYER_STATE_SPAWNED) ? 1 : 0;
}

// Returns a float
Plugin_Native(GetPlayerMaxHealth, AMX* amx, cell* params) {
    return amx::AMX_FTOC(100.0f); // Returns 100.0f
}
```

### 3.5. `Plugin_Native_Hook`: Abfangen von vorhandenen SA-MP-Natives

Das Makro `Plugin_Native_Hook` ermöglicht es Ihnen, das Verhalten jeder vorhandenen SA-MP-Native-Funktion oder von Natives anderer Plugins abzufangen und zu modifizieren. Dies ist ein leistungsstarker Mechanismus, um die Standardlogik des Servers zu erweitern oder zu ändern.

#### Syntax und feste Signatur

- `Plugin_Native_Hook(NativeName, AMX* amx, cell* params)`
- Die C++-Funktion muss genau diese Signatur haben: `cell NativeName(AMX* amx, cell* params)`.
- `NativeName` muss der genaue Name der Native sein, die Sie hooken möchten (z.B. `SendClientMessage`, `SetPlayerPos`).

```cpp
// Intercepts the SendClientMessage native
Plugin_Native_Hook(SendClientMessage, AMX* amx, cell* params) {
    // ...
    return Call_Original_Native(SendClientMessage); // Important to call the original
}
```

#### Hook-Registrierung und -Aktivierung

> [!NOTE]
> Sie müssen `amx_Register` **nicht** manuell aufrufen oder `SAMP_SDK_WANT_AMX_EVENTS` speziell für `Plugin_Native_Hook` definieren. Das SDK erkennt und registriert Ihre Hooks automatisch. Bei der ersten Ausführung eines AMX-Skripts ersetzt das SDK den Native-Zeiger in der Tabelle durch ein "Trampolin", das zu Ihrer `Plugin_Native_Hook`-Funktion umleitet. Dieser Prozess gewährleistet die sichere Verkettung von Hooks mehrerer Plugins.

#### Aufruf der originalen Native (Hook-Kette): `Call_Original_Native`

Innerhalb Ihrer `Plugin_Native_Hook`-Funktion **MÜSSEN** Sie das Makro `Call_Original_Native(NativeName)` verwenden, um die Originalfunktion (oder den nächsten Hook in der Kette) aufzurufen. Dies ist entscheidend, um:
- **Funktionalität zu bewahren:** Wenn Sie die Originalfunktion nicht aufrufen, funktioniert die gehookte Native einfach nicht mehr für andere Plugins oder den Server.
- **Hook-Kettung:** Ermöglicht es mehreren Plugins, dieselbe Native zu hooken, und stellt sicher, dass alle Hooks in einer Sequenz ausgeführt werden.
- **Rückgabewertmanipulation:** Sie können den Rückgabewert von `Call_Original_Native` überprüfen und sogar ändern, bevor Sie ihn aus Ihrer Hook-Funktion zurückgeben.

```cpp
// Example: Blocking SendClientMessage if it contains a specific word
Plugin_Native_Hook(SendClientMessage, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    
    // Extracts the parameters for analysis
    int playerid = p.Get<int>(0);
    // int color = p.Get<int>(1); // We don't need the color for this logic
    std::string message = p.Get_String(2); // Gets the message string

    if (message.find("BADWORD") != std::string::npos) {
        Samp_SDK::Log("MESSAGE BLOCKED for playerid %d: %s", playerid, message.c_str());

        return 0; // Returns 0 (false) to Pawn, indicating the message was not sent.
                  // And more importantly, we DO NOT call Call_Original_Native, blocking the message.
    }

    // If the message does not contain the forbidden word, we call the original native
    // and return its value, ensuring the message is sent normally
    // and that other hooks (if any) are executed.
    return Call_Original_Native(SendClientMessage);
}
```

#### Vollständiges Beispiel für `Plugin_Native_Hook`

```cpp
#define SAMP_SDK_IMPLEMENTATION
// SAMP_SDK_WANT_AMX_EVENTS is not strictly necessary for hooks, but common for OnAmxLoad/Unload
// #define SAMP_SDK_WANT_AMX_EVENTS 
#include "samp-sdk/samp_sdk.hpp"

// Hook for the CreateVehicle native
Plugin_Native_Hook(CreateVehicle, AMX* amx, cell* params) {
    Native_Params p(amx, params);

    // Extracts the CreateVehicle native parameters for inspection
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
    // If the model is 400 (Landstalker), we change it to 401 (Bravura)
    if (modelid == 400) {
        // We directly modify the 'params' array for the original call
        params[1] = static_cast<cell>(401); // The model is at position 0 in the parameter array (params[1])
        Samp_SDK::Log("  -> Model 400 changed to 401 before creation.");
    }
    
    // We call the original native (or the next hook in the chain) with the possibly modified parameters
    cell original_retval = Call_Original_Native(CreateVehicle);

    Samp_SDK::Log("HOOK: CreateVehicle returned: %d (Vehicle ID)", (int)original_retval);

    // You can modify the return value here before returning it to Pawn.
    // Example: if vehicle creation failed, return a custom invalid ID.
    if ((int)original_retval == INVALID_VEHICLE_ID) {
        Samp_SDK::Log("  -> Vehicle creation failed in original native.");

        return -1; // Returns a different value to Pawn.
    }

    return original_retval; // Returns the value that the original native returned (or the modified one above).
}

unsigned int GetSupportFlags() {
    return SUPPORTS_VERSION; 
}

// Minimal implementations for the lifecycle
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
> Die direkte Manipulation des `cell* params`-Arrays zur Änderung von Eingabeparametern erfordert Vorsicht. Stellen Sie sicher, dass Sie die Reihenfolge und den Typ der Parameter verstehen. Für die meisten Anwendungsfälle reicht `p.Get(...)` zur Inspektion und `Call_Original_Native(...)` zur Fortsetzung der Kette aus. Die direkte Änderung von `params` sollte nur erfolgen, wenn Sie wissen, dass der Parameter ein Wert ist und für den ursprünglichen Aufruf geändert werden muss. Bei Strings und Arrays ist die Änderung komplexer und beinhaltet in der Regel `amx::Set_String`, um in die vorhandene Adresse zu schreiben oder neu zuzuweisen, was einfacher zu handhaben sein kann, indem die Native über `Pawn_Native` mit den neuen Werten aufgerufen und `0` von Ihrem Hook zurückgegeben wird, um den ursprünglichen Aufruf abzubrechen.

### 3.6. `Pawn_*` Makros: Aufrufen von Pawn-Funktionen aus C++

Diese Makros sind das Gegenteil von `Plugin_Public` und `Plugin_Native`: Sie ermöglichen es Ihrem C++-Code, Pawn-Funktionen aufzurufen.

#### `Pawn_Native(NativeName, ...)`

- **Zweck:** Die empfohlene Methode, SA-MP Native-Funktionen (oder die anderer Plugins) aus C++ aufzurufen.
- **Mechanismus:** Sucht den Zeiger der Native im internen Cache des SDK (gefüllt durch `Amx_Register_Detour`). Falls gefunden, führt es die Native in einer `Amx_Sandbox`-Umgebung (einer gefälschten und isolierten AMX-Instanz) aus.
- **Performance:** Am effizientesten, da es die teure Suche nach `publics` vermeidet und direkt mit dem Native-Zeiger interagiert.

#### `Pawn_Public(PublicName, ...)`

- **Zweck:** Ruft eine bestimmte öffentliche Funktion in einem Pawn-Skript auf.
- **Mechanismus:** Durchläuft die vom `Amx_Manager` verwalteten `AMX*`-Instanzen, sucht die `public` nach Namen und führt sie aus.
- **Performance:** Weniger effizient als `Pawn_Native` aufgrund der Suche und des tatsächlichen `amx_Exec`. Im Allgemeinen sind `publics` langsamer als `natives`.
- **Verwendung:** Ideal zum Aufrufen benutzerdefinierter Ereignisse in Ihren Gamemodes/Filterscripts, die keine Natives sind.

#### `Pawn(FunctionName, ...)`

- **Zweck:** Ein Komfortmakro, das versucht zu erraten, ob die Funktion eine Native oder eine Public ist.
- **Mechanismus:** Versucht zunächst, als `Pawn_Native` aufzurufen. Wenn dies fehlschlägt (die Native wird nicht gefunden), versucht es, als `Pawn_Public` aufzurufen.
- **Performance:** Kann etwas langsamer sein als `Pawn_Native`, wenn die Funktion eine Native ist, aufgrund des doppelten Suchversuchs. Für `publics` ist die Leistung die gleiche wie bei `Pawn_Public`.
- **Verwendung:** Für Funktionen, bei denen Sie nicht sicher sind, ob sie Natives oder Publics sind, oder um den Boilerplate-Code zu vermeiden, zuerst eine und dann die andere zu versuchen.

#### Syntax und Konventionen

- **Funktionsname:** Verwenden Sie immer den Pawn-Funktionsnamen **direkt, ohne Anführungszeichen**. Das SDK konvertiert ihn intern in einen String.
- **Parameter:** Übergeben Sie die C++-Parameter direkt.

```cpp
// Correct:
Pawn_Native(SetPlayerPos, playerid, 100.0f, 200.0f, 300.0f); 

// Wrong (but would technically work due to hashing, avoid):
Pawn_Native("SetPlayerPos", playerid, 100.0f, 200.0f, 300.0f); 
```

#### Marshalling von Eingabeparametern

Das SDK konvertiert Ihre C++-Typen in das `cell`-Format der AMX und verwaltet dabei den Speicher nach Bedarf:
- `int`, `bool`, `long`, `enum` -> `cell`
- `float`, `double` -> `cell` (mittels `amx::AMX_FTOC`)
- `const char*`, `std::string`, `std::string_view` (C++17+) -> `cell` (weist Speicher in der AMX zu, kopiert den String und übergibt die Adresse `amx_addr`)

```cpp
void Send_Formatted_Message(int playerid, const std::string& msg) {
    Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, msg);
}
```

#### Marshalling von Ausgabeparametern (Referenzen: `int&`, `float&`, `std::string&`)

Dies ist eine Schlüsselfunktionalität für Bequemlichkeit und Sicherheit. Für Pawn-Funktionen, die einen Zeiger (Referenz) erwarten, automatisiert das SDK den gesamten Prozess der Speicherzuweisung/-freigabe und Datenkopie.

- **Verwendung:** Übergeben Sie Ihre Variable einfach als Referenz (`&`).
- **Mechanismus:** Das SDK weist Speicher im AMX-Heap zu, übergibt die AMX-Adresse an die Pawn-Funktion, wartet darauf, dass die Pawn-Funktion diese Adresse füllt, liest den Wert zurück und gibt den AMX-Speicher frei. Alles transparent.
- **Mit `std::string&`:** Das SDK weist einen Standardpuffer (256 Zellen) in der AMX für den String zu.

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

#### Das `Callback_Result`-Objekt: Vollständige Analyse

Alle `Pawn_*`-Aufrufe geben ein `Callback_Result`-Objekt zurück. Dieses Objekt ist ein sicherer Wrapper für das Ergebnis des Pawn-Aufrufs.

- `Callback_Result() noexcept`: Standardkonstruktor, zeigt Fehlschlag an (`success_ = false`).
- `Callback_Result(bool success, cell value) noexcept`: Konstruktor für Erfolg oder Fehlschlag mit Wert.
- `explicit operator bool() const`: Ermöglicht die Verwendung von `if (result)`, um zu überprüfen, ob der Aufruf erfolgreich war.
- `operator cell() const`: Ermöglicht die Konvertierung des Ergebnisses in `cell`, um den Wert zu erhalten.
- `float As_Float() const`: Bequemlichkeit, um das Ergebnis als `float` zu erhalten.
- `cell Value() const`: Gibt den Rohwert `cell` zurück.
- `bool Success() const`: Gibt `true` zurück, wenn der Pawn-Aufruf erfolgreich war.
- `int Get_Amx_Error() const`: Gibt den AMX-Fehlercode zurück, wenn der Aufruf fehlgeschlagen ist (0 für Erfolg).

```cpp
// Example: Getting a player's health.
// The native GetPlayerHealth(playerid, &Float:health) expects a playerid and a reference to health.
int playerid = 0; // Example player ID
float player_health = 0.0f;

// We call GetPlayerHealth, passing playerid and player_health by reference.
// The SDK will handle the marshalling for the 'health' output parameter.
Callback_Result result = Pawn_Native(GetPlayerHealth, playerid, player_health);

if (result) { // Checks if the call was successful (operator bool)
    // The value returned by result.As_Float() or result (operator cell)
    // would be the return value of the *native*, not the output parameter.
    // The health value has already been updated in 'player_health' due to output parameter marshalling.
    Samp_SDK::Log("Player %d has %.1f health.", playerid, player_health);
}
else {
    // The call failed, perhaps the player does not exist or the native was not found.
    Samp_SDK::Log("Error getting player %d health. AMX code: %d", playerid, result.Get_Amx_Error());
}

// For natives that return a value and use output parameters (less common, but possible),
// you would use both:
// Callback_Result other_result = Pawn_Native(SomeNative, param1, output_param, param2);
// if (other_result) {
//     cell returned_value = other_result;
//     // output_param is already updated
// }
```

### 3.7. `Plugin_Module`: Dynamische Modulverwaltung

Das Makro `Plugin_Module` ermöglicht es Ihrem Plugin, als "Lader" für andere Plugins zu fungieren, wodurch eine modulare und erweiterbare Architektur entsteht. Ein auf diese Weise geladenes Modul wird als erstklassiges Plugin behandelt, mit einem eigenen Ereignislebenszyklus, der vom Host-Plugin verwaltet wird.

#### Syntax und Zweck

- `Plugin_Module(const char* base_filename, const char* module_directory, const char* optional_success_message)`
- `base_filename`: Der *Basisname* der Moduldatei **ohne Dateierweiterung** (z.B. für `my_module.dll` oder `my_module.so` verwenden Sie `"my_module"`). Das SDK fügt automatisch die entsprechende `.dll`- oder `.so`-Erweiterung hinzu.
- `module_directory`: Der Pfad des Verzeichnisses, in dem sich die Moduldatei befindet (z.B. `"plugins/my_custom_modules"`). **Fügen Sie den Dateinamen hier nicht ein.** Das SDK erstellt den vollständigen Pfad (`module_directory/base_filename.ext`).
- `optional_success_message`: Eine optionale Nachricht, die in der Serverkonsole protokolliert wird, wenn das Modul erfolgreich geladen wurde.

```cpp
// main.cpp, inside OnLoad()

// Loads the 'core_logic.dll' (or 'core_logic.so') module
// which is located in the 'modules/custom/' folder of the server.
if (!Plugin_Module("core_logic", "modules/custom", "Core Logic Module loaded successfully!"))
    return (Samp_SDK::Log("FATAL ERROR: Failed to load 'core_logic' module!"), false);

// Loads the 'admin_system.dll' (or 'admin_system.so') module
// which is located directly in the 'plugins/' folder of the server.
if (!Plugin_Module("admin_system", "plugins", "Administration Module activated."))
    Samp_SDK::Log("WARNING: Administration Module could not be loaded.");
```

#### Lebenszyklus eines Moduls

Ein Modul muss die Funktionen `Load`, `Unload` und `Supports` exportieren, genau wie ein normales Plugin. Das SDK verwaltet den Lebenszyklus des Moduls wie folgt:

- **Laden:** Wenn `Plugin_Module` aufgerufen wird, führt das SDK Folgendes aus:
   1. Erstellt den vollständigen Dateipfad (z.B. `modules/custom/core_logic.dll`).
   2. Verwendet `Dynamic_Library` (`LoadLibrary`/`dlopen`), um die Binärdatei zu laden.
   3. **Ruft die Zeiger für ALLE Lebenszyklusfunktionen des Moduls ab:**
      - **Erforderlich:** `Load`, `Unload`, `Supports`. Wenn eine fehlt, schlägt das Laden des Moduls fehl.
      - **Optional:** `AmxLoad`, `AmxUnload`, `ProcessTick`.
   4. Ruft die `Load`-Funktion des Moduls auf und übergibt `ppData` des Hauptplugins.
   5. Wenn `Load` `true` zurückgibt, wird das Modul zur internen Liste der geladenen Module hinzugefügt.

- **Ereignisweiterleitung:** Das Host-Plugin **leitet Ereignisse automatisch** an alle geladenen Module weiter.
 > [!IMPORTANT]
 > Damit die Ereignisse korrekt weitergeleitet werden, muss das **Host-Plugin** (das `Plugin_Module` aufruft) für den Empfang dieser Ereignisse konfiguriert sein.
 > - Damit `AmxLoad` und `AmxUnload` in den Modulen funktionieren, muss das Host-Plugin das Makro `SAMP_SDK_WANT_AMX_EVENTS` definieren.
 > - Damit `ProcessTick` in den Modulen funktioniert, muss das Host-Plugin das Makro `SAMP_SDK_WANT_PROCESS_TICK` definieren.

- **Entladen:** Während des `OnUnload` Ihres Hauptplugins entlädt das SDK alle Module, die über `Plugin_Module` geladen wurden. Dies geschieht in **umgekehrter Reihenfolge** zum Laden (das zuletzt geladene wird zuerst entladen), was entscheidend ist, um Abhängigkeiten zu verwalten und die korrekte Freigabe von Ressourcen zu gewährleisten.

#### Vorteile der Modularisierung

- **Code-Organisation:** Teilen Sie große Plugins in kleinere, überschaubare Komponenten auf, jede in einer eigenen Moduldatei.
- **Wiederverwendbarkeit:** Erstellen Sie generische Module (z.B. ein Datenbankmodul, ein erweitertes Protokollsystemmodul), die von verschiedenen Plugins verwendet werden können, und fördern Sie so die Code-Wiederverwendung.
- **Unabhängige Komponenten:** Erstellen Sie Module, die **vollständig ereignisgesteuert und unabhängig sind**. Ein Modul kann eigene `Plugin_Native`s haben, `Plugin_Public`s abfangen und eine eigene `OnProcessTick`-Logik haben, die wie ein eigenständiges Plugin funktioniert, aber von einem Host geladen wird.
- **Dynamische Updates:** In kontrollierten Szenarien ermöglicht dies die Aktualisierung von Teilen Ihres Systems (Ersetzen einer `.dll`- oder `.so`-Moduldatei), ohne das Hauptplugin oder den gesamten Server neu kompilieren und neu starten zu müssen (obwohl dies ein strenges Versions- und Kompatibilitätsmanagement erfordert).

### 3.8. `Plugin_Call`: Aufrufen interner Plugin-Natives

Verwenden Sie `Plugin_Call`, um eine `Plugin_Native` aufzurufen, die **innerhalb Ihres eigenen Plugins** definiert ist.

#### Syntax und Performance-Vorteile

- `Plugin_Call(NativeName, Param1, Param2, ...)`
- **Vorteil:** Vermeidet den Overhead, die Native im AMX-Native-Array zu suchen. Das SDK verwaltet eine direkte Zuordnung von Namens-Hashes zu Funktionszeigern für Ihre eigenen Natives, was dies zur schnellsten Methode macht, sie intern aufzurufen.
- **Erfordert:** `SAMP_SDK_WANT_AMX_EVENTS`.

```cpp
// main.cpp
Plugin_Native(InternalCheckPlayerLevel, AMX* amx, cell* params) {
    int playerid;
    Register_Parameters(playerid);

    // Logic to check the level
    return (playerid % 2 == 0) ? 1 : 0; // Example: even level for even IDs
}

void Check_All_Players_Level() {
    for (int i = 0; i < MAX_PLAYERS; ++i) {
        if (Pawn_Native(IsPlayerConnected, i)) {
            if (Plugin_Call(InternalCheckPlayerLevel, i)) // Calls your own native
                Samp_SDK::Log("Player %d is at a high level!", i);
        }
    }
}
```

### 3.9. SDK-Utility-Funktionen

#### `Samp_SDK::Log(const char* format, ...)`

- **Beschreibung:** Gibt Meldungen in der Serverkonsole und in der Datei `server_log.txt` aus. Ein sicherer Wrapper für `logprintf`.
- **Verwendung:** Zum Debuggen, für Statusmeldungen und Fehler.
- **Mechanismus:** Intern ruft das SDK den Zeiger auf `logprintf` über `ppData[PLUGIN_DATA_LOGPRINTF]` ab. Die Funktion handhabt die Formatierung des Strings auf sichere Weise.

```cpp
// Anywhere in your plugin
Samp_SDK::Log("The plugin was initialized with a value %d and a string '%s'.", 123, "test");
```

#### `std::string Plugin_Format(const char* format, ...)` (Empfohlen)

- **Beschreibung:** Formatiert einen String sicher (ähnlich wie `sprintf`) und gibt einen `std::string` zurück. Dies ist die **empfohlene und idiomatischste** Methode, Strings zur Verwendung innerhalb Ihres Plugins zu formatieren.
- **Verwendung:** Ideal zum Erstellen formatierter Nachrichten, bevor sie an `Samp_SDK::Log`, `Pawn_Native(SendClientMessage, ...)`, oder für andere String-Anforderungen in Ihrem C++-Code übergeben werden.
- **Mechanismus:** Intern ist `Plugin_Format` ein Makro, das `Samp_SDK::Format` aufruft. Es verwendet `vsnprintf`, um die genaue Größe des formatierten Strings zu bestimmen und weist einen `std::string` mit ausreichender Kapazität zu, wodurch Pufferüberläufe vermieden werden.

```cpp
int playerid = 0; // Example ID
int health = 50;
Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, Plugin_Format("Player %d, your current health is %d.", playerid, health));

// Can also be used for internal logs
Samp_SDK::Log(Plugin_Format("DEBUG: Processing status for ID %d", playerid));
```

#### `std::string Samp_SDK::Format(const char* format, ...)` (Implementierungsdetail)

- **Beschreibung:** Die zugrunde liegende Implementierungsfunktion für die Stringformatierung, die sich im `Samp_SDK`-Namespace befindet.
- **Verwendung:** Wird in der Regel nicht direkt vom Benutzer aufgerufen. Das Makro `Plugin_Format` wird als Komfort für diese Funktion bereitgestellt, um sich an die Namenskonventionen anderer SDK-Makros (`Plugin_Public`, `Plugin_Native`) anzupassen. Sie würden es nur direkt aufrufen, wenn Sie das Makro `Plugin_Format` aus einem bestimmten Grund vermeiden möchten.

```cpp
// Example of how Samp_SDK::Format works, but prefer Plugin_Format
std::string raw_status = Samp_SDK::Format("For internal use only: %d.", 42);
```

#### `std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`

- **Beschreibung:** Konvertiert eine AMX-String-Adresse (`cell amx_addr`) in einen C++-`std::string`.
- **Verwendung:** Hauptsächlich innerhalb von `Plugin_Native` und `Plugin_Native_Hook`, wenn Sie auf Strings zugreifen müssen, die nicht automatisch von `Register_Parameters` oder `Native_Params` konvertiert werden (z.B. wenn der Pawn-Parameter ein `const` `string` ist und nicht als `std::string` in Ihrer `Plugin_Native` oder `Plugin_Public` für das automatische Marshalling deklariert wurde).

```cpp
Plugin_Native(PrintRawAmxString, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    cell amx_string_addr = p.Get<cell>(0); // Gets the string address in AMX

    std::string cpp_string = Samp_SDK::Get_String(amx, amx_string_addr);
    Samp_SDK::Log("String from AMX: %s", cpp_string.c_str());

    return 1;
}
```

## 4. Kompilierung und Bereitstellung

### Architektur- und Plattformanforderungen

- Ihr Plugin **MUSS** für die Architektur **x86 (32-Bit)** kompiliert werden.
- Unterstützte Plattformen: Windows (.dll) und Linux (.so).

### Beispiele für Kompilierungsbefehle

#### **MSVC (Visual Studio)**

1. Erstellen Sie ein neues Projekt für eine "Dynamic-Link Library (DLL)".
2. Legen Sie in den Projekteinstellungen die "Lösungsplattform" auf **x86** fest.
3. Stellen Sie sicher, dass der C++ Language Standard mindestens C++17 ist.

#### **GCC / Clang (Linux)**

```bash
# For a plugin named 'my_plugin.so' from 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -fPIC -Wall -Wextra -Wl,--no-undefined main.cpp -o my_plugin.so
```
- `-m32`: Kompiliert für 32-Bit.
- `-shared`: Erstellt eine gemeinsam genutzte Bibliothek (`.so`).
- `-std=c++17`: Legt den C++-Standard auf C++17 fest (kann auch `c++20` sein, aber C++17 ist das Minimum).
- `-O2`: Optimierungsstufe 2.
- `-fPIC`: Generiert positionsunabhängigen Code, erforderlich für gemeinsam genutzte Bibliotheken.
- `-Wall -Wextra`: Aktiviert zusätzliche Warnungen, um Fehler zu erkennen.
- `-Wl,--no-undefined`: Verhindert das Erstellen der Bibliothek, wenn undefinierte Symbole vorhanden sind.

#### **GCC / Clang (MinGW unter Windows)**

```bash
# For a plugin named 'my_plugin.dll' from 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -static-libstdc++ -static-libgcc -Wl,--no-undefined main.cpp -o my_plugin.dll
```
- `-static-libstdc++`: Linkt die C++-Standardbibliothek statisch. Dies ist unerlässlich, um zu verhindern, dass Ihr Plugin von compilerspezifischen Laufzeit-DLLs abhängt, die auf dem System des Benutzers möglicherweise nicht vorhanden sind.
- `-static-libgcc`: Linkt die GCC-Bibliothek statisch.

### Überlegungen zur Verteilung

- **Dateiname:** Ihr Plugin muss die Erweiterung `.dll` (Windows) oder `.so` (Linux) haben. Beispiel: `my_plugin.dll`.
- **Speicherort:** Legen Sie die kompilierte Datei in den Ordner `plugins/` Ihres SA-MP-Servers.
- **server.cfg:** Fügen Sie den Namen Ihres Plugins (unter Windows ohne Erweiterung) zur Zeile `plugins` in der `server.cfg` hinzu.
   ```
   plugins my_plugin (if Linux, my_plugin.so)
   ```

## Lizenz

Copyright © **AlderGrounds**

Diese Software ist unter den Bedingungen der MIT-Lizenz ("Lizenz") lizenziert; Sie dürfen diese Software gemäß den Lizenzbedingungen nutzen. Eine Kopie der Lizenz finden Sie unter: [MIT License](https://opensource.org/licenses/MIT)

### Nutzungsbedingungen

#### 1. Gewährte Berechtigungen

Diese Lizenz gewährt jeder Person, die eine Kopie dieser Software und der zugehörigen Dokumentationsdateien erhält, kostenlos folgende Rechte:
* Die Software ohne Einschränkungen zu nutzen, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, zu unterlizenzieren und/oder zu verkaufen
* Personen, denen die Software zur Verfügung gestellt wird, dies unter den folgenden Bedingungen zu gestatten

#### 2. Verpflichtende Bedingungen

Alle Kopien oder wesentliche Teile der Software müssen enthalten:
* Den obigen Urheberrechtshinweis
* Diesen Erlaubnishinweis
* Den nachstehenden Haftungsausschluss

#### 3. Urheberrecht

Die Software und alle zugehörige Dokumentation sind durch Urheberrechtsgesetze geschützt. Die **AlderGrounds** behält die ursprünglichen Urheberrechte an der Software.

#### 4. Gewährleistungsausschluss und Haftungsbeschränkung

DIE SOFTWARE WIRD "WIE BESEHEN" ZUR VERFÜGUNG GESTELLT, OHNE JEGLICHE AUSDRÜCKLICHE ODER IMPLIZITE GEWÄHRLEISTUNG, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT, DER EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND DER NICHTVERLETZUNG VON RECHTEN DRITTER.

DIE AUTOREN ODER URHEBERRECHTSINHABER SIND IN KEINEM FALL HAFTBAR FÜR ANSPRÜCHE, SCHÄDEN ODER ANDERE VERPFLICHTUNGEN, OB IN EINER VERTRAGS- ODER DELIKTKLAGE, DIE AUS ODER IN VERBINDUNG MIT DER SOFTWARE ODER DER NUTZUNG ODER ANDEREN GESCHÄFTEN MIT DER SOFTWARE ENTSTEHEN.

---

For detailed information about the MIT License, visit: https://opensource.org/licenses/MIT