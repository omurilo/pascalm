#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    unsigned char length;
    char data[255];
} string;

string make_string(const char* c_str);
string concat_string(string s1, string s2);

int MAX = 0;
int MIN = 0;

typedef struct {
    string nome;
    int nota;
} TAluno;


int i = 0;
int soma = 0;
TAluno alunos[5];
int opt = 0;
double resultado;
string str;

string make_string(const char* c_str) {
    string ps;
    ps.length = strlen(c_str);
    if(ps.length > 255) ps.length = 255;
    strncpy(ps.data, c_str, ps.length);
    return ps;
}

string concat_string(string s1, string s2) {
    string result;
    result.length = s1.length + s2.length;
    if(result.length > 255) result.length = 255;
    memcpy(result.data, s1.data, s1.length);
    memcpy(result.data + s1.length, s2.data, result.length - s1.length);
    return result;
}

int Dobro(int x){
    return (x * 2);
}

double AplicarOperacao(double x, double y, double op(double a, double b));

double Multiplicar(double a, double b){
    return (a * b);
}

void ImprimeAluno(TAluno a){
    printf("%s: %d", a.nome, a.nota);
}

void ExecutarOperacao(int x, int y, void operacao(int a, int b)){
    operacao(x, y);
}

void Somar(int a, int b){
    printf("%d\n", (a + b));
}

double AplicarOperacao(double x, double y, double op(double a, double b)){
    return op(x, y);
}

char Chr(int n){
    return n;
}

int main() {
    soma = 0;
    for (i = MIN; i <= MAX; i++) {
        memcpy(&alunos[i - 0].nome, &("Aluno" +         Chr((48 + i));
), sizeof(alunos[i - 0].nome));
        alunos[i - 0].nota = (i * 10);
        soma = (soma + alunos[i - 0].nota);
    }
    for (i = MAX; i >= MIN; i--) {
        printf("%d\n", i);
    }
    opt = Dobro(soma);
;
    resultado = AplicarOperacao(4.50, 2.00, Multiplicar);
;
    printf("%.2f\n", resultado);
    ExecutarOperacao(5, 3, Somar);
/* case or case else */
    printf("\n");
    printf("Imprimindo lista de alunos:");
    printf("\n");
    i = 1;
    while ((i <= MAX)) {
        ImprimeAluno(alunos[i - 0]);
        printf("\n");
        i = (i + 1);
    }
    do {
        printf("Digite 0 para sair: ");
        scanf("%d", &opt);
    } while(!(opt == 0));
    return 0;
}
