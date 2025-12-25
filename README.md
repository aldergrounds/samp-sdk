# SA-MP SDK

<div align="center">

![C++](https://img.shields.io/badge/C%2B%2B-17%2B-00599C?style=for-the-badge&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-blue?style=for-the-badge&logo=windows&logoColor=white)
![Architecture](https://img.shields.io/badge/Architecture-x86%20(32--bit)-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**Um SDK C++ moderno, header-only e de alto nível para o desenvolvimento de plugins e módulos para SA-MP.**

</div>

## Idiomas

- Deutsch: [README](translations/Deutsch/README.md)
- English: [README](translations/English/README.md)
- Español: [README](translations/Espanol/README.md)
- Français: [README](translations/Francais/README.md)
- Italiano: [README](translations/Italiano/README.md)
- Polski: [README](translations/Polski/README.md)
- Русский: [README](translations/Русский/README.md)
- Svenska: [README](translations/Svenska/README.md)
- Türkçe: [README](translations/Turkce/README.md)

## Índice

- [SA-MP SDK](#sa-mp-sdk)
  - [Idiomas](#idiomas)
  - [Índice](#índice)
  - [1. Introdução e Filosofia de Design](#1-introdução-e-filosofia-de-design)
    - [O Problema com a API C Padrão do SA-MP](#o-problema-com-a-api-c-padrão-do-sa-mp)
    - [A Solução do SA-MP SDK: Abstração com Segurança e Performance](#a-solução-do-sa-mp-sdk-abstração-com-segurança-e-performance)
    - [Modelo Header-Only: Vantagens e Implicações](#modelo-header-only-vantagens-e-implicações)
  - [2. Configuração e Ambiente](#2-configuração-e-ambiente)
    - [Requisitos de Compilação](#requisitos-de-compilação)
    - [Estrutura de Arquivos Recomendada](#estrutura-de-arquivos-recomendada)
    - [Macros Essenciais de Configuração](#macros-essenciais-de-configuração)
      - [`SAMP_SDK_IMPLEMENTATION`](#samp_sdk_implementation)
      - [`SAMP_SDK_WANT_AMX_EVENTS`](#samp_sdk_want_amx_events)
      - [`SAMP_SDK_WANT_PROCESS_TICK`](#samp_sdk_want_process_tick)
    - [Definições e Constantes do SA-MP (`samp_defs.hpp`)](#definições-e-constantes-do-sa-mp-samp_defshpp)
  - [3. Guia de Uso Abrangente da API](#3-guia-de-uso-abrangente-da-api)
    - [3.1. O Ciclo de Vida do Plugin](#31-o-ciclo-de-vida-do-plugin)
      - [`bool OnLoad()`](#bool-onload)
      - [`void OnUnload()`](#void-onunload)
      - [`unsigned int GetSupportFlags()`](#unsigned-int-getsupportflags)
      - [`void OnAmxLoad(AMX* amx)`](#void-onamxloadamx-amx)
      - [`void OnAmxUnload(AMX* amx)`](#void-onamxunloadamx-amx)
      - [`void OnProcessTick()`](#void-onprocesstick)
    - [3.2. Exportando Funções do Plugin](#32-exportando-funções-do-plugin)
      - [Exportação para MSVC (Visual Studio) com `Export_Plugin`](#exportação-para-msvc-visual-studio-com-export_plugin)
      - [Exportação para GCC / Clang com `SAMP_SDK_EXPORT`](#exportação-para-gcc--clang-com-samp_sdk_export)
    - [3.3. `Plugin_Public`: Interceptando Eventos do Pawn](#33-plugin_public-interceptando-eventos-do-pawn)
      - [Sintaxe e Declaração](#sintaxe-e-declaração)
      - [Marshalling Automático de Parâmetros](#marshalling-automático-de-parâmetros)
      - [Controle de Fluxo: `PLUGIN_PUBLIC_CONTINUE` vs `PLUGIN_PUBLIC_STOP`](#controle-de-fluxo-plugin_public_continue-vs-plugin_public_stop)
      - [Ghost Callbacks](#ghost-callbacks)
    - [3.4. `Plugin_Native`: Criando Funções Nativas em C++](#34-plugin_native-criando-funções-nativas-em-c)
      - [Sintaxe e Assinatura Fixa](#sintaxe-e-assinatura-fixa)
      - [Registro Automático de Nativas](#registro-automático-de-nativas)
      - [Extração de Parâmetros: `Register_Parameters` vs. `Native_Params`](#extração-de-parâmetros-register_parameters-vs-native_params)
        - [`Register_Parameters(...)`](#register_parameters)
        - [`Native_Params` (API Completa: `Get`, `Get_REF`, `Set_REF`)](#native_params-api-completa-get-get_ref-set_ref)
          - [`p.Count()`](#pcount)
          - [`p.Get<T>(size_t index)`](#pgettsize_t-index)
          - [`p.Get_REF<T>(size_t index, T& out_value)`](#pget_reftsize_t-index-t-out_value)
          - [`p.Get_REF<T>(size_t index)` (C++17+)](#pget_reftsize_t-index-c17)
          - [`p.Set_REF<T>(size_t index, T value)`](#pset_reftsize_t-index-t-value)
      - [Retorno de Valores](#retorno-de-valores)
    - [3.5. `Plugin_Native_Hook`: Interceptando Nativas Existentes do SA-MP](#35-plugin_native_hook-interceptando-nativas-existentes-do-sa-mp)
      - [Sintaxe e Assinatura Fixa](#sintaxe-e-assinatura-fixa-1)
      - [Registro e Ativação do Hook](#registro-e-ativação-do-hook)
      - [Chamando a Native Original (Cadeia de Hooks): `Call_Original_Native`](#chamando-a-native-original-cadeia-de-hooks-call_original_native)
      - [Exemplo Completo de `Plugin_Native_Hook`](#exemplo-completo-de-plugin_native_hook)
    - [3.6. `Pawn_*` Macros: Chamando Funções do Pawn a Partir do C++](#36-pawn_-macros-chamando-funções-do-pawn-a-partir-do-c)
      - [`Pawn_Native(NomeDaNativa, ...)`](#pawn_nativenomedanativa-)
      - [`Pawn_Public(NomeDaPublic, ...)`](#pawn_publicnomedapublic-)
      - [`Pawn(NomeDaFuncao, ...)`](#pawnnomedafuncao-)
      - [Sintaxe e Convenções](#sintaxe-e-convenções)
      - [Marshalling de Parâmetros de Entrada](#marshalling-de-parâmetros-de-entrada)
      - [Marshalling de Parâmetros de Saída (Referências: `int&`, `float&`, `std::string&`)](#marshalling-de-parâmetros-de-saída-referências-int-float-stdstring)
      - [O Objeto `Callback_Result`: Análise Completa](#o-objeto-callback_result-análise-completa)
    - [3.7. `Plugin_Module`: Gerenciamento de Módulos Dinâmicos](#37-plugin_module-gerenciamento-de-módulos-dinâmicos)
      - [Sintaxe e Propósito](#sintaxe-e-propósito)
      - [Ciclo de Vida de um Módulo](#ciclo-de-vida-de-um-módulo)
      - [Benefícios da Modularização](#benefícios-da-modularização)
    - [3.8. `Plugin_Call`: Chamando Nativas Internas do Plugin](#38-plugin_call-chamando-nativas-internas-do-plugin)
      - [Sintaxe e Vantagens de Performance](#sintaxe-e-vantagens-de-performance)
    - [3.9. Funções Utilitárias do SDK](#39-funções-utilitárias-do-sdk)
      - [`Samp_SDK::Log(const char* format, ...)`](#samp_sdklogconst-char-format-)
      - [`std::string Plugin_Format(const char* format, ...)` (Recomendado)](#stdstring-plugin_formatconst-char-format--recomendado)
      - [`std::string Samp_SDK::Format(const char* format, ...)` (Detalhe de Implementação)](#stdstring-samp_sdkformatconst-char-format--detalhe-de-implementação)
      - [`std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`](#stdstring-samp_sdkget_stringamx-amx-cell-amx_addr)
  - [4. Compilação e Deploy](#4-compilação-e-deploy)
    - [Requisitos de Arquitetura e Plataforma](#requisitos-de-arquitetura-e-plataforma)
    - [Exemplos de Comandos de Compilação](#exemplos-de-comandos-de-compilação)
      - [**MSVC (Visual Studio)**](#msvc-visual-studio)
      - [**GCC / Clang (Linux)**](#gcc--clang-linux)
      - [**GCC / Clang (MinGW no Windows)**](#gcc--clang-mingw-no-windows)
    - [Considerações para Distribuição](#considerações-para-distribuição)
  - [Licença](#licença)
    - [Termos e Condições de Uso](#termos-e-condições-de-uso)
      - [1. Permissões Concedidas](#1-permissões-concedidas)
      - [2. Condições Obrigatórias](#2-condições-obrigatórias)
      - [3. Direitos Autorais](#3-direitos-autorais)
      - [4. Isenção de Garantias e Limitação de Responsabilidade](#4-isenção-de-garantias-e-limitação-de-responsabilidade)

## 1. Introdução e Filosofia de Design

### O Problema com a API C Padrão do SA-MP

A API de plugins do SA-MP é uma interface de programação em C. Embora funcional e fundamental, ela apresenta os desafios inerentes à programação de baixo nível:
- **Gerenciamento Manual de Memória:** Funções como `amx_Allot` e `amx_Release` exigem que o desenvolvedor aloque e desaloque explicitamente a memória na heap da AMX. Isso é uma fonte comum de vazamentos de memória e falhas de runtime.
- **Tipagem Fraca e Conversões Manuais:** Parâmetros são passados como um array de `cell`s, forçando conversões explícitas (e muitas vezes inseguras) entre `cell`, `int`, `float`, e `char*`.
- **Verbosidade e Boilerplate:** Extrair múltiplos parâmetros de um array `cell* params`, lidar com tamanhos de strings, e gerenciar a stack da AMX para chamadas de retorno C++ para Pawn exige código repetitivo.
- **Fragilidade da Interface:** A falta de verificação em tempo de compilação (type safety) significa que erros na passagem de parâmetros ou tipos podem passar despercebidos até a execução, causando crashes ou comportamentos indefinidos.

### A Solução do SA-MP SDK: Abstração com Segurança e Performance

O SA-MP SDK aborda esses problemas fornecendo uma poderosa camada de abstração em C++:
- **RAII (Resource Acquisition Is Initialization):** Gerenciamento automático de memória na AMX. `Amx_Scoped_Memory` garante que a memória alocada seja liberada.
- **Segurança de Tipos:** Conversão automática e segura de parâmetros entre C++ e Pawn. Você lida com `int`, `float`, `std::string` diretamente.
- **Sintaxe Concisa e Idiomática:** Macros e templates fornecem uma API limpa que se assemelha mais ao C++ moderno do que à API C tradicional.
- **Interceptação Robusta:** Um motor de hooking avançado permite a interceptação transparente de callbacks do Pawn (`Plugin_Public`), a criação de novas nativas (`Plugin_Native`), e **o hooking e encadeamento de funções nativas existentes do SA-MP (`Plugin_Native_Hook`)**.
- **Alta Performance:** Uso extensivo de hashing em tempo de compilação (FNV1a), caching de funções e otimizações de `thread_local` para minimizar o overhead das abstrações.

### Modelo Header-Only: Vantagens e Implicações

O SDK é composto exclusivamente por arquivos de cabeçalho (`.hpp`, `.h`).
- **Vantagens:**
   - **Integração Simplificada:** Não há bibliotecas para construir, vincular ou distribuir. Basta incluir os headers.
   - **Otimizações do Compilador:** O compilador tem visibilidade completa do código do SDK e do seu plugin, permitindo inlining agressivo e otimizações de tempo de linkagem, o que pode resultar em binários mais rápidos.
- **Implicações:**
   - **Tempo de Compilação:** Para projetos muito grandes, a compilação pode levar mais tempo devido à inclusão repetida do código do SDK. Isso é mitigado por guards de inclusão e pela natureza de "incluir apenas o que é necessário" do C++.
   - **Macros de Implementação:** A necessidade da macro `SAMP_SDK_IMPLEMENTATION` é uma consequência do modelo header-only para evitar redefinições de símbolos.

## 2. Configuração e Ambiente

### Requisitos de Compilação

- **Compilador C++:** Compatível com C++17 ou superior.
   - GCC (versão 8+)
   - Clang (versão 5+)
   - MSVC (Visual Studio 2017+)
- **Arquitetura:** **x86 (32-bit)**. O SA-MP opera exclusivamente nesta arquitetura. O SDK inclui verificações em `platform.hpp` que emitirão erros de compilação se a arquitetura incorreta for detectada.
- **Sistema Operacional:** Windows ou Linux.

### Estrutura de Arquivos Recomendada

Para clareza e organização, é comum organizar o SDK em uma subpasta `samp-sdk`.

```
meu_plugin/
├── samp-sdk/
│   ├── // Outros arquivos do SDK
│   └── samp_sdk.hpp // O principal header a ser incluído
│
├── src/
│   ├── main.cpp // Onde SAMP_SDK_IMPLEMENTATION é definido
│   └── my_custom_logic.cpp // Opcional, para organizar código
│
└── CMakeLists.txt (ou .vcxproj, Makefile)
```

### Macros Essenciais de Configuração

Sempre defina estas macros *antes* de incluir `samp_sdk.hpp`.

#### `SAMP_SDK_IMPLEMENTATION`

- **Propósito:** Sinaliza ao compilador que este arquivo `.cpp` deve gerar as implementações das funções de exportação do plugin (`Supports`, `Load`, `Unload`, `AmxLoad`, `AmxUnload`, `ProcessTick`). **O SDK cuida da exportação dessas funções automaticamente, eliminando a necessidade de arquivos `.def` (no Windows) ou declarações `__attribute__((visibility("default")))` (no Linux) para estas funções.**
- **Impacto Técnico:** Sem esta macro, o linker não encontrará as exportações necessárias, e o servidor SA-MP não conseguirá carregar seu plugin.
- **Regra Fundamental:** **Defina esta macro em APENAS UM arquivo `.cpp` em todo o seu projeto.** Definí-la em mais de um arquivo causará um erro de linkagem de "símbolo duplicado".

```cpp
// main.cpp
#define SAMP_SDK_IMPLEMENTATION // A macro faz o SDK exportar as funções necessárias automaticamente.
#include "samp-sdk/samp_sdk.hpp"

// ... seu código de plugin ...
```

#### `SAMP_SDK_WANT_AMX_EVENTS`

- **Propósito:** Habilita os callbacks de ciclo de vida do script Pawn (`OnAmxLoad`, `OnAmxUnload`) e a funcionalidade de criar novas nativas em C++ (`Plugin_Native`).
- **Funcionalidades Ativadas:**
   - Callbacks `OnAmxLoad(AMX* amx)` e `OnAmxUnload(AMX* amx)`.
   - Declaração e registro de novas nativas C++ usando `Plugin_Native`.
   - A macro `Plugin_Call` para invocar nativas criadas com `Plugin_Native` dentro do seu próprio plugin.
- **Impacto Técnico:** Quando esta macro é definida, o SDK coleta automaticamente todas as suas `Plugin_Native`s. Na função `Supports()`, a flag `SUPPORTS_AMX_NATIVES` é automaticamente adicionada se houver qualquer `Plugin_Native` no seu projeto.
- **Flexibilidade:** **Você pode definir esta macro em múltiplos arquivos `.cpp`**. O sistema de registro estático do SDK consolidará todas as nativas de diferentes unidades de compilação em uma única lista global.

```cpp
// my_natives.cpp (pode ser um arquivo separado do main.cpp)
#define SAMP_SDK_WANT_AMX_EVENTS // Apenas para habilitar Plugin_Native e os callbacks OnAmxLoad/OnAmxUnload
#include "samp-sdk/samp_sdk.hpp"

Plugin_Native(MyCustomNative, AMX* amx, cell* params) {
    // ...
    return 0;
}
```

#### `SAMP_SDK_WANT_PROCESS_TICK`

- **Propósito:** Habilita o callback `OnProcessTick()`, que é invocado regularmente pelo servidor.
- **Impacto Técnico:** Adiciona automaticamente a flag `SUPPORTS_PROCESS_TICK` na função `Supports()`.

```cpp
// main.cpp
#define SAMP_SDK_IMPLEMENTATION
#define SAMP_SDK_WANT_PROCESS_TICK
#include "samp-sdk/samp_sdk.hpp"

void OnProcessTick() {
    // Lógica executada a cada "tick" do servidor (ex: 20ms)
    // Cuidado com operações pesadas aqui!
}
```

### Definições e Constantes do SA-MP (`samp_defs.hpp`)

Este arquivo fornece todas as constantes e limites conhecidos do SA-MP, como `MAX_PLAYERS`, `INVALID_PLAYER_ID`, `PLAYER_STATE_ONFOOT`, `WEAPON_DEAGLE`, `DIALOG_STYLE_LIST`, etc. É automaticamente incluído por `samp_sdk.hpp` e deve ser usado para garantir a compatibilidade e legibilidade do código.

## 3. Guia de Uso Abrangente da API

### 3.1. O Ciclo de Vida do Plugin

As seguintes funções são os pontos de entrada e saída do seu plugin, exportadas automaticamente pelo SDK.

#### `bool OnLoad()`

- **Descrição:** Primeira função chamada pelo servidor SA-MP após o carregamento bem-sucedido do seu plugin na memória.
- **Uso:** Ideal para inicializar qualquer sistema, carregar configurações, abrir conexões com banco de dados, ou carregar módulos (`Plugin_Module`).
- **Retorno:**
   - `true`: O plugin foi inicializado com sucesso e o carregamento continua.
   - `false`: O plugin falhou ao inicializar. O carregamento será abortado e o plugin será descarregado.

```cpp
// main.cpp
bool OnLoad() {
    Samp_SDK::Log("Inicializando MeuPlugin v1.0...");

    // Exemplo: Carregar um módulo (mais detalhes na seção 3.6)
    if (!Plugin_Module("my_database_module", "plugins/db_connector", "Módulo de Banco de Dados carregado.")) {
        Samp_SDK::Log("ERRO: Falha ao carregar o módulo de banco de dados!");

        return false; // Aborta o carregamento do plugin principal
    }

    return true;
}
```

#### `void OnUnload()`

- **Descrição:** Última função chamada pelo servidor SA-MP antes de descarregar seu plugin da memória.
- **Uso:** Ideal para limpar recursos, fechar conexões, salvar estados, e garantir que nenhum recurso seja vazado. O SDK gerencia o descarregamento de módulos (`Plugin_Module`) automaticamente.

```cpp
// main.cpp
void OnUnload() {
    Samp_SDK::Log("MeuPlugin descarregado. Liberando recursos...");
    // Nenhuma ação manual é necessária para módulos carregados via Plugin_Module;
    // o SDK cuida disso.
}
```

#### `unsigned int GetSupportFlags()`

- **Descrição:** Informa ao servidor SA-MP quais recursos seu plugin suporta e deseja usar.
- **Uso:** **Sempre retorne `SUPPORTS_VERSION` (ou `SAMP_PLUGIN_VERSION`).** As flags `SUPPORTS_AMX_NATIVES` e `SUPPORTS_PROCESS_TICK` são adicionadas automaticamente pelo SDK se houver `Plugin_Native`s, e/ou se a macro `SAMP_SDK_WANT_PROCESS_TICK` for definida, respectivamente. Isso simplifica a manutenção e evita erros.

```cpp
// main.cpp
unsigned int GetSupportFlags() {
    return SUPPORTS_VERSION; // O SDK adiciona as flags necessárias automaticamente.
}
```

#### `void OnAmxLoad(AMX* amx)`

- **Requer:** `SAMP_SDK_WANT_AMX_EVENTS`
- **Descrição:** Chamada sempre que um novo script Pawn (um Gamemode ou Filterscript) é carregado e inicializado no servidor.
- **Uso:** Se você precisar de lógica específica para cada script AMX, ou inicializar dados específicos por script.

```cpp
// main.cpp (com SAMP_SDK_WANT_AMX_EVENTS definido)
void OnAmxLoad(AMX* amx) {
    // amx representa a nova instância do script carregado.
    Samp_SDK::Log("Script AMX carregado: %p", (void*)amx);
}
```

#### `void OnAmxUnload(AMX* amx)`

- **Requer:** `SAMP_SDK_WANT_AMX_EVENTS`
- **Descrição:** Chamada quando um script Pawn é descarregado do servidor.
- **Uso:** Para limpar quaisquer recursos específicos que você alocou ou associou àquele `AMX*` em particular.

```cpp
// main.cpp (com SAMP_SDK_WANT_AMX_EVENTS definido)
void OnAmxUnload(AMX* amx) {
    Samp_SDK::Log("Script AMX descarregado: %p", (void*)amx);
}
```

#### `void OnProcessTick()`

- **Requer:** `SAMP_SDK_WANT_PROCESS_TICK`
- **Descrição:** Chamada repetidamente a cada "tick" do servidor (geralmente 20 vezes por segundo, ou a cada 50ms).
- **Uso:** Para lógica de fundo contínua, temporizadores, atualizações de estado que não dependem de eventos de jogador, ou sincronização de dados.
- **Cuidado:** Evite operações de bloqueio ou computacionalmente pesadas aqui, pois podem causar lag no servidor.

```cpp
// main.cpp (com SAMP_SDK_WANT_PROCESS_TICK definido)
static int tick_count = 0;

void OnProcessTick() {
    tick_count++;

    if (tick_count % 200 == 0) // A cada 10 segundos (20 ticks/seg * 10 seg = 200 ticks)
        Samp_SDK::Log("Servidor ativo por %d segundos.", tick_count / 20);
}
```

### 3.2. Exportando Funções do Plugin

Para que o servidor SA-MP possa chamar as funções do seu plugin (`Load`, `Supports`, etc.), elas precisam ser "exportadas" do arquivo DLL (Windows) ou SO (Linux). O SDK automatiza a exportação das funções de ciclo de vida padrão, mas também fornece ferramentas para que você possa exportar suas próprias funções customizadas, caso necessite de interoperabilidade com outros programas.

O método para exportar funções varia conforme o compilador.

#### Exportação para MSVC (Visual Studio) com `Export_Plugin`

No Windows com MSVC, a maneira mais fácil de exportar funções customizadas é usando o macro `Export_Plugin`, definido em `exports.hpp`.

- **Sintaxe:** `Export_Plugin("Função", "Pilha")`
- **`Função`**: O nome exato da função a ser exportada.
- **`Pilha`**: A quantidade total de bytes que os parâmetros da função ocupam na pilha. Para a convenção `__stdcall` (padrão do SDK no Windows), o cálculo é `4 * (Quantidade de Parâmetros)`.

```cpp
#include "samp-sdk/exports.hpp"

// Exemplo: Exportando uma função customizada que poderia ser chamada
// por outro programa ou plugin que conheça sua assinatura.
const char* SAMP_SDK_CALL GetPluginVersion() {
    return "1.0.0";
}

Export_Plugin("GetPluginVersion", "0");
```

> [!WARNING]
> **Limitação do `Export_Plugin`**
> Este macro funciona **apenas com o compilador MSVC (Visual Studio)**. Ele utiliza uma diretiva `#pragma` específica da Microsoft que é ignorada por outros compiladores como GCC e Clang.

#### Exportação para GCC / Clang com `SAMP_SDK_EXPORT`

Para GCC e Clang (no Windows ou Linux), a exportação é gerenciada pelo macro `SAMP_SDK_EXPORT`, definido em `platform.hpp`. Você simplesmente o coloca antes da definição da função.

- **Mecanismo:** No Linux, ele adiciona `__attribute__((visibility("default")))`. No Windows com GCC/Clang, ele adiciona `__attribute__((dllexport))`.
- **Uso:** O SDK já aplica `SAMP_SDK_EXPORT` a todas as funções de ciclo de vida (`Load`, `Unload`, etc.), então a exportação delas é totalmente automática para esses compiladores. Para suas funções customizadas, basta fazer o mesmo.

```cpp
// Para GCC/Clang, a definição da função com SAMP_SDK_EXPORT é o suficiente.
SAMP_SDK_EXPORT const char* SAMP_SDK_CALL GetPluginVersion() {
    return "1.0.0";
}
```

### 3.3. `Plugin_Public`: Interceptando Eventos do Pawn

A macro `Plugin_Public` é a ponte primária para receber callbacks do Pawn em seu código C++.

#### Sintaxe e Declaração

- `Plugin_Public(NomeDaPublic, Tipo1 Param1, Tipo2 Param2, ...)`
- O nome da função C++ que você declara **deve ser o mesmo** do callback Pawn (ex: `OnPlayerConnect`).
- Os tipos de parâmetros C++ (`int`, `float`, `std::string`) são automaticamente convertidos pelo SDK.

```cpp
// Intercepta OnPlayerText(playerid, text[])
Plugin_Public(OnPlayerText, int playerid, std::string text) {
    Samp_SDK::Log("Jogador %d disse: %s", playerid, text.c_str());
    
    return PLUGIN_PUBLIC_CONTINUE;
}
```

#### Marshalling Automático de Parâmetros

O SDK automaticamente lida com a leitura da `cell stack` da AMX e a conversão para os tipos C++ especificados:
- `int`: Convertido diretamente de `cell`.
- `float`: Convertido de `cell` usando `amx::AMX_CTOF`.
- `std::string`: O SDK lê o endereço da string na AMX, aloca um `std::string` em C++ e copia o conteúdo.

#### Controle de Fluxo: `PLUGIN_PUBLIC_CONTINUE` vs `PLUGIN_PUBLIC_STOP`

O valor retornado pela sua função `Plugin_Public` é crucial e determina o fluxo de execução do callback:
- `return PLUGIN_PUBLIC_CONTINUE;` (valor `1`): Indica que a execução do callback deve **continuar**. Se houver outros plugins que também interceptam este callback, eles serão chamados (em ordem inversa de carregamento). Em seguida, a `public` original no script Pawn será invocada.
- `return PLUGIN_PUBLIC_STOP;` (valor `0`): Indica que a execução do callback deve ser **interrompida**. Nenhum outro plugin (com prioridade menor) ou a `public` original no script Pawn será invocado para este evento. Isso é ideal para implementar um sistema que "sobrescreve" ou "bloqueia" um comportamento padrão do SA-MP.

```cpp
// main.cpp
Plugin_Public(OnPlayerCommandText, int playerid, std::string cmdtext) {
    if (cmdtext == "/freeze") {
        Pawn_Native(TogglePlayerControllable, playerid, 0); // Congela o jogador
        Pawn_Native(SendClientMessage, playerid, -1, Plugin_Format("Jogador %d congelado.", playerid));

        return PLUGIN_PUBLIC_STOP; // Impede que o comando seja processado por outros scripts.
    }

    return PLUGIN_PUBLIC_CONTINUE; // Permite que outros comandos sejam processados.
}
```

#### Ghost Callbacks

Uma característica avançada do `Plugin_Public` é o suporte a "Ghost Callbacks". Isso significa que você pode interceptar um callback Pawn mesmo que ele **não esteja presente** no script `.amx` do gamemode ou filterscript. O SDK "engana" o servidor para que ele chame seu hook C++ de qualquer forma. Isso é útil para callbacks internos ou para criar novas funcionalidades sem depender da presença de uma `public` no script Pawn.

```cpp
// Você pode definir um callback que o script Pawn não possui, mas seu plugin irá ouvi-lo.
Plugin_Public(OnMyCustomInternalEvent, int data1, float data2) {
    Samp_SDK::Log("Evento interno customizado recebido: %d, %.2f", data1, data2);

    return PLUGIN_PUBLIC_CONTINUE;
}

// Para "disparar" este evento de outro ponto do seu código C++:
// Pawn_Public(OnMyCustomInternalEvent, 123, 45.67f);
// A chamada irá para o seu Plugin_Public acima, mesmo que não haja OnMyCustomInternalEvent no Pawn.
```

### 3.4. `Plugin_Native`: Criando Funções Nativas em C++

`Plugin_Native` permite que você estenda a funcionalidade do Pawn com código C++ de alta performance.

#### Sintaxe e Assinatura Fixa

- `Plugin_Native(NomeDaNativa, AMX* amx, cell* params)`
- A função C++ deve ter exatamente esta assinatura: `cell NomeDaNativa(AMX* amx, cell* params)`.
- `NomeDaNativa` é o nome que os scripts Pawn usarão.

```cpp
// Pawn: native GetPlayerPingAverage(playerid);
Plugin_Native(GetPlayerPingAverage, AMX* amx, cell* params) {
    // ... Implementação ...
    return 0;
}
```

#### Registro Automático de Nativas

> [!NOTE]
> Você **não precisa** chamar `amx_Register` manualmente. O SDK detecta todas as suas `Plugin_Native`s (em qualquer arquivo `.cpp` que tenha incluído `samp_sdk.hpp` e definido `SAMP_SDK_WANT_AMX_EVENTS`) e as registra automaticamente em cada script AMX carregado (`OnAmxLoad`).

#### Extração de Parâmetros: `Register_Parameters` vs. `Native_Params`

##### `Register_Parameters(...)`

- **Descrição:** Helper mais simples para extrair múltiplos parâmetros sequencialmente.
- **Uso:** `Register_Parameters(variavel1, variavel2, ...)`
- **Limitações:** Para parâmetros de entrada. Não lida com parâmetros opcionais ou acesso por índice.
- **Tipos Suportados:** `int`, `float`, `std::string`.

```cpp
// Pawn: native SetPlayerSkinAndMoney(playerid, skinid, money);
Plugin_Native(SetPlayerSkinAndMoney, AMX* amx, cell* params) {
    int playerid, skinid, money;
    Register_Parameters(playerid, skinid, money); // Extrai os 3 parâmetros
    
    Pawn_Native(SetPlayerSkin, playerid, skinid);
    Pawn_Native(GivePlayerMoney, playerid, money);
    
    return 1;
}
```

##### `Native_Params` (API Completa: `Get`, `Get_REF`, `Set_REF`)

- **Descrição:** Uma classe wrapper que fornece uma interface orientada a objetos para acessar os parâmetros de uma nativa. Mais poderosa para cenários complexos.
- **Construção:** `Native_Params p(amx, params);`

###### `p.Count()`

- **Descrição:** Retorna o número de parâmetros passados para a nativa.
- **Uso:** Essencial para lidar com parâmetros opcionais.

###### `p.Get<T>(size_t index)`

- **Descrição:** Extrai um parâmetro de entrada por índice e o converte para o tipo `T`.
- **Tipos Suportados:** `int`, `float`, `std::string`.

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

- **Descrição:** Obtém o valor de um parâmetro de **referência** (ponteiro Pawn) e o armazena em `out_value`.
- **Uso:** Para ler valores que foram passados por referência do Pawn.
- **Retorno:** `true` se o endereço AMX for válido, `false` caso contrário.

```cpp
// Pawn: native CheckPlayerStats(playerid, &Float:health, &money);
Plugin_Native(CheckPlayerStats, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    
    int playerid = p.Get<int>(0);
    float health = 0.0f;
    int money = 0;

    // Obtém os valores das referências (o Pawn passou endereços)
    p.Get_REF(1, health); // Lê o valor de Float:health
    p.Get_REF(2, money);   // Lê o valor de money
    
    Samp_SDK::Log("Jogador %d, Health: %.1f, Money: %d", playerid, health, money);
    
    // Agora, modifique-os
    health = 50.0f;
    money += 100;
    
    // E os escreve de volta na memória do Pawn
    p.Set_REF(1, health);
    p.Set_REF(2, money);
    
    return 1;
}
```

###### `p.Get_REF<T>(size_t index)` (C++17+)

- **Descrição:** Retorna um `std::optional<T>` para ler um parâmetro de referência. Mais seguro para C++17 e superior.

###### `p.Set_REF<T>(size_t index, T value)`

- **Descrição:** Escreve um valor `T` em um parâmetro de **referência** Pawn (o endereço que o Pawn passou).
- **Uso:** Para modificar valores que foram passados por referência, fazendo com que o Pawn veja a alteração.
- **Retorno:** `true` se a escrita foi bem-sucedida, `false` caso contrário.

#### Retorno de Valores

- Sua função `Plugin_Native` deve retornar um `cell`.
- Para retornar um `int` ou `bool`, use um cast para `cell`.
- Para retornar um `float`, use `amx::AMX_FTOC(meu_float)`.

```cpp
// Retorna um bool
Plugin_Native(IsPlayerSpawned, AMX* amx, cell* params) {
    int playerid;
    Register_Parameters(playerid);

    return (Pawn_Native(GetPlayerState, playerid) == PLAYER_STATE_SPAWNED) ? 1 : 0;
}

// Retorna um float
Plugin_Native(GetPlayerMaxHealth, AMX* amx, cell* params) {
    return amx::AMX_FTOC(100.0f); // Retorna 100.0f
}
```

### 3.5. `Plugin_Native_Hook`: Interceptando Nativas Existentes do SA-MP

A macro `Plugin_Native_Hook` permite que você intercepte e modifique o comportamento de qualquer função nativa existente do SA-MP ou de outros plugins. Este é um mecanismo poderoso para estender ou alterar a lógica padrão do servidor.

#### Sintaxe e Assinatura Fixa

- `Plugin_Native_Hook(NomeDaNativa, AMX* amx, cell* params)`
- A função C++ deve ter exatamente esta assinatura: `cell NomeDaNativa(AMX* amx, cell* params)`.
- `NomeDaNativa` deve ser o nome exato da native que você deseja hookar (ex: `SendClientMessage`, `SetPlayerPos`).

```cpp
// Intercepta a native SendClientMessage
Plugin_Native_Hook(SendClientMessage, AMX* amx, cell* params) {
    // ...
    return Call_Original_Native(SendClientMessage); // Importante chamar a original
}
```

#### Registro e Ativação do Hook

> [!NOTE]
> Você **não precisa** chamar `amx_Register` manualmente ou definir `SAMP_SDK_WANT_AMX_EVENTS` especificamente para `Plugin_Native_Hook`. O SDK detecta e registra automaticamente seus hooks. Na primeira execução de um script AMX, o SDK substitui o ponteiro da native na tabela por um "trampoline" que redireciona para sua função `Plugin_Native_Hook`. Este processo garante o encadeamento seguro de hooks de múltiplos plugins.

#### Chamando a Native Original (Cadeia de Hooks): `Call_Original_Native`

Dentro da sua função `Plugin_Native_Hook`, você **DEVE** usar o macro `Call_Original_Native(NomeDaNativa)` para invocar a função original (ou o próximo hook na cadeia). Isso é vital para:
- **Preservar a Funcionalidade:** Se você não chamar a original, a native hookada simplesmente deixará de funcionar para outros plugins ou para o servidor.
- **Encadeamento de Hooks:** Permite que múltiplos plugins hookem a mesma native e que todos os hooks sejam executados em uma sequência.
- **Manipulação de Retorno:** Você pode inspecionar e até mesmo modificar o valor de retorno da `Call_Original_Native` antes de retorná-lo da sua função de hook.

```cpp
// Exemplo: Bloqueando SendClientMessage se contiver uma palavra específica
Plugin_Native_Hook(SendClientMessage, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    
    // Extrai os parâmetros para análise
    int playerid = p.Get<int>(0);
    // int color = p.Get<int>(1); // Não precisamos da cor para esta lógica
    std::string message = p.Get_String(2); // Obtém a string da mensagem

    if (message.find("BADWORD") != std::string::npos) {
        Samp_SDK::Log("MENSAGEM BLOQUEADA para playerid %d: %s", playerid, message.c_str());

        return 0; // Retorna 0 (false) para o Pawn, indicando que a mensagem não foi enviada.
                  // E mais importante, NÃO chamamos Call_Original_Native, bloqueando a mensagem.
    }

    // Se a mensagem não contiver a palavra proibida, chamamos a native original
    // e retornamos seu valor, garantindo que a mensagem seja enviada normalmente
    // e que outros hooks (se existirem) sejam executados.
    return Call_Original_Native(SendClientMessage);
}
```

#### Exemplo Completo de `Plugin_Native_Hook`

```cpp
#define SAMP_SDK_IMPLEMENTATION
// SAMP_SDK_WANT_AMX_EVENTS não é estritamente necessário para hooks, mas é comum para ter OnAmxLoad/Unload
// #define SAMP_SDK_WANT_AMX_EVENTS 
#include "samp-sdk/samp_sdk.hpp"

// Hook para a native CreateVehicle
Plugin_Native_Hook(CreateVehicle, AMX* amx, cell* params) {
    Native_Params p(amx, params);

    // Extrai os parâmetros da native CreateVehicle para inspeção
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

    // Exemplo de como *modificar* um parâmetro de entrada
    // Se o modelo for 400 (Landstalker), mudamos ele para 401 (Bravura)
    if (modelid == 400) {
        // Modificamos diretamente o array 'params' para a chamada original
        params[1] = static_cast<cell>(401); // O modelo está na posição 0 do array de parâmetros (params[1])
        Samp_SDK::Log("  -> Model 400 alterado para 401 antes da criação.");
    }
    
    // Chamamos a native original (ou o próximo hook na cadeia) com os parâmetros possivelmente modificados
    cell original_retval = Call_Original_Native(CreateVehicle);

    Samp_SDK::Log("HOOK: CreateVehicle retornou: %d (ID do veículo)", (int)original_retval);

    // Você pode modificar o valor de retorno aqui antes de retorná-lo para o Pawn.
    // Exemplo: se o veículo falhou na criação, retorne um ID inválido customizado.
    if ((int)original_retval == INVALID_VEHICLE_ID) {
        Samp_SDK::Log("  -> Criação de veículo falhou na native original.");

        return -1; // Retorna um valor diferente para o Pawn.
    }

    return original_retval; // Retorna o valor que a native original retornou (ou o modificado acima).
}

unsigned int GetSupportFlags() {
    return SUPPORTS_VERSION; 
}

// Implementações mínimas para o ciclo de vida
bool OnLoad() {
    Samp_SDK::Log("Plugin de Exemplo de Native Hook carregado!");
    return true;
}

void OnUnload() {
    Samp_SDK::Log("Plugin de Exemplo de Native Hook descarregado!");
}

// Estes callbacks só estarão presentes se SAMP_SDK_WANT_AMX_EVENTS for definido
/*void OnAmxLoad(AMX* amx) {
    Samp_SDK::Log("AMX Load detectado: %p", (void*)amx);
}

void OnAmxUnload(AMX* amx) {
    Samp_SDK::Log("AMX Unload detectado: %p", (void*)amx);
}*/
```
> [!WARNING]
> A manipulação direta do array `cell* params` para alterar parâmetros de entrada exige cautela. Certifique-se de entender a ordem e o tipo dos parâmetros. Para a maioria dos casos de uso, `p.Get(...)` para inspecionar e `Call_Original_Native(...)` para continuar a cadeia é suficiente. A alteração direta de `params` deve ser feita apenas se você souber que o parâmetro é um valor e precisa ser modificado para a chamada original. Para strings e arrays, a modificação é mais complexa e geralmente envolve `amx::Set_String` para escrever no endereço existente ou realocar, o que pode ser mais fácil de gerenciar chamando a native via `Pawn_Native` com os novos valores e retornando `0` do seu hook para cancelar a chamada original.

### 3.6. `Pawn_*` Macros: Chamando Funções do Pawn a Partir do C++

Estas macros são o inverso de `Plugin_Public` e `Plugin_Native`: elas permitem que seu código C++ invoque funções Pawn.

#### `Pawn_Native(NomeDaNativa, ...)`

- **Propósito:** A forma recomendada de chamar funções nativas do SA-MP (ou de outras plugins) a partir do C++.
- **Mecanismo:** Busca o ponteiro da nativa no cache interno do SDK (preenchido por `Amx_Register_Detour`). Se encontrado, executa a nativa em um ambiente `Amx_Sandbox` (uma instância AMX falsa e isolada).
- **Performance:** A mais eficiente, pois evita a busca cara de `publics` e interage diretamente com o ponteiro da nativa.

#### `Pawn_Public(NomeDaPublic, ...)`

- **Propósito:** Chama uma função pública específica em um script Pawn.
- **Mecanismo:** Percorre as instâncias `AMX*` gerenciadas pelo `Amx_Manager`, busca a `public` pelo nome, e a executa.
- **Performance:** Menos eficiente que `Pawn_Native` devido à busca e ao `amx_Exec` real. Geralmente, `publics` são mais lentas que `natives`.
- **Uso:** Ideal para invocar eventos personalizados em seu Gamemode/Filterscripts que não são nativas.

#### `Pawn(NomeDaFuncao, ...)`

- **Propósito:** Uma macro de conveniência que tenta adivinhar se a função é uma nativa ou uma pública.
- **Mecanismo:** Primeiro, tenta chamar como `Pawn_Native`. Se falhar (a nativa não é encontrada), tenta chamar como `Pawn_Public`.
- **Performance:** Pode ser um pouco mais lenta que `Pawn_Native` se a função for nativa, devido à tentativa de busca dupla. Para `publics`, o desempenho é o mesmo de `Pawn_Public`.
- **Uso:** Para funções onde você não tem certeza se são nativas ou públicas, ou para evitar o boilerplate de tentar uma e depois a outra.

#### Sintaxe e Convenções

- **Nome da Função:** Sempre use o nome da função Pawn **diretamente, sem aspas**. O SDK o converterá para string internamente.
- **Parâmetros:** Passe os parâmetros C++ diretamente.

```cpp
// Certo:
Pawn_Native(SetPlayerPos, playerid, 100.0f, 200.0f, 300.0f); 

// Errado (mas tecnicamente funcionaria devido ao hash, evite):
Pawn_Native("SetPlayerPos", playerid, 100.0f, 200.0f, 300.0f); 
```

#### Marshalling de Parâmetros de Entrada

O SDK converte seus tipos C++ para o formato `cell` da AMX, gerenciando a memória conforme necessário:
- `int`, `bool`, `long`, `enum` -> `cell`
- `float`, `double` -> `cell` (usando `amx::AMX_FTOC`)
- `const char*`, `std::string`, `std::string_view` (C++17+) -> `cell` (aloca memória na AMX, copia a string, e passa o endereço `amx_addr`)

```cpp
void Send_Formatted_Message(int playerid, const std::string& msg) {
    Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, msg);
}
```

#### Marshalling de Parâmetros de Saída (Referências: `int&`, `float&`, `std::string&`)

Esta é uma funcionalidade-chave para conveniência e segurança. Para funções Pawn que esperam um ponteiro (referência), o SDK automatiza todo o processo de alocação/liberação de memória e cópia de dados.

- **Como usar:** Basta passar sua variável por referência (`&`).
- **Mecanismo:** O SDK aloca memória na heap da AMX, passa o endereço AMX para a função Pawn, espera que a função Pawn preencha esse endereço, lê o valor de volta, e libera a memória da AMX. Tudo de forma transparente.
- **Com `std::string&`:** O SDK aloca um buffer padrão (256 células) na AMX para a string.

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

#### O Objeto `Callback_Result`: Análise Completa

Todas as chamadas `Pawn_*` retornam um objeto `Callback_Result`. Este objeto é um wrapper seguro para o resultado da chamada Pawn.

- `Callback_Result() noexcept`: Construtor padrão, indica falha (`success_ = false`).
- `Callback_Result(bool success, cell value) noexcept`: Construtor para sucesso ou falha com valor.
- `explicit operator bool() const`: Permite usar `if (result)` para verificar se a chamada foi bem-sucedida.
- `operator cell() const`: Permite converter o resultado para `cell` para obter o valor.
- `float As_Float() const`: Conveniência para obter o resultado como `float`.
- `cell Value() const`: Retorna o valor bruto `cell`.
- `bool Success() const`: Retorna `true` se a chamada Pawn foi bem-sucedida.
- `int Get_Amx_Error() const`: Retorna o código de erro da AMX se a chamada falhou (0 para sucesso).

```cpp
// Exemplo: Obtendo a vida de um jogador.
// A nativa GetPlayerHealth(playerid, &Float:health) espera um playerid e uma referência para a vida.
int playerid = 0; // Exemplo de ID de jogador
float player_health = 0.0f;

// Chamamos GetPlayerHealth, passando playerid e player_health por referência.
// O SDK cuidará do marshalling para o parâmetro de saída 'health'.
Callback_Result result = Pawn_Native(GetPlayerHealth, playerid, player_health);

if (result) { // Verifica se a chamada foi bem-sucedida (operator bool)
    // O valor retornado por result.As_Float() ou result (operator cell)
    // seria o valor de retorno da *nativa*, não o parâmetro de saída.
    // O valor da vida já foi atualizado em 'player_health' devido ao marshalling do parâmetro de saída.
    Samp_SDK::Log("Jogador %d tem %.1f de vida.", playerid, player_health);
}
else {
    // A chamada falhou, talvez o jogador não exista ou a nativa não foi encontrada.
    Samp_SDK::Log("Erro ao obter vida do jogador %d. Código AMX: %d", playerid, result.Get_Amx_Error());
}

// Para nativas que retornam um valor e usam parâmetros de saída (menos comum, mas possível),
// você usaria ambos:
// Callback_Result other_result = Pawn_Native(SomeNative, param1, output_param, param2);
// if (other_result) {
//     cell returned_value = other_result;
//     // output_param já está atualizado
// }
```

### 3.7. `Plugin_Module`: Gerenciamento de Módulos Dinâmicos

A macro `Plugin_Module` permite que seu plugin atue como um "carregador" para outros plugins, criando uma arquitetura modular e extensível. Um módulo carregado desta forma é tratado como um plugin de primeira classe, com seu próprio ciclo de vida de eventos gerenciado pelo plugin hospedeiro.

#### Sintaxe e Propósito

- `Plugin_Module(const char* nome_do_arquivo_base, const char* diretorio_do_modulo, const char* mensagem_sucesso_opcional)`
- `nome_do_arquivo_base`: O nome *base* do arquivo do módulo, **sem a extensão** (ex: para `my_module.dll` ou `my_module.so`, use `"my_module"`). O SDK adicionará automaticamente a extensão `.dll` ou `.so` apropriada.
- `diretorio_do_modulo`: O caminho do diretório onde o arquivo do módulo está localizado (ex: `"plugins/my_custom_modules"`). **Não inclua o nome do arquivo aqui.** O SDK fará a concatenação do caminho completo (`diretorio_do_modulo/nome_do_arquivo_base.ext`).
- `mensagem_sucesso_opcional`: Uma mensagem opcional para ser logada no console do servidor se o módulo carregar com sucesso.

```cpp
// main.cpp, dentro de OnLoad()

// Carrega o módulo 'core_logic.dll' (ou 'core_logic.so')
// que está localizado na pasta 'modules/custom/' do servidor.
if (!Plugin_Module("core_logic", "modules/custom", "Módulo de Lógica Core carregado com sucesso!"))
    return (Samp_SDK::Log("ERRO FATAL: Falha ao carregar o módulo 'core_logic'!"), false);

// Carrega o módulo 'admin_system.dll' (ou 'admin_system.so')
// que está localizado diretamente na pasta 'plugins/' do servidor.
if (!Plugin_Module("admin_system", "plugins", "Módulo de Administração ativado."))
    Samp_SDK::Log("AVISO: Módulo de Administração não pôde ser carregado.");
```

#### Ciclo de Vida de um Módulo

Um módulo deve exportar as funções `Load`, `Unload` e `Supports`, assim como um plugin normal. O SDK gerencia o ciclo de vida do módulo da seguinte forma:

- **Carregamento:** Quando `Plugin_Module` é chamado, o SDK:
   1. Constrói o caminho completo do arquivo (ex: `modules/custom/core_logic.dll`).
   2. Usa `Dynamic_Library` (`LoadLibrary`/`dlopen`) para carregar o binário.
   3. **Obtém os ponteiros para TODAS as funções de ciclo de vida do módulo:**
      - **Obrigatórias:** `Load`, `Unload`, `Supports`. Se alguma faltar, o carregamento do módulo falha.
      - **Opcionais:** `AmxLoad`, `AmxUnload`, `ProcessTick`.
   4. Chama a função `Load` do módulo, passando `ppData` do plugin principal.
   5. Se `Load` retornar `true`, o módulo é adicionado à lista interna de módulos carregados.

- **Encaminhamento de Eventos:** O plugin hospedeiro **automaticamente encaminha** os eventos para todos os módulos carregados.
 > [!IMPORTANT]
 > Para que os eventos sejam encaminhados corretamente, o **plugin hospedeiro** (o que chama `Plugin_Module`) deve estar configurado para receber esses eventos.
 > - Para que `AmxLoad` e `AmxUnload` funcionem nos módulos, o plugin hospedeiro deve definir a macro `SAMP_SDK_WANT_AMX_EVENTS`.
 > - Para que `ProcessTick` funcione nos módulos, o plugin hospedeiro deve definir a macro `SAMP_SDK_WANT_PROCESS_TICK`.

- **Descarregamento:** Durante `OnUnload` do seu plugin principal, o SDK descarrega todos os módulos que foram carregados via `Plugin_Module`. Isso é feito na **ordem inversa** ao carregamento (o último a ser carregado é o primeiro a ser descarregado), o que é crucial para gerenciar dependências e garantir a liberação correta de recursos.

#### Benefícios da Modularização

- **Organização do Código:** Divida grandes plugins em componentes menores e gerenciáveis, cada um em seu próprio arquivo de módulo.
- **Reusabilidade:** Crie módulos genéricos (ex: um módulo de banco de dados, um módulo de sistema de log avançado) que podem ser usados por diferentes plugins, promovendo a reutilização de código.
- **Componentes Independentes:** Crie módulos que são **totalmente orientados a eventos e independentes**. Um módulo pode ter suas próprias `Plugin_Native`s, interceptar `Plugin_Public`s e ter sua própria lógica `OnProcessTick`, operando como um plugin autônomo, mas carregado por um hospedeiro.
- **Atualizações Dinâmicas:** Em cenários controlados, permite a atualização de partes do seu sistema (substituindo um `.dll` ou `.so` de módulo) sem a necessidade de recompilar e reiniciar o plugin principal ou o servidor inteiro (embora isso exija um gerenciamento de versão e compatibilidade rigorosos).

### 3.8. `Plugin_Call`: Chamando Nativas Internas do Plugin

Use `Plugin_Call` para invocar uma `Plugin_Native` definida **dentro do seu próprio plugin**.

#### Sintaxe e Vantagens de Performance

- `Plugin_Call(NomeDaNativa, Param1, Param2, ...)`
- **Vantagem:** Evita a sobrecarga de procurar a nativa no array de nativas da AMX. O SDK mantém um mapa direto de hashes de nome para ponteiros de função para suas próprias nativas, tornando esta a forma mais rápida de chamá-las internamente.
- **Requer:** `SAMP_SDK_WANT_AMX_EVENTS`.

```cpp
// main.cpp
Plugin_Native(InternalCheckPlayerLevel, AMX* amx, cell* params) {
    int playerid;
    Register_Parameters(playerid);

    // Lógica para verificar o nível
    return (playerid % 2 == 0) ? 1 : 0; // Exemplo: nível par para IDs pares
}

void Check_All_Players_Level() {
    for (int i = 0; i < MAX_PLAYERS; ++i) {
        if (Pawn_Native(IsPlayerConnected, i)) {
            if (Plugin_Call(InternalCheckPlayerLevel, i)) // Chama sua própria nativa
                Samp_SDK::Log("Jogador %d está em um nível alto!", i);
        }
    }
}
```

### 3.9. Funções Utilitárias do SDK

#### `Samp_SDK::Log(const char* format, ...)`

- **Descrição:** Imprime mensagens no console do servidor e no arquivo `server_log.txt`. Um wrapper seguro para `logprintf`.
- **Uso:** Para depuração, mensagens de status e erros.
- **Mecanismo:** Internamente, o SDK obtém o ponteiro para `logprintf` através de `ppData[PLUGIN_DATA_LOGPRINTF]`. A função lida com a formatação da string de forma segura.

```cpp
// Em qualquer lugar do seu plugin
Samp_SDK::Log("O plugin foi inicializado com um valor %d e uma string '%s'.", 123, "teste");
```

#### `std::string Plugin_Format(const char* format, ...)` (Recomendado)

- **Descrição:** Formata uma string de forma segura (similar a `sprintf`) e retorna um `std::string`. Esta é a maneira **recomendada e mais idiomática** de formatar strings para uso dentro do seu plugin.
- **Uso:** Ideal para construir mensagens formatadas antes de passá-las para `Samp_SDK::Log`, `Pawn_Native(SendClientMessage, ...)`, ou para qualquer outra necessidade de string dentro do seu código C++.
- **Mecanismo:** Internamente, `Plugin_Format` é uma macro que chama `Samp_SDK::Format`. Ele utiliza `vsnprintf` para determinar o tamanho exato da string formatada e aloca um `std::string` com capacidade suficiente, evitando estouros de buffer.

```cpp
int playerid = 0; // Exemplo de ID
int health = 50;
Pawn_Native(SendClientMessage, playerid, 0xFFFFFFFF, Plugin_Format("Jogador %d, sua vida atual é %d.", playerid, health));

// Também pode ser usado para logs internos
Samp_SDK::Log(Plugin_Format("DEBUG: Processando status para o ID %d", playerid));
```

#### `std::string Samp_SDK::Format(const char* format, ...)` (Detalhe de Implementação)

- **Descrição:** A função de implementação subjacente para formatação de strings, localizada dentro do namespace `Samp_SDK`.
- **Uso:** Geralmente não é chamada diretamente pelo usuário. A macro `Plugin_Format` é fornecida como uma conveniência para esta função, alinhando-se com a convenção de nomenclatura de outras macros do SDK (`Plugin_Public`, `Plugin_Native`). Você só a chamaria diretamente se quisesse evitar a macro `Plugin_Format` por algum motivo específico.

```cpp
// Exemplo de como Samp_SDK::Format funciona, mas prefira Plugin_Format
std::string raw_status = Samp_SDK::Format("Apenas para uso interno: %d.", 42);
```

#### `std::string Samp_SDK::Get_String(AMX* amx, cell amx_addr)`

- **Descrição:** Converte um endereço de string da AMX (`cell amx_addr`) em um `std::string` C++.
- **Uso:** Principalmente dentro de `Plugin_Native` e `Plugin_Native_Hook` quando você precisa acessar strings que não são automaticamente convertidas por `Register_Parameters` ou `Native_Params` (ex: se o parâmetro Pawn é um `const` `string` e não foi declarado como `std::string` no seu `Plugin_Native` ou `Plugin_Public` para Marshalling automático).

```cpp
Plugin_Native(PrintRawAmxString, AMX* amx, cell* params) {
    Native_Params p(amx, params);
    cell amx_string_addr = p.Get<cell>(0); // Obtém o endereço da string na AMX

    std::string cpp_string = Samp_SDK::Get_String(amx, amx_string_addr);
    Samp_SDK::Log("String da AMX: %s", cpp_string.c_str());

    return 1;
}
```

## 4. Compilação e Deploy

### Requisitos de Arquitetura e Plataforma

- Seu plugin **DEVE** ser compilado para a arquitetura **x86 (32-bit)**.
- Plataformas Suportadas: Windows (.dll) e Linux (.so).

### Exemplos de Comandos de Compilação

#### **MSVC (Visual Studio)**

1. Crie um novo projeto de "Dynamic-Link Library (DLL)".
2. Nas configurações do projeto, defina a "Plataforma de Solução" para **x86**.
3. Garanta que o C++ Language Standard seja pelo menos C++17.

#### **GCC / Clang (Linux)**

```bash
# Para um plugin chamado 'my_plugin.so' a partir de 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -fPIC -Wall -Wextra -Wl,--no-undefined main.cpp -o my_plugin.so
```
- `-m32`: Compila para 32-bit.
- `-shared`: Cria uma biblioteca compartilhada (`.so`).
- `-std=c++17`: Define o padrão C++ para C++17 (pode ser `c++20`, mas C++17 é o mínimo).
- `-O2`: Nível de otimização 2.
- `-fPIC`: Gera código independente de posição, necessário para bibliotecas compartilhadas.
- `-Wall -Wextra`: Ativa avisos adicionais para ajudar a pegar erros.
- `-Wl,--no-undefined`: Impede a criação da biblioteca se houver símbolos indefinidos.

#### **GCC / Clang (MinGW no Windows)**

```bash
# Para um plugin chamado 'my_plugin.dll' a partir de 'main.cpp'
g++ -m32 -shared -std=c++17 -O2 -static-libstdc++ -static-libgcc -Wl,--no-undefined main.cpp -o my_plugin.dll
```
- `-static-libstdc++`: Linka a biblioteca padrão C++ estaticamente. Essencial para evitar que seu plugin dependa de DLLs de runtime específicas do compilador que podem não estar presentes no sistema do usuário.
- `-static-libgcc`: Linka a biblioteca GCC estaticamente.

### Considerações para Distribuição

- **Nome do Arquivo:** Seu plugin deve ter a extensão `.dll` (Windows) ou `.so` (Linux). Ex: `my_plugin.dll`.
- **Localização:** Coloque o arquivo compilado na pasta `plugins/` do seu servidor SA-MP.
- **server.cfg:** Adicione o nome do seu plugin (se for Windows, sem a extensão) à linha `plugins` no `server.cfg`.
   ```
   plugins my_plugin (se for Linux, my_plugin.so)
   ```

## Licença

Copyright © **AlderGrounds**

Este software é licenciado sob os termos da Licença MIT ("Licença"); você pode utilizar este software de acordo com as condições da Licença. Uma cópia da Licença pode ser obtida em: [MIT License](https://opensource.org/licenses/MIT)

### Termos e Condições de Uso

#### 1. Permissões Concedidas

A presente licença concede, gratuitamente, a qualquer pessoa que obtenha uma cópia deste software e arquivos de documentação associados, os seguintes direitos:
* Utilizar, copiar, modificar, mesclar, publicar, distribuir, sublicenciar e/ou vender cópias do software sem restrições
* Permitir que pessoas para as quais o software é fornecido façam o mesmo, desde que sujeitas às condições a seguir

#### 2. Condições Obrigatórias

Todas as cópias ou partes substanciais do software devem incluir:
* O aviso de direitos autorais acima
* Este aviso de permissão
* O aviso de isenção de responsabilidade abaixo

#### 3. Direitos Autorais

O software e toda a documentação associada são protegidos por leis de direitos autorais. A **AlderGrounds** mantém a titularidade dos direitos autorais originais do software.

#### 4. Isenção de Garantias e Limitação de Responsabilidade

O SOFTWARE É FORNECIDO "COMO ESTÁ", SEM GARANTIA DE QUALQUER TIPO, EXPRESSA OU IMPLÍCITA, INCLUINDO, MAS NÃO SE LIMITANDO ÀS GARANTIAS DE COMERCIALIZAÇÃO, ADEQUAÇÃO A UM DETERMINADO FIM E NÃO VIOLAÇÃO. 

EM NENHUMA CIRCUNSTÂNCIA OS AUTORES OU TITULARES DOS DIREITOS AUTORAIS SERÃO RESPONSÁVEIS POR QUALQUER REIVINDICAÇÃO, DANOS OU OUTRA RESPONSABILIDADE, SEJA EM AÇÃO DE CONTRATO, DELITO OU DE OUTRA FORMA, DECORRENTE DE, FORA DE OU EM CONEXÃO COM O SOFTWARE OU O USO OU OUTRAS NEGOCIAÇÕES NO SOFTWARE.

---

Para informações detalhadas sobre a Licença MIT, consulte: https://opensource.org/licenses/MIT