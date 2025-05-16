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

#ifndef YY_YY_FINAL_WORK_TAB_H_INCLUDED
# define YY_YY_FINAL_WORK_TAB_H_INCLUDED
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
    WHILE = 270,                   /* WHILE  */
    DO = 271,                      /* DO  */
    FOR = 272,                     /* FOR  */
    TO = 273,                      /* TO  */
    DOWNTO = 274,                  /* DOWNTO  */
    REPEAT = 275,                  /* REPEAT  */
    UNTIL = 276,                   /* UNTIL  */
    CASE = 277,                    /* CASE  */
    OF = 278,                      /* OF  */
    GOTO = 279,                    /* GOTO  */
    INTEGER = 280,                 /* INTEGER  */
    REAL = 281,                    /* REAL  */
    BOOLEAN = 282,                 /* BOOLEAN  */
    CHAR = 283,                    /* CHAR  */
    ARRAY = 284,                   /* ARRAY  */
    RECORD = 285,                  /* RECORD  */
    SET = 286,                     /* SET  */
    FILE_TOK = 287,                /* FILE_TOK  */
    STRING = 288,                  /* STRING  */
    READ = 289,                    /* READ  */
    WRITE = 290,                   /* WRITE  */
    READLN = 291,                  /* READLN  */
    WRITELN = 292,                 /* WRITELN  */
    GT = 293,                      /* GT  */
    GTE = 294,                     /* GTE  */
    LT = 295,                      /* LT  */
    LTE = 296,                     /* LTE  */
    NEQ = 297,                     /* NEQ  */
    EQ = 298,                      /* EQ  */
    AND = 299,                     /* AND  */
    OR = 300,                      /* OR  */
    NOT = 301,                     /* NOT  */
    PLUS = 302,                    /* PLUS  */
    MINUS = 303,                   /* MINUS  */
    TIMES = 304,                   /* TIMES  */
    DIVIDE = 305,                  /* DIVIDE  */
    DIV = 306,                     /* DIV  */
    MOD = 307,                     /* MOD  */
    DOT = 308,                     /* DOT  */
    DOTDOT = 309,                  /* DOTDOT  */
    ASSIGN = 310,                  /* ASSIGN  */
    SEMICOLON = 311,               /* SEMICOLON  */
    COMMA = 312,                   /* COMMA  */
    COLON = 313,                   /* COLON  */
    L_PAREN = 314,                 /* L_PAREN  */
    R_PAREN = 315,                 /* R_PAREN  */
    L_BRACE = 316,                 /* L_BRACE  */
    R_BRACE = 317,                 /* R_BRACE  */
    L_BRACKET = 318,               /* L_BRACKET  */
    R_BRACKET = 319,               /* R_BRACKET  */
    CHAR_LITERAL = 320,            /* CHAR_LITERAL  */
    INTEGER_LITERAL = 321,         /* INTEGER_LITERAL  */
    STRING_LITERAL = 322,          /* STRING_LITERAL  */
    REAL_LITERAL = 323,            /* REAL_LITERAL  */
    BOOLEAN_LITERAL = 324,         /* BOOLEAN_LITERAL  */
    IDENTIFIER = 325,              /* IDENTIFIER  */
    SQRT = 326,                    /* SQRT  */
    NEG = 327,                     /* NEG  */
    IN = 328,                      /* IN  */
    LOWER_THAN_ELSE = 329          /* LOWER_THAN_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 18 "final_work.y"

  int ival;
  double fval;
  char cval;
  char* sval;
  bool bval;

  TypeInfo type;
  Field *field_list;
  Param *param_list;

  char** strlist;

  Constant constant;

  Expr* expr;
  Stmt* stmt;
  StmtList* stmt_list;

#line 158 "final_work.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;

int yyparse (void);


#endif /* !YY_YY_FINAL_WORK_TAB_H_INCLUDED  */
