# SA-MP SDK

<div align="center">

![C++](https://img.shields.io/badge/C%2B%2B-17%2B-00599C?style=for-the-badge&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-blue?style=for-the-badge&logo=windows&logoColor=white)
![Architecture](https://img.shields.io/badge/Architecture-x86%20(32--bit)-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**Un SDK C++ moderne, header-only et de haut niveau pour le développement de plugins et de modules pour SA-MP.**

</div>

## Langues

- Português: [README](../../)
- Deutsch: [README](../Deutsch/README.md)
- English: [README](../English/README.md)
- Español: [README](../Espanol/README.md)
- Italiano: [README](../Italiano/README.md)
- Polski: [README](../Polski/README.md)
- Русский: [README](../Русский/README.md)
- Svenska: [README](../Svenska/README.md)
- Türkçe: [README](../Turkce/README.md)

## Table des matières

- [SA-MP SDK](#sa-mp-sdk)
  - [Langues](#langues)
  - [Table des matières](#table-des-matières)
  - [1. Introduction et philosophie de conception](#1-introduction-et-philosophie-de-conception)
    - [Le problème avec l'API C standard de SA-MP](#le-problème-avec-lapi-c-standard-de-sa-mp)
    - [La solution SA-MP SDK : Abstraction avec sécurité et performance](#la-solution-sa-mp-sdk--abstraction-avec-sécurité-et-performance)
    - [Modèle Header-Only : Avantages et implications](#modèle-header-only--avantages-et-implications)
  - [2. Configuration et environnement](#2-configuration-et-environnement)
    - [Exigences de Compilation](#exigences-de-compilation)
    - [Structure de fichiers recommandée](#structure-de-fichiers-recommandée)
    - [Macros de configuration essentielles](#macros-de-configuration-essentielles)
      - [`SAMP_SDK_IMPLEMENTATION`](#samp_sdk_implementation)
      - [`SAMP_SDK_WANT_AMX_EVENTS`](#samp_sdk_want_amx_events)
      - [`SAMP_SDK_WANT_PROCESS_TICK`](#samp_sdk_want_process_tick)
    - [Définitions et constantes de SA-MP (`samp_defs.hpp`)](#définitions-et-constantes-de-sa-mp-samp_defshpp)
  - [3. Guide d'utilisation complet de l'API](#3-guide-dutilisation-complet-de-lapi)
    - [3.1. Le cycle de vie du plugin](#31-le-cycle-de-vie-du-plugin)
      - [`bool OnLoad()`](#bool-onload)
      - [`void OnUnload()`](#void-onunload)
      - [`unsigned int GetSupportFlags()`](#unsigned-int-getsupportflags)
      - [`void OnAmxLoad(AMX* amx)`](#void-onamxloadamx-amx)
      - [`void OnAmxUnload(AMX* amx)`](#void-onamxunloadamx-amx)
      - [`void OnProcessTick()`](#void-onprocesstick)
    - [3.2. Exportation des Fonctions du Plugin](#32-exportation-des-fonctions-du-plugin)
      - [Exportation pour MSVC (Visual Studio) avec `Export_Plugin`](#exportation-pour-msvc-visual-studio-avec-export_plugin)
      - [Exportation pour GCC / Clang avec `SAMP_SDK_EXPORT`](#exportation-pour-gcc--clang-avec-samp_sdk_export)
    - [3.3. `Plugin_Public`: Interception des événements Pawn](#33-plugin_public-interception-des-événements-pawn)
      - [Syntaxe et déclaration](#syntaxe-et-déclaration)
      - [Marshalling automatique des paramètres](#marshalling-automatique-des-paramètres)
      - [Contrôle de flux : `PLUGIN_PUBLIC_CONTINUE` vs `PLUGIN_PUBLIC_STOP`](#contrôle-de-flux--plugin_public_continue-vs-plugin_public_stop)
      - [Ghost Callbacks](#ghost-callbacks)
    - [3.4. `Plugin_Native`: Création de fonctions natives en C++](#34-plugin_native-création-de-fonctions-natives-en-c)
      - [Syntaxe et signature fixe](#syntaxe-et-signature-fixe)
      - [Enregistrement automatique des natives](#enregistrement-automatique-des-natives)
      - [Extraction des paramètres : `Register_Parameters` vs. `Native_Params`](#extraction-des-paramètres--register_parameters-vs-native_params)
        - [`Register_Parameters(...)`](#register_parameters)
        - [`Native_Params` (API complète : `Get`, `Get_REF`, `Set_REF`)](#native_params-api-complète--get-get_ref-set_ref)
          - [`p.Count()`](#pcount)
          - [`p.Get<T>(size_t index)`](#pgettsize_t-index)
          - [`p.Get_REF<T>(size_t index, T& out_value)`](#pget_reftsize_t-index-t-out_value)
          - [`p.Get_REF<T>(size_t index)` (C++17+)](#pget_reftsize_t-index-c17)
          - [`p.Set_REF<T>(size_t index, T value)`](#pset_reftsize_t-index-t-value)
      - [Retour de valeurs](#retour-de-valeurs)
    - [3.5. `Plugin_Native_Hook`: Interception des natives SA-MP existantes](#35-plugin_native_hook-interception-des-natives-sa-mp-existantes)
      - [Syntaxe et signature fixe](#syntaxe-et-signature-fixe-1)
      - [Enregistrement et activation du hook](#enregistrement-et-activation-du-hook)
      - [Appel de la native originale (chaîne de hooks) : `Call_Original_Native`](#appel-de-la-native-originale-chaîne-de-hooks--call_original_native)
      - [Exemple complet de `Plugin_Native_Hook`](#exemple-complet-de-plugin_native_hook)
    - [3.6. Macros `Pawn_*`: Appel de fonctions Pawn depuis le C++](#36-macros-pawn_-appel-de-fonctions-pawn-depuis-le-c)
      - [`Pawn_Native(NomDeLaNative, ...)`](#pawn_nativenomdelanative-)
      - [`Pawn_Public(NomDeLaPublic, ...)`](#pawn_publicnomdelapublic-)
      - [`Pawn(NomDeLaFonction, ...)`](#pawnnomdelafonction-)
      - [Syntaxe et conventions](#syntaxe-et-conventions)
      - [Marshalling des paramètres d'entrée](#marshalling-des-paramètres-dentrée)
      - [Marshalling des paramètres de sortie (références : `int&`, `float&`, `std::string&`)](#marshalling-des-paramètres-de-sortie-références--int-float-stdstring)
      - [L'objet `Callback_Result`: Analyse complète](#lobjet-callback_result-analyse-complète)
    - [3.7. `Plugin_Module`: Gestion des modules dynamiques](#37-plugin_module-gestion-des-modules-dynamiques)
      - [Syntaxe et objectif](#syntaxe-et-objectif)
      - [Cycle de vie d'un module](#cycle-de-vie-dun-module)
      - [Avantages de la modularisation](#avantages-de-la-modularisation)
    - [3.8. `Plugin_Call`: Appel des natives internes du plugin](#38-plugin_call-appel-des-natives-internes-du-plugin)
      - [Syntaxe et avantages en termes de performances](#syntaxe-et-avantages-en-termes-de-performances)
    - [3.9. Fonctions utilitaires du SDK](#39-fonctions-utilitaires-du-sdk)
      - [`Samp_SDK::Log(const char* format, ...)`](#samp_sdklogconst-char-format-)
      - [`std::string Plugin_Format(const char* format, ...)` (recommandé)](#stdstring-plugin_formatconst-char-format--recommandé)
      - [`std::string Samp_SDK::Format(const char* format, ...)` (détail d'implémentation)](#stdstring-samp_sdkformatconst-char-format--détail-dimplémentation)
      - [`std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`](#stdstring-samp_sdkget_stringamx-amx-cell-amx_addr)
  - [4. Compilation et déploiement](#4-compilation-et-déploiement)
    - [Exigences d'architecture et de plateforme](#exigences-darchitecture-et-de-plateforme)
    - [Exemples de commandes de compilation](#exemples-de-commandes-de-compilation)
      - [**MSVC (Visual Studio)**](#msvc-visual-studio)
      - [**GCC / Clang (Linux)**](#gcc--clang-linux)
      - [**GCC / Clang (MinGW sur Windows)**](#gcc--clang-mingw-sur-windows)
    - [Considérations pour la distribution](#considérations-pour-la-distribution)
  - [Licence](#licence)
    - [Conditions Générales d'Utilisation](#conditions-générales-dutilisation)
      - [1. Autorisations Accordées](#1-autorisations-accordées)
      - [2. Conditions Obligatoires](#2-conditions-obligatoires)
      - [3. Droits d'Auteur](#3-droits-dauteur)
      - [4. Exclusion de Garantie et Limitation de Responsabilité](#4-exclusion-de-garantie-et-limitation-de-responsabilité)

## 1. Introduction et philosophie de conception

### Le problème avec l'API C standard de SA-MP

L'API de plugins de SA-MP est une interface de programmation en C. Bien que fonctionnelle et fondamentale, elle présente les défis inhérents à la programmation de bas niveau :
- **Gestion manuelle de la mémoire :** Des fonctions comme `amx_Allot` et `amx_Release` exigent que le développeur alloue et désalloue explicitement la mémoire dans le tas de l'AMX. C'est une source courante de fuites de mémoire et de pannes d'exécution.
- **Typage faible et conversions manuelles :** Les paramètres sont passés sous forme de tableau de `cell`s, ce qui force des conversions explicites (et souvent dangereuses) entre `cell`, `int`, `float`, et `char*`.
- **Verbosité et boilerplate :** Extraire plusieurs paramètres d'un tableau `cell* params`, gérer les tailles de chaînes et gérer la pile de l'AMX pour les rappels C++ vers Pawn exige un code répétitif.
- **Fragilité de l'interface :** Le manque de vérification au moment de la compilation (type safety) signifie que les erreurs de passage de paramètres ou de types peuvent passer inaperçues jusqu'à l'exécution, provoquant des plantages ou des comportements indéfinis.

### La solution SA-MP SDK : Abstraction avec sécurité et performance

Le SA-MP SDK aborde ces problèmes en fournissant une puissante couche d'abstraction en C++ :
- **RAII (Resource Acquisition Is Initialization) :** Gestion automatique de la mémoire dans l'AMX. `Amx_Scoped_Memory` garantit que la mémoire allouée est libérée.
- **Sécurité des types :** Conversion automatique et sécurisée des paramètres entre C++ et Pawn. Vous traitez directement avec `int`, `float`, `std::string`.
- **Syntaxe concise et idiomatique :** Les macros et les modèles fournissent une API propre qui ressemble davantage au C++ moderne qu'à l'API C traditionnelle.
- **Interception robuste :** Un moteur de hooking avancé permet l'interception transparente des callbacks Pawn (`Plugin_Public`), la création de nouvelles natives (`Plugin_Native`), et **le hooking et l'enchaînement des fonctions natives SA-MP existantes (`Plugin_Native_Hook`)**.
- **Haute performance :** Utilisation intensive du hachage au moment de la compilation (FNV1a), de la mise en cache des fonctions et des optimisations `thread_local` pour minimiser la surcharge des abstractions.

### Modèle Header-Only : Avantages et implications

Le SDK est composé exclusivement de fichiers d'en-tête (`.hpp`, `.h`).
- **Avantages :**
   - **Intégration simplifiée :** Il n'y a pas de bibliothèques à construire, lier ou distribuer. Il suffit d'inclure les en-têtes.
   - **Optimisations du compilateur :** Le compilateur a une visibilité complète du code du SDK et de votre plugin, ce qui permet un inlining agressif et des optimisations au moment de l'édition des liens, ce qui peut se traduire par des binaires plus rapides.
- **Implications :**
   - **Temps de compilation :** Pour les très grands projets, la compilation peut prendre plus de temps en raison de l'inclusion répétée du code du SDK. Cela est atténué par les gardes d'inclusion et la nature "n'inclure que ce qui est nécessaire" du C++.
   - **Macros d'implémentation :** La nécessité de la macro `SAMP_SDK_IMPLEMENTATION` est une conséquence du modèle header-only pour éviter les redéfinitions de symboles.

## 2. Configuration et environnement

### Exigences de Compilation

- **Compilateur C++ :** Compatible avec C++17 ou supérieur.
   - GCC (version 8+)
   - Clang (version 5+)
   - MSVC (Visual Studio 2017+)
- **Architecture :** **x86 (32 bits)**. SA-MP fonctionne exclusivement sur cette architecture. Le SDK inclut des vérifications dans `platform.hpp` qui généreront des erreurs de compilation si une architecture incorrecte est détectée.
- **Système d’exploitation :** Windows ou Linux.

### Structure de fichiers recommandée

Pour plus de clarté et d'organisation, il est courant d'organiser le SDK dans un sous-dossier `samp-sdk`.

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

### Macros de configuration essentielles

Définissez toujours ces macros *avant* d'inclure `samp_sdk.hpp`.

#### `SAMP_SDK_IMPLEMENTATION`

- **Objectif :** Indique au compilateur que ce fichier `.cpp` doit générer les implémentations des fonctions d'exportation du plugin (`Supports`, `Load`, `Unload`, `AmxLoad`, `AmxUnload`, `ProcessTick`). **Le SDK gère automatiquement l'exportation de ces fonctions, éliminant le besoin de fichiers `.def` (sous Windows) ou de déclarations `__attribute__((visibility("default")))` (sous Linux) pour ces fonctions.**
- **Impact technique :** Sans cette macro, l'éditeur de liens ne trouvera pas les exportations nécessaires, et le serveur SA-MP ne pourra pas charger votre plugin.
- **Règle fondamentale :** **Définissez cette macro dans UN SEUL fichier `.cpp` de tout votre projet.** La définir dans plus d'un fichier provoquera une erreur de liaison de "symbole dupliqué".

```cpp
// main.cpp
#define SAMP_SDK_IMPLEMENTATION // The macro makes the SDK export the necessary functions automatically.
#include "samp-sdk/samp_sdk.hpp"

// ... your plugin code ...
```

#### `SAMP_SDK_WANT_AMX_EVENTS`

- **Objectif :** Active les callbacks de cycle de vie du script Pawn (`OnAmxLoad`, `OnAmxUnload`) et la fonctionnalité de création de nouvelles natives en C++ (`Plugin_Native`).
- **Fonctionnalités activées :**
   - Callbacks `OnAmxLoad(AMX* amx)` et `OnAmxUnload(AMX* amx)`.
   - Déclaration et enregistrement de nouvelles natives C++ utilisant `Plugin_Native`.
   - La macro `Plugin_Call` pour invoquer des natives créées avec `Plugin_Native` au sein de votre propre plugin.
- **Impact technique :** Lorsque cette macro est définie, le SDK collecte automatiquement toutes vos `Plugin_Native`s. Dans la fonction `Supports()`, le drapeau `SUPPORTS_AMX_NATIVES` est automatiquement ajouté s'il y a des `Plugin_Native`s dans votre projet.
- **Flexibilité :** **Vous pouvez définir cette macro dans plusieurs fichiers `.cpp`**. Le système d'enregistrement statique du SDK consolidera toutes les natives de différentes unités de compilation en une seule liste globale.

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

- **Objectif :** Active le callback `OnProcessTick()`, qui est invoqué régulièrement par le serveur.
- **Impact technique :** Ajoute automatiquement le drapeau `SUPPORTS_PROCESS_TICK` dans la fonction `Supports()`.

```cpp
// main.cpp
#define SAMP_SDK_IMPLEMENTATION
#define SAMP_SDK_WANT_PROCESS_TICK
#include "samp-sdk/samp_sdk.hpp"

void OnProcessTick() {
    // Logic executed at each server "tick" (e.g. 20ms)
    // Be careful with heavy operations here!
}
```

### Définitions et constantes de SA-MP (`samp_defs.hpp`)

Ce fichier fournit toutes les constantes et limites connues de SA-MP, telles que `MAX_PLAYERS`, `INVALID_PLAYER_ID`, `PLAYER_STATE_ONFOOT`, `WEAPON_DEAGLE`, `DIALOG_STYLE_LIST`, etc. Il est automatiquement inclus par `samp_sdk.hpp` et doit être utilisé pour garantir la compatibilité et la lisibilité du code.

## 3. Guide d'utilisation complet de l'API

### 3.1. Le cycle de vie du plugin

Les fonctions suivantes sont les points d'entrée et de sortie de votre plugin, exportées automatiquement par le SDK.

#### `bool OnLoad()`

- **Description :** Première fonction appelée par le serveur SA-MP après le chargement réussi de votre plugin en mémoire.
- **Utilisation :** Idéal pour initialiser tout système, charger des configurations, ouvrir des connexions à des bases de données ou charger des modules (`Plugin_Module`).
- **Retour :**
   - `true` : Le plugin a été initialisé avec succès et le chargement se poursuit.
   - `false` : Le plugin a échoué à s'initialiser. Le chargement sera annulé et le plugin sera déchargé.

```cpp
// main.cpp
bool OnLoad() {
    Samp_SDK::Log("Initializing MyPlugin v1.0...");

    // Example: Load a module (more details in section 3.6)
    if (!Plugin_Module("my_database_module", "plugins/db_connector", "Database module loaded.")) {
        Samp_SDK::Log("ERROR: Failed to load database module!");

        return false; // Aborts loading of the main plugin
    }

    return true;
}
```

#### `void OnUnload()`

- **Description :** Dernière fonction appelée par le serveur SA-MP avant de décharger votre plugin de la mémoire.
- **Utilisation :** Idéal pour nettoyer les ressources, fermer les connexions, sauvegarder les états et s'assurer qu'aucune ressource n'est fuite. Le SDK gère automatiquement le déchargement des modules (`Plugin_Module`).

```cpp
// main.cpp
void OnUnload() {
    Samp_SDK::Log("MyPlugin unloaded. Releasing resources...");
    // No manual action is needed for modules loaded via Plugin_Module;
    // the SDK takes care of it.
}
```

#### `unsigned int GetSupportFlags()`

- **Description :** Informe le serveur SA-MP des fonctionnalités que votre plugin prend en charge et souhaite utiliser.
- **Utilisation :** **Retournez toujours `SUPPORTS_VERSION` (ou `SAMP_PLUGIN_VERSION`).** Les flags `SUPPORTS_AMX_NATIVES` et `SUPPORTS_PROCESS_TICK` sont automatiquement ajoutés par le SDK s'il y a des `Plugin_Native`s, et/ou si la macro `SAMP_SDK_WANT_PROCESS_TICK` est définie, respectivement. Cela simplifie la maintenance et évite les erreurs.

```cpp
// main.cpp
unsigned int GetSupportFlags() {
    return SUPPORTS_VERSION; // The SDK adds the necessary flags automatically.
}
```

#### `void OnAmxLoad(AMX* amx)`

- **Requis :** `SAMP_SDK_WANT_AMX_EVENTS`
- **Description :** Appelée chaque fois qu'un nouveau script Pawn (un Gamemode ou Filterscript) est chargé et initialisé sur le serveur.
- **Utilisation :** Si vous avez besoin d'une logique spécifique pour chaque script AMX, ou d'initialiser des données spécifiques par script.

```cpp
// main.cpp (with SAMP_SDK_WANT_AMX_EVENTS defined)
void OnAmxLoad(AMX* amx) {
    // amx represents the new loaded script instance.
    Samp_SDK::Log("AMX script loaded: %p", (void*)amx);
}
```

#### `void OnAmxUnload(AMX* amx)`

- **Requis :** `SAMP_SDK_WANT_AMX_EVENTS`
- **Description :** Appelée lorsqu'un script Pawn est déchargé du serveur.
- **Utilisation :** Pour nettoyer les ressources spécifiques que vous avez allouées ou associées à cet `AMX*` particulier.

```cpp
// main.cpp (with SAMP_SDK_WANT_AMX_EVENTS defined)
void OnAmxUnload(AMX* amx) {
    Samp_SDK::Log("AMX script unloaded: %p", (void*)amx);
}
```

#### `void OnProcessTick()`

- **Requis :** `SAMP_SDK_WANT_PROCESS_TICK`
- **Description :** Appelée de manière répétée à chaque "tick" du serveur (généralement 20 fois par seconde, soit toutes les 50ms).
- **Utilisation :** Pour la logique de fond continue, les minuteries, les mises à jour d'état qui ne dépendent pas des événements du joueur, ou la synchronisation des données.
- **Attention :** Évitez les opérations bloquantes ou gourmandes en calcul ici, car elles peuvent provoquer des latences sur le serveur.

```cpp
// main.cpp (with SAMP_SDK_WANT_PROCESS_TICK defined)
static int tick_count = 0;

void OnProcessTick() {
    tick_count++;

    if (tick_count % 200 == 0) // Every 10 seconds (20 ticks/sec * 10 sec = 200 ticks)
        Samp_SDK::Log("Server active for %d seconds.", tick_count / 20);
}
```

### 3.2. Exportation des Fonctions du Plugin

Pour que le serveur SA-MP puisse appeler les fonctions de votre plugin (`Load`, `Supports`, etc.), elles doivent être "exportées" du fichier DLL (Windows) ou SO (Linux). Le SDK automatise l'exportation des fonctions de cycle de vie standard, mais fournit également des outils pour que vous puissiez exporter vos propres fonctions personnalisées, si vous avez besoin d'interopérabilité avec d'autres programmes.

La méthode pour exporter des fonctions varie selon le compilateur.

#### Exportation pour MSVC (Visual Studio) avec `Export_Plugin`

Sous Windows avec MSVC, le moyen le plus simple d'exporter des fonctions personnalisées est d'utiliser la macro `Export_Plugin`, définie dans `exports.hpp`.

- **Syntaxe:** `Export_Plugin("Fonction", "Pile")`
- **`Fonction`**: Le nom exact de la fonction à exporter.
- **`Pile`**: La quantité totale d'octets que les paramètres de la fonction occupent dans la pile. Pour la convention `__stdcall` (standard du SDK sous Windows), le calcul est `4 * (Nombre de Paramètres)`.

```cpp
#include "samp-sdk/exports.hpp"

// Exemple: Exportation d'une fonction personnalisée qui pourrait être appelée
// par un autre programme ou plugin qui connaît sa signature.
const char* SAMP_SDK_CALL GetPluginVersion() {
    return "1.0.0";
}

Export_Plugin("GetPluginVersion", "0");
```

> [!WARNING]
> **Limitation de `Export_Plugin`**
> Cette macro fonctionne **uniquement avec le compilateur MSVC (Visual Studio)**. Elle utilise une directive `#pragma` spécifique à Microsoft qui est ignorée par d'autres compilateurs comme GCC et Clang.

#### Exportation pour GCC / Clang avec `SAMP_SDK_EXPORT`

Pour GCC et Clang (sous Windows ou Linux), l'exportation est gérée par la macro `SAMP_SDK_EXPORT`, définie dans `platform.hpp`. Vous la placez simplement avant la définition de la fonction.

- **Mécanisme:** Sous Linux, elle ajoute `__attribute__((visibility("default")))`. Sous Windows avec GCC/Clang, elle ajoute `__attribute__((dllexport))`.
- **Utilisation:** Le SDK applique déjà `SAMP_SDK_EXPORT` à toutes les fonctions de cycle de vie (`Load`, `Unload`, etc.), donc leur exportation est entièrement automatique pour ces compilateurs. Pour vos fonctions personnalisées, faites simplement la même chose.

```cpp
// Pour GCC/Clang, la définition de la fonction avec SAMP_SDK_EXPORT est suffisante.
SAMP_SDK_EXPORT const char* SAMP_SDK_CALL GetPluginVersion() {
    return "1.0.0";
}
```

### 3.3. `Plugin_Public`: Interception des événements Pawn

La macro `Plugin_Public` est le pont principal pour recevoir les rappels Pawn dans votre code C++.

#### Syntaxe et déclaration

- `Plugin_Public(NomDeLaPublic, Type1 Param1, Type2 Param2, ...)`
- Le nom de la fonction C++ que vous déclarez **doit être le même** que le callback Pawn (ex : `OnPlayerConnect`).
- Les types de paramètres C++ (`int`, `float`, `std::string`) sont automatiquement convertis par le SDK.

```cpp
// Intercepts OnPlayerText(playerid, text[])
Plugin_Public(OnPlayerText, int playerid, std::string text) {
    Samp_SDK::Log("Player %d said: %s", playerid, text.c_str());

    return PLUGIN_PUBLIC_CONTINUE;
}
```

#### Marshalling automatique des paramètres

Le SDK gère automatiquement la lecture de la `cell stack` de l'AMX et la conversion vers les types C++ spécifiés :
- `int` : Converti directement de `cell`.
- `float` : Converti de `cell` en utilisant `amx::AMX_CTOF`.
- `std::string` : Le SDK lit l'adresse de la chaîne dans l'AMX, alloue un `std::string` en C++ et copie le contenu.

#### Contrôle de flux : `PLUGIN_PUBLIC_CONTINUE` vs `PLUGIN_PUBLIC_STOP`

La valeur retournée par votre fonction `Plugin_Public` est cruciale et détermine le flux d'exécution du callback :
- `return PLUGIN_PUBLIC_CONTINUE;` (valeur `1`) : Indique que l'exécution du callback doit **continuer**. S'il y a d'autres plugins qui interceptent également ce callback, ils seront appelés (dans l'ordre inverse de chargement). Ensuite, la `public` originale dans le script Pawn sera invoquée.
- `return PLUGIN_PUBLIC_STOP;` (valeur `0`) : Indique que l'exécution du callback doit être **interrompue**. Aucun autre plugin (avec une priorité inférieure) ou la `public` originale dans le script Pawn ne sera invoqué pour cet événement. C'est idéal pour implémenter un système qui "remplace" ou "bloque" un comportement par défaut de SA-MP.

```cpp
// main.cpp
Plugin_Public(OnPlayerCommandText, int playerid, std::string cmdtext) {
    if (cmdtext == "/freeze") {
        Pawn_Native(TogglePlayerControllable, playerid, 0); // Freezes the player
        Pawn_Native(SendClientMessage, playerid, -1, Plugin_Format("Player %d frozen.", playerid));

        return PLUGIN_PUBLIC_STOP; // Prevents the command from being processed by other scripts.
    }

    return PLUGIN_PUBLIC_CONTINUE; // Allows other commands to be processed.
}
```

#### Ghost Callbacks

Une caractéristique avancée de `Plugin_Public` est le support des "Ghost Callbacks". Cela signifie que vous pouvez intercepter un callback Pawn même s'il **n'est pas présent** dans le script `.amx` du gamemode ou du filterscript. Le SDK "trompe" le serveur pour qu'il appelle votre hook C++ de toute façon. C'est utile pour les callbacks internes ou pour créer de nouvelles fonctionnalités sans dépendre de la présence d'une `public` dans le script Pawn.

```cpp
// You can define a callback that the Pawn script does not have, but your plugin will hear it.
Plugin_Public(OnMyCustomInternalEvent, int data1, float data2) {
    Samp_SDK::Log("Custom internal event received: %d, %.2f", data1, data2);

    return PLUGIN_PUBLIC_CONTINUE;
}

// To "fire" this event from another point in your C++ code:
// Pawn_Public(OnMyCustomInternalEvent, 123, 45.67f);
// The call will go to your Plugin_Public above, even if there is no OnMyCustomInternalEvent in Pawn.
```

### 3.4. `Plugin_Native`: Création de fonctions natives en C++

`Plugin_Native` vous permet d'étendre la fonctionnalité de Pawn avec du code C++ haute performance.

#### Syntaxe et signature fixe

- `Plugin_Native(NomeDaNativa, AMX* amx, cell* params)`
- La fonction C++ doit avoir exactement cette signature : `cell NomeDaNativa(AMX* amx, cell* params)`.
- `NomeDaNativa` est le nom que les scripts Pawn utiliseront.

```cpp
// Pawn: native GetPlayerPingAverage(playerid);
Plugin_Native(GetPlayerPingAverage, AMX* amx, cell* params) {
    // ... Implementation ...
    return 0;
}
```

#### Enregistrement automatique des natives

> [!NOTE]
> Vous **n'avez pas besoin** d'appeler `amx_Register` manuellement. Le SDK détecte toutes vos `Plugin_Native`s (dans n'importe quel fichier `.cpp` qui a inclus `samp_sdk.hpp` et défini `SAMP_SDK_WANT_AMX_EVENTS`) et les enregistre automatiquement dans chaque script AMX chargé (`OnAmxLoad`).

#### Extraction des paramètres : `Register_Parameters` vs. `Native_Params`

##### `Register_Parameters(...)`

- **Description :** Aide plus simple pour extraire plusieurs paramètres séquentiellement.
- **Utilisation :** `Register_Parameters(variable1, variable2, ...)`
- **Limitations :** Pour les paramètres d'entrée. Ne gère pas les paramètres facultatifs ou l'accès par index.
- **Types pris en charge :** `int`, `float`, `std::string`.

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

##### `Native_Params` (API complète : `Get`, `Get_REF`, `Set_REF`)

- **Description :** Une classe wrapper qui fournit une interface orientée objet pour accéder aux paramètres d'une native. Plus puissante pour les scénarios complexes.
- **Construction :** `Native_Params p(amx, params);`

###### `p.Count()`

- **Description :** Retourne le nombre de paramètres passés à la native.
- **Utilisation :** Essentiel pour gérer les paramètres facultatifs.

###### `p.Get<T>(size_t index)`

- **Description :** Extrait un paramètre d'entrée par index et le convertit au type `T`.
- **Types pris en charge :** `int`, `float`, `std::string`.

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

- **Description :** Obtient la valeur d'un paramètre de **référence** (pointeur Pawn) et la stocke dans `out_value`.
- **Utilisation :** Pour lire des valeurs qui ont été passées par référence depuis Pawn.
- **Retour :** `true` si l'adresse AMX est valide, `false` sinon.

```cpp
// Pawn: native CheckPlayerStats(playerid, &Float:health, &money);
Plugin_Native(CheckPlayerStats, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    
    int playerid = p.Get<int>(0);
    float health = 0.0f;
    int money = 0;

    // Gets the values from the references (Pawn passed addresses)
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

- **Description :** Retourne un `std::optional<T>` pour lire un paramètre de référence. Plus sûr pour C++17 et supérieur.

###### `p.Set_REF<T>(size_t index, T value)`

- **Description :** Écrit une valeur `T` dans un paramètre de **référence** Pawn (l'adresse que Pawn a passée).
- **Utilisation :** Pour modifier des valeurs qui ont été passées par référence, faisant en sorte que Pawn voit la modification.
- **Retour :** `true` si l'écriture a réussi, `false` sinon.

#### Retour de valeurs

- Votre fonction `Plugin_Native` doit retourner un `cell`.
- Pour retourner un `int` ou `bool`, utilisez un cast vers `cell`.
- Pour retourner un `float`, utilisez `amx::AMX_FTOC(mon_float)`.

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

### 3.5. `Plugin_Native_Hook`: Interception des natives SA-MP existantes

La macro `Plugin_Native_Hook` vous permet d'intercepter et de modifier le comportement de toute fonction native SA-MP existante ou d'autres plugins. C'est un mécanisme puissant pour étendre ou modifier la logique standard du serveur.

#### Syntaxe et signature fixe

- `Plugin_Native_Hook(NomDeLaNative, AMX* amx, cell* params)`
- La fonction C++ doit avoir exactement cette signature : `cell NomDeLaNative(AMX* amx, cell* params)`.
- `NomDeLaNative` doit être le nom exact de la native que vous souhaitez hooker (ex : `SendClientMessage`, `SetPlayerPos`).

```cpp
// Intercepts the SendClientMessage native
Plugin_Native_Hook(SendClientMessage, AMX* amx, cell* params) {
    // ...
    return Call_Original_Native(SendClientMessage); // Important to call the original
}
```

#### Enregistrement et activation du hook

> [!NOTE]
> Vous **n'avez pas besoin** d'appeler `amx_Register` manuellement ou de définir `SAMP_SDK_WANT_AMX_EVENTS` spécifiquement pour `Plugin_Native_Hook`. Le SDK détecte et enregistre automatiquement vos hooks. Lors de la première exécution d'un script AMX, le SDK remplace le pointeur de la native dans la table par un "trampoline" qui redirige vers votre fonction `Plugin_Native_Hook`. Ce processus garantit l'enchaînement sécurisé des hooks de plusieurs plugins.

#### Appel de la native originale (chaîne de hooks) : `Call_Original_Native`

Dans votre fonction `Plugin_Native_Hook`, vous **DEVEZ** utiliser la macro `Call_Original_Native(NomDeLaNative)` pour invoquer la fonction originale (ou le hook suivant dans la chaîne). C'est vital pour :
- **Préserver la fonctionnalité :** Si vous n'appelez pas l'original, la native hookée cessera simplement de fonctionner pour les autres plugins ou pour le serveur.
- **Enchaînement des hooks :** Permet à plusieurs plugins de hooker la même native et à tous les hooks d'être exécutés séquentiellement.
- **Manipulation du retour :** Vous pouvez inspecter et même modifier la valeur de retour de `Call_Original_Native` avant de la retourner depuis votre fonction de hook.

```cpp
// Example: Blocking SendClientMessage if it contains a specific word
Plugin_Native_Hook(SendClientMessage, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    
    // Extracts parameters for analysis
    int playerid = p.Get<int>(0);
    // int color = p.Get<int>(1); // We don't need the color for this logic
    std::string message = p.Get_String(2); // Gets the message string

    if (message.find("BADWORD") != std::string::npos) {
        Samp_SDK::Log("MESSAGE BLOCKED for playerid %d: %s", playerid, message.c_str());

        return 0; // Returns 0 (false) to Pawn, indicating the message was not sent.
                  // And most importantly, we do NOT call Call_Original_Native, blocking the message.
    }

    // If the message does not contain the forbidden word, we call the original native
    // and return its value, ensuring the message is sent normally
    // and that other hooks (if any) are executed.
    return Call_Original_Native(SendClientMessage);
}
```

#### Exemple complet de `Plugin_Native_Hook`

```cpp
#define SAMP_SDK_IMPLEMENTATION
// SAMP_SDK_WANT_AMX_EVENTS is not strictly necessary for hooks, but it's common to have OnAmxLoad/Unload
// #define SAMP_SDK_WANT_AMX_EVENTS 
#include "samp-sdk/samp_sdk.hpp"

// Hook for the CreateVehicle native
Plugin_Native_Hook(CreateVehicle, AMX* amx, cell* params) {
    Native_Params p(amx, params);

    // Extracts the parameters of the CreateVehicle native for inspection
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
        params[1] = static_cast<cell>(401); // The model is at position 0 in the parameters array (params[1])
        Samp_SDK::Log("  -> Model 400 changed to 401 before creation.");
    }
    
    // We call the original native (or the next hook in the chain) with the potentially modified parameters
    cell original_retval = Call_Original_Native(CreateVehicle);

    Samp_SDK::Log("HOOK: CreateVehicle returned: %d (Vehicle ID)", (int)original_retval);

    // You can modify the return value here before returning it to Pawn.
    // Example: if vehicle creation failed, return a custom invalid ID.
    if ((int)original_retval == INVALID_VEHICLE_ID) {
        Samp_SDK::Log("  -> Vehicle creation failed in the original native.");

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
> La manipulation directe du tableau `cell* params` pour modifier les paramètres d'entrée nécessite de la prudence. Assurez-vous de comprendre l'ordre et le type des paramètres. Pour la plupart des cas d'utilisation, `p.Get(...)` pour inspecter et `Call_Original_Native(...)` pour continuer la chaîne est suffisant. La modification directe de `params` ne doit être effectuée que si vous savez que le paramètre est une valeur et doit être modifié pour l'appel original. Pour les chaînes et les tableaux, la modification est plus complexe et implique généralement `amx::Set_String` pour écrire à l'adresse existante ou réallouer, ce qui peut être plus facile à gérer en appelant la native via `Pawn_Native` avec les nouvelles valeurs et en retournant `0` de votre hook pour annuler l'appel original.

### 3.6. Macros `Pawn_*`: Appel de fonctions Pawn depuis le C++

Ces macros sont l'inverse de `Plugin_Public` et `Plugin_Native` : elles permettent à votre code C++ d'invoquer des fonctions Pawn.

#### `Pawn_Native(NomDeLaNative, ...)`

- **Objectif :** La manière recommandée d'appeler des fonctions natives SA-MP (ou d'autres plugins) depuis C++.
- **Mécanisme :** Recherche le pointeur de la native dans le cache interne du SDK (rempli par `Amx_Register_Detour`). Si trouvé, exécute la native dans un `Amx_Sandbox` (une instance AMX fausse et isolée).
- **Performance :** La plus efficace, car elle évite la recherche coûteuse des `publics` et interagit directement avec le pointeur de la native.

#### `Pawn_Public(NomDeLaPublic, ...)`

- **Objectif :** Appelle une fonction publique spécifique dans un script Pawn.
- **Mécanisme :** Parcourt les instances `AMX*` gérées par l'`Amx_Manager`, recherche la `public` par son nom et l'exécute.
- **Performance :** Moins efficace que `Pawn_Native` en raison de la recherche et du véritable `amx_Exec`. Généralement, les `publics` sont plus lentes que les `natives`.
- **Utilisation :** Idéal pour invoquer des événements personnalisés dans vos Gamemode/Filterscripts qui ne sont pas des natives.

#### `Pawn(NomDeLaFonction, ...)`

- **Objectif :** Une macro de commodité qui tente de deviner si la fonction est une native ou une publique.
- **Mécanisme :** D'abord, tente d'appeler comme `Pawn_Native`. Si cela échoue (la native n'est pas trouvée), tente d'appeler comme `Pawn_Public`.
- **Performance :** Peut être légèrement plus lente que `Pawn_Native` si la fonction est native, en raison de la double tentative de recherche. Pour les `publics`, les performances sont les mêmes que `Pawn_Public`.
- **Utilisation :** Pour les fonctions dont vous n'êtes pas sûr qu'elles soient natives ou publiques, ou pour éviter la répétition de code en essayant l'une puis l'autre.

#### Syntaxe et conventions

- **Nom de la fonction :** Utilisez toujours le nom de la fonction Pawn **directement, sans guillemets**. Le SDK le convertira en chaîne de caractères en interne.
- **Paramètres :** Passez les paramètres C++ directement.

```cpp
// Correct:
Pawn_Native(SetPlayerPos, playerid, 100.0f, 200.0f, 300.0f); 

// Incorrect (but would technically work due to hashing, avoid):
Pawn_Native("SetPlayerPos", playerid, 100.0f, 200.0f, 300.0f); 
```

#### Marshalling des paramètres d'entrée

Le SDK convertit vos types C++ au format `cell` de l'AMX, gérant la mémoire selon les besoins :
- `int`, `bool`, `long`, `enum` -> `cell`
- `float`, `double` -> `cell` (en utilisant `amx::AMX_FTOC`)
- `const char*`, `std::string`, `std::string_view` (C++17+) -> `cell` (alloue de la mémoire dans l'AMX, copie la chaîne et passe l'adresse `amx_addr`)

```cpp
void Send_Formatted_Message(int playerid, const std::string& msg) {
    Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, msg);
}
```

#### Marshalling des paramètres de sortie (références : `int&`, `float&`, `std::string&`)

Ceci est une fonctionnalité clé pour la commodité et la sécurité. Pour les fonctions Pawn qui attendent un pointeur (référence), le SDK automatise tout le processus d'allocation/désallocation de mémoire et de copie des données.

- **Comment utiliser :** Il suffit de passer votre variable par référence (`&`).
- **Mécanisme :** Le SDK alloue de la mémoire sur le tas de l'AMX, passe l'adresse AMX à la fonction Pawn, attend que la fonction Pawn remplisse cette adresse, relit la valeur et libère la mémoire de l'AMX. Tout cela de manière transparente.
- **Avec `std::string&` :** Le SDK alloue un buffer standard (256 cellules) dans l'AMX pour la chaîne.

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

#### L'objet `Callback_Result`: Analyse complète

Tous les appels `Pawn_*` renvoient un objet `Callback_Result`. Cet objet est un wrapper sécurisé pour le résultat de l'appel Pawn.

- `Callback_Result() noexcept` : Constructeur par défaut, indique l'échec (`success_ = false`).
- `Callback_Result(bool success, cell value) noexcept` : Constructeur pour succès ou échec avec valeur.
- `explicit operator bool() const` : Permet d'utiliser `if (result)` pour vérifier si l'appel a réussi.
- `operator cell() const` : Permet de convertir le résultat en `cell` pour obtenir la valeur.
- `float As_Float() const` : Commodité pour obtenir le résultat sous forme de `float`.
- `cell Value() const` : Retourne la valeur brute `cell`.
- `bool Success() const` : Retourne `true` si l'appel Pawn a réussi.
- `int Get_Amx_Error() const` : Retourne le code d'erreur de l'AMX si l'appel a échoué (0 pour succès).

```cpp
// Example: Getting a player's health.
// The native GetPlayerHealth(playerid, &Float:health) expects a playerid and a reference to the health.
int playerid = 0; // Example player ID
float player_health = 0.0f;

// We call GetPlayerHealth, passing playerid and player_health by reference.
// The SDK will handle marshalling for the 'health' output parameter.
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

### 3.7. `Plugin_Module`: Gestion des modules dynamiques

La macro `Plugin_Module` permet à votre plugin d'agir comme un "chargeur" pour d'autres plugins, créant une architecture modulaire et extensible. Un module chargé de cette manière est traité comme un plugin de première classe, avec son propre cycle de vie d'événements géré par le plugin hôte.

#### Syntaxe et objectif

- `Plugin_Module(const char* nom_du_fichier_de_base, const char* repertoire_du_module, const char* message_de_succes_optionnel)`
- `nom_du_fichier_de_base` : Le nom *de base* du fichier du module, **sans l'extension** (ex : pour `my_module.dll` ou `my_module.so`, utilisez `"my_module"`). Le SDK ajoutera automatiquement l'extension `.dll` ou `.so` appropriée.
- `repertoire_du_module` : Le chemin du répertoire où se trouve le fichier du module (ex : `"plugins/my_custom_modules"`). **N'incluez pas le nom du fichier ici.** Le SDK concaténera le chemin complet (`repertoire_du_module/nom_du_fichier_de_base.ext`).
- `message_de_succes_optionnel` : Un message facultatif à afficher dans la console du serveur si le module se charge avec succès.

```cpp
// main.cpp, inside OnLoad()

// Loads the 'core_logic.dll' (or 'core_logic.so') module
// located in the server's 'modules/custom/' folder.
if (!Plugin_Module("core_logic", "modules/custom", "Core Logic Module loaded successfully!"))
    return (Samp_SDK::Log("FATAL ERROR: Failed to load 'core_logic' module!"), false);

// Loads the 'admin_system.dll' (or 'admin_system.so') module
// located directly in the server's 'plugins/' folder.
if (!Plugin_Module("admin_system", "plugins", "Administration Module activated."))
    Samp_SDK::Log("WARNING: Administration Module could not be loaded.");
```

#### Cycle de vie d'un module

Un module doit exporter les fonctions `Load`, `Unload` et `Supports`, tout comme un plugin normal. Le SDK gère le cycle de vie du module comme suit :

- **Chargement :** Lorsque `Plugin_Module` est appelé, le SDK :
   1. Construit le chemin complet du fichier (ex : `modules/custom/core_logic.dll`).
   2. Utilise `Dynamic_Library` (`LoadLibrary`/`dlopen`) pour charger le binaire.
   3. **Obtient les pointeurs de TOUTES les fonctions de cycle de vie du module :**
      - **Obligatoires :** `Load`, `Unload`, `Supports`. Si l'une d'elles manque, le chargement du module échoue.
      - **Optionnelles :** `AmxLoad`, `AmxUnload`, `ProcessTick`.
   4. Appelle la fonction `Load` du module, en passant `ppData` du plugin principal.
   5. Si `Load` retourne `true`, le module est ajouté à la liste interne des modules chargés.

- **Transfert d'événements :** Le plugin hôte **transfère automatiquement** les événements à tous les modules chargés.
 > [!IMPORTANT]
 > Pour que les événements soient transférés correctement, le **plugin hôte** (celui qui appelle `Plugin_Module`) doit être configuré pour recevoir ces événements.
 > - Pour que `AmxLoad` et `AmxUnload` fonctionnent dans les modules, le plugin hôte doit définir la macro `SAMP_SDK_WANT_AMX_EVENTS`.
 > - Pour que `ProcessTick` fonctionne dans les modules, le plugin hôte doit définir la macro `SAMP_SDK_WANT_PROCESS_TICK`.

- **Déchargement :** Lors du `OnUnload` de votre plugin principal, le SDK décharge tous les modules qui ont été chargés via `Plugin_Module`. Cela se fait dans l'**ordre inverse** du chargement (le dernier chargé est le premier déchargé), ce qui est crucial pour gérer les dépendances et garantir la libération correcte des ressources.

#### Avantages de la modularisation

- **Organisation du code :** Divisez les gros plugins en composants plus petits et gérables, chacun dans son propre fichier de module.
- **Réutilisabilité :** Créez des modules génériques (ex : un module de base de données, un module de système de journalisation avancé) qui peuvent être utilisés par différents plugins, favorisant la réutilisation du code.
- **Composants indépendants :** Créez des modules qui sont **totalement orientés événements et indépendants**. Un module peut avoir ses propres `Plugin_Native`s, intercepter des `Plugin_Public`s et avoir sa propre logique `OnProcessTick`, fonctionnant comme un plugin autonome, mais chargé par un hôte.
- **Mises à jour dynamiques :** Dans des scénarios contrôlés, permet la mise à jour de parties de votre système (en remplaçant un `.dll` ou un `.so` de module) sans avoir besoin de recompiler et de redémarrer le plugin principal ou l'ensemble du serveur (bien que cela nécessite une gestion rigoureuse des versions et de la compatibilité).

### 3.8. `Plugin_Call`: Appel des natives internes du plugin

Utilisez `Plugin_Call` pour invoquer une `Plugin_Native` définie **au sein de votre propre plugin**.

#### Syntaxe et avantages en termes de performances

- `Plugin_Call(NomeDaNativa, Param1, Param2, ...)`
- **Avantage :** Évite la surcharge de la recherche de la native dans le tableau des natives de l'AMX. Le SDK maintient une carte directe des hachages de noms vers les pointeurs de fonction pour ses propres natives, ce qui en fait le moyen le plus rapide de les appeler en interne.
- **Requis :** `SAMP_SDK_WANT_AMX_EVENTS`.

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
            if (Plugin_Call(InternalCheckPlayerLevel, i)) // Calls its own native
                Samp_SDK::Log("Player %d is at a high level!", i);
        }
    }
}
```

### 3.9. Fonctions utilitaires du SDK

#### `Samp_SDK::Log(const char* format, ...)`

- **Description :** Imprime des messages sur la console du serveur et dans le fichier `server_log.txt`. Un wrapper sécurisé pour `logprintf`.
- **Utilisation :** Pour le débogage, les messages d'état et les erreurs.
- **Mécanisme :** En interne, le SDK obtient le pointeur de `logprintf` via `ppData[PLUGIN_DATA_LOGPRINTF]`. La fonction gère le formatage de la chaîne de manière sécurisée.

```cpp
// Anywhere in your plugin
Samp_SDK::Log("The plugin was initialized with a value %d and a string '%s'.", 123, "test");
```

#### `std::string Plugin_Format(const char* format, ...)` (recommandé)

- **Description :** Formate une chaîne de caractères de manière sécurisée (similaire à `sprintf`) et renvoie un `std::string`. C'est le moyen **recommandé et le plus idiomatique** de formater des chaînes de caractères pour une utilisation dans votre plugin.
- **Utilisation :** Idéal pour construire des messages formatés avant de les passer à `Samp_SDK::Log`, `Pawn_Native(SendClientMessage, ...)`, ou pour tout autre besoin de chaîne de caractères dans votre code C++.
- **Mécanisme :** En interne, `Plugin_Format` est une macro qui appelle `Samp_SDK::Format`. Il utilise `vsnprintf` pour déterminer la taille exacte de la chaîne formatée et alloue un `std::string` avec une capacité suffisante, évitant les débordements de tampon.

```cpp
int playerid = 0; // Example ID
int health = 50;
Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, Plugin_Format("Player %d, your current health is %d.", playerid, health));

// Can also be used for internal logs
Samp_SDK::Log(Plugin_Format("DEBUG: Processing status for ID %d", playerid));
```

#### `std::string Samp_SDK::Format(const char* format, ...)` (détail d'implémentation)

- **Description :** La fonction d'implémentation sous-jacente pour le formatage des chaînes, située dans le namespace `Samp_SDK`.
- **Utilisation :** Généralement non appelée directement par l'utilisateur. La macro `Plugin_Format` est fournie comme une commodité pour cette fonction, s'alignant sur la convention de nommage des autres macros du SDK (`Plugin_Public`, `Plugin_Native`). Vous ne l'appelleriez directement que si vous vouliez éviter la macro `Plugin_Format` pour une raison spécifique.

```cpp
// Example of how Samp_SDK::Format works, but prefer Plugin_Format
std::string raw_status = Samp_SDK::Format("For internal use only: %d.", 42);
```

#### `std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`

- **Description :** Convertit une adresse de chaîne de l'AMX (`cell amx_addr`) en un `std::string` C++.
- **Utilisation :** Principalement à l'intérieur de `Plugin_Native` et `Plugin_Native_Hook` lorsque vous devez accéder à des chaînes qui ne sont pas automatiquement converties par `Register_Parameters` ou `Native_Params` (par exemple, si le paramètre Pawn est une `const` `string` et n'a pas été déclaré comme `std::string` dans votre `Plugin_Native` ou `Plugin_Public` pour le marshalling automatique).

```cpp
Plugin_Native(PrintRawAmxString, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    cell amx_string_addr = p.Get<cell>(0); // Gets the string address in AMX

    std::string cpp_string = Samp_SDK::Get_String(amx, amx_string_addr);
    Samp_SDK::Log("String from AMX: %s", cpp_string.c_str());

    return 1;
}
```

## 4. Compilation et déploiement

### Exigences d'architecture et de plateforme

- Votre plugin **DOIT** être compilé pour l'architecture **x86 (32 bits)**.
- Plateformes prises en charge : Windows (.dll) et Linux (.so).

### Exemples de commandes de compilation

#### **MSVC (Visual Studio)**

1. Créez un nouveau projet de "Dynamic-Link Library (DLL)".
2. Dans les paramètres du projet, définissez la "Plateforme de solution" sur **x86**.
3. Assurez-vous que le standard de langage C++ est au moins C++17.

#### **GCC / Clang (Linux)**

```bash
# For a plugin named 'my_plugin.so' from 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -fPIC -Wall -Wextra -Wl,--no-undefined main.cpp -o my_plugin.so
```
- `-m32` : Compile pour 32 bits.
- `-shared` : Crée une bibliothèque partagée (`.so`).
- `-std=c++17` : Définit la norme C++ comme C++17 (peut être `c++20`, mais C++17 est le minimum).
- `-O2` : Niveau d'optimisation 2.
- `-fPIC` : Génère du code indépendant de la position, nécessaire pour les bibliothèques partagées.
- `-Wall -Wextra` : Active des avertissements supplémentaires pour aider à détecter les erreurs.
- `-Wl,--no-undefined` : Empêche la création de la bibliothèque s'il y a des symboles non définis.

#### **GCC / Clang (MinGW sur Windows)**

```bash
# For a plugin named 'my_plugin.dll' from 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -static-libstdc++ -static-libgcc -Wl,--no-undefined main.cpp -o my_plugin.dll
```
- `-static-libstdc++` : Lie la bibliothèque standard C++ statiquement. Essentiel pour éviter que votre plugin ne dépende de DLLs d'exécution spécifiques au compilateur qui pourraient ne pas être présentes sur le système de l'utilisateur.
- `-static-libgcc` : Lie la bibliothèque GCC statiquement.

### Considérations pour la distribution

- **Nom du fichier :** Votre plugin doit avoir l'extension `.dll` (Windows) ou `.so` (Linux). Ex : `my_plugin.dll`.
- **Emplacement :** Placez le fichier compilé dans le dossier `plugins/` de votre serveur SA-MP.
- **server.cfg :** Ajoutez le nom de votre plugin (si Windows, sans l'extension) à la ligne `plugins` dans le `server.cfg`.
   ```
   plugins my_plugin (if Linux, my_plugin.so)
   ```

## Licence

Copyright © **AlderGrounds**

Ce logiciel est sous licence selon les termes de la Licence MIT ("Licence"); vous pouvez utiliser ce logiciel conformément aux conditions de la Licence. Une copie de la Licence peut être obtenue à: [MIT License](https://opensource.org/licenses/MIT)

### Conditions Générales d'Utilisation

#### 1. Autorisations Accordées

La présente licence accorde gratuitement à toute personne obtenant une copie de ce logiciel et des fichiers de documentation associés les droits suivants:
* Utiliser, copier, modifier, fusionner, publier, distribuer, sous-licencier et/ou vendre des copies du logiciel sans restriction
* Permettre aux personnes à qui le logiciel est fourni de faire de même, sous réserve des conditions suivantes

#### 2. Conditions Obligatoires

Toutes les copies ou parties substantielles du logiciel doivent inclure:
* L'avis de droit d'auteur ci-dessus
* Cet avis d'autorisation
* L'avis de non-responsabilité ci-dessous

#### 3. Droits d'Auteur

Le logiciel et toute la documentation associée sont protégés par les lois sur le droit d'auteur. La **AlderGrounds** conserve la propriété des droits d'auteur originaux du logiciel.

#### 4. Exclusion de Garantie et Limitation de Responsabilité

LE LOGICIEL EST FOURNI "TEL QUEL", SANS GARANTIE D'AUCUNE SORTE, EXPRESSE OU IMPLICITE, Y COMPRIS MAIS NON LIMITÉ AUX GARANTIES DE COMMERCIALISATION, D'ADÉQUATION À UN USAGE PARTICULIER ET DE NON-VIOLATION.

EN AUCUN CAS LES AUTEURS OU LES DÉTENTEURS DES DROITS D'AUTEUR NE SERONT RESPONSABLES DE TOUTE RÉCLAMATION, DOMMAGE OU AUTRE RESPONSABILITÉ, QUE CE SOIT DANS UNE ACTION DE CONTRAT, UN DÉLIT OU AUTRE, DÉCOULANT DE, HORS DE OU EN RELATION AVEC LE LOGICIEL OU L'UTILISATION OU D'AUTRES TRANSACTIONS DANS LE LOGICIEL.

---

Pour des informations détaillées sur la Licence MIT, consultez: https://opensource.org/licenses/MIT