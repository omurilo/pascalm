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
#include "../commons.h"
#include "../ast/ast.h"
#include "../symbol-table/symbol-table.h"

ASTNode *root = NULL;
extern ht *HashTable;

#line 82 "parser/parser.tab.c"

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
  YYSYMBOL_CARET = 59,                     /* CARET  */
  YYSYMBOL_ASSIGN = 60,                    /* ASSIGN  */
  YYSYMBOL_SEMICOLON = 61,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 62,                     /* COMMA  */
  YYSYMBOL_COLON = 63,                     /* COLON  */
  YYSYMBOL_L_PAREN = 64,                   /* L_PAREN  */
  YYSYMBOL_R_PAREN = 65,                   /* R_PAREN  */
  YYSYMBOL_L_BRACE = 66,                   /* L_BRACE  */
  YYSYMBOL_R_BRACE = 67,                   /* R_BRACE  */
  YYSYMBOL_L_BRACKET = 68,                 /* L_BRACKET  */
  YYSYMBOL_R_BRACKET = 69,                 /* R_BRACKET  */
  YYSYMBOL_CHAR_LITERAL = 70,              /* CHAR_LITERAL  */
  YYSYMBOL_INTEGER_LITERAL = 71,           /* INTEGER_LITERAL  */
  YYSYMBOL_REAL_LITERAL = 72,              /* REAL_LITERAL  */
  YYSYMBOL_BOOLEAN_LITERAL = 73,           /* BOOLEAN_LITERAL  */
  YYSYMBOL_IDENTIFIER = 74,                /* IDENTIFIER  */
  YYSYMBOL_STRING_LITERAL = 75,            /* STRING_LITERAL  */
  YYSYMBOL_SQRT = 76,                      /* SQRT  */
  YYSYMBOL_NEG = 77,                       /* NEG  */
  YYSYMBOL_IN = 78,                        /* IN  */
  YYSYMBOL_LOWER_THAN_ELSE = 79,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 80,                  /* $accept  */
  YYSYMBOL_pascal_program = 81,            /* pascal_program  */
  YYSYMBOL_program_headingopt = 82,        /* program_headingopt  */
  YYSYMBOL_identifier_list = 83,           /* identifier_list  */
  YYSYMBOL_block = 84,                     /* block  */
  YYSYMBOL_block1 = 85,                    /* block1  */
  YYSYMBOL_block2 = 86,                    /* block2  */
  YYSYMBOL_block3 = 87,                    /* block3  */
  YYSYMBOL_block4 = 88,                    /* block4  */
  YYSYMBOL_block5 = 89,                    /* block5  */
  YYSYMBOL_label_declaration = 90,         /* label_declaration  */
  YYSYMBOL_constant_declaration = 91,      /* constant_declaration  */
  YYSYMBOL_type_declaration = 92,          /* type_declaration  */
  YYSYMBOL_variable_declaration = 93,      /* variable_declaration  */
  YYSYMBOL_variableid_list = 94,           /* variableid_list  */
  YYSYMBOL_constant = 95,                  /* constant  */
  YYSYMBOL_type = 96,                      /* type  */
  YYSYMBOL_simple_type = 97,               /* simple_type  */
  YYSYMBOL_structured_type = 98,           /* structured_type  */
  YYSYMBOL_index_list = 99,                /* index_list  */
  YYSYMBOL_field_list = 100,               /* field_list  */
  YYSYMBOL_fixed_part = 101,               /* fixed_part  */
  YYSYMBOL_record_field = 102,             /* record_field  */
  YYSYMBOL_fieldid_list = 103,             /* fieldid_list  */
  YYSYMBOL_variant_part = 104,             /* variant_part  */
  YYSYMBOL_tag_field = 105,                /* tag_field  */
  YYSYMBOL_variant_list = 106,             /* variant_list  */
  YYSYMBOL_variant = 107,                  /* variant  */
  YYSYMBOL_proc_and_func_declaration = 108, /* proc_and_func_declaration  */
  YYSYMBOL_proc_or_func = 109,             /* proc_or_func  */
  YYSYMBOL_block_or_forward = 110,         /* block_or_forward  */
  YYSYMBOL_parameters = 111,               /* parameters  */
  YYSYMBOL_formal_parameter_list = 112,    /* formal_parameter_list  */
  YYSYMBOL_formal_parameter_section = 113, /* formal_parameter_section  */
  YYSYMBOL_parameterid_list = 114,         /* parameterid_list  */
  YYSYMBOL_statement_list = 115,           /* statement_list  */
  YYSYMBOL_statement = 116,                /* statement  */
  YYSYMBOL_variable = 117,                 /* variable  */
  YYSYMBOL_subscript_list = 118,           /* subscript_list  */
  YYSYMBOL_case_list = 119,                /* case_list  */
  YYSYMBOL_case_item = 120,                /* case_item  */
  YYSYMBOL_case_label_list = 121,          /* case_label_list  */
  YYSYMBOL_case_label = 122,               /* case_label  */
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
#define YYLAST   574

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  80
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  72
/* YYNRULES -- Number of rules.  */
#define YYNRULES  176
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  339

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   334


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
      75,    76,    77,    78,    79
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   141,   141,   147,   150,   153,   156,   161,   162,   167,
     168,   173,   174,   179,   180,   185,   186,   191,   196,   197,
     202,   205,   210,   211,   216,   217,   222,   223,   228,   231,
     234,   237,   238,   239,   242,   245,   248,   253,   254,   257,
     262,   265,   268,   271,   274,   279,   280,   285,   286,   287,
     290,   291,   294,   295,   298,   299,   302,   305,   306,   309,
     310,   315,   316,   321,   322,   327,   330,   335,   336,   339,
     342,   343,   348,   349,   350,   351,   354,   355,   361,   362,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   382,   383,   384,   385,   388,
     391,   396,   397,   402,   407,   408,   413,   414,   419,   424,
     427,   433,   434,   437,   440,   441,   446,   447,   450,   451,
     452,   453,   454,   455,   458,   459,   462,   463,   464,   467,
     468,   471,   472,   473,   474,   475,   476,   479,   480,   483,
     484,   485,   488,   489,   490,   491,   492,   495,   498,   499,
     502,   503,   504,   509,   510,   515,   520,   521,   522,   523,
     524,   525,   531,   536,   539,   540,   541,   542,   545,   550,
     555,   558,   563,   568,   573,   578,   592
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
  "DIVIDE", "DIV", "MOD", "DOT", "DOTDOT", "CARET", "ASSIGN", "SEMICOLON",
  "COMMA", "COLON", "L_PAREN", "R_PAREN", "L_BRACE", "R_BRACE",
  "L_BRACKET", "R_BRACKET", "CHAR_LITERAL", "INTEGER_LITERAL",
  "REAL_LITERAL", "BOOLEAN_LITERAL", "IDENTIFIER", "STRING_LITERAL",
  "SQRT", "NEG", "IN", "LOWER_THAN_ELSE", "$accept", "pascal_program",
  "program_headingopt", "identifier_list", "block", "block1", "block2",
  "block3", "block4", "block5", "label_declaration",
  "constant_declaration", "type_declaration", "variable_declaration",
  "variableid_list", "constant", "type", "simple_type", "structured_type",
  "index_list", "field_list", "fixed_part", "record_field", "fieldid_list",
  "variant_part", "tag_field", "variant_list", "variant",
  "proc_and_func_declaration", "proc_or_func", "block_or_forward",
  "parameters", "formal_parameter_list", "formal_parameter_section",
  "parameterid_list", "statement_list", "statement", "variable",
  "subscript_list", "case_list", "case_item", "case_label_list",
  "case_label", "case_else", "for_list", "expression_list", "label",
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

#define YYPACT_NINF (-294)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-170)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      26,   -28,    82,    37,  -294,    14,    45,  -294,  -294,    -6,
    -294,   558,    14,  -294,    14,    14,   344,    65,    90,    14,
     382,    54,  -294,  -294,  -294,  -294,  -294,    80,    93,   100,
     106,   111,  -294,  -294,   112,  -294,   129,  -294,  -294,  -294,
    -294,  -294,  -294,   135,  -294,  -294,  -294,  -294,  -294,  -294,
    -294,   145,  -294,   145,  -294,   382,   396,    14,   396,    14,
     382,   396,    65,    24,  -294,    -8,   123,   148,  -294,    91,
    -294,  -294,  -294,   495,    65,    22,   340,    13,   115,    14,
     443,    46,   443,    29,   136,   127,    25,  -294,  -294,  -294,
    -294,   396,   396,  -294,  -294,    34,   156,    95,   180,  -294,
     396,  -294,   152,   154,  -294,  -294,  -294,    34,    -1,  -294,
     395,   166,    15,   493,  -294,  -294,   382,    14,  -294,   396,
     396,   382,   396,  -294,  -294,  -294,   183,  -294,   192,  -294,
     117,  -294,  -294,  -294,   328,   159,   -11,   210,   214,    14,
      14,   344,    14,  -294,  -294,   191,  -294,  -294,  -294,  -294,
    -294,   194,  -294,  -294,  -294,  -294,  -294,    14,    14,    14,
      47,  -294,   122,  -294,   544,   344,  -294,   482,   499,   -35,
    -294,  -294,   382,  -294,  -294,  -294,  -294,  -294,  -294,   396,
    -294,  -294,  -294,   396,  -294,  -294,  -294,  -294,  -294,  -294,
     396,  -294,   396,   382,    14,   382,   396,   396,    46,  -294,
    -294,  -294,   527,   -15,   527,  -294,     7,   527,    46,   443,
     443,  -294,   459,   344,   239,   193,  -294,   126,  -294,  -294,
    -294,   459,   443,  -294,  -294,  -294,    51,    46,   132,   145,
     145,    29,  -294,    14,   344,  -294,  -294,  -294,   196,  -294,
     396,   396,  -294,   245,    95,   180,  -294,    70,  -294,    34,
    -294,   240,   280,   527,   203,    31,  -294,   142,  -294,   396,
    -294,   396,  -294,  -294,  -294,  -294,  -294,    21,   236,  -294,
     201,  -294,   -11,    14,   443,  -294,  -294,  -294,  -294,   344,
    -294,   204,  -294,  -294,  -294,   544,   527,  -294,   382,  -294,
     382,   396,   396,    46,  -294,    -7,    46,   382,   527,   527,
     459,   241,    46,   344,  -294,  -294,  -294,  -294,  -294,   344,
    -294,  -294,  -294,   527,   527,  -294,   382,  -294,   262,  -294,
    -294,  -294,   443,   213,  -294,   161,  -294,  -294,  -294,   218,
    -294,  -294,    46,   211,  -294,  -294,   -11,   215,  -294
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,   176,     1,     0,     0,     4,   170,     0,
       5,     0,     0,     3,     0,     0,     0,     0,     0,     0,
     176,     0,     7,     9,    11,    13,    15,     0,     0,     0,
       0,     0,    63,     6,     0,    26,     0,   155,   158,   159,
     157,   156,   160,     0,   161,   171,    18,   166,   164,   167,
     165,     0,   163,     0,   162,   176,     0,     0,     0,     0,
     176,     0,     0,     0,    78,     0,     0,    90,    95,   163,
     113,    80,     2,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   146,   141,   139,
     140,     0,   176,   172,   175,   142,     0,   117,   125,   130,
       0,   138,     0,   169,   143,   144,   145,   114,     0,   169,
       0,     0,     0,     0,    92,    17,   176,     0,    98,     0,
       0,   176,     0,     8,    19,    10,     0,    12,     0,    14,
       0,    16,    64,    27,     0,     0,   176,     0,     0,     0,
       0,     0,     0,   173,   174,     0,    24,    34,    35,    31,
      39,   161,    28,    29,    30,    20,    22,     0,     0,     0,
       0,    70,     0,    76,     0,     0,    82,     0,   153,     0,
     151,   150,   176,   123,   122,   118,   119,   121,   120,     0,
     128,   126,   127,     0,   135,   131,   132,   133,   134,   136,
       0,   137,     0,   176,     0,   176,     0,     0,     0,    79,
      97,   168,    81,     0,    99,    94,     0,   111,     0,     0,
       0,    44,     0,     0,     0,    47,    50,     0,    49,    54,
      52,     0,     0,    32,    33,    36,     0,     0,     0,     0,
       0,     0,    69,     0,     0,    68,    67,    65,     0,   149,
       0,     0,   148,    83,   116,   124,   129,     0,    93,   115,
      87,     0,     0,    88,   106,     0,   101,     0,   104,     0,
      96,     0,    91,    21,    23,    25,    45,     0,     0,    57,
     161,    41,   176,     0,     0,    42,    43,    37,    38,     0,
      74,     0,    71,    77,    72,     0,   154,   152,   176,   147,
     176,     0,     0,     0,    85,     0,     0,   176,   100,   112,
       0,     0,   176,     0,    51,    48,    55,    53,    73,     0,
      66,    84,    89,   109,   110,   107,   176,   102,     0,   105,
     103,    46,     0,    56,    59,     0,    61,    58,    75,     0,
      86,    40,   176,     0,   108,    60,   176,     0,    62
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -294,  -294,  -294,   140,   272,   216,   209,   220,   228,   212,
    -294,  -294,  -294,  -294,   229,   -40,   -57,  -201,   163,  -294,
     -23,  -294,    36,  -294,    43,  -294,  -294,   -16,  -294,   243,
      33,   -52,  -294,    88,   171,    40,   -50,    50,  -294,  -294,
      41,  -293,    39,  -294,  -294,   147,   270,  -294,   190,  -294,
     158,  -294,   168,  -294,   -96,  -294,  -294,  -294,   116,   -13,
       8,   333,   335,  -111,   297,    -2,   -12,  -294,  -294,  -294,
     133,    -3
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     2,     6,     9,   236,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    34,   145,   146,   147,   148,   267,
     214,   215,   216,   217,   218,   268,   323,   324,    31,    32,
     237,    84,   160,   161,   162,    63,    64,    95,   203,   255,
     256,   257,   258,   318,   251,   206,    66,   108,   168,   179,
      97,   183,    98,   190,    99,   100,   101,   169,   170,   149,
     150,   102,    67,   219,    68,   103,   104,   105,   152,   153,
     106,    71
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
       7,    85,    36,    10,   191,    46,   200,   316,    70,   325,
      33,   266,    35,    37,    44,   213,    52,    54,    69,   193,
     275,    18,    19,    20,    43,   156,    14,   241,    16,     1,
      18,    19,    20,   157,   242,   115,   166,   158,   159,   325,
     197,   155,   294,    70,   139,   140,     3,   259,    70,   117,
      70,   118,   119,    69,   260,   109,    12,   109,    69,    13,
     120,   194,   124,     8,   143,   144,   199,     8,    94,   261,
      65,   205,   262,   126,    44,    35,   116,   133,   151,    37,
     151,   163,     4,   300,   128,   116,   116,     8,     8,   171,
     301,   117,   295,   118,   246,    86,     8,   139,   140,   321,
     112,     5,   120,     8,    70,    65,    11,   107,   231,    70,
      65,    72,   232,    12,    69,   201,   277,   143,   144,    69,
       8,    94,   243,    18,    19,    20,   223,   224,    47,    48,
      49,    50,   261,   220,   201,   289,    45,    37,    37,    44,
      10,    73,    74,   248,   180,   250,   181,   182,  -169,   225,
    -169,  -169,   264,   265,    75,   163,   229,   230,   254,  -169,
      70,    76,   306,    44,     8,   276,    65,    77,   263,   172,
      69,    65,    78,   238,    79,    80,    81,   280,   281,    79,
     210,    70,    82,    70,   233,   234,   121,   278,   273,   274,
     165,    69,   109,    69,   233,   279,    37,   164,   173,   174,
     175,   176,   177,   178,   296,   297,    37,   151,   151,    83,
     151,   270,   122,   154,   154,   154,   192,   307,  -162,   151,
     151,   269,    65,   296,   333,    37,   196,   212,   184,   163,
     208,   283,    44,   185,   186,   187,   188,   221,   311,   209,
     312,   222,   284,    65,   249,    65,    96,   320,   110,   227,
     271,   113,  -155,   315,   272,   254,   254,   285,   189,   288,
     290,   293,   254,   302,   303,   331,   329,   309,   322,   220,
     201,   201,   151,   330,   332,   336,    70,    44,    70,   334,
     338,   167,   226,    21,   125,    70,    69,   308,    69,   123,
     131,    37,   254,    37,    37,    69,   127,   211,   151,   326,
      37,    44,   291,   292,    70,   129,   130,    44,   304,   202,
     204,   327,   207,   337,    69,   305,   335,   328,   310,   282,
     151,   132,   173,   174,   175,   176,   177,   178,   228,   326,
      37,   154,   114,   220,   201,   319,   317,   244,    65,   247,
      65,   154,   154,   154,    14,   154,   134,    65,    18,    19,
      20,   245,    53,    51,   154,   154,   111,   287,     0,     0,
     154,   135,   136,   137,   138,     0,    65,     0,     0,    38,
      39,    40,    41,    38,    39,    40,    41,    42,     0,     0,
       0,    42,   207,     0,     0,     0,   252,   253,     0,     0,
       0,     0,    55,     0,    56,     0,     0,     0,    57,     0,
       0,    58,     0,    59,     0,     0,    60,   154,    61,     0,
      62,    87,     0,     0,     8,   195,     0,     0,     8,     0,
      47,    48,    49,    50,     0,     0,   154,     0,   154,   154,
     286,     0,     0,   154,     0,   154,     0,   173,   174,   175,
     176,   177,   178,     0,     0,     0,    88,    89,    90,   298,
       0,   299,     0,    45,     0,   154,     8,     0,     0,     0,
      91,   134,     0,     0,    92,   154,     0,    45,    93,     0,
       8,    94,    38,    39,    40,    41,   135,   136,   137,   138,
      42,   313,   314,     0,     0,     0,     0,     0,    38,    39,
      40,    41,     0,     0,   139,   140,    42,     0,     0,    14,
      15,    16,   141,    18,    19,    20,     0,   142,     0,     0,
     139,   140,     0,     0,   143,   144,     0,     8,    94,     0,
     198,     0,     0,   142,   173,   174,   175,   176,   177,   178,
     143,   144,     0,     8,    94,   173,   174,   175,   176,   177,
     178,   173,   174,   175,   176,   177,   178,   239,    14,    15,
      16,    17,    18,    19,    20,     0,     0,   240,     0,     0,
       0,   235,    14,    15,    16,    17,    18,    19,    20,   173,
     174,   175,   176,   177,   178
};

static const yytype_int16 yycheck[] =
{
       3,    53,    15,     5,   100,    17,   117,    14,    20,   302,
      12,   212,    14,    15,    16,    26,    18,    19,    20,    20,
     221,     8,     9,    10,    16,    82,     4,    62,     6,     3,
       8,     9,    10,     4,    69,    11,    11,     8,     9,   332,
      25,    81,    11,    55,    51,    52,    74,    62,    60,    57,
      62,    59,    60,    55,    69,    57,    62,    59,    60,    65,
      68,    62,    74,    74,    71,    72,   116,    74,    75,    62,
      20,   121,    65,    75,    76,    77,    61,    79,    80,    81,
      82,    83,     0,    62,    76,    61,    61,    74,    74,    92,
      69,    57,    61,    59,   190,    55,    74,    51,    52,   300,
      60,    64,    68,    74,   116,    55,    61,    57,    61,   121,
      60,    57,    65,    62,   116,   117,    65,    71,    72,   121,
      74,    75,   172,     8,     9,    10,   139,   140,    38,    39,
      40,    41,    62,   136,   136,    65,    71,   139,   140,   141,
     142,    61,    62,   193,    49,   195,    51,    52,    57,   141,
      59,    60,   209,   210,    61,   157,   158,   159,   198,    68,
     172,    61,   273,   165,    74,   222,   116,    61,   208,    13,
     172,   121,    61,   165,    62,    63,    47,   229,   230,    62,
      63,   193,    47,   195,    62,    63,    63,   227,    62,    63,
      63,   193,   194,   195,    62,    63,   198,    61,    42,    43,
      44,    45,    46,    47,    62,    63,   208,   209,   210,    64,
     212,   213,    64,    80,    81,    82,    64,   274,    64,   221,
     222,   213,   172,    62,    63,   227,    60,    68,    48,   231,
      47,   233,   234,    53,    54,    55,    56,    27,   288,    47,
     290,    27,   234,   193,   194,   195,    56,   297,    58,    58,
      11,    61,    58,   293,    61,   295,   296,    61,    78,    14,
      20,    58,   302,    27,    63,   322,   316,    63,    27,   272,
     272,   273,   274,    11,    61,    64,   288,   279,   290,    61,
      65,    91,   142,    11,    75,   297,   288,   279,   290,    73,
      78,   293,   332,   295,   296,   297,    76,   134,   300,   302,
     302,   303,    22,    23,   316,    77,    77,   309,   272,   119,
     120,   303,   122,   336,   316,   272,   332,   309,   285,   231,
     322,    78,    42,    43,    44,    45,    46,    47,   157,   332,
     332,   198,    62,   336,   336,   296,   295,   179,   288,   192,
     290,   208,   209,   210,     4,   212,    18,   297,     8,     9,
      10,   183,    19,    18,   221,   222,    59,   241,    -1,    -1,
     227,    33,    34,    35,    36,    -1,   316,    -1,    -1,    29,
      30,    31,    32,    29,    30,    31,    32,    37,    -1,    -1,
      -1,    37,   192,    -1,    -1,    -1,   196,   197,    -1,    -1,
      -1,    -1,    10,    -1,    12,    -1,    -1,    -1,    16,    -1,
      -1,    19,    -1,    21,    -1,    -1,    24,   274,    26,    -1,
      28,    15,    -1,    -1,    74,    20,    -1,    -1,    74,    -1,
      38,    39,    40,    41,    -1,    -1,   293,    -1,   295,   296,
     240,    -1,    -1,   300,    -1,   302,    -1,    42,    43,    44,
      45,    46,    47,    -1,    -1,    -1,    50,    51,    52,   259,
      -1,   261,    -1,    71,    -1,   322,    74,    -1,    -1,    -1,
      64,    18,    -1,    -1,    68,   332,    -1,    71,    72,    -1,
      74,    75,    29,    30,    31,    32,    33,    34,    35,    36,
      37,   291,   292,    -1,    -1,    -1,    -1,    -1,    29,    30,
      31,    32,    -1,    -1,    51,    52,    37,    -1,    -1,     4,
       5,     6,    59,     8,     9,    10,    -1,    64,    -1,    -1,
      51,    52,    -1,    -1,    71,    72,    -1,    74,    75,    -1,
      27,    -1,    -1,    64,    42,    43,    44,    45,    46,    47,
      71,    72,    -1,    74,    75,    42,    43,    44,    45,    46,
      47,    42,    43,    44,    45,    46,    47,    65,     4,     5,
       6,     7,     8,     9,    10,    -1,    -1,    58,    -1,    -1,
      -1,    17,     4,     5,     6,     7,     8,     9,    10,    42,
      43,    44,    45,    46,    47
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    81,    74,     0,    64,    82,   151,    74,    83,
     145,    61,    62,    65,     4,     5,     6,     7,     8,     9,
      10,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,   108,   109,   145,    94,   145,   139,   145,    29,    30,
      31,    32,    37,   140,   145,    71,   146,    38,    39,    40,
      41,   142,   145,   141,   145,    10,    12,    16,    19,    21,
      24,    26,    28,   115,   116,   117,   126,   142,   144,   145,
     146,   151,    57,    61,    62,    61,    61,    61,    61,    62,
      63,    47,    47,    64,   111,   111,   115,    15,    50,    51,
      52,    64,    68,    72,    75,   117,   128,   130,   132,   134,
     135,   136,   141,   145,   146,   147,   150,   117,   127,   145,
     128,   144,   115,   128,   126,    11,    61,    57,    59,    60,
      68,    63,    64,    85,   146,    86,   145,    87,   140,    88,
      94,    89,   109,   145,    18,    33,    34,    35,    36,    51,
      52,    59,    64,    71,    72,    95,    96,    97,    98,   139,
     140,   145,   148,   149,   150,    95,    96,     4,     8,     9,
     112,   113,   114,   145,    61,    63,    11,   128,   128,   137,
     138,   151,    13,    42,    43,    44,    45,    46,    47,   129,
      49,    51,    52,   131,    48,    53,    54,    55,    56,    78,
     133,   134,    64,    20,    62,    20,    60,    25,    27,   116,
     143,   145,   128,   118,   128,   116,   125,   128,    47,    47,
      63,    98,    68,    26,   100,   101,   102,   103,   104,   143,
     151,    27,    27,   139,   139,   140,    83,    58,   114,   145,
     145,    61,    65,    62,    63,    17,    84,   110,   140,    65,
      58,    62,    69,   116,   130,   132,   134,   125,   116,   117,
     116,   124,   128,   128,    95,   119,   120,   121,   122,    62,
      69,    62,    65,    95,    96,    96,    97,    99,   105,   140,
     145,    11,    61,    62,    63,    97,    96,    65,    95,    63,
     111,   111,   113,   145,   140,    61,   128,   138,    14,    65,
      20,    22,    23,    58,    11,    61,    62,    63,   128,   128,
      62,    69,    27,    63,   102,   104,   143,    96,   140,    63,
     110,   116,   116,   128,   128,    95,    14,   120,   123,   122,
     116,    97,    27,   106,   107,   121,   151,   140,   140,   116,
      11,    96,    61,    63,    61,   107,    64,   100,    65
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    80,    81,    82,    82,    83,    83,    84,    84,    85,
      85,    86,    86,    87,    87,    88,    88,    89,    90,    90,
      91,    91,    92,    92,    93,    93,    94,    94,    95,    95,
      95,    95,    95,    95,    96,    96,    96,    97,    97,    97,
      98,    98,    98,    98,    98,    99,    99,   100,   100,   100,
     101,   101,   102,   102,   103,   103,   104,   105,   105,   106,
     106,   107,   107,   108,   108,   109,   109,   110,   110,   111,
     112,   112,   113,   113,   113,   113,   114,   114,   115,   115,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   117,   117,   117,   117,   118,
     118,   119,   119,   120,   121,   121,   122,   122,   123,   124,
     124,   125,   125,   126,   127,   127,   128,   128,   129,   129,
     129,   129,   129,   129,   130,   130,   131,   131,   131,   132,
     132,   133,   133,   133,   133,   133,   133,   134,   134,   135,
     135,   135,   136,   136,   136,   136,   136,   136,   136,   136,
     137,   137,   137,   138,   138,   139,   140,   140,   140,   140,
     140,   140,   141,   142,   142,   142,   142,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151
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
       3,     1,     5,     1,     3,     5,     7,     1,     1,     3,
       1,     3,     3,     4,     3,     5,     1,     3,     1,     3,
       1,     3,     3,     4,     6,     5,     7,     4,     4,     6,
       1,     4,     2,     4,     3,     1,     4,     3,     2,     1,
       3,     1,     3,     3,     1,     3,     1,     3,     3,     3,
       3,     1,     3,     1,     1,     3,     3,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     1,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     4,     3,     3,
       1,     1,     3,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0
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
#line 141 "parser/parser.y"
                                                             {
      (yyval.node) = create_program_node((yyvsp[-4].string), (yyvsp[-3].node), (yyvsp[-1].node), create_location((yyloc)));
      root = (yyval.node);
   }
#line 1916 "parser/parser.tab.c"
    break;

  case 3: /* program_headingopt: L_PAREN identifier_list R_PAREN  */
#line 147 "parser/parser.y"
                                    {
      (yyval.node) = create_heading_node((yyvsp[-1].node), create_location((yyloc)));
    }
#line 1924 "parser/parser.tab.c"
    break;

  case 5: /* identifier_list: identifier  */
#line 153 "parser/parser.y"
               {
      (yyval.node) = create_identifier_list_node((yyvsp[0].node), create_location((yyloc)));
    }
#line 1932 "parser/parser.tab.c"
    break;

  case 6: /* identifier_list: identifier_list COMMA identifier  */
#line 156 "parser/parser.y"
                                     {
      (yyval.node) = append_identifier_list_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 1940 "parser/parser.tab.c"
    break;

  case 7: /* block: block1  */
#line 161 "parser/parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 1946 "parser/parser.tab.c"
    break;

  case 8: /* block: label_declaration SEMICOLON block1  */
#line 162 "parser/parser.y"
                                       {
      (yyval.node) = add_labels_to_block((yyvsp[0].node), (yyvsp[-2].node));
    }
#line 1954 "parser/parser.tab.c"
    break;

  case 9: /* block1: block2  */
#line 167 "parser/parser.y"
            { (yyval.node) = (yyvsp[0].node); }
#line 1960 "parser/parser.tab.c"
    break;

  case 10: /* block1: constant_declaration SEMICOLON block2  */
#line 168 "parser/parser.y"
                                          {
    (yyval.node) = add_constants_to_block((yyvsp[0].node), (yyvsp[-2].node));
  }
#line 1968 "parser/parser.tab.c"
    break;

  case 11: /* block2: block3  */
#line 173 "parser/parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 1974 "parser/parser.tab.c"
    break;

  case 12: /* block2: type_declaration SEMICOLON block3  */
#line 174 "parser/parser.y"
                                      {
     (yyval.node) = add_types_to_block((yyvsp[0].node), (yyvsp[-2].node));
  }
#line 1982 "parser/parser.tab.c"
    break;

  case 13: /* block3: block4  */
#line 179 "parser/parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 1988 "parser/parser.tab.c"
    break;

  case 14: /* block3: variable_declaration SEMICOLON block4  */
#line 180 "parser/parser.y"
                                          {
      (yyval.node) = add_variables_to_block((yyvsp[0].node), (yyvsp[-2].node));
    }
#line 1996 "parser/parser.tab.c"
    break;

  case 15: /* block4: block5  */
#line 185 "parser/parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 2002 "parser/parser.tab.c"
    break;

  case 16: /* block4: proc_and_func_declaration SEMICOLON block5  */
#line 186 "parser/parser.y"
                                               {
      (yyval.node) = add_procs_funcs_to_block((yyvsp[0].node), (yyvsp[-2].node));
    }
#line 2010 "parser/parser.tab.c"
    break;

  case 17: /* block5: BEGIN_TOK statement_list END  */
#line 191 "parser/parser.y"
                                 {
      (yyval.node) = create_block_node(NULL, NULL, NULL, NULL, NULL, (yyvsp[-1].node), create_location((yyloc)));
    }
#line 2018 "parser/parser.tab.c"
    break;

  case 18: /* label_declaration: LABEL unsigned_integer  */
#line 196 "parser/parser.y"
                           { (yyval.node) = create_label_declaration_node((yyvsp[0].node), create_location((yyloc))); }
#line 2024 "parser/parser.tab.c"
    break;

  case 19: /* label_declaration: label_declaration COMMA unsigned_integer  */
#line 197 "parser/parser.y"
                                             {
      (yyval.node) = append_label_declaration((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2032 "parser/parser.tab.c"
    break;

  case 20: /* constant_declaration: CONST constid EQ constant  */
#line 202 "parser/parser.y"
                              {
      (yyval.node) = create_constant_declaration_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2040 "parser/parser.tab.c"
    break;

  case 21: /* constant_declaration: constant_declaration SEMICOLON identifier EQ constant  */
#line 205 "parser/parser.y"
                                                           {
      (yyval.node) = append_constant_declaration((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2048 "parser/parser.tab.c"
    break;

  case 22: /* type_declaration: TYPE typeid EQ type  */
#line 210 "parser/parser.y"
                        { (yyval.node) = create_type_declaration_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2054 "parser/parser.tab.c"
    break;

  case 23: /* type_declaration: type_declaration SEMICOLON typeid EQ type  */
#line 211 "parser/parser.y"
                                              {
      (yyval.node) = append_type_declaration((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2062 "parser/parser.tab.c"
    break;

  case 24: /* variable_declaration: VAR variableid_list COLON type  */
#line 216 "parser/parser.y"
                                   { (yyval.node) = create_variable_declaration_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2068 "parser/parser.tab.c"
    break;

  case 25: /* variable_declaration: variable_declaration SEMICOLON variableid_list COLON type  */
#line 217 "parser/parser.y"
                                                              {
      (yyval.node) = append_variable_declaration((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2076 "parser/parser.tab.c"
    break;

  case 26: /* variableid_list: identifier  */
#line 222 "parser/parser.y"
                { (yyval.node) = create_variable_identifier_list_node((yyvsp[0].node), create_location((yyloc))); }
#line 2082 "parser/parser.tab.c"
    break;

  case 27: /* variableid_list: variableid_list COMMA identifier  */
#line 223 "parser/parser.y"
                                     {
      (yyval.node) = append_variable_identifier_list((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2090 "parser/parser.tab.c"
    break;

  case 28: /* constant: integer_literal  */
#line 228 "parser/parser.y"
                    {
      (yyval.node) = create_constant_literal((yyvsp[0].node), create_location((yyloc)));
    }
#line 2098 "parser/parser.tab.c"
    break;

  case 29: /* constant: real_literal  */
#line 231 "parser/parser.y"
                 {
      (yyval.node) = create_constant_literal((yyvsp[0].node), create_location((yyloc)));
    }
#line 2106 "parser/parser.tab.c"
    break;

  case 30: /* constant: string_literal  */
#line 234 "parser/parser.y"
                   {
      (yyval.node) = create_constant_literal((yyvsp[0].node), create_location((yyloc)));
    }
#line 2114 "parser/parser.tab.c"
    break;

  case 31: /* constant: constid  */
#line 237 "parser/parser.y"
            { (yyval.node) = create_constant_identifier((yyvsp[0].node), create_location((yyloc))); }
#line 2120 "parser/parser.tab.c"
    break;

  case 32: /* constant: PLUS constid  */
#line 238 "parser/parser.y"
                 { (yyval.node) = create_constant_signed_identifier((yyvsp[0].node), "+", create_location((yyloc))); }
#line 2126 "parser/parser.tab.c"
    break;

  case 33: /* constant: MINUS constid  */
#line 239 "parser/parser.y"
                  { (yyval.node) = create_constant_signed_identifier((yyvsp[0].node), "-", create_location((yyloc))); }
#line 2132 "parser/parser.tab.c"
    break;

  case 34: /* type: simple_type  */
#line 242 "parser/parser.y"
                {
      (yyval.node) = create_simple_type_node((yyvsp[0].node), create_location((yyloc)));
    }
#line 2140 "parser/parser.tab.c"
    break;

  case 35: /* type: structured_type  */
#line 245 "parser/parser.y"
                    {
      (yyval.node) = create_structure_type_node((yyvsp[0].node), create_location((yyloc)));
    }
#line 2148 "parser/parser.tab.c"
    break;

  case 36: /* type: CARET typeid  */
#line 248 "parser/parser.y"
                 {
      (yyval.node) = create_poniter_type_node((yyvsp[0].node), create_location((yyloc)));
    }
#line 2156 "parser/parser.tab.c"
    break;

  case 37: /* simple_type: L_PAREN identifier_list R_PAREN  */
#line 253 "parser/parser.y"
                                     { (yyval.node) = create_identifier_list_node((yyvsp[-1].node), create_location((yyloc))); }
#line 2162 "parser/parser.tab.c"
    break;

  case 38: /* simple_type: constant DOTDOT constant  */
#line 254 "parser/parser.y"
                             {
      (yyval.node) = create_constant_range_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2170 "parser/parser.tab.c"
    break;

  case 39: /* simple_type: typeid  */
#line 257 "parser/parser.y"
           {
      (yyval.node) = (yyvsp[0].node);
    }
#line 2178 "parser/parser.tab.c"
    break;

  case 40: /* structured_type: ARRAY L_BRACKET index_list R_BRACKET OF type  */
#line 262 "parser/parser.y"
                                                 {
      (yyval.node) = create_array_type_node((yyvsp[-3].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2186 "parser/parser.tab.c"
    break;

  case 41: /* structured_type: RECORD field_list END  */
#line 265 "parser/parser.y"
                          {
    (yyval.node) = create_record_type_node((yyvsp[-1].node), create_location((yyloc)));
  }
#line 2194 "parser/parser.tab.c"
    break;

  case 42: /* structured_type: SET OF simple_type  */
#line 268 "parser/parser.y"
                       {
    (yyval.node) = create_set_of_type_node((yyvsp[0].node), create_location((yyloc)));
  }
#line 2202 "parser/parser.tab.c"
    break;

  case 43: /* structured_type: FILE_TOK OF type  */
#line 271 "parser/parser.y"
                     {
    (yyval.node) = create_file_of_type_node((yyvsp[0].node), create_location((yyloc)));
  }
#line 2210 "parser/parser.tab.c"
    break;

  case 44: /* structured_type: PACKED structured_type  */
#line 274 "parser/parser.y"
                           {
    (yyval.node) = create_packed_type((yyvsp[0].node), create_location((yyloc)));
  }
#line 2218 "parser/parser.tab.c"
    break;

  case 45: /* index_list: simple_type  */
#line 279 "parser/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 2224 "parser/parser.tab.c"
    break;

  case 46: /* index_list: index_list COMMA simple_type  */
#line 280 "parser/parser.y"
                                 {
      (yyval.node) = create_index_list_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2232 "parser/parser.tab.c"
    break;

  case 47: /* field_list: fixed_part  */
#line 285 "parser/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 2238 "parser/parser.tab.c"
    break;

  case 48: /* field_list: fixed_part SEMICOLON variant_part  */
#line 286 "parser/parser.y"
                                      { (yyval.node) = create_field_list((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2244 "parser/parser.tab.c"
    break;

  case 49: /* field_list: variant_part  */
#line 287 "parser/parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 2250 "parser/parser.tab.c"
    break;

  case 50: /* fixed_part: record_field  */
#line 290 "parser/parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 2256 "parser/parser.tab.c"
    break;

  case 51: /* fixed_part: fixed_part SEMICOLON record_field  */
#line 291 "parser/parser.y"
                                      { (yyval.node) = create_fixed_part_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2262 "parser/parser.tab.c"
    break;

  case 53: /* record_field: fieldid_list COLON type  */
#line 295 "parser/parser.y"
                            { (yyval.node) = create_record_field_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2268 "parser/parser.tab.c"
    break;

  case 54: /* fieldid_list: fieldid  */
#line 298 "parser/parser.y"
            { (yyval.node) = (yyvsp[0].node); /* Identifier of field identifier list (problably func or proc) */ }
#line 2274 "parser/parser.tab.c"
    break;

  case 55: /* fieldid_list: fieldid_list COMMA fieldid  */
#line 299 "parser/parser.y"
                               { (yyval.node) = create_field_identifier_list_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2280 "parser/parser.tab.c"
    break;

  case 56: /* variant_part: CASE tag_field OF variant_list  */
#line 302 "parser/parser.y"
                                   { (yyval.node) = create_case_of_variant_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2286 "parser/parser.tab.c"
    break;

  case 57: /* tag_field: typeid  */
#line 305 "parser/parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 2292 "parser/parser.tab.c"
    break;

  case 58: /* tag_field: identifier COLON typeid  */
#line 306 "parser/parser.y"
                            { (yyval.node) = create_tag_field_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2298 "parser/parser.tab.c"
    break;

  case 59: /* variant_list: variant  */
#line 309 "parser/parser.y"
            { (yyval.node) = (yyvsp[0].node); }
#line 2304 "parser/parser.tab.c"
    break;

  case 60: /* variant_list: variant_list SEMICOLON variant  */
#line 310 "parser/parser.y"
                                   {
      (yyval.node) = append_variant_list((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2312 "parser/parser.tab.c"
    break;

  case 62: /* variant: case_label_list COLON L_PAREN field_list R_PAREN  */
#line 316 "parser/parser.y"
                                                     {
      (yyval.node) = create_variant_node((yyvsp[-4].node), (yyvsp[-1].node), create_location((yyloc)));
    }
#line 2320 "parser/parser.tab.c"
    break;

  case 63: /* proc_and_func_declaration: proc_or_func  */
#line 321 "parser/parser.y"
                 { (yyval.node) = create_proc_and_func_declarations_node((yyvsp[0].node), create_location((yyloc))); }
#line 2326 "parser/parser.tab.c"
    break;

  case 64: /* proc_and_func_declaration: proc_and_func_declaration SEMICOLON proc_or_func  */
#line 322 "parser/parser.y"
                                                     {
      (yyval.node) = append_proc_and_func_declarations((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2334 "parser/parser.tab.c"
    break;

  case 65: /* proc_or_func: PROCEDURE procid parameters SEMICOLON block_or_forward  */
#line 327 "parser/parser.y"
                                                           { /* identifier of func/proc declaration */ 
      (yyval.node) = create_proc_declaration_node((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2342 "parser/parser.tab.c"
    break;

  case 66: /* proc_or_func: FUNCTION funcid parameters COLON typeid SEMICOLON block_or_forward  */
#line 330 "parser/parser.y"
                                                                       {
      (yyval.node) = create_func_declaration_node((yyvsp[-5].node), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2350 "parser/parser.tab.c"
    break;

  case 67: /* block_or_forward: block  */
#line 335 "parser/parser.y"
          { (yyval.node) = (yyvsp[0].node); }
#line 2356 "parser/parser.tab.c"
    break;

  case 68: /* block_or_forward: FORWARD  */
#line 336 "parser/parser.y"
             { /* descobrir o que fazer com forward */ }
#line 2362 "parser/parser.tab.c"
    break;

  case 69: /* parameters: L_PAREN formal_parameter_list R_PAREN  */
#line 339 "parser/parser.y"
                                         { (yyval.node) = create_parameters_node((yyvsp[-1].node), create_location((yyloc))); }
#line 2368 "parser/parser.tab.c"
    break;

  case 70: /* formal_parameter_list: formal_parameter_section  */
#line 342 "parser/parser.y"
                             { (yyval.node) = (yyvsp[0].node); }
#line 2374 "parser/parser.tab.c"
    break;

  case 71: /* formal_parameter_list: formal_parameter_list SEMICOLON formal_parameter_section  */
#line 343 "parser/parser.y"
                                                             {
      (yyval.node) = create_formal_parameters_list_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2382 "parser/parser.tab.c"
    break;

  case 72: /* formal_parameter_section: parameterid_list COLON typeid  */
#line 348 "parser/parser.y"
                                  { (yyval.node) = create_parameter_list_types_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2388 "parser/parser.tab.c"
    break;

  case 73: /* formal_parameter_section: VAR parameterid_list COLON typeid  */
#line 349 "parser/parser.y"
                                      { (yyval.node) = create_parameter_list_types_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2394 "parser/parser.tab.c"
    break;

  case 74: /* formal_parameter_section: PROCEDURE identifier parameters  */
#line 350 "parser/parser.y"
                                    { (yyval.node) = create_procedure_param_node((yyvsp[-1].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2400 "parser/parser.tab.c"
    break;

  case 75: /* formal_parameter_section: FUNCTION identifier parameters COLON typeid  */
#line 351 "parser/parser.y"
                                                { (yyval.node) = create_function_param_node((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2406 "parser/parser.tab.c"
    break;

  case 76: /* parameterid_list: identifier  */
#line 354 "parser/parser.y"
                { (yyval.node) = (yyvsp[0].node); /* identifier of func parameter */ }
#line 2412 "parser/parser.tab.c"
    break;

  case 77: /* parameterid_list: parameterid_list COMMA identifier  */
#line 355 "parser/parser.y"
                                       { 
      (yyval.node) = create_parameter_identifier_list_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
      /* identifier of func parameter */
    }
#line 2421 "parser/parser.tab.c"
    break;

  case 78: /* statement_list: statement  */
#line 361 "parser/parser.y"
              { (yyval.node) = create_stmt_list_node((yyvsp[0].node), create_location((yyloc))); }
#line 2427 "parser/parser.tab.c"
    break;

  case 79: /* statement_list: statement_list SEMICOLON statement  */
#line 362 "parser/parser.y"
                                       { (yyval.node) = append_stmt_list((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2433 "parser/parser.tab.c"
    break;

  case 81: /* statement: variable ASSIGN expression  */
#line 366 "parser/parser.y"
                               { (yyval.node) = create_assign_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2439 "parser/parser.tab.c"
    break;

  case 82: /* statement: BEGIN_TOK statement_list END  */
#line 367 "parser/parser.y"
                                  { (yyval.node) = create_stmt_list_node((yyvsp[-1].node), create_location((yyloc))); }
#line 2445 "parser/parser.tab.c"
    break;

  case 83: /* statement: IF expression THEN statement  */
#line 368 "parser/parser.y"
                                                       { (yyval.node) = create_if_stmt_node((yyvsp[-2].node), (yyvsp[0].node), NULL, create_location((yyloc))); }
#line 2451 "parser/parser.tab.c"
    break;

  case 84: /* statement: IF expression THEN statement ELSE statement  */
#line 369 "parser/parser.y"
                                                { (yyval.node) = create_if_stmt_node((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2457 "parser/parser.tab.c"
    break;

  case 85: /* statement: CASE expression OF case_list END  */
#line 370 "parser/parser.y"
                                     { (yyval.node) = create_case_stmt_node((yyvsp[-3].node), (yyvsp[-1].node), NULL, create_location((yyloc))); }
#line 2463 "parser/parser.tab.c"
    break;

  case 86: /* statement: CASE expression OF case_list SEMICOLON case_else END  */
#line 371 "parser/parser.y"
                                                         { (yyval.node) = create_case_stmt_with_else_node((yyvsp[-5].node), (yyvsp[-3].node), (yyvsp[-1].node), create_location((yyloc))); }
#line 2469 "parser/parser.tab.c"
    break;

  case 87: /* statement: WHILE expression DO statement  */
#line 372 "parser/parser.y"
                                  { (yyval.node) = create_while_stmt_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2475 "parser/parser.tab.c"
    break;

  case 88: /* statement: REPEAT statement_list UNTIL expression  */
#line 373 "parser/parser.y"
                                           { (yyval.node) = create_repeat_until_stmt_list_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2481 "parser/parser.tab.c"
    break;

  case 89: /* statement: FOR varid ASSIGN for_list DO statement  */
#line 374 "parser/parser.y"
                                           { (yyval.node) = create_for_stmt_node((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2487 "parser/parser.tab.c"
    break;

  case 90: /* statement: procid  */
#line 375 "parser/parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 2493 "parser/parser.tab.c"
    break;

  case 91: /* statement: procid L_PAREN expression_list R_PAREN  */
#line 376 "parser/parser.y"
                                           { (yyval.node) = create_procedure_call_node((yyvsp[-3].node), (yyvsp[-1].node), create_location((yyloc))); }
#line 2499 "parser/parser.tab.c"
    break;

  case 92: /* statement: GOTO label  */
#line 377 "parser/parser.y"
               { (yyval.node) = create_goto_label_node((yyvsp[0].node), create_location((yyloc))); }
#line 2505 "parser/parser.tab.c"
    break;

  case 93: /* statement: WITH record_variable_list DO statement  */
#line 378 "parser/parser.y"
                                           { (yyval.node) = create_with_record_list_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2511 "parser/parser.tab.c"
    break;

  case 94: /* statement: label COLON statement  */
#line 379 "parser/parser.y"
                          { (yyval.node) = create_label_stmt_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2517 "parser/parser.tab.c"
    break;

  case 95: /* variable: varid  */
#line 382 "parser/parser.y"
          { (yyval.node) = (yyvsp[0].node); }
#line 2523 "parser/parser.tab.c"
    break;

  case 96: /* variable: variable L_BRACKET subscript_list R_BRACKET  */
#line 383 "parser/parser.y"
                                                { (yyval.node) = create_array_access_node((yyvsp[-3].node), (yyvsp[-1].node), create_location((yyloc))); }
#line 2529 "parser/parser.tab.c"
    break;

  case 97: /* variable: variable DOT fieldid  */
#line 384 "parser/parser.y"
                         { (yyval.node) = create_record_access_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2535 "parser/parser.tab.c"
    break;

  case 98: /* variable: variable CARET  */
#line 385 "parser/parser.y"
                   { (yyval.node) = create_pointer_deref_node((yyvsp[-1].node), create_location((yyloc))); }
#line 2541 "parser/parser.tab.c"
    break;

  case 99: /* subscript_list: expression  */
#line 388 "parser/parser.y"
               { 
        (yyval.node) = create_subscript_list_node((yyvsp[0].node), create_location((yyloc))); 
    }
#line 2549 "parser/parser.tab.c"
    break;

  case 100: /* subscript_list: subscript_list COMMA expression  */
#line 391 "parser/parser.y"
                                    { 
        (yyval.node) = append_subscript_list_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2557 "parser/parser.tab.c"
    break;

  case 101: /* case_list: case_item  */
#line 396 "parser/parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 2563 "parser/parser.tab.c"
    break;

  case 102: /* case_list: case_list SEMICOLON case_item  */
#line 397 "parser/parser.y"
                                  { 
      (yyval.node) = append_case_item((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2571 "parser/parser.tab.c"
    break;

  case 103: /* case_item: case_label_list COLON statement  */
#line 402 "parser/parser.y"
                                    { 
      (yyval.node) = create_case_item_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2579 "parser/parser.tab.c"
    break;

  case 104: /* case_label_list: case_label  */
#line 407 "parser/parser.y"
               { (yyval.node) = create_case_label_list((yyvsp[0].node), create_location((yyloc))); }
#line 2585 "parser/parser.tab.c"
    break;

  case 105: /* case_label_list: case_label_list COMMA case_label  */
#line 408 "parser/parser.y"
                                     { 
      (yyval.node) = append_case_label_list((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2593 "parser/parser.tab.c"
    break;

  case 106: /* case_label: constant  */
#line 413 "parser/parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 2599 "parser/parser.tab.c"
    break;

  case 107: /* case_label: constant DOTDOT constant  */
#line 414 "parser/parser.y"
                             { 
      (yyval.node) = create_constant_range_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2607 "parser/parser.tab.c"
    break;

  case 108: /* case_else: ELSE statement SEMICOLON  */
#line 419 "parser/parser.y"
                             {
      (yyval.node) = create_case_else_node((yyvsp[-1].node), create_location((yyloc)));
    }
#line 2615 "parser/parser.tab.c"
    break;

  case 109: /* for_list: expression TO expression  */
#line 424 "parser/parser.y"
                             { 
      (yyval.node) = create_for_list_node((yyvsp[-2].node), (yyvsp[0].node), false, create_location((yyloc))); 
    }
#line 2623 "parser/parser.tab.c"
    break;

  case 110: /* for_list: expression DOWNTO expression  */
#line 427 "parser/parser.y"
                                 { 
      (yyval.node) = create_for_list_node((yyvsp[-2].node), (yyvsp[0].node), true, create_location((yyloc))); 
    }
#line 2631 "parser/parser.tab.c"
    break;

  case 111: /* expression_list: expression  */
#line 433 "parser/parser.y"
               { (yyval.node) = create_expression_list(NULL, (yyvsp[0].node), create_location((yyloc))); }
#line 2637 "parser/parser.tab.c"
    break;

  case 112: /* expression_list: expression_list COMMA expression  */
#line 434 "parser/parser.y"
                                     { (yyval.node) = append_expression_list((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2643 "parser/parser.tab.c"
    break;

  case 113: /* label: unsigned_integer  */
#line 437 "parser/parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 2649 "parser/parser.tab.c"
    break;

  case 114: /* record_variable_list: variable  */
#line 440 "parser/parser.y"
             { (yyval.node) = create_record_variable_list_node((yyvsp[0].node), create_location((yyloc))); }
#line 2655 "parser/parser.tab.c"
    break;

  case 115: /* record_variable_list: record_variable_list COMMA variable  */
#line 441 "parser/parser.y"
                                        { 
      (yyval.node) = append_record_variable_list((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2663 "parser/parser.tab.c"
    break;

  case 116: /* expression: expression relational_op additive_expression  */
#line 446 "parser/parser.y"
                                                  { (yyval.node) = create_expression((yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2669 "parser/parser.tab.c"
    break;

  case 117: /* expression: additive_expression  */
#line 447 "parser/parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 2675 "parser/parser.tab.c"
    break;

  case 118: /* relational_op: LT  */
#line 450 "parser/parser.y"
       { (yyval.node) = create_relational_op("<", create_location((yyloc))); }
#line 2681 "parser/parser.tab.c"
    break;

  case 119: /* relational_op: LTE  */
#line 451 "parser/parser.y"
        { (yyval.node) = create_relational_op("<=", create_location((yyloc))); }
#line 2687 "parser/parser.tab.c"
    break;

  case 120: /* relational_op: EQ  */
#line 452 "parser/parser.y"
       { (yyval.node) = create_relational_op("=", create_location((yyloc))); }
#line 2693 "parser/parser.tab.c"
    break;

  case 121: /* relational_op: NEQ  */
#line 453 "parser/parser.y"
        { (yyval.node) = create_relational_op("<>", create_location((yyloc))); }
#line 2699 "parser/parser.tab.c"
    break;

  case 122: /* relational_op: GTE  */
#line 454 "parser/parser.y"
        { (yyval.node) = create_relational_op(">=", create_location((yyloc))); }
#line 2705 "parser/parser.tab.c"
    break;

  case 123: /* relational_op: GT  */
#line 455 "parser/parser.y"
       { (yyval.node) = create_relational_op(">", create_location((yyloc))); }
#line 2711 "parser/parser.tab.c"
    break;

  case 124: /* additive_expression: additive_expression additive_op multiplicative_expression  */
#line 458 "parser/parser.y"
                                                              { (yyval.node) = create_additive_expression((yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2717 "parser/parser.tab.c"
    break;

  case 125: /* additive_expression: multiplicative_expression  */
#line 459 "parser/parser.y"
                              { (yyval.node) = (yyvsp[0].node); }
#line 2723 "parser/parser.tab.c"
    break;

  case 126: /* additive_op: PLUS  */
#line 462 "parser/parser.y"
         { (yyval.node) = create_additive_op("+", create_location((yyloc))); }
#line 2729 "parser/parser.tab.c"
    break;

  case 127: /* additive_op: MINUS  */
#line 463 "parser/parser.y"
          { (yyval.node) = create_additive_op("-", create_location((yyloc))); }
#line 2735 "parser/parser.tab.c"
    break;

  case 128: /* additive_op: OR  */
#line 464 "parser/parser.y"
       { (yyval.node) = create_additive_op("or", create_location((yyloc))); }
#line 2741 "parser/parser.tab.c"
    break;

  case 129: /* multiplicative_expression: multiplicative_expression multiplicative_op unary_expression  */
#line 467 "parser/parser.y"
                                                                 { (yyval.node) = create_multiplicative_expression((yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2747 "parser/parser.tab.c"
    break;

  case 130: /* multiplicative_expression: unary_expression  */
#line 468 "parser/parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2753 "parser/parser.tab.c"
    break;

  case 131: /* multiplicative_op: TIMES  */
#line 471 "parser/parser.y"
          { (yyval.node) = create_multiplicative_node("*", create_location((yyloc))); }
#line 2759 "parser/parser.tab.c"
    break;

  case 132: /* multiplicative_op: DIVIDE  */
#line 472 "parser/parser.y"
           { (yyval.node) = create_multiplicative_node("/", create_location((yyloc))); }
#line 2765 "parser/parser.tab.c"
    break;

  case 133: /* multiplicative_op: DIV  */
#line 473 "parser/parser.y"
        { (yyval.node) = create_multiplicative_node("div", create_location((yyloc))); }
#line 2771 "parser/parser.tab.c"
    break;

  case 134: /* multiplicative_op: MOD  */
#line 474 "parser/parser.y"
        { (yyval.node) = create_multiplicative_node("mod", create_location((yyloc))); }
#line 2777 "parser/parser.tab.c"
    break;

  case 135: /* multiplicative_op: AND  */
#line 475 "parser/parser.y"
        { (yyval.node) = create_multiplicative_node("and", create_location((yyloc))); }
#line 2783 "parser/parser.tab.c"
    break;

  case 136: /* multiplicative_op: IN  */
#line 476 "parser/parser.y"
       { (yyval.node) = create_multiplicative_node("in", create_location((yyloc))); }
#line 2789 "parser/parser.tab.c"
    break;

  case 137: /* unary_expression: unary_op unary_expression  */
#line 479 "parser/parser.y"
                              { (yyval.node) = create_unary_expression((yyvsp[-1].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2795 "parser/parser.tab.c"
    break;

  case 138: /* unary_expression: primary_expression  */
#line 480 "parser/parser.y"
                       { (yyval.node) = (yyvsp[0].node); }
#line 2801 "parser/parser.tab.c"
    break;

  case 139: /* unary_op: PLUS  */
#line 483 "parser/parser.y"
         { (yyval.node) = create_unary_node("+", 0, create_location((yyloc))); }
#line 2807 "parser/parser.tab.c"
    break;

  case 140: /* unary_op: MINUS  */
#line 484 "parser/parser.y"
                    { (yyval.node) = create_unary_node("-", 1, create_location((yyloc))); }
#line 2813 "parser/parser.tab.c"
    break;

  case 141: /* unary_op: NOT  */
#line 485 "parser/parser.y"
                  { (yyval.node) = create_unary_node("!", 1, create_location((yyloc))); }
#line 2819 "parser/parser.tab.c"
    break;

  case 142: /* primary_expression: variable  */
#line 488 "parser/parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 2825 "parser/parser.tab.c"
    break;

  case 143: /* primary_expression: unsigned_integer  */
#line 489 "parser/parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2831 "parser/parser.tab.c"
    break;

  case 144: /* primary_expression: unsigned_real  */
#line 490 "parser/parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 2837 "parser/parser.tab.c"
    break;

  case 145: /* primary_expression: string_literal  */
#line 491 "parser/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 2843 "parser/parser.tab.c"
    break;

  case 146: /* primary_expression: NIL  */
#line 492 "parser/parser.y"
        {
      (yyval.node) = create_nil_literal(create_location((yyloc)));
    }
#line 2851 "parser/parser.tab.c"
    break;

  case 147: /* primary_expression: funcid L_PAREN expression_list R_PAREN  */
#line 495 "parser/parser.y"
                                           {
      (yyval.node) = create_function_call_node((yyvsp[-3].node), (yyvsp[-1].node), create_location((yyloc)));
    }
#line 2859 "parser/parser.tab.c"
    break;

  case 148: /* primary_expression: L_BRACKET element_list R_BRACKET  */
#line 498 "parser/parser.y"
                                     { (yyval.node) = (yyvsp[-1].node); }
#line 2865 "parser/parser.tab.c"
    break;

  case 149: /* primary_expression: L_PAREN expression R_PAREN  */
#line 499 "parser/parser.y"
                               { (yyval.node) = (yyvsp[-1].node); }
#line 2871 "parser/parser.tab.c"
    break;

  case 151: /* element_list: element  */
#line 503 "parser/parser.y"
            { (yyval.node) = create_element_list(NULL, (yyvsp[0].node), create_location((yyloc))); }
#line 2877 "parser/parser.tab.c"
    break;

  case 152: /* element_list: element_list COMMA element  */
#line 504 "parser/parser.y"
                               {
      (yyval.node) = append_element_list((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2885 "parser/parser.tab.c"
    break;

  case 153: /* element: expression  */
#line 509 "parser/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 2891 "parser/parser.tab.c"
    break;

  case 154: /* element: expression DOTDOT expression  */
#line 510 "parser/parser.y"
                                  {
      (yyval.node) = create_expression_range_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2899 "parser/parser.tab.c"
    break;

  case 155: /* constid: identifier  */
#line 515 "parser/parser.y"
               {
      (yyval.node) = update_identifier_node_kind((yyvsp[0].node), SYMBOL_CONSTANT, true);
   }
#line 2907 "parser/parser.tab.c"
    break;

  case 156: /* typeid: CHAR  */
#line 520 "parser/parser.y"
         { (yyval.node) = create_builtin_type_identifier("char", create_location((yyloc))); }
#line 2913 "parser/parser.tab.c"
    break;

  case 157: /* typeid: BOOLEAN  */
#line 521 "parser/parser.y"
            { (yyval.node) = create_builtin_type_identifier("boolean", create_location((yyloc))); }
#line 2919 "parser/parser.tab.c"
    break;

  case 158: /* typeid: INTEGER  */
#line 522 "parser/parser.y"
            { (yyval.node) = create_builtin_type_identifier("integer", create_location((yyloc))); }
#line 2925 "parser/parser.tab.c"
    break;

  case 159: /* typeid: REAL  */
#line 523 "parser/parser.y"
         { (yyval.node) = create_builtin_type_identifier("real", create_location((yyloc))); }
#line 2931 "parser/parser.tab.c"
    break;

  case 160: /* typeid: STRING  */
#line 524 "parser/parser.y"
           { (yyval.node) = create_builtin_type_identifier("string", create_location((yyloc))); }
#line 2937 "parser/parser.tab.c"
    break;

  case 161: /* typeid: identifier  */
#line 525 "parser/parser.y"
               {
      ASTNode *typeId = update_identifier_node_kind((yyvsp[0].node), SYMBOL_TYPE, true);
      (yyval.node) = create_type_identifier(typeId, create_location((yyloc)));
    }
#line 2946 "parser/parser.tab.c"
    break;

  case 162: /* funcid: identifier  */
#line 531 "parser/parser.y"
              { 
    (yyval.node) = update_identifier_node_kind((yyvsp[0].node), SYMBOL_FUNCTION, true);
  }
#line 2954 "parser/parser.tab.c"
    break;

  case 163: /* procid: identifier  */
#line 536 "parser/parser.y"
             { 
    (yyval.node) = update_identifier_node_kind((yyvsp[0].node), SYMBOL_PROCEDURE, true);
  }
#line 2962 "parser/parser.tab.c"
    break;

  case 164: /* procid: WRITE  */
#line 539 "parser/parser.y"
          { (yyval.node) = create_builtin_identifier("write", create_location((yyloc))); }
#line 2968 "parser/parser.tab.c"
    break;

  case 165: /* procid: WRITELN  */
#line 540 "parser/parser.y"
            { (yyval.node) = create_builtin_identifier("writeln", create_location((yyloc))); }
#line 2974 "parser/parser.tab.c"
    break;

  case 166: /* procid: READ  */
#line 541 "parser/parser.y"
         { (yyval.node) = create_builtin_identifier("read", create_location((yyloc))); }
#line 2980 "parser/parser.tab.c"
    break;

  case 167: /* procid: READLN  */
#line 542 "parser/parser.y"
           { (yyval.node) = create_builtin_identifier("readln", create_location((yyloc))); }
#line 2986 "parser/parser.tab.c"
    break;

  case 168: /* fieldid: identifier  */
#line 545 "parser/parser.y"
             { 
    (yyval.node) = update_identifier_node_kind((yyvsp[0].node), SYMBOL_FIELD, true);
  }
#line 2994 "parser/parser.tab.c"
    break;

  case 169: /* varid: identifier  */
#line 550 "parser/parser.y"
             {
    (yyval.node) = update_identifier_node_kind((yyvsp[0].node), SYMBOL_VARIABLE, true);
  }
#line 3002 "parser/parser.tab.c"
    break;

  case 170: /* identifier: IDENTIFIER  */
#line 555 "parser/parser.y"
              { (yyval.node) = create_identifier_node((yyvsp[0].string), create_location((yyloc))); }
#line 3008 "parser/parser.tab.c"
    break;

  case 171: /* unsigned_integer: INTEGER_LITERAL  */
#line 558 "parser/parser.y"
                    {
      (yyval.node) = create_unsigned_integer_node((yyvsp[0].integer), create_location((yyloc)));
    }
#line 3016 "parser/parser.tab.c"
    break;

  case 172: /* unsigned_real: REAL_LITERAL  */
#line 563 "parser/parser.y"
                 {
      (yyval.node) = create_unsigned_real_node((yyvsp[0].number), create_location((yyloc)));
    }
#line 3024 "parser/parser.tab.c"
    break;

  case 173: /* integer_literal: INTEGER_LITERAL  */
#line 568 "parser/parser.y"
                    {
      (yyval.node) = create_integer_literal((yyvsp[0].integer), create_location((yyloc)));
    }
#line 3032 "parser/parser.tab.c"
    break;

  case 174: /* real_literal: REAL_LITERAL  */
#line 573 "parser/parser.y"
                 {
      (yyval.node) = create_real_literal((yyvsp[0].number), create_location((yyloc)));
    }
#line 3040 "parser/parser.tab.c"
    break;

  case 175: /* string_literal: STRING_LITERAL  */
#line 578 "parser/parser.y"
                   {
      (yyval.node) = create_string_literal((yyvsp[0].string), create_location((yyloc)));
    }
#line 3048 "parser/parser.tab.c"
    break;

  case 176: /* empty: %empty  */
#line 592 "parser/parser.y"
       { (yyval.node) = NULL; }
#line 3054 "parser/parser.tab.c"
    break;


#line 3058 "parser/parser.tab.c"

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

