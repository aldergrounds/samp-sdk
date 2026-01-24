# SA-MP SDK

<div align="center">

![C++](https://img.shields.io/badge/C%2B%2B-17%2B-00599C?style=for-the-badge&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-blue?style=for-the-badge&logo=windows&logoColor=white)
![Architecture](https://img.shields.io/badge/Architecture-x86%20(32--bit)-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**Un SDK C++ moderno, header-only y de alto nivel para el desarrollo de plugins y módulos para SA-MP.**

</div>

## Idiomas

- Português: [README](../../)
- Deutsch: [README](../Deutsch/README.md)
- English: [README](../English/README.md)
- Français: [README](../Francais/README.md)
- Italiano: [README](../Italiano/README.md)
- Polski: [README](../Polski/README.md)
- Русский: [README](../Русский/README.md)
- Svenska: [README](../Svenska/README.md)
- Türkçe: [README](../Turkce/README.md)

## Índice

- [SA-MP SDK](#sa-mp-sdk)
  - [Idiomas](#idiomas)
  - [Índice](#índice)
  - [1. Introducción y Filosofía de Diseño](#1-introducción-y-filosofía-de-diseño)
    - [El Problema con la API C Estándar de SA-MP](#el-problema-con-la-api-c-estándar-de-sa-mp)
    - [La Solución del SA-MP SDK: Abstracción con Seguridad y Performance](#la-solución-del-sa-mp-sdk-abstracción-con-seguridad-y-performance)
    - [Modelo Header-Only: Ventajas e Implicaciones](#modelo-header-only-ventajas-e-implicaciones)
  - [2. Configuración y Ambiente](#2-configuración-y-ambiente)
    - [Requisitos de Compilación](#requisitos-de-compilación)
    - [Estructura de Archivos Recomendada](#estructura-de-archivos-recomendada)
    - [Macros Esenciales de Configuración](#macros-esenciales-de-configuración)
      - [`SAMP_SDK_IMPLEMENTATION`](#samp_sdk_implementation)
      - [`SAMP_SDK_WANT_AMX_EVENTS`](#samp_sdk_want_amx_events)
      - [`SAMP_SDK_WANT_PROCESS_TICK`](#samp_sdk_want_process_tick)
    - [Definiciones y Constantes de SA-MP (`samp_defs.hpp`)](#definiciones-y-constantes-de-sa-mp-samp_defshpp)
  - [3. Guía de Uso Abrangente de la API](#3-guía-de-uso-abrangente-de-la-api)
    - [3.1. El Ciclo de Vida del Plugin](#31-el-ciclo-de-vida-del-plugin)
      - [`bool OnLoad()`](#bool-onload)
      - [`void OnUnload()`](#void-onunload)
      - [`unsigned int GetSupportFlags()`](#unsigned-int-getsupportflags)
      - [`void OnAmxLoad(AMX* amx)`](#void-onamxloadamx-amx)
      - [`void OnAmxUnload(AMX* amx)`](#void-onamxunloadamx-amx)
      - [`void OnProcessTick()`](#void-onprocesstick)
    - [3.2. Exportando Funciones del Plugin](#32-exportando-funciones-del-plugin)
      - [Exportación para MSVC (Visual Studio) con `Export_Plugin`](#exportación-para-msvc-visual-studio-con-export_plugin)
      - [Exportación para GCC / Clang con `SAMP_SDK_EXPORT`](#exportación-para-gcc--clang-con-samp_sdk_export)
    - [3.3. `Plugin_Public`: Interceptando Eventos de Pawn](#33-plugin_public-interceptando-eventos-de-pawn)
      - [Sintaxis y Declaración](#sintaxis-y-declaración)
      - [Marshalling Automático de Parámetros](#marshalling-automático-de-parámetros)
      - [Control de Flujo: `PUBLIC_CONTINUE` vs `PUBLIC_STOP`](#control-de-flujo-public_continue-vs-public_stop)
      - [Ghost Callbacks](#ghost-callbacks)
    - [3.4. `Plugin_Native`: Creando Funciones Nativas en C++](#34-plugin_native-creando-funciones-nativas-en-c)
      - [Sintaxis y Firma Fija](#sintaxis-y-firma-fija)
      - [Registro Automático de Nativas](#registro-automático-de-nativas)
      - [Extracción de Parámetros: `Register_Parameters` vs. `Native_Params`](#extracción-de-parámetros-register_parameters-vs-native_params)
        - [`Register_Parameters(...)`](#register_parameters)
        - [`Native_Params` (API Completa: `Get`, `Get_REF`, `Set_REF`)](#native_params-api-completa-get-get_ref-set_ref)
          - [`p.Count()`](#pcount)
          - [`p.Get<T>(size_t index)`](#pgettsize_t-index)
          - [`p.Get_REF<T>(size_t index, T& out_value)`](#pget_reftsize_t-index-t-out_value)
          - [`p.Get_REF<T>(size_t index)` (C++17+)](#pget_reftsize_t-index-c17)
          - [`p.Set_REF<T>(size_t index, T value)`](#pset_reftsize_t-index-t-value)
      - [Retorno de Valores](#retorno-de-valores)
    - [3.5. `Plugin_Native_Hook`: Interceptando Nativas Existentes de SA-MP](#35-plugin_native_hook-interceptando-nativas-existentes-de-sa-mp)
      - [Sintaxis y Firma Fija](#sintaxis-y-firma-fija-1)
      - [Registro y Activación del Hook](#registro-y-activación-del-hook)
      - [Llamando a la Native Original (Cadena de Hooks): `Call_Original_Native`](#llamando-a-la-native-original-cadena-de-hooks-call_original_native)
      - [Ejemplo Completo de `Plugin_Native_Hook`](#ejemplo-completo-de-plugin_native_hook)
    - [3.6. `Pawn_*` Macros: Llamando Funciones de Pawn desde C++](#36-pawn_-macros-llamando-funciones-de-pawn-desde-c)
      - [`Pawn_Native(NombreDeLaNative, ...)`](#pawn_nativenombredelanative-)
      - [`Pawn_Public(NombreDeLaPublic, ...)`](#pawn_publicnombredelapublic-)
      - [`Pawn(NombreDeLaFuncion, ...)`](#pawnnombredelafuncion-)
      - [Sintaxis y Convenciones](#sintaxis-y-convenciones)
      - [Marshalling de Parámetros de Entrada](#marshalling-de-parámetros-de-entrada)
      - [Marshalling de Parámetros de Salida (Referencias: `int&`, `float&`, `std::string&`)](#marshalling-de-parámetros-de-salida-referencias-int-float-stdstring)
      - [El Objeto `Callback_Result`: Análisis Completo](#el-objeto-callback_result-análisis-completo)
    - [3.7. `Plugin_Module`: Administración de Módulos Dinámicos](#37-plugin_module-administración-de-módulos-dinámicos)
      - [Sintaxis y Propósito](#sintaxis-y-propósito)
      - [Ciclo de Vida de un Módulo](#ciclo-de-vida-de-un-módulo)
      - [Beneficios de la Modularización](#beneficios-de-la-modularización)
    - [3.8. `Plugin_Call`: Llamando Nativas Internas del Plugin](#38-plugin_call-llamando-nativas-internas-del-plugin)
      - [Sintaxis y Ventajas de Performance](#sintaxis-y-ventajas-de-performance)
    - [3.9. Funciones Utilitarias del SDK](#39-funciones-utilitarias-del-sdk)
      - [`Samp_SDK::Log(const char* format, ...)`](#samp_sdklogconst-char-format-)
      - [`std::string Plugin_Format(const char* format, ...)` (Recomendado)](#stdstring-plugin_formatconst-char-format--recomendado)
      - [`std::string Samp_SDK::Format(const char* format, ...)` (Detalle de Implementación)](#stdstring-samp_sdkformatconst-char-format--detalle-de-implementación)
      - [`std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`](#stdstring-samp_sdkget_stringamx-amx-cell-amx_addr)
  - [4. Compilación y Despliegue](#4-compilación-y-despliegue)
    - [Requisitos de Arquitectura y Plataforma](#requisitos-de-arquitectura-y-plataforma)
    - [Ejemplos de Comandos de Compilación](#ejemplos-de-comandos-de-compilación)
      - [**MSVC (Visual Studio)**](#msvc-visual-studio)
      - [**GCC / Clang (Linux)**](#gcc--clang-linux)
      - [**GCC / Clang (MinGW en Windows)**](#gcc--clang-mingw-en-windows)
    - [Consideraciones para la Distribución](#consideraciones-para-la-distribución)
  - [Licencia](#licencia)
    - [Términos y Condiciones de Uso](#términos-y-condiciones-de-uso)
      - [1. Permisos Otorgados](#1-permisos-otorgados)
      - [2. Condiciones Obligatorias](#2-condiciones-obligatorias)
      - [3. Derechos de Autor](#3-derechos-de-autor)
      - [4. Exención de Garantías y Limitación de Responsabilidad](#4-exención-de-garantías-y-limitación-de-responsabilidad)

## 1. Introducción y Filosofía de Diseño

### El Problema con la API C Estándar de SA-MP

La API de plugins de SA-MP es una interfaz de programación en C. Aunque funcional y fundamental, presenta los desafíos inherentes a la programación de bajo nivel:
- **Administración Manual de Memoria:** Funciones como `amx_Allot` y `amx_Release` exigen que el desarrollador asigne y desasigne explícitamente la memoria en el heap de la AMX. Esto es una fuente común de fugas de memoria y fallos de runtime.
- **Tipado Débil y Conversiones Manuales:** Los parámetros se pasan como un array de `cell`s, forzando conversiones explícitas (y muchas veces inseguras) entre `cell`, `int`, `float` y `char*`.
- **Verbosidad y Código Repetitivo (Boilerplate):** Extraer múltiples parámetros de un array `cell* params`, manejar tamaños de strings y administrar la pila de la AMX para las llamadas de retorno de C++ a Pawn requiere código repetitivo.
- **Fragilidad de la Interfaz:** La falta de verificación en tiempo de compilación (type safety) significa que los errores en el paso de parámetros o tipos pueden pasar desapercibidos hasta la ejecución, causando bloqueos o comportamientos indefinidos.

### La Solución del SA-MP SDK: Abstracción con Seguridad y Performance

El SA-MP SDK aborda estos problemas proporcionando una potente capa de abstracción en C++:
- **RAII (Resource Acquisition Is Initialization):** Administración automática de memoria en la AMX. `Amx_Scoped_Memory` garantiza que la memoria asignada sea liberada.
- **Seguridad de Tipos:** Conversión automática y segura de parámetros entre C++ y Pawn. Usted trabaja con `int`, `float`, `std::string` directamente.
- **Sintaxis Concisa e Idiomática:** Las macros y las plantillas proporcionan una API limpia que se asemeja más al C++ moderno que a la API C tradicional.
- **Interceptación Robusta:** Un motor de hooking avanzado permite la interceptación transparente de callbacks de Pawn (`Plugin_Public`), la creación de nuevas nativas (`Plugin_Native`), y **el hooking y encadenamiento de funciones nativas existentes de SA-MP (`Plugin_Native_Hook`)**.
- **Alto Rendimiento:** Uso extensivo de hashing en tiempo de compilación (FNV1a), caching de funciones y optimizaciones de `thread_local` para minimizar la sobrecarga de las abstracciones.

### Modelo Header-Only: Ventajas e Implicaciones

El SDK está compuesto exclusivamente por archivos de cabecera (`.hpp`, `.h`).
- **Ventajas:**
   - **Integración Simplificada:** No hay bibliotecas para construir, vincular o distribuir. Simplemente incluya los headers.
   - **Optimizaciones del Compilador:** El compilador tiene visibilidad completa del código del SDK y de su plugin, permitiendo inlining agresivo y optimizaciones de tiempo de enlazado, lo que puede resultar en binarios más rápidos.
- **Implicaciones:**
   - **Tiempo de Compilación:** Para proyectos muy grandes, la compilación puede llevar más tiempo debido a la inclusión repetida del código del SDK. Esto se mitiga con guards de inclusión y por la naturaleza de "incluir solo lo necesario" de C++.
   - **Macros de Implementación:** La necesidad de la macro `SAMP_SDK_IMPLEMENTATION` es una consecuencia del modelo header-only para evitar redefiniciones de símbolos.

## 2. Configuración y Ambiente

### Requisitos de Compilación

- **Compilador C++:** Compatible con C++17 o superior.
   - GCC (versión 8+)
   - Clang (versión 5+)
   - MSVC (Visual Studio 2017+)
- **Arquitectura:** **x86 (32 bits)**. SA-MP opera exclusivamente en esta arquitectura. El SDK incluye comprobaciones en `platform.hpp` que emitirán errores de compilación si se detecta una arquitectura incorrecta.
- **Sistema Operativo:** Windows o Linux.

### Estructura de Archivos Recomendada

Para mayor claridad y organización, es común organizar el SDK en una subcarpeta `samp-sdk`.

```
my_plugin/
├── samp-sdk/
│   ├── // Otros archivos del SDK
│   └── samp_sdk.hpp // El principal header a incluir
│
├── src/
│   ├── main.cpp // Donde se define SAMP_SDK_IMPLEMENTATION
│   └── my_custom_logic.cpp // Opcional, para organizar el código
│
└── CMakeLists.txt (o .vcxproj, Makefile)
```

### Macros Esenciales de Configuración

Siempre defina estas macros *antes* de incluir `samp_sdk.hpp`.

#### `SAMP_SDK_IMPLEMENTATION`

- **Propósito:** Señaliza al compilador que este archivo `.cpp` debe generar las implementaciones de las funciones de exportación del plugin (`Supports`, `Load`, `Unload`, `AmxLoad`, `AmxUnload`, `ProcessTick`). **El SDK se encarga de la exportación de estas funciones automáticamente, eliminando la necesidad de archivos `.def` (en Windows) o declaraciones `__attribute__((visibility("default")))` (en Linux) para estas funciones.**
- **Impacto Técnico:** Sin esta macro, el enlazador no encontrará las exportaciones necesarias, y el servidor SA-MP no podrá cargar su plugin.
- **Regla Fundamental:** **Defina esta macro en SÓLO UN archivo `.cpp` en todo su proyecto.** Definirla en más de un archivo causará un error de enlazado de "símbolo duplicado".

```cpp
// main.cpp
#define SAMP_SDK_IMPLEMENTATION // La macro hace que el SDK exporte las funciones necesarias automáticamente.
#include "samp-sdk/samp_sdk.hpp"

// ... su código de plugin ...
```

#### `SAMP_SDK_WANT_AMX_EVENTS`

- **Propósito:** Habilita los callbacks de ciclo de vida del script Pawn (`OnAmxLoad`, `OnAmxUnload`) y la funcionalidad de crear nuevas nativas en C++ (`Plugin_Native`).
- **Funcionalidades Activadas:**
   - Callbacks `OnAmxLoad(AMX* amx)` y `OnAmxUnload(AMX* amx)`.
   - Declaración y registro de nuevas nativas C++ usando `Plugin_Native`.
   - La macro `Plugin_Call` para invocar nativas creadas con `Plugin_Native` dentro de su propio plugin.
- **Impacto Técnico:** Cuando se define esta macro, el SDK recolecta automáticamente todas sus `Plugin_Native`s. En la función `Supports()`, la flag `SUPPORTS_AMX_NATIVES` se añade automáticamente si hay alguna `Plugin_Native` en su proyecto.
- **Flexibilidad:** **Puede definir esta macro en múltiples archivos `.cpp`**. El sistema de registro estático del SDK consolidará todas las nativas de diferentes unidades de compilación en una única lista global.

```cpp
// my_natives.cpp (puede ser un archivo separado de main.cpp)
#define SAMP_SDK_WANT_AMX_EVENTS // Solo para habilitar Plugin_Native y los callbacks OnAmxLoad/OnAmxUnload
#include "samp-sdk/samp_sdk.hpp"

Plugin_Native(MyCustomNative, AMX* amx, cell* params) {
    // ...
    return 0;
}
```

#### `SAMP_SDK_WANT_PROCESS_TICK`

- **Propósito:** Habilita el callback `OnProcessTick()`, que es invocado regularmente por el servidor.
- **Impacto Técnico:** Añade automáticamente la flag `SUPPORTS_PROCESS_TICK` en la función `Supports()`.

```cpp
// main.cpp
#define SAMP_SDK_IMPLEMENTATION
#define SAMP_SDK_WANT_PROCESS_TICK
#include "samp-sdk/samp_sdk.hpp"

void OnProcessTick() {
    // Lógica ejecutada en cada "tick" del servidor (ej: 20ms)
    // ¡Cuidado con operaciones pesadas aquí!
}
```

### Definiciones y Constantes de SA-MP (`samp_defs.hpp`)

Este archivo proporciona todas las constantes y límites conocidos de SA-MP, como `MAX_PLAYERS`, `INVALID_PLAYER_ID`, `PLAYER_STATE_ONFOOT`, `WEAPON_DEAGLE`, `DIALOG_STYLE_LIST`, etc. Se incluye automáticamente por `samp_sdk.hpp` y debe usarse para garantizar la compatibilidad y legibilidad del código.

## 3. Guía de Uso Abrangente de la API

### 3.1. El Ciclo de Vida del Plugin

Las siguientes funciones son los puntos de entrada y salida de su plugin, exportadas automáticamente por el SDK.

#### `bool OnLoad()`

- **Descripción:** Primera función llamada por el servidor SA-MP después de la carga exitosa de su plugin en memoria.
- **Uso:** Ideal para inicializar cualquier sistema, cargar configuraciones, abrir conexiones a bases de datos o cargar módulos (`Plugin_Module`).
- **Retorno:**
   - `true`: El plugin se inicializó con éxito y la carga continúa.
   - `false`: El plugin falló al inicializar. La carga se abortará y el plugin se descargará.

```cpp
// main.cpp
bool OnLoad() {
    Samp_SDK::Log("Inicializando MeuPlugin v1.0...");

    // Ejemplo: Cargar un módulo (más detalles en la sección 3.6)
    if (!Plugin_Module("my_database_module", "plugins/db_connector", "Módulo de Base de Datos cargado.")) {
        Samp_SDK::Log("ERROR: ¡Fallo al cargar el módulo de base de datos!");

        return false; // Aborta la carga del plugin principal
    }

    return true;
}
```

#### `void OnUnload()`

- **Descripción:** Última función llamada por el servidor SA-MP antes de descargar su plugin de la memoria.
- **Uso:** Ideal para limpiar recursos, cerrar conexiones, guardar estados y garantizar que no se filtren recursos. El SDK administra la descarga de módulos (`Plugin_Module`) automáticamente.

```cpp
// main.cpp
void OnUnload() {
    Samp_SDK::Log("MeuPlugin descargado. Liberando recursos...");
    // No se requiere ninguna acción manual para los módulos cargados a través de Plugin_Module;
    // el SDK se encarga de ello.
}
```

#### `unsigned int GetSupportFlags()`

- **Descripción:** Informa al servidor SA-MP qué recursos soporta y desea utilizar su plugin.
- **Uso:** **Siempre devuelva `SUPPORTS_VERSION` (o `SAMP_PLUGIN_VERSION`).** Las flags `SUPPORTS_AMX_NATIVES` y `SUPPORTS_PROCESS_TICK` son añadidas automáticamente por el SDK si hay `Plugin_Native`s, y/o si la macro `SAMP_SDK_WANT_PROCESS_TICK` está definida, respectivamente. Esto simplifica el mantenimiento y evita errores.

```cpp
// main.cpp
unsigned int GetSupportFlags() {
    return SUPPORTS_VERSION; // El SDK añade las flags necesarias automáticamente.
}
```

#### `void OnAmxLoad(AMX* amx)`

- **Requiere:** `SAMP_SDK_WANT_AMX_EVENTS`
- **Descripción:** Llamada cada vez que se carga e inicializa un nuevo script Pawn (un Gamemode o Filterscript) en el servidor.
- **Uso:** Si necesita lógica específica para cada script AMX, o inicializar datos específicos por script.

```cpp
// main.cpp (con SAMP_SDK_WANT_AMX_EVENTS definido)
void OnAmxLoad(AMX* amx) {
    // amx representa la nueva instancia del script cargado.
    Samp_SDK::Log("Script AMX cargado: %p", (void*)amx);
}
```

#### `void OnAmxUnload(AMX* amx)`

- **Requiere:** `SAMP_SDK_WANT_AMX_EVENTS`
- **Descripción:** Llamada cuando un script Pawn se descarga del servidor.
- **Uso:** Para limpiar cualquier recurso específico que haya asignado o asociado a esa `AMX*` en particular.

```cpp
// main.cpp (con SAMP_SDK_WANT_AMX_EVENTS definido)
void OnAmxUnload(AMX* amx) {
    Samp_SDK::Log("Script AMX descargado: %p", (void*)amx);
}
```

#### `void OnProcessTick()`

- **Requiere:** `SAMP_SDK_WANT_PROCESS_TICK`
- **Descripción:** Llamada repetidamente en cada "tick" del servidor (generalmente 20 veces por segundo, o cada 50ms).
- **Uso:** Para lógica de fondo continua, temporizadores, actualizaciones de estado que no dependen de eventos del jugador, o sincronización de datos.
- **Cuidado:** Evite operaciones de bloqueo o computacionalmente pesadas aquí, ya que pueden causar lag en el servidor.

```cpp
// main.cpp (con SAMP_SDK_WANT_PROCESS_TICK definido)
static int tick_count = 0;

void OnProcessTick() {
    tick_count++;

    if (tick_count % 200 == 0) // Cada 10 segundos (20 ticks/seg * 10 seg = 200 ticks)
        Samp_SDK::Log("Servidor activo por %d segundos.", tick_count / 20);
}
```

### 3.2. Exportando Funciones del Plugin

Para que el servidor SA-MP pueda llamar a las funciones de tu plugin (`Load`, `Supports`, etc.), estas necesitan ser "exportadas" del archivo DLL (Windows) o SO (Linux). El SDK automatiza la exportación de las funciones de ciclo de vida estándar, pero también proporciona herramientas para que puedas exportar tus propias funciones personalizadas, en caso de que necesites interoperabilidad con otros programas.

El método para exportar funciones varía según el compilador.

#### Exportación para MSVC (Visual Studio) con `Export_Plugin`

En Windows con MSVC, la forma más fácil de exportar funciones personalizadas es usando el macro `Export_Plugin`, definido en `exports.hpp`.

- **Sintaxis:** `Export_Plugin("Función", "Pila")`
- **`Función`**: El nombre exacto de la función a exportar.
- **`Pila`**: La cantidad total de bytes que los parámetros de la función ocupan en la pila. Para la convención `__stdcall` (estándar del SDK en Windows), el cálculo es `4 * (Cantidad de Parámetros)`.

```cpp
#include "samp-sdk/exports.hpp"

// Ejemplo: Exportando una función personalizada que podría ser llamada
// por otro programa o plugin que conozca su firma.
const char* SAMP_SDK_CALL GetPluginVersion() {
    return "1.0.0";
}

Export_Plugin("GetPluginVersion", "0");
```

> [!WARNING]
> **Limitación de `Export_Plugin`**
> Este macro funciona **solo con el compilador MSVC (Visual Studio)**. Utiliza una directiva `#pragma` específica de Microsoft que es ignorada por otros compiladores como GCC y Clang.

#### Exportación para GCC / Clang con `SAMP_SDK_EXPORT`

Para GCC y Clang (en Windows o Linux), la exportación es gestionada por el macro `SAMP_SDK_EXPORT`, definido en `platform.hpp`. Simplemente lo colocas antes de la definición de la función.

- **Mecanismo:** En Linux, añade `__attribute__((visibility("default")))`. En Windows con GCC/Clang, añade `__attribute__((dllexport))`.
- **Uso:** El SDK ya aplica `SAMP_SDK_EXPORT` a todas las funciones de ciclo de vida (`Load`, `Unload`, etc.), por lo que la exportación de estas es totalmente automática para estos compiladores. Para tus funciones personalizadas, simplemente haz lo mismo.

```cpp
// Para GCC/Clang, la definición de la función con SAMP_SDK_EXPORT es suficiente.
SAMP_SDK_EXPORT const char* SAMP_SDK_CALL GetPluginVersion() {
    return "1.0.0";
}
```

### 3.3. `Plugin_Public`: Interceptando Eventos de Pawn

La macro `Plugin_Public` es el puente principal para recibir callbacks de Pawn en su código C++.

#### Sintaxis y Declaración

- `Plugin_Public(NombreDeLaPublic, Tipo1 Param1, Tipo2 Param2, ...)`
- El nombre de la función C++ que usted declara **debe ser el mismo** que el callback de Pawn (ej: `OnPlayerConnect`).
- Los tipos de parámetros C++ (`int`, `float`, `std::string`) son automáticamente convertidos por el SDK.

```cpp
// Intercepta OnPlayerText(playerid, text[])
Plugin_Public(OnPlayerText, int playerid, std::string text) {
    Samp_SDK::Log("Jugador %d dijo: %s", playerid, text.c_str());

    return PUBLIC_CONTINUE;
}
```

#### Marshalling Automático de Parámetros

El SDK maneja automáticamente la lectura de la `cell stack` de la AMX y la conversión a los tipos C++ especificados:
- `int`: Convertido directamente de `cell`.
- `float`: Convertido de `cell` usando `amx::AMX_CTOF`.
- `std::string`: El SDK lee la dirección de la string en la AMX, asigna una `std::string` en C++ y copia el contenido.

#### Control de Flujo: `PUBLIC_CONTINUE` vs `PUBLIC_STOP`

El valor devuelto por su función `Plugin_Public` es crucial y determina el flujo de ejecución del callback:
- `return PUBLIC_CONTINUE;` (valor `1`): Indica que la ejecución del callback debe **continuar**. Si hay otros plugins que también interceptan este callback, se les llamará (en orden inverso de carga). Luego, se invocará la `public` original en el script Pawn.
- `return PUBLIC_STOP;` (valor `0`): Indica que la ejecución del callback debe ser **interrumpida**. Ningún otro plugin (con menor prioridad) o la `public` original en el script Pawn será invocado para este evento. Esto es ideal para implementar un sistema que "sobrescribe" o "bloquea" un comportamiento estándar de SA-MP.

```cpp
// main.cpp
Plugin_Public(OnPlayerCommandText, int playerid, std::string cmdtext) {
    if (cmdtext == "/freeze") {
        Pawn_Native(TogglePlayerControllable, playerid, 0); // Congela al jugador
        Pawn_Native(SendClientMessage, playerid, -1, Plugin_Format("Jugador %d congelado.", playerid));

        return PUBLIC_STOP; // Impide que el comando sea procesado por otros scripts.
    }

    return PUBLIC_CONTINUE; // Permite que otros comandos sean procesados.
}
```

#### Ghost Callbacks

Una característica avanzada de `Plugin_Public` es el soporte a "Ghost Callbacks". Esto significa que puede interceptar un callback de Pawn incluso si **no está presente** en el script `.amx` del gamemode o filterscript. El SDK "engaña" al servidor para que llame a su hook C++ de todas formas. Esto es útil para callbacks internos o para crear nuevas funcionalidades sin depender de la presencia de una `public` en el script Pawn.

```cpp
// Puede definir un callback que el script Pawn no posee, pero su plugin lo escuchará.
Plugin_Public(OnMyCustomInternalEvent, int data1, float data2) {
    Samp_SDK::Log("Evento interno personalizado recibido: %d, %.2f", data1, data2);

    return PUBLIC_CONTINUE;
}

// Para "disparar" este evento desde otro punto de su código C++:
// Pawn_Public(OnMyCustomInternalEvent, 123, 45.67f);
// La llamada irá a su Plugin_Public anterior, incluso si no hay OnMyCustomInternalEvent en Pawn.
```

### 3.4. `Plugin_Native`: Creando Funciones Nativas en C++

`Plugin_Native` le permite extender la funcionalidad de Pawn con código C++ de alto rendimiento.

#### Sintaxis y Firma Fija

- `Plugin_Native(NombreDeLaNative, AMX* amx, cell* params)`
- La función C++ debe tener exactamente esta firma: `cell NombreDeLaNative(AMX* amx, cell* params)`.
- `NombreDeLaNative` es el nombre que utilizarán los scripts Pawn.

```cpp
// Pawn: native GetPlayerPingAverage(playerid);
Plugin_Native(GetPlayerPingAverage, AMX* amx, cell* params) {
    // ... Implementación ...
    return 0;
}
```

#### Registro Automático de Nativas

> [!NOTE]
> No necesita llamar a `amx_Register` manualmente. El SDK detecta todas sus `Plugin_Native`s (en cualquier archivo `.cpp` que haya incluido `samp_sdk.hpp` y definido `SAMP_SDK_WANT_AMX_EVENTS`) y las registra automáticamente en cada script AMX cargado (`OnAmxLoad`).

#### Extracción de Parámetros: `Register_Parameters` vs. `Native_Params`

##### `Register_Parameters(...)`

- **Descripción:** Un asistente más simple para extraer múltiples parámetros secuencialmente.
- **Uso:** `Register_Parameters(variable1, variable2, ...)`
- **Limitaciones:** Para parámetros de entrada. No maneja parámetros opcionales o acceso por índice.
- **Tipos Soportados:** `int`, `float`, `std::string`.

```cpp
// Pawn: native SetPlayerSkinAndMoney(playerid, skinid, money);
Plugin_Native(SetPlayerSkinAndMoney, AMX* amx, cell* params) {
    int playerid, skinid, money;
    Register_Parameters(playerid, skinid, money); // Extrae los 3 parámetros
    
    Pawn_Native(SetPlayerSkin, playerid, skinid);
    Pawn_Native(GivePlayerMoney, playerid, money);
    
    return 1;
}
```

##### `Native_Params` (API Completa: `Get`, `Get_REF`, `Set_REF`)

- **Descripción:** Una clase wrapper que proporciona una interfaz orientada a objetos para acceder a los parámetros de una nativa. Más potente para escenarios complejos.
- **Construcción:** `Native_Params p(amx, params);`

###### `p.Count()`

- **Descripción:** Devuelve el número de parámetros pasados a la nativa.
- **Uso:** Esencial para manejar parámetros opcionales.

###### `p.Get<T>(size_t index)`

- **Descripción:** Extrae un parámetro de entrada por índice y lo convierte al tipo `T`.
- **Tipos Soportados:** `int`, `float`, `std::string`.

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

- **Descripción:** Obtiene el valor de un parámetro de **referencia** (puntero Pawn) y lo almacena en `out_value`.
- **Uso:** Para leer valores que fueron pasados por referencia desde Pawn.
- **Retorno:** `true` si la dirección AMX es válida, `false` en caso contrario.

```cpp
// Pawn: native CheckPlayerStats(playerid, &Float:health, &money);
Plugin_Native(CheckPlayerStats, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    
    int playerid = p.Get<int>(0);
    float health = 0.0f;
    int money = 0;

    // Obtiene los valores de las referencias (Pawn pasó direcciones)
    p.Get_REF(1, health); // Lee el valor de Float:health
    p.Get_REF(2, money);   // Lee el valor de money
    
    Samp_SDK::Log("Jugador %d, Health: %.1f, Money: %d", playerid, health, money);
    
    // Ahora, modificarlos
    health = 50.0f;
    money += 100;
    
    // Y escribirlos de vuelta en la memoria de Pawn
    p.Set_REF(1, health);
    p.Set_REF(2, money);
    
    return 1;
}
```

###### `p.Get_REF<T>(size_t index)` (C++17+)

- **Descripción:** Devuelve un `std::optional<T>` para leer un parámetro de referencia. Más seguro para C++17 y superior.

###### `p.Set_REF<T>(size_t index, T value)`

- **Descripción:** Escribe un valor `T` en un parámetro de **referencia** de Pawn (la dirección que Pawn pasó).
- **Uso:** Para modificar valores que fueron pasados por referencia, haciendo que Pawn vea el cambio.
- **Retorno:** `true` si la escritura fue exitosa, `false` en caso contrario.

#### Retorno de Valores

- Su función `Plugin_Native` debe retornar una `cell`.
- Para retornar un `int` o `bool`, use un cast a `cell`.
- Para retornar un `float`, use `amx::AMX_FTOC(mi_float)`.

```cpp
// Retorna un bool
Plugin_Native(IsPlayerSpawned, AMX* amx, cell* params) {
    int playerid;
    Register_Parameters(playerid);

    return (Pawn_Native(GetPlayerState, playerid) == PLAYER_STATE_SPAWNED) ? 1 : 0;
}

// Retorna un float
Plugin_Native(GetPlayerMaxHealth, AMX* amx, cell* params) {
    return amx::AMX_FTOC(100.0f); // Retorna 100.0f
}
```

### 3.5. `Plugin_Native_Hook`: Interceptando Nativas Existentes de SA-MP

La macro `Plugin_Native_Hook` le permite interceptar y modificar el comportamiento de cualquier función nativa existente de SA-MP o de otros plugins. Este es un mecanismo potente para extender o alterar la lógica estándar del servidor.

#### Sintaxis y Firma Fija

- `Plugin_Native_Hook(NombreDeLaNative, AMX* amx, cell* params)`
- La función C++ debe tener exactamente esta firma: `cell NombreDeLaNative(AMX* amx, cell* params)`.
- `NombreDeLaNative` debe ser el nombre exacto de la native que desea hookear (ej: `SendClientMessage`, `SetPlayerPos`).

```cpp
// Intercepta la native SendClientMessage
Plugin_Native_Hook(SendClientMessage, AMX* amx, cell* params) {
    // ...
    return Call_Original_Native(SendClientMessage); // Importante llamar a la original
}
```

#### Registro y Activación del Hook

> [!NOTE]
> No necesita llamar a `amx_Register` manualmente o definir `SAMP_SDK_WANT_AMX_EVENTS` específicamente para `Plugin_Native_Hook`. El SDK detecta y registra automáticamente sus hooks. En la primera ejecución de un script AMX, el SDK reemplaza el puntero de la native en la tabla por un "trampoline" que redirige a su función `Plugin_Native_Hook`. Este proceso garantiza el encadenamiento seguro de hooks de múltiples plugins.

#### Llamando a la Native Original (Cadena de Hooks): `Call_Original_Native`

Dentro de su función `Plugin_Native_Hook`, **DEBE** usar la macro `Call_Original_Native(NombreDeLaNative)` para invocar la función original (o el siguiente hook en la cadena). Esto es vital para:
- **Preservar la Funcionalidad:** Si no llama a la original, la native hookeada simplemente dejará de funcionar para otros plugins o para el servidor.
- **Encadenamiento de Hooks:** Permite que múltiples plugins hookeen la misma native y que todos los hooks se ejecuten en una secuencia.
- **Manipulación de Retorno:** Puede inspeccionar e incluso modificar el valor de retorno de `Call_Original_Native` antes de retornarlo desde su función de hook.

```cpp
// Ejemplo: Bloqueando SendClientMessage si contiene una palabra específica
Plugin_Native_Hook(SendClientMessage, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    
    // Extrae los parámetros para análisis
    int playerid = p.Get<int>(0);
    // int color = p.Get<int>(1); // No necesitamos el color para esta lógica
    std::string message = p.Get_String(2); // Obtiene la string del mensaje

    if (message.find("BADWORD") != std::string::npos) {
        Samp_SDK::Log("MENSAJE BLOQUEADO para playerid %d: %s", playerid, message.c_str());

        return 0; // Retorna 0 (false) a Pawn, indicando que el mensaje no fue enviado.
                  // Y lo que es más importante, NO llamamos a Call_Original_Native, bloqueando el mensaje.
    }

    // Si el mensaje no contiene la palabra prohibida, llamamos a la native original
    // y retornamos su valor, garantizando que el mensaje se envíe normalmente
    // y que otros hooks (si existen) se ejecuten.
    return Call_Original_Native(SendClientMessage);
}
```

#### Ejemplo Completo de `Plugin_Native_Hook`

```cpp
#define SAMP_SDK_IMPLEMENTATION
// SAMP_SDK_WANT_AMX_EVENTS no es estrictamente necesario para hooks, pero es común tener OnAmxLoad/Unload
// #define SAMP_SDK_WANT_AMX_EVENTS 
#include "samp-sdk/samp_sdk.hpp"

// Hook para la native CreateVehicle
Plugin_Native_Hook(CreateVehicle, AMX* amx, cell* params) {
    Native_Params p(amx, params);

    // Extrae los parámetros de la native CreateVehicle para inspección
    int modelid = p.Get<int>(0);
    float x = p.Get<float>(1);
    float y = p.Get<float>(2);
    float z = p.Get<float>(3);
    float angle = p.Get<float>(4);
    int color1 = p.Get<int>(5);
    int color2 = p.Get<int>(6);
    int respawn_delay = p.Get<int>(7);
    bool addsiren = p.Get<bool>(8);

    Samp_SDK::Log("HOOK: CreateVehicle llamado! Model: %d, Pos: (%.2f, %.2f, %.2f)", modelid, x, y, z);

    // Ejemplo de cómo *modificar* un parámetro de entrada
    // Si el modelo es 400 (Landstalker), lo cambiamos a 401 (Bravura)
    if (modelid == 400) {
        // Modificamos directamente el array 'params' para la llamada original
        params[1] = static_cast<cell>(401); // El modelo está en la posición 0 del array de parámetros (params[1])
        Samp_SDK::Log("  -> Modelo 400 cambiado a 401 antes de la creación.");
    }
    
    // Llamamos a la native original (o el siguiente hook en la cadena) con los parámetros posiblemente modificados
    cell original_retval = Call_Original_Native(CreateVehicle);

    Samp_SDK::Log("HOOK: CreateVehicle retornó: %d (ID del vehículo)", (int)original_retval);

    // Puede modificar el valor de retorno aquí antes de retornarlo a Pawn.
    // Ejemplo: si el vehículo falló en la creación, retorne un ID inválido personalizado.
    if ((int)original_retval == INVALID_VEHICLE_ID) {
        Samp_SDK::Log("  -> La creación del vehículo falló en la native original.");

        return -1; // Retorna un valor diferente a Pawn.
    }

    return original_retval; // Retorna el valor que la native original retornó (o el modificado anteriormente).
}

unsigned int GetSupportFlags() {
    return SUPPORTS_VERSION; 
}

// Implementaciones mínimas para el ciclo de vida
bool OnLoad() {
    Samp_SDK::Log("¡Plugin de Ejemplo de Native Hook cargado!");
    return true;
}

void OnUnload() {
    Samp_SDK::Log("¡Plugin de Ejemplo de Native Hook descargado!");
}

// Estos callbacks solo estarán presentes si SAMP_SDK_WANT_AMX_EVENTS está definido
/*void OnAmxLoad(AMX* amx) {
    Samp_SDK::Log("AMX Load detectado: %p", (void*)amx);
}

void OnAmxUnload(AMX* amx) {
    Samp_SDK::Log("AMX Unload detectado: %p", (void*)amx);
}*/
```
> [!WARNING]
> La manipulación directa del array `cell* params` para alterar parámetros de entrada exige cautela. Asegúrese de entender el orden y el tipo de los parámetros. Para la mayoría de los casos de uso, `p.Get(...)` para inspeccionar y `Call_Original_Native(...)` para continuar la cadena es suficiente. La alteración directa de `params` debe hacerse solo si sabe que el parámetro es un valor y necesita ser modificado para la llamada original. Para strings y arrays, la modificación es más compleja y generalmente implica `amx::Set_String` para escribir en la dirección existente o reasignar, lo que puede ser más fácil de manejar llamando a la native a través de `Pawn_Native` con los nuevos valores y retornando `0` de su hook para cancelar la llamada original.

### 3.6. `Pawn_*` Macros: Llamando Funciones de Pawn desde C++

Estas macros son el inverso de `Plugin_Public` y `Plugin_Native`: permiten que su código C++ invoque funciones de Pawn.

#### `Pawn_Native(NombreDeLaNative, ...)`

- **Propósito:** La forma recomendada de llamar funciones nativas de SA-MP (o de otros plugins) desde C++.
- **Mecanismo:** Busca el puntero de la nativa en el caché interno del SDK (rellenado por `Amx_Register_Detour`). Si se encuentra, ejecuta la nativa en un entorno `Amx_Sandbox` (una instancia AMX falsa y aislada).
- **Rendimiento:** La más eficiente, ya que evita la costosa búsqueda de `publics` e interactúa directamente con el puntero de la nativa.

#### `Pawn_Public(NombreDeLaPublic, ...)`

- **Propósito:** Llama a una función pública específica en un script Pawn.
- **Mecanismo:** Recorre las instancias `AMX*` administradas por el `Amx_Manager`, busca la `public` por su nombre y la ejecuta.
- **Rendimiento:** Menos eficiente que `Pawn_Native` debido a la búsqueda y al `amx_Exec` real. Generalmente, las `publics` son más lentas que las `natives`.
- **Uso:** Ideal para invocar eventos personalizados en su Gamemode/Filterscripts que no son nativas.

#### `Pawn(NombreDeLaFuncion, ...)`

- **Propósito:** Una macro de conveniencia que intenta adivinar si la función es una nativa o una pública.
- **Mecanismo:** Primero, intenta llamar como `Pawn_Native`. Si falla (no se encuentra la nativa), intenta llamar como `Pawn_Public`.
- **Rendimiento:** Puede ser un poco más lenta que `Pawn_Native` si la función es nativa, debido al intento de búsqueda doble. Para `publics`, el rendimiento es el mismo que `Pawn_Public`.
- **Uso:** Para funciones donde no está seguro si son nativas o públicas, o para evitar el código repetitivo de intentar una y luego la otra.

#### Sintaxis y Convenciones

- **Nombre de la Función:** Siempre use el nombre de la función Pawn **directamente, sin comillas**. El SDK lo convertirá a string internamente.
- **Parámetros:** Pase los parámetros C++ directamente.

```cpp
// Correcto:
Pawn_Native(SetPlayerPos, playerid, 100.0f, 200.0f, 300.0f); 

// Incorrecto (pero técnicamente funcionaría debido al hash, evítelo):
Pawn_Native("SetPlayerPos", playerid, 100.0f, 200.0f, 300.0f); 
```

#### Marshalling de Parámetros de Entrada

El SDK convierte sus tipos C++ al formato `cell` de la AMX, administrando la memoria según sea necesario:
- `int`, `bool`, `long`, `enum` -> `cell`
- `float`, `double` -> `cell` (usando `amx::AMX_FTOC`)
- `const char*`, `std::string`, `std::string_view` (C++17+) -> `cell` (asigna memoria en la AMX, copia la string y pasa la dirección `amx_addr`)

```cpp
void Send_Formatted_Message(int playerid, const std::string& msg) {
    Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, msg);
}
```

#### Marshalling de Parámetros de Salida (Referencias: `int&`, `float&`, `std::string&`)

Esta es una funcionalidad clave para la comodidad y seguridad. Para funciones de Pawn que esperan un puntero (referencia), el SDK automatiza todo el proceso de asignación/liberación de memoria y copia de datos.

- **Cómo usar:** Simplemente pase su variable por referencia (`&`).
- **Mecanismo:** El SDK asigna memoria en el heap de la AMX, pasa la dirección AMX a la función de Pawn, espera que la función de Pawn rellene esa dirección, lee el valor de vuelta y libera la memoria de la AMX. Todo de forma transparente.
- **Con `std::string&`:** El SDK asigna un búfer estándar (256 celdas) en la AMX para la string.

```cpp
void Get_Player_Location(int playerid) {
    float x, y, z;
    int interiorid, worldid;
    std::string name;

    Pawn_Native(GetPlayerPos, playerid, x, y, z);
    Pawn_Native(GetPlayerInterior, playerid, interiorid);
    Pawn_Native(GetPlayerVirtualWorld, playerid, worldid);
    Pawn_Native(GetPlayerName, playerid, name, MAX_PLAYER_NAME);

    Samp_SDK::Log("Ubicación de %s (ID:%d): Pos(%.2f, %.2f, %.2f) Interior:%d World:%d", name.c_str(), playerid, x, y, z, interiorid, worldid);
}
```

#### El Objeto `Callback_Result`: Análisis Completo

Todas las llamadas `Pawn_*` devuelven un objeto `Callback_Result`. Este objeto es un envoltorio seguro para el resultado de la llamada de Pawn.

- `Callback_Result() noexcept`: Constructor predeterminado, indica fallo (`success_ = false`).
- `Callback_Result(bool success, cell value) noexcept`: Constructor para éxito o fallo con valor.
- `explicit operator bool() const`: Permite usar `if (result)` para verificar si la llamada fue exitosa.
- `operator cell() const`: Permite convertir el resultado a `cell` para obtener el valor.
- `float As_Float() const`: Conveniencia para obtener el resultado como `float`.
- `cell Value() const`: Retorna el valor `cell` bruto.
- `bool Success() const`: Retorna `true` si la llamada de Pawn fue exitosa.
- `int Get_Amx_Error() const`: Retorna el código de error de la AMX si la llamada falló (0 para éxito).

```cpp
// Ejemplo: Obteniendo la vida de un jugador.
// La nativa GetPlayerHealth(playerid, &Float:health) espera un playerid y una referencia para la vida.
int playerid = 0; // Ejemplo de ID de jugador
float player_health = 0.0f;

// Llamamos a GetPlayerHealth, pasando playerid y player_health por referencia.
// El SDK se encargará del marshalling para el parámetro de salida 'health'.
Callback_Result result = Pawn_Native(GetPlayerHealth, playerid, player_health);

if (result) { // Verifica si la llamada fue exitosa (operator bool)
    // El valor retornado por result.As_Float() o result (operator cell)
    // sería el valor de retorno de la *nativa*, no el parámetro de salida.
    // El valor de la vida ya se actualizó en 'player_health' debido al marshalling del parámetro de salida.
    Samp_SDK::Log("Jugador %d tiene %.1f de vida.", playerid, player_health);
}
else {
    // La llamada falló, quizás el jugador no existe o la nativa no fue encontrada.
    Samp_SDK::Log("Error al obtener vida del jugador %d. Código AMX: %d", playerid, result.Get_Amx_Error());
}

// Para nativas que devuelven un valor y usan parámetros de salida (menos común, pero posible),
// usted usaría ambos:
// Callback_Result other_result = Pawn_Native(SomeNative, param1, output_param, param2);
// if (other_result) {
//     cell returned_value = other_result;
//     // output_param ya está actualizado
// }
```

### 3.7. `Plugin_Module`: Administración de Módulos Dinámicos

La macro `Plugin_Module` permite que su plugin actúe como un "cargador" para otros plugins, creando una arquitectura modular y extensible. Un módulo cargado de esta forma es tratado como un plugin de primera clase, con su propio ciclo de vida de eventos administrado por el plugin anfitrión.

#### Sintaxis y Propósito

- `Plugin_Module(const char* nombre_del_archivo_base, const char* directorio_del_modulo, const char* mensaje_exito_opcional)`
- `nombre_del_archivo_base`: El nombre *base* del archivo del módulo, **sin la extensión** (ej: para `my_module.dll` o `my_module.so`, use `"my_module"`). El SDK agregará automáticamente la extensión `.dll` o `.so` apropiada.
- `directorio_del_modulo`: La ruta del directorio donde se encuentra el archivo del módulo (ej: `"plugins/my_custom_modules"`). **No incluya el nombre del archivo aquí.** El SDK concatenará la ruta completa (`directorio_del_modulo/nombre_del_archivo_base.ext`).
- `mensaje_exito_opcional`: Un mensaje opcional que se registrará en la consola del servidor si el módulo se carga con éxito.

```cpp
// main.cpp, dentro de OnLoad()

// Carga el módulo 'core_logic.dll' (o 'core_logic.so')
// que está ubicado en la carpeta 'modules/custom/' del servidor.
if (!Plugin_Module("core_logic", "modules/custom", "¡Módulo de Lógica Core cargado con éxito!"))
    return (Samp_SDK::Log("¡ERROR FATAL: Fallo al cargar el módulo 'core_logic'!"), false);

// Carga el módulo 'admin_system.dll' (o 'admin_system.so')
// que está ubicado directamente en la carpeta 'plugins/' del servidor.
if (!Plugin_Module("admin_system", "plugins", "Módulo de Administración activado."))
    Samp_SDK::Log("AVISO: El módulo de Administración no pudo ser cargado.");
```

#### Ciclo de Vida de un Módulo

Un módulo debe exportar las funciones `Load`, `Unload` y `Supports`, al igual que un plugin normal. El SDK administra el ciclo de vida del módulo de la siguiente manera:

- **Carga:** Cuando se llama a `Plugin_Module`, el SDK:
   1. Construye la ruta completa del archivo (ej: `modules/custom/core_logic.dll`).
   2. Usa `Dynamic_Library` (`LoadLibrary`/`dlopen`) para cargar el binario.
   3. **Obtiene los punteros a TODAS las funciones del ciclo de vida del módulo:**
      - **Obligatorias:** `Load`, `Unload`, `Supports`. Si alguna falta, la carga del módulo falla.
      - **Opcionales:** `AmxLoad`, `AmxUnload`, `ProcessTick`.
   4. Llama a la función `Load` del módulo, pasando `ppData` del plugin principal.
   5. Si `Load` devuelve `true`, el módulo se añade a la lista interna de módulos cargados.

- **Reenvío de Eventos:** El plugin anfitrión **reenvía automáticamente** los eventos a todos los módulos cargados.
 > [!IMPORTANT]
 > Para que los eventos se reenvíen correctamente, el **plugin anfitrión** (el que llama a `Plugin_Module`) debe estar configurado para recibir esos eventos.
 > - Para que `AmxLoad` y `AmxUnload` funcionen en los módulos, el plugin anfitrión debe definir la macro `SAMP_SDK_WANT_AMX_EVENTS`.
 > - Para que `ProcessTick` funcione en los módulos, el plugin anfitrión debe definir la macro `SAMP_SDK_WANT_PROCESS_TICK`.

- **Descarga:** Durante `OnUnload` de su plugin principal, el SDK descarga todos los módulos que fueron cargados a través de `Plugin_Module`. Esto se realiza en **orden inverso** a la carga (el último en cargarse es el primero en descargarse), lo cual es crucial para administrar dependencias y garantizar la liberación correcta de recursos.

#### Beneficios de la Modularización

- **Organización del Código:** Divida grandes plugins en componentes más pequeños y manejables, cada uno en su propio archivo de módulo.
- **Reusabilidad:** Cree módulos genéricos (ej: un módulo de base de datos, un módulo de sistema de registro avanzado) que puedan ser utilizados por diferentes plugins, promoviendo la reutilización de código.
- **Componentes Independientes:** Cree módulos que sean **totalmente orientados a eventos e independientes**. Un módulo puede tener sus propias `Plugin_Native`s, interceptar `Plugin_Public`s y tener su propia lógica `OnProcessTick`, operando como un plugin autónomo, pero cargado por un anfitrión.
- **Actualizaciones Dinámicas:** En escenarios controlados, permite la actualización de partes de su sistema (reemplazando un `.dll` o `.so` de módulo) sin la necesidad de recompilar y reiniciar el plugin principal o el servidor completo (aunque esto requiere una gestión de versiones y compatibilidad rigurosas).

### 3.8. `Plugin_Call`: Llamando Nativas Internas del Plugin

Utilice `Plugin_Call` para invocar una `Plugin_Native` definida **dentro de su propio plugin**.

#### Sintaxis y Ventajas de Performance

- `Plugin_Call(NombreDeLaNative, Param1, Param2, ...)`
- **Ventaja:** Evita la sobrecarga de buscar la nativa en el array de nativas de la AMX. El SDK mantiene un mapa directo de hashes de nombre a punteros de función para sus propias nativas, lo que hace de esta la forma más rápida de llamarlas internamente.
- **Requiere:** `SAMP_SDK_WANT_AMX_EVENTS`.

```cpp
// main.cpp
Plugin_Native(InternalCheckPlayerLevel, AMX* amx, cell* params) {
    int playerid;
    Register_Parameters(playerid);

    // Lógica para verificar el nivel
    return (playerid % 2 == 0) ? 1 : 0; // Ejemplo: nivel par para IDs pares
}

void Check_All_Players_Level() {
    for (int i = 0; i < MAX_PLAYERS; ++i) {
        if (Pawn_Native(IsPlayerConnected, i)) {
            if (Plugin_Call(InternalCheckPlayerLevel, i)) // Llama a su propia nativa
                Samp_SDK::Log("¡Jugador %d está en un nivel alto!", i);
        }
    }
}
```

### 3.9. Funciones Utilitarias del SDK

#### `Samp_SDK::Log(const char* format, ...)`

- **Descripción:** Imprime mensajes en la consola del servidor y en el archivo `server_log.txt`. Un envoltorio seguro para `logprintf`.
- **Uso:** Para depuración, mensajes de estado y errores.
- **Mecanismo:** Internamente, el SDK obtiene el puntero a `logprintf` a través de `ppData[PLUGIN_DATA_LOGPRINTF]`. La función maneja el formato de la string de forma segura.

```cpp
// En cualquier lugar de su plugin
Samp_SDK::Log("El plugin fue inicializado con un valor %d y una string '%s'.", 123, "prueba");
```

#### `std::string Plugin_Format(const char* format, ...)` (Recomendado)

- **Descripción:** Formatea una string de forma segura (similar a `sprintf`) y devuelve un `std::string`. Esta es la manera **recomendada y más idiomática** de formatear strings para usar dentro de su plugin.
- **Uso:** Ideal para construir mensajes formateados antes de pasarlos a `Samp_SDK::Log`, `Pawn_Native(SendClientMessage, ...)`, o para cualquier otra necesidad de string dentro de su código C++.
- **Mecanismo:** Internamente, `Plugin_Format` es una macro que llama a `Samp_SDK::Format`. Utiliza `vsnprintf` para determinar el tamaño exacto de la string formateada y asigna un `std::string` con capacidad suficiente, evitando desbordamientos de búfer.

```cpp
int playerid = 0; // Ejemplo de ID
int health = 50;
Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, Plugin_Format("Jugador %d, tu vida actual es %d.", playerid, health));

// También se puede usar para logs internos
Samp_SDK::Log(Plugin_Format("DEBUG: Procesando estado para el ID %d", playerid));
```

#### `std::string Samp_SDK::Format(const char* format, ...)` (Detalle de Implementación)

- **Descripción:** La función de implementación subyacente para el formato de strings, ubicada dentro del namespace `Samp_SDK`.
- **Uso:** Generalmente no es llamada directamente por el usuario. La macro `Plugin_Format` se proporciona como una conveniencia para esta función, alineándose con la convención de nombres de otras macros del SDK (`Plugin_Public`, `Plugin_Native`). Solo la llamaría directamente si quisiera evitar la macro `Plugin_Format` por alguna razón específica.

```cpp
// Ejemplo de cómo funciona Samp_SDK::Format, pero prefiera Plugin_Format
std::string raw_status = Samp_SDK::Format("Solo para uso interno: %d.", 42);
```

#### `std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`

- **Descripción:** Convierte una dirección de string de la AMX (`cell amx_addr`) en un `std::string` de C++.
- **Uso:** Principalmente dentro de `Plugin_Native` y `Plugin_Native_Hook` cuando necesita acceder a strings que no son convertidas automáticamente por `Register_Parameters` o `Native_Params` (ej: si el parámetro de Pawn es un `const` `string` y no fue declarado como `std::string` en su `Plugin_Native` o `Plugin_Public` para el Marshalling automático).

```cpp
Plugin_Native(PrintRawAmxString, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    cell amx_string_addr = p.Get<cell>(0); // Obtiene la dirección de la string en la AMX

    std::string cpp_string = Samp_SDK::Get_String(amx, amx_string_addr);
    Samp_SDK::Log("String de la AMX: %s", cpp_string.c_str());

    return 1;
}
```

## 4. Compilación y Despliegue

### Requisitos de Arquitectura y Plataforma

- Su plugin **DEBE** ser compilado para la arquitectura **x86 (32-bit)**.
- Plataformas Soportadas: Windows (.dll) y Linux (.so).

### Ejemplos de Comandos de Compilación

#### **MSVC (Visual Studio)**

1. Cree un nuevo proyecto de "Dynamic-Link Library (DLL)".
2. En las configuraciones del proyecto, defina la "Plataforma de Solución" a **x86**.
3. Asegúrese de que el estándar del lenguaje C++ sea al menos C++17.

#### **GCC / Clang (Linux)**

```bash
# Para un plugin llamado 'my_plugin.so' a partir de 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -fPIC -Wall -Wextra -Wl,--no-undefined main.cpp -o my_plugin.so
```
- `-m32`: Compila para 32-bit.
- `-shared`: Crea una biblioteca compartida (`.so`).
- `-std=c++17`: Define el estándar de C++ a C++17 (puede ser `c++20`, pero C++17 es el mínimo).
- `-O2`: Nivel de optimización 2.
- `-fPIC`: Genera código independiente de la posición, necesario para bibliotecas compartidas.
- `-Wall -Wextra`: Activa advertencias adicionales para ayudar a detectar errores.
- `-Wl,--no-undefined`: Impide la creación de la biblioteca si hay símbolos indefinidos.

#### **GCC / Clang (MinGW en Windows)**

```bash
# Para un plugin llamado 'my_plugin.dll' a partir de 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -static-libstdc++ -static-libgcc -Wl,--no-undefined main.cpp -o my_plugin.dll
```
- `-static-libstdc++`: Enlaza la biblioteca estándar C++ estáticamente. Es esencial para evitar que su plugin dependa de DLLs de tiempo de ejecución específicas del compilador que podrían no estar presentes en el sistema del usuario.
- `-static-libgcc`: Enlaza la biblioteca GCC estáticamente.

### Consideraciones para la Distribución

- **Nombre del Archivo:** Su plugin debe tener la extensión `.dll` (Windows) o `.so` (Linux). Ej: `my_plugin.dll`.
- **Ubicación:** Coloque el archivo compilado en la carpeta `plugins/` de su servidor SA-MP.
- **server.cfg:** Agregue el nombre de su plugin (si es Windows, sin la extensión) a la línea `plugins` en `server.cfg`.
   ```
   plugins my_plugin (si es Linux, my_plugin.so)
   ```

## Licencia

Copyright © **AlderGrounds**

Este software está licenciado bajo los términos de la Licencia MIT ("Licencia"); puede utilizar este software de acuerdo con las condiciones de la Licencia. Puede obtener una copia de la Licencia en: [MIT License](https://opensource.org/licenses/MIT)

### Términos y Condiciones de Uso

#### 1. Permisos Otorgados

La presente licencia otorga, gratuitamente, a cualquier persona que obtenga una copia de este software y archivos de documentación asociados, los siguientes derechos:
* Usar, copiar, modificar, fusionar, publicar, distribuir, sublicenciar y/o vender copias del software sin restricciones
* Permitir que las personas a las que se les proporciona el software hagan lo mismo, sujeto a las siguientes condiciones

#### 2. Condiciones Obligatorias

Todas las copias o partes sustanciales del software deben incluir:
* El aviso de derechos de autor anterior
* Este aviso de permiso
* El aviso de exención de responsabilidad a continuación

#### 3. Derechos de Autor

El software y toda la documentación asociada están protegidos por leyes de derechos de autor. La **AlderGrounds** mantiene la titularidad de los derechos de autor originales del software.

#### 4. Exención de Garantías y Limitación de Responsabilidad

EL SOFTWARE SE PROPORCIONA "TAL CUAL", SIN GARANTÍA DE NINGÚN TIPO, EXPRESA O IMPLÍCITA, INCLUYENDO PERO NO LIMITADO A LAS GARANTÍAS DE COMERCIABILIDAD, IDONEIDAD PARA UN PROPÓSITO PARTICULAR Y NO INFRACCIÓN.

EN NINGÚN CASO LOS AUTORES O TITULARES DE LOS DERECHOS DE AUTOR SERÁN RESPONSABLES DE CUALQUIER RECLAMACIÓN, DAÑOS U OTRA RESPONSABILIDAD, YA SEA EN UNA ACCIÓN DE CONTRATO, AGRAVIO O DE OTRO MODO, QUE SURJA DE, FUERA DE O EN CONEXIÓN CON EL SOFTWARE O EL USO U OTROS TRATOS EN EL SOFTWARE.

---

Para información detallada sobre la Licencia MIT, consulte: https://opensource.org/licenses/MIT