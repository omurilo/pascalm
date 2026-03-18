#ifndef STRING_H
#define STRING_H

#ifndef PASCAL_STRING_DEFINED
#define PASCAL_STRING_DEFINED
typedef struct {
    unsigned int length;
    char *data;
} PascalString;
#endif

/* string é um alias para PascalString para uso no PascalM */
typedef PascalString string;

string make_string(const char* c_str);
string make_string_from_char(char ch);
string concat_string(string s1, string s2);

#endif