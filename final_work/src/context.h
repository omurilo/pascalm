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
} CompilerContext;

CompilerContext *context_create(void);
void context_destroy(CompilerContext *context);

void scope_stack_push(ScopeStack *stack);
void scope_stack_pop(ScopeStack *stack);
ht *scope_stack_peek(ScopeStack *stack);

SymbolEntry *context_lookup(CompilerContext *context, const char *key);
void context_insert(CompilerContext *context, const char *key,
                    SymbolEntry *entry);

#endif
