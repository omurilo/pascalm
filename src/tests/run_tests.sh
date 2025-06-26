#!/bin/bash

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

total_tests=0
failed_tests=0
failure_log=""

log_failure() {
  local test_name=$1
  local reason=$2
  local details=$3

  failed_tests=$((failed_tests + 1))
  failure_log+="\n${YELLOW}-[Fail] Test: ${test_name}${NC}\n"
  failure_log+="\t${RED}Reason: ${reason}${NC}\n"

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
    
    # Compila o PascalM para C
    "$COMPILER" -f "${test_dir}test.pascalm" -o "${test_dir}generated.c" 2> /dev/null
    
    # Compila o C gerado para um executável
    gcc -w "${test_dir}generated.c" -o "${test_dir}program" 2> /dev/null
    
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
        diff_output=$(diff -w --label="Actual Output" --label="Golden Output" "${test_dir}actual.out" "${test_dir}output.golden")
        log_failure "${test_name}" "The output of program doesnt match with expected." "$diff_output"
    fi
    rm -f "${test_dir}generated.c" "${test_dir}program" "${test_dir}actual.out"
done

echo "Running COMPILE_ERROR tests..."
for test_dir in compile_error/*/; do
    total_tests=$((total_tests + 1))
    test_name=$(basename "$test_dir")
    echo -n "  [TEST] $test_name..."

    # Roda o compilador esperando um erro (código de saída != 0) e captura stderr
    if ! "$COMPILER" "${test_dir}test.pascalm" 2> "${test_dir}actual.err"; then
        # Compara a saída de erro com a esperada
        if diff -w "${test_dir}actual.err" "${test_dir}error.golden" > /dev/null; then
            echo -e " ${GREEN}PASS${NC}"
        else
            echo -e " ${RED}FAIL (wrong error message)${NC}"
            echo -e " ${RED}FAIL${NC}"
            diff_output=$(diff -w --label="Actual Error" --label="Error Expected" "${test_dir}actual.err" "${test_dir}error.golden")
            log_failure "${test_name}" "The message of compile error doesnt match the expected." "$diff_output"
        fi
    else
        echo -e " ${RED}FAIL (should have failed to compile)${NC}"
        log_failure "$test_name" "The compiler should be return error, but compilation succeded." ""
    fi
    rm -f "${test_dir}actual.err"
done

echo "-----------------------------------------------------"
if [ $failed_tests -gt 0 ]; then
    echo -e "${RED}RESULT: FAIL${NC}"
    echo -e "Failed ${failed_tests} of ${total_tests} tests.\n"
    echo -e "--- ERROR LOGS ---"
    echo -e "${failure_log}"
    exit 1
else
    echo -e "${GREEN}RESULT: SUCCESS${NC}"
    echo "All of ${total_tests} tests Pass! Calm!"
    exit 0
fi
