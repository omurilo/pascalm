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
│       └── init.lua           #   exemplo de configuração para Neovim
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

## Ferramentas de editor

### Language server (`pascalmls`)

O LSP fica em `src/lsp` e oferece diagnósticos, hover, ir-para-definição, *semantic tokens* (highlight) e formatação.

```bash
cd src/lsp
cargo build --release
# instale no PATH para o editor encontrar:
cargo install --path .
```

Para Neovim há um exemplo de configuração em `src/lsp/init.lua` (associa as extensões `.pas`/`.pascalm` ao servidor `pascalmls`).

### Formatador

A formatação é exposta pelo LSP (`textDocument/formatting`) e implementada em `src/formatter.rs`. Ela reescreve o código em estilo canônico (indentação de 2 espaços, palavras-chave em minúsculo) preservando os comentários do original.

## Testes

```bash
# suíte de integração (compila e roda os programas em src/tests/success)
./run_rust_tests.sh

# testes unitários do crate (analisador, formatador, etc.)
export LLVM_SYS_180_PREFIX=/usr/lib/llvm-18
cargo test
```

## Autor

- **Nome:** Murilo Henrique Alves
- **Contato:** hi@omurilo.dev
