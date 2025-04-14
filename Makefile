SHELL := /bin/bash

LD=g++
TARGET=$(shell basename $(PWD))
FLEX=flex
BISON=bison

FG_BLACK :=\033[30m

BG_RED := \033[101m
BG_GREEN := \033[42m
BG_YELLOW := \033[43m
NC=\033[0m

.PHONY: all clean

all: build run test clean

build: $(TARGET).tab.c lex.yy.c
	@$(LD) -o $(TARGET) $?
	@printf "✅$(BG_GREEN)$(FG_BLACK) Build program finish $(NC)\n"

run: $(TARGET).test.txt build
	@printf "$(BG_YELLOW)$(FG_BLACK) Run program $(NC)\n"
	@./$(TARGET) < $< > $(TARGET).output
	@cat $(TARGET).output

test: $(TARGET).output.txt run
	@printf "$(BG_YELLOW)$(FG_BLACK) Test program and compare output $(NC)\n"
	@
	@if diff_output=$$(diff $(TARGET).output $<); then \
		printf  "✅$(BG_GREEN)$(FG_BLACK) Test sucessful $(NC)\n"; \
	else \
		printf  "❌$(BG_RED)$(FG_BLACK) Test error $(NC)\n"; \
		echo "$$diff_output"; \
		exit 1; \
	fi

$(filter %.tab.c,$(TARGET).y): %.tab.c: %.y
	@printf  "$(RED)target: $@ prereq: $<$(NC)"

%.tab.c: $(TARGET).y
	@$(BISON) -o $@ -H $< -Wcounterexamples

lex.yy.c: $(TARGET).lex $(TARGET).tab.c
	@$(FLEX) $<

clean:
	@rm -rf $(TARGET).output $(TARGET)
	@printf  "✅$(BG_GREEN)$(FG_BLACK) Files cleaned $(NC)\n"
