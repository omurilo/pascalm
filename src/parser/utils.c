#include <stdlib.h>
#include <strings.h>
#include <stdio.h>
#include "../memory.h"

char *process_string_literal(char *text) {
  int len = strlen(text);
  char *value = xalloc(len, sizeof(char *));

  int j = 0; 
  for (int i = 1; i < len - 1; i++) {
    if (text[i] == '\'' && i + 1 < len - 1 && text[i + 1] == '\'') {
      value[j++] = '\'';
      i++;
    } else {
      value[j++] = text[i];
    }
  }
  value[j] = '\0'; 
  return value;
}
