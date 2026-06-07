#!/bin/bash

# Configuration
COMPILER_DIR="src"
TESTS_DIR="src/tests/success"
LOCAL_LIBS="$PWD/lib"
LLVM_PREFIX="/usr/lib/llvm-18"

export LIBRARY_PATH="$LOCAL_LIBS:/usr/lib/x86_64-linux-gnu"
export LLVM_SYS_180_PREFIX="$LLVM_PREFIX"
export LLVM_SYS_180_BUILD_SHARED=1

# Colors
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

echo "Building compiler..."
cd $COMPILER_DIR && cargo build --quiet
if [ $? -ne 0 ]; then
  echo -e "${RED}Failed to build compiler${NC}"
  exit 1
fi
cd ..

passed=0
failed=0

for test_dir in $TESTS_DIR/*; do
  if [ -d "$test_dir" ]; then
    test_file="$test_dir/test.pascalm"
    test_name=$(basename "$test_dir")

    echo -n "Running test $test_name... "

    # Run compiler
    ./target/debug/pascalm --file "$test_file" --output "test.ll" >/dev/null 2>&1

    if [ $? -eq 0 ]; then
      if [ -f "test.ll" ]; then
        echo -e "${GREEN}PASSED (Codegen)${NC}"
        passed=$((passed + 1))
        rm "test.ll"
      else
        echo -e "${RED}FAILED (IR not found)${NC}"
        failed=$((failed + 1))
      fi
    else
      echo -e "${RED}FAILED (Compile error)${NC}"
      failed=$((failed + 1))
    fi
  fi
done

echo "--------------------------"
echo "Results: $passed passed, $failed failed"
