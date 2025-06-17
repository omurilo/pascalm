#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    unsigned char length;
    char data[255];
} string;

typedef int IntArray[10];
typedef unsigned long long CharSet;
typedef struct Person {
    string name;
    int age;
    IntArray scores;
} Person;
typedef int Max;

Person people[5];
CharSet vowels = 0ULL;
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

int set_is_empty(unsigned long long s) {
    return s == 0ULL;
}

unsigned long long set_include(unsigned long long s, int element) {
    return s | (1ULL << element % 64);
}

unsigned long long set_exclude(unsigned long long s, int element) {
    return s & ~(1ULL << element % 64);
}

void print_set(unsigned long long s) {
    printf("[");
    int first = 1;
    for(int i = 0; i < 64; i++) {
        if(s & (1ULL << i % 64)) {
            if(!first) printf(", ");
            printf("%llu", (1ULL << i % 64));
            first = 0;
        }
    }
    printf("]\n");
}

void InitializePerson(Person *p, string name, int age){
    p->name = name;
    p->age = age;
    for(int i = (1-1); i < 10; i++){
        p->scores[i] = 0;
    }
}

bool IsVowel(char c){
    return ((vowels & (1ULL << c % 64)) != 0);
}

int main() {
    vowels = (0ULL | (1ULL << 'a' % 64) | (1ULL << 'e' % 64) | (1ULL << 'i' % 64) | (1ULL << 'o' % 64) | (1ULL << 'u' % 64));
    InitializePerson(&people[1], make_string("João"), 25);
    people[1].scores[1] = 85;
    people[1].scores[2] = 90;
    if(IsVowel('a')) {
        printf("a é uma vogal\n");
    }
    for(int i = (1-1); i < 10; i++){
        if(people[1].scores[i] > 0) {
            printf("Score  %d :  %d\n", i, people[1].scores[i]);
        }
    }
    return 0;
}
