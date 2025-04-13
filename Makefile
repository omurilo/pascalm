LD=g++
TARGET=$(shell basename $(PWD))
FLEX=flex
BISON=bison
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

.PHONY: all clean

all: build run test clean

build: $(TARGET).tab.c lex.yy.c
	@$(LD) -o $(TARGET) $?
	@echo "✅ \033[0;46m\033[30mBuild program finish\033[m"

run: $(TARGET).test.txt build
	@echo "Run program"
	@./$(TARGET) < $< > $(TARGET).output
	@cat $(TARGET).output

test: $(TARGET).output.txt run
	@echo "Test program and compare output"
	@
	@if diff_output=$$(diff $(TARGET).output $<); then \
		echo "✅ \033[0;46m\033[30mTest sucessful\033[m\033[m"; \
	else \
		echo "❌ \033[0;41m\033[30mTest error\033[m\033[m"; \
		echo "$$diff_output"; \
		exit 1; \
	fi

$(filter %.tab.c,$(TARGET).y): %.tab.c: %.y
	echo "target: $@ prereq: $<"

%.tab.c: $(TARGET).y
	@$(BISON) -o $@ -H $< -Wcounterexamples

lex.yy.c: $(TARGET).lex $(TARGET).tab.c
	@$(FLEX) $<

clean:
	@rm -rf $(TARGET).output $(TARGET)
	@echo "✅ \033[0;46m\033[30mFiles cleaned\033[m"
