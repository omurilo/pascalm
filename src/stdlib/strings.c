#include <string.h>
#include <stdio.h>
#include <stdlib.h>

string make_string(const char* c_str) {
    string ps;
    ps.length = strlen(c_str);
    if(ps.length > 255) ps.length = 255;
    ps.data = (char*)malloc(ps.length + 1);
    strncpy(ps.data, c_str, ps.length);
    ps.data[ps.length] = '\0';
    return ps;
}

string make_string_from_char(char ch) {
    char s[2];
    sprintf(s, "%c", ch);
    return make_string(s);
}

  // função para concatenar duas strings
string concat_string(string s1, string s2) {
    string result;
    result.length = s1.length + s2.length;
    if(result.length > 255) result.length = 255;
    result.data = (char*)malloc(result.length + 1);
    memcpy(result.data, s1.data, s1.length);
    memcpy(result.data + s1.length, s2.data, result.length - s1.length);
    result.data[result.length] = '\0';
    return result;
}