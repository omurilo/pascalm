# Comparação: Pascalm vs. Pascal Oficial (ISO 7185 / ANTLR)

Este documento detalha as principais diferenças, ausências e limitações da gramática do **Pascalm** em relação à especificação oficial do Pascal.

## 1. Modularização e Estrutura de Unidades
*   **Ausência de `UNIT`:** O Pascalm suporta apenas a estrutura `PROGRAM`. A gramática oficial suporta `UNIT`, que inclui as seções `INTERFACE`, `IMPLEMENTATION`, `INITIALIZATION` e `FINALIZATION`.
*   **Cláusula `USES`:** Não há suporte para a importação de módulos ou bibliotecas externas através da palavra-chave `uses`.
*   **Parâmetros de Sistema:** O suporte para parâmetros no cabeçalho do programa (ex: `program Exemplo(input, output);`) é limitado ou simplificado.

## 2. Tipos de Dados e Estruturas
*   **Variant Records (Registros Variantes):** Embora a AST possua suporte interno, a gramática (`parser.lalrpop`) não implementa a sintaxe para campos variantes (similar a `unions` em C, usando `case .. of`).
*   **Tipos Compactados (`packed`):** A palavra-chave `packed` é reconhecida pelo lexer mas ignorada pela gramática. No Pascal padrão, ela é essencial para otimização de memória em arrays e registros.
*   **Strings com Tamanho Fixo:** O Pascalm trata `string` como um tipo genérico. Falta o suporte para definir limites, como `string[100]`.
*   **Arquivos Binários Genéricos:** Falta suporte para `file` sem tipo definido (untyped files), comum para I/O de baixo nível.

## 3. Lexer e Literais
*   **Limitação de `CharLiteral`:** O lexer atual aceita apenas uma única letra (`[a-zA-Z]`). O Pascal oficial permite qualquer caractere ASCII, símbolos e sequências de escape.
*   **Constantes de Caractere por Código:** Falta suporte para a sintaxe `#` (ex: `#13` para Carriage Return).
*   **Bases Numéricas:** Ausência de literais hexadecimais (ex: `$FF`), muito comuns em implementações como FreePascal.
*   **Comentários Aninhados:** O suporte atual para comentários `(* *)` e `{ }` não prevê aninhamento.

## 4. Instruções e Sintaxe de I/O
*   **Formatação no `write`/`writeln`:** A sintaxe especial de formatação de largura e precisão (ex: `write(x:5:2)`) não está implementada na gramática; o compilador os trata como chamadas de função comuns.
*   **Extensões do `Case`:** O Pascalm utiliza `else` no bloco `case`. Embora útil, o padrão original ISO 7185 não definia um comportamento para valores não mapeados.
*   **Diretivas de Sub-rotinas:** Faltam diretivas adicionais além de `forward`, como `external` ou modificadores de visibilidade.

## 5. Ordem de Declarações
*   **Rigidez de Blocos:** O Pascalm impõe uma ordem estrita para `label`, `const`, `type` e `var`. Gramáticas mais modernas e flexíveis permitem que essas seções sejam intercaladas ou repetidas conforme a necessidade.

---
*Documento gerado para análise de evolução do compilador Pascalm.*
