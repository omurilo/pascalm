#include "symbol_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Symbol* add_symbol(char *id, SymbolKind kind, TypeInfo *type, SymbolValue value, Param *params, Symbol *next) {
  for (int i = 0; i < symb_count; i++) {
    if (strcmp(symb_table[i].name, id) == 0) {
      return NULL;
    }
  }

  Symbol *sym = &symb_table[symb_count];
  sym->name = strdup(id);
  sym->kind = kind;
  sym->type = type;
  sym->params = params;
  sym->value = value;
  sym->next = next;
  sym->name[sizeof(sym->name) - 1] = '\0';
  symb_count++;
  return sym;
}

int get_symbol_index(const char *id) {
  for (int i = 0; i < symb_count; i++) {
    if (strcmp(symb_table[i].name, id) == 0) {
      return i;
    }
  }
  return -1;
}

Symbol *get_symbol_by_name(const char *id) {
  int i = get_symbol_index(id);
  if (i == -1) {
    fprintf(stderr, "Error: undeclared variable '%s'\n", id);
    exit(1);
  }

  return &symb_table[i];
}
