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
#line 3 "final_work.y"

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "symbol_table.h"
#include "types.h"

#line 79 "final_work.tab.c"

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
  YYSYMBOL_declaration = 81,               /* declaration  */
  YYSYMBOL_label_declaration = 82,         /* label_declaration  */
  YYSYMBOL_unsigned_integer_list = 83,     /* unsigned_integer_list  */
  YYSYMBOL_constant_declaration = 84,      /* constant_declaration  */
  YYSYMBOL_const_assignment_list = 85,     /* const_assignment_list  */
  YYSYMBOL_const_assignment = 86,          /* const_assignment  */
  YYSYMBOL_constant = 87,                  /* constant  */
  YYSYMBOL_type_declaration = 88,          /* type_declaration  */
  YYSYMBOL_type_assignment_list = 89,      /* type_assignment_list  */
  YYSYMBOL_variable_declaration = 90,      /* variable_declaration  */
  YYSYMBOL_variable_declaration_list = 91, /* variable_declaration_list  */
  YYSYMBOL_variable_list_type = 92,        /* variable_list_type  */
  YYSYMBOL_variable_list = 93,             /* variable_list  */
  YYSYMBOL_type = 94,                      /* type  */
  YYSYMBOL_field_list = 95,                /* field_list  */
  YYSYMBOL_field_decl = 96,                /* field_decl  */
  YYSYMBOL_procedure_declaration = 97,     /* procedure_declaration  */
  YYSYMBOL_function_declaration = 98,      /* function_declaration  */
  YYSYMBOL_param_list = 99,                /* param_list  */
  YYSYMBOL_param_seq = 100,                /* param_seq  */
  YYSYMBOL_statement_list = 101,           /* statement_list  */
  YYSYMBOL_statement = 102,                /* statement  */
  YYSYMBOL_assign = 103,                   /* assign  */
  YYSYMBOL_compound_stmt = 104,            /* compound_stmt  */
  YYSYMBOL_procedure_stmt = 105,           /* procedure_stmt  */
  YYSYMBOL_if_stmt = 106,                  /* if_stmt  */
  YYSYMBOL_case_stmt = 107,                /* case_stmt  */
  YYSYMBOL_case_list = 108,                /* case_list  */
  YYSYMBOL_case_elem = 109,                /* case_elem  */
  YYSYMBOL_repeat_stmt = 110,              /* repeat_stmt  */
  YYSYMBOL_goto_stmt = 111,                /* goto_stmt  */
  YYSYMBOL_while_stmt = 112,               /* while_stmt  */
  YYSYMBOL_for_stmt = 113,                 /* for_stmt  */
  YYSYMBOL_expression_list = 114,          /* expression_list  */
  YYSYMBOL_expr = 115,                     /* expr  */
  YYSYMBOL_term = 116,                     /* term  */
  YYSYMBOL_var_access = 117,               /* var_access  */
  YYSYMBOL_func_call = 118,                /* func_call  */
  YYSYMBOL_array_access = 119,             /* array_access  */
  YYSYMBOL_record_access = 120,            /* record_access  */
  YYSYMBOL_literals = 121,                 /* literals  */
  YYSYMBOL_const_numbers = 122,            /* const_numbers  */
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


#ifdef NDEBUG
# define YY_ASSERT(E) ((void) (0 && (E)))
#else
# include <assert.h> /* INFRINGES ON USER NAME SPACE */
# define YY_ASSERT(E) assert (E)
#endif


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
#define YYLAST   448

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  75
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  52
/* YYNRULES -- Number of rules.  */
#define YYNRULES  137
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  284

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
       0,   113,   113,   117,   118,   122,   123,   127,   131,   132,
     136,   137,   138,   139,   140,   141,   145,   152,   153,   157,
     165,   166,   170,   176,   182,   188,   194,   200,   207,   217,
     227,   235,   249,   257,   258,   275,   289,   295,   306,   311,
     316,   321,   326,   331,   342,   348,   363,   364,   373,   383,
     390,   397,   398,   402,   409,   422,   423,   427,   428,   429,
     430,   431,   432,   433,   435,   436,   437,   441,   442,   443,
     447,   451,   457,   463,   476,   477,   481,   485,   486,   490,
     491,   492,   496,   500,   504,   508,   509,   513,   514,   515,
     519,   522,   529,   536,   543,   550,   557,   564,   571,   578,
     585,   592,   599,   606,   613,   620,   627,   634,   635,   639,
     640,   646,   647,   648,   657,   666,   673,   683,   690,   700,
     707,   717,   720,   727,   734,   744,   750,   759,   765,   771,
     780,   781,   787,   793,   806,   828,   837,   843
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
  "identifier_list", "block", "declarations", "declaration",
  "label_declaration", "unsigned_integer_list", "constant_declaration",
  "const_assignment_list", "const_assignment", "constant",
  "type_declaration", "type_assignment_list", "variable_declaration",
  "variable_declaration_list", "variable_list_type", "variable_list",
  "type", "field_list", "field_decl", "procedure_declaration",
  "function_declaration", "param_list", "param_seq", "statement_list",
  "statement", "assign", "compound_stmt", "procedure_stmt", "if_stmt",
  "case_stmt", "case_list", "case_elem", "repeat_stmt", "goto_stmt",
  "while_stmt", "for_stmt", "expression_list", "expr", "term",
  "var_access", "func_call", "array_access", "record_access", "literals",
  "const_numbers", "write", "write_args", "write_arg", "read", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-229)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      26,   -33,    46,    -6,  -229,   -14,     9,  -229,   -29,  -229,
     -10,  -229,    21,   343,  -229,  -229,    15,    28,    36,    30,
      37,    38,    -2,  -229,  -229,  -229,  -229,  -229,    54,    69,
    -229,    75,  -229,    32,    90,    78,  -229,    94,    83,  -229,
      48,    81,    84,    -2,   118,   118,    72,    -2,   118,    80,
      85,    88,    89,    92,    -1,     1,  -229,  -229,  -229,  -229,
    -229,  -229,  -229,  -229,  -229,  -229,    42,   103,  -229,  -229,
    -229,  -229,    15,    79,   127,   159,    28,   127,    91,  -229,
      93,    95,    95,     3,   118,   118,   118,  -229,  -229,  -229,
    -229,  -229,    10,   108,   199,  -229,  -229,  -229,   115,  -229,
    -229,  -229,   229,   114,    -5,   317,  -229,   100,   -31,   102,
     -31,   104,   118,   118,   134,  -229,    -2,   105,   118,   118,
    -229,  -229,  -229,  -229,  -229,  -229,   110,   106,  -229,  -229,
    -229,   111,   120,  -229,  -229,  -229,  -229,  -229,  -229,  -229,
     135,  -229,   133,   138,   139,   151,  -229,   276,   223,   350,
     118,   118,    -2,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,    -2,   118,   118,
      66,   163,  -229,    29,   115,  -229,   -19,  -229,   164,     4,
    -229,   276,    18,   276,   130,   332,  -229,  -229,   276,   276,
     159,   172,    -4,   176,  -229,  -229,   127,   127,   178,   165,
     196,  -229,    24,   373,   241,   365,   365,   365,   365,   365,
     365,   223,   223,   396,   396,   177,   177,   177,   177,  -229,
     294,   276,  -229,   198,   200,   234,    13,  -229,  -229,   239,
     -31,  -229,  -229,  -229,   118,  -229,  -229,  -229,   268,   127,
    -229,   273,  -229,  -229,  -229,  -229,   272,   127,  -229,  -229,
      -2,   118,   118,    -2,  -229,  -229,  -229,   296,  -229,   276,
     159,  -229,  -229,  -229,   127,   275,  -229,   244,   259,   307,
     312,   321,  -229,  -229,    -2,    -2,  -229,  -229,   363,  -229,
    -229,  -229,   127,  -229
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     3,     1,     0,     0,     5,     0,     8,
       0,     4,     0,     0,     6,     2,     0,     0,     0,     0,
       0,     0,    66,     9,    10,    11,    12,    13,     0,     0,
      36,     0,    33,     0,     0,     0,    20,     0,     0,    17,
       0,     0,     0,    66,     0,     0,     0,    66,     0,     0,
       0,     0,     0,   129,     0,     0,    55,    57,    63,    64,
      58,    62,    61,    65,    59,    60,     0,     0,    72,    71,
      14,    15,    32,     0,     0,     0,    19,     0,    29,    16,
       0,    51,    51,     0,     0,     0,     0,   124,   125,   122,
     126,   123,   110,     0,     0,   108,   113,   107,   111,   112,
     109,   121,     0,     0,     0,     0,    83,     0,     0,     0,
       0,     0,     0,    89,     0,     7,    66,     0,     0,     0,
      34,    37,    38,    40,    42,    41,     0,     0,    39,    45,
      35,     0,     0,    23,    25,    24,    26,    22,    21,    30,
       0,    18,     0,     0,    52,     0,    70,   105,   106,     0,
      89,     0,    66,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    66,     0,     0,
       0,     0,   132,   134,     0,   135,     0,   130,     0,     0,
     119,    67,     0,    87,   125,     0,    56,   120,    69,    68,
       0,     0,     0,     0,    27,    28,     0,     0,     0,     0,
       0,    90,     0,     0,    74,   101,   102,    99,   100,    97,
      98,   104,   103,    91,    92,    93,    94,    95,    96,    84,
       0,    82,    80,     0,     0,     0,     0,    78,   136,     0,
       0,   127,   137,   128,     0,    73,   118,   117,     0,     0,
      44,     0,    46,    31,    53,     8,     0,     0,   115,   116,
      66,     0,     0,    66,    81,    76,    77,     0,   131,    88,
       0,    48,    47,    49,     0,     0,    75,     0,     0,     0,
       0,     0,    54,     8,    66,    66,    79,   133,     0,    50,
      85,    86,     0,    43
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -229,  -229,  -229,  -229,  -228,  -229,  -229,  -229,  -229,  -229,
    -229,   311,  -189,  -229,  -229,  -229,  -229,   337,  -229,   -68,
    -229,   227,  -229,  -229,   344,  -229,   -24,  -112,  -229,  -229,
    -159,  -229,  -229,  -229,   201,  -229,  -229,  -229,  -229,   278,
     -42,  -229,  -229,  -229,   -22,   -17,  -229,  -229,  -229,   319,
     202,  -229
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     6,     8,    12,    13,    23,    24,    40,    25,
      35,    36,   137,    26,    38,    27,    31,    32,    33,   130,
     192,   193,    28,    29,   143,   144,    55,    56,    57,    58,
      59,    60,    61,   226,   227,    62,    63,    64,    65,   182,
     183,    95,    96,    97,    98,    99,   100,   101,    68,   176,
     177,    69
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      66,   238,    94,   102,   186,    67,   105,   240,    43,   139,
      44,   225,   115,    45,   146,    46,   169,   263,    47,    83,
      48,    66,    49,   104,   255,    66,    67,   222,    10,     1,
      67,    11,    50,    51,    52,    53,   172,     3,   230,   173,
     204,   231,   147,   148,   149,   279,     4,    50,    51,    52,
      53,   116,   111,     5,   112,   219,     7,   116,   113,   116,
      14,   230,   114,   111,   233,     9,   191,   225,    54,   150,
     181,   271,   185,   114,    15,   234,   188,   189,   235,   223,
     222,   234,   111,   224,   248,    30,   174,   229,   174,    73,
      74,   175,   114,   175,    66,   117,    39,   118,    34,    67,
      50,    51,    52,    53,    79,    80,    37,    41,    42,   203,
      70,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,    71,   220,   221,   243,   244,
      66,    72,   223,    75,    76,    67,   224,    77,   266,    78,
      81,   269,   103,    82,   107,    66,   106,   108,   109,   121,
      67,   110,   122,   123,   124,   125,   126,   127,   119,   141,
     128,   140,   280,   281,    84,   142,    85,   151,   117,   168,
     171,   261,   178,   190,   180,   187,   191,    86,   196,   265,
      84,   194,    85,    87,    88,    89,    90,    91,    92,    93,
     195,   197,   259,    86,   236,   199,   272,   129,   198,    87,
     184,    89,    90,    91,    92,    93,   131,   132,   174,   267,
     268,   200,   152,   175,   283,   153,   154,   155,   156,   157,
     158,   159,   160,   228,   232,   133,   134,   135,    66,   136,
     239,    66,   242,    67,   245,   246,    67,   153,   154,   155,
     156,   157,   158,   159,   160,   167,   161,   162,   163,   164,
     165,   166,    66,    66,   247,   250,   253,    67,    67,   113,
     274,   153,   154,   155,   156,   157,   158,   153,   154,   155,
     156,   157,   158,   159,   160,   275,   161,   162,   163,   164,
     165,   166,   153,   154,   155,   156,   157,   158,   159,   160,
     254,   161,   162,   163,   164,   165,   166,   153,   154,   155,
     156,   157,   158,   159,   160,   257,   161,   162,   163,   164,
     165,   166,   251,   252,   153,   154,   155,   156,   157,   158,
     159,   160,   260,   161,   162,   163,   164,   165,   166,   262,
     264,   273,   153,   154,   155,   156,   157,   158,   159,   160,
     170,   161,   162,   163,   164,   165,   166,    16,    17,    18,
      19,    20,    21,    22,   270,   153,   154,   155,   156,   157,
     158,   159,   160,   276,   161,   162,   163,   164,   165,   166,
     153,   154,   155,   156,   157,   158,   159,   160,   277,   161,
     162,   163,   164,   165,   166,   278,   282,   138,   153,   154,
     155,   156,   157,   158,   159,   160,   237,   161,   162,   163,
     164,   165,   166,    -1,    -1,    -1,    -1,    -1,    -1,   120,
     201,   153,   154,   155,   156,   157,   158,   159,   160,   241,
     161,   162,   163,   164,   165,   166,   145,   256,   202,   179,
       0,     0,   258,   249,   153,   154,   155,   156,   157,   158,
     159,   160,     0,     0,     0,   163,   164,   165,   166
};

static const yytype_int16 yycheck[] =
{
      22,   190,    44,    45,   116,    22,    48,    11,    10,    77,
      12,   170,    11,    15,    11,    17,    21,   245,    20,    43,
      22,    43,    24,    47,    11,    47,    43,    14,    57,     3,
      47,    60,    34,    35,    36,    37,    67,    70,    57,    70,
     152,    60,    84,    85,    86,   273,     0,    34,    35,    36,
      37,    56,    53,    59,    55,   167,    70,    56,    59,    56,
      70,    57,    63,    53,    60,    56,    70,   226,    70,    59,
     112,   260,   114,    63,    53,    57,   118,   119,    60,    66,
      14,    57,    53,    70,    60,    70,   108,    58,   110,    57,
      58,   108,    63,   110,   116,    53,    66,    55,    70,   116,
      34,    35,    36,    37,    56,    57,    70,    70,    70,   151,
      56,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,    56,   168,   169,   196,   197,
     152,    56,    66,    43,    56,   152,    70,    43,   250,    56,
      59,   253,    70,    59,    59,   167,    66,    59,    59,    70,
     167,    59,    25,    26,    27,    28,    29,    30,    55,    66,
      33,    70,   274,   275,    46,    70,    48,    59,    53,    55,
      70,   239,    70,    63,    70,    70,    70,    59,    43,   247,
      46,    70,    48,    65,    66,    67,    68,    69,    70,    71,
      70,    58,   234,    59,    64,    56,   264,    70,    60,    65,
      66,    67,    68,    69,    70,    71,    47,    48,   230,   251,
     252,    60,    13,   230,   282,    38,    39,    40,    41,    42,
      43,    44,    45,    60,    60,    66,    67,    68,   250,    70,
      58,   253,    56,   250,    56,    70,   253,    38,    39,    40,
      41,    42,    43,    44,    45,    16,    47,    48,    49,    50,
      51,    52,   274,   275,    58,    14,    58,   274,   275,    59,
      16,    38,    39,    40,    41,    42,    43,    38,    39,    40,
      41,    42,    43,    44,    45,    16,    47,    48,    49,    50,
      51,    52,    38,    39,    40,    41,    42,    43,    44,    45,
      56,    47,    48,    49,    50,    51,    52,    38,    39,    40,
      41,    42,    43,    44,    45,    66,    47,    48,    49,    50,
      51,    52,    18,    19,    38,    39,    40,    41,    42,    43,
      44,    45,    54,    47,    48,    49,    50,    51,    52,    56,
      58,    56,    38,    39,    40,    41,    42,    43,    44,    45,
      23,    47,    48,    49,    50,    51,    52,     4,     5,     6,
       7,     8,     9,    10,    58,    38,    39,    40,    41,    42,
      43,    44,    45,    56,    47,    48,    49,    50,    51,    52,
      38,    39,    40,    41,    42,    43,    44,    45,    66,    47,
      48,    49,    50,    51,    52,    64,    23,    76,    38,    39,
      40,    41,    42,    43,    44,    45,    64,    47,    48,    49,
      50,    51,    52,    38,    39,    40,    41,    42,    43,    72,
      60,    38,    39,    40,    41,    42,    43,    44,    45,   192,
      47,    48,    49,    50,    51,    52,    82,   226,   150,   110,
      -1,    -1,   230,    60,    38,    39,    40,    41,    42,    43,
      44,    45,    -1,    -1,    -1,    49,    50,    51,    52
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    76,    70,     0,    59,    77,    70,    78,    56,
      57,    60,    79,    80,    70,    53,     4,     5,     6,     7,
       8,     9,    10,    81,    82,    84,    88,    90,    97,    98,
      70,    91,    92,    93,    70,    85,    86,    70,    89,    66,
      83,    70,    70,    10,    12,    15,    17,    20,    22,    24,
      34,    35,    36,    37,    70,   101,   102,   103,   104,   105,
     106,   107,   110,   111,   112,   113,   119,   120,   123,   126,
      56,    56,    56,    57,    58,    43,    56,    43,    56,    56,
      57,    59,    59,   101,    46,    48,    59,    65,    66,    67,
      68,    69,    70,    71,   115,   116,   117,   118,   119,   120,
     121,   122,   115,    70,   101,   115,    66,    59,    59,    59,
      59,    53,    55,    59,    63,    11,    56,    53,    55,    55,
      92,    70,    25,    26,    27,    28,    29,    30,    33,    70,
      94,    47,    48,    66,    67,    68,    70,    87,    86,    94,
      70,    66,    70,    99,   100,    99,    11,   115,   115,   115,
      59,    59,    13,    38,    39,    40,    41,    42,    43,    44,
      45,    47,    48,    49,    50,    51,    52,    16,    55,    21,
      23,    70,    67,    70,   119,   120,   124,   125,    70,   124,
      70,   115,   114,   115,    66,   115,   102,    70,   115,   115,
      63,    70,    95,    96,    70,    70,    43,    58,    60,    56,
      60,    60,   114,   115,   102,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   102,
     115,   115,    14,    66,    70,   105,   108,   109,    60,    58,
      57,    60,    60,    60,    57,    60,    64,    64,    87,    58,
      11,    96,    56,    94,    94,    56,    70,    58,    60,    60,
      14,    18,    19,    58,    56,    11,   109,    66,   125,   115,
      54,    94,    56,    79,    58,    94,   102,   115,   115,   102,
      58,    87,    94,    56,    16,    16,    56,    66,    64,    79,
     102,   102,    23,    94
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    75,    76,    77,    77,    78,    78,    79,    80,    80,
      81,    81,    81,    81,    81,    81,    82,    83,    83,    84,
      85,    85,    86,    87,    87,    87,    87,    87,    87,    88,
      89,    89,    90,    91,    91,    92,    93,    93,    94,    94,
      94,    94,    94,    94,    94,    94,    95,    95,    96,    97,
      98,    99,    99,   100,   100,   101,   101,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   103,   103,   103,
     104,   105,   105,   105,   106,   106,   107,   108,   108,   109,
     109,   109,   110,   111,   112,   113,   113,   114,   114,   114,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   116,
     116,   116,   116,   116,   117,   118,   118,   119,   119,   120,
     120,   121,   121,   121,   121,   122,   122,   123,   123,   123,
     124,   124,   125,   125,   125,   125,   126,   126
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     6,     0,     3,     1,     3,     4,     0,     2,
       1,     1,     1,     1,     2,     2,     3,     1,     3,     3,
       1,     3,     3,     1,     1,     1,     1,     2,     2,     3,
       3,     5,     3,     1,     3,     3,     1,     3,     1,     1,
       1,     1,     1,     8,     3,     1,     2,     3,     3,     7,
       9,     0,     1,     3,     5,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     3,     3,     3,
       3,     1,     1,     4,     4,     6,     5,     2,     1,     4,
       1,     2,     4,     2,     4,     8,     8,     1,     3,     0,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     4,     4,     4,     3,
       3,     1,     1,     1,     1,     1,     1,     4,     4,     1,
       1,     3,     1,     5,     1,     1,     4,     4
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
#line 113 "final_work.y"
                                                     { /* tac_print(generate_stmt_list_tac($2));*/ }
#line 1820 "final_work.tab.c"
    break;

  case 3: /* heading: %empty  */
#line 117 "final_work.y"
           {}
#line 1826 "final_work.tab.c"
    break;

  case 8: /* declarations: %empty  */
#line 131 "final_work.y"
           { (yyval.decl) = NULL; }
#line 1832 "final_work.tab.c"
    break;

  case 9: /* declarations: declarations declaration  */
#line 132 "final_work.y"
                             {}
#line 1838 "final_work.tab.c"
    break;

  case 10: /* declaration: label_declaration  */
#line 136 "final_work.y"
                      { (yyval.decl) = (struct Decl*)(yyvsp[0].label_decl); }
#line 1844 "final_work.tab.c"
    break;

  case 11: /* declaration: constant_declaration  */
#line 137 "final_work.y"
                         { (yyval.decl) = (struct Decl*)(yyvsp[0].cons_decl); }
#line 1850 "final_work.tab.c"
    break;

  case 12: /* declaration: type_declaration  */
#line 138 "final_work.y"
                     { (yyval.decl) = (struct Decl*)(yyvsp[0].type_decl); }
#line 1856 "final_work.tab.c"
    break;

  case 13: /* declaration: variable_declaration  */
#line 139 "final_work.y"
                         { (yyval.decl) = (struct Decl*)(yyvsp[0].var_decl); }
#line 1862 "final_work.tab.c"
    break;

  case 14: /* declaration: procedure_declaration SEMICOLON  */
#line 140 "final_work.y"
                                    { (yyval.decl) = (struct Decl*)(yyvsp[-1].proc_decl); }
#line 1868 "final_work.tab.c"
    break;

  case 15: /* declaration: function_declaration SEMICOLON  */
#line 141 "final_work.y"
                                   { (yyval.decl) = (struct Decl*)(yyvsp[-1].func_decl); }
#line 1874 "final_work.tab.c"
    break;

  case 16: /* label_declaration: LABEL unsigned_integer_list SEMICOLON  */
#line 145 "final_work.y"
                                          {
      struct LabelDecl *lb = (LabelDecl*)malloc(sizeof *lb);
      (yyval.label_decl) = lb;
    }
#line 1883 "final_work.tab.c"
    break;

  case 19: /* constant_declaration: CONST const_assignment_list SEMICOLON  */
#line 157 "final_work.y"
                                        {
      struct ConstDecl *cd = (ConstDecl*)malloc(sizeof *cd);
      (yyval.cons_decl) = cd;
    }
#line 1892 "final_work.tab.c"
    break;

  case 22: /* const_assignment: IDENTIFIER EQ constant  */
#line 170 "final_work.y"
                           {
      fprintf(stderr, "vamos colocar na synbol table: %s: %d\n", (yyvsp[-2].string), (yyvsp[0].constant).ival);
    }
#line 1900 "final_work.tab.c"
    break;

  case 23: /* constant: INTEGER_LITERAL  */
#line 176 "final_work.y"
                    {
      Constant c;
      c.kind = C_INTEGER;
      c.ival = (yyvsp[0].integer);
      (yyval.constant) = c;
    }
#line 1911 "final_work.tab.c"
    break;

  case 24: /* constant: REAL_LITERAL  */
#line 182 "final_work.y"
                 {
      Constant c;
      c.kind = C_REAL;
      c.fval = (yyvsp[0].number);
      (yyval.constant) = c;
  }
#line 1922 "final_work.tab.c"
    break;

  case 25: /* constant: STRING_LITERAL  */
#line 188 "final_work.y"
                   {
      Constant c;
      c.kind = C_STRING;
      c.sval = (yyvsp[0].string);
      (yyval.constant) = c;
  }
#line 1933 "final_work.tab.c"
    break;

  case 26: /* constant: IDENTIFIER  */
#line 194 "final_work.y"
               {
      Constant c;
      c.kind = C_ID;
      c.id = strdup((yyvsp[0].string));
      (yyval.constant) = c;
    }
#line 1944 "final_work.tab.c"
    break;

  case 27: /* constant: PLUS IDENTIFIER  */
#line 200 "final_work.y"
                    {
      Constant c;
      c.kind = C_ID;
      c.op = '+';
      c.id = strdup((yyvsp[0].string));
      (yyval.constant) = c;
    }
#line 1956 "final_work.tab.c"
    break;

  case 28: /* constant: MINUS IDENTIFIER  */
#line 207 "final_work.y"
                     {
      Constant c;
      c.kind = C_ID;
      c.op = '-';
      c.id = strdup((yyvsp[0].string));
      (yyval.constant) = c;
    }
#line 1968 "final_work.tab.c"
    break;

  case 29: /* type_declaration: TYPE type_assignment_list SEMICOLON  */
#line 217 "final_work.y"
                                        {
      struct TypeDecl *tp = (TypeDecl*)malloc(sizeof *tp);
      tp->list = (yyvsp[-1].strlist);
      (yyval.type_decl) = tp;
      free((yyvsp[-1].strlist));
    }
#line 1979 "final_work.tab.c"
    break;

  case 30: /* type_assignment_list: IDENTIFIER EQ type  */
#line 227 "final_work.y"
                       {
      if (add_symbol((yyvsp[-2].string), SKIND_TYPE, (yyvsp[0].type)) == -1) {
        fprintf(stderr, "Error to declare variable %s\n", (yyvsp[-2].string));
      }
      (yyval.strlist)[0] = strdup((yyvsp[-2].string));
      (yyval.strlist)[1] = NULL;
      free((yyvsp[-2].string));
    }
#line 1992 "final_work.tab.c"
    break;

  case 31: /* type_assignment_list: type_assignment_list SEMICOLON IDENTIFIER EQ type  */
#line 235 "final_work.y"
                                                      {
      int i;
      for (i = 0; (yyvsp[-4].strlist)[i] != NULL; i++);
      if (add_symbol((yyvsp[-2].string), SKIND_TYPE, (yyvsp[0].type)) == -1) {
        fprintf(stderr, "Error to declare variable %s\n", (yyvsp[-2].string));
      }
      (yyvsp[-4].strlist)[i] = strdup((yyvsp[-2].string));
      (yyvsp[-4].strlist)[1+1] = NULL;
      free((yyvsp[-2].string));
      (yyval.strlist) = (yyvsp[-4].strlist);
    }
#line 2008 "final_work.tab.c"
    break;

  case 32: /* variable_declaration: VAR variable_declaration_list SEMICOLON  */
#line 249 "final_work.y"
                                            {
      struct VarDecl *vd = (VarDecl*)malloc(sizeof *vd);
      vd->list = (yyvsp[-1].strlist);
      (yyval.var_decl) = vd;
    }
#line 2018 "final_work.tab.c"
    break;

  case 33: /* variable_declaration_list: variable_list_type  */
#line 257 "final_work.y"
                       { (yyval.strlist) = (yyvsp[0].strlist); }
#line 2024 "final_work.tab.c"
    break;

  case 34: /* variable_declaration_list: variable_declaration_list SEMICOLON variable_list_type  */
#line 258 "final_work.y"
                                                           {
    int i;
    for (i = 0; (yyvsp[-2].strlist)[i] != NULL; i++);
    int j = 0;
    (yyval.strlist) = (char**)malloc(i * sizeof(char*));
    (yyval.strlist) = (yyvsp[-2].strlist);
    while((yyvsp[0].strlist)[j] != NULL) {
      char** tmp = (char**)realloc((yyval.strlist), (i+2) * sizeof(char*));
      tmp[i+j] = (yyvsp[0].strlist)[j];
      tmp[i+j+1] = NULL;
      j++;
      (yyval.strlist) = tmp;
    }
  }
#line 2043 "final_work.tab.c"
    break;

  case 35: /* variable_list_type: variable_list COLON type  */
#line 275 "final_work.y"
                             {
      TypeInfo *t = (yyvsp[0].type);
      for (int i = 0; (yyvsp[-2].strlist)[i] != NULL; i++) {
        if (add_symbol((yyvsp[-2].strlist)[i], SKIND_VAR, t) == -1) {
          fprintf(stderr, "Error to declare variable %s\n", (yyvsp[-2].strlist)[i]);
        }
        free((yyvsp[-2].strlist)[i]);
      }
      (yyval.strlist) = (yyvsp[-2].strlist);
      free((yyvsp[-2].strlist));
    }
#line 2059 "final_work.tab.c"
    break;

  case 36: /* variable_list: IDENTIFIER  */
#line 289 "final_work.y"
               {
      char** l = (char**)malloc(2*sizeof(char**));
      l[0] = strdup((yyvsp[0].string));
      l[1] = NULL;
      (yyval.strlist) = l;
    }
#line 2070 "final_work.tab.c"
    break;

  case 37: /* variable_list: variable_list COMMA IDENTIFIER  */
#line 295 "final_work.y"
                                   {
      int i;
      for (i = 0; (yyvsp[-2].strlist)[i] != NULL; i++);
      char** tmp = (char**)realloc((yyvsp[-2].strlist), (i+2) * sizeof(char*));
      tmp[i] = strdup((yyvsp[0].string));
      tmp[i+1] = NULL;
      (yyval.strlist) = tmp;
    }
#line 2083 "final_work.tab.c"
    break;

  case 38: /* type: INTEGER  */
#line 306 "final_work.y"
            {
      TypeInfo *tmp = (TypeInfo*)malloc(sizeof *tmp);
      tmp->kind = KIND_INT;
      (yyval.type) = tmp;
    }
#line 2093 "final_work.tab.c"
    break;

  case 39: /* type: STRING  */
#line 311 "final_work.y"
           {
      TypeInfo *tmp = (TypeInfo*)malloc(sizeof *tmp);
      tmp->kind = KIND_STRING;
      (yyval.type) = tmp;
  }
#line 2103 "final_work.tab.c"
    break;

  case 40: /* type: REAL  */
#line 316 "final_work.y"
         {
      TypeInfo *tmp = (TypeInfo*)malloc(sizeof *tmp);
      tmp->kind = KIND_REAL;
      (yyval.type) = tmp;
  }
#line 2113 "final_work.tab.c"
    break;

  case 41: /* type: CHAR  */
#line 321 "final_work.y"
         {
      TypeInfo *tmp = (TypeInfo*)malloc(sizeof *tmp);
      tmp->kind = KIND_CHAR;
      (yyval.type) = tmp;
  }
#line 2123 "final_work.tab.c"
    break;

  case 42: /* type: BOOLEAN  */
#line 326 "final_work.y"
            {
      TypeInfo *tmp = (TypeInfo*)malloc(sizeof *tmp);
      tmp->kind = KIND_BOOL;
      (yyval.type) = tmp;
  }
#line 2133 "final_work.tab.c"
    break;

  case 43: /* type: ARRAY L_BRACKET constant DOTDOT constant R_BRACKET OF type  */
#line 331 "final_work.y"
                                                               {
      TypeInfo *tmp = (TypeInfo*)malloc(sizeof *tmp);
      tmp->kind = KIND_ARRAY;
      tmp->arrayInfo.type=(yyvsp[0].type);
      tmp->arrayInfo.low=(yyvsp[-5].constant).ival;
      if ((yyvsp[-3].constant).kind == C_STRING) {
        // Symbol* s = get_symbol_by_name($5.id);
        // tmp.arrayInfo.high=s->data.i;
      }
      (yyval.type) = tmp;
  }
#line 2149 "final_work.tab.c"
    break;

  case 44: /* type: RECORD field_list END  */
#line 342 "final_work.y"
                          {
      TypeInfo *tmp = (TypeInfo*)malloc(sizeof *tmp);
      tmp->kind = KIND_RECORD;
      tmp->recordFields = (yyvsp[-1].field_list);
      (yyval.type) = tmp;
  }
#line 2160 "final_work.tab.c"
    break;

  case 45: /* type: IDENTIFIER  */
#line 348 "final_work.y"
               {
      TypeInfo *tmp = (TypeInfo*)malloc(sizeof *tmp);
      tmp->kind = KIND_CUSTOM;
      tmp->custom = (yyvsp[0].string);
  
     Symbol *s = get_symbol_by_name((yyvsp[0].string));
      if (s != NULL && s->skind == SKIND_TYPE) {
        printf("Tipo custom: %s at line %d col %d\n", s->name, yylloc.first_line, yylloc.first_column);
        printf("Tipo do %s: %s\n", s->name, describeType(s->type));
      }
      (yyval.type) = tmp;
    }
#line 2177 "final_work.tab.c"
    break;

  case 46: /* field_list: field_decl SEMICOLON  */
#line 363 "final_work.y"
                         { (yyval.field_list) = (yyvsp[-1].field_list); }
#line 2183 "final_work.tab.c"
    break;

  case 47: /* field_list: field_list field_decl SEMICOLON  */
#line 364 "final_work.y"
                                    { 
      Field* last = (yyvsp[-2].field_list);
      while(last->next) last = last->next;
      last->next = (yyvsp[-1].field_list);
      (yyval.field_list) = (yyvsp[-2].field_list);
    }
#line 2194 "final_work.tab.c"
    break;

  case 48: /* field_decl: IDENTIFIER COLON type  */
#line 373 "final_work.y"
                          {
      Field* f = (Field*)malloc(sizeof(Field));
      f->name = strdup((yyvsp[-2].string));
      f->type = (yyvsp[0].type);
      f->next = NULL;
      (yyval.field_list)=f;
    }
#line 2206 "final_work.tab.c"
    break;

  case 49: /* procedure_declaration: PROCEDURE IDENTIFIER L_PAREN param_list R_PAREN SEMICOLON block  */
#line 383 "final_work.y"
                                                                    {
      struct ProcDecl *pd = (ProcDecl*)malloc(sizeof *pd);
      (yyval.proc_decl) = pd;
    }
#line 2215 "final_work.tab.c"
    break;

  case 50: /* function_declaration: FUNCTION IDENTIFIER L_PAREN param_list R_PAREN COLON type SEMICOLON block  */
#line 390 "final_work.y"
                                                                              {
      struct FuncDecl *fd = (FuncDecl*)malloc(sizeof *fd);
      (yyval.func_decl) = fd;
    }
#line 2224 "final_work.tab.c"
    break;

  case 51: /* param_list: %empty  */
#line 397 "final_work.y"
           { (yyval.param_list) = NULL; }
#line 2230 "final_work.tab.c"
    break;

  case 52: /* param_list: param_seq  */
#line 398 "final_work.y"
              { (yyval.param_list) = (yyvsp[0].param_list); }
#line 2236 "final_work.tab.c"
    break;

  case 53: /* param_seq: IDENTIFIER COLON type  */
#line 402 "final_work.y"
                          { 
      Param* p = (Param*)malloc(sizeof(Param));
      p->name = strdup((yyvsp[-2].string));
      // p->type = lookup_type($3);
      p->next = NULL;
      (yyval.param_list) = p;
    }
#line 2248 "final_work.tab.c"
    break;

  case 54: /* param_seq: param_seq SEMICOLON IDENTIFIER COLON type  */
#line 409 "final_work.y"
                                              { 
      Param* last = (yyvsp[-4].param_list);
      while(last->next) last = last->next;
      Param* p = (Param*)malloc(sizeof(Param));
      p->name = strdup((yyvsp[-2].string));
      // p->type = lookup_type($5);
      p->next = NULL;
      last->next = p;
      (yyval.param_list) = (yyvsp[-4].param_list);
    }
#line 2263 "final_work.tab.c"
    break;

  case 66: /* statement: %empty  */
#line 437 "final_work.y"
           {}
#line 2269 "final_work.tab.c"
    break;

  case 71: /* procedure_stmt: read  */
#line 451 "final_work.y"
         {
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind = EXPR_PROC;
      e->proc = (yyvsp[0].proc_call);
      (yyval.expr) = e;
    }
#line 2280 "final_work.tab.c"
    break;

  case 72: /* procedure_stmt: write  */
#line 457 "final_work.y"
          {
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind = EXPR_PROC;
      e->proc = (yyvsp[0].proc_call);
      (yyval.expr) = e;
    }
#line 2291 "final_work.tab.c"
    break;

  case 73: /* procedure_stmt: IDENTIFIER L_PAREN expression_list R_PAREN  */
#line 463 "final_work.y"
                                               {
      struct ProcCall *proc = (ProcCall*)malloc(sizeof *proc);
      proc->method = (yyvsp[-3].string);
      proc->list = (yyvsp[-1].arg_list);
  
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind = EXPR_PROC;
      e->proc = proc;
      (yyval.expr) = e;
  }
#line 2306 "final_work.tab.c"
    break;

  case 89: /* expression_list: %empty  */
#line 515 "final_work.y"
           {}
#line 2312 "final_work.tab.c"
    break;

  case 90: /* expr: L_PAREN expr R_PAREN  */
#line 519 "final_work.y"
                         {
      (yyval.expr) = (yyvsp[-1].expr);
    }
#line 2320 "final_work.tab.c"
    break;

  case 91: /* expr: expr PLUS expr  */
#line 522 "final_work.y"
                   {
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind   = EXPR_ADD;
      e->left   = (yyvsp[-2].expr);
      e->right  = (yyvsp[0].expr);
      (yyval.expr) = e;
  }
#line 2332 "final_work.tab.c"
    break;

  case 92: /* expr: expr MINUS expr  */
#line 529 "final_work.y"
                    {
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind   = EXPR_SUB;
      e->left   = (yyvsp[-2].expr);
      e->right  = (yyvsp[0].expr);
      (yyval.expr) = e;
  }
#line 2344 "final_work.tab.c"
    break;

  case 93: /* expr: expr TIMES expr  */
#line 536 "final_work.y"
                    {
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind   = EXPR_MUL;
      e->left   = (yyvsp[-2].expr);
      e->right  = (yyvsp[0].expr);
      (yyval.expr) = e;
  }
#line 2356 "final_work.tab.c"
    break;

  case 94: /* expr: expr DIVIDE expr  */
#line 543 "final_work.y"
                     {
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind   = EXPR_DIV;
      e->left   = (yyvsp[-2].expr);
      e->right  = (yyvsp[0].expr);
      (yyval.expr) = e;
  }
#line 2368 "final_work.tab.c"
    break;

  case 95: /* expr: expr DIV expr  */
#line 550 "final_work.y"
                  {
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind   = EXPR_DIVR;
      e->left   = (yyvsp[-2].expr);
      e->right  = (yyvsp[0].expr);
      (yyval.expr) = e;
  }
#line 2380 "final_work.tab.c"
    break;

  case 96: /* expr: expr MOD expr  */
#line 557 "final_work.y"
                 {
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind   = EXPR_MOD;
      e->left   = (yyvsp[-2].expr);
      e->right  = (yyvsp[0].expr);
      (yyval.expr) = e;
  }
#line 2392 "final_work.tab.c"
    break;

  case 97: /* expr: expr NEQ expr  */
#line 564 "final_work.y"
                 {
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind   = EXPR_NEQ;
      e->left   = (yyvsp[-2].expr);
      e->right  = (yyvsp[0].expr);
      (yyval.expr) = e;
  }
#line 2404 "final_work.tab.c"
    break;

  case 98: /* expr: expr EQ expr  */
#line 571 "final_work.y"
                {
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind   = EXPR_EQ;
      e->left   = (yyvsp[-2].expr);
      e->right  = (yyvsp[0].expr);
      (yyval.expr) = e;
  }
#line 2416 "final_work.tab.c"
    break;

  case 99: /* expr: expr LT expr  */
#line 578 "final_work.y"
                {
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind   = EXPR_LT;
      e->left   = (yyvsp[-2].expr);
      e->right  = (yyvsp[0].expr);
      (yyval.expr) = e;
  }
#line 2428 "final_work.tab.c"
    break;

  case 100: /* expr: expr LTE expr  */
#line 585 "final_work.y"
                 {
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind   = EXPR_LTE;
      e->left   = (yyvsp[-2].expr);
      e->right  = (yyvsp[0].expr);
      (yyval.expr) = e;
  }
#line 2440 "final_work.tab.c"
    break;

  case 101: /* expr: expr GT expr  */
#line 592 "final_work.y"
                {
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind   = EXPR_GT;
      e->left   = (yyvsp[-2].expr);
      e->right  = (yyvsp[0].expr);
      (yyval.expr) = e;
  }
#line 2452 "final_work.tab.c"
    break;

  case 102: /* expr: expr GTE expr  */
#line 599 "final_work.y"
                 {
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind   = EXPR_GTE;
      e->left   = (yyvsp[-2].expr);
      e->right  = (yyvsp[0].expr);
      (yyval.expr) = e;
  }
#line 2464 "final_work.tab.c"
    break;

  case 103: /* expr: expr OR expr  */
#line 606 "final_work.y"
                {
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind   = EXPR_OR;
      e->left   = (yyvsp[-2].expr);
      e->right  = (yyvsp[0].expr);
      (yyval.expr) = e;
  }
#line 2476 "final_work.tab.c"
    break;

  case 104: /* expr: expr AND expr  */
#line 613 "final_work.y"
                 {
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind   = EXPR_AND;
      e->left   = (yyvsp[-2].expr);
      e->right  = (yyvsp[0].expr);
      (yyval.expr) = e;
  }
#line 2488 "final_work.tab.c"
    break;

  case 105: /* expr: NOT expr  */
#line 620 "final_work.y"
             {
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind   = EXPR_NOT;
      e->left   = NULL;
      e->right  = (yyvsp[0].expr);
      (yyval.expr) = e;
  }
#line 2500 "final_work.tab.c"
    break;

  case 106: /* expr: MINUS expr  */
#line 627 "final_work.y"
                         {
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind   = EXPR_UMINUS;
      e->left   = NULL;
      e->right  = (yyvsp[0].expr);
      (yyval.expr) = e;
  }
#line 2512 "final_work.tab.c"
    break;

  case 107: /* expr: func_call  */
#line 634 "final_work.y"
              { (yyval.expr) = (yyvsp[0].expr); }
#line 2518 "final_work.tab.c"
    break;

  case 108: /* expr: term  */
#line 635 "final_work.y"
         { (yyval.expr) = (yyvsp[0].expr); }
#line 2524 "final_work.tab.c"
    break;

  case 109: /* term: literals  */
#line 639 "final_work.y"
             { (yyval.expr) = (yyvsp[0].expr); }
#line 2530 "final_work.tab.c"
    break;

  case 110: /* term: IDENTIFIER  */
#line 640 "final_work.y"
               {
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind   = EXPR_ID;
      e->string = (yyvsp[0].string);
      (yyval.expr) = e;
  }
#line 2541 "final_work.tab.c"
    break;

  case 111: /* term: array_access  */
#line 646 "final_work.y"
                 { (yyval.expr) = (yyvsp[0].expr); }
#line 2547 "final_work.tab.c"
    break;

  case 112: /* term: record_access  */
#line 647 "final_work.y"
                  { (yyval.expr) = (yyvsp[0].expr); }
#line 2553 "final_work.tab.c"
    break;

  case 113: /* term: var_access  */
#line 648 "final_work.y"
               {
    struct Expr *e = (Expr*)malloc(sizeof *e);
    e->kind = EXPR_VAR;
    e->var_ref = (yyvsp[0].var_ref);
    (yyval.expr) = e;
  }
#line 2564 "final_work.tab.c"
    break;

  case 114: /* var_access: IDENTIFIER  */
#line 657 "final_work.y"
               {
      struct VarRefExpr *vr = (VarRefExpr*)malloc(sizeof *vr);
      vr->string = (yyvsp[0].string);
      (yyval.var_ref) = vr;
      // TODO: adicionar o ponteiro da symbol_table
    }
#line 2575 "final_work.tab.c"
    break;

  case 115: /* func_call: IDENTIFIER L_PAREN expression_list R_PAREN  */
#line 666 "final_work.y"
                                               {
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind   = EXPR_FUNC;
      e->string = (yyvsp[-3].string);
      e->list = (yyvsp[-1].expr);
      (yyval.expr) = e;
    }
#line 2587 "final_work.tab.c"
    break;

  case 116: /* func_call: SQRT L_PAREN expr R_PAREN  */
#line 673 "final_work.y"
                              {
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind   = EXPR_SQRT;
      e->right  = (yyvsp[-1].expr);
      e->method = "sqrt";
      (yyval.expr) = e;
  }
#line 2599 "final_work.tab.c"
    break;

  case 117: /* array_access: IDENTIFIER L_BRACKET expr R_BRACKET  */
#line 683 "final_work.y"
                                        {
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind   = EXPR_ARRCE;
      e->string = (yyvsp[-3].string);
      e->expr = (yyvsp[-1].expr);
      (yyval.expr) = e;
    }
#line 2611 "final_work.tab.c"
    break;

  case 118: /* array_access: IDENTIFIER L_BRACKET INTEGER_LITERAL R_BRACKET  */
#line 690 "final_work.y"
                                                   {
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind   = EXPR_ARRCL;
      e->string = (yyvsp[-3].string);
      e->integer = (yyvsp[-1].integer);
      (yyval.expr) = e;
  }
#line 2623 "final_work.tab.c"
    break;

  case 119: /* record_access: IDENTIFIER DOT IDENTIFIER  */
#line 700 "final_work.y"
                              {
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind   = EXPR_RCD;
      e->string = (yyvsp[0].string);
      e->record = (yyvsp[-2].string);
      (yyval.expr) = e;
    }
#line 2635 "final_work.tab.c"
    break;

  case 120: /* record_access: array_access DOT IDENTIFIER  */
#line 707 "final_work.y"
                                {
      struct Expr *e = (Expr*)malloc(sizeof *e);
      e->kind   = EXPR_ARCD;
      e->string = (yyvsp[0].string);
      e->expr = (yyvsp[-2].expr);
      (yyval.expr) = e;
  }
#line 2647 "final_work.tab.c"
    break;

  case 121: /* literals: const_numbers  */
#line 717 "final_work.y"
                  {
      (yyval.expr) = (yyvsp[0].expr);
    }
#line 2655 "final_work.tab.c"
    break;

  case 122: /* literals: STRING_LITERAL  */
#line 720 "final_work.y"
                  {
        struct Expr *e = (Expr*)malloc(sizeof *e);
        e->kind   = EXPR_STR;
        e->string = (yyvsp[0].string);
        (yyval.expr) = e;
      }
#line 2666 "final_work.tab.c"
    break;

  case 123: /* literals: BOOLEAN_LITERAL  */
#line 727 "final_work.y"
                   {
        struct Expr *e = (Expr*)malloc(sizeof *e);
        e->kind   = EXPR_BOOL;
        e->boolean = (yyvsp[0].boolean);
        (yyval.expr) = e;
      }
#line 2677 "final_work.tab.c"
    break;

  case 124: /* literals: CHAR_LITERAL  */
#line 734 "final_work.y"
                {
        struct Expr *e = (Expr*)malloc(sizeof *e);
        e->kind   = EXPR_CHAR;
        e->character = (yyvsp[0].character);
        (yyval.expr) = e;
      }
#line 2688 "final_work.tab.c"
    break;

  case 125: /* const_numbers: INTEGER_LITERAL  */
#line 744 "final_work.y"
                      {
        struct Expr *e = (Expr*)malloc(sizeof *e);
        e->kind   = EXPR_INT;
        e->integer = (yyvsp[0].integer);
        (yyval.expr) = e;
      }
#line 2699 "final_work.tab.c"
    break;

  case 126: /* const_numbers: REAL_LITERAL  */
#line 750 "final_work.y"
                   {
        struct Expr *e = (Expr*)malloc(sizeof *e);
        e->kind   = EXPR_REAL;
        e->number = (yyvsp[0].number);
        (yyval.expr) = e;
      }
#line 2710 "final_work.tab.c"
    break;

  case 127: /* write: WRITE L_PAREN write_args R_PAREN  */
#line 759 "final_work.y"
                                     {
      struct ProcCall *proc = (ProcCall*)malloc(sizeof *proc);
      proc->method = "write";
      proc->list = (yyvsp[-1].arg_list);
      (yyval.proc_call) = proc;
    }
#line 2721 "final_work.tab.c"
    break;

  case 128: /* write: WRITELN L_PAREN write_args R_PAREN  */
#line 765 "final_work.y"
                                       {
      struct ProcCall *proc = (ProcCall*)malloc(sizeof *proc);
      proc->method = "writeln";
      proc->list = (yyvsp[-1].arg_list);
      (yyval.proc_call) = proc;
  }
#line 2732 "final_work.tab.c"
    break;

  case 129: /* write: WRITELN  */
#line 771 "final_work.y"
            {
      struct ProcCall *proc = (ProcCall*)malloc(sizeof *proc);
      proc->method = "writeln";
      proc->list = NULL;
      (yyval.proc_call) = proc;
  }
#line 2743 "final_work.tab.c"
    break;

  case 130: /* write_args: write_arg  */
#line 780 "final_work.y"
              { (yyval.arg_list) = (yyvsp[0].arg_list); }
#line 2749 "final_work.tab.c"
    break;

  case 131: /* write_args: write_args COMMA write_arg  */
#line 781 "final_work.y"
                               {
    (yyvsp[-2].arg_list)->next = (yyvsp[0].arg_list);
  }
#line 2757 "final_work.tab.c"
    break;

  case 132: /* write_arg: STRING_LITERAL  */
#line 787 "final_work.y"
                   {
      struct ArgList *ag = (ArgList*)malloc(sizeof *ag);
      ag->next = NULL;
      ag->string = (yyvsp[0].string);
      (yyval.arg_list) = ag;
    }
#line 2768 "final_work.tab.c"
    break;

  case 133: /* write_arg: IDENTIFIER COLON INTEGER_LITERAL COLON INTEGER_LITERAL  */
#line 793 "final_work.y"
                                                             {
        // printf(" [FORMAT: %s:%d:%d] ", $1, $3, $5);
        struct VarRefExpr *vr = (VarRefExpr*)malloc(sizeof *vr);
        vr->string = (yyvsp[-4].string);


        struct ArgList *ag = (ArgList*)malloc(sizeof *ag);
        ag->next = NULL;
        ag->var = vr;
        ag->width = (yyvsp[-2].integer);
        ag->length = (yyvsp[0].integer);
        (yyval.arg_list) = ag;
    }
#line 2786 "final_work.tab.c"
    break;

  case 134: /* write_arg: IDENTIFIER  */
#line 806 "final_work.y"
                 {
        // Symbol* s = get_symbol_by_name($1);
        // if (s->type == TYPE_INT) {
        //   printf(" [INTEGER: %d] ", s->data.i);
        // } else if (s->type == TYPE_REAL) {
        //   printf(" [REAL: %.2f] ", s->data.f);
        // } else if (s->type == TYPE_CHAR) {
        //   printf(" [CHAR: %c] ", s->data.c);
        // } else if (s->type == TYPE_BOOL) {
        //   printf(" [BOOL: %s] ", s->data.b ? "true" : "false");
        // } else {
        //   printf(" [VARIAVEL: %s] ", $1);
        // }

        struct VarRefExpr *vr = (VarRefExpr*)malloc(sizeof *vr);
        vr->string = (yyvsp[0].string);

        struct ArgList *ag = (ArgList*)malloc(sizeof *ag);
        ag->next = NULL;
        ag->var = vr;
        (yyval.arg_list) = ag;
    }
#line 2813 "final_work.tab.c"
    break;

  case 135: /* write_arg: record_access  */
#line 828 "final_work.y"
                    {
        struct ArgList *ag = (ArgList*)malloc(sizeof *ag);
        ag->next = NULL;
        ag->expr = (yyvsp[0].expr);
        (yyval.arg_list) = ag;
    }
#line 2824 "final_work.tab.c"
    break;

  case 136: /* read: READ L_PAREN IDENTIFIER R_PAREN  */
#line 837 "final_work.y"
                                    {
      struct ProcCall *proc = (ProcCall*)malloc(sizeof *proc);
      proc->method = "read";
      proc->var = (yyvsp[-1].var_ref);
      (yyval.proc_call) = proc;
    }
#line 2835 "final_work.tab.c"
    break;

  case 137: /* read: READLN L_PAREN IDENTIFIER R_PAREN  */
#line 843 "final_work.y"
                                      {
      struct ProcCall *proc = (ProcCall*)malloc(sizeof *proc);
      proc->method = "readln";
      proc->var = (yyvsp[-1].var_ref);
      (yyval.proc_call) = proc;

      // TODO: adicionar ref a var $3 da symbol_table
  }
#line 2848 "final_work.tab.c"
    break;


#line 2852 "final_work.tab.c"

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

#line 853 "final_work.y"

