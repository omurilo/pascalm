#ifndef CONTEXT_H
#define CONTEXT_H

#include "symbol-table/symbol-table.h"

typedef struct {
  ht **tables;
  int scope_level;
  int capacity;
} ScopeStack;

typedef struct {
  ScopeStack *scope_stack;
  SymbolEntry *current_function;
  bool has_errors;
} CompilerContext;

CompilerContext *context_create(void);
void context_destroy(CompilerContext *context);

void scope_stack_push(ScopeStack *stack);
void scope_stack_pop(ScopeStack *stack);
ht *scope_stack_peek(ScopeStack *stack);

SymbolEntry *context_lookup(CompilerContext *context, const char *key);
void context_insert(CompilerContext *context, const char *key,
                    SymbolEntry *entry);

void context_insert_field(CompilerContext *context, SymbolEntry *record_type_symbol, SymbolEntry *field_symbol);
SymbolEntry *context_lookup_field(ht *table, const char *key);
#endif
