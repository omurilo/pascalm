#!/bin/bash

# Script para compilar o projeto Pascal-para-C sem make

# Etapa 1: Gerar fontes do Bison e Flex
echo "Gerando parser e lexer..."
bison -d -o parser/parser.tab.c parser/parser.y
flex -o parser/lex.yy.c parser/parser.l

# Etapa 2: Compilar tudo com GCC
echo "Compilando o projeto..."
gcc -g -Wall -o compilador \
    main.c \
    context.c \
    ast/ast.c \
    symbol-table/symbol-table.c \
    semantic-analyzer/analyzer.c \
    code-generation/code.c \
    code-generation/utils.c \
    parser/parser.tab.c \
    parser/lex.yy.c \
    -lfl -lm

# Verifica se a compilação foi bem-sucedida
if [ $? -eq 0 ]; then
    echo "Compilação concluída com sucesso! Executável 'compilador' criado."
else
    echo "Erro na compilação."
fi
