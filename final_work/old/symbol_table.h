#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "final_work_types.h"

static Symbol symb_table[100];
static int symb_count = 0;

Symbol* add_symbol(char *id, SymbolKind kind, TypeInfo *type, SymbolValue value, Param *params, Symbol *next);
int get_symbol_index(const char* id);
Symbol* get_symbol_by_name(const char* name);

#endif
