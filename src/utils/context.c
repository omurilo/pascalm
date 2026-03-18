#include "context.h"
#include <stdlib.h>
#include <assert.h>
#include "logger.h"
#include "memory.h"

ScopeStack *scope_stack_create() {
  ScopeStack *stack = xalloc(1, sizeof(ScopeStack));
  stack->capacity = 8;
  stack->tables = xalloc(stack->capacity, sizeof(ht *));
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

void scope_stack_push_table(ScopeStack *stack, ht *table) {
  stack->scope_level++;
  if (stack->scope_level >= stack->capacity) {
    stack->capacity *= 2;
    stack->tables = realloc(stack->tables, stack->capacity * sizeof(ht *));
  }
  stack->tables[stack->scope_level] = table;
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

ASTNode **with_stack_create(CompilerContext *context) {
  context->with_stack_capacity = 8;
  context->with_stack =
      xalloc(context->with_stack_capacity, sizeof(ASTNode *));
  context->with_stack_top = 1;
  return context->with_stack;
}

void with_stack_push(CompilerContext *context, ASTNode *entry) {
  if (!context->with_stack)
    with_stack_create(context);
  if (context->with_stack_top >= context->with_stack_capacity) {
    context->with_stack_capacity *= 2;
    context->with_stack =
        realloc(context->with_stack,
                context->with_stack_capacity * sizeof(ASTNode *));
  }
  context->with_stack[context->with_stack_top] = entry;
  context->with_stack_top++;
}

ASTNode *with_stack_pop(CompilerContext *context) {
  if (context->with_stack_top > 0) {
    // free(context->with_stack[context->with_stack_top]);
    context->with_stack_top--;
    return context->with_stack[context->with_stack_top];
  }
  return NULL;
}

ASTNode *with_stack_peek(CompilerContext *context) {
  if (context->with_stack_top > 0) {
    return context->with_stack[context->with_stack_top - 1];
  }
  return NULL;
}

CompilerContext *context_create() {
  CompilerContext *context = xalloc(1, sizeof(CompilerContext));
  context->scope_stack = scope_stack_create();
  context->current_function = NULL;
  context->has_errors = false;
  context->with_stack = NULL;
  context->with_stack_capacity = 0;
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
      yyerrorf(entry->location,
               "Error: Symbol (%s) already declared in this scope (%d)", key,
               context->scope_stack->scope_level);
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

void context_insert_field(CompilerContext *context,
                          SymbolEntry *record_type_symbol,
                          SymbolEntry *field_symbol) {
  assert(record_type_symbol->kind == SYMBOL_TYPE);
  assert(field_symbol->kind == SYMBOL_FIELD);

  if (record_type_symbol->info.type_info.fields == NULL) {
    record_type_symbol->info.type_info.fields = ht_create();
  }

  ht *fields_table = record_type_symbol->info.type_info.fields;

  if (ht_get(fields_table, field_symbol->name) != NULL) {
    yyerrorf(record_type_symbol->location,
             "Error: Field '%s' already declared in record '%s'",
             field_symbol->name, record_type_symbol->name);
    context->has_errors = true;
  }

  ht_set(fields_table, field_symbol->name, field_symbol);
}

SymbolEntry *context_lookup_field(ht *table, const char *key) {
  SymbolEntry *entry = ht_get(table, key);
  if (entry != NULL)
    return entry;
  return NULL;
}
