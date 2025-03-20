NEW_PLATE [A-Z]{3}[0-9]{1}[A-Z]{1}[0-9]{2}
PLATE [A-Z]{3}-[0-9]{4}

%{
FILE *yyin;
%}

%%
{PLATE}|{NEW_PLATE} { printf("Valid plate: %s\n", yytext); }
.|[\n] { continue; }
%%

int yywrap();

int main(int argc, char **argv) {
  yyin = fopen(argv[1], "r");
  yylex();
  fclose(yyin);
  return 0;
}

int yywrap() {
  return 1;
}
