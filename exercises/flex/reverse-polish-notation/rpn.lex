DIGIT [0-9]

%{
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    double v;
    struct node *next;
} Node;

Node *stack = NULL;
void push(Node **stack, double val);
int pop(Node **stack, double *val);
void checkStack(int a, int b);

FILE *yyin;
%}

%%
{DIGIT}+(\.{DIGIT}*)? {
  double a = atof(yytext);
  printf("%f", a);
  push(&stack, a);
}
[+] {
  printf("%s\n", yytext);
  double a, b;
  checkStack(pop(&stack, &a), pop(&stack, &b));
  double c = b + a;
  printf("%f", c);
  push(&stack, c);
}
[-] {
  printf("%s\n", yytext);
  double a, b;
  checkStack(pop(&stack, &a), pop(&stack, &b));
  double c = b -a;
  printf("%f", c);
  push(&stack, c);
}
[*] {
  printf("%s\n", yytext);
  double a, b;
  checkStack(pop(&stack, &a), pop(&stack, &b));
  double c = b*a;
  printf("%f", c);
  push(&stack, c);
}
[/] {
  printf("%s\n", yytext);
  double a, b;
  checkStack(pop(&stack, &a), pop(&stack, &b));
  double c = b / a;
  printf("%f", c);
  push(&stack, c);
}
. {
  printf("Invalid operation or symbol\n");
  exit(1);
}
%%

void push( Node **stack, double val )
{
    Node *p = malloc( sizeof( Node ) );

    if (p != NULL)
    {
        p->v = val;
        p->next = *stack;
        *stack = p;
    }
}

int pop( Node **stack, double *val )
{
    if (*stack != NULL)
    {
      Node *p = *stack;
      *stack = ( *stack )->next;
      *val = p->v;
      free(p);
      return 1;
    }       
    return 0;
}

void checkStack(int a, int b) {
  if (a && b){
    return;
  } else {
    printf("Erro: pilha insuficiente para operação\n");
    exit(1);
  }
}

int main(int argc, char **argv) {
  yyin = fopen(argv[1], "r");
  yylex();
  fclose(yyin);
  return 0;
}

int yywrap() {
  return 1;
}
