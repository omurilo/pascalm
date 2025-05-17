#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "types.h"

static Symbol symb_table[100];
static int symb_count = 0;

int add_symbol(char* id, SymbolKind kind, struct TypeInfo *type);
int get_symbol_index(const char* id);
Symbol* get_symbol_by_name(const char* name);

#endif
