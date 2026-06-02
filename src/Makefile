# ==============================================================================
# Pascalm Compiler - Rust Makefile
# ==============================================================================
# Refactored for Rust implementation using Cargo and LLVM.

# ------------------------------------------------------------------------------
# Configuration
# ------------------------------------------------------------------------------

# Cargo and Binary configuration
CARGO      := cargo
PROJECT    := pascalm

# Library path for local dependencies (like libzstd.so)
export LIBRARY_PATH := $(shell pwd)/../lib:$(LIBRARY_PATH)
# Target binary path relative to the root (where Cargo.toml usually is)
# From src/ directory, cargo will find the parent Cargo.toml automatically.

# Default test settings
FILE       ?= examples/parameters.pascalm
OUTPUT     ?= output
FLAGS      ?= 

# Aesthetic colors for output
CYAN       := \033[0;36m
GREEN      := \033[0;32m
YELLOW     := \033[0;33m
RED        := \033[0;31m
BOLD       := \033[1m
RESET      := \033[0m

# ------------------------------------------------------------------------------
# Primary Targets
# ------------------------------------------------------------------------------

.PHONY: all build release run test clean fmt clippy help

all: build

## build: Build the project in debug mode
build:
	@printf "$(CYAN)▶ Building $(PROJECT)...$(RESET)\n"
	@$(CARGO) build

## release: Build the project in release mode
release:
	@printf "$(CYAN)▶ Building $(PROJECT) (release)...$(RESET)\n"
	@$(CARGO) build --release

## run: Run the compiler on a specific file (e.g., make run FILE=examples/test.pascalm)
run:
	@printf "$(CYAN)▶ Running $(PROJECT) on $(FILE)...$(RESET)\n"
	@$(CARGO) run -- --file $(FILE) --output $(OUTPUT) $(FLAGS)
	@if [ -f "$(OUTPUT)" ]; then printf "$(GREEN)✔ Executable '$(OUTPUT)' generated successfully.$(RESET)\n"; fi

## test: Run unit tests
test:
	@printf "$(CYAN)▶ Running Rust tests...$(RESET)\n"
	@$(CARGO) test

## clean: Remove build artifacts and temporary files
clean:
	@printf "$(YELLOW)▶ Cleaning up...$(RESET)\n"
	@$(CARGO) clean
	@rm -f *.ll *.bc *.o $(OUTPUT)
	@printf "$(GREEN)✔ Cleaned.$(RESET)\n"

## fmt: Format the source code using rustfmt
fmt:
	@printf "$(CYAN)▶ Formatting code...$(RESET)\n"
	@$(CARGO) fmt

## clippy: Run clippy linter for code quality
clippy:
	@printf "$(CYAN)▶ Running Clippy...$(RESET)\n"
	@$(CARGO) clippy -- -D warnings

# ------------------------------------------------------------------------------
# Documentation & Help
# ------------------------------------------------------------------------------

## help: Show this help message
help:
	@printf "$(BOLD)Pascalm Compiler - Makefile$(RESET)\n"
	@echo ""
	@echo "Usage:"
	@echo "  make <target> [FILE=<path>] [OUTPUT=<name>]"
	@echo ""
	@echo "Targets:"
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "  $(CYAN)%-12s$(RESET) %s\n", $$1, $$2}'
	@echo ""
	@echo "Examples:"
	@echo "  make run FILE=examples/controls.pascalm"
	@echo "  make test"
	@echo "  make clean"
