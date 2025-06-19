#include "context.h"
#include <stdlib.h>

ScopeStack *scope_stack_create() {
  ScopeStack *stack = malloc(sizeof(ScopeStack));
  stack->capacity = 8;
  stack->tables = malloc(stack->capacity * sizeof(ht *));
  stack->scope_level = -1;
  return stack;
}

void scope_stack_destroy(ScopeStack *stack) {
  for (int i = 0; i <= stack->scope_level; i++) {
    ht_destroy(stack->tables[i]);
  }
  free(stack->tables);
  free(stack);
}

void scope_stack_push(ScopeStack *stack) {
  stack->scope_level++;
  if (stack->scope_level >= stack->capacity) {
    stack->capacity *= 2;
    stack->tables = realloc(stack->tables, stack->capacity * sizeof(ht *));
  }
  stack->tables[stack->scope_level] = ht_create();
}

void scope_stack_pop(ScopeStack *stack) {
  if (stack->scope_level >= 0) {
    ht_destroy(stack->tables[stack->scope_level]);
    stack->scope_level--;
  }
}

ht *scope_stack_peek(ScopeStack *stack) {
  if (stack->scope_level >= 0) {
    return stack->tables[stack->scope_level];
  }
  return NULL;
}

CompilerContext *context_create() {
  CompilerContext *context = malloc(sizeof(CompilerContext));
  context->scope_stack = scope_stack_create();
  scope_stack_push(context->scope_stack);
  return context;
}

void context_destroy(CompilerContext *context) {
  scope_stack_destroy(context->scope_stack);
  free(context);
}

// --- Funções Semânticas ---

void context_insert(CompilerContext *context, const char *key,
                    SymbolEntry *entry) {
  ht *current_scope_table = scope_stack_peek(context->scope_stack);
  if (current_scope_table) {
    if (ht_get(current_scope_table, key) != NULL) {
      char err[255];
      sprintf(err, "Error: Symbol (%s) already declared in this scope (%d)", key, context->scope_stack->scope_level);
      yyerror(err);
    }
    ht_set(current_scope_table, key, entry);
  }
}

SymbolEntry *context_lookup(CompilerContext *context, const char *key) {
  for (int i = context->scope_stack->scope_level; i >= 0; i--) {
    SymbolEntry *entry = ht_get(context->scope_stack->tables[i], key);
    if (entry != NULL) {
      return entry;
    }
  }
  return NULL;
}
