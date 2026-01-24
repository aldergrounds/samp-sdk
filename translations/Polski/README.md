# SA-MP SDK

<div align="center">

![C++](https://img.shields.io/badge/C%2B%2B-17%2B-00599C?style=for-the-badge&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-blue?style=for-the-badge&logo=windows&logoColor=white)
![Architecture](https://img.shields.io/badge/Architecture-x86%20(32--bit)-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**Nowoczesne, wyłącznie nagłówkowe i wysokopoziomowe SDK C++ do tworzenia wtyczek i modułów dla SA-MP.**

</div>

## Języki

- Português: [README](../../)
- Deutsch: [README](../Deutsch/README.md)
- English: [README](../English/README.md)
- Español: [README](../Espanol/README.md)
- Français: [README](../Francais/README.md)
- Italiano: [README](../Italiano/README.md)
- Русский: [README](../Русский/README.md)
- Svenska: [README](../Svenska/README.md)
- Türkçe: [README](../Turkce/README.md)

## Spis Treści

- [SA-MP SDK](#sa-mp-sdk)
  - [Języki](#języki)
  - [Spis Treści](#spis-treści)
  - [1. Wprowadzenie i filozofia projektowania](#1-wprowadzenie-i-filozofia-projektowania)
    - [Problem ze standardowym API C SA-MP](#problem-ze-standardowym-api-c-sa-mp)
    - [Rozwiązanie SA-MP SDK: abstrakcja z bezpieczeństwem i wydajnością](#rozwiązanie-sa-mp-sdk-abstrakcja-z-bezpieczeństwem-i-wydajnością)
    - [Model tylko nagłówkowy: zalety i implikacje](#model-tylko-nagłówkowy-zalety-i-implikacje)
  - [2. Konfiguracja i środowisko](#2-konfiguracja-i-środowisko)
    - [Wymagania kompilacji](#wymagania-kompilacji)
    - [Zalecana struktura plików](#zalecana-struktura-plików)
    - [Podstawowe makra konfiguracyjne](#podstawowe-makra-konfiguracyjne)
      - [`SAMP_SDK_IMPLEMENTATION`](#samp_sdk_implementation)
      - [`SAMP_SDK_WANT_AMX_EVENTS`](#samp_sdk_want_amx_events)
      - [`SAMP_SDK_WANT_PROCESS_TICK`](#samp_sdk_want_process_tick)
    - [Definicje i stałe SA-MP (`samp_defs.hpp`)](#definicje-i-stałe-sa-mp-samp_defshpp)
  - [3. Obszerny przewodnik po API](#3-obszerny-przewodnik-po-api)
    - [3.1. Cykl życia wtyczki](#31-cykl-życia-wtyczki)
      - [`bool OnLoad()`](#bool-onload)
      - [`void OnUnload()`](#void-onunload)
      - [`unsigned int GetSupportFlags()`](#unsigned-int-getsupportflags)
      - [`void OnAmxLoad(AMX* amx)`](#void-onamxloadamx-amx)
      - [`void OnAmxUnload(AMX* amx)`](#void-onamxunloadamx-amx)
      - [`void OnProcessTick()`](#void-onprocesstick)
    - [3.2. Eksportowanie Funkcji Pluginu](#32-eksportowanie-funkcji-pluginu)
      - [Eksport dla MSVC (Visual Studio) z `Export_Plugin`](#eksport-dla-msvc-visual-studio-z-export_plugin)
      - [Eksport dla GCC / Clang z `SAMP_SDK_EXPORT`](#eksport-dla-gcc--clang-z-samp_sdk_export)
    - [3.3. `Plugin_Public`: przechwytywanie zdarzeń Pawn](#33-plugin_public-przechwytywanie-zdarzeń-pawn)
      - [Składnia i deklaracja](#składnia-i-deklaracja)
      - [Automatyczne marszowanie parametrów](#automatyczne-marszowanie-parametrów)
      - [Kontrola przepływu: `PUBLIC_CONTINUE` vs `PUBLIC_STOP`](#kontrola-przepływu-public_continue-vs-public_stop)
      - [Ghost Callbacks](#ghost-callbacks)
    - [3.4. `Plugin_Native`: tworzenie funkcji natywnych w C++](#34-plugin_native-tworzenie-funkcji-natywnych-w-c)
      - [Składnia i stała sygnatura](#składnia-i-stała-sygnatura)
      - [Automatyczna rejestracja natywnych](#automatyczna-rejestracja-natywnych)
      - [Wyodrębnianie parametrów: `Register_Parameters` vs. `Native_Params`](#wyodrębnianie-parametrów-register_parameters-vs-native_params)
        - [`Register_Parameters(...)`](#register_parameters)
        - [`Native_Params` (pełne API: `Get`, `Get_REF`, `Set_REF`)](#native_params-pełne-api-get-get_ref-set_ref)
          - [`p.Count()`](#pcount)
          - [`p.Get<T>(size_t index)`](#pgettsize_t-index)
          - [`p.Get_REF<T>(size_t index, T& out_value)`](#pget_reftsize_t-index-t-out_value)
          - [`p.Get_REF<T>(size_t index)` (C++17+)](#pget_reftsize_t-index-c17)
          - [`p.Set_REF<T>(size_t index, T value)`](#pset_reftsize_t-index-t-value)
      - [Zwracanie wartości](#zwracanie-wartości)
    - [3.5. `Plugin_Native_Hook`: przechwytywanie istniejących natywnych funkcji SA-MP](#35-plugin_native_hook-przechwytywanie-istniejących-natywnych-funkcji-sa-mp)
      - [Składnia i stała sygnatura](#składnia-i-stała-sygnatura-1)
      - [Rejestracja i aktywacja hooka](#rejestracja-i-aktywacja-hooka)
      - [Wywołanie oryginalnej funkcji natywnej (łańcuch hooków): `Call_Original_Native`](#wywołanie-oryginalnej-funkcji-natywnej-łańcuch-hooków-call_original_native)
      - [Kompletny przykład `Plugin_Native_Hook`](#kompletny-przykład-plugin_native_hook)
    - [3.6. Makra `Pawn_*`: wywoływanie funkcji Pawn z C++](#36-makra-pawn_-wywoływanie-funkcji-pawn-z-c)
      - [`Pawn_Native(NativeName, ...)`](#pawn_nativenativename-)
      - [`Pawn_Public(PublicName, ...)`](#pawn_publicpublicname-)
      - [`Pawn(FunctionName, ...)`](#pawnfunctionname-)
      - [Składnia i konwencje](#składnia-i-konwencje)
      - [Marszowanie parametrów wejściowych](#marszowanie-parametrów-wejściowych)
      - [Marszowanie parametrów wyjściowych (referencje: `int&`, `float&`, `std::string&`)](#marszowanie-parametrów-wyjściowych-referencje-int-float-stdstring)
      - [Obiekt `Callback_Result`: pełna analiza](#obiekt-callback_result-pełna-analiza)
    - [3.7. `Plugin_Module`: zarządzanie dynamicznymi modułami](#37-plugin_module-zarządzanie-dynamicznymi-modułami)
      - [Składnia i cel](#składnia-i-cel)
      - [Cykl życia modułu](#cykl-życia-modułu)
      - [Korzyści z modularizacji](#korzyści-z-modularizacji)
    - [3.8. `Plugin_Call`: wywoływanie wewnętrznych natywnych funkcji wtyczki](#38-plugin_call-wywoływanie-wewnętrznych-natywnych-funkcji-wtyczki)
      - [Składnia i zalety wydajności](#składnia-i-zalety-wydajności)
    - [3.9. Funkcje narzędziowe SDK](#39-funkcje-narzędziowe-sdk)
      - [`Samp_SDK::Log(const char* format, ...)`](#samp_sdklogconst-char-format-)
      - [`std::string Plugin_Format(const char* format, ...)` (zalecane)](#stdstring-plugin_formatconst-char-format--zalecane)
      - [`std::string Samp_SDK::Format(const char* format, ...)` (szczegół implementacji)](#stdstring-samp_sdkformatconst-char-format--szczegół-implementacji)
      - [`std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`](#stdstring-samp_sdkget_stringamx-amx-cell-amx_addr)
  - [4. Kompilacja i wdrożenie](#4-kompilacja-i-wdrożenie)
    - [Wymagania architektury i platformy](#wymagania-architektury-i-platformy)
    - [Przykłady poleceń kompilacji](#przykłady-poleceń-kompilacji)
      - [**MSVC (Visual Studio)**](#msvc-visual-studio)
      - [**GCC / Clang (Linux)**](#gcc--clang-linux)
      - [**GCC / Clang (MinGW w systemie Windows)**](#gcc--clang-mingw-w-systemie-windows)
    - [Wskazówki dotyczące dystrybucji](#wskazówki-dotyczące-dystrybucji)
  - [Licencja](#licencja)
    - [Warunki użytkowania](#warunki-użytkowania)
      - [1. Przyznane uprawnienia](#1-przyznane-uprawnienia)
      - [2. Obowiązkowe warunki](#2-obowiązkowe-warunki)
      - [3. Prawa autorskie](#3-prawa-autorskie)
      - [4. Wyłączenie gwarancji i ograniczenie odpowiedzialności](#4-wyłączenie-gwarancji-i-ograniczenie-odpowiedzialności)

## 1. Wprowadzenie i filozofia projektowania

### Problem ze standardowym API C SA-MP

API wtyczek SA-MP to interfejs programowania w języku C. Choć funkcjonalny i podstawowy, stwarza on wyzwania związane z programowaniem niskopoziomowym:
- **Ręczne zarządzanie pamięcią:** Funkcje takie jak `amx_Allot` i `amx_Release` wymagają od programisty jawnego alokowania i zwalniania pamięci na stercie AMX. Jest to częsta przyczyna wycieków pamięci i błędów wykonawczych.
- **Słabe typowanie i ręczne konwersje:** Parametry są przekazywane jako tablica `cell`s, wymuszając jawne (i często niebezpieczne) konwersje między `cell`, `int`, `float` i `char*`.
- **Wielomówność i boilerplate:** Wyodrębnianie wielu parametrów z tablicy `cell* params`, obsługa długości ciągów znaków i zarządzanie stosem AMX dla wywołań zwrotnych C++ do Pawn wymaga powtarzającego się kodu.
- **Kruchość interfejsu:** Brak sprawdzania typów w czasie kompilacji (type safety) oznacza, że błędy w przekazywaniu parametrów lub typów mogą pozostać niezauważone aż do wykonania, powodując awarie lub niezdefiniowane zachowanie.

### Rozwiązanie SA-MP SDK: abstrakcja z bezpieczeństwem i wydajnością

SA-MP SDK rozwiązuje te problemy, dostarczając potężną warstwę abstrakcji w C++:
- **RAII (Resource Acquisition Is Initialization):** Automatyczne zarządzanie pamięcią w AMX. `Amx_Scoped_Memory` gwarantuje, że zaalokowana pamięć zostanie zwolniona.
- **Bezpieczeństwo typów:** Automatyczna i bezpieczna konwersja parametrów między C++ a Pawn. Działasz bezpośrednio z `int`, `float`, `std::string`.
- **Zwięzła i idiomatyczna składnia:** Makra i szablony zapewniają czyste API, które bardziej przypomina nowoczesne C++ niż tradycyjne API C.
- **Solidne przechwytywanie:** Zaawansowany silnik hakowania umożliwia przezroczyste przechwytywanie wywołań zwrotnych Pawn (`Plugin_Public`), tworzenie nowych natywnych (`Plugin_Native`) oraz **hakowanie i łączenie istniejących natywnych funkcji SA-MP (`Plugin_Native_Hook`)**.
- **Wysoka wydajność:** Szerokie wykorzystanie haszowania w czasie kompilacji (FNV1a), buforowanie funkcji i optymalizacje `thread_local` w celu zminimalizowania narzutu abstrakcji.

### Model tylko nagłówkowy: zalety i implikacje

SDK składa się wyłącznie z plików nagłówkowych (`.hpp`, `.h`).
- **Zalety:**
   - **Uproszczona integracja:** Brak bibliotek do zbudowania, połączenia lub dystrybucji. Wystarczy dołączyć nagłówki.
   - **Optymalizacje kompilatora:** Kompilator ma pełny wgląd w kod SDK i twojej wtyczki, co pozwala na agresywne wbudowywanie i optymalizacje czasu linkowania, co może skutkować szybszymi binariami.
- **Implikacje:**
   - **Czas kompilacji:** W przypadku bardzo dużych projektów kompilacja może trwać dłużej z powodu wielokrotnego dołączania kodu SDK. Jest to łagodzone przez strażników dołączeń i zasadę C++ „dołączaj tylko to, co jest potrzebne”.
   - **Makra implementacyjne:** Konieczność makra `SAMP_SDK_IMPLEMENTATION` jest konsekwencją modelu tylko nagłówkowego, aby uniknąć redefinicji symboli.

## 2. Konfiguracja i środowisko

### Wymagania kompilacji

- **Kompilator C++:** Zgodny z C++17 lub nowszym.
   - GCC (wersja 8+)
   - Clang (wersja 5+)
   - MSVC (Visual Studio 2017+)
- **Architektura:** **x86 (32-bit)**. SA-MP działa wyłącznie na tej architekturze. SDK zawiera sprawdzenia w pliku `platform.hpp`, które spowodują błędy kompilacji w przypadku wykrycia nieprawidłowej architektury.
- **System operacyjny:** Windows lub Linux.

### Zalecana struktura plików

Dla przejrzystości i organizacji, powszechne jest organizowanie SDK w podfolderze `samp-sdk`.

```
meu_plugin/
├── samp-sdk/
│   ├── // Outros arquivos do SDK
│   └── samp_sdk.hpp // Główny nagłówek do dołączenia
│
├── src/
│   ├── main.cpp // Gdzie definiuje się SAMP_SDK_IMPLEMENTATION
│   └── my_custom_logic.cpp // Opcjonalnie, do organizacji kodu
│
└── CMakeLists.txt (ou .vcxproj, Makefile)
```

### Podstawowe makra konfiguracyjne

Zawsze definiuj te makra *przed* dołączeniem `samp_sdk.hpp`.

#### `SAMP_SDK_IMPLEMENTATION`

- **Cel:** Sygnalizuje kompilatorowi, że ten plik `.cpp` powinien generować implementacje funkcji eksportowych wtyczki (`Supports`, `Load`, `Unload`, `AmxLoad`, `AmxUnload`, `ProcessTick`). **SDK automatycznie zajmuje się eksportem tych funkcji, eliminując potrzebę plików `.def` (w systemie Windows) lub deklaracji `__attribute__((visibility("default")))` (w systemie Linux) dla tych funkcji.**
- **Wpływ techniczny:** Bez tego makra linker nie znajdzie wymaganych eksportów, a serwer SA-MP nie będzie w stanie załadować Twojej wtyczki.
- **Podstawowa zasada:** **Zdefiniuj to makro w TYLKO JEDNYM pliku `.cpp` w całym swoim projekcie.** Zdefiniowanie go w więcej niż jednym pliku spowoduje błąd linkowania „zduplikowanego symbolu”.

```cpp
// main.cpp
#define SAMP_SDK_IMPLEMENTATION // Makro powoduje, że SDK automatycznie eksportuje wymagane funkcje.
#include "samp-sdk/samp_sdk.hpp"

// ... twój kod wtyczki ...
```

#### `SAMP_SDK_WANT_AMX_EVENTS`

- **Cel:** Włącza wywołania zwrotne cyklu życia skryptu Pawn (`OnAmxLoad`, `OnAmxUnload`) oraz możliwość tworzenia nowych funkcji natywnych w C++ (`Plugin_Native`).
- **Włączone funkcje:**
   - Wywołania zwrotne `OnAmxLoad(AMX* amx)` i `OnAmxUnload(AMX* amx)`.
   - Deklarowanie i rejestrowanie nowych natywnych funkcji C++ za pomocą `Plugin_Native`.
   - Makro `Plugin_Call` do wywoływania natywnych funkcji stworzonych za pomocą `Plugin_Native` wewnątrz własnej wtyczki.
- **Wpływ techniczny:** Kiedy to makro jest zdefiniowane, SDK automatycznie zbiera wszystkie Twoje `Plugin_Native`s. W funkcji `Supports()`, flaga `SUPPORTS_AMX_NATIVES` jest automatycznie dodawana, jeśli w Twoim projekcie znajdują się jakieś `Plugin_Native`s.
- **Elastyczność:** **Możesz zdefiniować to makro w wielu plikach `.cpp`**. System rejestracji statycznej SDK skonsoliduje wszystkie natywne z różnych jednostek kompilacji w jedną globalną listę.

```cpp
// my_natives.cpp (może być oddzielnym plikiem od main.cpp)
#define SAMP_SDK_WANT_AMX_EVENTS // Tylko do włączenia Plugin_Native i wywołań zwrotnych OnAmxLoad/OnAmxUnload
#include "samp-sdk/samp_sdk.hpp"

Plugin_Native(MyCustomNative, AMX* amx, cell* params) {
    // ...
    return 0;
}
```

#### `SAMP_SDK_WANT_PROCESS_TICK`

- **Cel:** Włącza wywołanie zwrotne `OnProcessTick()`, które jest regularnie wywoływane przez serwer.
- **Wpływ techniczny:** Automatycznie dodaje flagę `SUPPORTS_PROCESS_TICK` w funkcji `Supports()`.

```cpp
// main.cpp
#define SAMP_SDK_IMPLEMENTATION
#define SAMP_SDK_WANT_PROCESS_TICK
#include "samp-sdk/samp_sdk.hpp"

void OnProcessTick() {
    // Logika wykonywana co "takt" serwera (np. 20 ms)
    // Ostrożnie z ciężkimi operacjami tutaj!
}
```

### Definicje i stałe SA-MP (`samp_defs.hpp`)

Ten plik dostarcza wszystkie znane stałe i limity SA-MP, takie jak `MAX_PLAYERS`, `INVALID_PLAYER_ID`, `PLAYER_STATE_ONFOOT`, `WEAPON_DEAGLE`, `DIALOG_STYLE_LIST` itp. Jest automatycznie dołączany przez `samp_sdk.hpp` i powinien być używany do zapewnienia kompatybilności i czytelności kodu.

## 3. Obszerny przewodnik po API

### 3.1. Cykl życia wtyczki

Poniższe funkcje są punktami wejścia i wyjścia Twojej wtyczki, automatycznie eksportowanymi przez SDK.

#### `bool OnLoad()`

- **Opis:** Pierwsza funkcja wywoływana przez serwer SA-MP po pomyślnym załadowaniu Twojej wtyczki do pamięci.
- **Użycie:** Idealne do inicjalizacji dowolnego systemu, ładowania konfiguracji, otwierania połączeń z bazami danych lub ładowania modułów (`Plugin_Module`).
- **Zwraca:**
   - `true`: Wtyczka została pomyślnie zainicjowana, a ładowanie jest kontynuowane.
   - `false`: Wtyczka nie powiodła się podczas inicjalizacji. Ładowanie zostanie przerwane, a wtyczka zostanie odładowana.

```cpp
// main.cpp
bool OnLoad() {
    Samp_SDK::Log("Inicializando MeuPlugin v1.0...");

    // Przykład: Ładowanie modułu (więcej szczegółów w sekcji 3.6)
    if (!Plugin_Module("my_database_module", "plugins/db_connector", "Módulo de Banco de Dados carregado.")) {
        Samp_SDK::Log("ERRO: Falha ao carregar o módulo de banco de dados!");

        return false; // Przerywa ładowanie głównej wtyczki
    }

    return true;
}
```

#### `void OnUnload()`

- **Opis:** Ostatnia funkcja wywoływana przez serwer SA-MP przed odładowaniem Twojej wtyczki z pamięci.
- **Użycie:** Idealne do czyszczenia zasobów, zamykania połączeń, zapisywania stanów i zapewniania, że żadne zasoby nie wyciekną. SDK automatycznie zarządza odładowywaniem modułów (`Plugin_Module`).

```cpp
// main.cpp
void OnUnload() {
    Samp_SDK::Log("MeuPlugin descarregado. Liberando recursos...");
    // Nie są wymagane żadne ręczne działania dla modułów ładowanych za pomocą Plugin_Module;
    // SDK zajmuje się tym.
}
```

#### `unsigned int GetSupportFlags()`

- **Opis:** Informuje serwer SA-MP, które funkcje Twoja wtyczka obsługuje i chce używać.
- **Użycie:** **Zawsze zwracaj `SUPPORTS_VERSION` (lub `SAMP_PLUGIN_VERSION`).** Flagi `SUPPORTS_AMX_NATIVES` i `SUPPORTS_PROCESS_TICK` są automatycznie dodawane przez SDK, jeśli istnieją `Plugin_Native`s i/lub jeśli makro `SAMP_SDK_WANT_PROCESS_TICK` jest zdefiniowane, odpowiednio. Upraszcza to konserwację i zapobiega błędom.

```cpp
// main.cpp
unsigned int GetSupportFlags() {
    return SUPPORTS_VERSION; // SDK automatycznie dodaje niezbędne flagi.
}
```

#### `void OnAmxLoad(AMX* amx)`

- **Wymaga:** `SAMP_SDK_WANT_AMX_EVENTS`
- **Opis:** Wywoływana za każdym razem, gdy nowy skrypt Pawn (Gamemode lub Filterscript) jest ładowany i inicjowany na serwerze.
- **Użycie:** Jeśli potrzebujesz specyficznej logiki dla każdego skryptu AMX lub chcesz zainicjować dane specyficzne dla skryptu.

```cpp
// main.cpp (z zdefiniowanym SAMP_SDK_WANT_AMX_EVENTS)
void OnAmxLoad(AMX* amx) {
    // amx reprezentuje nową, załadowaną instancję skryptu.
    Samp_SDK::Log("Script AMX carregado: %p", (void*)amx);
}
```

#### `void OnAmxUnload(AMX* amx)`

- **Wymaga:** `SAMP_SDK_WANT_AMX_EVENTS`
- **Opis:** Wywoływana, gdy skrypt Pawn jest odładowywany z serwera.
- **Użycie:** Do czyszczenia wszelkich zasobów, które zaalokowałeś lub powiązałeś z danym `AMX*`.

```cpp
// main.cpp (z zdefiniowanym SAMP_SDK_WANT_AMX_EVENTS)
void OnAmxUnload(AMX* amx) {
    Samp_SDK::Log("Script AMX descarregado: %p", (void*)amx);
}
```

#### `void OnProcessTick()`

- **Wymaga:** `SAMP_SDK_WANT_PROCESS_TICK`
- **Opis:** Wywoływana wielokrotnie co "takt" serwera (zazwyczaj 20 razy na sekundę, czyli co 50 ms).
- **Użycie:** Do ciągłej logiki w tle, timerów, aktualizacji stanu, które nie zależą od zdarzeń graczy, lub synchronizacji danych.
- **Ostrożnie:** Unikaj operacji blokujących lub wymagających dużej mocy obliczeniowej, ponieważ mogą one powodować opóźnienia na serwerze.

```cpp
// main.cpp (z zdefiniowanym SAMP_SDK_WANT_PROCESS_TICK)
static int tick_count = 0;

void OnProcessTick() {
    tick_count++;

    if (tick_count % 200 == 0) // Co 10 sekund (20 taktów/s * 10 s = 200 taktów)
        Samp_SDK::Log("Servidor ativo por %d segundos.", tick_count / 20);
}
```

### 3.2. Eksportowanie Funkcji Pluginu

Aby serwer SA-MP mógł wywoływać funkcje twojego pluginu (`Load`, `Supports`, itp.), muszą one zostać "wyeksportowane" z pliku DLL (Windows) lub SO (Linux). SDK automatyzuje eksport standardowych funkcji cyklu życia, ale również dostarcza narzędzia, dzięki którym możesz eksportować własne niestandardowe funkcje, jeśli potrzebujesz interoperacyjności z innymi programami.

Metoda eksportowania funkcji różni się w zależności od kompilatora.

#### Eksport dla MSVC (Visual Studio) z `Export_Plugin`

W systemie Windows z MSVC najłatwiejszym sposobem eksportowania niestandardowych funkcji jest użycie makra `Export_Plugin`, zdefiniowanego w `exports.hpp`.

- **Składnia:** `Export_Plugin("Funkcja", "Stos")`
- **`Funkcja`**: Dokładna nazwa funkcji do wyeksportowania.
- **`Stos`**: Całkowita liczba bajtów, które parametry funkcji zajmują na stosie. Dla konwencji `__stdcall` (standard SDK w systemie Windows) obliczenie to `4 * (Liczba Parametrów)`.

```cpp
#include "samp-sdk/exports.hpp"

// Przykład: Eksportowanie niestandardowej funkcji, która mogłaby być wywołana
// przez inny program lub plugin, który zna jej sygnaturę.
const char* SAMP_SDK_CALL GetPluginVersion() {
    return "1.0.0";
}

Export_Plugin("GetPluginVersion", "0");
```

> [!WARNING]
> **Ograniczenie `Export_Plugin`**
> To makro działa **tylko z kompilatorem MSVC (Visual Studio)**. Wykorzystuje dyrektywę `#pragma` specyficzną dla Microsoft, która jest ignorowana przez inne kompilatory takie jak GCC i Clang.

#### Eksport dla GCC / Clang z `SAMP_SDK_EXPORT`

Dla GCC i Clang (w systemie Windows lub Linux) eksport jest zarządzany przez makro `SAMP_SDK_EXPORT`, zdefiniowane w `platform.hpp`. Po prostu umieszczasz je przed definicją funkcji.

- **Mechanizm:** W systemie Linux dodaje `__attribute__((visibility("default")))`. W systemie Windows z GCC/Clang dodaje `__attribute__((dllexport))`.
- **Użycie:** SDK już stosuje `SAMP_SDK_EXPORT` do wszystkich funkcji cyklu życia (`Load`, `Unload`, itp.), więc ich eksport jest w pełni automatyczny dla tych kompilatorów. Dla swoich niestandardowych funkcji po prostu zrób to samo.

```cpp
// Dla GCC/Clang definicja funkcji z SAMP_SDK_EXPORT jest wystarczająca.
SAMP_SDK_EXPORT const char* SAMP_SDK_CALL GetPluginVersion() {
    return "1.0.0";
}
```

### 3.3. `Plugin_Public`: przechwytywanie zdarzeń Pawn

Makro `Plugin_Public` jest głównym pomostem do odbierania wywołań zwrotnych z Pawn w Twoim kodzie C++.

#### Składnia i deklaracja

- `Plugin_Public(NazwaPubliczna, Typ1 Param1, Typ2 Param2, ...)`
- Nazwa funkcji C++, którą deklarujesz, **musi być taka sama** jak nazwa wywołania zwrotnego Pawn (np. `OnPlayerConnect`).
- Typy parametrów C++ (`int`, `float`, `std::string`) są automatycznie konwertowane przez SDK.

```cpp
// Przechwytuje OnPlayerText(playerid, text[])
Plugin_Public(OnPlayerText, int playerid, std::string text) {
    Samp_SDK::Log("Jogador %d disse: %s", playerid, text.c_str());

    return PUBLIC_CONTINUE;
}
```

#### Automatyczne marszowanie parametrów

SDK automatycznie obsługuje odczytywanie stosu `cell` AMX i konwersję do określonych typów C++:
- `int`: Konwertowane bezpośrednio z `cell`.
- `float`: Konwertowane z `cell` za pomocą `amx::AMX_CTOF`.
- `std::string`: SDK odczytuje adres ciągu znaków w AMX, alokuje `std::string` w C++ i kopiuje zawartość.

#### Kontrola przepływu: `PUBLIC_CONTINUE` vs `PUBLIC_STOP`

Wartość zwracana przez Twoją funkcję `Plugin_Public` jest kluczowa i określa przepływ wykonania wywołania zwrotnego:
- `return PUBLIC_CONTINUE;` (wartość `1`): Wskazuje, że wykonanie wywołania zwrotnego powinno być **kontynuowane**. Jeśli istnieją inne wtyczki, które również przechwytują to wywołanie zwrotne, zostaną one wywołane (w odwrotnej kolejności ładowania). Następnie zostanie wywołana oryginalna `public` w skrypcie Pawn.
- `return PUBLIC_STOP;` (wartość `0`): Wskazuje, że wykonanie wywołania zwrotnego powinno zostać **przerwane**. Żadna inna wtyczka (o niższym priorytecie) ani oryginalna `public` w skrypcie Pawn nie zostanie wywołana dla tego zdarzenia. Jest to idealne rozwiązanie do implementacji systemu, który „nadpisuje” lub „blokuje” standardowe zachowanie SA-MP.

```cpp
// main.cpp
Plugin_Public(OnPlayerCommandText, int playerid, std::string cmdtext) {
    if (cmdtext == "/freeze") {
        Pawn_Native(TogglePlayerControllable, playerid, 0); // Zamraża gracza
        Pawn_Native(SendClientMessage, playerid, -1, Plugin_Format("Jogador %d congelado.", playerid));

        return PUBLIC_STOP; // Zapobiega przetwarzaniu polecenia przez inne skrypty.
    }

    return PUBLIC_CONTINUE; // Pozwala na przetwarzanie innych poleceń.
}
```

#### Ghost Callbacks

Zaawansowaną funkcją `Plugin_Public` jest obsługa „Ghost Callbacks”. Oznacza to, że możesz przechwycić wywołanie zwrotne Pawn, nawet jeśli **nie jest ono obecne** w skrypcie `.amx` trybu gry lub skryptu filtrującego. SDK „oszukuje” serwer, aby i tak wywołał Twój hook C++. Jest to przydatne w przypadku wywołań zwrotnych wewnętrznych lub do tworzenia nowych funkcji bez zależności od obecności `public` w skrypcie Pawn.

```cpp
// Możesz zdefiniować wywołanie zwrotne, którego skrypt Pawn nie posiada, ale Twoja wtyczka będzie go nasłuchiwać.
Plugin_Public(OnMyCustomInternalEvent, int data1, float data2) {
    Samp_SDK::Log("Evento interno customizado recebido: %d, %.2f", data1, data2);

    return PUBLIC_CONTINUE;
}

// Aby "wyzwolić" to zdarzenie z innego miejsca w Twoim kodzie C++:
// Pawn_Public(OnMyCustomInternalEvent, 123, 45.67f);
// Wywołanie trafi do Twojego Plugin_Public powyżej, nawet jeśli w Pawn nie ma OnMyCustomInternalEvent.
```

### 3.4. `Plugin_Native`: tworzenie funkcji natywnych w C++

`Plugin_Native` pozwala rozszerzyć funkcjonalność Pawn o wysokowydajny kod C++.

#### Składnia i stała sygnatura

- `Plugin_Native(NativeName, AMX* amx, cell* params)`
- Funkcja C++ musi mieć dokładnie tę sygnaturę: `cell NativeName(AMX* amx, cell* params)`.
- `NativeName` to nazwa, której będą używać skrypty Pawn.

```cpp
// Pawn: native GetPlayerPingAverage(playerid);
Plugin_Native(GetPlayerPingAverage, AMX* amx, cell* params) {
    // ... Implementacja ...
    return 0;
}
```

#### Automatyczna rejestracja natywnych

> [!NOTE]
> **Nie musisz** ręcznie wywoływać `amx_Register`. SDK wykrywa wszystkie Twoje `Plugin_Native`s (w dowolnym pliku `.cpp`, który dołączył `samp_sdk.hpp` i zdefiniował `SAMP_SDK_WANT_AMX_EVENTS`) i automatycznie rejestruje je w każdym załadowanym skrypcie AMX (`OnAmxLoad`).

#### Wyodrębnianie parametrów: `Register_Parameters` vs. `Native_Params`

##### `Register_Parameters(...)`

- **Opis:** Prostszy pomocnik do sekwencyjnego wyodrębniania wielu parametrów.
- **Użycie:** `Register_Parameters(zmienna1, zmienna2, ...)`
- **Ograniczenia:** Dotyczy parametrów wejściowych. Nie obsługuje parametrów opcjonalnych ani dostępu według indeksu.
- **Obsługiwane typy:** `int`, `float`, `std::string`.

```cpp
// Pawn: native SetPlayerSkinAndMoney(playerid, skinid, money);
Plugin_Native(SetPlayerSkinAndMoney, AMX* amx, cell* params) {
    int playerid, skinid, money;
    Register_Parameters(playerid, skinid, money); // Wyodrębnia 3 parametry
    
    Pawn_Native(SetPlayerSkin, playerid, skinid);
    Pawn_Native(GivePlayerMoney, playerid, money);
    
    return 1;
}
```

##### `Native_Params` (pełne API: `Get`, `Get_REF`, `Set_REF`)

- **Opis:** Klasa opakowująca, która zapewnia obiektowy interfejs do dostępu do parametrów natywnej funkcji. Potężniejsza dla złożonych scenariuszy.
- **Konstrukcja:** `Native_Params p(amx, params);`

###### `p.Count()`

- **Opis:** Zwraca liczbę parametrów przekazanych do natywnej funkcji.
- **Użycie:** Niezbędne do obsługi parametrów opcjonalnych.

###### `p.Get<T>(size_t index)`

- **Opis:** Wyodrębnia parametr wejściowy według indeksu i konwertuje go na typ `T`.
- **Obsługiwane typy:** `int`, `float`, `std::string`.

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

- **Opis:** Pobiera wartość parametru **referencyjnego** (wskaźnik Pawn) i przechowuje ją w `out_value`.
- **Użycie:** Do odczytywania wartości, które zostały przekazane przez referencję z Pawn.
- **Zwraca:** `true`, jeśli adres AMX jest prawidłowy, `false` w przeciwnym razie.

```cpp
// Pawn: native CheckPlayerStats(playerid, &Float:health, &money);
Plugin_Native(CheckPlayerStats, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    
    int playerid = p.Get<int>(0);
    float health = 0.0f;
    int money = 0;

    // Pobiera wartości referencji (Pawn przekazał adresy)
    p.Get_REF(1, health); // Odczytuje wartość Float:health
    p.Get_REF(2, money);   // Odczytuje wartość money
    
    Samp_SDK::Log("Jogador %d, Health: %.1f, Money: %d", playerid, health, money);
    
    // Teraz je modyfikujemy
    health = 50.0f;
    money += 100;
    
    // I zapisujemy z powrotem do pamięci Pawn
    p.Set_REF(1, health);
    p.Set_REF(2, money);
    
    return 1;
}
```

###### `p.Get_REF<T>(size_t index)` (C++17+)

- **Opis:** Zwraca `std::optional<T>` do odczytania parametru referencyjnego. Bezpieczniejsze dla C++17 i nowszych.

###### `p.Set_REF<T>(size_t index, T value)`

- **Opis:** Zapisuje wartość `T` do parametru **referencyjnego** Pawn (adres, który Pawn przekazał).
- **Użycie:** Do modyfikacji wartości, które zostały przekazane przez referencję, sprawiając, że Pawn widzi zmianę.
- **Zwraca:** `true`, jeśli zapis powiódł się, `false` w przeciwnym razie.

#### Zwracanie wartości

- Twoja funkcja `Plugin_Native` musi zwracać `cell`.
- Aby zwrócić `int` lub `bool`, użyj rzutowania na `cell`.
- Aby zwrócić `float`, użyj `amx::AMX_FTOC(mój_float)`.

```cpp
// Zwraca bool
Plugin_Native(IsPlayerSpawned, AMX* amx, cell* params) {
    int playerid;
    Register_Parameters(playerid);

    return (Pawn_Native(GetPlayerState, playerid) == PLAYER_STATE_SPAWNED) ? 1 : 0;
}

// Zwraca float
Plugin_Native(GetPlayerMaxHealth, AMX* amx, cell* params) {
    return amx::AMX_FTOC(100.0f); // Zwraca 100.0f
}
```

### 3.5. `Plugin_Native_Hook`: przechwytywanie istniejących natywnych funkcji SA-MP

Makro `Plugin_Native_Hook` pozwala przechwycić i zmodyfikować zachowanie dowolnej istniejącej funkcji natywnej SA-MP lub innych wtyczek. Jest to potężny mechanizm do rozszerzania lub zmiany standardowej logiki serwera.

#### Składnia i stała sygnatura

- `Plugin_Native_Hook(NativeName, AMX* amx, cell* params)`
- Funkcja C++ musi mieć dokładnie tę sygnaturę: `cell NativeName(AMX* amx, cell* params)`.
- `NativeName` musi być dokładną nazwą natywnej funkcji, którą chcesz zahakować (np. `SendClientMessage`, `SetPlayerPos`).

```cpp
// Przechwytuje natywną funkcję SendClientMessage
Plugin_Native_Hook(SendClientMessage, AMX* amx, cell* params) {
    // ...
    return Call_Original_Native(SendClientMessage); // Ważne, aby wywołać oryginalną
}
```

#### Rejestracja i aktywacja hooka

> [!NOTE]
> **Nie musisz** ręcznie wywoływać `amx_Register` ani definiować `SAMP_SDK_WANT_AMX_EVENTS` specjalnie dla `Plugin_Native_Hook`. SDK automatycznie wykrywa i rejestruje Twoje hooki. Przy pierwszym uruchomieniu skryptu AMX, SDK zastępuje wskaźnik natywnej funkcji w tabeli "trampoliną", która przekierowuje do Twojej funkcji `Plugin_Native_Hook`. Ten proces zapewnia bezpieczne łączenie hooków z wielu wtyczek.

#### Wywołanie oryginalnej funkcji natywnej (łańcuch hooków): `Call_Original_Native`

Wewnątrz funkcji `Plugin_Native_Hook` **MUSISZ** użyć makra `Call_Original_Native(NativeName)` do wywołania oryginalnej funkcji (lub kolejnego hooka w łańcuchu). Jest to kluczowe dla:
- **Zachowania funkcjonalności:** Jeśli nie wywołasz oryginalnej funkcji, zahakowana funkcja natywna po prostu przestanie działać dla innych wtyczek lub serwera.
- **Łączenia hooków:** Pozwala wielu wtyczkom zahakować tę samą funkcję natywną i wykonanie wszystkich hooków w sekwencji.
- **Manipulacji wartością zwracaną:** Możesz sprawdzić, a nawet zmodyfikować wartość zwracaną przez `Call_Original_Native` przed zwróceniem jej z funkcji hooka.

```cpp
// Przykład: blokowanie SendClientMessage, jeśli zawiera określone słowo
Plugin_Native_Hook(SendClientMessage, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    
    // Wyodrębnia parametry do analizy
    int playerid = p.Get<int>(0);
    // int color = p.Get<int>(1); // Nie potrzebujemy koloru do tej logiki
    std::string message = p.Get_String(2); // Pobiera ciąg znaków wiadomości

    if (message.find("BADWORD") != std::string::npos) {
        Samp_SDK::Log("MENSAGEM BLOQUEADA para playerid %d: %s", playerid, message.c_str());

        return 0; // Zwraca 0 (false) do Pawn, wskazując, że wiadomość nie została wysłana.
                  // I co ważniejsze, NIE wywołujemy Call_Original_Native, blokując wiadomość.
    }

    // Jeśli wiadomość nie zawiera zakazanego słowa, wywołujemy oryginalną funkcję natywną
    // i zwracamy jej wartość, zapewniając, że wiadomość zostanie wysłana normalnie
    // i że inne hooki (jeśli istnieją) zostaną wykonane.
    return Call_Original_Native(SendClientMessage);
}
```

#### Kompletny przykład `Plugin_Native_Hook`

```cpp
#define SAMP_SDK_IMPLEMENTATION
// SAMP_SDK_WANT_AMX_EVENTS nie jest ściśle wymagane dla hooków, ale jest często używane do obsługi OnAmxLoad/Unload
// #define SAMP_SDK_WANT_AMX_EVENTS 
#include "samp-sdk/samp_sdk.hpp"

// Hook dla natywnej funkcji CreateVehicle
Plugin_Native_Hook(CreateVehicle, AMX* amx, cell* params) {
    Native_Params p(amx, params);

    // Wyodrębnia parametry natywnej funkcji CreateVehicle do inspekcji
    int modelid = p.Get<int>(0);
    float x = p.Get<float>(1);
    float y = p.Get<float>(2);
    float z = p.Get<float>(3);
    float angle = p.Get<float>(4);
    int color1 = p.Get<int>(5);
    int color2 = p.Get<int>(6);
    int respawn_delay = p.Get<int>(7);
    bool addsiren = p.Get<bool>(8);

    Samp_SDK::Log("HOOK: CreateVehicle chamado! Model: %d, Pos: (%.2f, %.2f, %.2f)", modelid, x, y, z);

    // Przykład, jak *zmodyfikować* parametr wejściowy
    // Jeśli model to 400 (Landstalker), zmieniamy go na 401 (Bravura)
    if (modelid == 400) {
        // Modyfikujemy bezpośrednio tablicę 'params' dla oryginalnego wywołania
        params[1] = static_cast<cell>(401); // Model znajduje się na pozycji 0 w tablicy parametrów (params[1])
        Samp_SDK::Log("  -> Model 400 alterado para 401 antes da criação.");
    }
    
    // Wywołujemy oryginalną funkcję natywną (lub następny hook w łańcuchu) z ewentualnie zmodyfikowanymi parametrami
    cell original_retval = Call_Original_Native(CreateVehicle);

    Samp_SDK::Log("HOOK: CreateVehicle retornou: %d (ID do veículo)", (int)original_retval);

    // Tutaj możesz zmodyfikować wartość zwracaną przed zwróceniem jej do Pawn.
    // Przykład: jeśli tworzenie pojazdu nie powiodło się, zwróć niestandardowy nieprawidłowy ID.
    if ((int)original_retval == INVALID_VEHICLE_ID) {
        Samp_SDK::Log("  -> Criação de veículo falhou na native original.");

        return -1; // Zwraca inną wartość do Pawn.
    }

    return original_retval; // Zwraca wartość, którą zwróciła oryginalna natywna funkcja (lub zmodyfikowana powyżej).
}

unsigned int GetSupportFlags() {
    return SUPPORTS_VERSION; 
}

// Minimalne implementacje dla cyklu życia
bool OnLoad() {
    Samp_SDK::Log("Plugin de Exemplo de Native Hook carregado!");
    return true;
}

void OnUnload() {
    Samp_SDK::Log("Plugin de Exemplo de Native Hook descarregado!");
}

// Te wywołania zwrotne będą dostępne tylko wtedy, gdy zdefiniowano SAMP_SDK_WANT_AMX_EVENTS
/*void OnAmxLoad(AMX* amx) {
    Samp_SDK::Log("AMX Load detectado: %p", (void*)amx);
}

void OnAmxUnload(AMX* amx) {
    Samp_SDK::Log("AMX Unload detectado: %p", (void*)amx);
}*/
```
> [!WARNING]
> Bezpośrednia manipulacja tablicą `cell* params` w celu zmiany parametrów wejściowych wymaga ostrożności. Upewnij się, że rozumiesz kolejność i typy parametrów. W większości przypadków użycia `p.Get(...)` do inspekcji i `Call_Original_Native(...)` do kontynuowania łańcucha jest wystarczające. Bezpośrednia zmiana `params` powinna być wykonywana tylko wtedy, gdy wiesz, że parametr jest wartością i musi zostać zmodyfikowany dla oryginalnego wywołania. W przypadku ciągów znaków i tablic, modyfikacja jest bardziej złożona i zazwyczaj wymaga `amx::Set_String` do zapisu w istniejącym adresie lub realokacji, co może być łatwiejsze do zarządzania, wywołując funkcję natywną za pomocą `Pawn_Native` z nowymi wartościami i zwracając `0` z hooka, aby anulować oryginalne wywołanie.

### 3.6. Makra `Pawn_*`: wywoływanie funkcji Pawn z C++

Te makra są odwrotnością `Plugin_Public` i `Plugin_Native`: pozwalają Twojemu kodowi C++ wywoływać funkcje Pawn.

#### `Pawn_Native(NativeName, ...)`

- **Cel:** Zalecany sposób wywoływania natywnych funkcji SA-MP (lub innych wtyczek) z C++.
- **Mechanizm:** Wyszukuje wskaźnik natywnej funkcji w wewnętrznej pamięci podręcznej SDK (wypełnionej przez `Amx_Register_Detour`). Jeśli zostanie znaleziony, wykonuje natywną funkcję w środowisku `Amx_Sandbox` (fałszywa i izolowana instancja AMX).
- **Wydajność:** Najbardziej efektywna, ponieważ pozwala uniknąć kosztownego wyszukiwania `publics` i bezpośrednio współdziała ze wskaźnikiem natywnej funkcji.

#### `Pawn_Public(PublicName, ...)`

- **Cel:** Wywołuje określoną funkcję publiczną w skrypcie Pawn.
- **Mechanizm:** Przegląda instancje `AMX*` zarządzane przez `Amx_Manager`, wyszukuje `public` po nazwie i wykonuje ją.
- **Wydajność:** Mniej efektywna niż `Pawn_Native` z powodu wyszukiwania i rzeczywistego `amx_Exec`. Ogólnie, `publics` są wolniejsze niż `natives`.
- **Użycie:** Idealne do wywoływania niestandardowych zdarzeń w Twoich Gamemode/Filterscriptach, które nie są natywnymi funkcjami.

#### `Pawn(FunctionName, ...)`

- **Cel:** Wygodne makro, które próbuje odgadnąć, czy funkcja jest natywna czy publiczna.
- **Mechanizm:** Najpierw próbuje wywołać jako `Pawn_Native`. Jeśli to się nie uda (nie znaleziono natywnej funkcji), próbuje wywołać jako `Pawn_Public`.
- **Wydajność:** Może być nieco wolniejsza niż `Pawn_Native`, jeśli funkcja jest natywna, z powodu podwójnej próby wyszukiwania. W przypadku `publics` wydajność jest taka sama jak `Pawn_Public`.
- **Użycie:** Dla funkcji, w przypadku których nie masz pewności, czy są natywne czy publiczne, lub aby uniknąć powtarzania kodu, próbując jednej, a potem drugiej.

#### Składnia i konwencje

- **Nazwa funkcji:** Zawsze używaj nazwy funkcji Pawn **bezpośrednio, bez cudzysłowów**. SDK wewnętrznie przekonwertuje ją na ciąg znaków.
- **Parametry:** Przekazuj parametry C++ bezpośrednio.

```cpp
// Poprawnie:
Pawn_Native(SetPlayerPos, playerid, 100.0f, 200.0f, 300.0f); 

// Błędnie (ale technicznie zadziałałoby z powodu haszowania, unikaj):
Pawn_Native("SetPlayerPos", playerid, 100.0f, 200.0f, 300.0f); 
```

#### Marszowanie parametrów wejściowych

SDK konwertuje Twoje typy C++ na format `cell` AMX, zarządzając pamięcią w razie potrzeby:
- `int`, `bool`, `long`, `enum` -> `cell`
- `float`, `double` -> `cell` (używając `amx::AMX_FTOC`)
- `const char*`, `std::string`, `std::string_view` (C++17+) -> `cell` (alokuje pamięć w AMX, kopiuje ciąg znaków i przekazuje adres `amx_addr`)

```cpp
void Send_Formatted_Message(int playerid, const std::string& msg) {
    Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, msg);
}
```

#### Marszowanie parametrów wyjściowych (referencje: `int&`, `float&`, `std::string&`)

Jest to kluczowa funkcja zapewniająca wygodę i bezpieczeństwo. Dla funkcji Pawn, które oczekują wskaźnika (referencji), SDK automatyzuje cały proces alokacji/zwalniania pamięci i kopiowania danych.

- **Jak używać:** Wystarczy przekazać zmienną przez referencję (`&`).
- **Mechanizm:** SDK alokuje pamięć na stercie AMX, przekazuje adres AMX do funkcji Pawn, oczekuje, że funkcja Pawn wypełni ten adres, odczytuje wartość z powrotem i zwalnia pamięć AMX. Wszystko w sposób przezroczysty.
- **Z `std::string&`:** SDK alokuje standardowy bufor (256 komórek) w AMX dla ciągu znaków.

```cpp
void Get_Player_Location(int playerid) {
    float x, y, z;
    int interiorid, worldid;
    std::string name;

    Pawn_Native(GetPlayerPos, playerid, x, y, z);
    Pawn_Native(GetPlayerInterior, playerid, interiorid);
    Pawn_Native(GetPlayerVirtualWorld, playerid, worldid);
    Pawn_Native(GetPlayerName, playerid, name, MAX_PLAYER_NAME);

    Samp_SDK::Log("Localização de %s (ID:%d): Pos(%.2f, %.2f, %.2f) Interior:%d World:%d", name.c_str(), playerid, x, y, z, interiorid, worldid);
}
```

#### Obiekt `Callback_Result`: pełna analiza

Wszystkie wywołania `Pawn_*` zwracają obiekt `Callback_Result`. Obiekt ten jest bezpiecznym opakowaniem dla wyniku wywołania Pawn.

- `Callback_Result() noexcept`: Domyślny konstruktor, wskazuje na niepowodzenie (`success_ = false`).
- `Callback_Result(bool success, cell value) noexcept`: Konstruktor dla sukcesu lub niepowodzenia z wartością.
- `explicit operator bool() const`: Umożliwia użycie `if (result)` do sprawdzenia, czy wywołanie zakończyło się pomyślnie.
- `operator cell() const`: Umożliwia konwersję wyniku na `cell` w celu uzyskania wartości.
- `float As_Float() const`: Wygoda uzyskania wyniku jako `float`.
- `cell Value() const`: Zwraca surową wartość `cell`.
- `bool Success() const`: Zwraca `true`, jeśli wywołanie Pawn zakończyło się pomyślnie.
- `int Get_Amx_Error() const`: Zwraca kod błędu AMX, jeśli wywołanie zakończyło się niepowodzeniem (0 dla sukcesu).

```cpp
// Przykład: Pobieranie życia gracza.
// Natywna funkcja GetPlayerHealth(playerid, &Float:health) oczekuje playerid i referencji do życia.
int playerid = 0; // Przykładowe ID gracza
float player_health = 0.0f;

// Wywołujemy GetPlayerHealth, przekazując playerid i player_health przez referencję.
// SDK zajmie się marszowaniem dla parametru wyjściowego 'health'.
Callback_Result result = Pawn_Native(GetPlayerHealth, playerid, player_health);

if (result) { // Sprawdza, czy wywołanie zakończyło się pomyślnie (operator bool)
    // Wartość zwrócona przez result.As_Float() lub result (operator cell)
    // byłaby wartością zwracaną przez *natywną funkcję*, a nie parametrem wyjściowym.
    // Wartość życia została już zaktualizowana w 'player_health' dzięki marszowaniu parametru wyjściowego.
    Samp_SDK::Log("Jogador %d tem %.1f de vida.", playerid, player_health);
}
else {
    // Wywołanie nie powiodło się, być może gracz nie istnieje lub natywna funkcja nie została znaleziona.
    Samp_SDK::Log("Erro ao obter vida do jogador %d. Código AMX: %d", playerid, result.Get_Amx_Error());
}

// W przypadku natywnych funkcji, które zwracają wartość i używają parametrów wyjściowych (mniej powszechne, ale możliwe),
// użyłbyś obu:
// Callback_Result other_result = Pawn_Native(SomeNative, param1, output_param, param2);
// if (other_result) {
//     cell returned_value = other_result;
//     // output_param jest już zaktualizowany
// }
```

### 3.7. `Plugin_Module`: zarządzanie dynamicznymi modułami

Makro `Plugin_Module` pozwala Twojej wtyczce działać jako „ładowarka” dla innych wtyczek, tworząc modułową i rozszerzalną architekturę. Moduł załadowany w ten sposób jest traktowany jako pełnoprawna wtyczka, z własnym cyklem życia zdarzeń zarządzanym przez wtyczkę-hosta.

#### Składnia i cel

- `Plugin_Module(const char* nazwa_pliku_bazowego, const char* katalog_modułu, const char* opcjonalna_wiadomość_sukcesu)`
- `nazwa_pliku_bazowego`: **podstawowa** nazwa pliku modułu, **bez rozszerzenia** (np. dla `my_module.dll` lub `my_module.so`, użyj `"my_module"`). SDK automatycznie doda odpowiednie rozszerzenie `.dll` lub `.so`.
- `katalog_modułu`: Ścieżka do katalogu, w którym znajduje się plik modułu (np. `"plugins/my_custom_modules"`). **Nie dołączaj tutaj nazwy pliku.** SDK utworzy pełną ścieżkę (`katalog_modułu/nazwa_pliku_bazowego.rozszerzenie`).
- `opcjonalna_wiadomość_sukcesu`: Opcjonalna wiadomość do zalogowania w konsoli serwera, jeśli moduł zostanie pomyślnie załadowany.

```cpp
// main.cpp, wewnątrz OnLoad()

// Ładuje moduł 'core_logic.dll' (lub 'core_logic.so')
// który znajduje się w folderze 'modules/custom/' serwera.
if (!Plugin_Module("core_logic", "modules/custom", "Módulo de Lógica Core carregado com sucesso!"))
    return (Samp_SDK::Log("ERRO FATAL: Falha ao carregar o módulo 'core_logic'!"), false);

// Ładuje moduł 'admin_system.dll' (lub 'admin_system.so')
// który znajduje się bezpośrednio w folderze 'plugins/' serwera.
if (!Plugin_Module("admin_system", "plugins", "Módulo de Administração ativado."))
    Samp_SDK::Log("AVISO: Módulo de Administração não pôde ser carregado.");
```

#### Cykl życia modułu

Moduł musi eksportować funkcje `Load`, `Unload` i `Supports`, podobnie jak normalna wtyczka. SDK zarządza cyklem życia modułu w następujący sposób:

- **Ładowanie:** Gdy wywołane zostanie `Plugin_Module`, SDK:
   1. Tworzy pełną ścieżkę do pliku (np. `modules/custom/core_logic.dll`).
   2. Używa `Dynamic_Library` (`LoadLibrary`/`dlopen`) do załadowania pliku binarnego.
   3. **Pobiera wskaźniki do WSZYSTKICH funkcji cyklu życia modułu:**
      - **Obowiązkowe:** `Load`, `Unload`, `Supports`. Jeśli którakolwiek brakuje, ładowanie modułu kończy się niepowodzeniem.
      - **Opcjonalne:** `AmxLoad`, `AmxUnload`, `ProcessTick`.
   4. Wywołuje funkcję `Load` modułu, przekazując `ppData` z głównej wtyczki.
   5. Jeśli `Load` zwróci `true`, moduł jest dodawany do wewnętrznej listy załadowanych modułów.

- **Przekazywanie zdarzeń:** Wtyczka-host **automatycznie przekazuje** zdarzenia do wszystkich załadowanych modułów.
 > [!IMPORTANT]
 > Aby zdarzenia były poprawnie przekazywane, **wtyczka-host** (ta, która wywołuje `Plugin_Module`) musi być skonfigurowana do odbierania tych zdarzeń.
 > - Aby `AmxLoad` i `AmxUnload` działały w modułach, wtyczka-host musi zdefiniować makro `SAMP_SDK_WANT_AMX_EVENTS`.
 > - Aby `ProcessTick` działał w modułach, wtyczka-host musi zdefiniować makro `SAMP_SDK_WANT_PROCESS_TICK`.

- **Odładowywanie:** Podczas `OnUnload` Twojej głównej wtyczki, SDK odładowuje wszystkie moduły, które zostały załadowane za pomocą `Plugin_Module`. Odbywa się to w **odwrotnej kolejności** do ładowania (ostatni załadowany jest pierwszym odładowywanym), co jest kluczowe dla zarządzania zależnościami i zapewnienia prawidłowego zwalniania zasobów.

#### Korzyści z modularizacji

- **Organizacja kodu:** Podziel duże wtyczki na mniejsze, łatwe w zarządzaniu komponenty, każdy w osobnym pliku modułu.
- **Ponowne użycie:** Twórz ogólne moduły (np. moduł bazy danych, moduł zaawansowanego systemu logowania), które mogą być używane przez różne wtyczki, promując ponowne użycie kodu.
- **Niezależne komponenty:** Twórz moduły, które są **całkowicie zorientowane na zdarzenia i niezależne**. Moduł może mieć własne `Plugin_Native`s, przechwytywać `Plugin_Public`s i mieć własną logikę `OnProcessTick`, działając jako autonomiczna wtyczka, ale ładowana przez hosta.
- **Dynamiczne aktualizacje:** W kontrolowanych scenariuszach pozwala na aktualizację części systemu (zastępowanie pliku `.dll` lub `.so` modułu) bez konieczności ponownej kompilacji i ponownego uruchamiania głównej wtyczki lub całego serwera (choć wymaga to rygorystycznego zarządzania wersjami i kompatybilnością).

### 3.8. `Plugin_Call`: wywoływanie wewnętrznych natywnych funkcji wtyczki

Użyj `Plugin_Call`, aby wywołać `Plugin_Native` zdefiniowaną **wewnątrz Twojej własnej wtyczki**.

#### Składnia i zalety wydajności

- `Plugin_Call(NativeName, Param1, Param2, ...)`
- **Zaleta:** Unika narzutu związanego z wyszukiwaniem natywnej funkcji w tablicy natywnych AMX. SDK utrzymuje bezpośrednią mapę skrótów nazw na wskaźniki funkcji dla własnych natywnych funkcji, co czyni to najszybszym sposobem ich wywoływania wewnętrznie.
- **Wymaga:** `SAMP_SDK_WANT_AMX_EVENTS`.

```cpp
// main.cpp
Plugin_Native(InternalCheckPlayerLevel, AMX* amx, cell* params) {
    int playerid;
    Register_Parameters(playerid);

    // Logika sprawdzania poziomu
    return (playerid % 2 == 0) ? 1 : 0; // Przykład: poziom parzysty dla parzystych ID
}

void Check_All_Players_Level() {
    for (int i = 0; i < MAX_PLAYERS; ++i) {
        if (Pawn_Native(IsPlayerConnected, i)) {
            if (Plugin_Call(InternalCheckPlayerLevel, i)) // Wywołuje własną funkcję natywną
                Samp_SDK::Log("Jogador %d está em um nível alto!", i);
        }
    }
}
```

### 3.9. Funkcje narzędziowe SDK

#### `Samp_SDK::Log(const char* format, ...)`

- **Opis:** Wyświetla wiadomości w konsoli serwera i w pliku `server_log.txt`. Bezpieczny wrapper dla `logprintf`.
- **Użycie:** Do debugowania, wiadomości o statusie i błędach.
- **Mechanizm:** Wewnętrznie SDK pobiera wskaźnik do `logprintf` poprzez `ppData[PLUGIN_DATA_LOGPRINTF]`. Funkcja bezpiecznie obsługuje formatowanie ciągów znaków.

```cpp
// W dowolnym miejscu w Twojej wtyczce
Samp_SDK::Log("O plugin foi inicializado com um valor %d e uma string '%s'.", 123, "teste");
```

#### `std::string Plugin_Format(const char* format, ...)` (zalecane)

- **Opis:** Bezpiecznie formatuje ciąg znaków (podobnie do `sprintf`) i zwraca `std::string`. Jest to **zalecany i najbardziej idiomatyczny** sposób formatowania ciągów znaków do użycia w Twojej wtyczce.
- **Użycie:** Idealne do konstruowania sformatowanych wiadomości przed przekazaniem ich do `Samp_SDK::Log`, `Pawn_Native(SendClientMessage, ...)`, lub do innych potrzeb związanych z ciągami znaków w Twoim kodzie C++.
- **Mechanizm:** Wewnętrznie `Plugin_Format` to makro, które wywołuje `Samp_SDK::Format`. Wykorzystuje `vsnprintf` do określenia dokładnej długości sformatowanego ciągu znaków i alokuje `std::string` o wystarczającej pojemności, zapobiegając przepełnieniom bufora.

```cpp
int playerid = 0; // Przykładowe ID
int health = 50;
Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, Plugin_Format("Jogador %d, sua vida atual é %d.", playerid, health));

// Może być również używany do wewnętrznych logów
Samp_SDK::Log(Plugin_Format("DEBUG: Processando status para o ID %d", playerid));
```

#### `std::string Samp_SDK::Format(const char* format, ...)` (szczegół implementacji)

- **Opis:** Podstawowa funkcja implementacji formatowania ciągów znaków, znajdująca się w przestrzeni nazw `Samp_SDK`.
- **Użycie:** Zazwyczaj nie jest wywoływana bezpośrednio przez użytkownika. Makro `Plugin_Format` jest dostarczone jako wygoda dla tej funkcji, zgodnie z konwencją nazewnictwa innych makr SDK (`Plugin_Public`, `Plugin_Native`). Wywołałbyś ją bezpośrednio tylko wtedy, gdybyś chciał uniknąć makra `Plugin_Format` z jakiegoś konkretnego powodu.

```cpp
// Przykład działania Samp_SDK::Format, ale preferuj Plugin_Format
std::string raw_status = Samp_SDK::Format("Apenas para uso interno: %d.", 42);
```

#### `std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`

- **Opis:** Konwertuje adres ciągu znaków AMX (`cell amx_addr`) na `std::string` C++.
- **Użycie:** Głównie w `Plugin_Native` i `Plugin_Native_Hook`, gdy potrzebujesz dostępu do ciągów znaków, które nie są automatycznie konwertowane przez `Register_Parameters` lub `Native_Params` (np. jeśli parametr Pawn jest `const` `string` i nie został zadeklarowany jako `std::string` w Twoim `Plugin_Native` lub `Plugin_Public` dla automatycznego marszowania).

```cpp
Plugin_Native(PrintRawAmxString, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    cell amx_string_addr = p.Get<cell>(0); // Pobiera adres ciągu znaków w AMX

    std::string cpp_string = Samp_SDK::Get_String(amx, amx_string_addr);
    Samp_SDK::Log("String da AMX: %s", cpp_string.c_str());

    return 1;
}
```

## 4. Kompilacja i wdrożenie

### Wymagania architektury i platformy

- Twoja wtyczka **MUSI** być skompilowana dla architektury **x86 (32-bit)**.
- Obsługiwane platformy: Windows (.dll) i Linux (.so).

### Przykłady poleceń kompilacji

#### **MSVC (Visual Studio)**

1. Utwórz nowy projekt „Dynamic-Link Library (DLL)”.
2. W ustawieniach projektu ustaw „Platforma rozwiązania” na **x86**.
3. Upewnij się, że standard języka C++ to co najmniej C++17.

#### **GCC / Clang (Linux)**

```bash
# Dla wtyczki o nazwie 'my_plugin.so' z 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -fPIC -Wall -Wextra -Wl,--no-undefined main.cpp -o my_plugin.so
```
- `-m32`: Kompiluje dla 32-bit.
- `-shared`: Tworzy bibliotekę współdzieloną (`.so`).
- `-std=c++17`: Ustawia standard C++ na C++17 (może być `c++20`, ale C++17 jest minimum).
- `-O2`: Poziom optymalizacji 2.
- `-fPIC`: Generuje kod niezależny od pozycji, niezbędny dla bibliotek współdzielonych.
- `-Wall -Wextra`: Włącza dodatkowe ostrzeżenia, aby pomóc wychwycić błędy.
- `-Wl,--no-undefined`: Zapobiega tworzeniu biblioteki, jeśli istnieją niezdefiniowane symbole.

#### **GCC / Clang (MinGW w systemie Windows)**

```bash
# Dla wtyczki o nazwie 'my_plugin.dll' z 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -static-libstdc++ -static-libgcc -Wl,--no-undefined main.cpp -o my_plugin.dll
```
- `-static-libstdc++`: Statycznie łączy standardową bibliotekę C++. Niezbędne, aby Twoja wtyczka nie zależała od konkretnych dla kompilatora bibliotek wykonawczych DLL, które mogą nie być obecne w systemie użytkownika.
- `-static-libgcc`: Statycznie łączy bibliotekę GCC.

### Wskazówki dotyczące dystrybucji

- **Nazwa pliku:** Twoja wtyczka powinna mieć rozszerzenie `.dll` (Windows) lub `.so` (Linux). Np. `my_plugin.dll`.
- **Lokalizacja:** Umieść skompilowany plik w folderze `plugins/` Twojego serwera SA-MP.
- **server.cfg:** Dodaj nazwę swojej wtyczki (jeśli to Windows, bez rozszerzenia) do linii `plugins` w `server.cfg`.
   ```
   plugins my_plugin (jeśli to Linux, my_plugin.so)
   ```

## Licencja

Copyright © **AlderGrounds**

To oprogramowanie jest licencjonowane na warunkach licencji MIT ("Licencja"); możesz korzystać z tego oprogramowania zgodnie z warunkami Licencji. Kopię Licencji można uzyskać pod adresem: [MIT License](https://opensource.org/licenses/MIT)

### Warunki użytkowania

#### 1. Przyznane uprawnienia

Niniejsza licencja bezpłatnie przyznaje każdej osobie otrzymującej kopię tego oprogramowania i powiązanych plików dokumentacji następujące prawa:
* Używanie, kopiowanie, modyfikowanie, łączenie, publikowanie, rozpowszechnianie, sublicencjonowanie i/lub sprzedaż kopii oprogramowania bez ograniczeń
* Zezwalanie osobom, którym oprogramowanie jest dostarczane, na to samo, pod warunkiem przestrzegania poniższych warunków

#### 2. Obowiązkowe warunki

Wszystkie kopie lub istotne części oprogramowania muszą zawierać:
* Powyższą informację o prawach autorskich
* Niniejsze zezwolenie
* Poniższe wyłączenie odpowiedzialności

#### 3. Prawa autorskie

Oprogramowanie i cała powiązana dokumentacja są chronione prawami autorskimi. **AlderGrounds** zachowuje oryginalne prawa autorskie do oprogramowania.

#### 4. Wyłączenie gwarancji i ograniczenie odpowiedzialności

OPROGRAMOWANIE JEST DOSTARCZANE "TAK JAK JEST", BEZ JAKIEJKOLWIEK GWARANCJI, WYRAŹNEJ LUB DOROZUMIANEJ, W TYM MIĘDZY INNYMI GWARANCJI PRZYDATNOŚCI HANDLOWEJ, PRZYDATNOŚCI DO OKREŚLONEGO CELU I NIENARUSZANIA PRAW.

W ŻADNYM WYPADKU AUTORZY LUB POSIADACZE PRAW AUTORSKICH NIE PONOSZĄ ODPOWIEDZIALNOŚCI ZA JAKIEKOLWIEK ROSZCZENIA, SZKODY LUB INNE ZOBOWIĄZANIA, CZY TO W RAMACH DZIAŁAŃ UMOWNYCH, DELIKTOWYCH CZY INNYCH, WYNIKAJĄCYCH Z OPROGRAMOWANIA LUB ZWIĄZANYCH Z NIM LUB Z JEGO UŻYTKOWANIEM LUB INNYMI CZYNNOŚCIAMI W OPROGRAMOWANIU.

---

Szczegółowe informacje o licencji MIT można znaleźć pod adresem: https://opensource.org/licenses/MIT