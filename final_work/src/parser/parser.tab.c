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
#line 3 "parser/parser.y"

#include <stdlib.h>
#include <string.h>
#include "../ast/ast.h"
#include "types.h"

ASTNode *root = NULL;

#line 80 "parser/parser.tab.c"

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

#include "parser.tab.h"
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
  YYSYMBOL_NIL = 15,                       /* NIL  */
  YYSYMBOL_WITH = 16,                      /* WITH  */
  YYSYMBOL_FORWARD = 17,                   /* FORWARD  */
  YYSYMBOL_PACKED = 18,                    /* PACKED  */
  YYSYMBOL_WHILE = 19,                     /* WHILE  */
  YYSYMBOL_DO = 20,                        /* DO  */
  YYSYMBOL_FOR = 21,                       /* FOR  */
  YYSYMBOL_TO = 22,                        /* TO  */
  YYSYMBOL_DOWNTO = 23,                    /* DOWNTO  */
  YYSYMBOL_REPEAT = 24,                    /* REPEAT  */
  YYSYMBOL_UNTIL = 25,                     /* UNTIL  */
  YYSYMBOL_CASE = 26,                      /* CASE  */
  YYSYMBOL_OF = 27,                        /* OF  */
  YYSYMBOL_GOTO = 28,                      /* GOTO  */
  YYSYMBOL_INTEGER = 29,                   /* INTEGER  */
  YYSYMBOL_REAL = 30,                      /* REAL  */
  YYSYMBOL_BOOLEAN = 31,                   /* BOOLEAN  */
  YYSYMBOL_CHAR = 32,                      /* CHAR  */
  YYSYMBOL_ARRAY = 33,                     /* ARRAY  */
  YYSYMBOL_RECORD = 34,                    /* RECORD  */
  YYSYMBOL_SET = 35,                       /* SET  */
  YYSYMBOL_FILE_TOK = 36,                  /* FILE_TOK  */
  YYSYMBOL_STRING = 37,                    /* STRING  */
  YYSYMBOL_READ = 38,                      /* READ  */
  YYSYMBOL_WRITE = 39,                     /* WRITE  */
  YYSYMBOL_READLN = 40,                    /* READLN  */
  YYSYMBOL_WRITELN = 41,                   /* WRITELN  */
  YYSYMBOL_GT = 42,                        /* GT  */
  YYSYMBOL_GTE = 43,                       /* GTE  */
  YYSYMBOL_LT = 44,                        /* LT  */
  YYSYMBOL_LTE = 45,                       /* LTE  */
  YYSYMBOL_NEQ = 46,                       /* NEQ  */
  YYSYMBOL_EQ = 47,                        /* EQ  */
  YYSYMBOL_AND = 48,                       /* AND  */
  YYSYMBOL_OR = 49,                        /* OR  */
  YYSYMBOL_NOT = 50,                       /* NOT  */
  YYSYMBOL_PLUS = 51,                      /* PLUS  */
  YYSYMBOL_MINUS = 52,                     /* MINUS  */
  YYSYMBOL_TIMES = 53,                     /* TIMES  */
  YYSYMBOL_DIVIDE = 54,                    /* DIVIDE  */
  YYSYMBOL_DIV = 55,                       /* DIV  */
  YYSYMBOL_MOD = 56,                       /* MOD  */
  YYSYMBOL_DOT = 57,                       /* DOT  */
  YYSYMBOL_DOTDOT = 58,                    /* DOTDOT  */
  YYSYMBOL_DOTDOTDOT = 59,                 /* DOTDOTDOT  */
  YYSYMBOL_CARET = 60,                     /* CARET  */
  YYSYMBOL_ASSIGN = 61,                    /* ASSIGN  */
  YYSYMBOL_SEMICOLON = 62,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 63,                     /* COMMA  */
  YYSYMBOL_COLON = 64,                     /* COLON  */
  YYSYMBOL_L_PAREN = 65,                   /* L_PAREN  */
  YYSYMBOL_R_PAREN = 66,                   /* R_PAREN  */
  YYSYMBOL_L_BRACE = 67,                   /* L_BRACE  */
  YYSYMBOL_R_BRACE = 68,                   /* R_BRACE  */
  YYSYMBOL_L_BRACKET = 69,                 /* L_BRACKET  */
  YYSYMBOL_R_BRACKET = 70,                 /* R_BRACKET  */
  YYSYMBOL_CHAR_LITERAL = 71,              /* CHAR_LITERAL  */
  YYSYMBOL_INTEGER_LITERAL = 72,           /* INTEGER_LITERAL  */
  YYSYMBOL_REAL_LITERAL = 73,              /* REAL_LITERAL  */
  YYSYMBOL_BOOLEAN_LITERAL = 74,           /* BOOLEAN_LITERAL  */
  YYSYMBOL_IDENTIFIER = 75,                /* IDENTIFIER  */
  YYSYMBOL_STRING_LITERAL = 76,            /* STRING_LITERAL  */
  YYSYMBOL_SQRT = 77,                      /* SQRT  */
  YYSYMBOL_NEG = 78,                       /* NEG  */
  YYSYMBOL_IN = 79,                        /* IN  */
  YYSYMBOL_LOWER_THAN_ELSE = 80,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 81,                  /* $accept  */
  YYSYMBOL_pascal_program = 82,            /* pascal_program  */
  YYSYMBOL_program_headingopt = 83,        /* program_headingopt  */
  YYSYMBOL_identifier_list = 84,           /* identifier_list  */
  YYSYMBOL_block = 85,                     /* block  */
  YYSYMBOL_block1 = 86,                    /* block1  */
  YYSYMBOL_block2 = 87,                    /* block2  */
  YYSYMBOL_block3 = 88,                    /* block3  */
  YYSYMBOL_block4 = 89,                    /* block4  */
  YYSYMBOL_block5 = 90,                    /* block5  */
  YYSYMBOL_label_declaration = 91,         /* label_declaration  */
  YYSYMBOL_constant_declaration = 92,      /* constant_declaration  */
  YYSYMBOL_type_declaration = 93,          /* type_declaration  */
  YYSYMBOL_variable_declaration = 94,      /* variable_declaration  */
  YYSYMBOL_variableid_list = 95,           /* variableid_list  */
  YYSYMBOL_constant = 96,                  /* constant  */
  YYSYMBOL_type = 97,                      /* type  */
  YYSYMBOL_simple_type = 98,               /* simple_type  */
  YYSYMBOL_structured_type = 99,           /* structured_type  */
  YYSYMBOL_index_list = 100,               /* index_list  */
  YYSYMBOL_field_list = 101,               /* field_list  */
  YYSYMBOL_fixed_part = 102,               /* fixed_part  */
  YYSYMBOL_record_field = 103,             /* record_field  */
  YYSYMBOL_fieldid_list = 104,             /* fieldid_list  */
  YYSYMBOL_variant_part = 105,             /* variant_part  */
  YYSYMBOL_tag_field = 106,                /* tag_field  */
  YYSYMBOL_variant_list = 107,             /* variant_list  */
  YYSYMBOL_variant = 108,                  /* variant  */
  YYSYMBOL_case_label_list = 109,          /* case_label_list  */
  YYSYMBOL_proc_and_func_declaration = 110, /* proc_and_func_declaration  */
  YYSYMBOL_proc_or_func = 111,             /* proc_or_func  */
  YYSYMBOL_block_or_forward = 112,         /* block_or_forward  */
  YYSYMBOL_parameters = 113,               /* parameters  */
  YYSYMBOL_formal_parameter_list = 114,    /* formal_parameter_list  */
  YYSYMBOL_formal_parameter_section = 115, /* formal_parameter_section  */
  YYSYMBOL_parameterid_list = 116,         /* parameterid_list  */
  YYSYMBOL_statement_list = 117,           /* statement_list  */
  YYSYMBOL_statement = 118,                /* statement  */
  YYSYMBOL_variable = 119,                 /* variable  */
  YYSYMBOL_subscript_list = 120,           /* subscript_list  */
  YYSYMBOL_case_list = 121,                /* case_list  */
  YYSYMBOL_case_element = 122,             /* case_element  */
  YYSYMBOL_case_else = 123,                /* case_else  */
  YYSYMBOL_for_list = 124,                 /* for_list  */
  YYSYMBOL_expression_list = 125,          /* expression_list  */
  YYSYMBOL_label = 126,                    /* label  */
  YYSYMBOL_record_variable_list = 127,     /* record_variable_list  */
  YYSYMBOL_expression = 128,               /* expression  */
  YYSYMBOL_relational_op = 129,            /* relational_op  */
  YYSYMBOL_additive_expression = 130,      /* additive_expression  */
  YYSYMBOL_additive_op = 131,              /* additive_op  */
  YYSYMBOL_multiplicative_expression = 132, /* multiplicative_expression  */
  YYSYMBOL_multiplicative_op = 133,        /* multiplicative_op  */
  YYSYMBOL_unary_expression = 134,         /* unary_expression  */
  YYSYMBOL_unary_op = 135,                 /* unary_op  */
  YYSYMBOL_primary_expression = 136,       /* primary_expression  */
  YYSYMBOL_element_list = 137,             /* element_list  */
  YYSYMBOL_element = 138,                  /* element  */
  YYSYMBOL_constid = 139,                  /* constid  */
  YYSYMBOL_typeid = 140,                   /* typeid  */
  YYSYMBOL_funcid = 141,                   /* funcid  */
  YYSYMBOL_procid = 142,                   /* procid  */
  YYSYMBOL_fieldid = 143,                  /* fieldid  */
  YYSYMBOL_varid = 144,                    /* varid  */
  YYSYMBOL_identifier = 145,               /* identifier  */
  YYSYMBOL_unsigned_integer = 146,         /* unsigned_integer  */
  YYSYMBOL_unsigned_real = 147,            /* unsigned_real  */
  YYSYMBOL_integer_literal = 148,          /* integer_literal  */
  YYSYMBOL_real_literal = 149,             /* real_literal  */
  YYSYMBOL_string_literal = 150,           /* string_literal  */
  YYSYMBOL_empty = 151                     /* empty  */
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
#define YYLAST   481

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  81
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  71
/* YYNRULES -- Number of rules.  */
#define YYNRULES  174
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  334

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   335


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
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   138,   138,   144,   147,   150,   153,   158,   159,   164,
     165,   170,   171,   176,   177,   182,   183,   188,   193,   194,
     199,   202,   207,   208,   213,   214,   219,   220,   225,   228,
     231,   234,   235,   236,   239,   242,   245,   250,   251,   254,
     259,   262,   265,   268,   271,   276,   277,   282,   283,   284,
     287,   288,   291,   292,   295,   296,   299,   302,   303,   306,
     307,   312,   313,   318,   319,   322,   323,   328,   331,   336,
     337,   340,   343,   344,   349,   350,   351,   352,   355,   356,
     359,   360,   363,   364,   365,   366,   367,   368,   369,   370,
     371,   372,   373,   374,   375,   376,   377,   380,   381,   382,
     383,   386,   389,   394,   397,   402,   407,   412,   413,   417,
     418,   421,   424,   425,   428,   429,   432,   433,   434,   435,
     436,   437,   440,   441,   444,   445,   446,   449,   450,   453,
     454,   455,   456,   457,   458,   461,   462,   465,   466,   467,
     470,   471,   472,   473,   474,   477,   478,   479,   482,   483,
     484,   487,   488,   491,   494,   495,   496,   497,   498,   499,
     502,   505,   506,   507,   508,   509,   512,   515,   518,   521,
     526,   531,   536,   541,   555
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
  "IF", "THEN", "ELSE", "NIL", "WITH", "FORWARD", "PACKED", "WHILE", "DO",
  "FOR", "TO", "DOWNTO", "REPEAT", "UNTIL", "CASE", "OF", "GOTO",
  "INTEGER", "REAL", "BOOLEAN", "CHAR", "ARRAY", "RECORD", "SET",
  "FILE_TOK", "STRING", "READ", "WRITE", "READLN", "WRITELN", "GT", "GTE",
  "LT", "LTE", "NEQ", "EQ", "AND", "OR", "NOT", "PLUS", "MINUS", "TIMES",
  "DIVIDE", "DIV", "MOD", "DOT", "DOTDOT", "DOTDOTDOT", "CARET", "ASSIGN",
  "SEMICOLON", "COMMA", "COLON", "L_PAREN", "R_PAREN", "L_BRACE",
  "R_BRACE", "L_BRACKET", "R_BRACKET", "CHAR_LITERAL", "INTEGER_LITERAL",
  "REAL_LITERAL", "BOOLEAN_LITERAL", "IDENTIFIER", "STRING_LITERAL",
  "SQRT", "NEG", "IN", "LOWER_THAN_ELSE", "$accept", "pascal_program",
  "program_headingopt", "identifier_list", "block", "block1", "block2",
  "block3", "block4", "block5", "label_declaration",
  "constant_declaration", "type_declaration", "variable_declaration",
  "variableid_list", "constant", "type", "simple_type", "structured_type",
  "index_list", "field_list", "fixed_part", "record_field", "fieldid_list",
  "variant_part", "tag_field", "variant_list", "variant",
  "case_label_list", "proc_and_func_declaration", "proc_or_func",
  "block_or_forward", "parameters", "formal_parameter_list",
  "formal_parameter_section", "parameterid_list", "statement_list",
  "statement", "variable", "subscript_list", "case_list", "case_element",
  "case_else", "for_list", "expression_list", "label",
  "record_variable_list", "expression", "relational_op",
  "additive_expression", "additive_op", "multiplicative_expression",
  "multiplicative_op", "unary_expression", "unary_op",
  "primary_expression", "element_list", "element", "constid", "typeid",
  "funcid", "procid", "fieldid", "varid", "identifier", "unsigned_integer",
  "unsigned_real", "integer_literal", "real_literal", "string_literal",
  "empty", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-280)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-161)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       4,   -15,    43,   -42,  -280,     0,    40,  -280,  -280,    27,
    -280,   464,     0,  -280,     0,     0,     0,    24,     0,     0,
     323,    74,  -280,  -280,  -280,  -280,  -280,    93,    50,    75,
      80,    82,  -280,  -280,   113,  -280,   101,   112,  -280,  -280,
      64,    64,   323,   186,     0,   186,     0,   323,   186,    24,
    -280,  -280,  -280,  -280,    -9,  -280,    46,   104,   105,   171,
    -280,  -280,  -280,   471,    24,    16,    23,    72,   116,     0,
     337,   356,   337,    47,   111,   115,    -5,  -280,  -280,  -280,
    -280,   186,   186,  -280,  -280,   -21,   264,    67,   239,  -280,
     186,  -280,   117,   132,  -280,  -280,   -21,    26,  -280,   372,
     123,  -280,   -24,   406,  -280,  -280,   323,     0,  -280,   186,
     186,   323,   186,  -280,  -280,  -280,   147,  -280,   153,  -280,
     128,  -280,  -280,  -280,   268,  -280,  -280,  -280,  -280,   133,
       3,   184,   188,  -280,     0,     0,    55,     0,  -280,  -280,
    -280,   148,  -280,  -280,  -280,  -280,  -280,   151,  -280,  -280,
    -280,  -280,  -280,  -280,     0,     0,     0,    -4,  -280,   150,
    -280,   450,    55,  -280,   119,   340,   -29,  -280,  -280,   323,
    -280,  -280,  -280,  -280,  -280,  -280,   186,  -280,  -280,  -280,
     186,  -280,  -280,  -280,  -280,  -280,  -280,   186,  -280,   186,
     323,     0,   323,   186,   186,   356,  -280,  -280,  -280,   392,
      13,   392,  -280,    34,   392,   356,   337,   337,  -280,   328,
      55,   215,   187,  -280,   161,  -280,  -280,  -280,   328,   337,
    -280,  -280,  -280,  -280,    48,   356,   179,    64,    64,    47,
    -280,     0,    55,  -280,  -280,  -280,   194,  -280,   186,   186,
    -280,   246,    67,   239,  -280,    57,  -280,   -21,  -280,   245,
     398,   392,  -280,   182,    99,  -280,   186,  -280,   186,  -280,
    -280,  -280,  -280,  -280,    25,   243,  -280,   207,  -280,     3,
       0,   337,  -280,  -280,  -280,  -280,    55,  -280,   212,  -280,
    -280,  -280,   450,   392,  -280,   323,  -280,   323,   186,   186,
     356,   323,  -280,   323,  -280,   267,   392,   392,   328,   253,
     356,    55,  -280,  -280,  -280,  -280,  -280,    55,  -280,  -280,
    -280,   392,   392,  -280,   220,   222,  -280,  -280,   337,   228,
    -280,   190,  -280,  -280,  -280,  -280,  -280,  -280,   356,   235,
    -280,     3,   247,  -280
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,   174,     1,     0,     0,     4,   168,     0,
       5,     0,     0,     3,     0,     0,     0,     0,     0,     0,
     174,     0,     7,     9,    11,    13,    15,     0,     0,     0,
       0,     0,    65,     6,     0,    26,     0,     0,   169,    18,
       0,     0,   174,     0,     0,     0,     0,   174,     0,     0,
     164,   162,   165,   163,     0,    80,     0,     0,    92,   161,
     111,    82,     2,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   144,   139,   137,
     138,     0,   174,   170,   143,   140,     0,   115,   123,   128,
       0,   136,     0,    97,   141,   142,   112,     0,    97,     0,
       0,   167,     0,     0,    94,    17,   174,     0,   100,     0,
       0,   174,     0,     8,    19,    10,     0,    12,     0,    14,
       0,    16,    66,    27,     0,   156,   157,   155,   154,     0,
     174,     0,     0,   158,     0,     0,     0,     0,   171,   172,
     173,     0,    24,    34,    35,    31,    39,   159,    28,    29,
      30,    20,   153,    22,     0,     0,     0,     0,    72,     0,
      78,     0,     0,    84,     0,   151,     0,   149,   148,   174,
     121,   120,   116,   117,   119,   118,     0,   126,   124,   125,
       0,   133,   129,   130,   131,   132,   134,     0,   135,     0,
     174,     0,   174,     0,     0,     0,    81,    99,   166,    83,
       0,   101,    96,     0,   109,     0,     0,     0,    44,     0,
       0,     0,    47,    50,     0,    49,    54,    52,     0,     0,
      32,    33,    36,   159,     0,     0,     0,     0,     0,     0,
      71,     0,     0,    70,    69,    67,     0,   147,     0,     0,
     146,    85,   114,   122,   127,     0,    95,   113,    89,     0,
       0,    90,    63,     0,     0,   103,     0,    98,     0,    93,
      21,    23,    25,    45,     0,     0,    57,   159,    41,   174,
       0,     0,    42,    43,    37,    38,     0,    76,     0,    73,
      79,    74,     0,   152,   150,   174,   145,   174,     0,     0,
       0,   174,    87,   174,   104,     0,   102,   110,     0,     0,
     174,     0,    51,    48,    55,    53,    75,     0,    68,    86,
      91,   107,   108,    64,     0,     0,    88,    46,     0,    56,
      59,     0,    61,    58,    77,   105,   106,    40,   174,     0,
      60,   174,     0,    62
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -280,  -280,  -280,   175,   303,   256,   255,   258,   263,   254,
    -280,  -280,  -280,  -280,   269,   -56,   -61,  -190,   210,  -280,
       6,  -280,    69,  -280,    71,  -280,  -280,    15,  -279,  -280,
     273,    63,   -32,  -280,   121,   192,    19,   -52,    30,  -280,
    -280,    94,  -280,  -280,   163,   304,  -280,   138,  -280,   178,
    -280,   176,  -280,   -86,  -280,  -280,  -280,   136,   129,   -89,
    -280,  -280,  -280,  -280,    -2,   -12,  -280,  -280,  -280,  -280,
      -3
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     2,     6,     9,   234,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    34,   141,   142,   143,   144,   264,
     211,   212,   213,   214,   215,   265,   319,   320,   253,    31,
      32,   235,    74,   157,   158,   159,    54,    55,    85,   200,
     254,   255,   295,   249,   203,    57,    97,   165,   176,    87,
     180,    88,   187,    89,    90,    91,   166,   167,   145,   146,
      92,    58,   197,   100,    93,    94,    95,   148,   149,   150,
      61
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
       7,   194,   105,    10,   188,    39,   163,     1,    60,    75,
      33,   153,    35,    36,    37,   151,    40,    41,    59,   263,
      14,   321,    16,     5,    18,    19,    20,    14,   272,   210,
      60,    18,    19,    20,   239,    60,   107,    60,   106,   108,
      59,   240,    98,     4,   101,    59,   190,   222,   110,   321,
      56,   154,   114,   106,   196,   155,   156,   106,   229,   202,
       3,    76,   230,   116,   118,    35,   102,   123,   147,   152,
     147,   160,    56,   236,    96,     8,   256,    56,     8,   168,
      18,    19,    20,   257,   125,   126,   127,   128,   298,   191,
      12,     8,   133,    13,    60,   299,    38,   258,     8,    60,
     259,   244,    11,   107,    59,   198,   108,   109,   317,    59,
     292,    12,    65,   293,   274,   110,   177,   241,   178,   179,
     258,   266,     8,   286,    18,    19,    20,   217,   216,    73,
       8,    62,   152,   152,   223,    10,    56,    66,   246,   252,
     248,    56,    67,   281,    68,   261,   262,     8,    71,   260,
     134,   135,   160,   227,   228,    63,    64,    60,   273,    72,
     223,   170,   171,   172,   173,   174,   175,    59,   111,   275,
     112,   138,   139,   161,     8,   140,    69,    70,    60,   162,
      60,    86,   189,    99,   193,   237,   103,   306,    59,    98,
      59,    69,   207,   152,   205,   277,   278,  -160,   252,    56,
     206,    77,   209,   152,   147,   147,   225,   147,   267,  -153,
     305,   218,   323,   231,   232,   219,   147,   147,   324,   164,
      56,   247,    56,   152,   270,   271,   268,   160,   -97,   280,
     223,   -97,   -97,   309,   313,   310,    78,    79,    80,   314,
     -97,   315,   231,   276,   252,   290,   291,   199,   201,   269,
     204,    81,   152,   290,   329,    82,   282,   327,    38,    83,
     285,     8,    84,   220,   221,   287,   217,   216,   304,   147,
     300,   301,   252,    60,   223,    60,   307,   169,   316,    60,
     318,    60,   325,    59,   326,    59,   124,   181,   152,    59,
     328,    59,   182,   183,   184,   185,   147,   322,   152,   223,
     331,   129,   130,   131,   132,   223,   170,   171,   172,   173,
     174,   175,   224,   333,    21,    56,   147,    56,   186,   113,
     115,    56,   121,    56,   117,   322,   152,   204,   217,   216,
     119,   250,   251,    42,   208,    43,   120,   332,   302,    44,
     303,   122,    45,   330,    46,   308,   226,    47,   294,    48,
     279,    49,   245,   104,   242,   124,   243,   125,   126,   127,
     128,    50,    51,    52,    53,   133,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   284,   283,     0,     0,   134,
     135,     0,   170,   171,   172,   173,   174,   175,   134,   135,
       0,     0,   192,   137,   296,    38,   297,   136,     8,   238,
     138,   139,   137,     8,   140,     0,     0,   134,   135,   138,
     139,     0,     8,   140,   170,   171,   172,   173,   174,   175,
     288,   289,     0,     0,     0,     0,   311,   312,   138,   139,
       0,     8,   140,   195,   170,   171,   172,   173,   174,   175,
     170,   171,   172,   173,   174,   175,     0,     0,   170,   171,
     172,   173,   174,   175,    14,    15,    16,    17,    18,    19,
      20,     0,     0,     0,     0,     0,     0,   233,    14,    15,
      16,    17,    18,    19,    20,    14,    15,    16,     0,    18,
      19,    20
};

static const yytype_int16 yycheck[] =
{
       3,    25,    11,     5,    90,    17,    11,     3,    20,    41,
      12,    72,    14,    15,    16,    71,    18,    19,    20,   209,
       4,   300,     6,    65,     8,     9,    10,     4,   218,    26,
      42,     8,     9,    10,    63,    47,    57,    49,    62,    60,
      42,    70,    44,     0,    46,    47,    20,   136,    69,   328,
      20,     4,    64,    62,   106,     8,     9,    62,    62,   111,
      75,    42,    66,    65,    66,    67,    47,    69,    70,    71,
      72,    73,    42,   162,    44,    75,    63,    47,    75,    82,
       8,     9,    10,    70,    29,    30,    31,    32,    63,    63,
      63,    75,    37,    66,   106,    70,    72,    63,    75,   111,
      66,   187,    62,    57,   106,   107,    60,    61,   298,   111,
      11,    63,    62,    14,    66,    69,    49,   169,    51,    52,
      63,   210,    75,    66,     8,     9,    10,   130,   130,    65,
      75,    57,   134,   135,   136,   137,   106,    62,   190,   195,
     192,   111,    62,   232,    62,   206,   207,    75,    47,   205,
      51,    52,   154,   155,   156,    62,    63,   169,   219,    47,
     162,    42,    43,    44,    45,    46,    47,   169,    64,   225,
      65,    72,    73,    62,    75,    76,    63,    64,   190,    64,
     192,    43,    65,    45,    61,    66,    48,   276,   190,   191,
     192,    63,    64,   195,    47,   227,   228,    65,   254,   169,
      47,    15,    69,   205,   206,   207,    58,   209,   210,    58,
     271,    27,   301,    63,    64,    27,   218,   219,   307,    81,
     190,   191,   192,   225,    63,    64,    11,   229,    57,   231,
     232,    60,    61,   285,   290,   287,    50,    51,    52,   291,
      69,   293,    63,    64,   300,    63,    64,   109,   110,    62,
     112,    65,   254,    63,    64,    69,    62,   318,    72,    73,
      14,    75,    76,   134,   135,    20,   269,   269,   270,   271,
      27,    64,   328,   285,   276,   287,    64,    13,    11,   291,
      27,   293,    62,   285,    62,   287,    18,    48,   290,   291,
      62,   293,    53,    54,    55,    56,   298,   300,   300,   301,
      65,    33,    34,    35,    36,   307,    42,    43,    44,    45,
      46,    47,   137,    66,    11,   285,   318,   287,    79,    63,
      65,   291,    68,   293,    66,   328,   328,   189,   331,   331,
      67,   193,   194,    10,   124,    12,    67,   331,   269,    16,
     269,    68,    19,   328,    21,   282,   154,    24,   254,    26,
     229,    28,   189,    49,   176,    18,   180,    29,    30,    31,
      32,    38,    39,    40,    41,    37,    29,    30,    31,    32,
      33,    34,    35,    36,    37,   239,   238,    -1,    -1,    51,
      52,    -1,    42,    43,    44,    45,    46,    47,    51,    52,
      -1,    -1,    20,    65,   256,    72,   258,    60,    75,    59,
      72,    73,    65,    75,    76,    -1,    -1,    51,    52,    72,
      73,    -1,    75,    76,    42,    43,    44,    45,    46,    47,
      22,    23,    -1,    -1,    -1,    -1,   288,   289,    72,    73,
      -1,    75,    76,    27,    42,    43,    44,    45,    46,    47,
      42,    43,    44,    45,    46,    47,    -1,    -1,    42,    43,
      44,    45,    46,    47,     4,     5,     6,     7,     8,     9,
      10,    -1,    -1,    -1,    -1,    -1,    -1,    17,     4,     5,
       6,     7,     8,     9,    10,     4,     5,     6,    -1,     8,
       9,    10
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    82,    75,     0,    65,    83,   151,    75,    84,
     145,    62,    63,    66,     4,     5,     6,     7,     8,     9,
      10,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,   110,   111,   145,    95,   145,   145,   145,    72,   146,
     145,   145,    10,    12,    16,    19,    21,    24,    26,    28,
      38,    39,    40,    41,   117,   118,   119,   126,   142,   145,
     146,   151,    57,    62,    63,    62,    62,    62,    62,    63,
      64,    47,    47,    65,   113,   113,   117,    15,    50,    51,
      52,    65,    69,    73,    76,   119,   128,   130,   132,   134,
     135,   136,   141,   145,   146,   147,   119,   127,   145,   128,
     144,   145,   117,   128,   126,    11,    62,    57,    60,    61,
      69,    64,    65,    86,   146,    87,   145,    88,   145,    89,
      95,    90,   111,   145,    18,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    51,    52,    60,    65,    72,    73,
      76,    96,    97,    98,    99,   139,   140,   145,   148,   149,
     150,    96,   145,    97,     4,     8,     9,   114,   115,   116,
     145,    62,    64,    11,   128,   128,   137,   138,   151,    13,
      42,    43,    44,    45,    46,    47,   129,    49,    51,    52,
     131,    48,    53,    54,    55,    56,    79,   133,   134,    65,
      20,    63,    20,    61,    25,    27,   118,   143,   145,   128,
     120,   128,   118,   125,   128,    47,    47,    64,    99,    69,
      26,   101,   102,   103,   104,   105,   145,   151,    27,    27,
     139,   139,   140,   145,    84,    58,   116,   145,   145,    62,
      66,    63,    64,    17,    85,   112,   140,    66,    59,    63,
      70,   118,   130,   132,   134,   125,   118,   119,   118,   124,
     128,   128,    96,   109,   121,   122,    63,    70,    63,    66,
      96,    97,    97,    98,   100,   106,   140,   145,    11,    62,
      63,    64,    98,    97,    66,    96,    64,   113,   113,   115,
     145,   140,    62,   128,   138,    14,    66,    20,    22,    23,
      63,    64,    11,    14,   122,   123,   128,   128,    63,    70,
      27,    64,   103,   105,   145,    97,   140,    64,   112,   118,
     118,   128,   128,    96,   118,   118,    11,    98,    27,   107,
     108,   109,   151,   140,   140,    62,    62,    97,    62,    64,
     108,    65,   101,    66
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    81,    82,    83,    83,    84,    84,    85,    85,    86,
      86,    87,    87,    88,    88,    89,    89,    90,    91,    91,
      92,    92,    93,    93,    94,    94,    95,    95,    96,    96,
      96,    96,    96,    96,    97,    97,    97,    98,    98,    98,
      99,    99,    99,    99,    99,   100,   100,   101,   101,   101,
     102,   102,   103,   103,   104,   104,   105,   106,   106,   107,
     107,   108,   108,   109,   109,   110,   110,   111,   111,   112,
     112,   113,   114,   114,   115,   115,   115,   115,   116,   116,
     117,   117,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   119,   119,   119,
     119,   120,   120,   121,   121,   122,   123,   124,   124,   125,
     125,   126,   127,   127,   128,   128,   129,   129,   129,   129,
     129,   129,   130,   130,   131,   131,   131,   132,   132,   133,
     133,   133,   133,   133,   133,   134,   134,   135,   135,   135,
     136,   136,   136,   136,   136,   136,   136,   136,   137,   137,
     137,   138,   138,   139,   140,   140,   140,   140,   140,   140,
     141,   142,   142,   142,   142,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     6,     3,     1,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     3,     2,     3,
       4,     5,     4,     5,     4,     5,     1,     3,     1,     1,
       1,     1,     2,     2,     1,     1,     2,     3,     3,     1,
       6,     3,     3,     3,     2,     1,     3,     1,     3,     1,
       1,     3,     1,     3,     1,     3,     4,     1,     3,     1,
       3,     1,     5,     1,     3,     1,     3,     5,     7,     1,
       1,     3,     1,     3,     3,     4,     3,     5,     1,     3,
       1,     3,     1,     3,     3,     4,     6,     5,     6,     4,
       4,     6,     1,     4,     2,     4,     3,     1,     4,     3,
       2,     1,     3,     1,     2,     4,     3,     3,     3,     1,
       3,     1,     1,     3,     3,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     1,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     3,     3,     1,     1,
       3,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0
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
  case 2: /* pascal_program: PROGRAM IDENTIFIER program_headingopt SEMICOLON block DOT  */
#line 138 "parser/parser.y"
                                                             {
      (yyval.node) = create_program_node((yyvsp[-4].string), (yyvsp[-3].node), (yyvsp[-1].node), create_location((yyloc)));
      root = (yyval.node);
   }
#line 1896 "parser/parser.tab.c"
    break;

  case 3: /* program_headingopt: L_PAREN identifier_list R_PAREN  */
#line 144 "parser/parser.y"
                                    {
      (yyval.node) = create_heading_node((yyvsp[-1].node), create_location((yyloc)));
    }
#line 1904 "parser/parser.tab.c"
    break;

  case 5: /* identifier_list: identifier  */
#line 150 "parser/parser.y"
               {
      (yyval.node) = create_identifier_list_node((yyvsp[0].node), create_location((yyloc)));
    }
#line 1912 "parser/parser.tab.c"
    break;

  case 6: /* identifier_list: identifier_list COMMA identifier  */
#line 153 "parser/parser.y"
                                     {
      (yyval.node) = append_identifier_list_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 1920 "parser/parser.tab.c"
    break;

  case 7: /* block: block1  */
#line 158 "parser/parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 1926 "parser/parser.tab.c"
    break;

  case 8: /* block: label_declaration SEMICOLON block1  */
#line 159 "parser/parser.y"
                                       {
      (yyval.node) = add_labels_to_block((yyvsp[0].node), (yyvsp[-2].node));
    }
#line 1934 "parser/parser.tab.c"
    break;

  case 9: /* block1: block2  */
#line 164 "parser/parser.y"
            { (yyval.node) = (yyvsp[0].node); }
#line 1940 "parser/parser.tab.c"
    break;

  case 10: /* block1: constant_declaration SEMICOLON block2  */
#line 165 "parser/parser.y"
                                          {
    (yyval.node) = add_constants_to_block((yyvsp[0].node), (yyvsp[-2].node));
  }
#line 1948 "parser/parser.tab.c"
    break;

  case 11: /* block2: block3  */
#line 170 "parser/parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 1954 "parser/parser.tab.c"
    break;

  case 12: /* block2: type_declaration SEMICOLON block3  */
#line 171 "parser/parser.y"
                                      {
     (yyval.node) = add_types_to_block((yyvsp[0].node), (yyvsp[-2].node));
  }
#line 1962 "parser/parser.tab.c"
    break;

  case 13: /* block3: block4  */
#line 176 "parser/parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 1968 "parser/parser.tab.c"
    break;

  case 14: /* block3: variable_declaration SEMICOLON block4  */
#line 177 "parser/parser.y"
                                          {
      (yyval.node) = add_variables_to_block((yyvsp[0].node), (yyvsp[-2].node));
    }
#line 1976 "parser/parser.tab.c"
    break;

  case 15: /* block4: block5  */
#line 182 "parser/parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 1982 "parser/parser.tab.c"
    break;

  case 16: /* block4: proc_and_func_declaration SEMICOLON block5  */
#line 183 "parser/parser.y"
                                               {
      (yyval.node) = add_procs_funcs_to_block((yyvsp[0].node), (yyvsp[-2].node));
    }
#line 1990 "parser/parser.tab.c"
    break;

  case 17: /* block5: BEGIN_TOK statement_list END  */
#line 188 "parser/parser.y"
                                 {
      (yyval.node) = create_block_node(NULL, NULL, NULL, NULL, NULL, (yyvsp[-1].node), create_location((yyloc)));
    }
#line 1998 "parser/parser.tab.c"
    break;

  case 18: /* label_declaration: LABEL unsigned_integer  */
#line 193 "parser/parser.y"
                           { (yyval.node) = create_label_declaration_node((yyvsp[0].node), create_location((yyloc))); }
#line 2004 "parser/parser.tab.c"
    break;

  case 19: /* label_declaration: label_declaration COMMA unsigned_integer  */
#line 194 "parser/parser.y"
                                             {
      (yyval.node) = append_label_declaration((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2012 "parser/parser.tab.c"
    break;

  case 20: /* constant_declaration: CONST identifier EQ constant  */
#line 199 "parser/parser.y"
                                 {
      (yyval.node) = create_constant_declaration_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2020 "parser/parser.tab.c"
    break;

  case 21: /* constant_declaration: constant_declaration SEMICOLON identifier EQ constant  */
#line 202 "parser/parser.y"
                                                           {
      (yyval.node) = append_constant_declaration((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2028 "parser/parser.tab.c"
    break;

  case 22: /* type_declaration: TYPE identifier EQ type  */
#line 207 "parser/parser.y"
                            { (yyval.node) = create_type_declaration_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2034 "parser/parser.tab.c"
    break;

  case 23: /* type_declaration: type_declaration SEMICOLON identifier EQ type  */
#line 208 "parser/parser.y"
                                                  {
      (yyval.node) = append_type_declaration((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2042 "parser/parser.tab.c"
    break;

  case 24: /* variable_declaration: VAR variableid_list COLON type  */
#line 213 "parser/parser.y"
                                   { (yyval.node) = create_variable_declaration_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2048 "parser/parser.tab.c"
    break;

  case 25: /* variable_declaration: variable_declaration SEMICOLON variableid_list COLON type  */
#line 214 "parser/parser.y"
                                                              {
      (yyval.node) = append_variable_declaration((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2056 "parser/parser.tab.c"
    break;

  case 26: /* variableid_list: identifier  */
#line 219 "parser/parser.y"
                { (yyval.node) = create_variable_identifier_list_node((yyvsp[0].node), create_location((yyloc))); }
#line 2062 "parser/parser.tab.c"
    break;

  case 27: /* variableid_list: variableid_list COMMA identifier  */
#line 220 "parser/parser.y"
                                     {
      (yyval.node) = append_variable_identifier_list((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2070 "parser/parser.tab.c"
    break;

  case 28: /* constant: integer_literal  */
#line 225 "parser/parser.y"
                    {
      (yyval.node) = create_constant_literal((yyvsp[0].node), create_location((yyloc)));
    }
#line 2078 "parser/parser.tab.c"
    break;

  case 29: /* constant: real_literal  */
#line 228 "parser/parser.y"
                 {
      (yyval.node) = create_constant_literal((yyvsp[0].node), create_location((yyloc)));
    }
#line 2086 "parser/parser.tab.c"
    break;

  case 30: /* constant: string_literal  */
#line 231 "parser/parser.y"
                   {
      (yyval.node) = create_constant_literal((yyvsp[0].node), create_location((yyloc)));
    }
#line 2094 "parser/parser.tab.c"
    break;

  case 31: /* constant: constid  */
#line 234 "parser/parser.y"
            { (yyval.node) = create_constant_identifier((yyvsp[0].node), create_location((yyloc))); }
#line 2100 "parser/parser.tab.c"
    break;

  case 32: /* constant: PLUS constid  */
#line 235 "parser/parser.y"
                 { (yyval.node) = create_constant_signed_identifier((yyvsp[0].node), "+", create_location((yyloc))); }
#line 2106 "parser/parser.tab.c"
    break;

  case 33: /* constant: MINUS constid  */
#line 236 "parser/parser.y"
                  { (yyval.node) = create_constant_signed_identifier((yyvsp[0].node), "-", create_location((yyloc))); }
#line 2112 "parser/parser.tab.c"
    break;

  case 34: /* type: simple_type  */
#line 239 "parser/parser.y"
                {
      (yyval.node) = create_simple_type_node((yyvsp[0].node), create_location((yyloc)));
    }
#line 2120 "parser/parser.tab.c"
    break;

  case 35: /* type: structured_type  */
#line 242 "parser/parser.y"
                    {
      (yyval.node) = create_structure_type_node((yyvsp[0].node), create_location((yyloc)));
    }
#line 2128 "parser/parser.tab.c"
    break;

  case 36: /* type: CARET typeid  */
#line 245 "parser/parser.y"
                 {
      (yyval.node) = create_poniter_type_node((yyvsp[0].node), create_location((yyloc)));
    }
#line 2136 "parser/parser.tab.c"
    break;

  case 37: /* simple_type: L_PAREN identifier_list R_PAREN  */
#line 250 "parser/parser.y"
                                     { (yyval.node) = create_identifier_list_node((yyvsp[-1].node), create_location((yyloc))); }
#line 2142 "parser/parser.tab.c"
    break;

  case 38: /* simple_type: constant DOTDOT constant  */
#line 251 "parser/parser.y"
                             {
      (yyval.node) = create_record_access_type((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2150 "parser/parser.tab.c"
    break;

  case 39: /* simple_type: typeid  */
#line 254 "parser/parser.y"
           {
      (yyval.node) = create_type_identifier((yyvsp[0].node), create_location((yyloc)));
    }
#line 2158 "parser/parser.tab.c"
    break;

  case 40: /* structured_type: ARRAY L_BRACKET index_list R_BRACKET OF type  */
#line 259 "parser/parser.y"
                                                 {
      (yyval.node) = create_array_type_node((yyvsp[-3].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2166 "parser/parser.tab.c"
    break;

  case 41: /* structured_type: RECORD field_list END  */
#line 262 "parser/parser.y"
                          {
    (yyval.node) = create_record_type_node((yyvsp[-1].node), create_location((yyloc)));
  }
#line 2174 "parser/parser.tab.c"
    break;

  case 42: /* structured_type: SET OF simple_type  */
#line 265 "parser/parser.y"
                       {
    (yyval.node) = create_set_of_type_node((yyvsp[0].node), create_location((yyloc)));
  }
#line 2182 "parser/parser.tab.c"
    break;

  case 43: /* structured_type: FILE_TOK OF type  */
#line 268 "parser/parser.y"
                     {
    (yyval.node) = create_file_of_type_node((yyvsp[0].node), create_location((yyloc)));
  }
#line 2190 "parser/parser.tab.c"
    break;

  case 44: /* structured_type: PACKED structured_type  */
#line 271 "parser/parser.y"
                           {
    (yyval.node) = create_packed_type((yyvsp[0].node), create_location((yyloc)));
  }
#line 2198 "parser/parser.tab.c"
    break;

  case 45: /* index_list: simple_type  */
#line 276 "parser/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 2204 "parser/parser.tab.c"
    break;

  case 46: /* index_list: index_list COMMA simple_type  */
#line 277 "parser/parser.y"
                                 {
      (yyval.node) = create_index_list_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2212 "parser/parser.tab.c"
    break;

  case 47: /* field_list: fixed_part  */
#line 282 "parser/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 2218 "parser/parser.tab.c"
    break;

  case 48: /* field_list: fixed_part SEMICOLON variant_part  */
#line 283 "parser/parser.y"
                                      { (yyval.node) = create_field_list((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2224 "parser/parser.tab.c"
    break;

  case 49: /* field_list: variant_part  */
#line 284 "parser/parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 2230 "parser/parser.tab.c"
    break;

  case 50: /* fixed_part: record_field  */
#line 287 "parser/parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 2236 "parser/parser.tab.c"
    break;

  case 51: /* fixed_part: fixed_part SEMICOLON record_field  */
#line 288 "parser/parser.y"
                                      { (yyval.node) = create_fixed_part_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2242 "parser/parser.tab.c"
    break;

  case 53: /* record_field: fieldid_list COLON type  */
#line 292 "parser/parser.y"
                            { (yyval.node) = create_record_field_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2248 "parser/parser.tab.c"
    break;

  case 54: /* fieldid_list: identifier  */
#line 295 "parser/parser.y"
               { (yyval.node) = (yyvsp[0].node); /* Identifier of field identifier list (problably func or proc) */ }
#line 2254 "parser/parser.tab.c"
    break;

  case 55: /* fieldid_list: fieldid_list COMMA identifier  */
#line 296 "parser/parser.y"
                                  { (yyval.node) = create_field_identifier_list_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2260 "parser/parser.tab.c"
    break;

  case 56: /* variant_part: CASE tag_field OF variant_list  */
#line 299 "parser/parser.y"
                                   { (yyval.node) = create_case_of_variant_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2266 "parser/parser.tab.c"
    break;

  case 57: /* tag_field: typeid  */
#line 302 "parser/parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 2272 "parser/parser.tab.c"
    break;

  case 58: /* tag_field: identifier COLON typeid  */
#line 303 "parser/parser.y"
                            { (yyval.node) = create_tag_field_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2278 "parser/parser.tab.c"
    break;

  case 59: /* variant_list: variant  */
#line 306 "parser/parser.y"
            { (yyval.node) = (yyvsp[0].node); }
#line 2284 "parser/parser.tab.c"
    break;

  case 60: /* variant_list: variant_list SEMICOLON variant  */
#line 307 "parser/parser.y"
                                   {
      (yyval.node) = append_variant_list((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2292 "parser/parser.tab.c"
    break;

  case 62: /* variant: case_label_list COLON L_PAREN field_list R_PAREN  */
#line 313 "parser/parser.y"
                                                     {
      (yyval.node) = create_variant_node((yyvsp[-4].node), (yyvsp[-1].node), create_location((yyloc)));
    }
#line 2300 "parser/parser.tab.c"
    break;

  case 63: /* case_label_list: constant  */
#line 318 "parser/parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 2306 "parser/parser.tab.c"
    break;

  case 64: /* case_label_list: case_label_list COMMA constant  */
#line 319 "parser/parser.y"
                                   { (yyval.node) = append_case_list_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2312 "parser/parser.tab.c"
    break;

  case 65: /* proc_and_func_declaration: proc_or_func  */
#line 322 "parser/parser.y"
                 { (yyval.node) = create_proc_and_func_declarations_node((yyvsp[0].node), create_location((yyloc))); }
#line 2318 "parser/parser.tab.c"
    break;

  case 66: /* proc_and_func_declaration: proc_and_func_declaration SEMICOLON proc_or_func  */
#line 323 "parser/parser.y"
                                                     {
      (yyval.node) = append_proc_and_func_declarations((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2326 "parser/parser.tab.c"
    break;

  case 67: /* proc_or_func: PROCEDURE identifier parameters SEMICOLON block_or_forward  */
#line 328 "parser/parser.y"
                                                               { /* identifier of func/proc declaration */ 
      (yyval.node) = create_proc_declaration_node((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2334 "parser/parser.tab.c"
    break;

  case 68: /* proc_or_func: FUNCTION identifier parameters COLON typeid SEMICOLON block_or_forward  */
#line 331 "parser/parser.y"
                                                                           {
      (yyval.node) = create_func_declaration_node((yyvsp[-5].node), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2342 "parser/parser.tab.c"
    break;

  case 69: /* block_or_forward: block  */
#line 336 "parser/parser.y"
          { (yyval.node) = (yyvsp[0].node); }
#line 2348 "parser/parser.tab.c"
    break;

  case 70: /* block_or_forward: FORWARD  */
#line 337 "parser/parser.y"
             { /* descobrir o que fazer com forward */ }
#line 2354 "parser/parser.tab.c"
    break;

  case 71: /* parameters: L_PAREN formal_parameter_list R_PAREN  */
#line 340 "parser/parser.y"
                                         { (yyval.node) = create_parameters_node((yyvsp[-1].node), create_location((yyloc))); }
#line 2360 "parser/parser.tab.c"
    break;

  case 72: /* formal_parameter_list: formal_parameter_section  */
#line 343 "parser/parser.y"
                             { (yyval.node) = (yyvsp[0].node); }
#line 2366 "parser/parser.tab.c"
    break;

  case 73: /* formal_parameter_list: formal_parameter_list SEMICOLON formal_parameter_section  */
#line 344 "parser/parser.y"
                                                             {
      (yyval.node) = create_formal_parameters_list_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2374 "parser/parser.tab.c"
    break;

  case 74: /* formal_parameter_section: parameterid_list COLON typeid  */
#line 349 "parser/parser.y"
                                  { (yyval.node) = create_parameter_list_types_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2380 "parser/parser.tab.c"
    break;

  case 75: /* formal_parameter_section: VAR parameterid_list COLON typeid  */
#line 350 "parser/parser.y"
                                      { (yyval.node) = create_parameter_list_types_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2386 "parser/parser.tab.c"
    break;

  case 76: /* formal_parameter_section: PROCEDURE identifier parameters  */
#line 351 "parser/parser.y"
                                    { (yyval.node) = create_procedure_param_node((yyvsp[-1].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2392 "parser/parser.tab.c"
    break;

  case 77: /* formal_parameter_section: FUNCTION identifier parameters COLON typeid  */
#line 352 "parser/parser.y"
                                                { (yyval.node) = create_function_param_node((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2398 "parser/parser.tab.c"
    break;

  case 78: /* parameterid_list: identifier  */
#line 355 "parser/parser.y"
                { (yyval.node) = (yyvsp[0].node); /* identifier of func parameter */ }
#line 2404 "parser/parser.tab.c"
    break;

  case 79: /* parameterid_list: parameterid_list COMMA identifier  */
#line 356 "parser/parser.y"
                                       { (yyval.node) = create_parameter_identifier_list_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); /* identifier of func parameter */ }
#line 2410 "parser/parser.tab.c"
    break;

  case 80: /* statement_list: statement  */
#line 359 "parser/parser.y"
              { (yyval.node) = create_stmt_list_node((yyvsp[0].node), create_location((yyloc))); }
#line 2416 "parser/parser.tab.c"
    break;

  case 81: /* statement_list: statement_list SEMICOLON statement  */
#line 360 "parser/parser.y"
                                       { (yyval.node) = append_stmt_list((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2422 "parser/parser.tab.c"
    break;

  case 83: /* statement: variable ASSIGN expression  */
#line 364 "parser/parser.y"
                               { (yyval.node) = create_assign_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2428 "parser/parser.tab.c"
    break;

  case 84: /* statement: BEGIN_TOK statement_list END  */
#line 365 "parser/parser.y"
                                  { (yyval.node) = create_stmt_list_node((yyvsp[-1].node), create_location((yyloc))); }
#line 2434 "parser/parser.tab.c"
    break;

  case 85: /* statement: IF expression THEN statement  */
#line 366 "parser/parser.y"
                                                       { (yyval.node) = create_if_stmt_node((yyvsp[-2].node), (yyvsp[0].node), NULL, create_location((yyloc))); }
#line 2440 "parser/parser.tab.c"
    break;

  case 86: /* statement: IF expression THEN statement ELSE statement  */
#line 367 "parser/parser.y"
                                                { (yyval.node) = create_if_stmt_node((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2446 "parser/parser.tab.c"
    break;

  case 87: /* statement: CASE expression OF case_list END  */
#line 368 "parser/parser.y"
                                     { (yyval.node) = create_case_stmt_node((yyvsp[-3].node), (yyvsp[-1].node), NULL, create_location((yyloc))); }
#line 2452 "parser/parser.tab.c"
    break;

  case 88: /* statement: CASE expression OF case_list case_else END  */
#line 369 "parser/parser.y"
                                               { (yyval.node) = create_case_stmt_with_else_node((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[-1].node), create_location((yyloc))); }
#line 2458 "parser/parser.tab.c"
    break;

  case 89: /* statement: WHILE expression DO statement  */
#line 370 "parser/parser.y"
                                  { (yyval.node) = create_while_stmt_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2464 "parser/parser.tab.c"
    break;

  case 90: /* statement: REPEAT statement_list UNTIL expression  */
#line 371 "parser/parser.y"
                                           { (yyval.node) = create_repeat_until_stmt_list_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2470 "parser/parser.tab.c"
    break;

  case 91: /* statement: FOR varid ASSIGN for_list DO statement  */
#line 372 "parser/parser.y"
                                           { (yyval.node) = create_for_stmt_node((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2476 "parser/parser.tab.c"
    break;

  case 92: /* statement: procid  */
#line 373 "parser/parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 2482 "parser/parser.tab.c"
    break;

  case 93: /* statement: procid L_PAREN expression_list R_PAREN  */
#line 374 "parser/parser.y"
                                           { (yyval.node) = create_procedure_call_node((yyvsp[-3].node), (yyvsp[-1].node), create_location((yyloc))); }
#line 2488 "parser/parser.tab.c"
    break;

  case 94: /* statement: GOTO label  */
#line 375 "parser/parser.y"
               { (yyval.node) = create_goto_label_node((yyvsp[0].node), create_location((yyloc))); }
#line 2494 "parser/parser.tab.c"
    break;

  case 95: /* statement: WITH record_variable_list DO statement  */
#line 376 "parser/parser.y"
                                           { (yyval.node) = create_with_record_list_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2500 "parser/parser.tab.c"
    break;

  case 96: /* statement: label COLON statement  */
#line 377 "parser/parser.y"
                          { (yyval.node) = create_label_stmt_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2506 "parser/parser.tab.c"
    break;

  case 97: /* variable: identifier  */
#line 380 "parser/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 2512 "parser/parser.tab.c"
    break;

  case 98: /* variable: variable L_BRACKET subscript_list R_BRACKET  */
#line 381 "parser/parser.y"
                                                { (yyval.node) = create_array_access_node((yyvsp[-3].node), (yyvsp[-1].node), create_location((yyloc))); }
#line 2518 "parser/parser.tab.c"
    break;

  case 99: /* variable: variable DOT fieldid  */
#line 382 "parser/parser.y"
                         { (yyval.node) = create_record_access_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2524 "parser/parser.tab.c"
    break;

  case 100: /* variable: variable CARET  */
#line 383 "parser/parser.y"
                   { (yyval.node) = create_pointer_deref_node((yyvsp[-1].node), create_location((yyloc))); }
#line 2530 "parser/parser.tab.c"
    break;

  case 101: /* subscript_list: expression  */
#line 386 "parser/parser.y"
               { 
        (yyval.node) = create_subscript_list_node((yyvsp[0].node), create_location((yyloc))); 
    }
#line 2538 "parser/parser.tab.c"
    break;

  case 102: /* subscript_list: subscript_list COMMA expression  */
#line 389 "parser/parser.y"
                                    { 
        (yyval.node) = append_subscript_list_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2546 "parser/parser.tab.c"
    break;

  case 103: /* case_list: case_element  */
#line 394 "parser/parser.y"
                 {
      (yyval.node) = create_case_list_node((yyvsp[0].node), create_location((yyloc)));
    }
#line 2554 "parser/parser.tab.c"
    break;

  case 104: /* case_list: case_list case_element  */
#line 397 "parser/parser.y"
                           {
      (yyval.node) = append_case_list_node((yyvsp[-1].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2562 "parser/parser.tab.c"
    break;

  case 105: /* case_element: case_label_list COLON statement SEMICOLON  */
#line 402 "parser/parser.y"
                                              {
      (yyval.node) = create_case_element_node((yyvsp[-3].node), (yyvsp[-1].node), create_location((yyloc)));
    }
#line 2570 "parser/parser.tab.c"
    break;

  case 106: /* case_else: ELSE statement SEMICOLON  */
#line 407 "parser/parser.y"
                             {
      (yyval.node) = create_case_else_node((yyvsp[-1].node), create_location((yyloc)));
    }
#line 2578 "parser/parser.tab.c"
    break;

  case 111: /* label: unsigned_integer  */
#line 421 "parser/parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 2584 "parser/parser.tab.c"
    break;

  case 144: /* primary_expression: NIL  */
#line 474 "parser/parser.y"
        {
      (yyval.node) = create_nil_literal(create_location((yyloc)));
    }
#line 2592 "parser/parser.tab.c"
    break;

  case 153: /* constid: identifier  */
#line 491 "parser/parser.y"
               { /* identifier of const */ }
#line 2598 "parser/parser.tab.c"
    break;

  case 159: /* typeid: identifier  */
#line 499 "parser/parser.y"
                { /* identifier of type */ }
#line 2604 "parser/parser.tab.c"
    break;

  case 160: /* funcid: identifier  */
#line 502 "parser/parser.y"
               { /* identifier of func */ }
#line 2610 "parser/parser.tab.c"
    break;

  case 161: /* procid: identifier  */
#line 505 "parser/parser.y"
              { /* identifier of proc */ }
#line 2616 "parser/parser.tab.c"
    break;

  case 166: /* fieldid: identifier  */
#line 512 "parser/parser.y"
              { /* identifier of field */ }
#line 2622 "parser/parser.tab.c"
    break;

  case 167: /* varid: identifier  */
#line 515 "parser/parser.y"
              { /* identifier of variable */ }
#line 2628 "parser/parser.tab.c"
    break;

  case 168: /* identifier: IDENTIFIER  */
#line 518 "parser/parser.y"
              { (yyval.node) = create_identifier_node((yyvsp[0].string), create_location((yyloc))); }
#line 2634 "parser/parser.tab.c"
    break;

  case 169: /* unsigned_integer: INTEGER_LITERAL  */
#line 521 "parser/parser.y"
                    {
      (yyval.node) = create_unsigned_integer_node((yyvsp[0].integer), create_location((yyloc)));
    }
#line 2642 "parser/parser.tab.c"
    break;

  case 170: /* unsigned_real: REAL_LITERAL  */
#line 526 "parser/parser.y"
                 {
      (yyval.node) = create_unsigned_real_node((yyvsp[0].number), create_location((yyloc)));
    }
#line 2650 "parser/parser.tab.c"
    break;

  case 171: /* integer_literal: INTEGER_LITERAL  */
#line 531 "parser/parser.y"
                    {
      (yyval.node) = create_integer_literal((yyvsp[0].integer), create_location((yyloc)));
    }
#line 2658 "parser/parser.tab.c"
    break;

  case 172: /* real_literal: REAL_LITERAL  */
#line 536 "parser/parser.y"
                 {
      (yyval.node) = create_real_literal((yyvsp[0].number), create_location((yyloc)));
    }
#line 2666 "parser/parser.tab.c"
    break;

  case 173: /* string_literal: STRING_LITERAL  */
#line 541 "parser/parser.y"
                   {
      (yyval.node) = create_string_literal((yyvsp[0].string), create_location((yyloc)));
    }
#line 2674 "parser/parser.tab.c"
    break;

  case 174: /* empty: %empty  */
#line 555 "parser/parser.y"
       { (yyval.node) = NULL; }
#line 2680 "parser/parser.tab.c"
    break;


#line 2684 "parser/parser.tab.c"

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

