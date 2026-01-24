# SA-MP SDK

<div align="center">

![C++](https://img.shields.io/badge/C%2B%2B-17%2B-00599C?style=for-the-badge&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-blue?style=for-the-badge&logo=windows&logoColor=white)
![Architecture](https://img.shields.io/badge/Architecture-x86%20(32--bit)-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**Un SDK C++ moderno, header-only e di alto livello per lo sviluppo di plugin e moduli per SA-MP.**

</div>

## Lingue

- Português: [README](../../)
- Deutsch: [README](../Deutsch/README.md)
- English: [README](../English/README.md)
- Español: [README](../Espanol/README.md)
- Français: [README](../Francais/README.md)
- Polski: [README](../Polski/README.md)
- Русский: [README](../Русский/README.md)
- Svenska: [README](../Svenska/README.md)
- Türkçe: [README](../Turkce/README.md)

## Indice

- [SA-MP SDK](#sa-mp-sdk)
  - [Lingue](#lingue)
  - [Indice](#indice)
  - [1. Introduzione e Filosofia di Design](#1-introduzione-e-filosofia-di-design)
    - [Il Problema con l'API C Standard di SA-MP](#il-problema-con-lapi-c-standard-di-sa-mp)
    - [La Soluzione del SA-MP SDK: Astrazione con Sicurezza e Performance](#la-soluzione-del-sa-mp-sdk-astrazione-con-sicurezza-e-performance)
    - [Modello Header-Only: Vantaggi e Implicazioni](#modello-header-only-vantaggi-e-implicazioni)
  - [2. Configurazione e Ambiente](#2-configurazione-e-ambiente)
    - [Requisiti di Compilazione](#requisiti-di-compilazione)
    - [Struttura di File Raccomandata](#struttura-di-file-raccomandata)
    - [Macro Essenziali di Configurazione](#macro-essenziali-di-configurazione)
      - [`SAMP_SDK_IMPLEMENTATION`](#samp_sdk_implementation)
      - [`SAMP_SDK_WANT_AMX_EVENTS`](#samp_sdk_want_amx_events)
      - [`SAMP_SDK_WANT_PROCESS_TICK`](#samp_sdk_want_process_tick)
    - [Definizioni e Costanti di SA-MP (`samp_defs.hpp`)](#definizioni-e-costanti-di-sa-mp-samp_defshpp)
  - [3. Guida all'Uso Completa dell'API](#3-guida-alluso-completa-dellapi)
    - [3.1. Il Ciclo di Vita del Plugin](#31-il-ciclo-di-vita-del-plugin)
      - [`bool OnLoad()`](#bool-onload)
      - [`void OnUnload()`](#void-onunload)
      - [`unsigned int GetSupportFlags()`](#unsigned-int-getsupportflags)
      - [`void OnAmxLoad(AMX* amx)`](#void-onamxloadamx-amx)
      - [`void OnAmxUnload(AMX* amx)`](#void-onamxunloadamx-amx)
      - [`void OnProcessTick()`](#void-onprocesstick)
    - [3.2. Esportazione delle Funzioni del Plugin](#32-esportazione-delle-funzioni-del-plugin)
      - [Esportazione per MSVC (Visual Studio) con `Export_Plugin`](#esportazione-per-msvc-visual-studio-con-export_plugin)
      - [Esportazione per GCC / Clang con `SAMP_SDK_EXPORT`](#esportazione-per-gcc--clang-con-samp_sdk_export)
    - [3.3. `Plugin_Public`: Intercettazione degli Eventi Pawn](#33-plugin_public-intercettazione-degli-eventi-pawn)
      - [Sintassi e Dichiarazione](#sintassi-e-dichiarazione)
      - [Marshalling Automatico dei Parametri](#marshalling-automatico-dei-parametri)
      - [Controllo di Flusso: `PUBLIC_CONTINUE` vs `PUBLIC_STOP`](#controllo-di-flusso-public_continue-vs-public_stop)
      - [Ghost Callbacks](#ghost-callbacks)
    - [3.4. `Plugin_Native`: Creazione di Funzioni Native in C++](#34-plugin_native-creazione-di-funzioni-native-in-c)
      - [Sintassi e Firma Fissa](#sintassi-e-firma-fissa)
      - [Registrazione Automatica delle Native](#registrazione-automatica-delle-native)
      - [Estrazione dei Parametri: `Register_Parameters` vs. `Native_Params`](#estrazione-dei-parametri-register_parameters-vs-native_params)
        - [`Register_Parameters(...)`](#register_parameters)
        - [`Native_Params` (API Completa: `Get`, `Get_REF`, `Set_REF`)](#native_params-api-completa-get-get_ref-set_ref)
          - [`p.Count()`](#pcount)
          - [`p.Get<T>(size_t index)`](#pgettsize_t-index)
          - [`p.Get_REF<T>(size_t index, T& out_value)`](#pget_reftsize_t-index-t-out_value)
          - [`p.Get_REF<T>(size_t index)` (C++17+)](#pget_reftsize_t-index-c17)
          - [`p.Set_REF<T>(size_t index, T value)`](#pset_reftsize_t-index-t-value)
      - [Restituzione di Valori](#restituzione-di-valori)
    - [3.5. `Plugin_Native_Hook`: Intercettazione delle Native SA-MP Esistenti](#35-plugin_native_hook-intercettazione-delle-native-sa-mp-esistenti)
      - [Sintassi e Firma Fissa](#sintassi-e-firma-fissa-1)
      - [Registrazione e Attivazione dell'Hook](#registrazione-e-attivazione-dellhook)
      - [Chiamata della Native Originale (Catena di Hooks): `Call_Original_Native`](#chiamata-della-native-originale-catena-di-hooks-call_original_native)
      - [Esempio Completo di `Plugin_Native_Hook`](#esempio-completo-di-plugin_native_hook)
    - [3.6. `Pawn_*` Macro: Chiamata di Funzioni Pawn da C++](#36-pawn_-macro-chiamata-di-funzioni-pawn-da-c)
      - [`Pawn_Native(NomeDellaNative, ...)`](#pawn_nativenomedellanative-)
      - [`Pawn_Public(NomeDellaPublic, ...)`](#pawn_publicnomedellapublic-)
      - [`Pawn(NomeDellaFunzione, ...)`](#pawnnomedellafunzione-)
      - [Sintassi e Convenzioni](#sintassi-e-convenzioni)
      - [Marshalling dei Parametri di Input](#marshalling-dei-parametri-di-input)
      - [Marshalling dei Parametri di Output (Riferimenti: `int&`, `float&`, `std::string&`)](#marshalling-dei-parametri-di-output-riferimenti-int-float-stdstring)
      - [L'Oggetto `Callback_Result`: Analisi Completa](#loggetto-callback_result-analisi-completa)
    - [3.7. `Plugin_Module`: Gestione dei Moduli Dinamici](#37-plugin_module-gestione-dei-moduli-dinamici)
      - [Sintassi e Scopo](#sintassi-e-scopo)
      - [Ciclo di Vita di un Modulo](#ciclo-di-vita-di-un-modulo)
      - [Benefici della Modularizzazione](#benefici-della-modularizzazione)
    - [3.8. `Plugin_Call`: Chiamata delle Native Interne del Plugin](#38-plugin_call-chiamata-delle-native-interne-del-plugin)
      - [Sintassi e Vantaggi di Performance](#sintassi-e-vantaggi-di-performance)
    - [3.9. Funzioni Utilità dell'SDK](#39-funzioni-utilità-dellsdk)
      - [`Samp_SDK::Log(const char* format, ...)`](#samp_sdklogconst-char-format-)
      - [`std::string Plugin_Format(const char* format, ...)` (Raccomandato)](#stdstring-plugin_formatconst-char-format--raccomandato)
      - [`std::string Samp_SDK::Format(const char* format, ...)` (Dettaglio di Implementazione)](#stdstring-samp_sdkformatconst-char-format--dettaglio-di-implementazione)
      - [`std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`](#stdstring-samp_sdkget_stringamx-amx-cell-amx_addr)
  - [4. Compilazione e Deploy](#4-compilazione-e-deploy)
    - [Requisiti di Architettura e Piattaforma](#requisiti-di-architettura-e-piattaforma)
    - [Esempi di Comandi di Compilazione](#esempi-di-comandi-di-compilazione)
      - [**MSVC (Visual Studio)**](#msvc-visual-studio)
      - [**GCC / Clang (Linux)**](#gcc--clang-linux)
      - [**GCC / Clang (MinGW su Windows)**](#gcc--clang-mingw-su-windows)
    - [Considerazioni per la Distribuzione](#considerazioni-per-la-distribuzione)
  - [Licenza](#licenza)
    - [Termini e Condizioni d'Uso](#termini-e-condizioni-duso)
      - [1. Permessi Concessi](#1-permessi-concessi)
      - [2. Condizioni Obbligatorie](#2-condizioni-obbligatorie)
      - [3. Diritti d'Autore](#3-diritti-dautore)
      - [4. Esclusione di Garanzia e Limitazione di Responsabilità](#4-esclusione-di-garanzia-e-limitazione-di-responsabilità)

## 1. Introduzione e Filosofia di Design

### Il Problema con l'API C Standard di SA-MP

L'API dei plugin di SA-MP è un'interfaccia di programmazione in C. Sebbene funzionale e fondamentale, presenta le sfide inerenti alla programmazione di basso livello:
- **Gestione Manuale della Memoria:** Funzioni come `amx_Allot` e `amx_Release` richiedono che lo sviluppatore allochi e deallochi esplicitamente la memoria nell'heap dell'AMX. Questa è una fonte comune di perdite di memoria e errori di runtime.
- **Tipizzazione Debole e Conversioni Manuali:** I parametri vengono passati come un array di `cell`, forzando conversioni esplicite (e spesso insicure) tra `cell`, `int`, `float` e `char*`.
- **Verbosità e Boilerplate:** Estrarre più parametri da un array `cell* params`, gestire le dimensioni delle stringhe e gestire lo stack dell'AMX per le chiamate di ritorno da C++ a Pawn richiede codice ripetitivo.
- **Fragilità dell'Interfaccia:** La mancanza di verifica in fase di compilazione (type safety) significa che gli errori nel passaggio dei parametri o nei tipi possono passare inosservati fino all'esecuzione, causando crash o comportamenti indefiniti.

### La Soluzione del SA-MP SDK: Astrazione con Sicurezza e Performance

L'SA-MP SDK affronta questi problemi fornendo un potente strato di astrazione in C++:
- **RAII (Resource Acquisition Is Initialization):** Gestione automatica della memoria nell'AMX. `Amx_Scoped_Memory` garantisce che la memoria allocata venga liberata.
- **Sicurezza dei Tipi:** Conversione automatica e sicura dei parametri tra C++ e Pawn. Si gestiscono direttamente `int`, `float`, `std::string`.
- **Sintassi Concisa e Idiomatica:** Macro e template forniscono un'API pulita che assomiglia più al C++ moderno che all'API C tradizionale.
- **Intercettazione Robusta:** Un motore di hooking avanzato consente l'intercettazione trasparente dei callbacks di Pawn (`Plugin_Public`), la creazione di nuove native (`Plugin_Native`) e **l'hooking e l'incatenamento di funzioni native SA-MP esistenti (`Plugin_Native_Hook`)**.
- **Alte Performance:** Uso estensivo di hashing in fase di compilazione (FNV1a), caching delle funzioni e ottimizzazioni di `thread_local` per minimizzare l'overhead delle astrazioni.

### Modello Header-Only: Vantaggi e Implicazioni

L'SDK è composto esclusivamente da file di intestazione (`.hpp`, `.h`).
- **Vantaggi:**
   - **Integrazione Semplificata:** Non ci sono librerie da costruire, collegare o distribuire. Basta includere gli header.
   - **Ottimizzazioni del Compilatore:** Il compilatore ha piena visibilità del codice SDK e del tuo plugin, consentendo un inlining aggressivo e ottimizzazioni in fase di linking, che possono portare a binari più veloci.
- **Implicazioni:**
   - **Tempo di Compilazione:** Per progetti molto grandi, la compilazione potrebbe richiedere più tempo a causa dell'inclusione ripetuta del codice SDK. Questo è mitigato dalle guardie di inclusione e dalla natura "includi solo ciò che è necessario" del C++.
   - **Macro di Implementazione:** La necessità della macro `SAMP_SDK_IMPLEMENTATION` è una conseguenza del modello header-only per evitare ridefinizioni di simboli.

## 2. Configurazione e Ambiente

### Requisiti di Compilazione

- **Compilatore C++:** Compatibile con C++17 o superiore.
   - GCC (versione 8+)
   - Clang (versione 5+)
   - MSVC (Visual Studio 2017+)
- **Architettura:** **x86 (32-bit)**. SA-MP opera esclusivamente su questa architettura. L’SDK include controlli in `platform.hpp` che genereranno errori di compilazione se viene rilevata un’architettura non corretta.
- **Sistema Operativo:** Windows o Linux.

### Struttura di File Raccomandata

Per chiarezza e organizzazione, è comune organizzare l'SDK in una sottocartella `samp-sdk`.

```
my_plugin/
├── samp-sdk/
│   ├── // Altri file dell'SDK
│   └── samp_sdk.hpp // L'header principale da includere
│
├── src/
│   ├── main.cpp // Dove SAMP_SDK_IMPLEMENTATION è definito
│   └── my_custom_logic.cpp // Opzionale, per organizzare il codice
│
└── CMakeLists.txt (o .vcxproj, Makefile)
```

### Macro Essenziali di Configurazione

Definire sempre queste macro *prima* di includere `samp_sdk.hpp`.

#### `SAMP_SDK_IMPLEMENTATION`

- **Scopo:** Segnala al compilatore che questo file `.cpp` deve generare le implementazioni delle funzioni di esportazione del plugin (`Supports`, `Load`, `Unload`, `AmxLoad`, `AmxUnload`, `ProcessTick`). **L'SDK si occupa automaticamente dell'esportazione di queste funzioni, eliminando la necessità di file `.def` (su Windows) o dichiarazioni `__attribute__((visibility("default")))` (su Linux) per queste funzioni.**
- **Impatto Tecnico:** Senza questa macro, il linker non troverà le esportazioni necessarie e il server SA-MP non sarà in grado di caricare il tuo plugin.
- **Regola Fondamentale:** **Definire questa macro in SOLO UN file `.cpp` in tutto il tuo progetto.** Definirla in più di un file causerà un errore di linking di "simbolo duplicato".

```cpp
// main.cpp
#define SAMP_SDK_IMPLEMENTATION // La macro fa sì che l'SDK esporti automaticamente le funzioni necessarie.
#include "samp-sdk/samp_sdk.hpp"

// ... il tuo codice plugin ...
```

#### `SAMP_SDK_WANT_AMX_EVENTS`

- **Scopo:** Abilita i callbacks del ciclo di vita dello script Pawn (`OnAmxLoad`, `OnAmxUnload`) e la funzionalità di creare nuove native in C++ (`Plugin_Native`).
- **Funzionalità Attivate:**
   - Callbacks `OnAmxLoad(AMX* amx)` e `OnAmxUnload(AMX* amx)`.
   - Dichiarazione e registrazione di nuove native C++ usando `Plugin_Native`.
   - La macro `Plugin_Call` per invocare native create con `Plugin_Native` all'interno del proprio plugin.
- **Impatto Tecnico:** Quando questa macro è definita, l'SDK raccoglie automaticamente tutte le tue `Plugin_Native`s. Nella funzione `Supports()`, il flag `SUPPORTS_AMX_NATIVES` viene automaticamente aggiunto se ci sono `Plugin_Native`s nel tuo progetto.
- **Flessibilità:** **Puoi definire questa macro in più file `.cpp`**. Il sistema di registrazione statico dell'SDK consoliderà tutte le native da diverse unità di compilazione in un'unica lista globale.

```cpp
// my_natives.cpp (può essere un file separato da main.cpp)
#define SAMP_SDK_WANT_AMX_EVENTS // Solo per abilitare Plugin_Native e i callbacks OnAmxLoad/OnAmxUnload
#include "samp-sdk/samp_sdk.hpp"

Plugin_Native(MyCustomNative, AMX* amx, cell* params) {
    // ...
    return 0;
}
```

#### `SAMP_SDK_WANT_PROCESS_TICK`

- **Scopo:** Abilita il callback `OnProcessTick()`, che viene invocato regolarmente dal server.
- **Impatto Tecnico:** Aggiunge automaticamente il flag `SUPPORTS_PROCESS_TICK` alla funzione `Supports()`.

```cpp
// main.cpp
#define SAMP_SDK_IMPLEMENTATION
#define SAMP_SDK_WANT_PROCESS_TICK
#include "samp-sdk/samp_sdk.hpp"

void OnProcessTick() {
    // Logica eseguita ad ogni "tick" del server (es: 20ms)
    // Attenzione con operazioni pesanti qui!
}
```

### Definizioni e Costanti di SA-MP (`samp_defs.hpp`)

Questo file fornisce tutte le costanti e i limiti noti di SA-MP, come `MAX_PLAYERS`, `INVALID_PLAYER_ID`, `PLAYER_STATE_ONFOOT`, `WEAPON_DEAGLE`, `DIALOG_STYLE_LIST`, ecc. È automaticamente incluso da `samp_sdk.hpp` e deve essere utilizzato per garantire compatibilità e leggibilità del codice.

## 3. Guida all'Uso Completa dell'API

### 3.1. Il Ciclo di Vita del Plugin

Le seguenti funzioni sono i punti di ingresso e uscita del tuo plugin, esportate automaticamente dall'SDK.

#### `bool OnLoad()`

- **Descrizione:** Prima funzione chiamata dal server SA-MP dopo il caricamento riuscito del tuo plugin in memoria.
- **Uso:** Ideale per inizializzare qualsiasi sistema, caricare configurazioni, aprire connessioni a database o caricare moduli (`Plugin_Module`).
- **Ritorno:**
   - `true`: Il plugin è stato inizializzato con successo e il caricamento continua.
   - `false`: Il plugin non è riuscito a inizializzare. Il caricamento verrà interrotto e il plugin verrà scaricato.

```cpp
// main.cpp
bool OnLoad() {
    Samp_SDK::Log("Inizializzando MyPlugin v1.0...");

    // Esempio: Caricare un modulo (maggiori dettagli nella sezione 3.6)
    if (!Plugin_Module("my_database_module", "plugins/db_connector", "Modulo Database caricato.")) {
        Samp_SDK::Log("ERRORE: Impossibile caricare il modulo database!");

        return false; // Aborta il caricamento del plugin principale
    }

    return true;
}
```

#### `void OnUnload()`

- **Descrizione:** Ultima funzione chiamata dal server SA-MP prima di scaricare il tuo plugin dalla memoria.
- **Uso:** Ideale per pulire risorse, chiudere connessioni, salvare stati e garantire che nessuna risorsa venga persa. L'SDK gestisce automaticamente lo scaricamento dei moduli (`Plugin_Module`).

```cpp
// main.cpp
void OnUnload() {
    Samp_SDK::Log("MyPlugin scaricato. Rilascio risorse...");
    // Nessuna azione manuale è necessaria per i moduli caricati tramite Plugin_Module;
    // l'SDK se ne occupa.
}
```

#### `unsigned int GetSupportFlags()`

- **Descrizione:** Informa il server SA-MP quali funzionalità il tuo plugin supporta e desidera utilizzare.
- **Uso:** **Restituire sempre `SUPPORTS_VERSION` (o `SAMP_PLUGIN_VERSION`).** I flag `SUPPORTS_AMX_NATIVES` e `SUPPORTS_PROCESS_TICK` vengono aggiunti automaticamente dall'SDK se sono presenti `Plugin_Native`s e/o se la macro `SAMP_SDK_WANT_PROCESS_TICK` è definita, rispettivamente. Questo semplifica la manutenzione ed evita errori.

```cpp
// main.cpp
unsigned int GetSupportFlags() {
    return SUPPORTS_VERSION; // L'SDK aggiunge automaticamente i flag necessari.
}
```

#### `void OnAmxLoad(AMX* amx)`

- **Richiede:** `SAMP_SDK_WANT_AMX_EVENTS`
- **Descrizione:** Chiamato ogni volta che un nuovo script Pawn (un Gamemode o Filterscript) viene caricato e inizializzato sul server.
- **Uso:** Se hai bisogno di logica specifica per ogni script AMX, o inizializzare dati specifici per script.

```cpp
// main.cpp (con SAMP_SDK_WANT_AMX_EVENTS definito)
void OnAmxLoad(AMX* amx) {
    // amx rappresenta la nuova istanza dello script caricato.
    Samp_SDK::Log("Script AMX caricato: %p", (void*)amx);
}
```

#### `void OnAmxUnload(AMX* amx)`

- **Richiede:** `SAMP_SDK_WANT_AMX_EVENTS`
- **Descrizione:** Chiamato quando uno script Pawn viene scaricato dal server.
- **Uso:** Per pulire qualsiasi risorsa specifica che hai allocato o associato a quella particolare `AMX*`.

```cpp
// main.cpp (con SAMP_SDK_WANT_AMX_EVENTS definito)
void OnAmxUnload(AMX* amx) {
    Samp_SDK::Log("Script AMX scaricato: %p", (void*)amx);
}
```

#### `void OnProcessTick()`

- **Richiede:** `SAMP_SDK_WANT_PROCESS_TICK`
- **Descrizione:** Chiamato ripetutamente ad ogni "tick" del server (solitamente 20 volte al secondo, o ogni 50ms).
- **Uso:** Per logiche di background continue, timer, aggiornamenti di stato che non dipendono dagli eventi del giocatore, o sincronizzazione dei dati.
- **Attenzione:** Evitare operazioni bloccanti o computazionalmente pesanti qui, poiché possono causare lag nel server.

```cpp
// main.cpp (con SAMP_SDK_WANT_PROCESS_TICK definito)
static int tick_count = 0;

void OnProcessTick() {
    tick_count++;

    if (tick_count % 200 == 0) // Ogni 10 secondi (20 tick/sec * 10 sec = 200 tick)
        Samp_SDK::Log("Server attivo da %d secondi.", tick_count / 20);
}
```

### 3.2. Esportazione delle Funzioni del Plugin

Affinché il server SA-MP possa chiamare le funzioni del tuo plugin (`Load`, `Supports`, ecc.), esse devono essere "esportate" dal file DLL (Windows) o SO (Linux). L'SDK automatizza l'esportazione delle funzioni di ciclo di vita standard, ma fornisce anche strumenti affinché tu possa esportare le tue funzioni personalizzate, qualora necessitassi di interoperabilità con altri programmi.

Il metodo per esportare funzioni varia in base al compilatore.

#### Esportazione per MSVC (Visual Studio) con `Export_Plugin`

Su Windows con MSVC, il modo più semplice per esportare funzioni personalizzate è utilizzare la macro `Export_Plugin`, definita in `exports.hpp`.

- **Sintassi:** `Export_Plugin("Funzione", "Pila")`
- **`Funzione`**: Il nome esatto della funzione da esportare.
- **`Pila`**: La quantità totale di byte che i parametri della funzione occupano nello stack. Per la convenzione `__stdcall` (standard dell'SDK su Windows), il calcolo è `4 * (Numero di Parametri)`.

```cpp
#include "samp-sdk/exports.hpp"

// Esempio: Esportazione di una funzione personalizzata che potrebbe essere chiamata
// da un altro programma o plugin che conosce la sua firma.
const char* SAMP_SDK_CALL GetPluginVersion() {
    return "1.0.0";
}

Export_Plugin("GetPluginVersion", "0");
```

> [!WARNING]
> **Limitazione di `Export_Plugin`**
> Questa macro funziona **solo con il compilatore MSVC (Visual Studio)**. Utilizza una direttiva `#pragma` specifica di Microsoft che viene ignorata da altri compilatori come GCC e Clang.

#### Esportazione per GCC / Clang con `SAMP_SDK_EXPORT`

Per GCC e Clang (su Windows o Linux), l'esportazione è gestita dalla macro `SAMP_SDK_EXPORT`, definita in `platform.hpp`. È sufficiente posizionarla prima della definizione della funzione.

- **Meccanismo:** Su Linux, aggiunge `__attribute__((visibility("default")))`. Su Windows con GCC/Clang, aggiunge `__attribute__((dllexport))`.
- **Uso:** L'SDK applica già `SAMP_SDK_EXPORT` a tutte le funzioni di ciclo di vita (`Load`, `Unload`, ecc.), quindi la loro esportazione è completamente automatica per questi compilatori. Per le tue funzioni personalizzate, fai semplicemente lo stesso.

```cpp
// Per GCC/Clang, la definizione della funzione con SAMP_SDK_EXPORT è sufficiente.
SAMP_SDK_EXPORT const char* SAMP_SDK_CALL GetPluginVersion() {
    return "1.0.0";
}
```

### 3.3. `Plugin_Public`: Intercettazione degli Eventi Pawn

La macro `Plugin_Public` è il ponte primario per ricevere callbacks da Pawn nel tuo codice C++.

#### Sintassi e Dichiarazione

- `Plugin_Public(NomeDellaPublic, Tipo1 Param1, Tipo2 Param2, ...)`
- Il nome della funzione C++ che dichiari **deve essere lo stesso** del callback Pawn (es: `OnPlayerConnect`).
- I tipi di parametri C++ (`int`, `float`, `std::string`) vengono automaticamente convertiti dall'SDK.

```cpp
// Intercetta OnPlayerText(playerid, text[])
Plugin_Public(OnPlayerText, int playerid, std::string text) {
    Samp_SDK::Log("Giocatore %d ha detto: %s", playerid, text.c_str());

    return PUBLIC_CONTINUE;
}
```

#### Marshalling Automatico dei Parametri

L'SDK gestisce automaticamente la lettura dello `cell stack` dell'AMX e la conversione ai tipi C++ specificati:
- `int`: Convertito direttamente da `cell`.
- `float`: Convertito da `cell` usando `amx::AMX_CTOF`.
- `std::string`: L'SDK legge l'indirizzo della stringa nell'AMX, alloca una `std::string` in C++ e copia il contenuto.

#### Controllo di Flusso: `PUBLIC_CONTINUE` vs `PUBLIC_STOP`

Il valore restituito dalla tua funzione `Plugin_Public` è cruciale e determina il flusso di esecuzione del callback:
- `return PUBLIC_CONTINUE;` (valore `1`): Indica che l'esecuzione del callback deve **continuare**. Se ci sono altri plugin che intercettano questo callback, verranno chiamati (in ordine inverso di caricamento). Successivamente, la `public` originale nello script Pawn verrà invocata.
- `return PUBLIC_STOP;` (valore `0`): Indica che l'esecuzione del callback deve essere **interrotta**. Nessun altro plugin (con priorità inferiore) o la `public` originale nello script Pawn verrà invocato per questo evento. Questo è ideale per implementare un sistema che "sovrascrive" o "blocca" un comportamento standard di SA-MP.

```cpp
// main.cpp
Plugin_Public(OnPlayerCommandText, int playerid, std::string cmdtext) {
    if (cmdtext == "/freeze") {
        Pawn_Native(TogglePlayerControllable, playerid, 0); // Congela il giocatore
        Pawn_Native(SendClientMessage, playerid, -1, Plugin_Format("Giocatore %d congelato.", playerid));

        return PUBLIC_STOP; // Impedisce che il comando venga elaborato da altri script.
    }

    return PUBLIC_CONTINUE; // Permette che altri comandi vengano elaborati.
}
```

#### Ghost Callbacks

Una caratteristica avanzata di `Plugin_Public` è il supporto ai "Ghost Callbacks". Ciò significa che puoi intercettare un callback Pawn anche se **non è presente** nello script `.amx` del gamemode o del filterscript. L'SDK "inganna" il server in modo che chiami il tuo hook C++ comunque. Questo è utile per callbacks interni o per creare nuove funzionalità senza dipendere dalla presenza di una `public` nello script Pawn.

```cpp
// Puoi definire un callback che lo script Pawn non possiede, ma il tuo plugin lo ascolterà.
Plugin_Public(OnMyCustomInternalEvent, int data1, float data2) {
    Samp_SDK::Log("Evento interno personalizzato ricevuto: %d, %.2f", data1, data2);

    return PUBLIC_CONTINUE;
}

// Per "attivare" questo evento da un altro punto del tuo codice C++:
// Pawn_Public(OnMyCustomInternalEvent, 123, 45.67f);
// La chiamata andrà al tuo Plugin_Public qui sopra, anche se non c'è OnMyCustomInternalEvent in Pawn.
```

### 3.4. `Plugin_Native`: Creazione di Funzioni Native in C++

`Plugin_Native` ti permette di estendere la funzionalità di Pawn con codice C++ ad alte prestazioni.

#### Sintassi e Firma Fissa

- `Plugin_Native(NomeDellaNative, AMX* amx, cell* params)`
- La funzione C++ deve avere esattamente questa firma: `cell NomeDellaNative(AMX* amx, cell* params)`.
- `NomeDellaNative` è il nome che gli script Pawn useranno.

```cpp
// Pawn: native GetPlayerPingAverage(playerid);
Plugin_Native(GetPlayerPingAverage, AMX* amx, cell* params) {
    // ... Implementazione ...
    return 0;
}
```

#### Registrazione Automatica delle Native

> [!NOTE]
> **Non è necessario** chiamare `amx_Register` manualmente. L'SDK rileva tutte le tue `Plugin_Native`s (in qualsiasi file `.cpp` che abbia incluso `samp_sdk.hpp` e definito `SAMP_SDK_WANT_AMX_EVENTS`) e le registra automaticamente in ogni script AMX caricato (`OnAmxLoad`).

#### Estrazione dei Parametri: `Register_Parameters` vs. `Native_Params`

##### `Register_Parameters(...)`

- **Descrizione:** Helper più semplice per estrarre più parametri in sequenza.
- **Uso:** `Register_Parameters(variabile1, variabile2, ...)`
- **Limitazioni:** Per parametri di input. Non gestisce parametri opzionali o accesso per indice.
- **Tipi Supportati:** `int`, `float`, `std::string`.

```cpp
// Pawn: native SetPlayerSkinAndMoney(playerid, skinid, money);
Plugin_Native(SetPlayerSkinAndMoney, AMX* amx, cell* params) {
    int playerid, skinid, money;
    Register_Parameters(playerid, skinid, money); // Estrae i 3 parametri
    
    Pawn_Native(SetPlayerSkin, playerid, skinid);
    Pawn_Native(GivePlayerMoney, playerid, money);
    
    return 1;
}
```

##### `Native_Params` (API Completa: `Get`, `Get_REF`, `Set_REF`)

- **Descrizione:** Una classe wrapper che fornisce un'interfaccia orientata agli oggetti per accedere ai parametri di una native. Più potente per scenari complessi.
- **Costruzione:** `Native_Params p(amx, params);`

###### `p.Count()`

- **Descrizione:** Restituisce il numero di parametri passati alla native.
- **Uso:** Essenziale per gestire parametri opzionali.

###### `p.Get<T>(size_t index)`

- **Descrizione:** Estrae un parametro di input per indice e lo converte al tipo `T`.
- **Tipi Supportati:** `int`, `float`, `std::string`.

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

- **Descrizione:** Ottiene il valore di un parametro di **riferimento** (puntatore Pawn) e lo memorizza in `out_value`.
- **Uso:** Per leggere valori che sono stati passati per riferimento da Pawn.
- **Ritorno:** `true` se l'indirizzo AMX è valido, `false` altrimenti.

```cpp
// Pawn: native CheckPlayerStats(playerid, &Float:health, &money);
Plugin_Native(CheckPlayerStats, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    
    int playerid = p.Get<int>(0);
    float health = 0.0f;
    int money = 0;

    // Ottiene i valori dei riferimenti (Pawn ha passato indirizzi)
    p.Get_REF(1, health); // Legge il valore di Float:health
    p.Get_REF(2, money);   // Legge il valore di money
    
    Samp_SDK::Log("Giocatore %d, Vita: %.1f, Denaro: %d", playerid, health, money);
    
    // Ora, modificali
    health = 50.0f;
    money += 100;
    
    // E li riscrive nella memoria di Pawn
    p.Set_REF(1, health);
    p.Set_REF(2, money);
    
    return 1;
}
```

###### `p.Get_REF<T>(size_t index)` (C++17+)

- **Descrizione:** Restituisce un `std::optional<T>` per leggere un parametro di riferimento. Più sicuro per C++17 e superiori.

###### `p.Set_REF<T>(size_t index, T value)`

- **Descrizione:** Scrive un valore `T` in un parametro di **riferimento** Pawn (l'indirizzo che Pawn ha passato).
- **Uso:** Per modificare valori che sono stati passati per riferimento, facendo in modo che Pawn veda la modifica.
- **Ritorno:** `true` se la scrittura è avvenuta con successo, `false` altrimenti.

#### Restituzione di Valori

- La tua funzione `Plugin_Native` deve restituire una `cell`.
- Per restituire un `int` o `bool`, usa un cast a `cell`.
- Per restituire un `float`, usa `amx::AMX_FTOC(mio_float)`.

```cpp
// Restituisce un bool
Plugin_Native(IsPlayerSpawned, AMX* amx, cell* params) {
    int playerid;
    Register_Parameters(playerid);

    return (Pawn_Native(GetPlayerState, playerid) == PLAYER_STATE_SPAWNED) ? 1 : 0;
}

// Restituisce un float
Plugin_Native(GetPlayerMaxHealth, AMX* amx, cell* params) {
    return amx::AMX_FTOC(100.0f); // Restituisce 100.0f
}
```

### 3.5. `Plugin_Native_Hook`: Intercettazione delle Native SA-MP Esistenti

La macro `Plugin_Native_Hook` ti permette di intercettare e modificare il comportamento di qualsiasi funzione nativa SA-MP esistente o di altri plugin. Questo è un meccanismo potente per estendere o alterare la logica standard del server.

#### Sintassi e Firma Fissa

- `Plugin_Native_Hook(NomeDellaNative, AMX* amx, cell* params)`
- La funzione C++ deve avere esattamente questa firma: `cell NomeDellaNative(AMX* amx, cell* params)`.
- `NomeDellaNative` deve essere il nome esatto della native che vuoi hookare (es: `SendClientMessage`, `SetPlayerPos`).

```cpp
// Intercetta la native SendClientMessage
Plugin_Native_Hook(SendClientMessage, AMX* amx, cell* params) {
    // ...
    return Call_Original_Native(SendClientMessage); // Importante chiamare l'originale
}
```

#### Registrazione e Attivazione dell'Hook

> [!NOTE]
> **Non è necessario** chiamare `amx_Register` manualmente o definire `SAMP_SDK_WANT_AMX_EVENTS` specificamente per `Plugin_Native_Hook`. L'SDK rileva e registra automaticamente i tuoi hook. Alla prima esecuzione di uno script AMX, l'SDK sostituisce il puntatore della native nella tabella con un "trampoline" che reindirizza alla tua funzione `Plugin_Native_Hook`. Questo processo garantisce l'incatenamento sicuro degli hook di più plugin.

#### Chiamata della Native Originale (Catena di Hooks): `Call_Original_Native`

All'interno della tua funzione `Plugin_Native_Hook`, **DEVI** usare la macro `Call_Original_Native(NomeDellaNative)` per invocare la funzione originale (o il prossimo hook nella catena). Questo è vitale per:
- **Preservare la Funzionalità:** Se non chiami l'originale, la native hookata smetterà semplicemente di funzionare per altri plugin o per il server.
- **Incatenamento di Hooks:** Permette a più plugin di hookare la stessa native e che tutti gli hook vengano eseguiti in sequenza.
- **Manipolazione del Ritorno:** Puoi ispezionare e persino modificare il valore di ritorno di `Call_Original_Native` prima di restituirlo dalla tua funzione di hook.

```cpp
// Esempio: Blocco di SendClientMessage se contiene una parola specifica
Plugin_Native_Hook(SendClientMessage, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    
    // Estrae i parametri per l'analisi
    int playerid = p.Get<int>(0);
    // int color = p.Get<int>(1); // Non abbiamo bisogno del colore per questa logica
    std::string message = p.Get_String(2); // Ottiene la stringa del messaggio

    if (message.find("BADWORD") != std::string::npos) {
        Samp_SDK::Log("MESSAGGIO BLOCCATO per playerid %d: %s", playerid, message.c_str());

        return 0; // Restituisce 0 (false) a Pawn, indicando che il messaggio non è stato inviato.
                  // E, cosa più importante, NON chiamiamo Call_Original_Native, bloccando il messaggio.
    }

    // Se il messaggio non contiene la parola proibita, chiamiamo la native originale
    // e ne restituiamo il valore, garantendo che il messaggio venga inviato normalmente
    // e che altri hook (se esistono) vengano eseguiti.
    return Call_Original_Native(SendClientMessage);
}
```

#### Esempio Completo di `Plugin_Native_Hook`

```cpp
#define SAMP_SDK_IMPLEMENTATION
// SAMP_SDK_WANT_AMX_EVENTS non è strettamente necessario per gli hook, ma è comune avere OnAmxLoad/Unload
// #define SAMP_SDK_WANT_AMX_EVENTS 
#include "samp-sdk/samp_sdk.hpp"

// Hook per la native CreateVehicle
Plugin_Native_Hook(CreateVehicle, AMX* amx, cell* params) {
    Native_Params p(amx, params);

    // Estrae i parametri della native CreateVehicle per l'ispezione
    int modelid = p.Get<int>(0);
    float x = p.Get<float>(1);
    float y = p.Get<float>(2);
    float z = p.Get<float>(3);
    float angle = p.Get<float>(4);
    int color1 = p.Get<int>(5);
    int color2 = p.Get<int>(6);
    int respawn_delay = p.Get<int>(7);
    bool addsiren = p.Get<bool>(8);

    Samp_SDK::Log("HOOK: CreateVehicle chiamato! Modello: %d, Pos: (%.2f, %.2f, %.2f)", modelid, x, y, z);

    // Esempio di come *modificare* un parametro di input
    // Se il modello è 400 (Landstalker), lo cambiamo in 401 (Bravura)
    if (modelid == 400) {
        // Modifichiamo direttamente l'array 'params' per la chiamata originale
        params[1] = static_cast<cell>(401); // Il modello è nella posizione 0 dell'array di parametri (params[1])
        Samp_SDK::Log("  -> Modello 400 cambiato in 401 prima della creazione.");
    }
    
    // Chiamiamo la native originale (o il prossimo hook nella catena) con i parametri eventualmente modificati
    cell original_retval = Call_Original_Native(CreateVehicle);

    Samp_SDK::Log("HOOK: CreateVehicle ha restituito: %d (ID del veicolo)", (int)original_retval);

    // Puoi modificare il valore di ritorno qui prima di restituirlo a Pawn.
    // Esempio: se la creazione del veicolo è fallita, restituisci un ID invalido personalizzato.
    if ((int)original_retval == INVALID_VEHICLE_ID) {
        Samp_SDK::Log("  -> Creazione del veicolo fallita nella native originale.");

        return -1; // Restituisce un valore diverso a Pawn.
    }

    return original_retval; // Restituisce il valore restituito dalla native originale (o quello modificato sopra).
}

unsigned int GetSupportFlags() {
    return SUPPORTS_VERSION; 
}

// Implementazioni minime per il ciclo di vita
bool OnLoad() {
    Samp_SDK::Log("Plugin di Esempio di Native Hook caricato!");
    return true;
}

void OnUnload() {
    Samp_SDK::Log("Plugin di Esempio di Native Hook scaricato!");
}

// Questi callbacks saranno presenti solo se SAMP_SDK_WANT_AMX_EVENTS è definito
/*void OnAmxLoad(AMX* amx) {
    Samp_SDK::Log("AMX Load rilevato: %p", (void*)amx);
}

void OnAmxUnload(AMX* amx) {
    Samp_SDK::Log("AMX Unload rilevato: %p", (void*)amx);
}*/
```
> [!WARNING]
> La manipolazione diretta dell'array `cell* params` per alterare i parametri di input richiede cautela. Assicurati di comprendere l'ordine e il tipo dei parametri. Per la maggior parte dei casi d'uso, `p.Get(...)` per ispezionare e `Call_Original_Native(...)` per continuare la catena è sufficiente. La modifica diretta di `params` dovrebbe essere fatta solo se sai che il parametro è un valore e deve essere modificato per la chiamata originale. Per stringhe e array, la modifica è più complessa e generalmente coinvolge `amx::Set_String` per scrivere all'indirizzo esistente o riallocare, il che può essere più facile da gestire chiamando la native tramite `Pawn_Native` con i nuovi valori e restituendo `0` dal tuo hook per annullare la chiamata originale.

### 3.6. `Pawn_*` Macro: Chiamata di Funzioni Pawn da C++

Queste macro sono l'inverso di `Plugin_Public` e `Plugin_Native`: permettono al tuo codice C++ di invocare funzioni Pawn.

#### `Pawn_Native(NomeDellaNative, ...)`

- **Scopo:** Il modo raccomandato per chiamare funzioni native di SA-MP (o di altri plugin) da C++.
- **Meccanismo:** Cerca il puntatore della native nella cache interna dell'SDK (popolata da `Amx_Register_Detour`). Se trovato, esegue la native in un ambiente `Amx_Sandbox` (un'istanza AMX fittizia e isolata).
- **Performance:** La più efficiente, poiché evita la costosa ricerca di `publics` e interagisce direttamente con il puntatore della native.

#### `Pawn_Public(NomeDellaPublic, ...)`

- **Scopo:** Chiama una funzione pubblica specifica in uno script Pawn.
- **Meccanismo:** Percorre le istanze `AMX*` gestite da `Amx_Manager`, cerca la `public` per nome e la esegue.
- **Performance:** Meno efficiente di `Pawn_Native` a causa della ricerca e dell'`amx_Exec` reale. Generalmente, le `publics` sono più lente delle `natives`.
- **Uso:** Ideale per invocare eventi personalizzati nei tuoi Gamemode/Filterscripts che non sono native.

#### `Pawn(NomeDellaFunzione, ...)`

- **Scopo:** Una macro di convenienza che tenta di indovinare se la funzione è una native o una public.
- **Meccanismo:** Per prima cosa, tenta di chiamare come `Pawn_Native`. Se fallisce (la native non viene trovata), tenta di chiamare come `Pawn_Public`.
- **Performance:** Può essere leggermente più lenta di `Pawn_Native` se la funzione è native, a causa del doppio tentativo di ricerca. Per le `publics`, le prestazioni sono le stesse di `Pawn_Public`.
- **Uso:** Per funzioni dove non sei sicuro se sono native o public, o per evitare il boilerplate di tentare una e poi l'altra.

#### Sintassi e Convenzioni

- **Nome della Funzione:** Usa sempre il nome della funzione Pawn **direttamente, senza virgolette**. L'SDK lo convertirà internamente in una stringa.
- **Parametri:** Passa direttamente i parametri C++.

```cpp
// Corretto:
Pawn_Native(SetPlayerPos, playerid, 100.0f, 200.0f, 300.0f); 

// Errato (ma tecnicamente funzionerebbe a causa dell'hash, evitare):
Pawn_Native("SetPlayerPos", playerid, 100.0f, 200.0f, 300.0f); 
```

#### Marshalling dei Parametri di Input

L'SDK converte i tuoi tipi C++ nel formato `cell` dell'AMX, gestendo la memoria come necessario:
- `int`, `bool`, `long`, `enum` -> `cell`
- `float`, `double` -> `cell` (usando `amx::AMX_FTOC`)
- `const char*`, `std::string`, `std::string_view` (C++17+) -> `cell` (alloca memoria nell'AMX, copia la stringa e passa l'indirizzo `amx_addr`)

```cpp
void Send_Formatted_Message(int playerid, const std::string& msg) {
    Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, msg);
}
```

#### Marshalling dei Parametri di Output (Riferimenti: `int&`, `float&`, `std::string&`)

Questa è una funzionalità chiave per comodità e sicurezza. Per le funzioni Pawn che si aspettano un puntatore (riferimento), l'SDK automatizza l'intero processo di allocazione/deallocazione della memoria e copia dei dati.

- **Come usare:** Basta passare la tua variabile per riferimento (`&`).
- **Meccanismo:** L'SDK alloca memoria nell'heap dell'AMX, passa l'indirizzo AMX alla funzione Pawn, si aspetta che la funzione Pawn riempia questo indirizzo, rilegge il valore e libera la memoria dell'AMX. Tutto in modo trasparente.
- **Con `std::string&`:** L'SDK alloca un buffer standard (256 celle) nell'AMX per la stringa.

```cpp
void Get_Player_Location(int playerid) {
    float x, y, z;
    int interiorid, worldid;
    std::string name;

    Pawn_Native(GetPlayerPos, playerid, x, y, z);
    Pawn_Native(GetPlayerInterior, playerid, interiorid);
    Pawn_Native(GetPlayerVirtualWorld, playerid, worldid);
    Pawn_Native(GetPlayerName, playerid, name, MAX_PLAYER_NAME);

    Samp_SDK::Log("Posizione di %s (ID:%d): Pos(%.2f, %.2f, %.2f) Interno:%d Mondo:%d", name.c_str(), playerid, x, y, z, interiorid, worldid);
}
```

#### L'Oggetto `Callback_Result`: Analisi Completa

Tutte le chiamate `Pawn_*` restituiscono un oggetto `Callback_Result`. Questo oggetto è un wrapper sicuro per il risultato della chiamata Pawn.

- `Callback_Result() noexcept`: Costruttore predefinito, indica fallimento (`success_ = false`).
- `Callback_Result(bool success, cell value) noexcept`: Costruttore per successo o fallimento con valore.
- `explicit operator bool() const`: Permette di usare `if (result)` per verificare se la chiamata ha avuto successo.
- `operator cell() const`: Permette di convertire il risultato in `cell` per ottenere il valore.
- `float As_Float() const`: Comodità per ottenere il risultato come `float`.
- `cell Value() const`: Restituisce il valore `cell` grezzo.
- `bool Success() const`: Restituisce `true` se la chiamata Pawn ha avuto successo.
- `int Get_Amx_Error() const`: Restituisce il codice di errore dell'AMX se la chiamata è fallita (0 per successo).

```cpp
// Esempio: Ottenere la vita di un giocatore.
// La native GetPlayerHealth(playerid, &Float:health) si aspetta un playerid e un riferimento alla vita.
int playerid = 0; // Esempio di ID giocatore
float player_health = 0.0f;

// Chiamiamo GetPlayerHealth, passando playerid e player_health per riferimento.
// L'SDK si occuperà del marshalling per il parametro di output 'health'.
Callback_Result result = Pawn_Native(GetPlayerHealth, playerid, player_health);

if (result) { // Verifica se la chiamata ha avuto successo (operatore bool)
    // Il valore restituito da result.As_Float() o result (operatore cell)
    // sarebbe il valore di ritorno della *native*, non il parametro di output.
    // Il valore della vita è già stato aggiornato in 'player_health' a causa del marshalling del parametro di output.
    Samp_SDK::Log("Giocatore %d ha %.1f di vita.", playerid, player_health);
}
else {
    // La chiamata è fallita, forse il giocatore non esiste o la native non è stata trovata.
    Samp_SDK::Log("Errore nell'ottenere la vita del giocatore %d. Codice AMX: %d", playerid, result.Get_Amx_Error());
}

// Per le native che restituiscono un valore e usano parametri di output (meno comune, ma possibile),
// useresti entrambi:
// Callback_Result other_result = Pawn_Native(SomeNative, param1, output_param, param2);
// if (other_result) {
//     cell returned_value = other_result;
//     // output_param è già aggiornato
// }
```

### 3.7. `Plugin_Module`: Gestione dei Moduli Dinamici

La macro `Plugin_Module` consente al tuo plugin di agire come un "caricatore" per altri plugin, creando un'architettura modulare ed estensibile. Un modulo caricato in questo modo è trattato come un plugin di prima classe, con il proprio ciclo di vita degli eventi gestito dal plugin host.

#### Sintassi e Scopo

- `Plugin_Module(const char* nome_del_file_base, const char* directory_del_modulo, const char* messaggio_di_successo_opzionale)`
- `nome_del_file_base`: Il nome *base* del file del modulo, **senza estensione** (es: per `my_module.dll` o `my_module.so`, usa `"my_module"`). L'SDK aggiungerà automaticamente l'estensione `.dll` o `.so` appropriata.
- `directory_del_modulo`: Il percorso della directory in cui si trova il file del modulo (es: `"plugins/my_custom_modules"`). **Non includere il nome del file qui.** L'SDK concatenerà il percorso completo (`directory_del_modulo/nome_del_file_base.ext`).
- `messaggio_di_successo_opzionale`: Un messaggio opzionale da loggare nella console del server se il modulo viene caricato con successo.

```cpp
// main.cpp, all'interno di OnLoad()

// Carica il modulo 'core_logic.dll' (o 'core_logic.so')
// che si trova nella cartella 'modules/custom/' del server.
if (!Plugin_Module("core_logic", "modules/custom", "Modulo Logica Core caricato con successo!"))
    return (Samp_SDK::Log("ERRORE FATALE: Impossibile caricare il modulo 'core_logic'!"), false);

// Carica il modulo 'admin_system.dll' (o 'admin_system.so')
// che si trova direttamente nella cartella 'plugins/' del server.
if (!Plugin_Module("admin_system", "plugins", "Modulo di Amministrazione attivato."))
    Samp_SDK::Log("AVVISO: Impossibile caricare il modulo di Amministrazione.");
```

#### Ciclo di Vita di un Modulo

Un modulo deve esportare le funzioni `Load`, `Unload` e `Supports`, proprio come un normale plugin. L'SDK gestisce il ciclo di vita del modulo come segue:

- **Caricamento:** Quando viene chiamato `Plugin_Module`, l'SDK:
   1. Costruisce il percorso completo del file (es: `modules/custom/core_logic.dll`).
   2. Usa `Dynamic_Library` (`LoadLibrary`/`dlopen`) per caricare il binario.
   3. **Ottiene i puntatori a TUTTE le funzioni del ciclo di vita del modulo:**
      - **Obbligatorie:** `Load`, `Unload`, `Supports`. Se ne manca una, il caricamento del modulo fallisce.
      - **Opzionali:** `AmxLoad`, `AmxUnload`, `ProcessTick`.
   4. Chiama la funzione `Load` del modulo, passando `ppData` del plugin principale.
   5. Se `Load` restituisce `true`, il modulo viene aggiunto alla lista interna dei moduli caricati.

- **Inoltro di Eventi:** Il plugin host **inoltra automaticamente** gli eventi a tutti i moduli caricati.
 > [!IMPORTANT]
 > Affinché gli eventi vengano inoltrati correttamente, il **plugin host** (quello che chiama `Plugin_Module`) deve essere configurato per ricevere tali eventi.
 > - Affinché `AmxLoad` e `AmxUnload` funzionino nei moduli, il plugin host deve definire la macro `SAMP_SDK_WANT_AMX_EVENTS`.
 > - Affinché `ProcessTick` funzioni nei moduli, il plugin host deve definire la macro `SAMP_SDK_WANT_PROCESS_TICK`.

- **Scaricamento:** Durante `OnUnload` del tuo plugin principale, l'SDK scarica tutti i moduli che sono stati caricati tramite `Plugin_Module`. Questo viene fatto in **ordine inverso** rispetto al caricamento (l'ultimo caricato è il primo a essere scaricato), il che è cruciale per gestire le dipendenze e garantire il corretto rilascio delle risorse.

#### Benefici della Modularizzazione

- **Organizzazione del Codice:** Dividi grandi plugin in componenti più piccoli e gestibili, ognuno nel proprio file modulo.
- **Riusabilità:** Crea moduli generici (es: un modulo database, un modulo avanzato di sistema di log) che possono essere usati da diversi plugin, promuovendo la riusabilità del codice.
- **Componenti Indipendenti:** Crea moduli che sono **totalmente orientati agli eventi e indipendenti**. Un modulo può avere le proprie `Plugin_Native`s, intercettare `Plugin_Public`s e avere la propria logica `OnProcessTick`, operando come un plugin autonomo, ma caricato da un host.
- **Aggiornamenti Dinamici:** In scenari controllati, consente l'aggiornamento di parti del tuo sistema (sostituendo una `.dll` o `.so` del modulo) senza la necessità di ricompilare e riavviare il plugin principale o l'intero server (anche se ciò richiede una gestione rigorosa della versione e della compatibilità).

### 3.8. `Plugin_Call`: Chiamata delle Native Interne del Plugin

Usa `Plugin_Call` per invocare una `Plugin_Native` definita **all'interno del tuo stesso plugin**.

#### Sintassi e Vantaggi di Performance

- `Plugin_Call(NomeDellaNative, Param1, Param2, ...)`
- **Vantaggio:** Evita l'overhead di cercare la native nell'array di native dell'AMX. L'SDK mantiene una mappa diretta di hash di nomi a puntatori di funzione per le proprie native, rendendo questo il modo più veloce per chiamarle internamente.
- **Richiede:** `SAMP_SDK_WANT_AMX_EVENTS`.

```cpp
// main.cpp
Plugin_Native(InternalCheckPlayerLevel, AMX* amx, cell* params) {
    int playerid;
    Register_Parameters(playerid);

    // Logica per verificare il livello
    return (playerid % 2 == 0) ? 1 : 0; // Esempio: livello pari per ID pari
}

void Check_All_Players_Level() {
    for (int i = 0; i < MAX_PLAYERS; ++i) {
        if (Pawn_Native(IsPlayerConnected, i)) {
            if (Plugin_Call(InternalCheckPlayerLevel, i)) // Chiama la tua stessa native
                Samp_SDK::Log("Giocatore %d è di alto livello!", i);
        }
    }
}
```

### 3.9. Funzioni Utilità dell'SDK

#### `Samp_SDK::Log(const char* format, ...)`

- **Descrizione:** Stampa messaggi nella console del server e nel file `server_log.txt`. Un wrapper sicuro per `logprintf`.
- **Uso:** Per debug, messaggi di stato ed errori.
- **Meccanismo:** Internamente, l'SDK ottiene il puntatore a `logprintf` tramite `ppData[PLUGIN_DATA_LOGPRINTF]`. La funzione gestisce la formattazione della stringa in modo sicuro.

```cpp
// Ovunque nel tuo plugin
Samp_SDK::Log("Il plugin è stato inizializzato con un valore %d e una stringa '%s'.", 123, "test");
```

#### `std::string Plugin_Format(const char* format, ...)` (Raccomandato)

- **Descrizione:** Formatta una stringa in modo sicuro (simile a `sprintf`) e restituisce una `std::string`. Questo è il modo **raccomandato e più idiomatico** per formattare stringhe da utilizzare all'interno del tuo plugin.
- **Uso:** Ideale per costruire messaggi formattati prima di passarli a `Samp_SDK::Log`, `Pawn_Native(SendClientMessage, ...)`, o per qualsiasi altra esigenza di stringa all'interno del tuo codice C++.
- **Meccanismo:** Internamente, `Plugin_Format` è una macro che chiama `Samp_SDK::Format`. Utilizza `vsnprintf` per determinare la dimensione esatta della stringa formattata e alloca una `std::string` con capacità sufficiente, evitando overflow del buffer.

```cpp
int playerid = 0; // Esempio di ID
int health = 50;
Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, Plugin_Format("Giocatore %d, la tua vita attuale è %d.", playerid, health));

// Può essere usato anche per i log interni
Samp_SDK::Log(Plugin_Format("DEBUG: Elaborazione dello stato per l'ID %d", playerid));
```

#### `std::string Samp_SDK::Format(const char* format, ...)` (Dettaglio di Implementazione)

- **Descrizione:** La funzione di implementazione sottostante per la formattazione di stringhe, situata all'interno del namespace `Samp_SDK`.
- **Uso:** Generalmente non è chiamata direttamente dall'utente. La macro `Plugin_Format` è fornita come una convenienza per questa funzione, allineandosi con la convenzione di denominazione di altre macro dell'SDK (`Plugin_Public`, `Plugin_Native`). La chiameresti direttamente solo se volessi evitare la macro `Plugin_Format` per qualche motivo specifico.

```cpp
// Esempio di come funziona Samp_SDK::Format, ma preferisci Plugin_Format
std::string raw_status = Samp_SDK::Format("Solo per uso interno: %d.", 42);
```

#### `std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`

- **Descrizione:** Converte un indirizzo di stringa AMX (`cell amx_addr`) in una `std::string` C++.
- **Uso:** Principalmente all'interno di `Plugin_Native` e `Plugin_Native_Hook` quando è necessario accedere a stringhe che non vengono automaticamente convertite da `Register_Parameters` o `Native_Params` (es: se il parametro Pawn è una `const` `string` e non è stato dichiarato come `std::string` nel tuo `Plugin_Native` o `Plugin_Public` per il Marshalling automatico).

```cpp
Plugin_Native(PrintRawAmxString, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    cell amx_string_addr = p.Get<cell>(0); // Ottiene l'indirizzo della stringa nell'AMX

    std::string cpp_string = Samp_SDK::Get_String(amx, amx_string_addr);
    Samp_SDK::Log("Stringa dall'AMX: %s", cpp_string.c_str());

    return 1;
}
```

## 4. Compilazione e Deploy

### Requisiti di Architettura e Piattaforma

- Il tuo plugin **DEVE** essere compilato per l'architettura **x86 (32-bit)**.
- Piattaforme Supportate: Windows (.dll) e Linux (.so).

### Esempi di Comandi di Compilazione

#### **MSVC (Visual Studio)**

1. Crea un nuovo progetto di "Dynamic-Link Library (DLL)".
2. Nelle impostazioni del progetto, imposta la "Piattaforma di Soluzione" su **x86**.
3. Assicurati che lo standard del linguaggio C++ sia almeno C++17.

#### **GCC / Clang (Linux)**

```bash
# Per un plugin chiamato 'my_plugin.so' da 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -fPIC -Wall -Wextra -Wl,--no-undefined main.cpp -o my_plugin.so
```
- `-m32`: Compila per 32-bit.
- `-shared`: Crea una libreria condivisa (`.so`).
- `-std=c++17`: Imposta lo standard C++ su C++17 (può essere `c++20`, ma C++17 è il minimo).
- `-O2`: Livello di ottimizzazione 2.
- `-fPIC`: Genera codice indipendente dalla posizione, necessario per le librerie condivise.
- `-Wall -Wextra`: Attiva avvisi aggiuntivi per aiutare a rilevare errori.
- `-Wl,--no-undefined`: Impedisce la creazione della libreria se ci sono simboli indefiniti.

#### **GCC / Clang (MinGW su Windows)**

```bash
# Per un plugin chiamato 'my_plugin.dll' da 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -static-libstdc++ -static-libgcc -Wl,--no-undefined main.cpp -o my_plugin.dll
```
- `-static-libstdc++`: Collega la libreria standard C++ in modo statico. Essenziale per evitare che il tuo plugin dipenda da DLL di runtime specifiche del compilatore che potrebbero non essere presenti nel sistema dell'utente.
- `-static-libgcc`: Collega la libreria GCC in modo statico.

### Considerazioni per la Distribuzione

- **Nome del File:** Il tuo plugin deve avere l'estensione `.dll` (Windows) o `.so` (Linux). Es: `my_plugin.dll`.
- **Posizione:** Posiziona il file compilato nella cartella `plugins/` del tuo server SA-MP.
- **server.cfg:** Aggiungi il nome del tuo plugin (se è Windows, senza estensione) alla riga `plugins` in `server.cfg`.
   ```
   plugins my_plugin (se è Linux, my_plugin.so)
   ```

## Licenza

Copyright © **AlderGrounds**

Questo software è concesso in licenza secondo i termini della Licenza MIT ("Licenza"); è possibile utilizzare questo software in conformità con le condizioni della Licenza. Una copia della Licenza può essere ottenuta su: [MIT License](https://opensource.org/licenses/MIT)

### Termini e Condizioni d'Uso

#### 1. Permessi Concessi

La presente licenza concede gratuitamente a chiunque ottenga una copia di questo software e dei file di documentazione associati i seguenti diritti:
* Utilizzare, copiare, modificare, unire, pubblicare, distribuire, sublicenziare e/o vendere copie del software senza restrizioni
* Permettere alle persone a cui il software viene fornito di fare lo stesso, soggetto alle seguenti condizioni

#### 2. Condizioni Obbligatorie

Tutte le copie o parti sostanziali del software devono includere:
* L'avviso di copyright sopra riportato
* Questo avviso di permesso
* L'avviso di esclusione di responsabilità sotto riportato

#### 3. Diritti d'Autore

Il software e tutta la documentazione associata sono protetti dalle leggi sul diritto d'autore. La **AlderGrounds** mantiene la titolarità dei diritti d'autore originali del software.

#### 4. Esclusione di Garanzia e Limitazione di Responsabilità

IL SOFTWARE VIENE FORNITO "COSÌ COM'È", SENZA GARANZIE DI ALCUN TIPO, ESPLICITE O IMPLICITE, INCLUSE, MA NON LIMITATE A, LE GARANZIE DI COMMERCIABILITÀ, IDONEITÀ PER UN PARTICOLARE SCOPO E NON VIOLAZIONE.

IN NESSUN CASO GLI AUTORI O I TITOLARI DEL COPYRIGHT SARANNO RESPONSABILI PER QUALSIASI RECLAMO, DANNO O ALTRA RESPONSABILITÀ, SIA IN UN'AZIONE DI CONTRATTO, ILLECITO O ALTRO, DERIVANTE DA, FUORI O IN CONNESSIONE CON IL SOFTWARE O L'USO O ALTRE OPERAZIONI NEL SOFTWARE.

---

Per informazioni dettagliate sulla Licenza MIT, consultare: https://opensource.org/licenses/MIT