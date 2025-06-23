# Compilador Pascal-para-C

Este projeto é um compilador didático desenvolvido como parte da disciplina de Linguagens e Compiladores (CAES101 / LIN0018). O objetivo principal é traduzir um subconjunto robusto da linguagem Pascal para código-fonte C, aplicando os conceitos teóricos de construção de compiladores em um projeto prático e funcional.

O compilador é construído em C e utiliza as ferramentas `flex` para a análise léxica e `bison` para a análise sintática.

## Arquitetura do Compilador

O projeto segue a arquitetura clássica de um compilador, dividido nas seguintes fases:

1.  **Análise Léxica**: O scanner (definido em `parser/lexer.l`) converte o código-fonte Pascal em um fluxo de tokens.
2.  **Análise Sintática**: O parser (definido em `parser/parser.y`) analisa os tokens, valida a estrutura do programa de acordo com a gramática e constrói uma Árvore Sintática Abstrata (AST) para representar o código.
3.  **Análise Semântica**: Um analisador semântico percorre a AST para realizar a checagem de tipos, resolução de escopo e outras validações. Esta fase utiliza uma Tabela de Símbolos para armazenar informações sobre variáveis, tipos e funções.
4.  **Geração de Código**: Após a validação, a AST é percorrida uma última vez para traduzir as estruturas do Pascal em código C equivalente, que é então salvo em um arquivo de saída.

## Funcionalidades e Suporte à Linguagem

O compilador dá suporte a um subconjunto significativo da linguagem Pascal.

### Tipos de Dados Suportados

* **Tipos Primitivos**: `integer`, `real`, `char`, `boolean`.
* **String**: Um tipo `string` customizado para facilitar a manipulação de texto.
* **Tipos Estruturados**:
    * `ARRAY`: Vetores e matrizes de tipos primitivos ou outros tipos estruturados.
    * `RECORD`: Tipos de registro complexos, incluindo suporte para **partes variantes** (`case ... of`).
    * `SET`: Conjuntos de tipos ordinais, traduzidos para operações bitwise em C.
    * `FILE OF type` (suporte na gramática).
* **Ponteiros**: A gramática reconhece a sintaxe de ponteiros (`^`).
* **Tipos Definidos pelo Usuário**: Suporte completo a `TYPE` para criar apelidos e novos tipos estruturados.

### Estruturas de Controle

* `IF ... THEN ... ELSE`
* `CASE ... OF ... END`
* `WHILE ... DO`
* `REPEAT ... UNTIL`
* `FOR ... TO/DOWNTO ... DO`
~* `GOTO` (suporte na gramática).~

### Procedimentos e Funções

* Declaração de `PROCEDURE` e `FUNCTION`.
* Passagem de parâmetros **por valor** (padrão).
* Passagem de parâmetros **por referência** (usando a palavra-chave `VAR`).
* Declarações antecipadas (`FORWARD`).

## Como Compilar e Usar

### Pré-requisitos

Para compilar este projeto, você precisará ter os seguintes pacotes instalados:
* `gcc` (ou outro compilador C)
* `flex`
* `bison`
* `make` (recomendado)

### Compilando o Compilador

É altamente recomendado o uso de um `Makefile` para gerenciar a compilação. Um exemplo de regra de compilação seria:

```bash
# via bash script
cd src && ./build
```

```bash
# via comandos diretamente
bison -d -o parser/parser.tab.c parser/parser.y
flex -o parser/lex.yy.cc parser/parser.l parser/parser.tab.h
gcc -Wall -Wextra -o pascalm  ast/ast.c semantic-analyzer/analyzer.c symbol-table/symbol-table.c code-generation/code.c code-generation/utils.c main.c context.c logger.c parser/parser.tab.c parser/lex.yy.c -lfl -lm
```

Com um `Makefile`, você normalmente compilaria com um simples comando:
```bash
make
```

### Executando o Compilador

Para traduzir um arquivo Pascal para C, use o seguinte comando:

```bash
# por padrão o arquivo de saída será o mesmo de entrada, porém, com a extensão `.c`
./pascalm -f <arquivo_de_entrada.pascalm> -o <arquivo_de_saida.c>
```

Isso irá gerar um arquivo C. Para compilar e executar o programa final:

```bash
# Compila o código C gerado
gcc <arquivo_de_saida.c> -o meu_programa -lm

# Executa o programa
./meu_programa
```

## Autor

* **Nome:** Murilo Henrique Alves
* **Contato:** hi@omurilo.dev

