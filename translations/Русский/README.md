# SA-MP SDK

<div align="center">

![C++](https://img.shields.io/badge/C%2B%2B-17%2B-00599C?style=for-the-badge&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-blue?style=for-the-badge&logo=windows&logoColor=white)
![Architecture](https://img.shields.io/badge/Architecture-x86%20(32--bit)-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**Современный, header-only, высокоуровневый C++ SDK для разработки плагинов и модулей для SA-MP.**

</div>

## Языки

- Português: [README](../../)
- Deutsch: [README](../Deutsch/README.md)
- English: [README](../English/README.md)
- Español: [README](../Espanol/README.md)
- Français: [README](../Francais/README.md)
- Italiano: [README](../Italiano/README.md)
- Polski: [README](../Polski/README.md)
- Svenska: [README](../Svenska/README.md)
- Türkçe: [README](../Turkce/README.md)

## Оглавление

- [SA-MP SDK](#sa-mp-sdk)
  - [Языки](#языки)
  - [Оглавление](#оглавление)
  - [1. Введение и философия дизайна](#1-введение-и-философия-дизайна)
    - [Проблема со стандартным C API SA-MP](#проблема-со-стандартным-c-api-sa-mp)
    - [Решение SA-MP SDK: абстракция с безопасностью и производительностью](#решение-sa-mp-sdk-абстракция-с-безопасностью-и-производительностью)
    - [Модель Header-Only: преимущества и последствия](#модель-header-only-преимущества-и-последствия)
  - [2. Настройка и окружение](#2-настройка-и-окружение)
    - [Требования к компиляции](#требования-к-компиляции)
    - [Рекомендуемая структура файлов](#рекомендуемая-структура-файлов)
    - [Основные макросы конфигурации](#основные-макросы-конфигурации)
      - [`SAMP_SDK_IMPLEMENTATION`](#samp_sdk_implementation)
      - [`SAMP_SDK_WANT_AMX_EVENTS`](#samp_sdk_want_amx_events)
      - [`SAMP_SDK_WANT_PROCESS_TICK`](#samp_sdk_want_process_tick)
    - [Определения и константы SA-MP (`samp_defs.hpp`)](#определения-и-константы-sa-mp-samp_defshpp)
  - [3. Полное руководство по использованию API](#3-полное-руководство-по-использованию-api)
    - [3.1. Жизненный цикл плагина](#31-жизненный-цикл-плагина)
      - [`bool OnLoad()`](#bool-onload)
      - [`void OnUnload()`](#void-onunload)
      - [`unsigned int GetSupportFlags()`](#unsigned-int-getsupportflags)
      - [`void OnAmxLoad(AMX* amx)`](#void-onamxloadamx-amx)
      - [`void OnAmxUnload(AMX* amx)`](#void-onamxunloadamx-amx)
      - [`void OnProcessTick()`](#void-onprocesstick)
    - [3.2. Экспорт Функций Плагина](#32-экспорт-функций-плагина)
      - [Экспорт для MSVC (Visual Studio) с `Export_Plugin`](#экспорт-для-msvc-visual-studio-с-export_plugin)
      - [Экспорт для GCC / Clang с `SAMP_SDK_EXPORT`](#экспорт-для-gcc--clang-с-samp_sdk_export)
    - [3.3. `Plugin_Public`: Перехват Pawn-событий](#33-plugin_public-перехват-pawn-событий)
      - [Синтаксис и объявление](#синтаксис-и-объявление)
      - [Автоматический маршалинг параметров](#автоматический-маршалинг-параметров)
      - [Управление потоком: `PUBLIC_CONTINUE` vs `PUBLIC_STOP`](#управление-потоком-public_continue-vs-public_stop)
      - [Ghost Callbacks](#ghost-callbacks)
    - [3.4. `Plugin_Native`: Создание нативных функций на C++](#34-plugin_native-создание-нативных-функций-на-c)
      - [Синтаксис и фиксированная сигнатура](#синтаксис-и-фиксированная-сигнатура)
      - [Автоматическая регистрация Natives](#автоматическая-регистрация-natives)
      - [Извлечение параметров: `Register_Parameters` vs. `Native_Params`](#извлечение-параметров-register_parameters-vs-native_params)
        - [`Register_Parameters(...)`](#register_parameters)
        - [`Native_Params` (Полный API: `Get`, `Get_REF`, `Set_REF`)](#native_params-полный-api-get-get_ref-set_ref)
          - [`p.Count()`](#pcount)
          - [`p.Get<T>(size_t index)`](#pgettsize_t-index)
          - [`p.Get_REF<T>(size_t index, T& out_value)`](#pget_reftsize_t-index-t-out_value)
          - [`p.Get_REF<T>(size_t index)` (C++17+)](#pget_reftsize_t-index-c17)
          - [`p.Set_REF<T>(size_t index, T value)`](#pset_reftsize_t-index-t-value)
      - [Возврат значений](#возврат-значений)
    - [3.5. `Plugin_Native_Hook`: Перехват существующих Natives SA-MP](#35-plugin_native_hook-перехват-существующих-natives-sa-mp)
      - [Синтаксис и фиксированная сигнатура](#синтаксис-и-фиксированная-сигнатура-1)
      - [Регистрация и активация Hook](#регистрация-и-активация-hook)
      - [Вызов оригинальной Native (цепь Hooks): `Call_Original_Native`](#вызов-оригинальной-native-цепь-hooks-call_original_native)
      - [Полный пример `Plugin_Native_Hook`](#полный-пример-plugin_native_hook)
    - [3.6. `Pawn_*` Макросы: Вызов Pawn-функций из C++](#36-pawn_-макросы-вызов-pawn-функций-из-c)
      - [`Pawn_Native(NativeName, ...)`](#pawn_nativenativename-)
      - [`Pawn_Public(PublicName, ...)`](#pawn_publicpublicname-)
      - [`Pawn(FunctionName, ...)`](#pawnfunctionname-)
      - [Синтаксис и соглашения](#синтаксис-и-соглашения)
      - [Маршалинг входных параметров](#маршалинг-входных-параметров)
      - [Маршалинг выходных параметров (Ссылки: `int&`, `float&`, `std::string&`)](#маршалинг-выходных-параметров-ссылки-int-float-stdstring)
      - [Объект `Callback_Result`: полный анализ](#объект-callback_result-полный-анализ)
    - [3.7. `Plugin_Module`: Управление динамическими модулями](#37-plugin_module-управление-динамическими-модулями)
      - [Синтаксис и назначение](#синтаксис-и-назначение)
      - [Жизненный цикл модуля](#жизненный-цикл-модуля)
      - [Преимущества модульности](#преимущества-модульности)
    - [3.8. `Plugin_Call`: Вызов внутренних Native-функций плагина](#38-plugin_call-вызов-внутренних-native-функций-плагина)
      - [Синтаксис и преимущества производительности](#синтаксис-и-преимущества-производительности)
    - [3.9. Утилитарные функции SDK](#39-утилитарные-функции-sdk)
      - [`Samp_SDK::Log(const char* format, ...)`](#samp_sdklogconst-char-format-)
      - [`std::string Plugin_Format(const char* format, ...)` (Рекомендуется)](#stdstring-plugin_formatconst-char-format--рекомендуется)
      - [`std::string Samp_SDK::Format(const char* format, ...)` (Деталь реализации)](#stdstring-samp_sdkformatconst-char-format--деталь-реализации)
      - [`std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`](#stdstring-samp_sdkget_stringamx-amx-cell-amx_addr)
  - [4. Компиляция и развертывание](#4-компиляция-и-развертывание)
    - [Требования к архитектуре и платформе](#требования-к-архитектуре-и-платформе)
    - [Примеры команд компиляции](#примеры-команд-компиляции)
      - [**MSVC (Visual Studio)**](#msvc-visual-studio)
      - [**GCC / Clang (Linux)**](#gcc--clang-linux)
      - [**GCC / Clang (MinGW в Windows)**](#gcc--clang-mingw-в-windows)
    - [Соображения по распространению](#соображения-по-распространению)
  - [Лицензия](#лицензия)
    - [Условия использования](#условия-использования)
      - [1. Предоставленные разрешения](#1-предоставленные-разрешения)
      - [2. Обязательные условия](#2-обязательные-условия)
      - [3. Авторские права](#3-авторские-права)
      - [4. Отказ от гарантий и ограничение ответственности](#4-отказ-от-гарантий-и-ограничение-ответственности)

## 1. Введение и философия дизайна

### Проблема со стандартным C API SA-MP

API плагинов SA-MP — это программный интерфейс на C. Хотя он функционален и фундаментален, он представляет собой проблемы, присущие низкоуровневому программированию:
- **Ручное управление памятью:** Функции, такие как `amx_Allot` и `amx_Release`, требуют, чтобы разработчик явно выделял и освобождал память в куче AMX. Это распространенный источник утечек памяти и сбоев во время выполнения.
- **Слабая типизация и ручные преобразования:** Параметры передаются в виде массива `cell`s, что требует явных (и часто небезопасных) преобразований между `cell`, `int`, `float` и `char*`.
- **Многословность и boilerplate:** Извлечение нескольких параметров из массива `cell* params`, работа с размерами строк и управление стеком AMX для обратных вызовов C++ в Pawn требует повторяющегося кода.
- **Хрупкость интерфейса:** Отсутствие проверки типов во время компиляции (type safety) означает, что ошибки при передаче параметров или типов могут оставаться незамеченными до выполнения, вызывая сбои или неопределенное поведение.

### Решение SA-MP SDK: абстракция с безопасностью и производительностью

SA-MP SDK решает эти проблемы, предоставляя мощный уровень абстракции на C++:
- **RAII (Resource Acquisition Is Initialization):** Автоматическое управление памятью в AMX. `Amx_Scoped_Memory` гарантирует освобождение выделенной памяти.
- **Безопасность типов:** Автоматическое и безопасное преобразование параметров между C++ и Pawn. Вы работаете напрямую с `int`, `float`, `std::string`.
- **Краткий и идиоматический синтаксис:** Макросы и шаблоны предоставляют чистый API, который больше похож на современный C++, чем на традиционный C API.
- **Надежный перехват:** Расширенный механизм hooking позволяет прозрачно перехватывать коллбэки Pawn (`Plugin_Public`), создавать новые нативные функции (`Plugin_Native`) и **перехватывать и связывать существующие нативные функции SA-MP (`Plugin_Native_Hook`)**.
- **Высокая производительность:** Широкое использование хеширования во время компиляции (FNV1a), кеширование функций и оптимизации `thread_local` для минимизации накладных расходов абстракций.

### Модель Header-Only: преимущества и последствия

SDK состоит исключительно из заголовочных файлов (`.hpp`, `.h`).
- **Преимущества:**
   - **Упрощенная интеграция:** Нет библиотек для сборки, компоновки или распространения. Просто включите заголовки.
   - **Оптимизации компилятора:** Компилятор имеет полный доступ к коду SDK и вашему плагину, что позволяет агрессивное встраивание и оптимизации на этапе компоновки, что может привести к более быстрым бинарникам.
- **Последствия:**
   - **Время компиляции:** Для очень больших проектов компиляция может занимать больше времени из-за повторного включения кода SDK. Это смягчается guards включения и природой C++ "включать только то, что необходимо".
   - **Макросы реализации:** Необходимость макроса `SAMP_SDK_IMPLEMENTATION` является следствием модели header-only для предотвращения переопределения символов.

## 2. Настройка и окружение

### Требования к компиляции

- **Компилятор C++:** Совместим с C++17 или выше.
   - GCC (версия 8+)
   - Clang (версия 5+)
   - MSVC (Visual Studio 2017+)
- **Архитектура:** **x86 (32-бит)**. SA-MP работает исключительно на этой архитектуре. SDK включает проверки в `platform.hpp`, которые будут выдавать ошибки компиляции при обнаружении неверной архитектуры.
- **Операционная система:** Windows или Linux.

### Рекомендуемая структура файлов

Для ясности и организации обычно SDK размещается в подпапке `samp-sdk`.

```
meu_plugin/
├── samp-sdk/
│   ├── // Другие файлы SDK
│   └── samp_sdk.hpp // Основной заголовочный файл для включения
│
├── src/
│   ├── main.cpp // Где определен SAMP_SDK_IMPLEMENTATION
│   └── my_custom_logic.cpp // Опционально, для организации кода
│
└── CMakeLists.txt (или .vcxproj, Makefile)
```

### Основные макросы конфигурации

Всегда определяйте эти макросы *перед* включением `samp_sdk.hpp`.

#### `SAMP_SDK_IMPLEMENTATION`

- **Цель:** Сигнализирует компилятору, что этот файл `.cpp` должен генерировать реализации экспортных функций плагина (`Supports`, `Load`, `Unload`, `AmxLoad`, `AmxUnload`, `ProcessTick`). **SDK автоматически берет на себя экспорт этих функций, устраняя необходимость в файлах `.def` (в Windows) или объявлениях `__attribute__((visibility("default")))` (в Linux) для этих функций.**
- **Техническое воздействие:** Без этого макроса компоновщик не найдет необходимые экспорты, и сервер SA-MP не сможет загрузить ваш плагин.
- **Фундаментальное правило:** **Определите этот макрос ТОЛЬКО в ОДНОМ файле `.cpp` во всем вашем проекте.** Определение его в более чем одном файле вызовет ошибку компоновки "дублирующийся символ".

```cpp
// main.cpp
#define SAMP_SDK_IMPLEMENTATION // Макрос заставляет SDK автоматически экспортировать необходимые функции.
#include "samp-sdk/samp_sdk.hpp"

// ... код вашего плагина ...
```

#### `SAMP_SDK_WANT_AMX_EVENTS`

- **Цель:** Включает коллбэки жизненного цикла Pawn-скрипта (`OnAmxLoad`, `OnAmxUnload`) и функциональность создания новых нативных функций на C++ (`Plugin_Native`).
- **Включенные функции:**
   - Коллбэки `OnAmxLoad(AMX* amx)` и `OnAmxUnload(AMX* amx)`.
   - Объявление и регистрация новых нативных функций C++ с использованием `Plugin_Native`.
   - Макрос `Plugin_Call` для вызова нативных функций, созданных с помощью `Plugin_Native` внутри вашего собственного плагина.
- **Техническое воздействие:** Когда этот макрос определен, SDK автоматически собирает все ваши `Plugin_Native`s. В функции `Supports()` флаг `SUPPORTS_AMX_NATIVES` автоматически добавляется, если в вашем проекте есть какие-либо `Plugin_Native`.
- **Гибкость:** **Вы можете определить этот макрос в нескольких файлах `.cpp`**. Система статической регистрации SDK объединит все нативные функции из разных единиц компиляции в единый глобальный список.

```cpp
// my_natives.cpp (может быть отдельным файлом от main.cpp)
#define SAMP_SDK_WANT_AMX_EVENTS // Только для включения Plugin_Native и коллбэков OnAmxLoad/OnAmxUnload
#include "samp-sdk/samp_sdk.hpp"

Plugin_Native(MyCustomNative, AMX* amx, cell* params) {
    // ...
    return 0;
}
```

#### `SAMP_SDK_WANT_PROCESS_TICK`

- **Цель:** Включает коллбэк `OnProcessTick()`, который регулярно вызывается сервером.
- **Техническое воздействие:** Автоматически добавляет флаг `SUPPORTS_PROCESS_TICK` в функцию `Supports()`.

```cpp
// main.cpp
#define SAMP_SDK_IMPLEMENTATION
#define SAMP_SDK_WANT_PROCESS_TICK
#include "samp-sdk/samp_sdk.hpp"

void OnProcessTick() {
    // Логика, выполняемая на каждом "тике" сервера (например, 20 мс)
    // Будьте осторожны с тяжелыми операциями здесь!
}
```

### Определения и константы SA-MP (`samp_defs.hpp`)

Этот файл предоставляет все известные константы и лимиты SA-MP, такие как `MAX_PLAYERS`, `INVALID_PLAYER_ID`, `PLAYER_STATE_ONFOOT`, `WEAPON_DEAGLE`, `DIALOG_STYLE_LIST` и т.д. Он автоматически включается `samp_sdk.hpp` и должен использоваться для обеспечения совместимости и читабельности кода.

## 3. Полное руководство по использованию API

### 3.1. Жизненный цикл плагина

Следующие функции являются точками входа и выхода вашего плагина, автоматически экспортируемыми SDK.

#### `bool OnLoad()`

- **Описание:** Первая функция, вызываемая SA-MP сервером после успешной загрузки вашего плагина в память.
- **Использование:** Идеально подходит для инициализации любой системы, загрузки конфигураций, открытия соединений с базой данных или загрузки модулей (`Plugin_Module`).
- **Возврат:**
   - `true`: Плагин успешно инициализирован, и загрузка продолжается.
   - `false`: Плагин не удалось инициализировать. Загрузка будет прервана, и плагин будет выгружен.

```cpp
// main.cpp
bool OnLoad() {
    Samp_SDK::Log("Initializing MyPlugin v1.0...");

    // Пример: Загрузка модуля (подробнее в разделе 3.6)
    if (!Plugin_Module("my_database_module", "plugins/db_connector", "Database Module loaded.")) {
        Samp_SDK::Log("ERROR: Failed to load the database module!");

        return false; // Прерывает загрузку основного плагина
    }

    return true;
}
```

#### `void OnUnload()`

- **Описание:** Последняя функция, вызываемая SA-MP сервером перед выгрузкой вашего плагина из памяти.
- **Использование:** Идеально подходит для очистки ресурсов, закрытия соединений, сохранения состояний и обеспечения отсутствия утечек ресурсов. SDK автоматически управляет выгрузкой модулей (`Plugin_Module`).

```cpp
// main.cpp
void OnUnload() {
    Samp_SDK::Log("MyPlugin unloaded. Releasing resources...");
    // Ручных действий для модулей, загруженных через Plugin_Module, не требуется;
    // SDK обрабатывает это.
}
```

#### `unsigned int GetSupportFlags()`

- **Описание:** Информирует SA-MP сервер о том, какие функции ваш плагин поддерживает и хочет использовать.
- **Использование:** **Всегда возвращайте `SUPPORTS_VERSION` (или `SAMP_PLUGIN_VERSION`).** Флаги `SUPPORTS_AMX_NATIVES` и `SUPPORTS_PROCESS_TICK` автоматически добавляются SDK, если есть `Plugin_Native`s, и/или если определен макрос `SAMP_SDK_WANT_PROCESS_TICK` соответственно. Это упрощает обслуживание и предотвращает ошибки.

```cpp
// main.cpp
unsigned int GetSupportFlags() {
    return SUPPORTS_VERSION; // SDK автоматически добавляет необходимые флаги.
}
```

#### `void OnAmxLoad(AMX* amx)`

- **Требуется:** `SAMP_SDK_WANT_AMX_EVENTS`
- **Описание:** Вызывается всякий раз, когда новый Pawn-скрипт (Gamemode или Filterscript) загружается и инициализируется на сервере.
- **Использование:** Если вам нужна специфическая логика для каждого AMX-скрипта или инициализация данных, специфичных для скрипта.

```cpp
// main.cpp (с определенным SAMP_SDK_WANT_AMX_EVENTS)
void OnAmxLoad(AMX* amx) {
    // amx представляет новый экземпляр загруженного скрипта.
    Samp_SDK::Log("AMX script loaded: %p", (void*)amx);
}
```

#### `void OnAmxUnload(AMX* amx)`

- **Требуется:** `SAMP_SDK_WANT_AMX_EVENTS`
- **Описание:** Вызывается, когда Pawn-скрипт выгружается с сервера.
- **Использование:** Для очистки любых специфических ресурсов, которые вы выделили или связали с этим конкретным `AMX*`.

```cpp
// main.cpp (с определенным SAMP_SDK_WANT_AMX_EVENTS)
void OnAmxUnload(AMX* amx) {
    Samp_SDK::Log("AMX script unloaded: %p", (void*)amx);
}
```

#### `void OnProcessTick()`

- **Требуется:** `SAMP_SDK_WANT_PROCESS_TICK`
- **Описание:** Вызывается повторно с каждым "тиком" сервера (обычно 20 раз в секунду или каждые 50 мс).
- **Использование:** Для непрерывной фоновой логики, таймеров, обновлений состояния, которые не зависят от событий игрока, или синхронизации данных.
- **Внимание:** Избегайте блокирующих или вычислительно тяжелых операций здесь, так как они могут вызвать задержку на сервере.

```cpp
// main.cpp (с определенным SAMP_SDK_WANT_PROCESS_TICK)
static int tick_count = 0;

void OnProcessTick() {
    tick_count++;

    if (tick_count % 200 == 0) // Каждые 10 секунд (20 тиков/сек * 10 сек = 200 тиков)
        Samp_SDK::Log("Server active for %d seconds.", tick_count / 20);
}
```

### 3.2. Экспорт Функций Плагина

Чтобы сервер SA-MP мог вызывать функции вашего плагина (`Load`, `Supports` и т.д.), они должны быть "экспортированы" из файла DLL (Windows) или SO (Linux). SDK автоматизирует экспорт стандартных функций жизненного цикла, но также предоставляет инструменты для экспорта ваших собственных пользовательских функций, если вам необходима совместимость с другими программами.

Метод экспорта функций различается в зависимости от компилятора.

#### Экспорт для MSVC (Visual Studio) с `Export_Plugin`

В Windows с MSVC самый простой способ экспортировать пользовательские функции — использовать макрос `Export_Plugin`, определенный в `exports.hpp`.

- **Синтаксис:** `Export_Plugin("Функция", "Стек")`
- **`Функция`**: Точное имя функции для экспорта.
- **`Стек`**: Общее количество байтов, которое параметры функции занимают в стеке. Для соглашения `__stdcall` (стандарт SDK в Windows) расчет составляет `4 * (Количество Параметров)`.

```cpp
#include "samp-sdk/exports.hpp"

// Пример: Экспорт пользовательской функции, которая могла бы быть вызвана
// другой программой или плагином, который знает её сигнатуру.
const char* SAMP_SDK_CALL GetPluginVersion() {
    return "1.0.0";
}

Export_Plugin("GetPluginVersion", "0");
```

> [!WARNING]
> **Ограничение `Export_Plugin`**
> Этот макрос работает **только с компилятором MSVC (Visual Studio)**. Он использует специфичную для Microsoft директиву `#pragma`, которая игнорируется другими компиляторами, такими как GCC и Clang.

#### Экспорт для GCC / Clang с `SAMP_SDK_EXPORT`

Для GCC и Clang (в Windows или Linux) экспорт управляется макросом `SAMP_SDK_EXPORT`, определенным в `platform.hpp`. Вы просто размещаете его перед определением функции.

- **Механизм:** В Linux он добавляет `__attribute__((visibility("default")))`. В Windows с GCC/Clang он добавляет `__attribute__((dllexport))`.
- **Использование:** SDK уже применяет `SAMP_SDK_EXPORT` ко всем функциям жизненного цикла (`Load`, `Unload` и т.д.), поэтому их экспорт полностью автоматический для этих компиляторов. Для ваших пользовательских функций просто делайте то же самое.

```cpp
// Для GCC/Clang определения функции с SAMP_SDK_EXPORT достаточно.
SAMP_SDK_EXPORT const char* SAMP_SDK_CALL GetPluginVersion() {
    return "1.0.0";
}
```

### 3.3. `Plugin_Public`: Перехват Pawn-событий

Макрос `Plugin_Public` является основным мостом для получения Pawn-коллбэков в вашем коде C++.

#### Синтаксис и объявление

- `Plugin_Public(NameOfPublic, Type1 Param1, Type2 Param2, ...)`
- Имя функции C++, которую вы объявляете, **должно совпадать** с именем Pawn-коллбэка (например: `OnPlayerConnect`).
- Типы параметров C++ (`int`, `float`, `std::string`) автоматически преобразуются SDK.

```cpp
// Перехватывает OnPlayerText(playerid, text[])
Plugin_Public(OnPlayerText, int playerid, std::string text) {
    Samp_SDK::Log("Player %d said: %s", playerid, text.c_str());

    return PUBLIC_CONTINUE;
}
```

#### Автоматический маршалинг параметров

SDK автоматически обрабатывает чтение `cell stack` AMX и преобразование в указанные типы C++:
- `int`: Преобразуется напрямую из `cell`.
- `float`: Преобразуется из `cell` с использованием `amx::AMX_CTOF`.
- `std::string`: SDK считывает адрес строки в AMX, выделяет `std::string` в C++ и копирует содержимое.

#### Управление потоком: `PUBLIC_CONTINUE` vs `PUBLIC_STOP`

Возвращаемое значение вашей функции `Plugin_Public` имеет решающее значение и определяет поток выполнения коллбэка:
- `return PUBLIC_CONTINUE;` (значение `1`): Указывает, что выполнение коллбэка должно **продолжаться**. Если есть другие плагины, которые также перехватывают этот коллбэк, они будут вызваны (в обратном порядке загрузки). Затем будет вызвана оригинальная `public` в Pawn-скрипте.
- `return PUBLIC_STOP;` (значение `0`): Указывает, что выполнение коллбэка должно быть **прервано**. Никакие другие плагины (с меньшим приоритетом) или оригинальная `public` в Pawn-скрипте не будут вызваны для этого события. Это идеально подходит для реализации системы, которая "переопределяет" или "блокирует" стандартное поведение SA-MP.

```cpp
// main.cpp
Plugin_Public(OnPlayerCommandText, int playerid, std::string cmdtext) {
    if (cmdtext == "/freeze") {
        Pawn_Native(TogglePlayerControllable, playerid, 0); // Замораживает игрока
        Pawn_Native(SendClientMessage, playerid, -1, Plugin_Format("Player %d frozen.", playerid));

        return PUBLIC_STOP; // Предотвращает обработку команды другими скриптами.
    }

    return PUBLIC_CONTINUE; // Позволяет обрабатывать другие команды.
}
```

#### Ghost Callbacks

Расширенная функция `Plugin_Public` — это поддержка "Ghost Callbacks". Это означает, что вы можете перехватить Pawn-коллбэк, даже если он **отсутствует** в `.amx` скрипте gamemode или filterscript. SDK "обманывает" сервер, чтобы он все равно вызывал ваш C++ хук. Это полезно для внутренних коллбэков или для создания новой функциональности без зависимости от наличия `public` в Pawn-скрипте.

```cpp
// Вы можете определить коллбэк, которого нет в Pawn-скрипте, но ваш плагин будет его слушать.
Plugin_Public(OnMyCustomInternalEvent, int data1, float data2) {
    Samp_SDK::Log("Custom internal event received: %d, %.2f", data1, data2);

    return PUBLIC_CONTINUE;
}

// Чтобы "вызвать" это событие из другой точки вашего кода C++:
// Pawn_Public(OnMyCustomInternalEvent, 123, 45.67f);
// Вызов перейдет к вашему Plugin_Public выше, даже если в Pawn нет OnMyCustomInternalEvent.
```

### 3.4. `Plugin_Native`: Создание нативных функций на C++

`Plugin_Native` позволяет расширять функциональность Pawn с помощью высокопроизводительного кода C++.

#### Синтаксис и фиксированная сигнатура

- `Plugin_Native(NativeName, AMX* amx, cell* params)`
- Функция C++ должна иметь точно такую сигнатуру: `cell NativeName(AMX* amx, cell* params)`.
- `NativeName` — это имя, которое будут использовать Pawn-скрипты.

```cpp
// Pawn: native GetPlayerPingAverage(playerid);
Plugin_Native(GetPlayerPingAverage, AMX* amx, cell* params) {
    // ... Реализация ...
    return 0;
}
```

#### Автоматическая регистрация Natives

> [!NOTE]
> Вам **не нужно** вручную вызывать `amx_Register`. SDK обнаруживает все ваши `Plugin_Native`s (в любом файле `.cpp`, который включает `samp_sdk.hpp` и определяет `SAMP_SDK_WANT_AMX_EVENTS`) и автоматически регистрирует их в каждом загруженном AMX-скрипте (`OnAmxLoad`).

#### Извлечение параметров: `Register_Parameters` vs. `Native_Params`

##### `Register_Parameters(...)`

- **Описание:** Более простой вспомогательный инструмент для последовательного извлечения нескольких параметров.
- **Использование:** `Register_Parameters(variable1, variable2, ...)`
- **Ограничения:** Для входных параметров. Не работает с необязательными параметрами или доступом по индексу.
- **Поддерживаемые типы:** `int`, `float`, `std::string`.

```cpp
// Pawn: native SetPlayerSkinAndMoney(playerid, skinid, money);
Plugin_Native(SetPlayerSkinAndMoney, AMX* amx, cell* params) {
    int playerid, skinid, money;
    Register_Parameters(playerid, skinid, money); // Извлекает 3 параметра
    
    Pawn_Native(SetPlayerSkin, playerid, skinid);
    Pawn_Native(GivePlayerMoney, playerid, money);
    
    return 1;
}
```

##### `Native_Params` (Полный API: `Get`, `Get_REF`, `Set_REF`)

- **Описание:** Класс-обертка, предоставляющий объектно-ориентированный интерфейс для доступа к параметрам нативной функции. Более мощный для сложных сценариев.
- **Создание:** `Native_Params p(amx, params);`

###### `p.Count()`

- **Описание:** Возвращает количество параметров, переданных нативной функции.
- **Использование:** Необходимо для работы с необязательными параметрами.

###### `p.Get<T>(size_t index)`

- **Описание:** Извлекает входной параметр по индексу и преобразует его в тип `T`.
- **Поддерживаемые типы:** `int`, `float`, `std::string`.

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

- **Описание:** Получает значение **ссылочного** параметра (Pawn-указателя) и сохраняет его в `out_value`.
- **Использование:** Для чтения значений, переданных по ссылке из Pawn.
- **Возврат:** `true`, если AMX-адрес действителен, `false` в противном случае.

```cpp
// Pawn: native CheckPlayerStats(playerid, &Float:health, &money);
Plugin_Native(CheckPlayerStats, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    
    int playerid = p.Get<int>(0);
    float health = 0.0f;
    int money = 0;

    // Получить значения из ссылок (Pawn передал адреса)
    p.Get_REF(1, health); // Читает значение Float:health
    p.Get_REF(2, money);  // Читает значение money
    
    Samp_SDK::Log("Player %d, Health: %.1f, Money: %d", playerid, health, money);
    
    // Теперь изменяем их
    health = 50.0f;
    money += 100;
    
    // И записываем их обратно в память Pawn
    p.Set_REF(1, health);
    p.Set_REF(2, money);
    
    return 1;
}
```

###### `p.Get_REF<T>(size_t index)` (C++17+)

- **Описание:** Возвращает `std::optional<T>` для чтения ссылочного параметра. Более безопасно для C++17 и выше.

###### `p.Set_REF<T>(size_t index, T value)`

- **Описание:** Записывает значение `T` в **ссылочный** параметр Pawn (адрес, переданный Pawn).
- **Использование:** Для изменения значений, переданных по ссылке, чтобы Pawn видел изменения.
- **Возврат:** `true`, если запись прошла успешно, `false` в противном случае.

#### Возврат значений

- Ваша функция `Plugin_Native` должна возвращать `cell`.
- Чтобы вернуть `int` или `bool`, используйте приведение к `cell`.
- Чтобы вернуть `float`, используйте `amx::AMX_FTOC(my_float)`.

```cpp
// Возвращает bool
Plugin_Native(IsPlayerSpawned, AMX* amx, cell* params) {
    int playerid;
    Register_Parameters(playerid);

    return (Pawn_Native(GetPlayerState, playerid) == PLAYER_STATE_SPAWNED) ? 1 : 0;
}

// Возвращает float
Plugin_Native(GetPlayerMaxHealth, AMX* amx, cell* params) {
    return amx::AMX_FTOC(100.0f); // Возвращает 100.0f
}
```

### 3.5. `Plugin_Native_Hook`: Перехват существующих Natives SA-MP

Макрос `Plugin_Native_Hook` позволяет перехватывать и изменять поведение любой существующей нативной функции SA-MP или других плагинов. Это мощный механизм для расширения или изменения стандартной логики сервера.

#### Синтаксис и фиксированная сигнатура

- `Plugin_Native_Hook(NativeName, AMX* amx, cell* params)`
- Функция C++ должна иметь точно такую сигнатуру: `cell NativeName(AMX* amx, cell* params)`.
- `NativeName` должно быть точным именем нативной функции, которую вы хотите хукнуть (например, `SendClientMessage`, `SetPlayerPos`).

```cpp
// Перехватывает нативную функцию SendClientMessage
Plugin_Native_Hook(SendClientMessage, AMX* amx, cell* params) {
    // ...
    return Call_Original_Native(SendClientMessage); // Важно вызвать оригинал
}
```

#### Регистрация и активация Hook

> [!NOTE]
> Вам **не нужно** вручную вызывать `amx_Register` или определять `SAMP_SDK_WANT_AMX_EVENTS` специально для `Plugin_Native_Hook`. SDK автоматически обнаруживает и регистрирует ваши хуки. При первом выполнении AMX-скрипта SDK заменяет указатель на native в таблице на "trampoline", который перенаправляет на вашу функцию `Plugin_Native_Hook`. Этот процесс обеспечивает безопасное связывание хуков из нескольких плагинов.

#### Вызов оригинальной Native (цепь Hooks): `Call_Original_Native`

Внутри вашей функции `Plugin_Native_Hook` вы **ДОЛЖНЫ** использовать макрос `Call_Original_Native(NativeName)` для вызова оригинальной функции (или следующего хука в цепочке). Это жизненно важно для:
- **Сохранения функциональности:** Если вы не вызовете оригинал, захуканная native просто перестанет работать для других плагинов или для сервера.
- **Цепочки хуков:** Позволяет нескольким плагинам хукать одну и ту же native и выполнять все хуки последовательно.
- **Обработки возврата:** Вы можете проверять и даже изменять возвращаемое значение `Call_Original_Native` перед возвратом его из вашей функции хука.

```cpp
// Пример: Блокировка SendClientMessage, если она содержит определенное слово
Plugin_Native_Hook(SendClientMessage, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    
    // Извлечение параметров для анализа
    int playerid = p.Get<int>(0);
    // int color = p.Get<int>(1); // Нам не нужен цвет для этой логики
    std::string message = p.Get_String(2); // Получает строку сообщения

    if (message.find("BADWORD") != std::string::npos) {
        Samp_SDK::Log("MESSAGE BLOCKED for playerid %d: %s", playerid, message.c_str());

        return 0; // Возвращает 0 (false) в Pawn, указывая, что сообщение не было отправлено.
                  // И что более важно, мы НЕ вызываем Call_Original_Native, блокируя сообщение.
    }

    // Если сообщение не содержит запрещенного слова, мы вызываем оригинальную нативную функцию
    // и возвращаем ее значение, гарантируя нормальную отправку сообщения
    // и выполнение других хуков (если они есть).
    return Call_Original_Native(SendClientMessage);
}
```

#### Полный пример `Plugin_Native_Hook`

```cpp
#define SAMP_SDK_IMPLEMENTATION
// SAMP_SDK_WANT_AMX_EVENTS не является строго обязательным для хуков, но обычно используется наличие OnAmxLoad/Unload
// #define SAMP_SDK_WANT_AMX_EVENTS 
#include "samp-sdk/samp_sdk.hpp"

// Хук для нативной функции CreateVehicle
Plugin_Native_Hook(CreateVehicle, AMX* amx, cell* params) {
    Native_Params p(amx, params);

    // Извлечение параметров нативной функции CreateVehicle для проверки
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

    // Пример того, как *изменить* входной параметр
    // Если модель 400 (Landstalker), меняем ее на 401 (Bravura)
    if (modelid == 400) {
        // Мы напрямую изменяем массив 'params' для оригинального вызова
        params[1] = static_cast<cell>(401); // Модель находится в позиции 0 массива параметров (params[1])
        Samp_SDK::Log("  -> Model 400 changed to 401 before creation.");
    }
    
    // Вызываем оригинальную нативную функцию (или следующий хук в цепочке) с возможно измененными параметрами
    cell original_retval = Call_Original_Native(CreateVehicle);

    Samp_SDK::Log("HOOK: CreateVehicle returned: %d (Vehicle ID)", (int)original_retval);

    // Здесь вы можете изменить возвращаемое значение перед возвратом его в Pawn.
    // Пример: если создание транспорта не удалось, вернуть пользовательский неверный ID.
    if ((int)original_retval == INVALID_VEHICLE_ID) {
        Samp_SDK::Log("  -> Vehicle creation failed in the original native.");

        return -1; // Возвращает другое значение в Pawn.
    }

    return original_retval; // Возвращает значение, которое вернула оригинальная нативная функция...
}

unsigned int GetSupportFlags() {
    return SUPPORTS_VERSION; 
}

// Минимальные реализации жизненного цикла
bool OnLoad() {
    Samp_SDK::Log("Native Hook Example Plugin loaded!");
    return true;
}

void OnUnload() {
    Samp_SDK::Log("Native Hook Example Plugin unloaded!");
}

// Эти коллбэки будут присутствовать только если SAMP_SDK_WANT_AMX_EVENTS определен
/*void OnAmxLoad(AMX* amx) {
    Samp_SDK::Log("AMX Load detected: %p", (void*)amx);
}

void OnAmxUnload(AMX* amx) {
    Samp_SDK::Log("AMX Unload detected: %p", (void*)amx);
}*/
```
> [!WARNING]
> Прямая манипуляция массивом `cell* params` для изменения входных параметров требует осторожности. Убедитесь, что вы понимаете порядок и тип параметров. В большинстве случаев достаточно `p.Get(...)` для проверки и `Call_Original_Native(...)` для продолжения цепочки. Прямое изменение `params` следует выполнять только в том случае, если вы знаете, что параметр является значением и должен быть изменен для исходного вызова. Для строк и массивов изменение более сложно и обычно включает `amx::Set_String` для записи по существующему адресу или перераспределения, что может быть проще управлять, вызывая native через `Pawn_Native` с новыми значениями и возвращая `0` из вашего хука, чтобы отменить исходный вызов.

### 3.6. `Pawn_*` Макросы: Вызов Pawn-функций из C++

Эти макросы являются противоположностью `Plugin_Public` и `Plugin_Native`: они позволяют вашему коду C++ вызывать Pawn-функции.

#### `Pawn_Native(NativeName, ...)`

- **Цель:** Рекомендуемый способ вызова нативных функций SA-MP (или других плагинов) из C++.
- **Механизм:** Ищет указатель на нативную функцию во внутреннем кэше SDK (заполненном `Amx_Register_Detour`). Если найдено, выполняет нативную функцию в среде `Amx_Sandbox` (фальшивый и изолированный экземпляр AMX).
- **Производительность:** Наиболее эффективный, поскольку избегает дорогостоящего поиска `publics` и напрямую взаимодействует с указателем на нативную функцию.

#### `Pawn_Public(PublicName, ...)`

- **Цель:** Вызывает конкретную публичную функцию в Pawn-скрипте.
- **Механизм:** Проходит по экземплярам `AMX*`, управляемым `Amx_Manager`, ищет `public` по имени и выполняет ее.
- **Производительность:** Менее эффективен, чем `Pawn_Native` из-за поиска и реального `amx_Exec`. Обычно `publics` медленнее, чем `natives`.
- **Использование:** Идеально подходит для вызова пользовательских событий в вашем Gamemode/Filterscripts, которые не являются нативными функциями.

#### `Pawn(FunctionName, ...)`

- **Цель:** Вспомогательный макрос, который пытается определить, является ли функция нативной или публичной.
- **Механизм:** Сначала пытается вызвать как `Pawn_Native`. Если не удается (нативная функция не найдена), пытается вызвать как `Pawn_Public`.
- **Производительность:** Может быть немного медленнее, чем `Pawn_Native`, если функция является нативной, из-за двойной попытки поиска. Для `publics` производительность такая же, как у `Pawn_Public`.
- **Использование:** Для функций, в которых вы не уверены, являются ли они нативными или публичными, или чтобы избежать повторяющегося кода попыток одной, а затем другой.

#### Синтаксис и соглашения

- **Имя функции:** Всегда используйте имя Pawn-функции **напрямую, без кавычек**. SDK преобразует его в строку внутри.
- **Параметры:** Передавайте C++ параметры напрямую.

```cpp
// Правильно:
Pawn_Native(SetPlayerPos, playerid, 100.0f, 200.0f, 300.0f); 

// Неправильно (но технически сработает благодаря хешированию, избегайте):
Pawn_Native("SetPlayerPos", playerid, 100.0f, 200.0f, 300.0f); 
```

#### Маршалинг входных параметров

SDK преобразует ваши типы C++ в формат `cell` AMX, управляя памятью по мере необходимости:
- `int`, `bool`, `long`, `enum` -> `cell`
- `float`, `double` -> `cell` (с использованием `amx::AMX_FTOC`)
- `const char*`, `std::string`, `std::string_view` (C++17+) -> `cell` (выделяет память в AMX, копирует строку и передает адрес `amx_addr`)

```cpp
void Send_Formatted_Message(int playerid, const std::string& msg) {
    Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, msg);
}
```

#### Маршалинг выходных параметров (Ссылки: `int&`, `float&`, `std::string&`)

Это ключевая особенность для удобства и безопасности. Для функций Pawn, которые ожидают указатель (ссылку), SDK автоматизирует весь процесс выделения/освобождения памяти и копирования данных.

- **Как использовать:** Просто передайте вашу переменную по ссылке (`&`).
- **Механизм:** SDK выделяет память в куче AMX, передает AMX-адрес Pawn-функции, ждет, пока Pawn-функция заполнит этот адрес, считывает значение обратно и освобождает память AMX. Все это прозрачно.
- **С `std::string&`:** SDK выделяет стандартный буфер (256 ячеек) в AMX для строки.

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

#### Объект `Callback_Result`: полный анализ

Все вызовы `Pawn_*` возвращают объект `Callback_Result`. Этот объект является безопасной оберткой для результата вызова Pawn.

- `Callback_Result() noexcept`: Конструктор по умолчанию, указывает на сбой (`success_ = false`).
- `Callback_Result(bool success, cell value) noexcept`: Конструктор для успеха или сбоя со значением.
- `explicit operator bool() const`: Позволяет использовать `if (result)` для проверки успешности вызова.
- `operator cell() const`: Позволяет преобразовать результат в `cell` для получения значения.
- `float As_Float() const`: Удобство для получения результата в виде `float`.
- `cell Value() const`: Возвращает сырое значение `cell`.
- `bool Success() const`: Возвращает `true`, если вызов Pawn был успешным.
- `int Get_Amx_Error() const`: Возвращает код ошибки AMX, если вызов не удался (0 для успеха).

```cpp
// Пример: Получение здоровья игрока.
// Нативная функция GetPlayerHealth(playerid, &Float:health) ожидает playerid и ссылку на health.
int playerid = 0; // Пример ID игрока
float player_health = 0.0f;

// Вызываем GetPlayerHealth, передавая playerid и player_health по ссылке.
// SDK обработает маршалинг для выходного параметра 'health'.
Callback_Result result = Pawn_Native(GetPlayerHealth, playerid, player_health);

if (result) { // Проверяет, был ли вызов успешным (operator bool)
    // Значение, возвращаемое result.As_Float() или result (operator cell),
    // будет возвращаемым значением *нативной функции*, а не выходным параметром.
    // Значение здоровья уже обновлено в 'player_health' благодаря маршалингу выходных параметров.
    Samp_SDK::Log("Player %d has %.1f health.", playerid, player_health);
}
else {
    // Вызов не удался, возможно, игрока не существует или нативная функция не найдена.
    Samp_SDK::Log("Error getting player %d health. AMX Code: %d", playerid, result.Get_Amx_Error());
}

// Для нативных функций, которые возвращают значение и используют выходные параметры (реже, но возможно),
// вы бы использовали и то, и другое:
// Callback_Result other_result = Pawn_Native(SomeNative, param1, output_param, param2);
// if (other_result) {
//     cell returned_value = other_result;
//     // output_param уже обновлен
// }
```

### 3.7. `Plugin_Module`: Управление динамическими модулями

Макрос `Plugin_Module` позволяет вашему плагину выступать в качестве "загрузчика" для других плагинов, создавая модульную и расширяемую архитектуру. Модуль, загруженный таким образом, рассматривается как плагин первого класса, со своим собственным жизненным циклом событий, управляемым хост-плагином.

#### Синтаксис и назначение

- `Plugin_Module(const char* base_filename, const char* module_directory, const char* optional_success_message)`
- `base_filename`: **Базовое** имя файла модуля, **без расширения** (например, для `my_module.dll` или `my_module.so` используйте `"my_module"`). SDK автоматически добавит соответствующее расширение `.dll` или `.so`.
- `module_directory`: Путь к каталогу, где находится файл модуля (например, `"plugins/my_custom_modules"`). **Не включайте имя файла сюда.** SDK выполнит конкатенацию полного пути (`module_directory/base_filename.ext`).
- `optional_success_message`: Необязательное сообщение, которое будет записано в консоль сервера, если модуль успешно загрузится.

```cpp
// main.cpp, внутри OnLoad()

// Загружает модуль 'core_logic.dll' (или 'core_logic.so')
// который находится в папке 'modules/custom/' сервера.
if (!Plugin_Module("core_logic", "modules/custom", "Core Logic Module loaded successfully!"))
    return (Samp_SDK::Log("FATAL ERROR: Failed to load module 'core_logic'!"), false);

// Загружает модуль 'admin_system.dll' (или 'admin_system.so')
// который находится прямо в папке 'plugins/' сервера.
if (!Plugin_Module("admin_system", "plugins", "Administration Module activated."))
    Samp_SDK::Log("WARNING: Administration Module could not be loaded.");
```

#### Жизненный цикл модуля

Модуль должен экспортировать функции `Load`, `Unload` и `Supports`, как обычный плагин. SDK управляет жизненным циклом модуля следующим образом:

- **Загрузка:** При вызове `Plugin_Module` SDK:
   1. Создает полный путь к файлу (например, `modules/custom/core_logic.dll`).
   2. Использует `Dynamic_Library` (`LoadLibrary`/`dlopen`) для загрузки бинарного файла.
   3. **Получает указатели на ВСЕ функции жизненного цикла модуля:**
      - **Обязательные:** `Load`, `Unload`, `Supports`. Если какая-либо отсутствует, загрузка модуля завершается неудачей.
      - **Необязательные:** `AmxLoad`, `AmxUnload`, `ProcessTick`.
   4. Вызывает функцию `Load` модуля, передавая `ppData` основного плагина.
   5. Если `Load` возвращает `true`, модуль добавляется во внутренний список загруженных модулей.

- **Перенаправление событий:** Хост-плагин **автоматически перенаправляет** события всем загруженным модулям.
 > [!IMPORTANT]
 > Чтобы события перенаправлялись правильно, **хост-плагин** (который вызывает `Plugin_Module`) должен быть настроен на получение этих событий.
 > - Для работы `AmxLoad` и `AmxUnload` в модулях хост-плагин должен определить макрос `SAMP_SDK_WANT_AMX_EVENTS`.
 > - Для работы `ProcessTick` в модулях хост-плагин должен определить макрос `SAMP_SDK_WANT_PROCESS_TICK`.

- **Выгрузка:** Во время `OnUnload` вашего основного плагина SDK выгружает все модули, которые были загружены через `Plugin_Module`. Это делается в **обратном порядке** к загрузке (последний загруженный выгружается первым), что критически важно для управления зависимостями и обеспечения правильного освобождения ресурсов.

#### Преимущества модульности

- **Организация кода:** Разделите большие плагины на более мелкие, управляемые компоненты, каждый в своем файле модуля.
- **Повторное использование:** Создавайте общие модули (например, модуль базы данных, модуль расширенной системы логирования), которые могут использоваться различными плагинами, способствуя повторному использованию кода.
- **Независимые компоненты:** Создавайте модули, которые **полностью ориентированы на события и независимы**. Модуль может иметь свои собственные `Plugin_Native`s, перехватывать `Plugin_Public`s и иметь свою собственную логику `OnProcessTick`, работая как автономный плагин, но загружаемый хостом.
- **Динамические обновления:** В контролируемых сценариях позволяет обновлять части вашей системы (заменяя `.dll` или `.so` модуля) без необходимости перекомпилировать и перезапускать основной плагин или весь сервер (хотя это требует строгого управления версиями и совместимостью).

### 3.8. `Plugin_Call`: Вызов внутренних Native-функций плагина

Используйте `Plugin_Call` для вызова `Plugin_Native`, определенной **внутри вашего собственного плагина**.

#### Синтаксис и преимущества производительности

- `Plugin_Call(NativeName, Param1, Param2, ...)`
- **Преимущество:** Избегает накладных расходов на поиск native в массиве native AMX. SDK поддерживает прямую карту хэшей имен на указатели функций для ваших собственных native, что делает этот способ самым быстрым для их вызова внутри.
- **Требуется:** `SAMP_SDK_WANT_AMX_EVENTS`.

```cpp
// main.cpp
Plugin_Native(InternalCheckPlayerLevel, AMX* amx, cell* params) {
    int playerid;
    Register_Parameters(playerid);

    // Логика проверки уровня
    return (playerid % 2 == 0) ? 1 : 0; // Пример: четный уровень для четных ID
}

void Check_All_Players_Level() {
    for (int i = 0; i < MAX_PLAYERS; ++i) {
        if (Pawn_Native(IsPlayerConnected, i)) {
            if (Plugin_Call(InternalCheckPlayerLevel, i)) // Вызывает вашу собственную нативную функцию
                Samp_SDK::Log("Player %d is at a high level!", i);
        }
    }
}
```

### 3.9. Утилитарные функции SDK

#### `Samp_SDK::Log(const char* format, ...)`

- **Описание:** Печатает сообщения в консоль сервера и в файл `server_log.txt`. Безопасная обертка для `logprintf`.
- **Использование:** Для отладки, сообщений о статусе и ошибках.
- **Механизм:** Внутри SDK получает указатель на `logprintf` через `ppData[PLUGIN_DATA_LOGPRINTF]`. Функция безопасно обрабатывает форматирование строки.

```cpp
// В любом месте вашего плагина
Samp_SDK::Log("The plugin was initialized with a value %d and a string '%s'.", 123, "test");
```

#### `std::string Plugin_Format(const char* format, ...)` (Рекомендуется)

- **Описание:** Безопасно форматирует строку (подобно `sprintf`) и возвращает `std::string`. Это **рекомендуемый и наиболее идиоматичный** способ форматирования строк для использования внутри вашего плагина.
- **Использование:** Идеально подходит для создания отформатированных сообщений перед их передачей в `Samp_SDK::Log`, `Pawn_Native(SendClientMessage, ...)`, или для любых других потребностей в строках внутри вашего кода C++.
- **Механизм:** Внутри `Plugin_Format` является макросом, который вызывает `Samp_SDK::Format`. Он использует `vsnprintf` для определения точного размера форматированной строки и выделяет `std::string` достаточной емкости, предотвращая переполнение буфера.

```cpp
int playerid = 0; // Пример ID
int health = 50;
Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, Plugin_Format("Player %d, your current health is %d.", playerid, health));

// Также может использоваться для внутренних логов
Samp_SDK::Log(Plugin_Format("DEBUG: Processing status for ID %d", playerid));
```

#### `std::string Samp_SDK::Format(const char* format, ...)` (Деталь реализации)

- **Описание:** Базовая функция реализации для форматирования строк, расположенная в пространстве имен `Samp_SDK`.
- **Использование:** Обычно не вызывается пользователем напрямую. Макрос `Plugin_Format` предоставляется как удобство для этой функции, соответствуя соглашению об именовании других макросов SDK (`Plugin_Public`, `Plugin_Native`). Вы бы вызывали его напрямую только в том случае, если бы хотели избежать макроса `Plugin_Format` по какой-либо конкретной причине.

```cpp
// Пример работы Samp_SDK::Format, но предпочитайте Plugin_Format
std::string raw_status = Samp_SDK::Format("For internal use only: %d.", 42);
```

#### `std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`

- **Описание:** Преобразует AMX-адрес строки (`cell amx_addr`) в `std::string` C++.
- **Использование:** В основном внутри `Plugin_Native` и `Plugin_Native_Hook`, когда вам нужно получить доступ к строкам, которые не преобразуются автоматически `Register_Parameters` или `Native_Params` (например, если Pawn-параметр является `const` `string` и не был объявлен как `std::string` в вашем `Plugin_Native` или `Plugin_Public` для автоматического маршалинга).

```cpp
Plugin_Native(PrintRawAmxString, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    cell amx_string_addr = p.Get<cell>(0); // Получает адрес строки в AMX

    std::string cpp_string = Samp_SDK::Get_String(amx, amx_string_addr);
    Samp_SDK::Log("String from AMX: %s", cpp_string.c_str());

    return 1;
}
```

## 4. Компиляция и развертывание

### Требования к архитектуре и платформе

- Ваш плагин **ДОЛЖЕН** быть скомпилирован для архитектуры **x86 (32-бит)**.
- Поддерживаемые платформы: Windows (.dll) и Linux (.so).

### Примеры команд компиляции

#### **MSVC (Visual Studio)**

1. Создайте новый проект "Динамически подключаемая библиотека (DLL)".
2. В параметрах проекта установите "Платформа решения" на **x86**.
3. Убедитесь, что стандарт языка C++ не ниже C++17.

#### **GCC / Clang (Linux)**

```bash
# Для плагина с именем 'my_plugin.so' из 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -fPIC -Wall -Wextra -Wl,--no-undefined main.cpp -o my_plugin.so
```
- `-m32`: Компилирует для 32-битной архитектуры.
- `-shared`: Создает общую библиотеку (`.so`).
- `-std=c++17`: Устанавливает стандарт C++ на C++17 (можно использовать `c++20`, но C++17 является минимальным требованием).
- `-O2`: Уровень оптимизации 2.
- `-fPIC`: Генерирует позиционно-независимый код, необходимый для общих библиотек.
- `-Wall -Wextra`: Включает дополнительные предупреждения для выявления ошибок.
- `-Wl,--no-undefined`: Предотвращает создание библиотеки, если есть неопределенные символы.

#### **GCC / Clang (MinGW в Windows)**

```bash
# Для плагина с именем 'my_plugin.dll' из 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -static-libstdc++ -static-libgcc -Wl,--no-undefined main.cpp -o my_plugin.dll
```
- `-static-libstdc++`: Статически компонует стандартную библиотеку C++. Важно для предотвращения зависимости вашего плагина от специфических для компилятора DLL среды выполнения, которые могут отсутствовать в системе пользователя.
- `-static-libgcc`: Статически компонует библиотеку GCC.

### Соображения по распространению

- **Имя файла:** Ваш плагин должен иметь расширение `.dll` (Windows) или `.so` (Linux). Например: `my_plugin.dll`.
- **Расположение:** Поместите скомпилированный файл в папку `plugins/` вашего SA-MP сервера.
- **server.cfg:** Добавьте имя вашего плагина (если Windows, без расширения) в строку `plugins` в `server.cfg`.
   ```
   plugins my_plugin (если Linux, my_plugin.so)
   ```

## Лицензия

Copyright © **AlderGrounds**

Данное программное обеспечение лицензируется в соответствии с условиями лицензии MIT ("Лицензия"); вы можете использовать это программное обеспечение в соответствии с условиями Лицензии. Копию Лицензии можно получить по адресу: [MIT License](https://opensource.org/licenses/MIT)

### Условия использования

#### 1. Предоставленные разрешения

Настоящая лицензия бесплатно предоставляет любому лицу, получающему копию данного программного обеспечения и связанных с ним файлов документации, следующие права:
* Использовать, копировать, изменять, объединять, публиковать, распространять, сублицензировать и/или продавать копии программного обеспечения без ограничений
* Разрешать лицам, которым предоставляется программное обеспечение, делать то же самое при соблюдении указанных ниже условий

#### 2. Обязательные условия

Все копии или существенные части программного обеспечения должны включать:
* Вышеуказанное уведомление об авторских правах
* Данное уведомление о разрешении
* Приведенное ниже заявление об отказе от ответственности

#### 3. Авторские права

Программное обеспечение и вся связанная с ним документация защищены законами об авторских правах. **AlderGrounds** сохраняет за собой оригинальные авторские права на программное обеспечение.

#### 4. Отказ от гарантий и ограничение ответственности

ПРОГРАММНОЕ ОБЕСПЕЧЕНИЕ ПРЕДОСТАВЛЯЕТСЯ "КАК ЕСТЬ", БЕЗ КАКИХ-ЛИБО ГАРАНТИЙ, ЯВНЫХ ИЛИ ПОДРАЗУМЕВАЕМЫХ, ВКЛЮЧАЯ, НО НЕ ОГРАНИЧИВАЯСЬ ГАРАНТИЯМИ ТОВАРНОЙ ПРИГОДНОСТИ, ПРИГОДНОСТИ ДЛЯ КОНКРЕТНОЙ ЦЕЛИ И НЕНАРУШЕНИЯ ПРАВ.

НИ ПРИ КАКИХ ОБСТОЯТЕЛЬСТВАХ АВТОРЫ ИЛИ ПРАВООБЛАДАТЕЛИ НЕ НЕСУТ ОТВЕТСТВЕННОСТИ ЗА ЛЮБЫЕ ПРЕТЕНЗИИ, УБЫТКИ ИЛИ ИНУЮ ОТВЕТСТВЕННОСТЬ, БУДЬ ТО В СИЛУ ДОГОВОРА, ДЕЛИКТА ИЛИ ИНЫМ ОБРАЗОМ, ВОЗНИКАЮЩИЕ ИЗ, ИЗ-ЗА ИЛИ В СВЯЗИ С ПРОГРАММНЫМ ОБЕСПЕЧЕНИЕМ ИЛИ ИСПОЛЬЗОВАНИЕМ ИЛИ ИНЫМИ ДЕЙСТВИЯМИ С ПРОГРАММНЫМ ОБЕСПЕЧЕНИЕМ.

---

Для подробной информации о лицензии MIT посетите: https://opensource.org/licenses/MIT