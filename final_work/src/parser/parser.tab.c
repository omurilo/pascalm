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
  YYSYMBOL_empty = 149                     /* empty  */
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
#define YYLAST   563

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  80
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  70
/* YYNRULES -- Number of rules.  */
#define YYNRULES  175
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  351

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
       0,   137,   137,   143,   146,   149,   152,   157,   158,   163,
     164,   169,   170,   175,   176,   181,   182,   187,   192,   193,
     198,   201,   206,   207,   212,   213,   218,   219,   224,   227,
     230,   233,   234,   235,   238,   241,   244,   249,   250,   253,
     258,   261,   266,   269,   272,   275,   278,   283,   286,   291,
     292,   293,   296,   297,   300,   301,   304,   305,   308,   311,
     312,   315,   316,   321,   322,   327,   328,   333,   336,   341,
     342,   345,   348,   349,   354,   357,   360,   364,   370,   371,
     376,   377,   380,   381,   382,   383,   384,   385,   386,   387,
     388,   389,   390,   391,   392,   393,   394,   397,   398,   399,
     400,   403,   406,   411,   412,   417,   422,   423,   428,   429,
     434,   439,   442,   447,   448,   451,   454,   455,   460,   463,
     466,   469,   472,   475,   478,   481,   484,   487,   490,   493,
     496,   499,   502,   505,   508,   511,   514,   517,   520,   523,
     526,   527,   528,   529,   530,   533,   536,   537,   540,   543,
     548,   551,   556,   559,   564,   569,   570,   571,   572,   573,
     574,   580,   585,   588,   589,   590,   591,   594,   599,   604,
     607,   612,   617,   622,   627,   641
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
  "real_literal", "string_literal", "empty", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-308)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-169)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       6,   -46,    51,    -4,  -308,    -9,     2,  -308,  -308,    29,
    -308,   547,    -9,  -308,    -9,    -9,    69,     1,   120,    -9,
     393,    25,  -308,  -308,  -308,  -308,  -308,    73,    79,    91,
     108,   114,  -308,  -308,   117,  -308,    39,  -308,  -308,  -308,
    -308,  -308,  -308,    43,  -308,  -308,  -308,  -308,  -308,  -308,
    -308,    48,  -308,    48,  -308,   393,   313,    -9,   313,    -9,
     393,   313,     1,    -5,  -308,    28,   122,   131,  -308,   129,
    -308,  -308,  -308,   250,     1,    23,   330,    36,   121,    -9,
     406,   417,   406,    31,   138,   127,     0,  -308,   313,   313,
     313,   313,   313,  -308,  -308,    58,   402,    19,    94,  -308,
    -308,   141,   152,  -308,  -308,  -308,    58,    21,  -308,   348,
      32,     5,   472,  -308,  -308,   393,    -9,  -308,   313,   313,
     393,   313,  -308,  -308,  -308,   156,  -308,   171,  -308,   159,
    -308,  -308,  -308,   230,   167,    10,   197,   216,    -9,    -9,
      69,    -9,  -308,  -308,   191,  -308,  -308,  -308,  -308,  -308,
    -308,   203,  -308,  -308,  -308,  -308,  -308,    -9,    -9,    -9,
     -23,  -308,   164,  -308,   533,    69,  -308,  -308,  -308,  -308,
     466,   478,   202,   213,  -308,  -308,   393,   313,   313,   313,
     313,   313,   313,   313,   313,   313,   313,   313,   313,   313,
     313,   313,   313,   393,    -9,   393,   313,   313,   417,  -308,
    -308,  -308,   502,   -15,   502,  -308,   103,   502,   417,   406,
     406,  -308,   422,    69,   266,   234,  -308,   176,  -308,  -308,
    -308,   422,   406,  -308,  -308,  -308,   139,   417,   190,    48,
      48,    31,  -308,    -9,    69,  -308,  -308,  -308,   235,  -308,
     313,  -308,   313,   278,    19,    19,    19,    19,    19,    19,
      94,    94,    94,  -308,  -308,  -308,  -308,  -308,  -308,   150,
    -308,    58,  -308,   279,   460,   502,   243,     8,  -308,   217,
    -308,   313,  -308,   313,  -308,  -308,  -308,  -308,  -308,   -10,
     275,  -308,   241,  -308,    10,    -9,   406,  -308,  -308,  -308,
    -308,    69,  -308,   245,  -308,  -308,  -308,   533,   502,  -308,
     393,  -308,   393,   313,   313,   417,  -308,   162,   417,   393,
     502,   502,   422,   282,   417,    69,  -308,  -308,  -308,  -308,
    -308,    69,  -308,  -308,  -308,   502,   502,  -308,   393,  -308,
     303,  -308,  -308,  -308,   406,   254,  -308,   231,  -308,  -308,
    -308,   256,  -308,  -308,   417,   257,  -308,  -308,    10,   255,
    -308
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,   175,     1,     0,     0,     4,   169,     0,
       5,     0,     0,     3,     0,     0,     0,     0,     0,     0,
     175,     0,     7,     9,    11,    13,    15,     0,     0,     0,
       0,     0,    65,     6,     0,    26,     0,   154,   157,   158,
     156,   155,   159,     0,   160,   170,    18,   165,   163,   166,
     164,     0,   162,     0,   161,   175,     0,     0,     0,     0,
     175,     0,     0,     0,    80,     0,     0,    92,    97,   162,
     115,    82,     2,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   144,     0,     0,
       0,     0,   175,   171,   174,   140,     0,   124,   128,   135,
     139,     0,   168,   141,   142,   143,   116,     0,   168,     0,
       0,     0,     0,    94,    17,   175,     0,   100,     0,     0,
     175,     0,     8,    19,    10,     0,    12,     0,    14,     0,
      16,    66,    27,     0,     0,   175,     0,    45,     0,     0,
       0,     0,   172,   173,     0,    24,    34,    35,    40,    31,
      39,   160,    28,    29,    30,    20,    22,     0,     0,     0,
       0,    72,     0,    78,     0,     0,    84,   138,   136,   137,
       0,   152,     0,   149,   150,   148,   175,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   175,     0,   175,     0,     0,     0,    81,
      99,   167,    83,     0,   101,    96,     0,   113,     0,     0,
       0,    41,     0,     0,     0,    49,    52,     0,    51,    56,
      54,     0,     0,    32,    33,    36,     0,     0,     0,     0,
       0,     0,    71,     0,     0,    70,    69,    67,     0,   147,
       0,   146,     0,    85,   123,   122,   118,   119,   121,   120,
     127,   125,   126,   133,   129,   130,   131,   132,   134,     0,
      95,   117,    89,     0,     0,    90,   108,     0,   103,     0,
     106,     0,    98,     0,    93,    21,    23,    25,    47,     0,
       0,    59,   160,    43,   175,     0,     0,    44,    46,    37,
      38,     0,    76,     0,    73,    79,    74,     0,   153,   151,
     175,   145,   175,     0,     0,     0,    87,     0,     0,   175,
     102,   114,     0,     0,   175,     0,    53,    50,    57,    55,
      75,     0,    68,    86,    91,   111,   112,   109,   175,   104,
       0,   107,   105,    48,     0,    58,    61,     0,    63,    60,
      77,     0,    88,    42,   175,     0,   110,    62,   175,     0,
      64
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -308,  -308,  -308,   184,   316,   258,   260,   253,   259,   252,
    -308,  -308,  -308,  -308,   267,   -57,   -56,  -187,  -308,   200,
    -308,     3,  -308,    53,  -308,    59,  -308,  -308,     9,  -308,
     274,    60,   -52,  -308,   124,   201,    56,  -100,    47,  -308,
    -308,    63,  -307,    65,  -308,  -308,   182,   317,  -308,   126,
     381,    85,   -67,  -308,  -308,  -308,   140,   -11,    33,   361,
     365,  -114,   327,    -2,   -12,  -308,  -308,  -308,    64,    -3
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     2,     6,     9,   236,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    34,   144,   145,   146,   147,   148,
     279,   214,   215,   216,   217,   218,   280,   335,   336,    31,
      32,   237,    84,   160,   161,   162,    63,    64,    95,   203,
     267,   268,   269,   270,   330,   263,   206,    66,   107,   171,
      97,    98,    99,   100,   172,   173,   174,   149,   150,   101,
      67,   219,    68,   102,   103,   104,   152,   153,   105,    71
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
       7,    85,   200,    10,    36,    46,   114,   337,    70,     1,
      33,   166,    35,    37,    44,   199,    52,    54,    69,   306,
     205,   167,   168,   169,   155,   278,   156,    14,     3,    16,
     197,    18,    19,    20,   287,   157,   213,   337,   231,   158,
     159,   193,   232,    70,    18,    19,    20,   271,    70,    43,
      70,     4,   312,    69,   272,   108,   115,   108,    69,   313,
       5,   115,   123,    11,   125,     8,   115,    65,   183,   307,
     184,   185,    45,    37,    44,    35,   243,   132,   151,    37,
     151,   163,    72,   194,     8,   116,    81,   117,   118,   175,
      82,    12,   196,   260,    13,   262,   119,     8,    38,    39,
      40,    41,    65,    70,   106,     8,    42,    65,    70,   127,
       8,    86,    83,    69,   201,   116,   111,   117,    69,   253,
     254,   255,   256,   257,   258,   333,   119,   223,   224,    18,
      19,    20,   220,   201,    73,    74,    37,    37,    44,    10,
      75,   266,   186,     8,   154,   154,   154,   187,   188,   189,
     190,   275,    76,   276,   277,   163,   229,   230,    47,    48,
      49,    50,    65,    44,    70,   273,   288,    65,   274,    77,
     290,   318,   191,   225,    69,    78,   328,   292,   293,    79,
      80,    70,    96,    70,   109,   120,  -168,   112,  -168,  -168,
     165,    69,   108,    69,     8,   121,    37,  -168,   238,   164,
     323,    12,   324,   208,   289,   192,    37,   151,   151,   332,
     151,   282,   273,   138,   139,   301,  -161,   170,   209,   151,
     151,    79,   210,    65,   221,    37,   233,   234,   341,   163,
     319,   295,    44,   142,   143,   212,     8,    94,   285,   286,
      65,   261,    65,   222,   202,   204,   281,   207,   327,   227,
     266,   266,   233,   291,    14,    15,    16,   266,    18,    19,
      20,  -154,   154,   134,   135,   136,   137,   296,   250,   251,
     252,   241,   154,   154,   154,   242,   154,   283,   343,   308,
     309,   220,   201,   201,   151,   154,   154,   266,    70,    44,
      70,   154,   300,   308,   345,   284,   297,    70,    69,   302,
      69,   305,   314,    37,   315,    37,    37,    69,   321,   334,
     151,   338,    37,    44,   342,   344,    70,   346,   207,    44,
     350,   348,   264,   265,   320,   226,    69,    21,    87,   126,
     130,   122,   151,   211,    14,   124,   128,   316,    18,    19,
      20,   338,    37,   317,   129,   220,   201,    65,   339,    65,
     154,   349,   131,   347,   340,   294,    65,   322,   228,    38,
      39,    40,    41,    88,    89,    90,   298,    42,   195,   154,
     329,   154,   154,   331,   259,    65,   154,    91,   154,   113,
      53,    92,   299,    51,    45,    93,   110,     8,    94,     0,
     177,   178,   179,   180,   181,   182,     0,   310,   154,   311,
       0,     0,     0,    55,     8,    56,     0,     0,   154,    57,
       0,     0,    58,     0,    59,   176,     0,    60,     0,    61,
       0,    62,     0,     0,   133,     0,     0,     0,     0,   325,
     326,    47,    48,    49,    50,    38,    39,    40,    41,   134,
     135,   136,   137,    42,   177,   178,   179,   180,   181,   182,
       0,    38,    39,    40,    41,     0,     0,   138,   139,    42,
       0,     0,     0,     0,    45,   140,     0,     8,   138,   139,
     141,     0,     0,   138,   139,     0,     0,   142,   143,     0,
       8,    94,   303,   304,     0,     0,   141,     0,   142,   143,
       0,     8,    94,   142,   143,     0,     8,    94,     0,   198,
       0,     0,   177,   178,   179,   180,   181,   182,   177,   178,
     179,   180,   181,   182,   177,   178,   179,   180,   181,   182,
     177,   178,   179,   180,   181,   182,     0,     0,     0,     0,
       0,   239,     0,     0,     0,     0,   240,    14,    15,    16,
      17,    18,    19,    20,   177,   178,   179,   180,   181,   182,
     235,    14,    15,    16,    17,    18,    19,    20,   244,   245,
     246,   247,   248,   249
};

static const yytype_int16 yycheck[] =
{
       3,    53,   116,     5,    15,    17,    11,   314,    20,     3,
      12,    11,    14,    15,    16,   115,    18,    19,    20,    11,
     120,    88,    89,    90,    81,   212,    82,     4,    74,     6,
      25,     8,     9,    10,   221,     4,    26,   344,    61,     8,
       9,    20,    65,    55,     8,     9,    10,    62,    60,    16,
      62,     0,    62,    55,    69,    57,    61,    59,    60,    69,
      64,    61,    74,    61,    75,    74,    61,    20,    49,    61,
      51,    52,    71,    75,    76,    77,   176,    79,    80,    81,
      82,    83,    57,    62,    74,    57,    47,    59,    60,    92,
      47,    62,    60,   193,    65,   195,    68,    74,    29,    30,
      31,    32,    55,   115,    57,    74,    37,    60,   120,    76,
      74,    55,    64,   115,   116,    57,    60,    59,   120,   186,
     187,   188,   189,   190,   191,   312,    68,   138,   139,     8,
       9,    10,   135,   135,    61,    62,   138,   139,   140,   141,
      61,   198,    48,    74,    80,    81,    82,    53,    54,    55,
      56,   208,    61,   209,   210,   157,   158,   159,    38,    39,
      40,    41,   115,   165,   176,    62,   222,   120,    65,    61,
     227,   285,    78,   140,   176,    61,    14,   229,   230,    62,
      63,   193,    56,   195,    58,    63,    57,    61,    59,    60,
      63,   193,   194,   195,    74,    64,   198,    68,   165,    61,
     300,    62,   302,    47,    65,    64,   208,   209,   210,   309,
     212,   213,    62,    51,    52,    65,    64,    91,    47,   221,
     222,    62,    63,   176,    27,   227,    62,    63,   328,   231,
     286,   233,   234,    71,    72,    68,    74,    75,    62,    63,
     193,   194,   195,    27,   118,   119,   213,   121,   305,    58,
     307,   308,    62,    63,     4,     5,     6,   314,     8,     9,
      10,    58,   198,    33,    34,    35,    36,   234,   183,   184,
     185,    69,   208,   209,   210,    62,   212,    11,   334,    62,
      63,   284,   284,   285,   286,   221,   222,   344,   300,   291,
     302,   227,    14,    62,    63,    61,    61,   309,   300,    20,
     302,    58,    27,   305,    63,   307,   308,   309,    63,    27,
     312,   314,   314,   315,    11,    61,   328,    61,   192,   321,
      65,    64,   196,   197,   291,   141,   328,    11,    15,    76,
      78,    73,   334,   133,     4,    75,    77,   284,     8,     9,
      10,   344,   344,   284,    77,   348,   348,   300,   315,   302,
     286,   348,    78,   344,   321,   231,   309,   297,   157,    29,
      30,    31,    32,    50,    51,    52,   240,    37,    20,   305,
     307,   307,   308,   308,   192,   328,   312,    64,   314,    62,
      19,    68,   242,    18,    71,    72,    59,    74,    75,    -1,
      42,    43,    44,    45,    46,    47,    -1,   271,   334,   273,
      -1,    -1,    -1,    10,    74,    12,    -1,    -1,   344,    16,
      -1,    -1,    19,    -1,    21,    13,    -1,    24,    -1,    26,
      -1,    28,    -1,    -1,    18,    -1,    -1,    -1,    -1,   303,
     304,    38,    39,    40,    41,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    42,    43,    44,    45,    46,    47,
      -1,    29,    30,    31,    32,    -1,    -1,    51,    52,    37,
      -1,    -1,    -1,    -1,    71,    59,    -1,    74,    51,    52,
      64,    -1,    -1,    51,    52,    -1,    -1,    71,    72,    -1,
      74,    75,    22,    23,    -1,    -1,    64,    -1,    71,    72,
      -1,    74,    75,    71,    72,    -1,    74,    75,    -1,    27,
      -1,    -1,    42,    43,    44,    45,    46,    47,    42,    43,
      44,    45,    46,    47,    42,    43,    44,    45,    46,    47,
      42,    43,    44,    45,    46,    47,    -1,    -1,    -1,    -1,
      -1,    65,    -1,    -1,    -1,    -1,    58,     4,     5,     6,
       7,     8,     9,    10,    42,    43,    44,    45,    46,    47,
      17,     4,     5,     6,     7,     8,     9,    10,   177,   178,
     179,   180,   181,   182
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    81,    74,     0,    64,    82,   149,    74,    83,
     143,    61,    62,    65,     4,     5,     6,     7,     8,     9,
      10,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,   109,   110,   143,    94,   143,   137,   143,    29,    30,
      31,    32,    37,   138,   143,    71,   144,    38,    39,    40,
      41,   140,   143,   139,   143,    10,    12,    16,    19,    21,
      24,    26,    28,   116,   117,   118,   127,   140,   142,   143,
     144,   149,    57,    61,    62,    61,    61,    61,    61,    62,
      63,    47,    47,    64,   112,   112,   116,    15,    50,    51,
      52,    64,    68,    72,    75,   118,   129,   130,   131,   132,
     133,   139,   143,   144,   145,   148,   118,   128,   143,   129,
     142,   116,   129,   127,    11,    61,    57,    59,    60,    68,
      63,    64,    85,   144,    86,   137,    87,   138,    88,    94,
      89,   110,   143,    18,    33,    34,    35,    36,    51,    52,
      59,    64,    71,    72,    95,    96,    97,    98,    99,   137,
     138,   143,   146,   147,   148,    95,    96,     4,     8,     9,
     113,   114,   115,   143,    61,    63,    11,   132,   132,   132,
     129,   129,   134,   135,   136,   149,    13,    42,    43,    44,
      45,    46,    47,    49,    51,    52,    48,    53,    54,    55,
      56,    78,    64,    20,    62,    20,    60,    25,    27,   117,
     141,   143,   129,   119,   129,   117,   126,   129,    47,    47,
      63,    99,    68,    26,   101,   102,   103,   104,   105,   141,
     149,    27,    27,   137,   137,   138,    83,    58,   115,   143,
     143,    61,    65,    62,    63,    17,    84,   111,   138,    65,
      58,    69,    62,   117,   130,   130,   130,   130,   130,   130,
     131,   131,   131,   132,   132,   132,   132,   132,   132,   126,
     117,   118,   117,   125,   129,   129,    95,   120,   121,   122,
     123,    62,    69,    62,    65,    95,    96,    96,    97,   100,
     106,   138,   143,    11,    61,    62,    63,    97,    96,    65,
      95,    63,   112,   112,   114,   143,   138,    61,   129,   136,
      14,    65,    20,    22,    23,    58,    11,    61,    62,    63,
     129,   129,    62,    69,    27,    63,   103,   105,   141,    96,
     138,    63,   111,   117,   117,   129,   129,    95,    14,   121,
     124,   123,   117,    97,    27,   107,   108,   122,   149,   138,
     138,   117,    11,    96,    61,    63,    61,   108,    64,   101,
      65
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
     133,   133,   133,   133,   133,   133,   133,   133,   134,   134,
     135,   135,   136,   136,   137,   138,   138,   138,   138,   138,
     138,   139,   140,   140,   140,   140,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149
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
       1,     1,     1,     1,     1,     4,     3,     3,     1,     1,
       1,     3,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0
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
#line 137 "parser/parser.y"
                                                             {
      (yyval.node) = create_program_node((yyvsp[-4].string), (yyvsp[-3].node), (yyvsp[-1].node), create_location((yyloc)));
      root = (yyval.node);
   }
#line 1915 "parser/parser.tab.c"
    break;

  case 3: /* program_headingopt: L_PAREN identifier_list R_PAREN  */
#line 143 "parser/parser.y"
                                    {
      (yyval.node) = create_heading_node((yyvsp[-1].node), create_location((yyloc)));
    }
#line 1923 "parser/parser.tab.c"
    break;

  case 5: /* identifier_list: identifier  */
#line 149 "parser/parser.y"
               {
      (yyval.node) = create_identifier_list_node((yyvsp[0].node), create_location((yyloc)));
    }
#line 1931 "parser/parser.tab.c"
    break;

  case 6: /* identifier_list: identifier_list COMMA identifier  */
#line 152 "parser/parser.y"
                                     {
      (yyval.node) = append_identifier_list_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 1939 "parser/parser.tab.c"
    break;

  case 7: /* block: block1  */
#line 157 "parser/parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 1945 "parser/parser.tab.c"
    break;

  case 8: /* block: label_declaration SEMICOLON block1  */
#line 158 "parser/parser.y"
                                       {
      (yyval.node) = add_labels_to_block((yyvsp[0].node), (yyvsp[-2].node));
    }
#line 1953 "parser/parser.tab.c"
    break;

  case 9: /* block1: block2  */
#line 163 "parser/parser.y"
            { (yyval.node) = (yyvsp[0].node); }
#line 1959 "parser/parser.tab.c"
    break;

  case 10: /* block1: constant_declaration SEMICOLON block2  */
#line 164 "parser/parser.y"
                                          {
    (yyval.node) = add_constants_to_block((yyvsp[0].node), (yyvsp[-2].node));
  }
#line 1967 "parser/parser.tab.c"
    break;

  case 11: /* block2: block3  */
#line 169 "parser/parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 1973 "parser/parser.tab.c"
    break;

  case 12: /* block2: type_declaration SEMICOLON block3  */
#line 170 "parser/parser.y"
                                      {
     (yyval.node) = add_types_to_block((yyvsp[0].node), (yyvsp[-2].node));
  }
#line 1981 "parser/parser.tab.c"
    break;

  case 13: /* block3: block4  */
#line 175 "parser/parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 1987 "parser/parser.tab.c"
    break;

  case 14: /* block3: variable_declaration SEMICOLON block4  */
#line 176 "parser/parser.y"
                                          {
      (yyval.node) = add_variables_to_block((yyvsp[0].node), (yyvsp[-2].node));
    }
#line 1995 "parser/parser.tab.c"
    break;

  case 15: /* block4: block5  */
#line 181 "parser/parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 2001 "parser/parser.tab.c"
    break;

  case 16: /* block4: proc_and_func_declaration SEMICOLON block5  */
#line 182 "parser/parser.y"
                                               {
      (yyval.node) = add_procs_funcs_to_block((yyvsp[0].node), (yyvsp[-2].node));
    }
#line 2009 "parser/parser.tab.c"
    break;

  case 17: /* block5: BEGIN_TOK statement_list END  */
#line 187 "parser/parser.y"
                                 {
      (yyval.node) = create_block_node(NULL, NULL, NULL, NULL, NULL, (yyvsp[-1].node), create_location((yyloc)));
    }
#line 2017 "parser/parser.tab.c"
    break;

  case 18: /* label_declaration: LABEL unsigned_integer  */
#line 192 "parser/parser.y"
                           { (yyval.node) = create_label_declaration_node((yyvsp[0].node), create_location((yyloc))); }
#line 2023 "parser/parser.tab.c"
    break;

  case 19: /* label_declaration: label_declaration COMMA unsigned_integer  */
#line 193 "parser/parser.y"
                                             {
      (yyval.node) = append_label_declaration((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2031 "parser/parser.tab.c"
    break;

  case 20: /* constant_declaration: CONST constid EQ constant  */
#line 198 "parser/parser.y"
                              {
      (yyval.node) = create_constant_declaration_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2039 "parser/parser.tab.c"
    break;

  case 21: /* constant_declaration: constant_declaration SEMICOLON constid EQ constant  */
#line 201 "parser/parser.y"
                                                       {
      (yyval.node) = append_constant_declaration((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2047 "parser/parser.tab.c"
    break;

  case 22: /* type_declaration: TYPE typeid EQ type  */
#line 206 "parser/parser.y"
                        { (yyval.node) = create_type_declaration_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2053 "parser/parser.tab.c"
    break;

  case 23: /* type_declaration: type_declaration SEMICOLON typeid EQ type  */
#line 207 "parser/parser.y"
                                              {
      (yyval.node) = append_type_declaration((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2061 "parser/parser.tab.c"
    break;

  case 24: /* variable_declaration: VAR variableid_list COLON type  */
#line 212 "parser/parser.y"
                                   { (yyval.node) = create_variable_declaration_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2067 "parser/parser.tab.c"
    break;

  case 25: /* variable_declaration: variable_declaration SEMICOLON variableid_list COLON type  */
#line 213 "parser/parser.y"
                                                              {
      (yyval.node) = append_variable_declaration((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2075 "parser/parser.tab.c"
    break;

  case 26: /* variableid_list: identifier  */
#line 218 "parser/parser.y"
                { (yyval.node) = create_variable_identifier_list_node((yyvsp[0].node), create_location((yyloc))); }
#line 2081 "parser/parser.tab.c"
    break;

  case 27: /* variableid_list: variableid_list COMMA identifier  */
#line 219 "parser/parser.y"
                                     {
      (yyval.node) = append_variable_identifier_list((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2089 "parser/parser.tab.c"
    break;

  case 28: /* constant: integer_literal  */
#line 224 "parser/parser.y"
                    {
      (yyval.node) = create_constant_literal((yyvsp[0].node), create_location((yyloc)));
    }
#line 2097 "parser/parser.tab.c"
    break;

  case 29: /* constant: real_literal  */
#line 227 "parser/parser.y"
                 {
      (yyval.node) = create_constant_literal((yyvsp[0].node), create_location((yyloc)));
    }
#line 2105 "parser/parser.tab.c"
    break;

  case 30: /* constant: string_literal  */
#line 230 "parser/parser.y"
                   {
      (yyval.node) = create_constant_literal((yyvsp[0].node), create_location((yyloc)));
    }
#line 2113 "parser/parser.tab.c"
    break;

  case 31: /* constant: constid  */
#line 233 "parser/parser.y"
            { (yyval.node) = create_constant_identifier((yyvsp[0].node), create_location((yyloc))); }
#line 2119 "parser/parser.tab.c"
    break;

  case 32: /* constant: PLUS constid  */
#line 234 "parser/parser.y"
                 { (yyval.node) = create_constant_signed_identifier((yyvsp[0].node), "+", create_location((yyloc))); }
#line 2125 "parser/parser.tab.c"
    break;

  case 33: /* constant: MINUS constid  */
#line 235 "parser/parser.y"
                  { (yyval.node) = create_constant_signed_identifier((yyvsp[0].node), "-", create_location((yyloc))); }
#line 2131 "parser/parser.tab.c"
    break;

  case 34: /* type: simple_type  */
#line 238 "parser/parser.y"
                {
      (yyval.node) = create_simple_type_node((yyvsp[0].node), create_location((yyloc)));
    }
#line 2139 "parser/parser.tab.c"
    break;

  case 35: /* type: structured_type  */
#line 241 "parser/parser.y"
                    {
      (yyval.node) = create_structure_type_node((yyvsp[0].node), create_location((yyloc)));
    }
#line 2147 "parser/parser.tab.c"
    break;

  case 36: /* type: CARET typeid  */
#line 244 "parser/parser.y"
                 {
      (yyval.node) = create_pointer_type_node((yyvsp[0].node), create_location((yyloc)));
    }
#line 2155 "parser/parser.tab.c"
    break;

  case 37: /* simple_type: L_PAREN identifier_list R_PAREN  */
#line 249 "parser/parser.y"
                                     { (yyval.node) = create_enumerated_type_node((yyvsp[-1].node), create_location((yyloc))); }
#line 2161 "parser/parser.tab.c"
    break;

  case 38: /* simple_type: constant DOTDOT constant  */
#line 250 "parser/parser.y"
                             {
      (yyval.node) = create_constant_range_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2169 "parser/parser.tab.c"
    break;

  case 39: /* simple_type: typeid  */
#line 253 "parser/parser.y"
           {
      (yyval.node) = (yyvsp[0].node);
    }
#line 2177 "parser/parser.tab.c"
    break;

  case 40: /* structured_type: unpacked_structured_type  */
#line 258 "parser/parser.y"
                             {
      (yyval.node) = (yyvsp[0].node);
    }
#line 2185 "parser/parser.tab.c"
    break;

  case 41: /* structured_type: PACKED unpacked_structured_type  */
#line 261 "parser/parser.y"
                                      {
      (yyval.node) = create_packed_type((yyvsp[0].node), create_location((yyloc)));
    }
#line 2193 "parser/parser.tab.c"
    break;

  case 42: /* unpacked_structured_type: ARRAY L_BRACKET index_list R_BRACKET OF type  */
#line 266 "parser/parser.y"
                                                   {
        (yyval.node) = create_array_type_node((yyvsp[-3].node), (yyvsp[0].node), create_location((yyloc)));
      }
#line 2201 "parser/parser.tab.c"
    break;

  case 43: /* unpacked_structured_type: RECORD field_list END  */
#line 269 "parser/parser.y"
                            {
        (yyval.node) = create_record_type_node((yyvsp[-1].node), create_location((yyloc)));
      }
#line 2209 "parser/parser.tab.c"
    break;

  case 44: /* unpacked_structured_type: SET OF simple_type  */
#line 272 "parser/parser.y"
                         {
        (yyval.node) = create_set_of_type_node((yyvsp[0].node), create_location((yyloc)));
      }
#line 2217 "parser/parser.tab.c"
    break;

  case 45: /* unpacked_structured_type: FILE_TOK  */
#line 275 "parser/parser.y"
               {
        (yyval.node) = create_file_of_type_node(NULL, create_location((yyloc)));
      }
#line 2225 "parser/parser.tab.c"
    break;

  case 46: /* unpacked_structured_type: FILE_TOK OF type  */
#line 278 "parser/parser.y"
                       {
        (yyval.node) = create_file_of_type_node((yyvsp[0].node), create_location((yyloc)));
      }
#line 2233 "parser/parser.tab.c"
    break;

  case 47: /* index_list: simple_type  */
#line 283 "parser/parser.y"
                { 
      (yyval.node) = create_index_list_start((yyvsp[0].node), create_location((yyloc))); 
    }
#line 2241 "parser/parser.tab.c"
    break;

  case 48: /* index_list: index_list COMMA simple_type  */
#line 286 "parser/parser.y"
                                 {
      (yyval.node) = append_index_to_list((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2249 "parser/parser.tab.c"
    break;

  case 49: /* field_list: fixed_part  */
#line 291 "parser/parser.y"
               { (yyval.node) = create_field_list((yyvsp[0].node), NULL, create_location((yyloc))); }
#line 2255 "parser/parser.tab.c"
    break;

  case 50: /* field_list: fixed_part SEMICOLON variant_part  */
#line 292 "parser/parser.y"
                                      { (yyval.node) = create_field_list((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2261 "parser/parser.tab.c"
    break;

  case 51: /* field_list: variant_part  */
#line 293 "parser/parser.y"
                 { (yyval.node) = create_field_list(NULL, (yyvsp[0].node), create_location((yyloc))); }
#line 2267 "parser/parser.tab.c"
    break;

  case 52: /* fixed_part: record_field  */
#line 296 "parser/parser.y"
                 { (yyval.node) = create_fixed_part_node(NULL, (yyvsp[0].node), create_location((yyloc))); }
#line 2273 "parser/parser.tab.c"
    break;

  case 53: /* fixed_part: fixed_part SEMICOLON record_field  */
#line 297 "parser/parser.y"
                                      { (yyval.node) = create_fixed_part_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2279 "parser/parser.tab.c"
    break;

  case 55: /* record_field: fieldid_list COLON type  */
#line 301 "parser/parser.y"
                            { (yyval.node) = create_record_field_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2285 "parser/parser.tab.c"
    break;

  case 56: /* fieldid_list: fieldid  */
#line 304 "parser/parser.y"
            { (yyval.node) = create_field_identifier_list_node(NULL, (yyvsp[0].node), create_location((yyloc))); }
#line 2291 "parser/parser.tab.c"
    break;

  case 57: /* fieldid_list: fieldid_list COMMA fieldid  */
#line 305 "parser/parser.y"
                               { (yyval.node) = create_field_identifier_list_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2297 "parser/parser.tab.c"
    break;

  case 58: /* variant_part: CASE tag_field OF variant_list  */
#line 308 "parser/parser.y"
                                   { (yyval.node) = create_case_of_variant_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2303 "parser/parser.tab.c"
    break;

  case 59: /* tag_field: typeid  */
#line 311 "parser/parser.y"
           { (yyval.node) = create_tag_field_node(NULL, (yyvsp[0].node), create_location((yyloc))); }
#line 2309 "parser/parser.tab.c"
    break;

  case 60: /* tag_field: identifier COLON typeid  */
#line 312 "parser/parser.y"
                            { (yyval.node) = create_tag_field_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2315 "parser/parser.tab.c"
    break;

  case 61: /* variant_list: variant  */
#line 315 "parser/parser.y"
            { (yyval.node) = append_variant_list(NULL, (yyvsp[0].node), create_location((yyloc))); }
#line 2321 "parser/parser.tab.c"
    break;

  case 62: /* variant_list: variant_list SEMICOLON variant  */
#line 316 "parser/parser.y"
                                   {
      (yyval.node) = append_variant_list((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2329 "parser/parser.tab.c"
    break;

  case 64: /* variant: case_label_list COLON L_PAREN field_list R_PAREN  */
#line 322 "parser/parser.y"
                                                     {
      (yyval.node) = create_variant_node((yyvsp[-4].node), (yyvsp[-1].node), create_location((yyloc)));
    }
#line 2337 "parser/parser.tab.c"
    break;

  case 65: /* proc_and_func_declaration: proc_or_func  */
#line 327 "parser/parser.y"
                 { (yyval.node) = create_proc_and_func_declarations_node((yyvsp[0].node), create_location((yyloc))); }
#line 2343 "parser/parser.tab.c"
    break;

  case 66: /* proc_and_func_declaration: proc_and_func_declaration SEMICOLON proc_or_func  */
#line 328 "parser/parser.y"
                                                     {
      (yyval.node) = append_proc_and_func_declarations((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2351 "parser/parser.tab.c"
    break;

  case 67: /* proc_or_func: PROCEDURE procid parameters SEMICOLON block_or_forward  */
#line 333 "parser/parser.y"
                                                           { /* identifier of func/proc declaration */ 
      (yyval.node) = create_proc_declaration_node((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2359 "parser/parser.tab.c"
    break;

  case 68: /* proc_or_func: FUNCTION funcid parameters COLON typeid SEMICOLON block_or_forward  */
#line 336 "parser/parser.y"
                                                                       {
      (yyval.node) = create_func_declaration_node((yyvsp[-5].node), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2367 "parser/parser.tab.c"
    break;

  case 69: /* block_or_forward: block  */
#line 341 "parser/parser.y"
          { (yyval.node) = (yyvsp[0].node); }
#line 2373 "parser/parser.tab.c"
    break;

  case 70: /* block_or_forward: FORWARD  */
#line 342 "parser/parser.y"
             { (yyval.node) = create_forward_declaration_node(create_location((yyloc))); }
#line 2379 "parser/parser.tab.c"
    break;

  case 71: /* parameters: L_PAREN formal_parameter_list R_PAREN  */
#line 345 "parser/parser.y"
                                         { (yyval.node) = create_parameters_node((yyvsp[-1].node), create_location((yyloc))); }
#line 2385 "parser/parser.tab.c"
    break;

  case 72: /* formal_parameter_list: formal_parameter_section  */
#line 348 "parser/parser.y"
                             { (yyval.node) = create_formal_parameters_list_node(NULL, (yyvsp[0].node), create_location((yyloc))); }
#line 2391 "parser/parser.tab.c"
    break;

  case 73: /* formal_parameter_list: formal_parameter_list SEMICOLON formal_parameter_section  */
#line 349 "parser/parser.y"
                                                             {
      (yyval.node) = create_formal_parameters_list_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2399 "parser/parser.tab.c"
    break;

  case 74: /* formal_parameter_section: parameterid_list COLON typeid  */
#line 354 "parser/parser.y"
                                  { 
        (yyval.node) = create_formal_parameter_section_node(PARAM_VALUE, (yyvsp[-2].node), (yyvsp[0].node), NULL, NULL, create_location((yyloc))); 
      }
#line 2407 "parser/parser.tab.c"
    break;

  case 75: /* formal_parameter_section: VAR parameterid_list COLON typeid  */
#line 357 "parser/parser.y"
                                        { 
        (yyval.node) = create_formal_parameter_section_node(PARAM_VAR, (yyvsp[-2].node), (yyvsp[0].node), NULL, NULL, create_location((yyloc))); 
      }
#line 2415 "parser/parser.tab.c"
    break;

  case 76: /* formal_parameter_section: PROCEDURE identifier parameters  */
#line 360 "parser/parser.y"
                                      { 
        ASTNode* single_id = create_parameter_identifier_list_node(NULL, (yyvsp[-1].node), create_location((yylsp[-1])));
        (yyval.node) = create_formal_parameter_section_node(PARAM_PROCEDURE, single_id, NULL, (yyvsp[0].node), NULL, create_location((yyloc))); 
      }
#line 2424 "parser/parser.tab.c"
    break;

  case 77: /* formal_parameter_section: FUNCTION identifier parameters COLON typeid  */
#line 364 "parser/parser.y"
                                                  { 
        ASTNode* single_id = create_parameter_identifier_list_node(NULL, (yyvsp[-3].node), create_location((yylsp[-3])));
        (yyval.node) = create_formal_parameter_section_node(PARAM_FUNCTION, single_id, NULL, (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); 
      }
#line 2433 "parser/parser.tab.c"
    break;

  case 78: /* parameterid_list: identifier  */
#line 370 "parser/parser.y"
                { (yyval.node) = create_parameter_identifier_list_node(NULL, (yyvsp[0].node), create_location((yyloc))); }
#line 2439 "parser/parser.tab.c"
    break;

  case 79: /* parameterid_list: parameterid_list COMMA identifier  */
#line 371 "parser/parser.y"
                                       { 
      (yyval.node) = create_parameter_identifier_list_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2447 "parser/parser.tab.c"
    break;

  case 80: /* statement_list: statement  */
#line 376 "parser/parser.y"
              { (yyval.node) = create_stmt_list_node((yyvsp[0].node), create_location((yyloc))); }
#line 2453 "parser/parser.tab.c"
    break;

  case 81: /* statement_list: statement_list SEMICOLON statement  */
#line 377 "parser/parser.y"
                                       { (yyval.node) = append_stmt_list((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2459 "parser/parser.tab.c"
    break;

  case 83: /* statement: variable ASSIGN expression  */
#line 381 "parser/parser.y"
                               { (yyval.node) = create_assign_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2465 "parser/parser.tab.c"
    break;

  case 84: /* statement: BEGIN_TOK statement_list END  */
#line 382 "parser/parser.y"
                                  { (yyval.node) = create_stmt_list_node((yyvsp[-1].node), create_location((yyloc))); }
#line 2471 "parser/parser.tab.c"
    break;

  case 85: /* statement: IF expression THEN statement  */
#line 383 "parser/parser.y"
                                                       { (yyval.node) = create_if_stmt_node((yyvsp[-2].node), (yyvsp[0].node), NULL, create_location((yyloc))); }
#line 2477 "parser/parser.tab.c"
    break;

  case 86: /* statement: IF expression THEN statement ELSE statement  */
#line 384 "parser/parser.y"
                                                { (yyval.node) = create_if_stmt_node((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2483 "parser/parser.tab.c"
    break;

  case 87: /* statement: CASE expression OF case_list END  */
#line 385 "parser/parser.y"
                                     { (yyval.node) = create_case_stmt_node((yyvsp[-3].node), (yyvsp[-1].node), NULL, create_location((yyloc))); }
#line 2489 "parser/parser.tab.c"
    break;

  case 88: /* statement: CASE expression OF case_list SEMICOLON case_else END  */
#line 386 "parser/parser.y"
                                                         { (yyval.node) = create_case_stmt_with_else_node((yyvsp[-5].node), (yyvsp[-3].node), (yyvsp[-1].node), create_location((yyloc))); }
#line 2495 "parser/parser.tab.c"
    break;

  case 89: /* statement: WHILE expression DO statement  */
#line 387 "parser/parser.y"
                                  { (yyval.node) = create_while_stmt_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2501 "parser/parser.tab.c"
    break;

  case 90: /* statement: REPEAT statement_list UNTIL expression  */
#line 388 "parser/parser.y"
                                           { (yyval.node) = create_repeat_until_stmt_list_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2507 "parser/parser.tab.c"
    break;

  case 91: /* statement: FOR varid ASSIGN for_list DO statement  */
#line 389 "parser/parser.y"
                                           { (yyval.node) = create_for_stmt_node((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2513 "parser/parser.tab.c"
    break;

  case 92: /* statement: procid  */
#line 390 "parser/parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 2519 "parser/parser.tab.c"
    break;

  case 93: /* statement: procid L_PAREN expression_list R_PAREN  */
#line 391 "parser/parser.y"
                                           { (yyval.node) = create_procedure_call_node((yyvsp[-3].node), (yyvsp[-1].node), create_location((yyloc))); }
#line 2525 "parser/parser.tab.c"
    break;

  case 94: /* statement: GOTO label  */
#line 392 "parser/parser.y"
               { (yyval.node) = create_goto_label_node((yyvsp[0].node), create_location((yyloc))); }
#line 2531 "parser/parser.tab.c"
    break;

  case 95: /* statement: WITH record_variable_list DO statement  */
#line 393 "parser/parser.y"
                                           { (yyval.node) = create_with_record_list_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2537 "parser/parser.tab.c"
    break;

  case 96: /* statement: label COLON statement  */
#line 394 "parser/parser.y"
                          { (yyval.node) = create_label_stmt_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2543 "parser/parser.tab.c"
    break;

  case 97: /* variable: varid  */
#line 397 "parser/parser.y"
          { (yyval.node) = (yyvsp[0].node); }
#line 2549 "parser/parser.tab.c"
    break;

  case 98: /* variable: variable L_BRACKET subscript_list R_BRACKET  */
#line 398 "parser/parser.y"
                                                { (yyval.node) = create_array_access_node((yyvsp[-3].node), (yyvsp[-1].node), create_location((yyloc))); }
#line 2555 "parser/parser.tab.c"
    break;

  case 99: /* variable: variable DOT fieldid  */
#line 399 "parser/parser.y"
                         { (yyval.node) = create_record_access_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2561 "parser/parser.tab.c"
    break;

  case 100: /* variable: variable CARET  */
#line 400 "parser/parser.y"
                   { (yyval.node) = create_pointer_deref_node((yyvsp[-1].node), create_location((yyloc))); }
#line 2567 "parser/parser.tab.c"
    break;

  case 101: /* subscript_list: expression  */
#line 403 "parser/parser.y"
               { 
        (yyval.node) = create_subscript_list_node((yyvsp[0].node), create_location((yyloc))); 
    }
#line 2575 "parser/parser.tab.c"
    break;

  case 102: /* subscript_list: subscript_list COMMA expression  */
#line 406 "parser/parser.y"
                                    { 
        (yyval.node) = append_subscript_list_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2583 "parser/parser.tab.c"
    break;

  case 103: /* case_list: case_item  */
#line 411 "parser/parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 2589 "parser/parser.tab.c"
    break;

  case 104: /* case_list: case_list SEMICOLON case_item  */
#line 412 "parser/parser.y"
                                  { 
      (yyval.node) = append_case_item((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2597 "parser/parser.tab.c"
    break;

  case 105: /* case_item: case_label_list COLON statement  */
#line 417 "parser/parser.y"
                                    { 
      (yyval.node) = create_case_item_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2605 "parser/parser.tab.c"
    break;

  case 106: /* case_label_list: case_label  */
#line 422 "parser/parser.y"
               { (yyval.node) = create_case_label_list((yyvsp[0].node), create_location((yyloc))); }
#line 2611 "parser/parser.tab.c"
    break;

  case 107: /* case_label_list: case_label_list COMMA case_label  */
#line 423 "parser/parser.y"
                                     { 
      (yyval.node) = append_case_label_list((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2619 "parser/parser.tab.c"
    break;

  case 108: /* case_label: constant  */
#line 428 "parser/parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 2625 "parser/parser.tab.c"
    break;

  case 109: /* case_label: constant DOTDOT constant  */
#line 429 "parser/parser.y"
                             { 
      (yyval.node) = create_constant_range_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2633 "parser/parser.tab.c"
    break;

  case 110: /* case_else: ELSE statement SEMICOLON  */
#line 434 "parser/parser.y"
                             {
      (yyval.node) = create_case_else_node((yyvsp[-1].node), create_location((yyloc)));
    }
#line 2641 "parser/parser.tab.c"
    break;

  case 111: /* for_list: expression TO expression  */
#line 439 "parser/parser.y"
                             { 
      (yyval.node) = create_for_list_node((yyvsp[-2].node), (yyvsp[0].node), false, create_location((yyloc))); 
    }
#line 2649 "parser/parser.tab.c"
    break;

  case 112: /* for_list: expression DOWNTO expression  */
#line 442 "parser/parser.y"
                                 { 
      (yyval.node) = create_for_list_node((yyvsp[-2].node), (yyvsp[0].node), true, create_location((yyloc))); 
    }
#line 2657 "parser/parser.tab.c"
    break;

  case 113: /* expression_list: expression  */
#line 447 "parser/parser.y"
               { (yyval.node) = create_expression_list((yyvsp[0].node), create_location((yyloc))); }
#line 2663 "parser/parser.tab.c"
    break;

  case 114: /* expression_list: expression_list COMMA expression  */
#line 448 "parser/parser.y"
                                     { (yyval.node) = append_expression_list((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2669 "parser/parser.tab.c"
    break;

  case 115: /* label: unsigned_integer  */
#line 451 "parser/parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 2675 "parser/parser.tab.c"
    break;

  case 116: /* record_variable_list: variable  */
#line 454 "parser/parser.y"
             { (yyval.node) = create_record_variable_list_node((yyvsp[0].node), create_location((yyloc))); }
#line 2681 "parser/parser.tab.c"
    break;

  case 117: /* record_variable_list: record_variable_list COMMA variable  */
#line 455 "parser/parser.y"
                                        { 
      (yyval.node) = append_record_variable_list((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2689 "parser/parser.tab.c"
    break;

  case 118: /* expression: expression LT additive_expression  */
#line 460 "parser/parser.y"
                                      { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_LT, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2697 "parser/parser.tab.c"
    break;

  case 119: /* expression: expression LTE additive_expression  */
#line 463 "parser/parser.y"
                                       { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_LTE, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2705 "parser/parser.tab.c"
    break;

  case 120: /* expression: expression EQ additive_expression  */
#line 466 "parser/parser.y"
                                      { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_EQ, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2713 "parser/parser.tab.c"
    break;

  case 121: /* expression: expression NEQ additive_expression  */
#line 469 "parser/parser.y"
                                       { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_NEQ, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2721 "parser/parser.tab.c"
    break;

  case 122: /* expression: expression GTE additive_expression  */
#line 472 "parser/parser.y"
                                       { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_GTE, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2729 "parser/parser.tab.c"
    break;

  case 123: /* expression: expression GT additive_expression  */
#line 475 "parser/parser.y"
                                      { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_GT, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2737 "parser/parser.tab.c"
    break;

  case 124: /* expression: additive_expression  */
#line 478 "parser/parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 2743 "parser/parser.tab.c"
    break;

  case 125: /* additive_expression: additive_expression PLUS multiplicative_expression  */
#line 481 "parser/parser.y"
                                                       { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_PLUS, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2751 "parser/parser.tab.c"
    break;

  case 126: /* additive_expression: additive_expression MINUS multiplicative_expression  */
#line 484 "parser/parser.y"
                                                        { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_MINUS, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2759 "parser/parser.tab.c"
    break;

  case 127: /* additive_expression: additive_expression OR multiplicative_expression  */
#line 487 "parser/parser.y"
                                                     { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_OR, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2767 "parser/parser.tab.c"
    break;

  case 128: /* additive_expression: multiplicative_expression  */
#line 490 "parser/parser.y"
                              { (yyval.node) = (yyvsp[0].node); }
#line 2773 "parser/parser.tab.c"
    break;

  case 129: /* multiplicative_expression: multiplicative_expression TIMES unary_expression  */
#line 493 "parser/parser.y"
                                                     { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_TIMES, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2781 "parser/parser.tab.c"
    break;

  case 130: /* multiplicative_expression: multiplicative_expression DIVIDE unary_expression  */
#line 496 "parser/parser.y"
                                                      { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_DIVIDE, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2789 "parser/parser.tab.c"
    break;

  case 131: /* multiplicative_expression: multiplicative_expression DIV unary_expression  */
#line 499 "parser/parser.y"
                                                   { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_DIV, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2797 "parser/parser.tab.c"
    break;

  case 132: /* multiplicative_expression: multiplicative_expression MOD unary_expression  */
#line 502 "parser/parser.y"
                                                   { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_MOD, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2805 "parser/parser.tab.c"
    break;

  case 133: /* multiplicative_expression: multiplicative_expression AND unary_expression  */
#line 505 "parser/parser.y"
                                                   { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_AND, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2813 "parser/parser.tab.c"
    break;

  case 134: /* multiplicative_expression: multiplicative_expression IN unary_expression  */
#line 508 "parser/parser.y"
                                                  { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_IN, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2821 "parser/parser.tab.c"
    break;

  case 135: /* multiplicative_expression: unary_expression  */
#line 511 "parser/parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2827 "parser/parser.tab.c"
    break;

  case 136: /* unary_expression: PLUS unary_expression  */
#line 514 "parser/parser.y"
                          { 
      (yyval.node) = create_unary_expression(UNOP_PLUS, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2835 "parser/parser.tab.c"
    break;

  case 137: /* unary_expression: MINUS unary_expression  */
#line 517 "parser/parser.y"
                                     { 
      (yyval.node) = create_unary_expression(UNOP_MINUS, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2843 "parser/parser.tab.c"
    break;

  case 138: /* unary_expression: NOT unary_expression  */
#line 520 "parser/parser.y"
                                   { 
      (yyval.node) = create_unary_expression(UNOP_NOT, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2851 "parser/parser.tab.c"
    break;

  case 139: /* unary_expression: primary_expression  */
#line 523 "parser/parser.y"
                       { (yyval.node) = (yyvsp[0].node); }
#line 2857 "parser/parser.tab.c"
    break;

  case 140: /* primary_expression: variable  */
#line 526 "parser/parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 2863 "parser/parser.tab.c"
    break;

  case 141: /* primary_expression: unsigned_integer  */
#line 527 "parser/parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2869 "parser/parser.tab.c"
    break;

  case 142: /* primary_expression: unsigned_real  */
#line 528 "parser/parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 2875 "parser/parser.tab.c"
    break;

  case 143: /* primary_expression: string_literal  */
#line 529 "parser/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 2881 "parser/parser.tab.c"
    break;

  case 144: /* primary_expression: NIL  */
#line 530 "parser/parser.y"
        {
      (yyval.node) = create_nil_literal(create_location((yyloc)));
    }
#line 2889 "parser/parser.tab.c"
    break;

  case 145: /* primary_expression: funcid L_PAREN expression_list R_PAREN  */
#line 533 "parser/parser.y"
                                           {
      (yyval.node) = create_function_call_node((yyvsp[-3].node), (yyvsp[-1].node), create_location((yyloc)));
    }
#line 2897 "parser/parser.tab.c"
    break;

  case 146: /* primary_expression: L_BRACKET element_list R_BRACKET  */
#line 536 "parser/parser.y"
                                     { (yyval.node) = (yyvsp[-1].node); }
#line 2903 "parser/parser.tab.c"
    break;

  case 147: /* primary_expression: L_PAREN expression R_PAREN  */
#line 537 "parser/parser.y"
                               { (yyval.node) = (yyvsp[-1].node); }
#line 2909 "parser/parser.tab.c"
    break;

  case 148: /* element_list: empty  */
#line 540 "parser/parser.y"
          { 
      (yyval.node) = create_set_literal(create_location((yyloc))); 
    }
#line 2917 "parser/parser.tab.c"
    break;

  case 149: /* element_list: element_list_non_empty  */
#line 543 "parser/parser.y"
                           { 
      (yyval.node) = (yyvsp[0].node); 
    }
#line 2925 "parser/parser.tab.c"
    break;

  case 150: /* element_list_non_empty: element  */
#line 548 "parser/parser.y"
            { 
      (yyval.node) = create_set_literal_with_element((yyvsp[0].node), create_location((yyloc))); 
    }
#line 2933 "parser/parser.tab.c"
    break;

  case 151: /* element_list_non_empty: element_list_non_empty COMMA element  */
#line 551 "parser/parser.y"
                                         {
      (yyval.node) = add_element_to_set_literal((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2941 "parser/parser.tab.c"
    break;

  case 152: /* element: expression  */
#line 556 "parser/parser.y"
               { 
      (yyval.node) = create_set_element((yyvsp[0].node), create_location((yyloc))); 
    }
#line 2949 "parser/parser.tab.c"
    break;

  case 153: /* element: expression DOTDOT expression  */
#line 559 "parser/parser.y"
                                 {
      (yyval.node) = create_set_range_element((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2957 "parser/parser.tab.c"
    break;

  case 154: /* constid: identifier  */
#line 564 "parser/parser.y"
               {
      (yyval.node) = update_identifier_node_kind((yyvsp[0].node), SYMBOL_CONSTANT);
   }
#line 2965 "parser/parser.tab.c"
    break;

  case 155: /* typeid: CHAR  */
#line 569 "parser/parser.y"
         { (yyval.node) = create_builtin_type_identifier("char", create_location((yyloc))); }
#line 2971 "parser/parser.tab.c"
    break;

  case 156: /* typeid: BOOLEAN  */
#line 570 "parser/parser.y"
            { (yyval.node) = create_builtin_type_identifier("boolean", create_location((yyloc))); }
#line 2977 "parser/parser.tab.c"
    break;

  case 157: /* typeid: INTEGER  */
#line 571 "parser/parser.y"
            { (yyval.node) = create_builtin_type_identifier("integer", create_location((yyloc))); }
#line 2983 "parser/parser.tab.c"
    break;

  case 158: /* typeid: REAL  */
#line 572 "parser/parser.y"
         { (yyval.node) = create_builtin_type_identifier("real", create_location((yyloc))); }
#line 2989 "parser/parser.tab.c"
    break;

  case 159: /* typeid: STRING  */
#line 573 "parser/parser.y"
           { (yyval.node) = create_builtin_type_identifier("string", create_location((yyloc))); }
#line 2995 "parser/parser.tab.c"
    break;

  case 160: /* typeid: identifier  */
#line 574 "parser/parser.y"
               {
      ASTNode *typeId = update_identifier_node_kind((yyvsp[0].node), SYMBOL_TYPE);
      (yyval.node) = create_type_identifier(typeId, create_location((yyloc)));
    }
#line 3004 "parser/parser.tab.c"
    break;

  case 161: /* funcid: identifier  */
#line 580 "parser/parser.y"
              { 
    (yyval.node) = update_identifier_node_kind((yyvsp[0].node), SYMBOL_FUNCTION);
  }
#line 3012 "parser/parser.tab.c"
    break;

  case 162: /* procid: identifier  */
#line 585 "parser/parser.y"
             { 
    (yyval.node) = update_identifier_node_kind((yyvsp[0].node), SYMBOL_PROCEDURE);
  }
#line 3020 "parser/parser.tab.c"
    break;

  case 163: /* procid: WRITE  */
#line 588 "parser/parser.y"
          { (yyval.node) = create_builtin_identifier("write", create_location((yyloc))); }
#line 3026 "parser/parser.tab.c"
    break;

  case 164: /* procid: WRITELN  */
#line 589 "parser/parser.y"
            { (yyval.node) = create_builtin_identifier("writeln", create_location((yyloc))); }
#line 3032 "parser/parser.tab.c"
    break;

  case 165: /* procid: READ  */
#line 590 "parser/parser.y"
         { (yyval.node) = create_builtin_identifier("read", create_location((yyloc))); }
#line 3038 "parser/parser.tab.c"
    break;

  case 166: /* procid: READLN  */
#line 591 "parser/parser.y"
           { (yyval.node) = create_builtin_identifier("readln", create_location((yyloc))); }
#line 3044 "parser/parser.tab.c"
    break;

  case 167: /* fieldid: identifier  */
#line 594 "parser/parser.y"
             { 
    (yyval.node) = update_identifier_node_kind((yyvsp[0].node), SYMBOL_FIELD);
  }
#line 3052 "parser/parser.tab.c"
    break;

  case 168: /* varid: identifier  */
#line 599 "parser/parser.y"
             {
    (yyval.node) = update_identifier_node_kind((yyvsp[0].node), SYMBOL_VARIABLE);
  }
#line 3060 "parser/parser.tab.c"
    break;

  case 169: /* identifier: IDENTIFIER  */
#line 604 "parser/parser.y"
              { (yyval.node) = create_identifier_node((yyvsp[0].string), create_location((yyloc))); }
#line 3066 "parser/parser.tab.c"
    break;

  case 170: /* unsigned_integer: INTEGER_LITERAL  */
#line 607 "parser/parser.y"
                    {
      (yyval.node) = create_unsigned_integer_node((yyvsp[0].integer), create_location((yyloc)));
    }
#line 3074 "parser/parser.tab.c"
    break;

  case 171: /* unsigned_real: REAL_LITERAL  */
#line 612 "parser/parser.y"
                 {
      (yyval.node) = create_unsigned_real_node((yyvsp[0].number), create_location((yyloc)));
    }
#line 3082 "parser/parser.tab.c"
    break;

  case 172: /* integer_literal: INTEGER_LITERAL  */
#line 617 "parser/parser.y"
                    {
      (yyval.node) = create_integer_literal((yyvsp[0].integer), create_location((yyloc)));
    }
#line 3090 "parser/parser.tab.c"
    break;

  case 173: /* real_literal: REAL_LITERAL  */
#line 622 "parser/parser.y"
                 {
      (yyval.node) = create_real_literal((yyvsp[0].number), create_location((yyloc)));
    }
#line 3098 "parser/parser.tab.c"
    break;

  case 174: /* string_literal: STRING_LITERAL  */
#line 627 "parser/parser.y"
                   {
      (yyval.node) = create_string_literal((yyvsp[0].string), create_location((yyloc)));
    }
#line 3106 "parser/parser.tab.c"
    break;

  case 175: /* empty: %empty  */
#line 641 "parser/parser.y"
       { (yyval.node) = NULL; }
#line 3112 "parser/parser.tab.c"
    break;


#line 3116 "parser/parser.tab.c"

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

