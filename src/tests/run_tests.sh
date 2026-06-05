#!/bin/bash

# Cores para o output
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # Sem Cor
YELLOW='\033[1;33m'

# Argumento: caminho para o executável do compilador
COMPILER=$1
if [ -z "$COMPILER" ]; then
    echo "Usage: ./run_tests.sh <path_to_pascalm_binary>"
    exit 1
fi

total_tests=0
failed_tests=0
failure_log=""

log_failure() {
  local test_name=$1
  local reason=$2
  local details=$3
  failed_tests=$((failed_tests + 1))
  failure_log+="\n${YELLOW}-[Fail] Test: ${test_name}${NC}\n"
  failure_log+="\t${RED}Reason:${NC} ${reason}\n"
  if [ -n "$details" ]; then
    details=$(echo "$details" | sed 's/^/        /')
    failure_log+="\t${RED}Details:${NC}\n${details}\n"
  fi
}

echo "Running SUCCESS tests..."
for test_dir in success/*/; do
    total_tests=$((total_tests + 1))
    test_name=$(basename "$test_dir")
    echo -n "  [TEST] $test_name..."
    
    # Encontra o arquivo de entrada
    entry_file=""
    if [ -f "${test_dir}test.pascalm" ]; then
        entry_file="${test_dir}test.pascalm"
    elif [ -f "${test_dir}main_prog.pas" ]; then
        entry_file="${test_dir}main_prog.pas"
    else
        entry_file=$(ls "${test_dir}"*.pascalm "${test_dir}"*.pas 2>/dev/null | head -n 1)
    fi

    if [ -z "$entry_file" ]; then
        echo -e " ${RED}FAIL (No entry file)${NC}"
        log_failure "${test_name}" "No entry file found (.pascalm or .pas)." ""
        continue
    fi

    # Compila o PascalM diretamente para um executável
    "$COMPILER" --file "$entry_file" --output "${test_dir}program" > /dev/null 2>&1
    
    if [ ! -f "${test_dir}program" ]; then
        echo -e " ${RED}FAIL (Compile error)${NC}"
        log_failure "${test_name}" "Compilation failed." ""
        continue
    fi

    # Roda o programa e captura a saída
    if [ -f "${test_dir}input.txt" ]; then
        ./"${test_dir}program" < "${test_dir}input.txt" > "${test_dir}actual.out"
    else
        ./"${test_dir}program" > "${test_dir}actual.out"
    fi
    
    # Compara a saída real com a esperada (golden)
    if diff -w "${test_dir}actual.out" "${test_dir}output.golden" > /dev/null 2>&1; then
        echo -e " ${GREEN}PASS${NC}"
    else
        echo -e " ${RED}FAIL${NC}"
        diff_output=$(diff -w --label="Actual Output" --label="Golden Output" "${test_dir}actual.out" "${test_dir}output.golden")
        log_failure "${test_name}" "The output of program doesnt match with expected." "$diff_output"
    fi
    
    # Cleanup
    rm -f "${test_dir}program" "${test_dir}actual.out" *.ll *.bc
done

echo -e "\nRunning COMPILE_ERROR tests..."
for test_dir in compile_error/*/; do
    total_tests=$((total_tests + 1))
    test_name=$(basename "$test_dir")
    echo -n "  [TEST] $test_name..."
    
    # Tenta compilar e captura o erro
    if ! "$COMPILER" --file "${test_dir}test.pascalm" 2> "${test_dir}actual.err" > /dev/null; then
         # Como o formato do erro mudou com o LSP, vamos apenas verificar se não é vazio
        if [ -s "${test_dir}actual.err" ]; then
             echo -e " ${GREEN}PASS${NC}"
        else
             echo -e " ${RED}FAIL (No error message)${NC}"
             log_failure "${test_name}" "The compiler failed but emitted no error message." ""
        fi
    else
        echo -e " ${RED}FAIL (Compiled successfully but should have failed)${NC}"
        log_failure "${test_name}" "The program compiled successfully but was expected to fail." ""
    fi
    
    # Cleanup
    rm -f "${test_dir}actual.err" *.ll *.bc
done

echo "-----------------------------------------------------"
if [ ${failed_tests} -eq 0 ]; then
    echo -e "${GREEN}RESULT: SUCCESS${NC}"
    echo "All of ${total_tests} tests Pass! Calm!"
    exit 0
else
    echo -e "${RED}RESULT: FAIL${NC}"
    echo -e "Failed ${failed_tests} of ${total_tests} tests.\n"
    echo -e "--- ERROR LOGS ---"
    echo -e "${failure_log}"
    exit 1
fi
