/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    PROGRAM = 258,                 /* PROGRAM  */
    VAR = 259,                     /* VAR  */
    CONST = 260,                   /* CONST  */
    TYPE = 261,                    /* TYPE  */
    LABEL = 262,                   /* LABEL  */
    PROCEDURE = 263,               /* PROCEDURE  */
    FUNCTION = 264,                /* FUNCTION  */
    BEGIN_TOK = 265,               /* BEGIN_TOK  */
    END = 266,                     /* END  */
    IF = 267,                      /* IF  */
    THEN = 268,                    /* THEN  */
    ELSE = 269,                    /* ELSE  */
    NIL = 270,                     /* NIL  */
    WITH = 271,                    /* WITH  */
    FORWARD = 272,                 /* FORWARD  */
    PACKED = 273,                  /* PACKED  */
    WHILE = 274,                   /* WHILE  */
    DO = 275,                      /* DO  */
    FOR = 276,                     /* FOR  */
    TO = 277,                      /* TO  */
    DOWNTO = 278,                  /* DOWNTO  */
    REPEAT = 279,                  /* REPEAT  */
    UNTIL = 280,                   /* UNTIL  */
    CASE = 281,                    /* CASE  */
    OF = 282,                      /* OF  */
    GOTO = 283,                    /* GOTO  */
    INTEGER = 284,                 /* INTEGER  */
    REAL = 285,                    /* REAL  */
    BOOLEAN = 286,                 /* BOOLEAN  */
    CHAR = 287,                    /* CHAR  */
    ARRAY = 288,                   /* ARRAY  */
    RECORD = 289,                  /* RECORD  */
    SET = 290,                     /* SET  */
    FILE_TOK = 291,                /* FILE_TOK  */
    STRING = 292,                  /* STRING  */
    READ = 293,                    /* READ  */
    WRITE = 294,                   /* WRITE  */
    READLN = 295,                  /* READLN  */
    WRITELN = 296,                 /* WRITELN  */
    GT = 297,                      /* GT  */
    GTE = 298,                     /* GTE  */
    LT = 299,                      /* LT  */
    LTE = 300,                     /* LTE  */
    NEQ = 301,                     /* NEQ  */
    EQ = 302,                      /* EQ  */
    AND = 303,                     /* AND  */
    OR = 304,                      /* OR  */
    NOT = 305,                     /* NOT  */
    PLUS = 306,                    /* PLUS  */
    MINUS = 307,                   /* MINUS  */
    TIMES = 308,                   /* TIMES  */
    DIVIDE = 309,                  /* DIVIDE  */
    DIV = 310,                     /* DIV  */
    MOD = 311,                     /* MOD  */
    DOT = 312,                     /* DOT  */
    DOTDOT = 313,                  /* DOTDOT  */
    CARET = 314,                   /* CARET  */
    ASSIGN = 315,                  /* ASSIGN  */
    SEMICOLON = 316,               /* SEMICOLON  */
    COMMA = 317,                   /* COMMA  */
    COLON = 318,                   /* COLON  */
    L_PAREN = 319,                 /* L_PAREN  */
    R_PAREN = 320,                 /* R_PAREN  */
    L_BRACE = 321,                 /* L_BRACE  */
    R_BRACE = 322,                 /* R_BRACE  */
    L_BRACKET = 323,               /* L_BRACKET  */
    R_BRACKET = 324,               /* R_BRACKET  */
    CHAR_LITERAL = 325,            /* CHAR_LITERAL  */
    INTEGER_LITERAL = 326,         /* INTEGER_LITERAL  */
    REAL_LITERAL = 327,            /* REAL_LITERAL  */
    BOOLEAN_LITERAL = 328,         /* BOOLEAN_LITERAL  */
    IDENTIFIER = 329,              /* IDENTIFIER  */
    STRING_LITERAL = 330,          /* STRING_LITERAL  */
    SQRT = 331,                    /* SQRT  */
    NEG = 332,                     /* NEG  */
    IN = 333,                      /* IN  */
    LOWER_THAN_ELSE = 334          /* LOWER_THAN_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 20 "parser/parser.y"

  int integer;
  bool boolean;
  char character;
  double number;
  char* string;

  ASTNode* node;

  LiteralNode *lnode;
  ListNode *ltnode;

#line 156 "parser/parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
typedef YYLTYPE YYLTYPE;


extern YYSTYPE yylval;
extern YYLTYPE yylloc;

int yyparse (void);


#endif /* !YY_YY_PARSER_PARSER_TAB_H_INCLUDED  */
