#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    unsigned char length;
    char data[255];
} string;

typedef struct {\n    string nome;\n    int idade;\n} TPessoa;\n\n
TPessoa (null)[3];
int i = 0;

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

int main() {
    turma