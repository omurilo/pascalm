#include "symbol_table.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int add_symbol(char *id, SymbolKind skind, struct TypeInfo *type) {
  for (int i = 0; i < symb_count; i++) {
    if (strcmp(symb_table[i].name, id) == 0) {
      return i;
    }
  }

  Symbol *sym = &symb_table[symb_count];
  sym->name = strdup(id);
  sym->skind = skind;
  sym->type = type;
  sym->name[sizeof(sym->name) - 1] = '\0';
  return symb_count++;
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
