# PascalM — Compilador Pascal para LLVM

PascalM é um compilador didático para um subconjunto robusto da linguagem Pascal, desenvolvido como parte da disciplina de Linguagens e Compiladores (CAES101 / LIN0018).

Originalmente escrito em C (flex/bison) gerando código C, o projeto foi **portado para Rust** e hoje gera **LLVM IR**, que é linkado em um **executável nativo** via `clang`. O projeto inclui também um **language server (LSP)** e um **formatador** de código.

## Arquitetura

O compilador segue o pipeline clássico, todo implementado em Rust:

1. **Análise léxica** — `src/lexer.rs`, usando [`logos`](https://crates.io/crates/logos). Converte o código-fonte em um fluxo de tokens (case-insensitive, ignora comentários `{ }` e `(* *)`).
2. **Análise sintática** — `src/parser.lalrpop`, usando [`lalrpop`](https://crates.io/crates/lalrpop). Consome os tokens e constrói a AST não-tipada (`src/ast.rs`). Cada nó relevante carrega um `Span` (offset no código), usado pelo LSP.
3. **Análise semântica** — `src/analyzer.rs` + `src/symbol_table.rs`. Percorre a AST fazendo checagem de tipos e resolução de escopo, produzindo uma **AST tipada** (`src/typed_ast.rs`) e uma lista de diagnósticos.
4. **Geração de código** — `src/codegen.rs`, usando [`inkwell`](https://crates.io/crates/inkwell) (bindings de LLVM 18). Cada módulo vira um arquivo `.ll` (LLVM IR).
5. **Linkagem** — `src/main.rs` invoca o `clang` para linkar os `.ll` gerados com as bibliotecas estáticas da stdlib, produzindo o executável final.

## Estrutura do projeto

```
.
├── Cargo.toml                 # crate principal `pascalm` (lib + binário)
├── build.rs                   # gera o parser (lalrpop) e compila a stdlib em .a
├── src/
│   ├── main.rs                # CLI: carregamento de módulos, pipeline e linkagem
│   ├── lib.rs                 # exporta os módulos da biblioteca
│   ├── lexer.rs               # analisador léxico (logos)
│   ├── parser.lalrpop         # gramática (lalrpop)
│   ├── ast.rs                 # AST não-tipada
│   ├── typed_ast.rs           # AST tipada (saída da análise semântica)
│   ├── analyzer.rs            # análise semântica + diagnósticos
│   ├── symbol_table.rs        # tabela de símbolos
│   ├── codegen.rs             # geração de LLVM IR (inkwell)
│   ├── formatter.rs           # formatador (pretty-printer, preserva comentários)
│   ├── stdlib/                # bibliotecas padrão (Rust + interface .pas)
│   │   ├── system/            #   runtime implícito (sqrt, halt, init, strings…)
│   │   ├── net/               #   sockets
│   │   └── json/              #   JSON
│   ├── examples/              # programas de exemplo (.pascalm)
│   ├── tests/                 # testes de integração + runners
│   │   ├── success/           #   programas que devem compilar e rodar
│   │   ├── compile_error/     #   programas que devem falhar
│   │   └── run_tests.sh
│   └── lsp/                   # language server `pascalmls`
│       ├── src/server.rs      #   servidor (tower-lsp)
│       ├── tests/lsp.rs       #   testes end-to-end (drive o servidor via JSON-RPC)
│       └── pascalmls.nvim/    #   plugin de integração para Neovim
├── run_rust_tests.sh          # roda a suíte de testes de integração
└── .github/workflows/         # CI (build + testes em Ubuntu)
```

## Funcionalidades da linguagem

### Tipos de dados
- **Primitivos**: `integer`, `real`, `char`, `boolean`.
- **String**: tipo `string` para manipulação de texto.
- **Estruturados**: `array` (incl. multidimensionais), `record` (incl. **partes variantes** `case … of`), `set` (operações bitwise), `file of`.
- **Ponteiros** (`^`) e desreferência.
- **Subfaixas** (`1..10`), **enumerações** e tipos definidos pelo usuário via `type`.

### Estruturas de controle
- `if … then … else`
- `case … of … [else] … end`
- `while … do`
- `repeat … until`
- `for … to/downto … do`
- `goto` / labels
- `with … do`

### Procedimentos e funções
- Declaração de `procedure` e `function`.
- Parâmetros **por valor** (padrão) e **por referência** (`var`).
- Declarações antecipadas (`forward`) e funções `external` (vinculadas à stdlib).

### Módulos
- `program` e `unit` (com seções `interface` e `implementation`).
- Cláusula `uses` para importar units, com resolução de caminhos (`-L`), ordenação topológica e detecção de dependência circular.
- A unit `system` é o runtime implícito, sempre linkado.

## Pré-requisitos

- **Rust** (stable) — via [rustup](https://rustup.rs).
- **LLVM 18** (o crate `inkwell` usa a feature `llvm18-0`).
- **clang** (usado para a linkagem final).

A localização do LLVM 18 é informada via a variável `LLVM_SYS_180_PREFIX`:

```bash
# Linux (apt.llvm.org / pacote llvm-18)
export LLVM_SYS_180_PREFIX=/usr/lib/llvm-18

# macOS (Homebrew)
export LLVM_SYS_180_PREFIX="$(brew --prefix llvm@18)"
# o zstd do Homebrew é keg-only; se a linkagem reclamar de `-lzstd`, adicione:
export RUSTFLAGS="-L $(brew --prefix zstd)/lib"
```

## Compilando

```bash
export LLVM_SYS_180_PREFIX=/usr/lib/llvm-18   # ajuste para o seu sistema
cargo build --release
```

O binário do compilador fica em `target/release/pascalm`.

## Usando o compilador

```bash
pascalm --file <entrada.pascalm> [--output <executável>] [-L <dir_de_units>]... [--verbose]
```

- `-f, --file` — arquivo de entrada (obrigatório).
- `-o, --output` — nome do executável de saída (padrão: `output`).
- `-L, --lib-path` — diretórios adicionais para procurar units (`uses`). Pode repetir.
- `-v, --verbose` — saída detalhada.

Exemplo:

```bash
pascalm --file src/examples/structures.pascalm --output structures
./structures
```

O compilador gera um `.ll` por módulo e os linka (com a stdlib) em um único executável nativo.

### Formatando pela CLI

Além de compilar, o binário expõe o subcomando `fmt`, que aplica a mesma formatação do LSP (ver [Formatador](#formatador)):

```bash
pascalm fmt --file <arquivo.pascalm>   # formata um arquivo no lugar
pascalm fmt --all                      # formata todos os .pas/.pascalm a partir do diretório atual
```

## Ferramentas de editor

### Language server (`pascalmls`)

O LSP fica em `src/lsp` (crate `pascalmls`, que depende do crate `pascalm` — o compilador e o LSP compartilham o **mesmo** analisador e formatador). O servidor é construído sobre [`tower-lsp`](https://crates.io/crates/tower-lsp).

#### Recursos disponíveis

| Recurso | Método LSP | Observações |
|---|---|---|
| Diagnósticos | `publish_diagnostics` | Sintáticos + semânticos, atualizados a cada mudança (*push*). |
| Hover | `textDocument/hover` | Mostra a assinatura/tipo do símbolo, **inclusive cross-file** (de units em `uses`) e da stdlib. |
| Ir para definição | `textDocument/definition` | **Cross-file** (pula para a unit definidora) e para símbolos da stdlib. |
| Referências | `textDocument/references` | No arquivo e **cross-file** para símbolos exportados (a unit definidora + todas que a usam). |
| Renomear | `textDocument/rename` | No arquivo e **cross-file** para símbolos exportados. Recusa *builtins*. |
| Autocomplete | `textDocument/completion` | Símbolos locais + exportados pelas units em `uses` + palavras-chave. |
| Outline / símbolos | `textDocument/documentSymbol` | Estrutura do arquivo (consts/types/vars/procs, com params e locais aninhados). |
| *Semantic tokens* | `textDocument/semanticTokens/full` | Realce semântico. |
| Formatação | `textDocument/formatting` | Documento inteiro; preserva comentários. |
| Índice de workspace | — | No `initialize`, varre e analisa as units do projeto (base das features cross-file). |

#### Instalação

```bash
export LLVM_SYS_180_PREFIX="$(brew --prefix llvm@18)"   # ajuste para o seu sistema
export LIBRARY_PATH="$(brew --prefix zstd)/lib:$LIBRARY_PATH"  # macOS, se reclamar de zstd
cargo install --path src/lsp --force
```

Isso coloca `pascalmls` no `PATH` (`~/.cargo/bin`). Depois de reinstalar, reinicie o servidor no editor (ex.: `:LspRestart` no Neovim).

Para Neovim há um plugin pronto em `src/lsp/pascalmls.nvim` (registra os filetypes `.pas`/`.pascalm`, configura e habilita o servidor, e re-attacha após restart). Veja o [README do plugin](src/lsp/pascalmls.nvim/README.md).

#### Limitações do que existe hoje

- **Completion** é por identificador, não *member-access*: depois de `registro.` ele não filtra pelos campos do tipo (lista os mesmos símbolos globais). O caractere de trigger `.` apenas reabre a lista geral.
- **References/rename cross-file** usam o índice construído no `initialize`. Edições **não salvas** em *outros* arquivos só refletem após nova análise (ao salvar); no caminho cross-file até o buffer atual é lido do disco.
- **Match cross-file é por nome + stem da unit**: duas units que exportem o mesmo identificador podem gerar ocorrências imprecisas.
- **Rename** recusa *builtins* (ex. `writeln`); símbolos da stdlib (`system`/`net`/`json`) só existem como cópia materializada em cache temporário, então renomeá-los não tem efeito prático.
- **Análise por-arquivo (buffer ao vivo) roda sem interfaces**: símbolos importados não entram em escopo nela, então features *single-file* (ex. *semantic tokens*) não enxergam referências a símbolos de outras units. As features cross-file contornam isso usando o índice de workspace.
- **Document symbols** usa o *span do nome* como range da entrada (não o range completo da declaração).
- **Sincronização é FULL**: o editor reenvia o documento inteiro a cada mudança.
- Diagnósticos são *push* e a análise semântica para no primeiro erro fatal (além dos coletados no buffer).

#### O que ainda não tem (ideias de roadmap)

- *Signature help* (ajuda de parâmetros ao chamar proc/função).
- Completion ciente de contexto e de *member-access* (`registro.campo`, `ponteiro^.`).
- *Workspace symbols* (`workspace/symbol`) — busca de símbolos no projeto inteiro.
- *Code actions* / *quick fixes*.
- *Document highlight* (destacar ocorrências do símbolo sob o cursor).
- *Inlay hints* (tipos inferidos, nomes de parâmetro) — a *capability* existe mas está desligada.
- *Folding ranges*, *selection ranges*, *code lens*, *document links*.
- *Call hierarchy* / *type hierarchy*.
- Ir para declaração / definição de tipo / implementação (hoje só `definition`).
- Formatação por intervalo (*range*) e *on-type* (hoje só documento inteiro).
- Diagnósticos *pull* (`textDocument/diagnostic`) e sincronização incremental.
- Re-análise incremental do workspace ao salvar (manter cross-file sempre fresco).

### Formatador

A formatação é exposta pelo LSP (`textDocument/formatting`) e implementada em `src/formatter.rs`. Ela reescreve o código em estilo canônico (indentação de 2 espaços, palavras-chave em minúsculo) preservando os comentários do original.

## Testes

```bash
# suíte de integração (compila e roda os programas em src/tests/success)
./run_rust_tests.sh

# testes unitários do crate (analisador, formatador, etc.)
export LLVM_SYS_180_PREFIX=/usr/lib/llvm-18
cargo test

# testes end-to-end do LSP (sobem o servidor e dirigem via JSON-RPC)
cargo test --manifest-path src/lsp/Cargo.toml
```

## Autor

- **Nome:** Murilo Henrique Alves
- **Contato:** hi@omurilo.dev
