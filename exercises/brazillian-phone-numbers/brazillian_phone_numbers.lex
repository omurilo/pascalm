PHONE [\(]?[0-9]{2}[\)]?[\ ]*[0-9]{4,5}-?[0-9]{4}

%%
{PHONE} { printf("Valid phone number: %s\n", yytext); }
. { continue; }
%%

int yywrap();

int main(int argc, char *argv[]) {
  yyin = fopen(argv[1], "r");
  yylex();
  fclose(yyin);
}

int yywrap() {
  return 1;
}
