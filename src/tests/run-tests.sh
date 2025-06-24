#!/bin/bash

# Para o script ao primeiro erro
set -e

# Cores para o output
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # Sem Cor

# Argumento: caminho para o executável do compilador
COMPILER=$1
if [ -z "$COMPILER" ]; then
    echo "Usage: ./run_tests.sh <path_to_compiler>"
    exit 1
fi

echo "Running SUCCESS tests..."
for test_dir in success/*/; do
    test_name=$(basename "$test_dir")
    echo -n "  [TEST] $test_name..."
    
    # Compila o PascalM para C
    "$COMPILER" -f "${test_dir}test.pascalm" -o "${test_dir}generated.c"
    
    # Compila o C gerado para um executável
    gcc "${test_dir}generated.c" -o "${test_dir}program"
    
    # Roda o programa e captura a saída
    if [ -f "${test_dir}input.txt" ]; then
        ./"${test_dir}program" < "${test_dir}input.txt" > "${test_dir}actual.out"
    else
        ./"${test_dir}program" > "${test_dir}actual.out"
    fi
    
    # Compara a saída real com a esperada (golden)
    if diff -w "${test_dir}actual.out" "${test_dir}output.golden" > /dev/null; then
        echo -e " ${GREEN}PASS${NC}"
    else
        echo -e " ${RED}FAIL${NC}"
        echo "------- Diff: -------"
        diff -w "${test_dir}actual.out" "${test_dir}output.golden"
        echo "---------------------"
        exit 1
    fi
    rm -f "${test_dir}generated.c" "${test_dir}program" "${test_dir}actual.out"
done

echo "Running COMPILE_ERROR tests..."
for test_dir in compile_error/*/; do
    test_name=$(basename "$test_dir")
    echo -n "  [TEST] $test_name..."

    # Roda o compilador esperando um erro (código de saída != 0) e captura stderr
    if ! "$COMPILER" "${test_dir}test.pascalm" 2> "${test_dir}actual.err"; then
        # Compara a saída de erro com a esperada
        if diff -w "${test_dir}actual.err" "${test_dir}error.golden" > /dev/null; then
            echo -e " ${GREEN}PASS${NC}"
        else
            echo -e " ${RED}FAIL (wrong error message)${NC}"
            echo "------- Diff: -------"
            diff -w "${test_dir}actual.err" "${test_dir}error.golden"
            echo "---------------------"
            exit 1
        fi
    else
        echo -e " ${RED}FAIL (should have failed to compile)${NC}"
        exit 1
    fi
    rm -f "${test_dir}actual.err"
done

# (Opcional) Adicione aqui a lógica para os testes de runtime_error

echo -e "\n${GREEN}All tests passed!${NC}"
exit 0
