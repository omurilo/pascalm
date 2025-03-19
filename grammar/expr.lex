%{
  FILE *out ;
%}
%option yylineno
%x COMMENT

%%
{number}+ {
            printf("Number %s", yytext);
          }
if|func|for|else  {
                    printf("Reserved functions %s", yytext);
                  }

. printf("Unrecognized character: %s\n", yytext);
%%

int yywrap();

int main() {
  yylex();
}

int yywrap() {
  return 1;
}
