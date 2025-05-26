#include "ast/ast.h"
#include "symbol-table/symbol-table.h"
#include "parser/types.h"
#include "parser/parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#if YYDEBUG
extern int yydebug;
#endif

extern struct ASTNode *root;
extern struct ht *HashTable;

void yyerror(const char *msg) {
  fprintf(stderr, "%s:%d.%d-%d.%d: error: %s\n",
          yylloc.file_name ? yylloc.file_name : "input", yylloc.first_line,
          yylloc.first_column, yylloc.last_line, yylloc.last_column, msg);
}

ht *HashTable = NULL;

int main(int argc, char **argv) {
  if (argc > 1) {
    yyin = fopen(argv[1], "r");
    if (!yyin) {
      perror("Error open file");
      return 1;
    }
    yylloc.file_name = strdup(argv[1]);
  } else {
    yyin = stdin;
    yylloc.file_name = (char *)"stdin";
  }
  yylloc.first_column = 1;
  yylloc.first_line = 1;
  yylloc.last_column = 1;
  yylloc.last_line = 1;

  HashTable = ht_create();
  if (HashTable == NULL) {
    yyerror((char *)"OUT OF MEMORY");
  }

  yyparse();

  if (yyin != stdin) {
    fclose(yyin);
    free((void *)yylloc.file_name);
  }

  if (root) {
    printf("AST construída com sucesso:\n");
    root->print(root, 0);
    free_node(root);
  }

  ht_destroy(HashTable);

  return 0;
}
