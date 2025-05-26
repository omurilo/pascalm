#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "../commons.h"

typedef struct ht ht;

ht *ht_create(void);

void ht_destroy(ht *table);

SymbolEntry *ht_get(ht *table, const char *key);

const char *ht_set(ht *table, const char *key, SymbolEntry *value);

size_t ht_length(ht *table);

typedef struct {
  const char *key;
  SymbolEntry *value;
  ht *_table;
  size_t _index;
} hti;

hti ht_iterator(ht *table);
bool ht_next(hti *it);

SymbolEntry *create_symbol_entry(char *name, SymbolKind kind, int scope_level,
                                 SourceLocation loc);

#endif
