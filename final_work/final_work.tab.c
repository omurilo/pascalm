/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "final_work.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "types.h"
#include "tac.h"
#include "symbol-table.h"

int yywrap();
int yylex();
extern FILE *yyin;
int yyparse();
void yyerror(const char *str);


#line 88 "final_work.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "final_work.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_PROGRAM = 3,                    /* PROGRAM  */
  YYSYMBOL_VAR = 4,                        /* VAR  */
  YYSYMBOL_CONST = 5,                      /* CONST  */
  YYSYMBOL_TYPE = 6,                       /* TYPE  */
  YYSYMBOL_LABEL = 7,                      /* LABEL  */
  YYSYMBOL_PROCEDURE = 8,                  /* PROCEDURE  */
  YYSYMBOL_FUNCTION = 9,                   /* FUNCTION  */
  YYSYMBOL_BEGIN_TOK = 10,                 /* BEGIN_TOK  */
  YYSYMBOL_END = 11,                       /* END  */
  YYSYMBOL_IF = 12,                        /* IF  */
  YYSYMBOL_THEN = 13,                      /* THEN  */
  YYSYMBOL_ELSE = 14,                      /* ELSE  */
  YYSYMBOL_WHILE = 15,                     /* WHILE  */
  YYSYMBOL_DO = 16,                        /* DO  */
  YYSYMBOL_FOR = 17,                       /* FOR  */
  YYSYMBOL_TO = 18,                        /* TO  */
  YYSYMBOL_DOWNTO = 19,                    /* DOWNTO  */
  YYSYMBOL_REPEAT = 20,                    /* REPEAT  */
  YYSYMBOL_UNTIL = 21,                     /* UNTIL  */
  YYSYMBOL_CASE = 22,                      /* CASE  */
  YYSYMBOL_OF = 23,                        /* OF  */
  YYSYMBOL_GOTO = 24,                      /* GOTO  */
  YYSYMBOL_INTEGER = 25,                   /* INTEGER  */
  YYSYMBOL_REAL = 26,                      /* REAL  */
  YYSYMBOL_BOOLEAN = 27,                   /* BOOLEAN  */
  YYSYMBOL_CHAR = 28,                      /* CHAR  */
  YYSYMBOL_ARRAY = 29,                     /* ARRAY  */
  YYSYMBOL_RECORD = 30,                    /* RECORD  */
  YYSYMBOL_SET = 31,                       /* SET  */
  YYSYMBOL_FILE_TOK = 32,                  /* FILE_TOK  */
  YYSYMBOL_STRING = 33,                    /* STRING  */
  YYSYMBOL_READ = 34,                      /* READ  */
  YYSYMBOL_WRITE = 35,                     /* WRITE  */
  YYSYMBOL_READLN = 36,                    /* READLN  */
  YYSYMBOL_WRITELN = 37,                   /* WRITELN  */
  YYSYMBOL_GT = 38,                        /* GT  */
  YYSYMBOL_GTE = 39,                       /* GTE  */
  YYSYMBOL_LT = 40,                        /* LT  */
  YYSYMBOL_LTE = 41,                       /* LTE  */
  YYSYMBOL_NEQ = 42,                       /* NEQ  */
  YYSYMBOL_EQ = 43,                        /* EQ  */
  YYSYMBOL_AND = 44,                       /* AND  */
  YYSYMBOL_OR = 45,                        /* OR  */
  YYSYMBOL_NOT = 46,                       /* NOT  */
  YYSYMBOL_PLUS = 47,                      /* PLUS  */
  YYSYMBOL_MINUS = 48,                     /* MINUS  */
  YYSYMBOL_TIMES = 49,                     /* TIMES  */
  YYSYMBOL_DIVIDE = 50,                    /* DIVIDE  */
  YYSYMBOL_DIV = 51,                       /* DIV  */
  YYSYMBOL_MOD = 52,                       /* MOD  */
  YYSYMBOL_DOT = 53,                       /* DOT  */
  YYSYMBOL_DOTDOT = 54,                    /* DOTDOT  */
  YYSYMBOL_ASSIGN = 55,                    /* ASSIGN  */
  YYSYMBOL_SEMICOLON = 56,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 57,                     /* COMMA  */
  YYSYMBOL_COLON = 58,                     /* COLON  */
  YYSYMBOL_L_PAREN = 59,                   /* L_PAREN  */
  YYSYMBOL_R_PAREN = 60,                   /* R_PAREN  */
  YYSYMBOL_L_BRACE = 61,                   /* L_BRACE  */
  YYSYMBOL_R_BRACE = 62,                   /* R_BRACE  */
  YYSYMBOL_L_BRACKET = 63,                 /* L_BRACKET  */
  YYSYMBOL_R_BRACKET = 64,                 /* R_BRACKET  */
  YYSYMBOL_CHAR_LITERAL = 65,              /* CHAR_LITERAL  */
  YYSYMBOL_INTEGER_LITERAL = 66,           /* INTEGER_LITERAL  */
  YYSYMBOL_STRING_LITERAL = 67,            /* STRING_LITERAL  */
  YYSYMBOL_REAL_LITERAL = 68,              /* REAL_LITERAL  */
  YYSYMBOL_BOOLEAN_LITERAL = 69,           /* BOOLEAN_LITERAL  */
  YYSYMBOL_IDENTIFIER = 70,                /* IDENTIFIER  */
  YYSYMBOL_SQRT = 71,                      /* SQRT  */
  YYSYMBOL_NEG = 72,                       /* NEG  */
  YYSYMBOL_IN = 73,                        /* IN  */
  YYSYMBOL_LOWER_THAN_ELSE = 74,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 75,                  /* $accept  */
  YYSYMBOL_program = 76,                   /* program  */
  YYSYMBOL_heading = 77,                   /* heading  */
  YYSYMBOL_identifier_list = 78,           /* identifier_list  */
  YYSYMBOL_block = 79,                     /* block  */
  YYSYMBOL_declarations = 80,              /* declarations  */
  YYSYMBOL_label_declaration = 81,         /* label_declaration  */
  YYSYMBOL_unsigned_integer_list = 82,     /* unsigned_integer_list  */
  YYSYMBOL_constant_declaration = 83,      /* constant_declaration  */
  YYSYMBOL_const_assignment_list = 84,     /* const_assignment_list  */
  YYSYMBOL_const_assignment = 85,          /* const_assignment  */
  YYSYMBOL_constant = 86,                  /* constant  */
  YYSYMBOL_type_declaration = 87,          /* type_declaration  */
  YYSYMBOL_type_assignment_list = 88,      /* type_assignment_list  */
  YYSYMBOL_variable_declaration = 89,      /* variable_declaration  */
  YYSYMBOL_variable_declaration_list = 90, /* variable_declaration_list  */
  YYSYMBOL_variable_list_type = 91,        /* variable_list_type  */
  YYSYMBOL_variable_list = 92,             /* variable_list  */
  YYSYMBOL_type = 93,                      /* type  */
  YYSYMBOL_field_list = 94,                /* field_list  */
  YYSYMBOL_field_decl = 95,                /* field_decl  */
  YYSYMBOL_procedure_declaration = 96,     /* procedure_declaration  */
  YYSYMBOL_function_declaration = 97,      /* function_declaration  */
  YYSYMBOL_param_list = 98,                /* param_list  */
  YYSYMBOL_param_seq = 99,                 /* param_seq  */
  YYSYMBOL_statement_list = 100,           /* statement_list  */
  YYSYMBOL_statement = 101,                /* statement  */
  YYSYMBOL_assign = 102,                   /* assign  */
  YYSYMBOL_procedure_stmt = 103,           /* procedure_stmt  */
  YYSYMBOL_compound_stmt = 104,            /* compound_stmt  */
  YYSYMBOL_if_stmt = 105,                  /* if_stmt  */
  YYSYMBOL_case_stmt = 106,                /* case_stmt  */
  YYSYMBOL_case_list = 107,                /* case_list  */
  YYSYMBOL_case_elem = 108,                /* case_elem  */
  YYSYMBOL_repeat_stmt = 109,              /* repeat_stmt  */
  YYSYMBOL_goto_stmt = 110,                /* goto_stmt  */
  YYSYMBOL_while_stmt = 111,               /* while_stmt  */
  YYSYMBOL_for_stmt = 112,                 /* for_stmt  */
  YYSYMBOL_expression_list = 113,          /* expression_list  */
  YYSYMBOL_expression = 114,               /* expression  */
  YYSYMBOL_primary = 115,                  /* primary  */
  YYSYMBOL_postfix = 116,                  /* postfix  */
  YYSYMBOL_simple_expr = 117,              /* simple_expr  */
  YYSYMBOL_term = 118,                     /* term  */
  YYSYMBOL_factor = 119,                   /* factor  */
  YYSYMBOL_relational_op = 120,            /* relational_op  */
  YYSYMBOL_add_op = 121,                   /* add_op  */
  YYSYMBOL_mul_op = 122,                   /* mul_op  */
  YYSYMBOL_write = 123,                    /* write  */
  YYSYMBOL_write_args = 124,               /* write_args  */
  YYSYMBOL_write_arg = 125,                /* write_arg  */
  YYSYMBOL_read = 126                      /* read  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   245

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  75
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  52
/* YYNRULES -- Number of rules.  */
#define YYNRULES  131
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  268

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   329


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    86,    86,    89,    91,    95,    96,   100,   103,   105,
     106,   107,   108,   109,   110,   114,   118,   119,   123,   127,
     128,   132,   138,   144,   150,   156,   162,   169,   179,   183,
     184,   188,   192,   193,   197,   210,   216,   227,   232,   237,
     242,   247,   252,   263,   269,   282,   283,   292,   302,   306,
     310,   311,   315,   322,   335,   336,   340,   341,   342,   343,
     344,   345,   346,   347,   348,   349,   353,   354,   355,   356,
     360,   361,   362,   366,   370,   371,   375,   379,   380,   384,
     385,   386,   390,   394,   398,   402,   403,   407,   408,   412,
     413,   417,   424,   430,   436,   442,   448,   454,   459,   460,
     461,   462,   465,   466,   470,   471,   475,   476,   477,   478,
     482,   483,   484,   485,   486,   487,   491,   492,   493,   497,
     498,   499,   542,   543,   546,   552,   553,   557,   558,   561,
     575,   579
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "PROGRAM", "VAR",
  "CONST", "TYPE", "LABEL", "PROCEDURE", "FUNCTION", "BEGIN_TOK", "END",
  "IF", "THEN", "ELSE", "WHILE", "DO", "FOR", "TO", "DOWNTO", "REPEAT",
  "UNTIL", "CASE", "OF", "GOTO", "INTEGER", "REAL", "BOOLEAN", "CHAR",
  "ARRAY", "RECORD", "SET", "FILE_TOK", "STRING", "READ", "WRITE",
  "READLN", "WRITELN", "GT", "GTE", "LT", "LTE", "NEQ", "EQ", "AND", "OR",
  "NOT", "PLUS", "MINUS", "TIMES", "DIVIDE", "DIV", "MOD", "DOT", "DOTDOT",
  "ASSIGN", "SEMICOLON", "COMMA", "COLON", "L_PAREN", "R_PAREN", "L_BRACE",
  "R_BRACE", "L_BRACKET", "R_BRACKET", "CHAR_LITERAL", "INTEGER_LITERAL",
  "STRING_LITERAL", "REAL_LITERAL", "BOOLEAN_LITERAL", "IDENTIFIER",
  "SQRT", "NEG", "IN", "LOWER_THAN_ELSE", "$accept", "program", "heading",
  "identifier_list", "block", "declarations", "label_declaration",
  "unsigned_integer_list", "constant_declaration", "const_assignment_list",
  "const_assignment", "constant", "type_declaration",
  "type_assignment_list", "variable_declaration",
  "variable_declaration_list", "variable_list_type", "variable_list",
  "type", "field_list", "field_decl", "procedure_declaration",
  "function_declaration", "param_list", "param_seq", "statement_list",
  "statement", "assign", "procedure_stmt", "compound_stmt", "if_stmt",
  "case_stmt", "case_list", "case_elem", "repeat_stmt", "goto_stmt",
  "while_stmt", "for_stmt", "expression_list", "expression", "primary",
  "postfix", "simple_expr", "term", "factor", "relational_op", "add_op",
  "mul_op", "write", "write_args", "write_arg", "read", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-211)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      28,   -65,    38,   -16,  -211,   -22,    15,  -211,   -27,  -211,
     -14,  -211,    47,   141,  -211,  -211,    11,    51,    55,    49,
      63,    71,     0,  -211,  -211,  -211,  -211,    67,    99,  -211,
     100,  -211,    18,    74,   101,  -211,   115,   103,  -211,    42,
     102,   104,     0,    37,    37,    92,     0,    37,    94,   105,
     106,   107,    61,     3,  -211,  -211,  -211,  -211,  -211,  -211,
    -211,  -211,  -211,  -211,  -211,  -211,  -211,  -211,    11,   108,
      25,    21,    51,    25,   109,  -211,   110,   111,   111,     5,
      37,    37,    37,    37,  -211,  -211,  -211,  -211,  -211,   112,
     156,  -211,   -34,    89,    30,  -211,   154,   117,     4,   151,
    -211,   113,    27,    27,   116,    37,    37,    37,  -211,     0,
    -211,  -211,  -211,  -211,  -211,  -211,   114,   118,  -211,  -211,
    -211,   119,   120,  -211,  -211,  -211,  -211,  -211,  -211,  -211,
     132,  -211,   122,   127,   126,   131,  -211,  -211,  -211,  -211,
     133,    37,     0,   124,    37,  -211,  -211,  -211,  -211,  -211,
    -211,  -211,  -211,  -211,    37,    37,  -211,  -211,  -211,    37,
       0,    37,    37,    12,   137,  -211,   -30,    53,  -211,    78,
     143,  -211,    82,  -211,   128,  -211,    21,   142,     2,   145,
    -211,  -211,    25,    25,   146,   129,   147,  -211,    83,   189,
    -211,   140,    45,    30,  -211,  -211,    90,  -211,  -211,   148,
     149,   153,     7,  -211,  -211,   144,   150,    27,  -211,  -211,
      37,    37,  -211,    10,   157,    25,  -211,   159,  -211,  -211,
    -211,  -211,   152,    25,  -211,     0,  -211,    37,    37,     0,
    -211,  -211,  -211,  -211,   155,  -211,  -211,  -211,   158,    37,
      21,  -211,  -211,  -211,    25,   162,  -211,   191,   196,   163,
     160,   165,  -211,   161,  -211,  -211,     0,     0,  -211,  -211,
      37,   198,  -211,  -211,  -211,  -211,    25,  -211
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     3,     1,     0,     0,     5,     0,     8,
       0,     4,     0,     0,     6,     2,     0,     0,     0,     0,
       0,     0,    65,     9,    10,    11,    12,     0,     0,    35,
       0,    32,     0,     0,     0,    19,     0,     0,    16,     0,
       0,     0,    65,     0,     0,     0,    65,     0,     0,     0,
       0,   124,     0,     0,    54,    56,    63,    62,    57,    61,
      60,    64,    58,    59,    72,    71,    13,    14,    31,     0,
       0,     0,    18,     0,    28,    15,     0,    50,    50,     0,
       0,     0,     0,     0,    94,    92,    95,    93,    96,    91,
       0,    98,   106,    89,   102,   104,     0,     0,     0,     0,
      83,     0,     0,     0,     0,     0,     0,     0,     7,    65,
      33,    36,    37,    39,    41,    40,     0,     0,    38,    44,
      34,     0,     0,    22,    24,    23,    25,    21,    20,    29,
       0,    17,     0,     0,    51,     0,    73,   107,   108,   109,
       0,     0,    65,     0,     0,   112,   113,   114,   115,   111,
     110,   118,   116,   117,     0,     0,   121,   119,   120,     0,
      65,     0,     0,     0,     0,   127,   129,     0,   125,     0,
       0,    66,     0,    87,     0,    55,     0,     0,     0,     0,
      26,    27,     0,     0,     0,     0,     0,    97,     0,    74,
      99,     0,    90,   103,   105,    84,     0,    82,    80,     0,
       0,     0,     0,    78,   131,     0,     0,     0,   122,   123,
       0,     0,    70,     0,     0,     0,    43,     0,    45,    30,
      52,     8,     0,     0,   101,    65,   100,     0,     0,    65,
      81,    76,    77,   130,     0,   126,    67,    88,     0,     0,
       0,    47,    46,    48,     0,     0,    75,     0,     0,     0,
       0,     0,    68,     0,    53,     8,    65,    65,    79,   128,
       0,     0,    49,    85,    86,    69,     0,    42
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -211,  -211,  -211,  -211,  -210,  -211,  -211,  -211,  -211,  -211,
     164,  -173,  -211,  -211,  -211,  -211,   166,  -211,   -71,  -211,
      44,  -211,  -211,   167,  -211,   -10,  -103,  -211,  -136,  -211,
    -211,  -211,  -211,    22,  -211,  -211,  -211,  -211,    86,   -43,
    -211,  -211,    69,    75,   -73,  -211,  -211,  -211,  -211,   130,
      24,  -211
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     6,     8,    12,    13,    23,    39,    24,    34,
      35,   127,    25,    37,    26,    30,    31,    32,   120,   178,
     179,    27,    28,   133,   134,    53,    54,    55,    56,    57,
      58,    59,   202,   203,    60,    61,    62,    63,   172,   173,
      91,    92,    93,    94,    95,   154,   155,   159,    64,   167,
     168,    65
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      90,    96,   129,   214,    99,     3,   175,   137,   138,   139,
      42,   243,    43,   216,   108,    44,   136,    45,   231,   143,
      46,   198,    47,   205,    48,   162,   198,   201,   206,   144,
      10,     1,    79,    11,    49,    50,    98,    51,     4,   189,
     140,    49,    50,     5,    51,   262,    49,    50,     7,    51,
     112,   113,   114,   115,   116,   117,    14,   195,   118,   109,
     109,   109,   171,   238,   174,   239,   201,   253,   121,   122,
      52,     9,   177,   199,   156,    69,    70,   200,   199,   157,
     158,    29,   200,    80,    81,    82,   194,   123,   124,   125,
     151,   126,   152,   153,   165,   119,    83,   166,    75,    76,
      15,   191,    84,    85,    86,    87,    88,    89,   227,   228,
     207,   219,   220,   208,   104,    38,   105,    71,   196,   197,
     106,    33,   246,    66,   107,    36,   249,   145,   146,   147,
     148,   149,   150,    40,   151,   207,   152,   153,   209,   211,
     211,    41,   212,   224,   241,    16,    17,    18,    19,    20,
      21,    22,   245,   263,   264,    67,    68,    72,    73,    74,
     100,    77,    97,    78,   101,   102,   103,   236,   237,   142,
     160,   141,   161,   254,   163,   182,   131,   176,   111,   130,
     183,   132,   185,   164,   247,   248,   170,   184,   177,   180,
     181,   186,   213,   187,   190,   267,   252,   204,   210,   222,
     215,   218,   221,   225,   226,   223,   229,   256,   106,   230,
     244,   240,   257,   250,   233,   242,   234,   265,   255,   258,
     260,   266,   217,   192,   232,   261,   259,   188,   251,     0,
     193,   235,     0,   169,   110,     0,   128,     0,     0,     0,
       0,     0,     0,     0,     0,   135
};

static const yytype_int16 yycheck[] =
{
      43,    44,    73,   176,    47,    70,   109,    80,    81,    82,
      10,   221,    12,    11,    11,    15,    11,    17,    11,    53,
      20,    14,    22,    53,    24,    21,    14,   163,    58,    63,
      57,     3,    42,    60,    34,    35,    46,    37,     0,   142,
      83,    34,    35,    59,    37,   255,    34,    35,    70,    37,
      25,    26,    27,    28,    29,    30,    70,   160,    33,    56,
      56,    56,   105,    53,   107,    55,   202,   240,    47,    48,
      70,    56,    70,    66,    44,    57,    58,    70,    66,    49,
      50,    70,    70,    46,    47,    48,   159,    66,    67,    68,
      45,    70,    47,    48,    67,    70,    59,    70,    56,    57,
      53,   144,    65,    66,    67,    68,    69,    70,    18,    19,
      57,   182,   183,    60,    53,    66,    55,    43,   161,   162,
      59,    70,   225,    56,    63,    70,   229,    38,    39,    40,
      41,    42,    43,    70,    45,    57,    47,    48,    60,    57,
      57,    70,    60,    60,   215,     4,     5,     6,     7,     8,
       9,    10,   223,   256,   257,    56,    56,    56,    43,    56,
      66,    59,    70,    59,    59,    59,    59,   210,   211,    13,
      16,    59,    55,   244,    23,    43,    66,    63,    70,    70,
      58,    70,    56,    70,   227,   228,    70,    60,    70,    70,
      70,    60,    64,    60,    70,   266,   239,    60,    55,    70,
      58,    56,    56,    14,    64,    58,    58,    16,    59,    56,
      58,    54,    16,    58,    70,    56,    66,   260,    56,    56,
      55,    23,   178,   154,   202,    64,    66,   141,    70,    -1,
     155,   207,    -1,   103,    68,    -1,    72,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    78
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    76,    70,     0,    59,    77,    70,    78,    56,
      57,    60,    79,    80,    70,    53,     4,     5,     6,     7,
       8,     9,    10,    81,    83,    87,    89,    96,    97,    70,
      90,    91,    92,    70,    84,    85,    70,    88,    66,    82,
      70,    70,    10,    12,    15,    17,    20,    22,    24,    34,
      35,    37,    70,   100,   101,   102,   103,   104,   105,   106,
     109,   110,   111,   112,   123,   126,    56,    56,    56,    57,
      58,    43,    56,    43,    56,    56,    57,    59,    59,   100,
      46,    47,    48,    59,    65,    66,    67,    68,    69,    70,
     114,   115,   116,   117,   118,   119,   114,    70,   100,   114,
      66,    59,    59,    59,    53,    55,    59,    63,    11,    56,
      91,    70,    25,    26,    27,    28,    29,    30,    33,    70,
      93,    47,    48,    66,    67,    68,    70,    86,    85,    93,
      70,    66,    70,    98,    99,    98,    11,   119,   119,   119,
     114,    59,    13,    53,    63,    38,    39,    40,    41,    42,
      43,    45,    47,    48,   120,   121,    44,    49,    50,   122,
      16,    55,    21,    23,    70,    67,    70,   124,   125,   124,
      70,   114,   113,   114,   114,   101,    63,    70,    94,    95,
      70,    70,    43,    58,    60,    56,    60,    60,   113,   101,
      70,   114,   117,   118,   119,   101,   114,   114,    14,    66,
      70,   103,   107,   108,    60,    53,    58,    57,    60,    60,
      55,    57,    60,    64,    86,    58,    11,    95,    56,    93,
      93,    56,    70,    58,    60,    14,    64,    18,    19,    58,
      56,    11,   108,    70,    66,   125,   114,   114,    53,    55,
      54,    93,    56,    79,    58,    93,   101,   114,   114,   101,
      58,    70,   114,    86,    93,    56,    16,    16,    56,    66,
      55,    64,    79,   101,   101,   114,    23,    93
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    75,    76,    77,    77,    78,    78,    79,    80,    80,
      80,    80,    80,    80,    80,    81,    82,    82,    83,    84,
      84,    85,    86,    86,    86,    86,    86,    86,    87,    88,
      88,    89,    90,    90,    91,    92,    92,    93,    93,    93,
      93,    93,    93,    93,    93,    94,    94,    95,    96,    97,
      98,    98,    99,    99,   100,   100,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   102,   102,   102,   102,
     103,   103,   103,   104,   105,   105,   106,   107,   107,   108,
     108,   108,   109,   110,   111,   112,   112,   113,   113,   114,
     114,   115,   115,   115,   115,   115,   115,   115,   116,   116,
     116,   116,   117,   117,   118,   118,   119,   119,   119,   119,
     120,   120,   120,   120,   120,   120,   121,   121,   121,   122,
     122,   122,   123,   123,   123,   124,   124,   125,   125,   125,
     125,   126
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     6,     0,     3,     1,     3,     4,     0,     2,
       2,     2,     2,     3,     3,     3,     1,     3,     3,     1,
       3,     3,     1,     1,     1,     1,     2,     2,     3,     3,
       5,     3,     1,     3,     3,     1,     3,     1,     1,     1,
       1,     1,     8,     3,     1,     2,     3,     3,     7,     9,
       0,     1,     3,     5,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     3,     5,     6,     8,
       4,     1,     1,     3,     4,     6,     5,     2,     1,     4,
       1,     2,     4,     2,     4,     8,     8,     1,     3,     1,
       3,     1,     1,     1,     1,     1,     1,     3,     1,     3,
       4,     4,     1,     3,     1,     3,     1,     2,     2,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     4,     4,     1,     1,     3,     1,     5,     1,
       3,     4
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: PROGRAM IDENTIFIER heading SEMICOLON block DOT  */
#line 86 "final_work.y"
                                                     { /* tac_print(generate_stmt_list_tac($2));*/ }
#line 1777 "final_work.tab.c"
    break;

  case 21: /* const_assignment: IDENTIFIER EQ constant  */
#line 132 "final_work.y"
                           {
      fprintf(stderr, "vamos colocar na synbol table: %s: %d\n", (yyvsp[-2].sval), (yyvsp[0].constant).ival);
    }
#line 1785 "final_work.tab.c"
    break;

  case 22: /* constant: INTEGER_LITERAL  */
#line 138 "final_work.y"
                    {
      Constant c;
      c.kind = TYPE_INT;
      c.ival = (yyvsp[0].ival);
      (yyval.constant) = c;
    }
#line 1796 "final_work.tab.c"
    break;

  case 23: /* constant: REAL_LITERAL  */
#line 144 "final_work.y"
                 {
      Constant c;
      c.kind = TYPE_REAL;
      c.fval = (yyvsp[0].fval);
      (yyval.constant) = c;
  }
#line 1807 "final_work.tab.c"
    break;

  case 24: /* constant: STRING_LITERAL  */
#line 150 "final_work.y"
                   {
      Constant c;
      c.kind = TYPE_STRING;
      c.sval = (yyvsp[0].sval);
      (yyval.constant) = c;
  }
#line 1818 "final_work.tab.c"
    break;

  case 25: /* constant: IDENTIFIER  */
#line 156 "final_work.y"
               {
      Constant c;
      c.kind = TYPE_STRING;
      c.id = strdup((yyvsp[0].sval));
      (yyval.constant) = c;
    }
#line 1829 "final_work.tab.c"
    break;

  case 26: /* constant: PLUS IDENTIFIER  */
#line 162 "final_work.y"
                    {
      Constant c;
      c.kind = TYPE_STRING;
      c.op = '+';
      c.id = strdup((yyvsp[0].sval));
      (yyval.constant) = c;
    }
#line 1841 "final_work.tab.c"
    break;

  case 27: /* constant: MINUS IDENTIFIER  */
#line 169 "final_work.y"
                     {
      Constant c;
      c.kind = TYPE_STRING;
      c.op = '-';
      c.id = strdup((yyvsp[0].sval));
      (yyval.constant) = c;
    }
#line 1853 "final_work.tab.c"
    break;

  case 34: /* variable_list_type: variable_list COLON type  */
#line 197 "final_work.y"
                             {
      TypeInfo t = (yyvsp[0].type);
      for (int i = 0; (yyvsp[-2].strlist)[i] != NULL; i++) {
        if (add_symbol((yyvsp[-2].strlist)[i], t) == -1) {
          fprintf(stderr, "Error to declare variable %s\n", (yyvsp[-2].strlist)[i]);
        }
        free((yyvsp[-2].strlist)[i]);
      }
      free((yyvsp[-2].strlist));
    }
#line 1868 "final_work.tab.c"
    break;

  case 35: /* variable_list: IDENTIFIER  */
#line 210 "final_work.y"
               {
      char** l = (char**)malloc(2*sizeof(char**));
      l[0] = strdup((yyvsp[0].sval));
      l[1] = NULL;
      (yyval.strlist) = l;
    }
#line 1879 "final_work.tab.c"
    break;

  case 36: /* variable_list: variable_list COMMA IDENTIFIER  */
#line 216 "final_work.y"
                                   {
      int i;
      for (i = 0; (yyvsp[-2].strlist)[i] != NULL; i++);
      char** tmp = (char**)realloc((yyvsp[-2].strlist), (i+2) * sizeof(char*));
      tmp[i] = strdup((yyvsp[0].sval));
      tmp[i+1] = NULL;
      (yyval.strlist) = tmp;
    }
#line 1892 "final_work.tab.c"
    break;

  case 37: /* type: INTEGER  */
#line 227 "final_work.y"
            {
      TypeInfo tmp;
      tmp.type = TYPE_INT;
      (yyval.type) = tmp;
    }
#line 1902 "final_work.tab.c"
    break;

  case 38: /* type: STRING  */
#line 232 "final_work.y"
           {
    TypeInfo tmp;
    tmp.type = TYPE_STRING;
    (yyval.type) = tmp;
  }
#line 1912 "final_work.tab.c"
    break;

  case 39: /* type: REAL  */
#line 237 "final_work.y"
         {
    TypeInfo tmp;
    tmp.type = TYPE_REAL;
    (yyval.type) = tmp;
  }
#line 1922 "final_work.tab.c"
    break;

  case 40: /* type: CHAR  */
#line 242 "final_work.y"
         {
    TypeInfo tmp;
    tmp.type = TYPE_CHAR;
    (yyval.type) = tmp;
  }
#line 1932 "final_work.tab.c"
    break;

  case 41: /* type: BOOLEAN  */
#line 247 "final_work.y"
            {
    TypeInfo tmp;
    tmp.type = TYPE_BOOL;
    (yyval.type) = tmp;
  }
#line 1942 "final_work.tab.c"
    break;

  case 42: /* type: ARRAY L_BRACKET constant DOTDOT constant R_BRACKET OF type  */
#line 252 "final_work.y"
                                                               {
      TypeInfo tmp;
      tmp.type = TYPE_ARRAY;
      tmp.arrayInfo.type=(yyvsp[0].type).type;
      tmp.arrayInfo.low=(yyvsp[-5].constant).ival;
      if ((yyvsp[-3].constant).kind == TYPE_STRING) {
        // Symbol* s = get_symbol_by_name($5.id);
        // tmp.arrayInfo.high=s->data.i;
      }
      (yyval.type) = tmp;
  }
#line 1958 "final_work.tab.c"
    break;

  case 43: /* type: RECORD field_list END  */
#line 263 "final_work.y"
                          {
      TypeInfo tmp;
      tmp.type = TYPE_RECORD;
      tmp.recordFields = (yyvsp[-1].field_list);
      (yyval.type) = tmp;
  }
#line 1969 "final_work.tab.c"
    break;

  case 44: /* type: IDENTIFIER  */
#line 269 "final_work.y"
               {
    TypeInfo tmp;
    tmp.type = TYPE_STRING;
  
    // Symbol* s = get_symbol_by_name($1);
    // if (s->skind == KIND_TYPE) {
    //   //TODO: rescue custom type
    // }
    (yyval.type) = tmp;
  }
#line 1984 "final_work.tab.c"
    break;

  case 45: /* field_list: field_decl SEMICOLON  */
#line 282 "final_work.y"
                         { (yyval.field_list) = (yyvsp[-1].field_list); }
#line 1990 "final_work.tab.c"
    break;

  case 46: /* field_list: field_list field_decl SEMICOLON  */
#line 283 "final_work.y"
                                    { 
      Field* last = (yyvsp[-2].field_list);
      while(last->next) last = last->next;
      last->next = (yyvsp[-1].field_list);
      (yyval.field_list) = (yyvsp[-2].field_list);
    }
#line 2001 "final_work.tab.c"
    break;

  case 47: /* field_decl: IDENTIFIER COLON type  */
#line 292 "final_work.y"
                          {
      Field* f = (Field*)malloc(sizeof(Field));
      f->name = strdup((yyvsp[-2].sval));
      f->type = &(yyvsp[0].type);
      f->next = NULL;
      (yyval.field_list)=f;
    }
#line 2013 "final_work.tab.c"
    break;

  case 50: /* param_list: %empty  */
#line 310 "final_work.y"
  { (yyval.param_list) = NULL; }
#line 2019 "final_work.tab.c"
    break;

  case 51: /* param_list: param_seq  */
#line 311 "final_work.y"
              { (yyval.param_list) = (yyvsp[0].param_list); }
#line 2025 "final_work.tab.c"
    break;

  case 52: /* param_seq: IDENTIFIER COLON type  */
#line 315 "final_work.y"
                          { 
      Param* p = (Param*)malloc(sizeof(Param));
      p->name = strdup((yyvsp[-2].sval));
      // p->type = lookup_type($3);
      p->next = NULL;
      (yyval.param_list) = p;
    }
#line 2037 "final_work.tab.c"
    break;

  case 53: /* param_seq: param_seq SEMICOLON IDENTIFIER COLON type  */
#line 322 "final_work.y"
                                              { 
      Param* last = (yyvsp[-4].param_list);
      while(last->next) last = last->next;
      Param* p = (Param*)malloc(sizeof(Param));
      p->name = strdup((yyvsp[-2].sval));
      // p->type = lookup_type($5);
      p->next = NULL;
      last->next = p;
      (yyval.param_list) = (yyvsp[-4].param_list);
    }
#line 2052 "final_work.tab.c"
    break;

  case 91: /* primary: IDENTIFIER  */
#line 417 "final_work.y"
               {
      TypeInfo tmp;
      tmp.type = TYPE_STRING;
      tmp.data.s = (yyvsp[0].sval);
      (yyval.type) = tmp;
      // TODO: criado o tipo para var
    }
#line 2064 "final_work.tab.c"
    break;

  case 92: /* primary: INTEGER_LITERAL  */
#line 424 "final_work.y"
                    {
      TypeInfo tmp;
      tmp.type = TYPE_INT;
      tmp.data.i = (yyvsp[0].ival);
      (yyval.type) = tmp;
    }
#line 2075 "final_work.tab.c"
    break;

  case 93: /* primary: REAL_LITERAL  */
#line 430 "final_work.y"
                 {
      TypeInfo tmp;
      tmp.type = TYPE_REAL;
      tmp.data.f = (yyvsp[0].fval);
      (yyval.type) = tmp;
    }
#line 2086 "final_work.tab.c"
    break;

  case 94: /* primary: CHAR_LITERAL  */
#line 436 "final_work.y"
                 {
      TypeInfo tmp;
      tmp.type = TYPE_CHAR;
      tmp.data.c = (yyvsp[0].cval);
      (yyval.type) = tmp;
    }
#line 2097 "final_work.tab.c"
    break;

  case 95: /* primary: STRING_LITERAL  */
#line 442 "final_work.y"
                   {
      TypeInfo tmp;
      tmp.type = TYPE_STRING;
      tmp.data.s = (yyvsp[0].sval);
      (yyval.type) = tmp;
    }
#line 2108 "final_work.tab.c"
    break;

  case 96: /* primary: BOOLEAN_LITERAL  */
#line 448 "final_work.y"
                    {
      TypeInfo tmp;
      tmp.type = TYPE_BOOL;
      tmp.data.b = (yyvsp[0].bval);
      (yyval.type) = tmp;
    }
#line 2119 "final_work.tab.c"
    break;

  case 97: /* primary: L_PAREN expression R_PAREN  */
#line 454 "final_work.y"
                               {
    (yyval.type) = (yyvsp[-1].type);
  }
#line 2127 "final_work.tab.c"
    break;

  case 123: /* write: WRITELN L_PAREN write_args R_PAREN  */
#line 543 "final_work.y"
                                       {
    printf("\n");
  }
#line 2135 "final_work.tab.c"
    break;

  case 124: /* write: WRITELN  */
#line 546 "final_work.y"
            {
    printf("\n");
  }
#line 2143 "final_work.tab.c"
    break;

  case 127: /* write_arg: STRING_LITERAL  */
#line 557 "final_work.y"
                   { printf("%s", (yyvsp[0].sval)); }
#line 2149 "final_work.tab.c"
    break;

  case 128: /* write_arg: IDENTIFIER COLON INTEGER_LITERAL COLON INTEGER_LITERAL  */
#line 558 "final_work.y"
                                                             {
        printf(" [FORMAT: %s:%d:%d] ", (yyvsp[-4].sval), (yyvsp[-2].ival), (yyvsp[0].ival));
    }
#line 2157 "final_work.tab.c"
    break;

  case 129: /* write_arg: IDENTIFIER  */
#line 561 "final_work.y"
                 {
        Symbol* s = get_symbol_by_name((yyvsp[0].sval));
        if (s->type == TYPE_INT) {
          printf(" [INTEGER: %d] ", s->data.i);
        } else if (s->type == TYPE_REAL) {
          printf(" [REAL: %.2f] ", s->data.f);
        } else if (s->type == TYPE_CHAR) {
          printf(" [CHAR: %c] ", s->data.c);
        } else if (s->type == TYPE_BOOL) {
          printf(" [BOOL: %s] ", s->data.b ? "true" : "false");
        } else {
          printf(" [VARIAVEL: %s] ", (yyvsp[0].sval));
        }
    }
#line 2176 "final_work.tab.c"
    break;

  case 131: /* read: READ L_PAREN IDENTIFIER R_PAREN  */
#line 579 "final_work.y"
                                    {
      // $$ = make_stmt_read($1);
      // $$->lineno = @1.first_line;
      // $$->col = @1.first_column;
      printf("read: %s", (yyvsp[-1].sval));
    }
#line 2187 "final_work.tab.c"
    break;


#line 2191 "final_work.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 698 "final_work.y"


// StmtList* make_stmt_list(Stmt* stmt, StmtList* list) {
//   StmtList* new_node = (StmtList*) malloc(sizeof(StmtList));
//   new_node->stmt = stmt;
//   new_node->next = NULL;
//
//   if (list == NULL) {
//     return new_node;
//   }
//
//   StmtList* tail = list;
//   while (tail->next != NULL) {
//     tail = tail->next;
//   }
//
//   tail->next = new_node;
//   return list;
// }
//
// Stmt* make_stmt_write(char* var_name, Expr* expr) {
//   Stmt* s = (Stmt*) malloc(sizeof(Stmt));
//   s->type = STMT_WRITE;
//   if (var_name != NULL) {
//     s->write.var_name = strdup(var_name);
//   }
//   s->write.expr = expr;
//   return s;
// }
//
// Stmt* make_stmt_read(char* var_name) {
//   Stmt* s = (Stmt*) malloc(sizeof(Stmt));
//   s->type = STMT_READ;
//   s->read.var_name = strdup(var_name);
//   return s;
// }
//
// Stmt* make_stmt_if(Expr* cond, StmtList* then_block, StmtList* else_block) {
//   Stmt* s = (Stmt*) malloc(sizeof(Stmt));
//   s->type = STMT_IF;
//   s->if_stmt.cond = cond;
//   s->if_stmt.then_block = then_block;
//   s->if_stmt.else_block = else_block;
//   return s;
// }
//
// Stmt* make_stmt_while(Expr* cond, StmtList* body) {
//   Stmt* s = (Stmt*) malloc(sizeof(Stmt));
//   s->type = STMT_WHILE;
//   s->while_stmt.cond = cond;
//   s->while_stmt.body = body;
//   return s;
// }
//
// Expr* make_literal_expr(VarType type, Value val, bool uminus) {
//   Expr* e = (Expr*) malloc(sizeof(Expr));
//   memset(e, 0, sizeof(Expr));
//
//   e->type = EXPR_LITERAL;
//   e->literal.type = type;
//
//   switch (type) {
//     case TYPE_BOOL:
//       e->literal.data.b = val.data.b;
//       break;
//     case TYPE_INT:
//       e->literal.data.i = uminus ? -val.data.i : val.data.i;
//       break;
//     case TYPE_CHAR:
//       e->literal.data.c = val.data.c;
//       break;
//     case TYPE_REAL:
//       e->literal.data.f = uminus ? -val.data.f : val.data.f;
//       break;
//     case TYPE_STRING:
//       e->literal.data.s = strdup(val.data.s);
//       break;
//     default:
//       break;
//   }
//   return e;
// }
//
// Expr* make_var_expr(char* name) {
//   Expr* e = (Expr*) malloc(sizeof(Expr));
//   e->type = EXPR_VAR;
//   e->var_name = strdup(name);
//   return e;
// }
//
// Expr* make_arith_expr(Expr* left, Expr* right, ArithmeticOp op) {
//   Expr* e = (Expr*) malloc(sizeof(Expr));
//   e->type = EXPR_ARITH;
//   e->arith.left = left;
//   e->arith.right = right;
//   e->arith.op = op;
//   return e;
// }
//
// Expr* make_logic_expr(Expr* left, Expr* right, Operation op) {
//   Expr* e = (Expr*) malloc(sizeof(Expr));
//   e->type = EXPR_LOGIC;
//   e->logic.left = left;
//   e->logic.right = right;
//   e->logic.op = op;
//   return e;
// }
//
// Stmt* make_stmt_ASSIGN(char* variable, Expr* expr) {
//   Stmt* s = (Stmt*) malloc(sizeof(Stmt));
//   s->type = STMT_ASSIGN;
//   s->assign.var_name = strdup(variable);
//   s->assign.expr = expr;
//   return s;
// }
//
// Value evaluate_factor_expr(Expr* e) {
//   Value result;
//
//   if (e->type == EXPR_VAR && e->var_name != NULL && strlen(e->var_name) > 0) {
//     Symbol* symb = get_symbol_by_name(e->var_name);
//
//     result.type = symb->type;
//
//     switch (result.type) {
//       case TYPE_INT:
//         result.data.i = symb->data.i;
//         break;
//       case TYPE_REAL:
//         result.data.f = symb->data.f;
//         break;
//       case TYPE_BOOL:
//         result.data.b = symb->data.b;
//         break;
//       case TYPE_CHAR:
//         result.data.c = symb->data.c;
//         break;
//       default:
//         break;
//     }
//   } else if (e->type == EXPR_LITERAL) {
//     result = e->literal;
//   } else {
//     fprintf(stderr,
//       "Erro: expressão inesperada em evaluate_factor_expr\n"
//       "  Tipo da expressão: %d\n"
//       "  Ponteiro da expressão: %p\n"
//       "  var_name: %s\n"
//       "  literal.type: %d\n"
//       "  line: %d and column: %d\n",
//       e->type,
//       (void*)e,
//       e->var_name ? e->var_name : "(null)",
//       e->literal.type,
//       e->lineno,
//       e->col
//     );
//     exit(1);
//   }
//
//   return result;
// }
//
// Value evaluate_arithmetic_expr(Expr* e) {
//   Value value;
//
//   if (e->type != EXPR_ARITH) {
//     return evaluate_factor_expr(e);
//   } 
//
//   Value t1 = e->arith.left != NULL ? evaluate_arithmetic_expr(e->arith.left) : value;
//   Value t2 = evaluate_arithmetic_expr(e->arith.right);
//   
//   switch (e->arith.op) {
//     case AOP_PLUS: {
//       if (t1.type == TYPE_INT && t2.type == TYPE_INT) {
//         value.type = TYPE_INT;
//         value.data.i = t1.data.i + t2.data.i;
//         return value;
//       }
//   
//       value.type = TYPE_REAL;
//       value.data.f = (t1.type == TYPE_INT ? (double)t1.data.i : t1.data.f) + (t2.type == TYPE_INT ? (double)t2.data.i : t2.data.f);
//       return value;
//     }
//     case AOP_MINUS: {
//       if (t1.type == TYPE_INT && t2.type == TYPE_INT) {
//         value.type = TYPE_INT;
//         value.data.i = t1.data.i - t2.data.i;
//         return value;
//       }
//       
//       value.type = TYPE_REAL;
//       value.data.f = (t1.type == TYPE_INT ? (double)t1.data.i : t1.data.f) - (t2.type == TYPE_INT ? (double)t2.data.i : t2.data.f);
//       return value;
//     }
//     case AOP_TIMES: {
//       if (t1.type == TYPE_INT && t2.type == TYPE_INT) {
//         value.type = TYPE_INT;
//         value.data.i = t1.data.i * t2.data.i;
//         return value;
//       }
//       
//       value.type = TYPE_REAL;
//       value.data.f = (t1.type == TYPE_INT ? (double)t1.data.i : t1.data.f) * (t2.type == TYPE_INT ? (double)t2.data.i : t2.data.f);
//       return value;
//     }
//     case AOP_DIVIDE: {
//       if (t1.type == TYPE_INT && t2.type == TYPE_INT) {
//         value.type = TYPE_INT;
//         value.data.i = t1.data.i / t2.data.i;
//         return value;
//       }
//       
//       value.type = TYPE_REAL;
//       value.data.f = (t1.type == TYPE_INT ? (double)t1.data.i : t1.data.f) / (t2.type == TYPE_INT ? (double)t2.data.i : t2.data.f);
//       return value;
//     }
//     case AOP_UMINUS: {
//       if (t2.type == TYPE_INT) {
//         value.type = TYPE_INT;
//         value.data.i = -t2.data.i;
//         return value;
//       }
//
//       value.type = TYPE_REAL;
//       value.data.f = -t2.data.i;
//       return value;
//     }
//     default:
//       return value;
//   }
//   
// }
//
// Value evaluate_logical_expr(Expr* e) {
//   Value t1, t2, result;
//
//   result.type = TYPE_BOOL;
//
//   switch (e->logic.op) {
//     case OP_GT: {
//       t1 = evaluate_arithmetic_expr(e->logic.left);
//       t2 = evaluate_arithmetic_expr(e->logic.right);
//       if (t1.type == TYPE_INT && t2.type == TYPE_INT) {
//         result.data.b = t1.data.i > t2.data.i;
//       } else {
//         result.data.b = t1.data.f > t2.data.f;
//       }
//       return result;
//     }
//     case OP_GTE: {
//       t1 = evaluate_arithmetic_expr(e->logic.left);
//       t2 = evaluate_arithmetic_expr(e->logic.right);
//       if (t1.type == TYPE_INT && t2.type == TYPE_INT) {
//         result.data.b = t1.data.i >= t2.data.i;
//       } else {
//         result.data.b = t1.data.f >= t2.data.f;
//       }
//       return result;
//     }
//     case OP_LT: {
//       t1 = evaluate_arithmetic_expr(e->logic.left);
//       t2 = evaluate_arithmetic_expr(e->logic.right);
//       if (t1.type == TYPE_INT && t2.type == TYPE_INT) {
//         result.data.b = t1.data.i < t2.data.i;
//       } else {
//         result.data.b = t1.data.f < t2.data.f;
//       }
//       return result;
//     }
//     case OP_LTE: {
//       t1 = evaluate_arithmetic_expr(e->logic.left);
//       t2 = evaluate_arithmetic_expr(e->logic.right);
//       if (t1.type == TYPE_INT && t2.type == TYPE_INT) {
//         result.data.b = t1.data.i <= t2.data.i;
//       } else {
//         result.data.b = t1.data.f <= t2.data.f;
//       }
//       return result;
//     }
//     case OP_EQ: {
//       t1 = evaluate_arithmetic_expr(e->logic.left);
//       t2 = evaluate_arithmetic_expr(e->logic.right);
//       if (t1.type == TYPE_INT && t2.type == TYPE_INT) {
//         result.data.b = t1.data.i == t2.data.i;
//       } else {
//         result.data.b = t1.data.f == t2.data.f;
//       }
//       return result;
//     }
//     case OP_NEQ: {
//       t1 = evaluate_arithmetic_expr(e->logic.left);
//       t2 = evaluate_arithmetic_expr(e->logic.right);
//       if (t1.type == TYPE_INT && t2.type == TYPE_INT) {
//         result.data.b = t1.data.i != t2.data.i;
//       } else {
//         result.data.b = t1.data.f != t2.data.f;
//       }
//       return result;
//     }
//     case OP_AND: {
//       t1 = evaluate_logical_expr(e->logic.left);
//       t2 = evaluate_logical_expr(e->logic.right);
//       result.data.b = t1.data.b && t2.data.b;
//       return result;
//     }
//     case OP_OR: {
//       t1 = evaluate_logical_expr(e->logic.left);
//       t2 = evaluate_logical_expr(e->logic.right);
//       result.data.b = t1.data.b || t2.data.b;
//       return result;
//     } 
//     default:
//       return result;
//   }
// }
//
// void print_symbol(Symbol symb) {
//   switch (symb.type) {
//     case TYPE_INT:
//       printf("%d\n", symb.data.i);
//       break;
//     case TYPE_REAL:
//       printf("%.2f\n", symb.data.f);
//       break;
//     case TYPE_BOOL:
//      printf("%s\n", symb.data.b == 1 ? "true" : "false");
//       break;
//     case TYPE_CHAR:
//       printf("%c\n", symb.data.c);
//       break;
//     case TYPE_STRING:
//       printf("%s\n", symb.data.s);
//       break;
//   }
// }
//
// void print_value(Value v) {
//   switch (v.type) {
//     case TYPE_INT:
//       printf("%d\n", v.data.i);
//       break;
//     case TYPE_REAL:
//       printf("%.2f\n", v.data.f);
//       break;
//     case TYPE_CHAR:
//       printf("%c\n", v.data.c);
//       break;
//     case TYPE_STRING:
//       printf("%s\n", v.data.s);
//       break;
//     case TYPE_BOOL:
//       printf("%s\n", v.data.b == 1 ? "true" : "false");
//       break;
//     default:
//       printf("Erro: tipo de valor desconhecido\n");
//       break;
//   }
// }
//
int yywrap( ) {
  return 1;
}

// void yyerror(const char* str) {
//   fprintf(stderr, "Compiler error: '%s'.\n", str);
//   exit(1);
// }

int main(int argc, char** argv) {
  if (argc > 1) {
      yyin = fopen(argv[1], "r");
      if (!yyin) {
        perror("Error open file");
        return 1;
      }
    } else {
      yyin = stdin;
    }

    yyparse();

    if (yyin != stdin) {
        fclose(yyin);
    }

    return 0;
}
//
// void print_expr(Expr* e) {
//   if (!e) {
//     fprintf(stderr, "Expr: NULL\n");
//     return;
//   }
//
//   fprintf(stderr, "Expr type: %d\n", e->type);
//
//   switch (e->type) {
//     case EXPR_LITERAL:
//       fprintf(stderr, "  Literal type: %d\n", e->literal.type);
//       switch (e->literal.type) {
//         case TYPE_INT:
//           fprintf(stderr, "  Literal int: %d\n", e->literal.data.i);
//           break;
//         case TYPE_REAL:
//           fprintf(stderr, "  Literal REAL: %.2f\n", e->literal.data.f);
//           break;
//         case TYPE_BOOL:
//           fprintf(stderr, "  Literal bool: %s\n", e->literal.data.b ? "true" : "false");
//           break;
//         case TYPE_CHAR:
//           fprintf(stderr, "  Literal char: %c\n", e->literal.data.c);
//           break;
//         case TYPE_STRING:
//           fprintf(stderr, "  Literal string: %s\n", e->literal.data.s);
//           break;
//       }
//       break;
//
//     case EXPR_VAR:
//       fprintf(stderr, "  Variable name: %s\n", e->var_name);
//       break;
//
//     case EXPR_ARITH:
//       fprintf(stderr, "  Arith op: %d\n", e->arith.op);
//       fprintf(stderr, "  Left:\n");
//       print_expr(e->arith.left);
//       if (e->arith.right) {
//         fprintf(stderr, "  Right:\n");
//         print_expr(e->arith.right);
//       }
//       break;
//
//     case EXPR_LOGIC:
//       fprintf(stderr, "  Logic op: %d\n", e->logic.op);
//       fprintf(stderr, "  Left:\n");
//       print_expr(e->logic.left);
//       if (e->logic.right) {
//         fprintf(stderr, "  Right:\n");
//         print_expr(e->logic.right);
//       }
//       break;
//
//     default:
//       fprintf(stderr, "  (Unknown expression type)\n");
//       break;
//   }
// }
