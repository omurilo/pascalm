#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "memory.h"

char *process_string_literal(char *text) {
  int len = strlen(text);
  char *value = xalloc(len, sizeof(char *));

  int j = 0;
  for (int i = 1; i < len - 1; i++) {
    if (text[i] == '\'' && i + 1 < len - 1 && text[i + 1] == '\'') {
      /* '' → ' (escape de aspas simples no estilo Pascal) */
      value[j++] = '\'';
      i++;
    } else if (text[i] == '\\' && i + 1 < len - 1) {
      /* sequências de escape estilo C dentro de strings PascalM */
      i++;
      switch (text[i]) {
        case 'n':  value[j++] = '\n'; break;
        case 'r':  value[j++] = '\r'; break;
        case 't':  value[j++] = '\t'; break;
        case '\\': value[j++] = '\\'; break;
        case '\'': value[j++] = '\''; break;
        case '0':  value[j++] = '\0'; break;
        default:
          /* sequência desconhecida: mantém o backslash e o char */
          value[j++] = '\\';
          value[j++] = text[i];
          break;
      }
    } else {
      value[j++] = text[i];
    }
  }
  value[j] = '\0';
  return value;
}
