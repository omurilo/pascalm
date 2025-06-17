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
#include "../code-generation/code.h"

ASTNode *root = NULL;
extern int scopes;
extern ht *HashTable;

#line 84 "parser/parser.tab.c"

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
  YYSYMBOL_unpacked_structured_type = 99,  /* unpacked_structured_type  */
  YYSYMBOL_index_list = 100,               /* index_list  */
  YYSYMBOL_field_list = 101,               /* field_list  */
  YYSYMBOL_fixed_part = 102,               /* fixed_part  */
  YYSYMBOL_record_field = 103,             /* record_field  */
  YYSYMBOL_fieldid_list = 104,             /* fieldid_list  */
  YYSYMBOL_variant_part = 105,             /* variant_part  */
  YYSYMBOL_tag_field = 106,                /* tag_field  */
  YYSYMBOL_variant_list = 107,             /* variant_list  */
  YYSYMBOL_variant = 108,                  /* variant  */
  YYSYMBOL_proc_and_func_declaration = 109, /* proc_and_func_declaration  */
  YYSYMBOL_proc_or_func = 110,             /* proc_or_func  */
  YYSYMBOL_block_or_forward = 111,         /* block_or_forward  */
  YYSYMBOL_parameters = 112,               /* parameters  */
  YYSYMBOL_formal_parameter_list = 113,    /* formal_parameter_list  */
  YYSYMBOL_formal_parameter_section = 114, /* formal_parameter_section  */
  YYSYMBOL_parameterid_list = 115,         /* parameterid_list  */
  YYSYMBOL_statement_list = 116,           /* statement_list  */
  YYSYMBOL_statement = 117,                /* statement  */
  YYSYMBOL_variable = 118,                 /* variable  */
  YYSYMBOL_subscript_list = 119,           /* subscript_list  */
  YYSYMBOL_case_list = 120,                /* case_list  */
  YYSYMBOL_case_item = 121,                /* case_item  */
  YYSYMBOL_case_label_list = 122,          /* case_label_list  */
  YYSYMBOL_case_label = 123,               /* case_label  */
  YYSYMBOL_case_else = 124,                /* case_else  */
  YYSYMBOL_for_list = 125,                 /* for_list  */
  YYSYMBOL_expression_list = 126,          /* expression_list  */
  YYSYMBOL_label = 127,                    /* label  */
  YYSYMBOL_record_variable_list = 128,     /* record_variable_list  */
  YYSYMBOL_expression = 129,               /* expression  */
  YYSYMBOL_additive_expression = 130,      /* additive_expression  */
  YYSYMBOL_multiplicative_expression = 131, /* multiplicative_expression  */
  YYSYMBOL_unary_expression = 132,         /* unary_expression  */
  YYSYMBOL_primary_expression = 133,       /* primary_expression  */
  YYSYMBOL_element_list = 134,             /* element_list  */
  YYSYMBOL_element_list_non_empty = 135,   /* element_list_non_empty  */
  YYSYMBOL_element = 136,                  /* element  */
  YYSYMBOL_constid = 137,                  /* constid  */
  YYSYMBOL_typeid = 138,                   /* typeid  */
  YYSYMBOL_funcid = 139,                   /* funcid  */
  YYSYMBOL_procid = 140,                   /* procid  */
  YYSYMBOL_fieldid = 141,                  /* fieldid  */
  YYSYMBOL_varid = 142,                    /* varid  */
  YYSYMBOL_identifier = 143,               /* identifier  */
  YYSYMBOL_unsigned_integer = 144,         /* unsigned_integer  */
  YYSYMBOL_unsigned_real = 145,            /* unsigned_real  */
  YYSYMBOL_integer_literal = 146,          /* integer_literal  */
  YYSYMBOL_real_literal = 147,             /* real_literal  */
  YYSYMBOL_string_literal = 148,           /* string_literal  */
  YYSYMBOL_char_literal = 149,             /* char_literal  */
  YYSYMBOL_empty = 150                     /* empty  */
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
#define YYLAST   569

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  80
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  71
/* YYNRULES -- Number of rules.  */
#define YYNRULES  177
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  353

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
       0,   139,   139,   146,   149,   152,   155,   160,   161,   166,
     167,   172,   173,   178,   179,   184,   185,   190,   195,   196,
     201,   204,   209,   210,   215,   216,   221,   222,   227,   230,
     233,   236,   237,   238,   241,   244,   247,   252,   253,   256,
     261,   264,   269,   272,   275,   278,   281,   286,   289,   294,
     295,   296,   299,   300,   303,   304,   307,   308,   311,   314,
     315,   318,   319,   324,   325,   330,   331,   336,   339,   344,
     345,   348,   351,   352,   357,   360,   363,   367,   373,   374,
     379,   380,   383,   384,   385,   386,   387,   388,   389,   390,
     391,   392,   393,   394,   395,   396,   397,   400,   401,   402,
     403,   406,   409,   414,   415,   420,   425,   426,   431,   432,
     437,   442,   445,   450,   451,   454,   457,   458,   463,   466,
     469,   472,   475,   478,   481,   484,   487,   490,   493,   496,
     499,   502,   505,   508,   511,   514,   517,   520,   523,   526,
     529,   530,   531,   532,   533,   534,   537,   540,   541,   544,
     547,   552,   555,   560,   563,   568,   573,   574,   575,   576,
     577,   578,   584,   589,   592,   593,   594,   595,   598,   603,
     608,   611,   616,   621,   626,   631,   636,   645
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
  "unpacked_structured_type", "index_list", "field_list", "fixed_part",
  "record_field", "fieldid_list", "variant_part", "tag_field",
  "variant_list", "variant", "proc_and_func_declaration", "proc_or_func",
  "block_or_forward", "parameters", "formal_parameter_list",
  "formal_parameter_section", "parameterid_list", "statement_list",
  "statement", "variable", "subscript_list", "case_list", "case_item",
  "case_label_list", "case_label", "case_else", "for_list",
  "expression_list", "label", "record_variable_list", "expression",
  "additive_expression", "multiplicative_expression", "unary_expression",
  "primary_expression", "element_list", "element_list_non_empty",
  "element", "constid", "typeid", "funcid", "procid", "fieldid", "varid",
  "identifier", "unsigned_integer", "unsigned_real", "integer_literal",
  "real_literal", "string_literal", "char_literal", "empty", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-310)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-170)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      36,   -33,    66,     4,  -310,     2,    11,  -310,  -310,    28,
    -310,   547,     2,  -310,     2,     2,    96,    25,   122,     2,
     373,    34,  -310,  -310,  -310,  -310,  -310,   -40,    42,    51,
      82,   106,  -310,  -310,    20,  -310,   135,  -310,  -310,  -310,
    -310,  -310,  -310,   137,  -310,  -310,  -310,  -310,  -310,  -310,
    -310,   143,  -310,   143,  -310,   373,   355,     2,   355,     2,
     373,   355,    25,    -9,  -310,    54,   134,   150,  -310,   160,
    -310,  -310,  -310,   331,    25,    21,    55,    26,   109,     2,
     402,   245,   402,    24,   138,   155,     8,  -310,   355,   355,
     355,   355,   355,  -310,  -310,  -310,    40,   159,    72,   133,
    -310,  -310,   162,   173,  -310,  -310,  -310,  -310,    40,   -11,
    -310,   451,   187,    -1,   413,  -310,  -310,   373,     2,  -310,
     355,   355,   373,   355,  -310,  -310,  -310,   212,  -310,   216,
    -310,   161,  -310,  -310,  -310,   220,   189,    14,   238,   240,
       2,     2,    96,     2,  -310,  -310,   214,  -310,  -310,  -310,
    -310,  -310,  -310,   223,  -310,  -310,  -310,  -310,  -310,     2,
       2,     2,   -23,  -310,   167,  -310,   533,    96,  -310,  -310,
    -310,  -310,   483,   489,   201,   225,  -310,  -310,   373,   355,
     355,   355,   355,   355,   355,   355,   355,   355,   355,   355,
     355,   355,   355,   355,   355,   373,     2,   373,   355,   355,
     245,  -310,  -310,  -310,   516,   -15,   516,  -310,    88,   516,
     245,   402,   402,  -310,   438,    96,   271,   228,  -310,   178,
    -310,  -310,  -310,   438,   402,  -310,  -310,  -310,    89,   245,
     183,   143,   143,    24,  -310,     2,    96,  -310,  -310,  -310,
     233,  -310,   355,  -310,   355,   281,    72,    72,    72,    72,
      72,    72,   133,   133,   133,  -310,  -310,  -310,  -310,  -310,
    -310,   112,  -310,    40,  -310,   283,   477,   516,   246,     9,
    -310,   213,  -310,   355,  -310,   355,  -310,  -310,  -310,  -310,
    -310,    32,   279,  -310,   247,  -310,    14,     2,   402,  -310,
    -310,  -310,  -310,    96,  -310,   248,  -310,  -310,  -310,   533,
     516,  -310,   373,  -310,   373,   355,   355,   245,  -310,   164,
     245,   373,   516,   516,   438,   295,   245,    96,  -310,  -310,
    -310,  -310,  -310,    96,  -310,  -310,  -310,   516,   516,  -310,
     373,  -310,   312,  -310,  -310,  -310,   402,   263,  -310,   215,
    -310,  -310,  -310,   264,  -310,  -310,   245,   265,  -310,  -310,
      14,   262,  -310
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,   177,     1,     0,     0,     4,   170,     0,
       5,     0,     0,     3,     0,     0,     0,     0,     0,     0,
     177,     0,     7,     9,    11,    13,    15,     0,     0,     0,
       0,     0,    65,     6,     0,    26,     0,   155,   158,   159,
     157,   156,   160,     0,   161,   171,    18,   166,   164,   167,
     165,     0,   163,     0,   162,   177,     0,     0,     0,     0,
     177,     0,     0,     0,    80,     0,     0,    92,    97,   163,
     115,    82,     2,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   145,     0,     0,
       0,     0,   177,   176,   172,   175,   140,     0,   124,   128,
     135,   139,     0,   169,   141,   142,   143,   144,   116,     0,
     169,     0,     0,     0,     0,    94,    17,   177,     0,   100,
       0,     0,   177,     0,     8,    19,    10,     0,    12,     0,
      14,     0,    16,    66,    27,     0,     0,   177,     0,    45,
       0,     0,     0,     0,   173,   174,     0,    24,    34,    35,
      40,    31,    39,   161,    28,    29,    30,    20,    22,     0,
       0,     0,     0,    72,     0,    78,     0,     0,    84,   138,
     136,   137,     0,   153,     0,   150,   151,   149,   177,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   177,     0,   177,     0,     0,
       0,    81,    99,   168,    83,     0,   101,    96,     0,   113,
       0,     0,     0,    41,     0,     0,     0,    49,    52,     0,
      51,    56,    54,     0,     0,    32,    33,    36,     0,     0,
       0,     0,     0,     0,    71,     0,     0,    70,    69,    67,
       0,   148,     0,   147,     0,    85,   123,   122,   118,   119,
     121,   120,   127,   125,   126,   133,   129,   130,   131,   132,
     134,     0,    95,   117,    89,     0,     0,    90,   108,     0,
     103,     0,   106,     0,    98,     0,    93,    21,    23,    25,
      47,     0,     0,    59,   161,    43,   177,     0,     0,    44,
      46,    37,    38,     0,    76,     0,    73,    79,    74,     0,
     154,   152,   177,   146,   177,     0,     0,     0,    87,     0,
       0,   177,   102,   114,     0,     0,   177,     0,    53,    50,
      57,    55,    75,     0,    68,    86,    91,   111,   112,   109,
     177,   104,     0,   107,   105,    48,     0,    58,    61,     0,
      63,    60,    77,     0,    88,    42,   177,     0,   110,    62,
     177,     0,    64
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -310,  -310,  -310,   199,   321,   272,   277,   270,   276,   284,
    -310,  -310,  -310,  -310,   278,   -58,   -56,  -208,  -310,   226,
    -310,    13,  -310,    79,  -310,    81,  -310,  -310,    22,  -310,
     291,    73,   -52,  -310,   141,   217,     1,   176,    47,  -310,
    -310,    69,  -309,    65,  -310,  -310,   185,   318,  -310,   210,
     385,     5,   -44,  -310,  -310,  -310,   140,    -4,    33,   362,
     364,  -114,   328,    -2,   -12,  -310,  -310,  -310,    50,  -310,
      -3
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     2,     6,     9,   238,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    34,   146,   147,   148,   149,   150,
     281,   216,   217,   218,   219,   220,   282,   337,   338,    31,
      32,   239,    84,   162,   163,   164,    63,    64,    96,   205,
     269,   270,   271,   272,   332,   265,   208,    66,   109,   173,
      98,    99,   100,   101,   174,   175,   176,   151,   152,   102,
      67,   221,    68,   103,   104,   105,   154,   155,   106,   107,
      71
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
       7,    85,   116,    10,   202,    46,   280,   339,    70,   195,
      33,    36,    35,    37,    44,   289,    52,    54,    69,   168,
     308,    73,    74,   157,   199,    14,   158,    16,   159,    18,
      19,    20,   160,   161,    18,    19,    20,   339,   233,     1,
     215,     3,   234,    70,   169,   170,   171,   273,    70,    43,
      70,   196,   117,    69,   274,   110,    86,   110,    69,    14,
     117,   113,   125,    18,    19,    20,     4,    65,     5,   117,
     309,   127,    11,    37,    44,    35,     8,   134,   153,    37,
     153,   165,    79,    80,    38,    39,    40,    41,     8,   177,
      12,    72,    42,    13,   314,     8,    45,   118,     8,   119,
       8,   315,    65,    75,   108,    70,   335,    65,   121,   129,
      70,   118,    76,   119,   120,    69,   203,    18,    19,    20,
      69,   185,   121,   186,   187,    38,    39,    40,    41,     8,
     156,   156,   156,    42,   222,   203,   225,   226,    37,    37,
      44,    10,   268,    77,   255,   256,   257,   258,   259,   260,
     275,    12,   277,   276,   291,   278,   279,   165,   231,   232,
      47,    48,    49,    50,    65,    44,    70,    78,   290,    65,
       8,   292,   178,   320,   275,   227,    69,   303,   330,   294,
     295,   188,    81,    70,    82,    70,   189,   190,   191,   192,
     252,   253,   254,    69,   110,    69,     8,   122,    37,   166,
     240,   179,   180,   181,   182,   183,   184,    83,    37,   153,
     153,   193,   153,   284,   123,   140,   141,  -169,   167,  -169,
    -169,   153,   153,    79,   212,    65,   194,    37,  -169,   235,
     236,   165,   321,   297,    44,   144,   145,  -162,     8,    95,
     287,   288,    65,   263,    65,   235,   293,   198,   283,   329,
     156,   268,   268,   136,   137,   138,   139,   214,   268,   210,
     156,   156,   156,   211,   156,   223,    97,   224,   111,   298,
     243,   114,   229,   156,   156,   310,   311,   310,   347,   156,
     345,  -155,   285,   222,   203,   203,   153,   244,   268,   286,
      70,    44,    70,   201,   299,   302,   140,   141,   207,    70,
      69,   172,    69,   304,   307,    37,   316,    37,    37,    69,
     317,   323,   153,   340,    37,    44,   144,   145,    70,     8,
      95,    44,   336,   344,   346,   348,   322,   352,    69,   350,
     204,   206,    21,   209,   153,    14,    15,    16,   156,    18,
      19,    20,   228,   340,    37,   124,   128,   222,   203,    65,
     341,    65,   126,   130,   245,   131,   342,   156,    65,   156,
     156,   213,   132,   351,   156,   318,   156,   319,   349,   133,
      87,   262,   324,   264,   296,   333,   230,    65,   331,   261,
     115,    53,    51,    55,   301,    56,   156,   112,     0,    57,
       0,     0,    58,     0,    59,     0,   156,    60,     0,    61,
       0,    62,     0,     0,   209,    88,    89,    90,   266,   267,
       0,    47,    48,    49,    50,     0,     0,     0,     0,    91,
     135,     0,     0,    92,     0,    93,    45,    94,     0,     8,
      95,    38,    39,    40,    41,   136,   137,   138,   139,    42,
     200,     0,     0,     0,    45,     0,     0,     8,     0,     0,
       0,     0,   300,   140,   141,   179,   180,   181,   182,   183,
     184,   142,     0,     0,     0,     0,   143,    38,    39,    40,
      41,   197,     0,   144,   145,    42,     8,    95,   325,     0,
     326,     0,     0,   312,     0,   313,     0,   334,     0,   140,
     141,     0,     0,   179,   180,   181,   182,   183,   184,   305,
     306,     0,   143,     0,     0,     0,   343,     0,     0,   144,
     145,     0,     8,    95,     0,   327,   328,     0,     0,   179,
     180,   181,   182,   183,   184,   179,   180,   181,   182,   183,
     184,   179,   180,   181,   182,   183,   184,    14,    15,    16,
      17,    18,    19,    20,     0,     0,     0,   242,   241,     0,
     237,    14,    15,    16,    17,    18,    19,    20,   179,   180,
     181,   182,   183,   184,   246,   247,   248,   249,   250,   251
};

static const yytype_int16 yycheck[] =
{
       3,    53,    11,     5,   118,    17,   214,   316,    20,    20,
      12,    15,    14,    15,    16,   223,    18,    19,    20,    11,
      11,    61,    62,    81,    25,     4,    82,     6,     4,     8,
       9,    10,     8,     9,     8,     9,    10,   346,    61,     3,
      26,    74,    65,    55,    88,    89,    90,    62,    60,    16,
      62,    62,    61,    55,    69,    57,    55,    59,    60,     4,
      61,    60,    74,     8,     9,    10,     0,    20,    64,    61,
      61,    75,    61,    75,    76,    77,    74,    79,    80,    81,
      82,    83,    62,    63,    29,    30,    31,    32,    74,    92,
      62,    57,    37,    65,    62,    74,    71,    57,    74,    59,
      74,    69,    55,    61,    57,   117,   314,    60,    68,    76,
     122,    57,    61,    59,    60,   117,   118,     8,     9,    10,
     122,    49,    68,    51,    52,    29,    30,    31,    32,    74,
      80,    81,    82,    37,   137,   137,   140,   141,   140,   141,
     142,   143,   200,    61,   188,   189,   190,   191,   192,   193,
      62,    62,   210,    65,    65,   211,   212,   159,   160,   161,
      38,    39,    40,    41,   117,   167,   178,    61,   224,   122,
      74,   229,    13,   287,    62,   142,   178,    65,    14,   231,
     232,    48,    47,   195,    47,   197,    53,    54,    55,    56,
     185,   186,   187,   195,   196,   197,    74,    63,   200,    61,
     167,    42,    43,    44,    45,    46,    47,    64,   210,   211,
     212,    78,   214,   215,    64,    51,    52,    57,    63,    59,
      60,   223,   224,    62,    63,   178,    64,   229,    68,    62,
      63,   233,   288,   235,   236,    71,    72,    64,    74,    75,
      62,    63,   195,   196,   197,    62,    63,    60,   215,   307,
     200,   309,   310,    33,    34,    35,    36,    68,   316,    47,
     210,   211,   212,    47,   214,    27,    56,    27,    58,   236,
      69,    61,    58,   223,   224,    62,    63,    62,    63,   229,
     336,    58,    11,   286,   286,   287,   288,    62,   346,    61,
     302,   293,   304,   117,    61,    14,    51,    52,   122,   311,
     302,    91,   304,    20,    58,   307,    27,   309,   310,   311,
      63,    63,   314,   316,   316,   317,    71,    72,   330,    74,
      75,   323,    27,    11,    61,    61,   293,    65,   330,    64,
     120,   121,    11,   123,   336,     4,     5,     6,   288,     8,
       9,    10,   143,   346,   346,    73,    76,   350,   350,   302,
     317,   304,    75,    77,   178,    77,   323,   307,   311,   309,
     310,   135,    78,   350,   314,   286,   316,   286,   346,    78,
      15,   195,   299,   197,   233,   310,   159,   330,   309,   194,
      62,    19,    18,    10,   244,    12,   336,    59,    -1,    16,
      -1,    -1,    19,    -1,    21,    -1,   346,    24,    -1,    26,
      -1,    28,    -1,    -1,   194,    50,    51,    52,   198,   199,
      -1,    38,    39,    40,    41,    -1,    -1,    -1,    -1,    64,
      18,    -1,    -1,    68,    -1,    70,    71,    72,    -1,    74,
      75,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      27,    -1,    -1,    -1,    71,    -1,    -1,    74,    -1,    -1,
      -1,    -1,   242,    51,    52,    42,    43,    44,    45,    46,
      47,    59,    -1,    -1,    -1,    -1,    64,    29,    30,    31,
      32,    20,    -1,    71,    72,    37,    74,    75,   302,    -1,
     304,    -1,    -1,   273,    -1,   275,    -1,   311,    -1,    51,
      52,    -1,    -1,    42,    43,    44,    45,    46,    47,    22,
      23,    -1,    64,    -1,    -1,    -1,   330,    -1,    -1,    71,
      72,    -1,    74,    75,    -1,   305,   306,    -1,    -1,    42,
      43,    44,    45,    46,    47,    42,    43,    44,    45,    46,
      47,    42,    43,    44,    45,    46,    47,     4,     5,     6,
       7,     8,     9,    10,    -1,    -1,    -1,    58,    65,    -1,
      17,     4,     5,     6,     7,     8,     9,    10,    42,    43,
      44,    45,    46,    47,   179,   180,   181,   182,   183,   184
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    81,    74,     0,    64,    82,   150,    74,    83,
     143,    61,    62,    65,     4,     5,     6,     7,     8,     9,
      10,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,   109,   110,   143,    94,   143,   137,   143,    29,    30,
      31,    32,    37,   138,   143,    71,   144,    38,    39,    40,
      41,   140,   143,   139,   143,    10,    12,    16,    19,    21,
      24,    26,    28,   116,   117,   118,   127,   140,   142,   143,
     144,   150,    57,    61,    62,    61,    61,    61,    61,    62,
      63,    47,    47,    64,   112,   112,   116,    15,    50,    51,
      52,    64,    68,    70,    72,    75,   118,   129,   130,   131,
     132,   133,   139,   143,   144,   145,   148,   149,   118,   128,
     143,   129,   142,   116,   129,   127,    11,    61,    57,    59,
      60,    68,    63,    64,    85,   144,    86,   137,    87,   138,
      88,    94,    89,   110,   143,    18,    33,    34,    35,    36,
      51,    52,    59,    64,    71,    72,    95,    96,    97,    98,
      99,   137,   138,   143,   146,   147,   148,    95,    96,     4,
       8,     9,   113,   114,   115,   143,    61,    63,    11,   132,
     132,   132,   129,   129,   134,   135,   136,   150,    13,    42,
      43,    44,    45,    46,    47,    49,    51,    52,    48,    53,
      54,    55,    56,    78,    64,    20,    62,    20,    60,    25,
      27,   117,   141,   143,   129,   119,   129,   117,   126,   129,
      47,    47,    63,    99,    68,    26,   101,   102,   103,   104,
     105,   141,   150,    27,    27,   137,   137,   138,    83,    58,
     115,   143,   143,    61,    65,    62,    63,    17,    84,   111,
     138,    65,    58,    69,    62,   117,   130,   130,   130,   130,
     130,   130,   131,   131,   131,   132,   132,   132,   132,   132,
     132,   126,   117,   118,   117,   125,   129,   129,    95,   120,
     121,   122,   123,    62,    69,    62,    65,    95,    96,    96,
      97,   100,   106,   138,   143,    11,    61,    62,    63,    97,
      96,    65,    95,    63,   112,   112,   114,   143,   138,    61,
     129,   136,    14,    65,    20,    22,    23,    58,    11,    61,
      62,    63,   129,   129,    62,    69,    27,    63,   103,   105,
     141,    96,   138,    63,   111,   117,   117,   129,   129,    95,
      14,   121,   124,   123,   117,    97,    27,   107,   108,   122,
     150,   138,   138,   117,    11,    96,    61,    63,    61,   108,
      64,   101,    65
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    80,    81,    82,    82,    83,    83,    84,    84,    85,
      85,    86,    86,    87,    87,    88,    88,    89,    90,    90,
      91,    91,    92,    92,    93,    93,    94,    94,    95,    95,
      95,    95,    95,    95,    96,    96,    96,    97,    97,    97,
      98,    98,    99,    99,    99,    99,    99,   100,   100,   101,
     101,   101,   102,   102,   103,   103,   104,   104,   105,   106,
     106,   107,   107,   108,   108,   109,   109,   110,   110,   111,
     111,   112,   113,   113,   114,   114,   114,   114,   115,   115,
     116,   116,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   118,   118,   118,
     118,   119,   119,   120,   120,   121,   122,   122,   123,   123,
     124,   125,   125,   126,   126,   127,   128,   128,   129,   129,
     129,   129,   129,   129,   129,   130,   130,   130,   130,   131,
     131,   131,   131,   131,   131,   131,   132,   132,   132,   132,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   134,
     134,   135,   135,   136,   136,   137,   138,   138,   138,   138,
     138,   138,   139,   140,   140,   140,   140,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     6,     3,     1,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     3,     2,     3,
       4,     5,     4,     5,     4,     5,     1,     3,     1,     1,
       1,     1,     2,     2,     1,     1,     2,     3,     3,     1,
       1,     2,     6,     3,     3,     1,     3,     1,     3,     1,
       3,     1,     1,     3,     1,     3,     1,     3,     4,     1,
       3,     1,     3,     1,     5,     1,     3,     5,     7,     1,
       1,     3,     1,     3,     3,     4,     3,     5,     1,     3,
       1,     3,     1,     3,     3,     4,     6,     5,     7,     4,
       4,     6,     1,     4,     2,     4,     3,     1,     4,     3,
       2,     1,     3,     1,     3,     3,     1,     3,     1,     3,
       3,     3,     3,     1,     3,     1,     1,     3,     3,     3,
       3,     3,     3,     3,     1,     3,     3,     3,     1,     3,
       3,     3,     3,     3,     3,     1,     2,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     4,     3,     3,     1,
       1,     1,     3,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0
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
#line 139 "parser/parser.y"
                                                             {
      (yyval.node) = create_program_node((yyvsp[-4].string), (yyvsp[-3].node), (yyvsp[-1].node), create_location((yyloc)));
      root = (yyval.node);
      root->code_gen = create_code_generator("../output.c");
    }
#line 1921 "parser/parser.tab.c"
    break;

  case 3: /* program_headingopt: L_PAREN identifier_list R_PAREN  */
#line 146 "parser/parser.y"
                                    {
      (yyval.node) = create_heading_node((yyvsp[-1].node), create_location((yyloc)));
    }
#line 1929 "parser/parser.tab.c"
    break;

  case 5: /* identifier_list: identifier  */
#line 152 "parser/parser.y"
               {
      (yyval.node) = create_identifier_list_node((yyvsp[0].node), create_location((yyloc)));
    }
#line 1937 "parser/parser.tab.c"
    break;

  case 6: /* identifier_list: identifier_list COMMA identifier  */
#line 155 "parser/parser.y"
                                     {
      (yyval.node) = append_identifier_list_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 1945 "parser/parser.tab.c"
    break;

  case 7: /* block: block1  */
#line 160 "parser/parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 1951 "parser/parser.tab.c"
    break;

  case 8: /* block: label_declaration SEMICOLON block1  */
#line 161 "parser/parser.y"
                                       {
      (yyval.node) = add_labels_to_block((yyvsp[0].node), (yyvsp[-2].node));
    }
#line 1959 "parser/parser.tab.c"
    break;

  case 9: /* block1: block2  */
#line 166 "parser/parser.y"
            { (yyval.node) = (yyvsp[0].node); }
#line 1965 "parser/parser.tab.c"
    break;

  case 10: /* block1: constant_declaration SEMICOLON block2  */
#line 167 "parser/parser.y"
                                          {
    (yyval.node) = add_constants_to_block((yyvsp[0].node), (yyvsp[-2].node));
  }
#line 1973 "parser/parser.tab.c"
    break;

  case 11: /* block2: block3  */
#line 172 "parser/parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 1979 "parser/parser.tab.c"
    break;

  case 12: /* block2: type_declaration SEMICOLON block3  */
#line 173 "parser/parser.y"
                                      {
     (yyval.node) = add_types_to_block((yyvsp[0].node), (yyvsp[-2].node));
  }
#line 1987 "parser/parser.tab.c"
    break;

  case 13: /* block3: block4  */
#line 178 "parser/parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 1993 "parser/parser.tab.c"
    break;

  case 14: /* block3: variable_declaration SEMICOLON block4  */
#line 179 "parser/parser.y"
                                          {
      (yyval.node) = add_variables_to_block((yyvsp[0].node), (yyvsp[-2].node));
    }
#line 2001 "parser/parser.tab.c"
    break;

  case 15: /* block4: block5  */
#line 184 "parser/parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 2007 "parser/parser.tab.c"
    break;

  case 16: /* block4: proc_and_func_declaration SEMICOLON block5  */
#line 185 "parser/parser.y"
                                               {
      (yyval.node) = add_procs_funcs_to_block((yyvsp[0].node), (yyvsp[-2].node));
    }
#line 2015 "parser/parser.tab.c"
    break;

  case 17: /* block5: BEGIN_TOK statement_list END  */
#line 190 "parser/parser.y"
                                 {
      (yyval.node) = create_block_node(NULL, NULL, NULL, NULL, NULL, (yyvsp[-1].node), create_location((yyloc)));
    }
#line 2023 "parser/parser.tab.c"
    break;

  case 18: /* label_declaration: LABEL unsigned_integer  */
#line 195 "parser/parser.y"
                           { (yyval.node) = create_label_declaration_node((yyvsp[0].node), create_location((yyloc))); }
#line 2029 "parser/parser.tab.c"
    break;

  case 19: /* label_declaration: label_declaration COMMA unsigned_integer  */
#line 196 "parser/parser.y"
                                             {
      (yyval.node) = append_label_declaration((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2037 "parser/parser.tab.c"
    break;

  case 20: /* constant_declaration: CONST constid EQ constant  */
#line 201 "parser/parser.y"
                              {
      (yyval.node) = create_constant_declaration_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2045 "parser/parser.tab.c"
    break;

  case 21: /* constant_declaration: constant_declaration SEMICOLON constid EQ constant  */
#line 204 "parser/parser.y"
                                                       {
      (yyval.node) = append_constant_declaration((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2053 "parser/parser.tab.c"
    break;

  case 22: /* type_declaration: TYPE typeid EQ type  */
#line 209 "parser/parser.y"
                        { (yyval.node) = create_type_declaration_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2059 "parser/parser.tab.c"
    break;

  case 23: /* type_declaration: type_declaration SEMICOLON typeid EQ type  */
#line 210 "parser/parser.y"
                                              {
      (yyval.node) = append_type_declaration((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2067 "parser/parser.tab.c"
    break;

  case 24: /* variable_declaration: VAR variableid_list COLON type  */
#line 215 "parser/parser.y"
                                   { (yyval.node) = create_variable_declaration_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2073 "parser/parser.tab.c"
    break;

  case 25: /* variable_declaration: variable_declaration SEMICOLON variableid_list COLON type  */
#line 216 "parser/parser.y"
                                                              {
      (yyval.node) = append_variable_declaration((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2081 "parser/parser.tab.c"
    break;

  case 26: /* variableid_list: identifier  */
#line 221 "parser/parser.y"
                { (yyval.node) = create_variable_identifier_list_node((yyvsp[0].node), create_location((yyloc))); }
#line 2087 "parser/parser.tab.c"
    break;

  case 27: /* variableid_list: variableid_list COMMA identifier  */
#line 222 "parser/parser.y"
                                     {
      (yyval.node) = append_variable_identifier_list((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2095 "parser/parser.tab.c"
    break;

  case 28: /* constant: integer_literal  */
#line 227 "parser/parser.y"
                    {
      (yyval.node) = create_constant_literal((yyvsp[0].node), create_location((yyloc)));
    }
#line 2103 "parser/parser.tab.c"
    break;

  case 29: /* constant: real_literal  */
#line 230 "parser/parser.y"
                 {
      (yyval.node) = create_constant_literal((yyvsp[0].node), create_location((yyloc)));
    }
#line 2111 "parser/parser.tab.c"
    break;

  case 30: /* constant: string_literal  */
#line 233 "parser/parser.y"
                   {
      (yyval.node) = create_constant_literal((yyvsp[0].node), create_location((yyloc)));
    }
#line 2119 "parser/parser.tab.c"
    break;

  case 31: /* constant: constid  */
#line 236 "parser/parser.y"
            { (yyval.node) = create_constant_identifier((yyvsp[0].node), create_location((yyloc))); }
#line 2125 "parser/parser.tab.c"
    break;

  case 32: /* constant: PLUS constid  */
#line 237 "parser/parser.y"
                 { (yyval.node) = create_constant_signed_identifier((yyvsp[0].node), "+", create_location((yyloc))); }
#line 2131 "parser/parser.tab.c"
    break;

  case 33: /* constant: MINUS constid  */
#line 238 "parser/parser.y"
                  { (yyval.node) = create_constant_signed_identifier((yyvsp[0].node), "-", create_location((yyloc))); }
#line 2137 "parser/parser.tab.c"
    break;

  case 34: /* type: simple_type  */
#line 241 "parser/parser.y"
                {
      (yyval.node) = create_simple_type_node((yyvsp[0].node), create_location((yyloc)));
    }
#line 2145 "parser/parser.tab.c"
    break;

  case 35: /* type: structured_type  */
#line 244 "parser/parser.y"
                    {
      (yyval.node) = create_structure_type_node((yyvsp[0].node), create_location((yyloc)));
    }
#line 2153 "parser/parser.tab.c"
    break;

  case 36: /* type: CARET typeid  */
#line 247 "parser/parser.y"
                 {
      (yyval.node) = create_pointer_type_node((yyvsp[0].node), create_location((yyloc)));
    }
#line 2161 "parser/parser.tab.c"
    break;

  case 37: /* simple_type: L_PAREN identifier_list R_PAREN  */
#line 252 "parser/parser.y"
                                     { (yyval.node) = create_enumerated_type_node((yyvsp[-1].node), create_location((yyloc))); }
#line 2167 "parser/parser.tab.c"
    break;

  case 38: /* simple_type: constant DOTDOT constant  */
#line 253 "parser/parser.y"
                             {
      (yyval.node) = create_constant_range_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2175 "parser/parser.tab.c"
    break;

  case 39: /* simple_type: typeid  */
#line 256 "parser/parser.y"
           {
      (yyval.node) = (yyvsp[0].node);
    }
#line 2183 "parser/parser.tab.c"
    break;

  case 40: /* structured_type: unpacked_structured_type  */
#line 261 "parser/parser.y"
                             {
      (yyval.node) = (yyvsp[0].node);
    }
#line 2191 "parser/parser.tab.c"
    break;

  case 41: /* structured_type: PACKED unpacked_structured_type  */
#line 264 "parser/parser.y"
                                      {
      (yyval.node) = create_packed_type((yyvsp[0].node), create_location((yyloc)));
    }
#line 2199 "parser/parser.tab.c"
    break;

  case 42: /* unpacked_structured_type: ARRAY L_BRACKET index_list R_BRACKET OF type  */
#line 269 "parser/parser.y"
                                                   {
        (yyval.node) = create_array_type_node((yyvsp[-3].node), (yyvsp[0].node), create_location((yyloc)));
      }
#line 2207 "parser/parser.tab.c"
    break;

  case 43: /* unpacked_structured_type: RECORD field_list END  */
#line 272 "parser/parser.y"
                            {
        (yyval.node) = create_record_type_node((yyvsp[-1].node), create_location((yyloc)));
      }
#line 2215 "parser/parser.tab.c"
    break;

  case 44: /* unpacked_structured_type: SET OF simple_type  */
#line 275 "parser/parser.y"
                         {
        (yyval.node) = create_set_of_type_node((yyvsp[0].node), create_location((yyloc)));
      }
#line 2223 "parser/parser.tab.c"
    break;

  case 45: /* unpacked_structured_type: FILE_TOK  */
#line 278 "parser/parser.y"
               {
        (yyval.node) = create_file_of_type_node(NULL, create_location((yyloc)));
      }
#line 2231 "parser/parser.tab.c"
    break;

  case 46: /* unpacked_structured_type: FILE_TOK OF type  */
#line 281 "parser/parser.y"
                       {
        (yyval.node) = create_file_of_type_node((yyvsp[0].node), create_location((yyloc)));
      }
#line 2239 "parser/parser.tab.c"
    break;

  case 47: /* index_list: simple_type  */
#line 286 "parser/parser.y"
                { 
      (yyval.node) = create_index_list_start((yyvsp[0].node), create_location((yyloc))); 
    }
#line 2247 "parser/parser.tab.c"
    break;

  case 48: /* index_list: index_list COMMA simple_type  */
#line 289 "parser/parser.y"
                                 {
      (yyval.node) = append_index_to_list((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2255 "parser/parser.tab.c"
    break;

  case 49: /* field_list: fixed_part  */
#line 294 "parser/parser.y"
               { (yyval.node) = create_field_list((yyvsp[0].node), NULL, create_location((yyloc))); }
#line 2261 "parser/parser.tab.c"
    break;

  case 50: /* field_list: fixed_part SEMICOLON variant_part  */
#line 295 "parser/parser.y"
                                      { (yyval.node) = create_field_list((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2267 "parser/parser.tab.c"
    break;

  case 51: /* field_list: variant_part  */
#line 296 "parser/parser.y"
                 { (yyval.node) = create_field_list(NULL, (yyvsp[0].node), create_location((yyloc))); }
#line 2273 "parser/parser.tab.c"
    break;

  case 52: /* fixed_part: record_field  */
#line 299 "parser/parser.y"
                 { (yyval.node) = create_fixed_part_node(NULL, (yyvsp[0].node), create_location((yyloc))); }
#line 2279 "parser/parser.tab.c"
    break;

  case 53: /* fixed_part: fixed_part SEMICOLON record_field  */
#line 300 "parser/parser.y"
                                      { (yyval.node) = create_fixed_part_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2285 "parser/parser.tab.c"
    break;

  case 55: /* record_field: fieldid_list COLON type  */
#line 304 "parser/parser.y"
                            { (yyval.node) = create_record_field_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2291 "parser/parser.tab.c"
    break;

  case 56: /* fieldid_list: fieldid  */
#line 307 "parser/parser.y"
            { (yyval.node) = create_field_identifier_list_node(NULL, (yyvsp[0].node), create_location((yyloc))); }
#line 2297 "parser/parser.tab.c"
    break;

  case 57: /* fieldid_list: fieldid_list COMMA fieldid  */
#line 308 "parser/parser.y"
                               { (yyval.node) = create_field_identifier_list_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2303 "parser/parser.tab.c"
    break;

  case 58: /* variant_part: CASE tag_field OF variant_list  */
#line 311 "parser/parser.y"
                                   { (yyval.node) = create_case_of_variant_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2309 "parser/parser.tab.c"
    break;

  case 59: /* tag_field: typeid  */
#line 314 "parser/parser.y"
           { (yyval.node) = create_tag_field_node(NULL, (yyvsp[0].node), create_location((yyloc))); }
#line 2315 "parser/parser.tab.c"
    break;

  case 60: /* tag_field: identifier COLON typeid  */
#line 315 "parser/parser.y"
                            { (yyval.node) = create_tag_field_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2321 "parser/parser.tab.c"
    break;

  case 61: /* variant_list: variant  */
#line 318 "parser/parser.y"
            { (yyval.node) = append_variant_list(NULL, (yyvsp[0].node), create_location((yyloc))); }
#line 2327 "parser/parser.tab.c"
    break;

  case 62: /* variant_list: variant_list SEMICOLON variant  */
#line 319 "parser/parser.y"
                                   {
      (yyval.node) = append_variant_list((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2335 "parser/parser.tab.c"
    break;

  case 64: /* variant: case_label_list COLON L_PAREN field_list R_PAREN  */
#line 325 "parser/parser.y"
                                                     {
      (yyval.node) = create_variant_node((yyvsp[-4].node), (yyvsp[-1].node), create_location((yyloc)));
    }
#line 2343 "parser/parser.tab.c"
    break;

  case 65: /* proc_and_func_declaration: proc_or_func  */
#line 330 "parser/parser.y"
                 { (yyval.node) = create_proc_and_func_declarations_node((yyvsp[0].node), create_location((yyloc))); }
#line 2349 "parser/parser.tab.c"
    break;

  case 66: /* proc_and_func_declaration: proc_and_func_declaration SEMICOLON proc_or_func  */
#line 331 "parser/parser.y"
                                                     {
      (yyval.node) = append_proc_and_func_declarations((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2357 "parser/parser.tab.c"
    break;

  case 67: /* proc_or_func: PROCEDURE procid parameters SEMICOLON block_or_forward  */
#line 336 "parser/parser.y"
                                                           { /* identifier of func/proc declaration */ 
      (yyval.node) = create_proc_declaration_node((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2365 "parser/parser.tab.c"
    break;

  case 68: /* proc_or_func: FUNCTION funcid parameters COLON typeid SEMICOLON block_or_forward  */
#line 339 "parser/parser.y"
                                                                       {
      (yyval.node) = create_func_declaration_node((yyvsp[-5].node), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2373 "parser/parser.tab.c"
    break;

  case 69: /* block_or_forward: block  */
#line 344 "parser/parser.y"
          { (yyval.node) = (yyvsp[0].node); }
#line 2379 "parser/parser.tab.c"
    break;

  case 70: /* block_or_forward: FORWARD  */
#line 345 "parser/parser.y"
             { (yyval.node) = create_forward_declaration_node(create_location((yyloc))); }
#line 2385 "parser/parser.tab.c"
    break;

  case 71: /* parameters: L_PAREN formal_parameter_list R_PAREN  */
#line 348 "parser/parser.y"
                                         { (yyval.node) = create_parameters_node((yyvsp[-1].node), create_location((yyloc))); }
#line 2391 "parser/parser.tab.c"
    break;

  case 72: /* formal_parameter_list: formal_parameter_section  */
#line 351 "parser/parser.y"
                             { (yyval.node) = create_formal_parameters_list_node(NULL, (yyvsp[0].node), create_location((yyloc))); }
#line 2397 "parser/parser.tab.c"
    break;

  case 73: /* formal_parameter_list: formal_parameter_list SEMICOLON formal_parameter_section  */
#line 352 "parser/parser.y"
                                                             {
      (yyval.node) = create_formal_parameters_list_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2405 "parser/parser.tab.c"
    break;

  case 74: /* formal_parameter_section: parameterid_list COLON typeid  */
#line 357 "parser/parser.y"
                                  { 
        (yyval.node) = create_formal_parameter_section_node(PARAM_VALUE, (yyvsp[-2].node), (yyvsp[0].node), NULL, NULL, create_location((yyloc))); 
      }
#line 2413 "parser/parser.tab.c"
    break;

  case 75: /* formal_parameter_section: VAR parameterid_list COLON typeid  */
#line 360 "parser/parser.y"
                                        { 
        (yyval.node) = create_formal_parameter_section_node(PARAM_VAR, (yyvsp[-2].node), (yyvsp[0].node), NULL, NULL, create_location((yyloc))); 
      }
#line 2421 "parser/parser.tab.c"
    break;

  case 76: /* formal_parameter_section: PROCEDURE identifier parameters  */
#line 363 "parser/parser.y"
                                      { 
        ASTNode* single_id = create_parameter_identifier_list_node(NULL, (yyvsp[-1].node), create_location((yylsp[-1])));
        (yyval.node) = create_formal_parameter_section_node(PARAM_PROCEDURE, single_id, NULL, (yyvsp[0].node), NULL, create_location((yyloc))); 
      }
#line 2430 "parser/parser.tab.c"
    break;

  case 77: /* formal_parameter_section: FUNCTION identifier parameters COLON typeid  */
#line 367 "parser/parser.y"
                                                  { 
        ASTNode* single_id = create_parameter_identifier_list_node(NULL, (yyvsp[-3].node), create_location((yylsp[-3])));
        (yyval.node) = create_formal_parameter_section_node(PARAM_FUNCTION, single_id, NULL, (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); 
      }
#line 2439 "parser/parser.tab.c"
    break;

  case 78: /* parameterid_list: identifier  */
#line 373 "parser/parser.y"
                { (yyval.node) = create_parameter_identifier_list_node(NULL, (yyvsp[0].node), create_location((yyloc))); }
#line 2445 "parser/parser.tab.c"
    break;

  case 79: /* parameterid_list: parameterid_list COMMA identifier  */
#line 374 "parser/parser.y"
                                       { 
      (yyval.node) = create_parameter_identifier_list_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2453 "parser/parser.tab.c"
    break;

  case 80: /* statement_list: statement  */
#line 379 "parser/parser.y"
              { (yyval.node) = create_stmt_list_node((yyvsp[0].node), create_location((yyloc))); }
#line 2459 "parser/parser.tab.c"
    break;

  case 81: /* statement_list: statement_list SEMICOLON statement  */
#line 380 "parser/parser.y"
                                       { (yyval.node) = append_stmt_list((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2465 "parser/parser.tab.c"
    break;

  case 83: /* statement: variable ASSIGN expression  */
#line 384 "parser/parser.y"
                               { (yyval.node) = create_assign_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2471 "parser/parser.tab.c"
    break;

  case 84: /* statement: BEGIN_TOK statement_list END  */
#line 385 "parser/parser.y"
                                  { (yyval.node) = create_stmt_list_node((yyvsp[-1].node), create_location((yyloc))); }
#line 2477 "parser/parser.tab.c"
    break;

  case 85: /* statement: IF expression THEN statement  */
#line 386 "parser/parser.y"
                                                       { (yyval.node) = create_if_stmt_node((yyvsp[-2].node), (yyvsp[0].node), NULL, create_location((yyloc))); }
#line 2483 "parser/parser.tab.c"
    break;

  case 86: /* statement: IF expression THEN statement ELSE statement  */
#line 387 "parser/parser.y"
                                                { (yyval.node) = create_if_stmt_node((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2489 "parser/parser.tab.c"
    break;

  case 87: /* statement: CASE expression OF case_list END  */
#line 388 "parser/parser.y"
                                     { (yyval.node) = create_case_stmt_node((yyvsp[-3].node), (yyvsp[-1].node), NULL, create_location((yyloc))); }
#line 2495 "parser/parser.tab.c"
    break;

  case 88: /* statement: CASE expression OF case_list SEMICOLON case_else END  */
#line 389 "parser/parser.y"
                                                         { (yyval.node) = create_case_stmt_with_else_node((yyvsp[-5].node), (yyvsp[-3].node), (yyvsp[-1].node), create_location((yyloc))); }
#line 2501 "parser/parser.tab.c"
    break;

  case 89: /* statement: WHILE expression DO statement  */
#line 390 "parser/parser.y"
                                  { (yyval.node) = create_while_stmt_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2507 "parser/parser.tab.c"
    break;

  case 90: /* statement: REPEAT statement_list UNTIL expression  */
#line 391 "parser/parser.y"
                                           { (yyval.node) = create_repeat_until_stmt_list_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2513 "parser/parser.tab.c"
    break;

  case 91: /* statement: FOR varid ASSIGN for_list DO statement  */
#line 392 "parser/parser.y"
                                           { (yyval.node) = create_for_stmt_node((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2519 "parser/parser.tab.c"
    break;

  case 92: /* statement: procid  */
#line 393 "parser/parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 2525 "parser/parser.tab.c"
    break;

  case 93: /* statement: procid L_PAREN expression_list R_PAREN  */
#line 394 "parser/parser.y"
                                           { (yyval.node) = create_procedure_call_node((yyvsp[-3].node), (yyvsp[-1].node), create_location((yyloc))); }
#line 2531 "parser/parser.tab.c"
    break;

  case 94: /* statement: GOTO label  */
#line 395 "parser/parser.y"
               { (yyval.node) = create_goto_label_node((yyvsp[0].node), create_location((yyloc))); }
#line 2537 "parser/parser.tab.c"
    break;

  case 95: /* statement: WITH record_variable_list DO statement  */
#line 396 "parser/parser.y"
                                           { (yyval.node) = create_with_record_list_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2543 "parser/parser.tab.c"
    break;

  case 96: /* statement: label COLON statement  */
#line 397 "parser/parser.y"
                          { (yyval.node) = create_label_stmt_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2549 "parser/parser.tab.c"
    break;

  case 97: /* variable: varid  */
#line 400 "parser/parser.y"
          { (yyval.node) = (yyvsp[0].node); }
#line 2555 "parser/parser.tab.c"
    break;

  case 98: /* variable: variable L_BRACKET subscript_list R_BRACKET  */
#line 401 "parser/parser.y"
                                                { (yyval.node) = create_array_access_node((yyvsp[-3].node), (yyvsp[-1].node), create_location((yyloc))); }
#line 2561 "parser/parser.tab.c"
    break;

  case 99: /* variable: variable DOT fieldid  */
#line 402 "parser/parser.y"
                         { (yyval.node) = create_record_access_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2567 "parser/parser.tab.c"
    break;

  case 100: /* variable: variable CARET  */
#line 403 "parser/parser.y"
                   { (yyval.node) = create_pointer_deref_node((yyvsp[-1].node), create_location((yyloc))); }
#line 2573 "parser/parser.tab.c"
    break;

  case 101: /* subscript_list: expression  */
#line 406 "parser/parser.y"
               { 
        (yyval.node) = create_subscript_list_node((yyvsp[0].node), create_location((yyloc))); 
    }
#line 2581 "parser/parser.tab.c"
    break;

  case 102: /* subscript_list: subscript_list COMMA expression  */
#line 409 "parser/parser.y"
                                    { 
        (yyval.node) = append_subscript_list_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2589 "parser/parser.tab.c"
    break;

  case 103: /* case_list: case_item  */
#line 414 "parser/parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 2595 "parser/parser.tab.c"
    break;

  case 104: /* case_list: case_list SEMICOLON case_item  */
#line 415 "parser/parser.y"
                                  { 
      (yyval.node) = append_case_item((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2603 "parser/parser.tab.c"
    break;

  case 105: /* case_item: case_label_list COLON statement  */
#line 420 "parser/parser.y"
                                    { 
      (yyval.node) = create_case_item_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2611 "parser/parser.tab.c"
    break;

  case 106: /* case_label_list: case_label  */
#line 425 "parser/parser.y"
               { (yyval.node) = create_case_label_list((yyvsp[0].node), create_location((yyloc))); }
#line 2617 "parser/parser.tab.c"
    break;

  case 107: /* case_label_list: case_label_list COMMA case_label  */
#line 426 "parser/parser.y"
                                     { 
      (yyval.node) = append_case_label_list((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2625 "parser/parser.tab.c"
    break;

  case 108: /* case_label: constant  */
#line 431 "parser/parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 2631 "parser/parser.tab.c"
    break;

  case 109: /* case_label: constant DOTDOT constant  */
#line 432 "parser/parser.y"
                             { 
      (yyval.node) = create_constant_range_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2639 "parser/parser.tab.c"
    break;

  case 110: /* case_else: ELSE statement SEMICOLON  */
#line 437 "parser/parser.y"
                             {
      (yyval.node) = create_case_else_node((yyvsp[-1].node), create_location((yyloc)));
    }
#line 2647 "parser/parser.tab.c"
    break;

  case 111: /* for_list: expression TO expression  */
#line 442 "parser/parser.y"
                             { 
      (yyval.node) = create_for_list_node((yyvsp[-2].node), (yyvsp[0].node), false, create_location((yyloc))); 
    }
#line 2655 "parser/parser.tab.c"
    break;

  case 112: /* for_list: expression DOWNTO expression  */
#line 445 "parser/parser.y"
                                 { 
      (yyval.node) = create_for_list_node((yyvsp[-2].node), (yyvsp[0].node), true, create_location((yyloc))); 
    }
#line 2663 "parser/parser.tab.c"
    break;

  case 113: /* expression_list: expression  */
#line 450 "parser/parser.y"
               { (yyval.node) = create_expression_list((yyvsp[0].node), create_location((yyloc))); }
#line 2669 "parser/parser.tab.c"
    break;

  case 114: /* expression_list: expression_list COMMA expression  */
#line 451 "parser/parser.y"
                                     { (yyval.node) = append_expression_list((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2675 "parser/parser.tab.c"
    break;

  case 115: /* label: unsigned_integer  */
#line 454 "parser/parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 2681 "parser/parser.tab.c"
    break;

  case 116: /* record_variable_list: variable  */
#line 457 "parser/parser.y"
             { (yyval.node) = create_record_variable_list_node((yyvsp[0].node), create_location((yyloc))); }
#line 2687 "parser/parser.tab.c"
    break;

  case 117: /* record_variable_list: record_variable_list COMMA variable  */
#line 458 "parser/parser.y"
                                        { 
      (yyval.node) = append_record_variable_list((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2695 "parser/parser.tab.c"
    break;

  case 118: /* expression: expression LT additive_expression  */
#line 463 "parser/parser.y"
                                      { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_LT, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2703 "parser/parser.tab.c"
    break;

  case 119: /* expression: expression LTE additive_expression  */
#line 466 "parser/parser.y"
                                       { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_LTE, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2711 "parser/parser.tab.c"
    break;

  case 120: /* expression: expression EQ additive_expression  */
#line 469 "parser/parser.y"
                                      { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_EQ, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2719 "parser/parser.tab.c"
    break;

  case 121: /* expression: expression NEQ additive_expression  */
#line 472 "parser/parser.y"
                                       { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_NEQ, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2727 "parser/parser.tab.c"
    break;

  case 122: /* expression: expression GTE additive_expression  */
#line 475 "parser/parser.y"
                                       { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_GTE, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2735 "parser/parser.tab.c"
    break;

  case 123: /* expression: expression GT additive_expression  */
#line 478 "parser/parser.y"
                                      { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_GT, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2743 "parser/parser.tab.c"
    break;

  case 124: /* expression: additive_expression  */
#line 481 "parser/parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 2749 "parser/parser.tab.c"
    break;

  case 125: /* additive_expression: additive_expression PLUS multiplicative_expression  */
#line 484 "parser/parser.y"
                                                       { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_PLUS, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2757 "parser/parser.tab.c"
    break;

  case 126: /* additive_expression: additive_expression MINUS multiplicative_expression  */
#line 487 "parser/parser.y"
                                                        { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_MINUS, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2765 "parser/parser.tab.c"
    break;

  case 127: /* additive_expression: additive_expression OR multiplicative_expression  */
#line 490 "parser/parser.y"
                                                     { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_OR, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2773 "parser/parser.tab.c"
    break;

  case 128: /* additive_expression: multiplicative_expression  */
#line 493 "parser/parser.y"
                              { (yyval.node) = (yyvsp[0].node); }
#line 2779 "parser/parser.tab.c"
    break;

  case 129: /* multiplicative_expression: multiplicative_expression TIMES unary_expression  */
#line 496 "parser/parser.y"
                                                     { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_TIMES, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2787 "parser/parser.tab.c"
    break;

  case 130: /* multiplicative_expression: multiplicative_expression DIVIDE unary_expression  */
#line 499 "parser/parser.y"
                                                      { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_DIVIDE, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2795 "parser/parser.tab.c"
    break;

  case 131: /* multiplicative_expression: multiplicative_expression DIV unary_expression  */
#line 502 "parser/parser.y"
                                                   { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_DIV, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2803 "parser/parser.tab.c"
    break;

  case 132: /* multiplicative_expression: multiplicative_expression MOD unary_expression  */
#line 505 "parser/parser.y"
                                                   { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_MOD, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2811 "parser/parser.tab.c"
    break;

  case 133: /* multiplicative_expression: multiplicative_expression AND unary_expression  */
#line 508 "parser/parser.y"
                                                   { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_AND, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2819 "parser/parser.tab.c"
    break;

  case 134: /* multiplicative_expression: multiplicative_expression IN unary_expression  */
#line 511 "parser/parser.y"
                                                  { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_IN, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2827 "parser/parser.tab.c"
    break;

  case 135: /* multiplicative_expression: unary_expression  */
#line 514 "parser/parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2833 "parser/parser.tab.c"
    break;

  case 136: /* unary_expression: PLUS unary_expression  */
#line 517 "parser/parser.y"
                          { 
      (yyval.node) = create_unary_expression(UNOP_PLUS, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2841 "parser/parser.tab.c"
    break;

  case 137: /* unary_expression: MINUS unary_expression  */
#line 520 "parser/parser.y"
                                     { 
      (yyval.node) = create_unary_expression(UNOP_MINUS, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2849 "parser/parser.tab.c"
    break;

  case 138: /* unary_expression: NOT unary_expression  */
#line 523 "parser/parser.y"
                                   { 
      (yyval.node) = create_unary_expression(UNOP_NOT, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2857 "parser/parser.tab.c"
    break;

  case 139: /* unary_expression: primary_expression  */
#line 526 "parser/parser.y"
                       { (yyval.node) = (yyvsp[0].node); }
#line 2863 "parser/parser.tab.c"
    break;

  case 140: /* primary_expression: variable  */
#line 529 "parser/parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 2869 "parser/parser.tab.c"
    break;

  case 141: /* primary_expression: unsigned_integer  */
#line 530 "parser/parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2875 "parser/parser.tab.c"
    break;

  case 142: /* primary_expression: unsigned_real  */
#line 531 "parser/parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 2881 "parser/parser.tab.c"
    break;

  case 143: /* primary_expression: string_literal  */
#line 532 "parser/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 2887 "parser/parser.tab.c"
    break;

  case 144: /* primary_expression: char_literal  */
#line 533 "parser/parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 2893 "parser/parser.tab.c"
    break;

  case 145: /* primary_expression: NIL  */
#line 534 "parser/parser.y"
        {
      (yyval.node) = create_nil_literal(create_location((yyloc)));
    }
#line 2901 "parser/parser.tab.c"
    break;

  case 146: /* primary_expression: funcid L_PAREN expression_list R_PAREN  */
#line 537 "parser/parser.y"
                                           {
      (yyval.node) = create_function_call_node((yyvsp[-3].node), (yyvsp[-1].node), create_location((yyloc)));
    }
#line 2909 "parser/parser.tab.c"
    break;

  case 147: /* primary_expression: L_BRACKET element_list R_BRACKET  */
#line 540 "parser/parser.y"
                                     { (yyval.node) = (yyvsp[-1].node); }
#line 2915 "parser/parser.tab.c"
    break;

  case 148: /* primary_expression: L_PAREN expression R_PAREN  */
#line 541 "parser/parser.y"
                               { (yyval.node) = (yyvsp[-1].node); }
#line 2921 "parser/parser.tab.c"
    break;

  case 149: /* element_list: empty  */
#line 544 "parser/parser.y"
          { 
      (yyval.node) = create_set_literal(create_location((yyloc))); 
    }
#line 2929 "parser/parser.tab.c"
    break;

  case 150: /* element_list: element_list_non_empty  */
#line 547 "parser/parser.y"
                           { 
      (yyval.node) = (yyvsp[0].node); 
    }
#line 2937 "parser/parser.tab.c"
    break;

  case 151: /* element_list_non_empty: element  */
#line 552 "parser/parser.y"
            { 
      (yyval.node) = create_set_literal_with_element((yyvsp[0].node), create_location((yyloc))); 
    }
#line 2945 "parser/parser.tab.c"
    break;

  case 152: /* element_list_non_empty: element_list_non_empty COMMA element  */
#line 555 "parser/parser.y"
                                         {
      (yyval.node) = add_element_to_set_literal((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2953 "parser/parser.tab.c"
    break;

  case 153: /* element: expression  */
#line 560 "parser/parser.y"
               { 
      (yyval.node) = create_set_element((yyvsp[0].node), create_location((yyloc))); 
    }
#line 2961 "parser/parser.tab.c"
    break;

  case 154: /* element: expression DOTDOT expression  */
#line 563 "parser/parser.y"
                                 {
      (yyval.node) = create_set_range_element((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2969 "parser/parser.tab.c"
    break;

  case 155: /* constid: identifier  */
#line 568 "parser/parser.y"
               {
      (yyval.node) = update_identifier_node_kind((yyvsp[0].node), SYMBOL_CONSTANT);
   }
#line 2977 "parser/parser.tab.c"
    break;

  case 156: /* typeid: CHAR  */
#line 573 "parser/parser.y"
         { (yyval.node) = create_builtin_type_identifier("char", create_location((yyloc))); }
#line 2983 "parser/parser.tab.c"
    break;

  case 157: /* typeid: BOOLEAN  */
#line 574 "parser/parser.y"
            { (yyval.node) = create_builtin_type_identifier("boolean", create_location((yyloc))); }
#line 2989 "parser/parser.tab.c"
    break;

  case 158: /* typeid: INTEGER  */
#line 575 "parser/parser.y"
            { (yyval.node) = create_builtin_type_identifier("integer", create_location((yyloc))); }
#line 2995 "parser/parser.tab.c"
    break;

  case 159: /* typeid: REAL  */
#line 576 "parser/parser.y"
         { (yyval.node) = create_builtin_type_identifier("real", create_location((yyloc))); }
#line 3001 "parser/parser.tab.c"
    break;

  case 160: /* typeid: STRING  */
#line 577 "parser/parser.y"
           { (yyval.node) = create_builtin_type_identifier("string", create_location((yyloc))); }
#line 3007 "parser/parser.tab.c"
    break;

  case 161: /* typeid: identifier  */
#line 578 "parser/parser.y"
               {
      ASTNode *typeId = update_identifier_node_kind((yyvsp[0].node), SYMBOL_TYPE);
      (yyval.node) = create_type_identifier(typeId, create_location((yyloc)));
    }
#line 3016 "parser/parser.tab.c"
    break;

  case 162: /* funcid: identifier  */
#line 584 "parser/parser.y"
              { 
    (yyval.node) = update_identifier_node_kind((yyvsp[0].node), SYMBOL_FUNCTION);
  }
#line 3024 "parser/parser.tab.c"
    break;

  case 163: /* procid: identifier  */
#line 589 "parser/parser.y"
             { 
    (yyval.node) = update_identifier_node_kind((yyvsp[0].node), SYMBOL_PROCEDURE);
  }
#line 3032 "parser/parser.tab.c"
    break;

  case 164: /* procid: WRITE  */
#line 592 "parser/parser.y"
          { (yyval.node) = create_builtin_identifier("write", create_location((yyloc))); }
#line 3038 "parser/parser.tab.c"
    break;

  case 165: /* procid: WRITELN  */
#line 593 "parser/parser.y"
            { (yyval.node) = create_builtin_identifier("writeln", create_location((yyloc))); }
#line 3044 "parser/parser.tab.c"
    break;

  case 166: /* procid: READ  */
#line 594 "parser/parser.y"
         { (yyval.node) = create_builtin_identifier("read", create_location((yyloc))); }
#line 3050 "parser/parser.tab.c"
    break;

  case 167: /* procid: READLN  */
#line 595 "parser/parser.y"
           { (yyval.node) = create_builtin_identifier("readln", create_location((yyloc))); }
#line 3056 "parser/parser.tab.c"
    break;

  case 168: /* fieldid: identifier  */
#line 598 "parser/parser.y"
             { 
    (yyval.node) = update_identifier_node_kind((yyvsp[0].node), SYMBOL_FIELD);
  }
#line 3064 "parser/parser.tab.c"
    break;

  case 169: /* varid: identifier  */
#line 603 "parser/parser.y"
             {
    (yyval.node) = update_identifier_node_kind((yyvsp[0].node), SYMBOL_VARIABLE);
  }
#line 3072 "parser/parser.tab.c"
    break;

  case 170: /* identifier: IDENTIFIER  */
#line 608 "parser/parser.y"
              { (yyval.node) = create_identifier_node((yyvsp[0].string), create_location((yyloc))); }
#line 3078 "parser/parser.tab.c"
    break;

  case 171: /* unsigned_integer: INTEGER_LITERAL  */
#line 611 "parser/parser.y"
                    {
      (yyval.node) = create_unsigned_integer_node((yyvsp[0].integer), create_location((yyloc)));
    }
#line 3086 "parser/parser.tab.c"
    break;

  case 172: /* unsigned_real: REAL_LITERAL  */
#line 616 "parser/parser.y"
                 {
      (yyval.node) = create_unsigned_real_node((yyvsp[0].number), create_location((yyloc)));
    }
#line 3094 "parser/parser.tab.c"
    break;

  case 173: /* integer_literal: INTEGER_LITERAL  */
#line 621 "parser/parser.y"
                    {
      (yyval.node) = create_integer_literal((yyvsp[0].integer), create_location((yyloc)));
    }
#line 3102 "parser/parser.tab.c"
    break;

  case 174: /* real_literal: REAL_LITERAL  */
#line 626 "parser/parser.y"
                 {
      (yyval.node) = create_real_literal((yyvsp[0].number), create_location((yyloc)));
    }
#line 3110 "parser/parser.tab.c"
    break;

  case 175: /* string_literal: STRING_LITERAL  */
#line 631 "parser/parser.y"
                   {
      (yyval.node) = create_string_literal((yyvsp[0].string), create_location((yyloc)));
    }
#line 3118 "parser/parser.tab.c"
    break;

  case 176: /* char_literal: CHAR_LITERAL  */
#line 636 "parser/parser.y"
                 {
      (yyval.node) = create_char_literal((yyvsp[0].character), create_location((yyloc)));
    }
#line 3126 "parser/parser.tab.c"
    break;

  case 177: /* empty: %empty  */
#line 645 "parser/parser.y"
       { (yyval.node) = NULL; }
#line 3132 "parser/parser.tab.c"
    break;


#line 3136 "parser/parser.tab.c"

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

