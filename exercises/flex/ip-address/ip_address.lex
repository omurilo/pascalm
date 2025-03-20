DIGIT [0-9]
OCTET {DIGIT}{1,2}|1{DIGIT}{1,2}|2[0-4][0-9]|25[0-5]
IP_ADDRESS  {OCTET}\.{OCTET}\.{OCTET}\.{OCTET}

%{
FILE *yyin;
%}

%%
{IP_ADDRESS} { printf("Valid ip: %s\n", yytext); }
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
