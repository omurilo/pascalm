#include "final_work.tab.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *msg) {
  fprintf(stderr, "Error: %s at %d.%d-%d.%d\n", msg, yylloc.first_line,
          yylloc.first_column, yylloc.last_line, yylloc.last_column);
}

int main(int argc, char **argv) {
  if (argc > 1) {
    yylloc.file_name = argv[1];
    yyin = fopen(argv[1], "r");
    if (!yyin) {
      perror("Error open file");
      return 1;
    }
  } else {
    yyin = stdin;
    yylloc.file_name = "stdin";
  }
  yylloc.first_column = 1;
  yylloc.first_line = 1;
  yylloc.last_column = 1;
  yylloc.last_line = 1;

  yyparse();

  if (yyin != stdin) {
    fclose(yyin);
  }

  return 0;
}

const char *getTypeString(const struct TypeInfo *type) {
  if (type->kind >= 0 && type->kind < KIND__COUNT) {
    return KindNames[type->kind];
  }
  return "unknown";
}

const char *describeType(const struct TypeInfo *type) {
  switch (type->kind) {
  case KIND_ARRAY: {
    static char buf[64];
    /* imagina que TypeInfo tem campo .elem */
    snprintf(buf, sizeof buf, "array of %s",
             getTypeString(type->arrayInfo.type));
    return buf;
  }
  case KIND_RECORD:
    static char buf[128];
    snprintf(buf, sizeof buf, "record\nfields:");
    for (struct Field *it = type->recordFields; it != NULL; it = it->next) {
      snprintf(buf, sizeof buf, "%s\n %s of type %s", buf, it->name,
               getTypeString(it->type));
    };
    return buf;
  default:
    return getTypeString(type);
  }
}
