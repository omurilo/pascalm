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

#line 82 "parser.tab.c"

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
  YYSYMBOL_CHR = 42,                       /* CHR  */
  YYSYMBOL_GT = 43,                        /* GT  */
  YYSYMBOL_GTE = 44,                       /* GTE  */
  YYSYMBOL_LT = 45,                        /* LT  */
  YYSYMBOL_LTE = 46,                       /* LTE  */
  YYSYMBOL_NEQ = 47,                       /* NEQ  */
  YYSYMBOL_EQ = 48,                        /* EQ  */
  YYSYMBOL_AND = 49,                       /* AND  */
  YYSYMBOL_OR = 50,                        /* OR  */
  YYSYMBOL_NOT = 51,                       /* NOT  */
  YYSYMBOL_PLUS = 52,                      /* PLUS  */
  YYSYMBOL_MINUS = 53,                     /* MINUS  */
  YYSYMBOL_TIMES = 54,                     /* TIMES  */
  YYSYMBOL_DIVIDE = 55,                    /* DIVIDE  */
  YYSYMBOL_DIV = 56,                       /* DIV  */
  YYSYMBOL_MOD = 57,                       /* MOD  */
  YYSYMBOL_DOT = 58,                       /* DOT  */
  YYSYMBOL_DOTDOT = 59,                    /* DOTDOT  */
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
  YYSYMBOL_unpacked_structured_type = 100, /* unpacked_structured_type  */
  YYSYMBOL_index_list = 101,               /* index_list  */
  YYSYMBOL_field_list = 102,               /* field_list  */
  YYSYMBOL_fixed_part = 103,               /* fixed_part  */
  YYSYMBOL_record_field = 104,             /* record_field  */
  YYSYMBOL_fieldid_list = 105,             /* fieldid_list  */
  YYSYMBOL_variant_part = 106,             /* variant_part  */
  YYSYMBOL_tag_field = 107,                /* tag_field  */
  YYSYMBOL_variant_list = 108,             /* variant_list  */
  YYSYMBOL_variant = 109,                  /* variant  */
  YYSYMBOL_proc_and_func_declaration = 110, /* proc_and_func_declaration  */
  YYSYMBOL_proc_or_func = 111,             /* proc_or_func  */
  YYSYMBOL_block_or_forward = 112,         /* block_or_forward  */
  YYSYMBOL_parameters = 113,               /* parameters  */
  YYSYMBOL_formal_parameter_list = 114,    /* formal_parameter_list  */
  YYSYMBOL_formal_parameter_section = 115, /* formal_parameter_section  */
  YYSYMBOL_parameterid_list = 116,         /* parameterid_list  */
  YYSYMBOL_statement_list = 117,           /* statement_list  */
  YYSYMBOL_optional_statement = 118,       /* optional_statement  */
  YYSYMBOL_statement = 119,                /* statement  */
  YYSYMBOL_variable = 120,                 /* variable  */
  YYSYMBOL_subscript_list = 121,           /* subscript_list  */
  YYSYMBOL_case_list = 122,                /* case_list  */
  YYSYMBOL_case_item = 123,                /* case_item  */
  YYSYMBOL_case_label_list = 124,          /* case_label_list  */
  YYSYMBOL_case_label = 125,               /* case_label  */
  YYSYMBOL_case_else = 126,                /* case_else  */
  YYSYMBOL_for_list = 127,                 /* for_list  */
  YYSYMBOL_optional_expression_list = 128, /* optional_expression_list  */
  YYSYMBOL_expression_list = 129,          /* expression_list  */
  YYSYMBOL_label = 130,                    /* label  */
  YYSYMBOL_record_variable_list = 131,     /* record_variable_list  */
  YYSYMBOL_expression = 132,               /* expression  */
  YYSYMBOL_additive_expression = 133,      /* additive_expression  */
  YYSYMBOL_multiplicative_expression = 134, /* multiplicative_expression  */
  YYSYMBOL_unary_expression = 135,         /* unary_expression  */
  YYSYMBOL_primary_expression = 136,       /* primary_expression  */
  YYSYMBOL_element_list = 137,             /* element_list  */
  YYSYMBOL_element_list_non_empty = 138,   /* element_list_non_empty  */
  YYSYMBOL_element = 139,                  /* element  */
  YYSYMBOL_constid = 140,                  /* constid  */
  YYSYMBOL_typeid = 141,                   /* typeid  */
  YYSYMBOL_funcid = 142,                   /* funcid  */
  YYSYMBOL_procid = 143,                   /* procid  */
  YYSYMBOL_fieldid = 144,                  /* fieldid  */
  YYSYMBOL_varid = 145,                    /* varid  */
  YYSYMBOL_identifier = 146,               /* identifier  */
  YYSYMBOL_unsigned_integer = 147,         /* unsigned_integer  */
  YYSYMBOL_unsigned_real = 148,            /* unsigned_real  */
  YYSYMBOL_integer_literal = 149,          /* integer_literal  */
  YYSYMBOL_real_literal = 150,             /* real_literal  */
  YYSYMBOL_string_literal = 151,           /* string_literal  */
  YYSYMBOL_char_literal = 152,             /* char_literal  */
  YYSYMBOL_boolean_literal = 153,          /* boolean_literal  */
  YYSYMBOL_empty = 154                     /* empty  */
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
#define YYLAST   584

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  81
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  74
/* YYNRULES -- Number of rules.  */
#define YYNRULES  185
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  361

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
       0,   137,   137,   143,   146,   149,   152,   157,   158,   163,
     164,   169,   170,   175,   176,   181,   182,   187,   192,   193,
     198,   201,   206,   207,   212,   213,   218,   219,   224,   227,
     230,   233,   236,   239,   240,   241,   244,   247,   250,   255,
     256,   259,   264,   267,   272,   275,   278,   281,   284,   289,
     292,   297,   298,   299,   300,   303,   304,   307,   308,   311,
     312,   315,   318,   319,   322,   323,   328,   329,   334,   335,
     340,   343,   348,   349,   352,   355,   356,   361,   364,   367,
     371,   377,   378,   383,   384,   387,   388,   391,   392,   393,
     394,   395,   396,   397,   398,   399,   400,   401,   402,   403,
     404,   407,   408,   409,   410,   413,   416,   421,   422,   427,
     432,   433,   438,   439,   444,   449,   452,   457,   458,   461,
     462,   465,   468,   469,   474,   477,   480,   483,   486,   489,
     492,   495,   498,   501,   504,   507,   510,   513,   516,   519,
     522,   525,   528,   531,   534,   537,   540,   541,   542,   543,
     544,   545,   548,   551,   552,   555,   558,   563,   566,   571,
     574,   579,   584,   585,   586,   587,   588,   589,   595,   598,
     602,   605,   606,   607,   608,   611,   616,   621,   624,   629,
     634,   639,   644,   649,   654,   658
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
  "FILE_TOK", "STRING", "READ", "WRITE", "READLN", "WRITELN", "CHR", "GT",
  "GTE", "LT", "LTE", "NEQ", "EQ", "AND", "OR", "NOT", "PLUS", "MINUS",
  "TIMES", "DIVIDE", "DIV", "MOD", "DOT", "DOTDOT", "CARET", "ASSIGN",
  "SEMICOLON", "COMMA", "COLON", "L_PAREN", "R_PAREN", "L_BRACE",
  "R_BRACE", "L_BRACKET", "R_BRACKET", "CHAR_LITERAL", "INTEGER_LITERAL",
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
  "optional_statement", "statement", "variable", "subscript_list",
  "case_list", "case_item", "case_label_list", "case_label", "case_else",
  "for_list", "optional_expression_list", "expression_list", "label",
  "record_variable_list", "expression", "additive_expression",
  "multiplicative_expression", "unary_expression", "primary_expression",
  "element_list", "element_list_non_empty", "element", "constid", "typeid",
  "funcid", "procid", "fieldid", "varid", "identifier", "unsigned_integer",
  "unsigned_real", "integer_literal", "real_literal", "string_literal",
  "char_literal", "boolean_literal", "empty", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-303)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-177)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       6,   -45,    55,    30,  -303,    -9,    35,  -303,  -303,    22,
    -303,   565,    -9,  -303,    -9,    -9,   152,    40,     1,     8,
     383,    51,  -303,  -303,  -303,  -303,  -303,    65,    59,    80,
      92,   110,  -303,  -303,   112,  -303,    75,  -303,  -303,  -303,
    -303,  -303,  -303,   119,  -303,  -303,  -303,  -303,  -303,  -303,
    -303,   108,  -303,  -303,   108,  -303,   383,   361,    -9,   361,
      -9,   383,   361,    40,    -5,  -303,    95,    93,   113,  -303,
     105,  -303,  -303,   250,    40,    19,    61,    25,   109,    -9,
     409,   459,   409,    28,   125,   131,    34,  -303,   361,   361,
     361,   361,   361,  -303,  -303,  -303,    53,   404,    97,   222,
    -303,  -303,   141,   143,  -303,  -303,  -303,  -303,    53,     0,
    -303,   447,   157,    -1,   500,  -303,  -303,   383,    -9,  -303,
     361,   361,   383,   361,  -303,  -303,  -303,   175,  -303,   185,
    -303,   130,  -303,  -303,  -303,   169,   170,    -7,   217,   218,
      -9,    -9,   152,    -9,  -303,  -303,  -303,   187,  -303,  -303,
    -303,  -303,  -303,  -303,   193,  -303,  -303,  -303,  -303,  -303,
    -303,  -303,    -9,    -9,    -9,   -19,  -303,   136,  -303,   551,
     152,  -303,  -303,  -303,  -303,   470,   494,   194,   206,  -303,
    -303,   383,   361,   361,   361,   361,   361,   361,   361,   361,
     361,   361,   361,   361,   361,   361,   361,   361,   383,    -9,
     383,   361,   361,   459,  -303,  -303,  -303,  -303,  -303,   519,
     -32,   519,  -303,   204,   209,   519,  -303,   459,   409,   409,
    -303,   434,   152,   262,   224,  -303,   158,  -303,  -303,   225,
     434,   409,  -303,  -303,  -303,    38,   459,   167,   108,   108,
      28,  -303,    -9,   152,  -303,  -303,  -303,   227,  -303,   361,
    -303,   361,   282,    97,    97,    97,    97,    97,    97,   222,
     222,   222,  -303,  -303,  -303,  -303,  -303,  -303,   236,  -303,
      53,  -303,   283,   478,   519,   245,    37,  -303,   173,  -303,
     361,  -303,  -303,   361,  -303,  -303,  -303,  -303,   -10,   278,
    -303,   244,  -303,    -7,    -9,   409,  -303,  -303,  -303,  -303,
     152,  -303,   249,  -303,  -303,  -303,   551,   519,  -303,   383,
    -303,   383,   361,   361,   459,  -303,   297,   459,   383,   519,
     519,   434,   290,   459,   152,  -303,  -303,  -303,  -303,  -303,
    -303,   152,  -303,  -303,  -303,   519,   519,  -303,   383,  -303,
     307,  -303,  -303,  -303,   409,   261,  -303,   179,  -303,  -303,
    -303,   263,  -303,  -303,   459,   259,  -303,  -303,    -7,   265,
    -303
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,   185,     1,     0,     0,     4,   177,     0,
       5,     0,     0,     3,     0,     0,     0,     0,     0,     0,
       0,     0,     7,     9,    11,    13,    15,     0,     0,     0,
       0,     0,    68,     6,     0,    26,     0,   161,   164,   165,
     163,   162,   166,     0,   167,   178,    18,   173,   171,   174,
     172,     0,   170,   169,     0,   168,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    83,     0,     0,    96,   101,
     170,   121,     2,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   151,     0,     0,
       0,     0,   185,   183,   179,   182,   146,     0,   130,   134,
     141,   145,     0,   176,   147,   148,   149,   150,   122,     0,
     176,     0,     0,     0,     0,    98,    17,   185,     0,   104,
       0,     0,     0,   185,     8,    19,    10,     0,    12,     0,
      14,     0,    16,    69,    27,     0,     0,   185,     0,    47,
       0,     0,     0,     0,   180,   181,   184,     0,    24,    36,
      37,    42,    33,    41,   167,    28,    29,    30,    31,    32,
      20,    22,     0,     0,     0,     0,    75,     0,    81,     0,
       0,    88,   144,   142,   143,     0,   159,     0,   156,   157,
     155,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   185,     0,     0,
       0,     0,     0,     0,    84,    85,    86,   103,   175,    87,
       0,   105,   100,     0,   118,   119,   117,     0,     0,     0,
      43,     0,     0,     0,    51,    55,     0,    53,    59,    54,
       0,     0,    34,    35,    38,     0,     0,     0,     0,     0,
       0,    74,     0,     0,    73,    72,    70,     0,   154,     0,
     153,     0,    89,   129,   128,   124,   125,   127,   126,   133,
     131,   132,   139,   135,   136,   137,   138,   140,     0,    99,
     123,    93,     0,     0,    94,   112,     0,   107,     0,   110,
       0,   102,    97,     0,    21,    23,    25,    49,     0,     0,
      62,   167,    45,   185,     0,     0,    46,    48,    39,    40,
       0,    79,     0,    76,    82,    77,     0,   160,   158,     0,
     152,     0,     0,     0,     0,    91,     0,     0,     0,   106,
     120,     0,     0,   185,     0,    56,    52,    57,    60,    58,
      78,     0,    71,    90,    95,   115,   116,   113,     0,   108,
       0,   111,   109,    50,     0,    61,    64,     0,    66,    63,
      80,     0,    92,    44,   185,     0,   114,    65,   185,     0,
      67
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -303,  -303,  -303,   184,   321,   267,   268,   269,   270,   260,
    -303,  -303,  -303,  -303,   276,   -66,   -60,  -219,  -303,   211,
    -303,    -4,  -303,    70,  -303,    73,  -303,  -303,    -6,  -303,
     279,    69,   -47,  -303,   134,   220,    11,  -303,    68,    26,
    -303,  -303,    67,  -302,    72,  -303,  -303,   199,  -303,   327,
    -303,   271,   394,   -57,    18,  -303,  -303,  -303,   133,   -11,
      10,   378,   382,  -117,   341,    -2,   -12,  -303,  -303,  -303,
      44,    64,  -303,    -3
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     2,     6,     9,   245,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    34,   147,   148,   149,   150,   151,
     288,   223,   224,   225,   226,   227,   289,   345,   346,    31,
      32,   246,    84,   165,   166,   167,    64,   204,    65,    96,
     210,   276,   277,   278,   279,   340,   272,   213,   214,    67,
     109,   176,    98,    99,   100,   101,   177,   178,   179,   152,
     153,   102,    68,   228,    69,   103,   104,   105,   155,   156,
     106,   107,   159,   216
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
       7,   207,   287,    10,    36,    46,   116,    85,    71,     1,
      33,   296,    35,    37,    44,   160,    52,    55,    70,   222,
     198,   347,   161,    14,   202,    16,    43,    18,    19,    20,
       3,   280,   162,    18,    19,    20,   163,   164,   281,    47,
      48,    49,    50,   240,    71,   171,    66,   241,   315,    71,
      53,    71,   347,   321,    70,     4,   110,   117,   110,    70,
     322,   117,   125,   199,   127,    14,     8,    86,     8,    18,
      19,    20,   113,    37,    44,    35,     8,   134,   154,    37,
     154,   168,    66,     8,   108,    12,   129,    66,    13,   180,
      38,    39,    40,    41,     8,     5,   117,    11,    42,   316,
       8,    12,   343,     8,   298,    71,   172,   173,   174,    72,
      71,   118,    45,   119,   206,    70,   208,    18,    19,    20,
      70,    75,   121,    81,   157,   157,   157,    73,    74,   232,
     233,   259,   260,   261,   229,   208,     8,   275,    37,    37,
      44,    10,    76,    66,   158,   158,   158,   188,    66,   189,
     190,   284,   234,   118,    77,   119,   120,   122,   285,   286,
     168,   238,   239,  -176,   121,  -176,  -176,    82,    44,    71,
     299,   297,    78,    83,  -176,    79,    80,   328,   123,    70,
     247,    38,    39,    40,    41,   205,    71,   169,    71,    42,
     212,   301,   302,    79,   219,   170,    70,   110,    70,   242,
     243,    37,   136,   137,   138,   139,   197,    66,  -168,   262,
     263,   264,   265,   266,   267,    37,   154,   154,   201,   154,
     291,   294,   295,   217,    66,   270,    66,     8,   154,   154,
     242,   300,   290,   218,    37,   329,   317,   318,   168,   221,
     304,    44,   317,   355,   230,   231,   236,   157,   337,   252,
     275,   275,  -161,   305,    14,    15,    16,   275,    18,    19,
      20,   157,   157,   157,   250,   157,   269,   158,   271,   251,
     282,   191,   283,   292,   157,   157,   192,   193,   194,   195,
     157,   158,   158,   158,   353,   158,   293,   -57,   275,   306,
     327,   208,   208,   154,   158,   158,   309,    71,    44,    71,
     158,   196,   310,   311,   314,   323,    71,    70,   324,    70,
     330,   338,    37,   331,    37,    37,    70,   344,   352,   154,
     348,    37,    44,   354,   358,   356,    71,   235,    97,    44,
     111,   360,    21,   114,   349,    66,    70,    66,   132,   157,
     124,   350,   154,   126,    66,   128,   220,   130,   357,   140,
     141,   348,    37,   131,   359,   229,   208,   133,   157,   158,
     157,   157,   175,   325,    66,   157,   326,   157,    93,   144,
     145,   146,     8,    95,   303,   332,    87,   333,   158,   334,
     158,   158,   237,   339,   308,   158,   342,   158,   157,   341,
     115,   209,   211,    56,   215,    57,   268,    54,   157,    58,
      51,   112,    59,    53,    60,     0,   351,    61,   158,    62,
       0,    63,    88,    89,    90,     0,     0,   181,   158,     0,
       0,    47,    48,    49,    50,     0,    91,   135,     0,     0,
      92,     0,    93,    45,    94,     0,     8,    95,    38,    39,
      40,    41,   136,   137,   138,   139,    42,   182,   183,   184,
     185,   186,   187,     0,     0,    45,     0,     0,     8,     0,
       0,   140,   141,    38,    39,    40,    41,   200,   215,   142,
       0,    42,   273,   274,   143,     0,     0,     0,     0,     0,
      93,   144,   145,   146,     8,    95,   140,   141,     0,     0,
     182,   183,   184,   185,   186,   187,     0,     0,     0,   143,
     312,   313,     0,     0,     0,    93,   144,   145,   146,     8,
      95,   140,   141,   182,   183,   184,   185,   186,   187,     0,
     307,   182,   183,   184,   185,   186,   187,   203,     0,     0,
      93,   144,   145,   146,     8,    95,   248,   182,   183,   184,
     185,   186,   187,   182,   183,   184,   185,   186,   187,     0,
       0,   319,     0,   249,   320,    14,    15,    16,    17,    18,
      19,    20,   182,   183,   184,   185,   186,   187,   244,    14,
      15,    16,    17,    18,    19,    20,   253,   254,   255,   256,
     257,   258,     0,   335,   336
};

static const yytype_int16 yycheck[] =
{
       3,   118,   221,     5,    15,    17,    11,    54,    20,     3,
      12,   230,    14,    15,    16,    81,    18,    19,    20,    26,
      20,   323,    82,     4,    25,     6,    16,     8,     9,    10,
      75,    63,     4,     8,     9,    10,     8,     9,    70,    38,
      39,    40,    41,    62,    56,    11,    20,    66,    11,    61,
      42,    63,   354,    63,    56,     0,    58,    62,    60,    61,
      70,    62,    74,    63,    75,     4,    75,    56,    75,     8,
       9,    10,    61,    75,    76,    77,    75,    79,    80,    81,
      82,    83,    56,    75,    58,    63,    76,    61,    66,    92,
      29,    30,    31,    32,    75,    65,    62,    62,    37,    62,
      75,    63,   321,    75,    66,   117,    88,    89,    90,    58,
     122,    58,    72,    60,   117,   117,   118,     8,     9,    10,
     122,    62,    69,    48,    80,    81,    82,    62,    63,   140,
     141,   188,   189,   190,   137,   137,    75,   203,   140,   141,
     142,   143,    62,   117,    80,    81,    82,    50,   122,    52,
      53,   217,   142,    58,    62,    60,    61,    64,   218,   219,
     162,   163,   164,    58,    69,    60,    61,    48,   170,   181,
     236,   231,    62,    65,    69,    63,    64,   294,    65,   181,
     170,    29,    30,    31,    32,   117,   198,    62,   200,    37,
     122,   238,   239,    63,    64,    64,   198,   199,   200,    63,
      64,   203,    33,    34,    35,    36,    65,   181,    65,   191,
     192,   193,   194,   195,   196,   217,   218,   219,    61,   221,
     222,    63,    64,    48,   198,   199,   200,    75,   230,   231,
      63,    64,   222,    48,   236,   295,    63,    64,   240,    69,
     242,   243,    63,    64,    27,    27,    59,   203,   314,   181,
     316,   317,    59,   243,     4,     5,     6,   323,     8,     9,
      10,   217,   218,   219,    70,   221,   198,   203,   200,    63,
      66,    49,    63,    11,   230,   231,    54,    55,    56,    57,
     236,   217,   218,   219,   344,   221,    62,    62,   354,    62,
     293,   293,   294,   295,   230,   231,    14,   309,   300,   311,
     236,    79,    66,    20,    59,    27,   318,   309,    64,   311,
     300,    14,   314,    64,   316,   317,   318,    27,    11,   321,
     323,   323,   324,    62,    65,    62,   338,   143,    57,   331,
      59,    66,    11,    62,   324,   309,   338,   311,    78,   295,
      73,   331,   344,    75,   318,    76,   135,    77,   354,    52,
      53,   354,   354,    77,   358,   358,   358,    78,   314,   295,
     316,   317,    91,   293,   338,   321,   293,   323,    71,    72,
      73,    74,    75,    76,   240,   306,    15,   309,   314,   311,
     316,   317,   162,   316,   251,   321,   318,   323,   344,   317,
      63,   120,   121,    10,   123,    12,   197,    19,   354,    16,
      18,    60,    19,    42,    21,    -1,   338,    24,   344,    26,
      -1,    28,    51,    52,    53,    -1,    -1,    13,   354,    -1,
      -1,    38,    39,    40,    41,    -1,    65,    18,    -1,    -1,
      69,    -1,    71,    72,    73,    -1,    75,    76,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    43,    44,    45,
      46,    47,    48,    -1,    -1,    72,    -1,    -1,    75,    -1,
      -1,    52,    53,    29,    30,    31,    32,    20,   197,    60,
      -1,    37,   201,   202,    65,    -1,    -1,    -1,    -1,    -1,
      71,    72,    73,    74,    75,    76,    52,    53,    -1,    -1,
      43,    44,    45,    46,    47,    48,    -1,    -1,    -1,    65,
      22,    23,    -1,    -1,    -1,    71,    72,    73,    74,    75,
      76,    52,    53,    43,    44,    45,    46,    47,    48,    -1,
     249,    43,    44,    45,    46,    47,    48,    27,    -1,    -1,
      71,    72,    73,    74,    75,    76,    66,    43,    44,    45,
      46,    47,    48,    43,    44,    45,    46,    47,    48,    -1,
      -1,   280,    -1,    59,   283,     4,     5,     6,     7,     8,
       9,    10,    43,    44,    45,    46,    47,    48,    17,     4,
       5,     6,     7,     8,     9,    10,   182,   183,   184,   185,
     186,   187,    -1,   312,   313
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    82,    75,     0,    65,    83,   154,    75,    84,
     146,    62,    63,    66,     4,     5,     6,     7,     8,     9,
      10,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,   110,   111,   146,    95,   146,   140,   146,    29,    30,
      31,    32,    37,   141,   146,    72,   147,    38,    39,    40,
      41,   143,   146,    42,   142,   146,    10,    12,    16,    19,
      21,    24,    26,    28,   117,   119,   120,   130,   143,   145,
     146,   147,    58,    62,    63,    62,    62,    62,    62,    63,
      64,    48,    48,    65,   113,   113,   117,    15,    51,    52,
      53,    65,    69,    71,    73,    76,   120,   132,   133,   134,
     135,   136,   142,   146,   147,   148,   151,   152,   120,   131,
     146,   132,   145,   117,   132,   130,    11,    62,    58,    60,
      61,    69,    64,    65,    86,   147,    87,   140,    88,   141,
      89,    95,    90,   111,   146,    18,    33,    34,    35,    36,
      52,    53,    60,    65,    72,    73,    74,    96,    97,    98,
      99,   100,   140,   141,   146,   149,   150,   151,   152,   153,
      96,    97,     4,     8,     9,   114,   115,   116,   146,    62,
      64,    11,   135,   135,   135,   132,   132,   137,   138,   139,
     154,    13,    43,    44,    45,    46,    47,    48,    50,    52,
      53,    49,    54,    55,    56,    57,    79,    65,    20,    63,
      20,    61,    25,    27,   118,   119,   154,   144,   146,   132,
     121,   132,   119,   128,   129,   132,   154,    48,    48,    64,
     100,    69,    26,   102,   103,   104,   105,   106,   144,   154,
      27,    27,   140,   140,   141,    84,    59,   116,   146,   146,
      62,    66,    63,    64,    17,    85,   112,   141,    66,    59,
      70,    63,   119,   133,   133,   133,   133,   133,   133,   134,
     134,   134,   135,   135,   135,   135,   135,   135,   128,   119,
     120,   119,   127,   132,   132,    96,   122,   123,   124,   125,
      63,    70,    66,    63,    96,    97,    97,    98,   101,   107,
     141,   146,    11,    62,    63,    64,    98,    97,    66,    96,
      64,   113,   113,   115,   146,   141,    62,   132,   139,    14,
      66,    20,    22,    23,    59,    11,    62,    63,    64,   132,
     132,    63,    70,    27,    64,   104,   106,   154,   144,    97,
     141,    64,   112,   119,   119,   132,   132,    96,    14,   123,
     126,   125,   119,    98,    27,   108,   109,   124,   154,   141,
     141,   119,    11,    97,    62,    64,    62,   109,    65,   102,
      66
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    81,    82,    83,    83,    84,    84,    85,    85,    86,
      86,    87,    87,    88,    88,    89,    89,    90,    91,    91,
      92,    92,    93,    93,    94,    94,    95,    95,    96,    96,
      96,    96,    96,    96,    96,    96,    97,    97,    97,    98,
      98,    98,    99,    99,   100,   100,   100,   100,   100,   101,
     101,   102,   102,   102,   102,   103,   103,   104,   104,   105,
     105,   106,   107,   107,   108,   108,   109,   109,   110,   110,
     111,   111,   112,   112,   113,   114,   114,   115,   115,   115,
     115,   116,   116,   117,   117,   118,   118,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   120,   120,   120,   120,   121,   121,   122,   122,   123,
     124,   124,   125,   125,   126,   127,   127,   128,   128,   129,
     129,   130,   131,   131,   132,   132,   132,   132,   132,   132,
     132,   133,   133,   133,   133,   134,   134,   134,   134,   134,
     134,   134,   135,   135,   135,   135,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   137,   137,   138,   138,   139,
     139,   140,   141,   141,   141,   141,   141,   141,   142,   142,
     143,   143,   143,   143,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     6,     3,     1,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     3,     2,     3,
       4,     5,     4,     5,     4,     5,     1,     3,     1,     1,
       1,     1,     1,     1,     2,     2,     1,     1,     2,     3,
       3,     1,     1,     2,     6,     3,     3,     1,     3,     1,
       3,     1,     3,     1,     1,     1,     3,     1,     3,     1,
       3,     4,     1,     3,     1,     3,     1,     5,     1,     3,
       5,     7,     1,     1,     3,     1,     3,     3,     4,     3,
       5,     1,     3,     1,     3,     1,     1,     3,     3,     4,
       6,     5,     7,     4,     4,     6,     1,     4,     2,     4,
       3,     1,     4,     3,     2,     1,     3,     1,     3,     3,
       1,     3,     1,     3,     3,     3,     3,     1,     1,     1,
       3,     1,     1,     3,     3,     3,     3,     3,     3,     3,
       1,     3,     3,     3,     1,     3,     3,     3,     3,     3,
       3,     1,     2,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     4,     3,     3,     1,     1,     1,     3,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
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
#line 1933 "parser.tab.c"
    break;

  case 3: /* program_headingopt: L_PAREN identifier_list R_PAREN  */
#line 143 "parser/parser.y"
                                    {
      (yyval.node) = create_heading_node((yyvsp[-1].node), create_location((yyloc)));
    }
#line 1941 "parser.tab.c"
    break;

  case 5: /* identifier_list: identifier  */
#line 149 "parser/parser.y"
               {
      (yyval.node) = create_identifier_list_node((yyvsp[0].node), create_location((yyloc)));
    }
#line 1949 "parser.tab.c"
    break;

  case 6: /* identifier_list: identifier_list COMMA identifier  */
#line 152 "parser/parser.y"
                                     {
      (yyval.node) = append_identifier_list_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 1957 "parser.tab.c"
    break;

  case 7: /* block: block1  */
#line 157 "parser/parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 1963 "parser.tab.c"
    break;

  case 8: /* block: label_declaration SEMICOLON block1  */
#line 158 "parser/parser.y"
                                       {
      (yyval.node) = add_labels_to_block((yyvsp[0].node), (yyvsp[-2].node));
    }
#line 1971 "parser.tab.c"
    break;

  case 9: /* block1: block2  */
#line 163 "parser/parser.y"
            { (yyval.node) = (yyvsp[0].node); }
#line 1977 "parser.tab.c"
    break;

  case 10: /* block1: constant_declaration SEMICOLON block2  */
#line 164 "parser/parser.y"
                                          {
    (yyval.node) = add_constants_to_block((yyvsp[0].node), (yyvsp[-2].node));
  }
#line 1985 "parser.tab.c"
    break;

  case 11: /* block2: block3  */
#line 169 "parser/parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 1991 "parser.tab.c"
    break;

  case 12: /* block2: type_declaration SEMICOLON block3  */
#line 170 "parser/parser.y"
                                      {
     (yyval.node) = add_types_to_block((yyvsp[0].node), (yyvsp[-2].node));
  }
#line 1999 "parser.tab.c"
    break;

  case 13: /* block3: block4  */
#line 175 "parser/parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 2005 "parser.tab.c"
    break;

  case 14: /* block3: variable_declaration SEMICOLON block4  */
#line 176 "parser/parser.y"
                                          {
      (yyval.node) = add_variables_to_block((yyvsp[0].node), (yyvsp[-2].node));
    }
#line 2013 "parser.tab.c"
    break;

  case 15: /* block4: block5  */
#line 181 "parser/parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 2019 "parser.tab.c"
    break;

  case 16: /* block4: proc_and_func_declaration SEMICOLON block5  */
#line 182 "parser/parser.y"
                                               {
      (yyval.node) = add_procs_funcs_to_block((yyvsp[0].node), (yyvsp[-2].node));
    }
#line 2027 "parser.tab.c"
    break;

  case 17: /* block5: BEGIN_TOK statement_list END  */
#line 187 "parser/parser.y"
                                 {
      (yyval.node) = create_block_node(NULL, NULL, NULL, NULL, NULL, (yyvsp[-1].node), create_location((yyloc)));
    }
#line 2035 "parser.tab.c"
    break;

  case 18: /* label_declaration: LABEL unsigned_integer  */
#line 192 "parser/parser.y"
                           { (yyval.node) = create_label_declaration_node((yyvsp[0].node), create_location((yyloc))); }
#line 2041 "parser.tab.c"
    break;

  case 19: /* label_declaration: label_declaration COMMA unsigned_integer  */
#line 193 "parser/parser.y"
                                             {
      (yyval.node) = append_label_declaration((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2049 "parser.tab.c"
    break;

  case 20: /* constant_declaration: CONST constid EQ constant  */
#line 198 "parser/parser.y"
                              {
      (yyval.node) = create_constant_declaration_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2057 "parser.tab.c"
    break;

  case 21: /* constant_declaration: constant_declaration SEMICOLON constid EQ constant  */
#line 201 "parser/parser.y"
                                                       {
      (yyval.node) = append_constant_declaration((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2065 "parser.tab.c"
    break;

  case 22: /* type_declaration: TYPE typeid EQ type  */
#line 206 "parser/parser.y"
                        { (yyval.node) = create_type_declaration_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2071 "parser.tab.c"
    break;

  case 23: /* type_declaration: type_declaration SEMICOLON typeid EQ type  */
#line 207 "parser/parser.y"
                                              {
      (yyval.node) = append_type_declaration((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2079 "parser.tab.c"
    break;

  case 24: /* variable_declaration: VAR variableid_list COLON type  */
#line 212 "parser/parser.y"
                                   { (yyval.node) = create_variable_declaration_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2085 "parser.tab.c"
    break;

  case 25: /* variable_declaration: variable_declaration SEMICOLON variableid_list COLON type  */
#line 213 "parser/parser.y"
                                                              {
      (yyval.node) = append_variable_declaration((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2093 "parser.tab.c"
    break;

  case 26: /* variableid_list: identifier  */
#line 218 "parser/parser.y"
                { (yyval.node) = create_variable_identifier_list_node((yyvsp[0].node), create_location((yyloc))); }
#line 2099 "parser.tab.c"
    break;

  case 27: /* variableid_list: variableid_list COMMA identifier  */
#line 219 "parser/parser.y"
                                     {
      (yyval.node) = append_variable_identifier_list((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2107 "parser.tab.c"
    break;

  case 28: /* constant: integer_literal  */
#line 224 "parser/parser.y"
                    {
      (yyval.node) = create_constant_literal((yyvsp[0].node), create_location((yyloc)));
    }
#line 2115 "parser.tab.c"
    break;

  case 29: /* constant: real_literal  */
#line 227 "parser/parser.y"
                 {
      (yyval.node) = create_constant_literal((yyvsp[0].node), create_location((yyloc)));
    }
#line 2123 "parser.tab.c"
    break;

  case 30: /* constant: string_literal  */
#line 230 "parser/parser.y"
                   {
      (yyval.node) = create_constant_literal((yyvsp[0].node), create_location((yyloc)));
    }
#line 2131 "parser.tab.c"
    break;

  case 31: /* constant: char_literal  */
#line 233 "parser/parser.y"
                 {
      (yyval.node) = create_constant_literal((yyvsp[0].node), create_location((yyloc)));
    }
#line 2139 "parser.tab.c"
    break;

  case 32: /* constant: boolean_literal  */
#line 236 "parser/parser.y"
                    {
      (yyval.node) = create_constant_literal((yyvsp[0].node), create_location((yyloc)));
    }
#line 2147 "parser.tab.c"
    break;

  case 33: /* constant: constid  */
#line 239 "parser/parser.y"
            { (yyval.node) = create_constant_identifier((yyvsp[0].node), create_location((yyloc))); }
#line 2153 "parser.tab.c"
    break;

  case 34: /* constant: PLUS constid  */
#line 240 "parser/parser.y"
                 { (yyval.node) = create_constant_signed_identifier((yyvsp[0].node), "+", create_location((yyloc))); }
#line 2159 "parser.tab.c"
    break;

  case 35: /* constant: MINUS constid  */
#line 241 "parser/parser.y"
                  { (yyval.node) = create_constant_signed_identifier((yyvsp[0].node), "-", create_location((yyloc))); }
#line 2165 "parser.tab.c"
    break;

  case 36: /* type: simple_type  */
#line 244 "parser/parser.y"
                {
      (yyval.node) = create_simple_type_node((yyvsp[0].node), create_location((yyloc)));
    }
#line 2173 "parser.tab.c"
    break;

  case 37: /* type: structured_type  */
#line 247 "parser/parser.y"
                    {
      (yyval.node) = create_structure_type_node((yyvsp[0].node), create_location((yyloc)));
    }
#line 2181 "parser.tab.c"
    break;

  case 38: /* type: CARET typeid  */
#line 250 "parser/parser.y"
                 {
      (yyval.node) = create_pointer_type_node((yyvsp[0].node), create_location((yyloc)));
    }
#line 2189 "parser.tab.c"
    break;

  case 39: /* simple_type: L_PAREN identifier_list R_PAREN  */
#line 255 "parser/parser.y"
                                     { (yyval.node) = create_enumerated_type_node((yyvsp[-1].node), create_location((yyloc))); }
#line 2195 "parser.tab.c"
    break;

  case 40: /* simple_type: constant DOTDOT constant  */
#line 256 "parser/parser.y"
                             {
      (yyval.node) = create_constant_range_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2203 "parser.tab.c"
    break;

  case 41: /* simple_type: typeid  */
#line 259 "parser/parser.y"
           {
      (yyval.node) = (yyvsp[0].node);
    }
#line 2211 "parser.tab.c"
    break;

  case 42: /* structured_type: unpacked_structured_type  */
#line 264 "parser/parser.y"
                             {
      (yyval.node) = (yyvsp[0].node);
    }
#line 2219 "parser.tab.c"
    break;

  case 43: /* structured_type: PACKED unpacked_structured_type  */
#line 267 "parser/parser.y"
                                      {
      (yyval.node) = create_packed_type((yyvsp[0].node), create_location((yyloc)));
    }
#line 2227 "parser.tab.c"
    break;

  case 44: /* unpacked_structured_type: ARRAY L_BRACKET index_list R_BRACKET OF type  */
#line 272 "parser/parser.y"
                                                   {
        (yyval.node) = create_array_type_node((yyvsp[-3].node), (yyvsp[0].node), create_location((yyloc)));
      }
#line 2235 "parser.tab.c"
    break;

  case 45: /* unpacked_structured_type: RECORD field_list END  */
#line 275 "parser/parser.y"
                            {
        (yyval.node) = create_record_type_node((yyvsp[-1].node), create_location((yyloc)));
      }
#line 2243 "parser.tab.c"
    break;

  case 46: /* unpacked_structured_type: SET OF simple_type  */
#line 278 "parser/parser.y"
                         {
        (yyval.node) = create_set_of_type_node((yyvsp[0].node), create_location((yyloc)));
      }
#line 2251 "parser.tab.c"
    break;

  case 47: /* unpacked_structured_type: FILE_TOK  */
#line 281 "parser/parser.y"
               {
        (yyval.node) = create_file_of_type_node(NULL, create_location((yyloc)));
      }
#line 2259 "parser.tab.c"
    break;

  case 48: /* unpacked_structured_type: FILE_TOK OF type  */
#line 284 "parser/parser.y"
                       {
        (yyval.node) = create_file_of_type_node((yyvsp[0].node), create_location((yyloc)));
      }
#line 2267 "parser.tab.c"
    break;

  case 49: /* index_list: simple_type  */
#line 289 "parser/parser.y"
                { 
      (yyval.node) = create_index_list_start((yyvsp[0].node), create_location((yyloc))); 
    }
#line 2275 "parser.tab.c"
    break;

  case 50: /* index_list: index_list COMMA simple_type  */
#line 292 "parser/parser.y"
                                 {
      (yyval.node) = append_index_to_list((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2283 "parser.tab.c"
    break;

  case 51: /* field_list: fixed_part  */
#line 297 "parser/parser.y"
               { (yyval.node) = create_field_list((yyvsp[0].node), NULL, create_location((yyloc))); }
#line 2289 "parser.tab.c"
    break;

  case 52: /* field_list: fixed_part SEMICOLON variant_part  */
#line 298 "parser/parser.y"
                                      { (yyval.node) = create_field_list((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2295 "parser.tab.c"
    break;

  case 53: /* field_list: variant_part  */
#line 299 "parser/parser.y"
                 { (yyval.node) = create_field_list(NULL, (yyvsp[0].node), create_location((yyloc))); }
#line 2301 "parser.tab.c"
    break;

  case 55: /* fixed_part: record_field  */
#line 303 "parser/parser.y"
                 { (yyval.node) = create_fixed_part_node(NULL, (yyvsp[0].node), create_location((yyloc))); }
#line 2307 "parser.tab.c"
    break;

  case 56: /* fixed_part: fixed_part SEMICOLON record_field  */
#line 304 "parser/parser.y"
                                      { (yyval.node) = create_fixed_part_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2313 "parser.tab.c"
    break;

  case 58: /* record_field: fieldid_list COLON type  */
#line 308 "parser/parser.y"
                            { (yyval.node) = create_record_field_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2319 "parser.tab.c"
    break;

  case 59: /* fieldid_list: fieldid  */
#line 311 "parser/parser.y"
            { (yyval.node) = create_field_identifier_list_node(NULL, (yyvsp[0].node), create_location((yyloc))); }
#line 2325 "parser.tab.c"
    break;

  case 60: /* fieldid_list: fieldid_list COMMA fieldid  */
#line 312 "parser/parser.y"
                               { (yyval.node) = create_field_identifier_list_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2331 "parser.tab.c"
    break;

  case 61: /* variant_part: CASE tag_field OF variant_list  */
#line 315 "parser/parser.y"
                                   { (yyval.node) = create_case_of_variant_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2337 "parser.tab.c"
    break;

  case 62: /* tag_field: typeid  */
#line 318 "parser/parser.y"
           { (yyval.node) = create_tag_field_node(NULL, (yyvsp[0].node), create_location((yyloc))); }
#line 2343 "parser.tab.c"
    break;

  case 63: /* tag_field: identifier COLON typeid  */
#line 319 "parser/parser.y"
                            { (yyval.node) = create_tag_field_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2349 "parser.tab.c"
    break;

  case 64: /* variant_list: variant  */
#line 322 "parser/parser.y"
            { (yyval.node) = append_variant_list(NULL, (yyvsp[0].node), create_location((yyloc))); }
#line 2355 "parser.tab.c"
    break;

  case 65: /* variant_list: variant_list SEMICOLON variant  */
#line 323 "parser/parser.y"
                                   {
      (yyval.node) = append_variant_list((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2363 "parser.tab.c"
    break;

  case 67: /* variant: case_label_list COLON L_PAREN field_list R_PAREN  */
#line 329 "parser/parser.y"
                                                     {
      (yyval.node) = create_variant_node((yyvsp[-4].node), (yyvsp[-1].node), create_location((yyloc)));
    }
#line 2371 "parser.tab.c"
    break;

  case 68: /* proc_and_func_declaration: proc_or_func  */
#line 334 "parser/parser.y"
                 { (yyval.node) = create_proc_and_func_declarations_node((yyvsp[0].node), create_location((yyloc))); }
#line 2377 "parser.tab.c"
    break;

  case 69: /* proc_and_func_declaration: proc_and_func_declaration SEMICOLON proc_or_func  */
#line 335 "parser/parser.y"
                                                     {
      (yyval.node) = append_proc_and_func_declarations((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2385 "parser.tab.c"
    break;

  case 70: /* proc_or_func: PROCEDURE procid parameters SEMICOLON block_or_forward  */
#line 340 "parser/parser.y"
                                                           { /* identifier of func/proc declaration */ 
      (yyval.node) = create_proc_declaration_node((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2393 "parser.tab.c"
    break;

  case 71: /* proc_or_func: FUNCTION funcid parameters COLON typeid SEMICOLON block_or_forward  */
#line 343 "parser/parser.y"
                                                                       {
      (yyval.node) = create_func_declaration_node((yyvsp[-5].node), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2401 "parser.tab.c"
    break;

  case 72: /* block_or_forward: block  */
#line 348 "parser/parser.y"
          { (yyval.node) = (yyvsp[0].node); }
#line 2407 "parser.tab.c"
    break;

  case 73: /* block_or_forward: FORWARD  */
#line 349 "parser/parser.y"
             { (yyval.node) = create_forward_declaration_node(create_location((yyloc))); }
#line 2413 "parser.tab.c"
    break;

  case 74: /* parameters: L_PAREN formal_parameter_list R_PAREN  */
#line 352 "parser/parser.y"
                                         { (yyval.node) = create_parameters_node((yyvsp[-1].node), create_location((yyloc))); }
#line 2419 "parser.tab.c"
    break;

  case 75: /* formal_parameter_list: formal_parameter_section  */
#line 355 "parser/parser.y"
                             { (yyval.node) = create_formal_parameters_list_node(NULL, (yyvsp[0].node), create_location((yyloc))); }
#line 2425 "parser.tab.c"
    break;

  case 76: /* formal_parameter_list: formal_parameter_list SEMICOLON formal_parameter_section  */
#line 356 "parser/parser.y"
                                                             {
      (yyval.node) = create_formal_parameters_list_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2433 "parser.tab.c"
    break;

  case 77: /* formal_parameter_section: parameterid_list COLON typeid  */
#line 361 "parser/parser.y"
                                  { 
        (yyval.node) = create_formal_parameter_section_node(PARAM_VALUE, (yyvsp[-2].node), (yyvsp[0].node), NULL, NULL, create_location((yyloc))); 
      }
#line 2441 "parser.tab.c"
    break;

  case 78: /* formal_parameter_section: VAR parameterid_list COLON typeid  */
#line 364 "parser/parser.y"
                                        { 
        (yyval.node) = create_formal_parameter_section_node(PARAM_VAR, (yyvsp[-2].node), (yyvsp[0].node), NULL, NULL, create_location((yyloc))); 
      }
#line 2449 "parser.tab.c"
    break;

  case 79: /* formal_parameter_section: PROCEDURE identifier parameters  */
#line 367 "parser/parser.y"
                                      { 
        ASTNode* single_id = create_parameter_identifier_list_node(NULL, (yyvsp[-1].node), create_location((yylsp[-1])));
        (yyval.node) = create_formal_parameter_section_node(PARAM_PROCEDURE, single_id, NULL, (yyvsp[0].node), NULL, create_location((yyloc))); 
      }
#line 2458 "parser.tab.c"
    break;

  case 80: /* formal_parameter_section: FUNCTION identifier parameters COLON typeid  */
#line 371 "parser/parser.y"
                                                  { 
        ASTNode* single_id = create_parameter_identifier_list_node(NULL, (yyvsp[-3].node), create_location((yylsp[-3])));
        (yyval.node) = create_formal_parameter_section_node(PARAM_FUNCTION, single_id, NULL, (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); 
      }
#line 2467 "parser.tab.c"
    break;

  case 81: /* parameterid_list: identifier  */
#line 377 "parser/parser.y"
                { (yyval.node) = create_parameter_identifier_list_node(NULL, (yyvsp[0].node), create_location((yyloc))); }
#line 2473 "parser.tab.c"
    break;

  case 82: /* parameterid_list: parameterid_list COMMA identifier  */
#line 378 "parser/parser.y"
                                       { 
      (yyval.node) = create_parameter_identifier_list_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2481 "parser.tab.c"
    break;

  case 83: /* statement_list: statement  */
#line 383 "parser/parser.y"
              { (yyval.node) = create_stmt_list_node((yyvsp[0].node), create_location((yyloc))); }
#line 2487 "parser.tab.c"
    break;

  case 84: /* statement_list: statement_list SEMICOLON optional_statement  */
#line 384 "parser/parser.y"
                                                { (yyval.node) = append_stmt_list((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2493 "parser.tab.c"
    break;

  case 85: /* optional_statement: statement  */
#line 387 "parser/parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 2499 "parser.tab.c"
    break;

  case 87: /* statement: variable ASSIGN expression  */
#line 391 "parser/parser.y"
                               { (yyval.node) = create_assign_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2505 "parser.tab.c"
    break;

  case 88: /* statement: BEGIN_TOK statement_list END  */
#line 392 "parser/parser.y"
                                  { (yyval.node) = create_stmt_list_node((yyvsp[-1].node), create_location((yyloc))); }
#line 2511 "parser.tab.c"
    break;

  case 89: /* statement: IF expression THEN statement  */
#line 393 "parser/parser.y"
                                                       { (yyval.node) = create_if_stmt_node((yyvsp[-2].node), (yyvsp[0].node), NULL, create_location((yyloc))); }
#line 2517 "parser.tab.c"
    break;

  case 90: /* statement: IF expression THEN statement ELSE statement  */
#line 394 "parser/parser.y"
                                                { (yyval.node) = create_if_stmt_node((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2523 "parser.tab.c"
    break;

  case 91: /* statement: CASE expression OF case_list END  */
#line 395 "parser/parser.y"
                                     { (yyval.node) = create_case_stmt_node((yyvsp[-3].node), (yyvsp[-1].node), NULL, create_location((yyloc))); }
#line 2529 "parser.tab.c"
    break;

  case 92: /* statement: CASE expression OF case_list SEMICOLON case_else END  */
#line 396 "parser/parser.y"
                                                         { (yyval.node) = create_case_stmt_with_else_node((yyvsp[-5].node), (yyvsp[-3].node), (yyvsp[-1].node), create_location((yyloc))); }
#line 2535 "parser.tab.c"
    break;

  case 93: /* statement: WHILE expression DO statement  */
#line 397 "parser/parser.y"
                                  { (yyval.node) = create_while_stmt_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2541 "parser.tab.c"
    break;

  case 94: /* statement: REPEAT statement_list UNTIL expression  */
#line 398 "parser/parser.y"
                                           { (yyval.node) = create_repeat_until_stmt_list_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2547 "parser.tab.c"
    break;

  case 95: /* statement: FOR varid ASSIGN for_list DO statement  */
#line 399 "parser/parser.y"
                                           { (yyval.node) = create_for_stmt_node((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2553 "parser.tab.c"
    break;

  case 96: /* statement: procid  */
#line 400 "parser/parser.y"
           { (yyval.node) = create_procedure_call_node((yyvsp[0].node), NULL, create_location((yyloc))); }
#line 2559 "parser.tab.c"
    break;

  case 97: /* statement: procid L_PAREN optional_expression_list R_PAREN  */
#line 401 "parser/parser.y"
                                                    { (yyval.node) = create_procedure_call_node((yyvsp[-3].node), (yyvsp[-1].node), create_location((yyloc))); }
#line 2565 "parser.tab.c"
    break;

  case 98: /* statement: GOTO label  */
#line 402 "parser/parser.y"
               { (yyval.node) = create_goto_label_node((yyvsp[0].node), create_location((yyloc))); }
#line 2571 "parser.tab.c"
    break;

  case 99: /* statement: WITH record_variable_list DO statement  */
#line 403 "parser/parser.y"
                                           { (yyval.node) = create_with_record_list_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2577 "parser.tab.c"
    break;

  case 100: /* statement: label COLON statement  */
#line 404 "parser/parser.y"
                          { (yyval.node) = create_label_stmt_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2583 "parser.tab.c"
    break;

  case 101: /* variable: varid  */
#line 407 "parser/parser.y"
          { (yyval.node) = (yyvsp[0].node); }
#line 2589 "parser.tab.c"
    break;

  case 102: /* variable: variable L_BRACKET subscript_list R_BRACKET  */
#line 408 "parser/parser.y"
                                                { (yyval.node) = create_array_access_node((yyvsp[-3].node), (yyvsp[-1].node), create_location((yyloc))); }
#line 2595 "parser.tab.c"
    break;

  case 103: /* variable: variable DOT fieldid  */
#line 409 "parser/parser.y"
                         { (yyval.node) = create_record_access_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2601 "parser.tab.c"
    break;

  case 104: /* variable: variable CARET  */
#line 410 "parser/parser.y"
                   { (yyval.node) = create_pointer_deref_node((yyvsp[-1].node), create_location((yyloc))); }
#line 2607 "parser.tab.c"
    break;

  case 105: /* subscript_list: expression  */
#line 413 "parser/parser.y"
               { 
        (yyval.node) = create_subscript_list_node((yyvsp[0].node), create_location((yyloc))); 
    }
#line 2615 "parser.tab.c"
    break;

  case 106: /* subscript_list: subscript_list COMMA expression  */
#line 416 "parser/parser.y"
                                    { 
        (yyval.node) = append_subscript_list_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2623 "parser.tab.c"
    break;

  case 107: /* case_list: case_item  */
#line 421 "parser/parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 2629 "parser.tab.c"
    break;

  case 108: /* case_list: case_list SEMICOLON case_item  */
#line 422 "parser/parser.y"
                                  { 
      (yyval.node) = append_case_item((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2637 "parser.tab.c"
    break;

  case 109: /* case_item: case_label_list COLON statement  */
#line 427 "parser/parser.y"
                                    { 
      (yyval.node) = create_case_item_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2645 "parser.tab.c"
    break;

  case 110: /* case_label_list: case_label  */
#line 432 "parser/parser.y"
               { (yyval.node) = create_case_label_list((yyvsp[0].node), create_location((yyloc))); }
#line 2651 "parser.tab.c"
    break;

  case 111: /* case_label_list: case_label_list COMMA case_label  */
#line 433 "parser/parser.y"
                                     { 
      (yyval.node) = append_case_label_list((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2659 "parser.tab.c"
    break;

  case 112: /* case_label: constant  */
#line 438 "parser/parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 2665 "parser.tab.c"
    break;

  case 113: /* case_label: constant DOTDOT constant  */
#line 439 "parser/parser.y"
                             { 
      (yyval.node) = create_constant_range_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2673 "parser.tab.c"
    break;

  case 114: /* case_else: ELSE statement SEMICOLON  */
#line 444 "parser/parser.y"
                             {
      (yyval.node) = create_case_else_node((yyvsp[-1].node), create_location((yyloc)));
    }
#line 2681 "parser.tab.c"
    break;

  case 115: /* for_list: expression TO expression  */
#line 449 "parser/parser.y"
                             { 
      (yyval.node) = create_for_list_node((yyvsp[-2].node), (yyvsp[0].node), false, create_location((yyloc))); 
    }
#line 2689 "parser.tab.c"
    break;

  case 116: /* for_list: expression DOWNTO expression  */
#line 452 "parser/parser.y"
                                 { 
      (yyval.node) = create_for_list_node((yyvsp[-2].node), (yyvsp[0].node), true, create_location((yyloc))); 
    }
#line 2697 "parser.tab.c"
    break;

  case 118: /* optional_expression_list: expression_list  */
#line 458 "parser/parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 2703 "parser.tab.c"
    break;

  case 119: /* expression_list: expression  */
#line 461 "parser/parser.y"
               { (yyval.node) = create_expression_list((yyvsp[0].node), create_location((yyloc))); }
#line 2709 "parser.tab.c"
    break;

  case 120: /* expression_list: expression_list COMMA expression  */
#line 462 "parser/parser.y"
                                     { (yyval.node) = append_expression_list((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2715 "parser.tab.c"
    break;

  case 121: /* label: unsigned_integer  */
#line 465 "parser/parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 2721 "parser.tab.c"
    break;

  case 122: /* record_variable_list: variable  */
#line 468 "parser/parser.y"
             { (yyval.node) = create_record_variable_list_node((yyvsp[0].node), create_location((yyloc))); }
#line 2727 "parser.tab.c"
    break;

  case 123: /* record_variable_list: record_variable_list COMMA variable  */
#line 469 "parser/parser.y"
                                        { 
      (yyval.node) = append_record_variable_list((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2735 "parser.tab.c"
    break;

  case 124: /* expression: expression LT additive_expression  */
#line 474 "parser/parser.y"
                                      { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_LT, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2743 "parser.tab.c"
    break;

  case 125: /* expression: expression LTE additive_expression  */
#line 477 "parser/parser.y"
                                       { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_LTE, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2751 "parser.tab.c"
    break;

  case 126: /* expression: expression EQ additive_expression  */
#line 480 "parser/parser.y"
                                      { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_EQ, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2759 "parser.tab.c"
    break;

  case 127: /* expression: expression NEQ additive_expression  */
#line 483 "parser/parser.y"
                                       { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_NEQ, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2767 "parser.tab.c"
    break;

  case 128: /* expression: expression GTE additive_expression  */
#line 486 "parser/parser.y"
                                       { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_GTE, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2775 "parser.tab.c"
    break;

  case 129: /* expression: expression GT additive_expression  */
#line 489 "parser/parser.y"
                                      { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_GT, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2783 "parser.tab.c"
    break;

  case 130: /* expression: additive_expression  */
#line 492 "parser/parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 2789 "parser.tab.c"
    break;

  case 131: /* additive_expression: additive_expression PLUS multiplicative_expression  */
#line 495 "parser/parser.y"
                                                       { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_PLUS, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2797 "parser.tab.c"
    break;

  case 132: /* additive_expression: additive_expression MINUS multiplicative_expression  */
#line 498 "parser/parser.y"
                                                        { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_MINUS, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2805 "parser.tab.c"
    break;

  case 133: /* additive_expression: additive_expression OR multiplicative_expression  */
#line 501 "parser/parser.y"
                                                     { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_OR, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2813 "parser.tab.c"
    break;

  case 134: /* additive_expression: multiplicative_expression  */
#line 504 "parser/parser.y"
                              { (yyval.node) = (yyvsp[0].node); }
#line 2819 "parser.tab.c"
    break;

  case 135: /* multiplicative_expression: multiplicative_expression TIMES unary_expression  */
#line 507 "parser/parser.y"
                                                     { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_TIMES, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2827 "parser.tab.c"
    break;

  case 136: /* multiplicative_expression: multiplicative_expression DIVIDE unary_expression  */
#line 510 "parser/parser.y"
                                                      { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_DIVIDE, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2835 "parser.tab.c"
    break;

  case 137: /* multiplicative_expression: multiplicative_expression DIV unary_expression  */
#line 513 "parser/parser.y"
                                                   { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_DIV, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2843 "parser.tab.c"
    break;

  case 138: /* multiplicative_expression: multiplicative_expression MOD unary_expression  */
#line 516 "parser/parser.y"
                                                   { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_MOD, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2851 "parser.tab.c"
    break;

  case 139: /* multiplicative_expression: multiplicative_expression AND unary_expression  */
#line 519 "parser/parser.y"
                                                   { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_AND, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2859 "parser.tab.c"
    break;

  case 140: /* multiplicative_expression: multiplicative_expression IN unary_expression  */
#line 522 "parser/parser.y"
                                                  { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_IN, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2867 "parser.tab.c"
    break;

  case 141: /* multiplicative_expression: unary_expression  */
#line 525 "parser/parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2873 "parser.tab.c"
    break;

  case 142: /* unary_expression: PLUS unary_expression  */
#line 528 "parser/parser.y"
                          { 
      (yyval.node) = create_unary_expression(UNOP_PLUS, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2881 "parser.tab.c"
    break;

  case 143: /* unary_expression: MINUS unary_expression  */
#line 531 "parser/parser.y"
                                     { 
      (yyval.node) = create_unary_expression(UNOP_MINUS, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2889 "parser.tab.c"
    break;

  case 144: /* unary_expression: NOT unary_expression  */
#line 534 "parser/parser.y"
                                   { 
      (yyval.node) = create_unary_expression(UNOP_NOT, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2897 "parser.tab.c"
    break;

  case 145: /* unary_expression: primary_expression  */
#line 537 "parser/parser.y"
                       { (yyval.node) = (yyvsp[0].node); }
#line 2903 "parser.tab.c"
    break;

  case 146: /* primary_expression: variable  */
#line 540 "parser/parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 2909 "parser.tab.c"
    break;

  case 147: /* primary_expression: unsigned_integer  */
#line 541 "parser/parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2915 "parser.tab.c"
    break;

  case 148: /* primary_expression: unsigned_real  */
#line 542 "parser/parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 2921 "parser.tab.c"
    break;

  case 149: /* primary_expression: string_literal  */
#line 543 "parser/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 2927 "parser.tab.c"
    break;

  case 150: /* primary_expression: char_literal  */
#line 544 "parser/parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 2933 "parser.tab.c"
    break;

  case 151: /* primary_expression: NIL  */
#line 545 "parser/parser.y"
        {
      (yyval.node) = create_nil_literal(create_location((yyloc)));
    }
#line 2941 "parser.tab.c"
    break;

  case 152: /* primary_expression: funcid L_PAREN optional_expression_list R_PAREN  */
#line 548 "parser/parser.y"
                                                    {
      (yyval.node) = create_function_call_node((yyvsp[-3].node), (yyvsp[-1].node), create_location((yyloc)));
    }
#line 2949 "parser.tab.c"
    break;

  case 153: /* primary_expression: L_BRACKET element_list R_BRACKET  */
#line 551 "parser/parser.y"
                                     { (yyval.node) = (yyvsp[-1].node); }
#line 2955 "parser.tab.c"
    break;

  case 154: /* primary_expression: L_PAREN expression R_PAREN  */
#line 552 "parser/parser.y"
                               { (yyval.node) = (yyvsp[-1].node); }
#line 2961 "parser.tab.c"
    break;

  case 155: /* element_list: empty  */
#line 555 "parser/parser.y"
          { 
      (yyval.node) = create_set_literal(create_location((yyloc))); 
    }
#line 2969 "parser.tab.c"
    break;

  case 156: /* element_list: element_list_non_empty  */
#line 558 "parser/parser.y"
                           { 
      (yyval.node) = (yyvsp[0].node); 
    }
#line 2977 "parser.tab.c"
    break;

  case 157: /* element_list_non_empty: element  */
#line 563 "parser/parser.y"
            { 
      (yyval.node) = create_set_literal_with_element((yyvsp[0].node), create_location((yyloc))); 
    }
#line 2985 "parser.tab.c"
    break;

  case 158: /* element_list_non_empty: element_list_non_empty COMMA element  */
#line 566 "parser/parser.y"
                                         {
      (yyval.node) = add_element_to_set_literal((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2993 "parser.tab.c"
    break;

  case 159: /* element: expression  */
#line 571 "parser/parser.y"
               { 
      (yyval.node) = create_set_element((yyvsp[0].node), create_location((yyloc))); 
    }
#line 3001 "parser.tab.c"
    break;

  case 160: /* element: expression DOTDOT expression  */
#line 574 "parser/parser.y"
                                 {
      (yyval.node) = create_set_range_element((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 3009 "parser.tab.c"
    break;

  case 161: /* constid: identifier  */
#line 579 "parser/parser.y"
               {
      (yyval.node) = update_identifier_node_kind((yyvsp[0].node), SYMBOL_CONSTANT);
   }
#line 3017 "parser.tab.c"
    break;

  case 162: /* typeid: CHAR  */
#line 584 "parser/parser.y"
         { (yyval.node) = create_builtin_type_identifier("char", create_location((yyloc))); }
#line 3023 "parser.tab.c"
    break;

  case 163: /* typeid: BOOLEAN  */
#line 585 "parser/parser.y"
            { (yyval.node) = create_builtin_type_identifier("boolean", create_location((yyloc))); }
#line 3029 "parser.tab.c"
    break;

  case 164: /* typeid: INTEGER  */
#line 586 "parser/parser.y"
            { (yyval.node) = create_builtin_type_identifier("integer", create_location((yyloc))); }
#line 3035 "parser.tab.c"
    break;

  case 165: /* typeid: REAL  */
#line 587 "parser/parser.y"
         { (yyval.node) = create_builtin_type_identifier("real", create_location((yyloc))); }
#line 3041 "parser.tab.c"
    break;

  case 166: /* typeid: STRING  */
#line 588 "parser/parser.y"
           { (yyval.node) = create_builtin_type_identifier("string", create_location((yyloc))); }
#line 3047 "parser.tab.c"
    break;

  case 167: /* typeid: identifier  */
#line 589 "parser/parser.y"
               {
      ASTNode *typeId = update_identifier_node_kind((yyvsp[0].node), SYMBOL_TYPE);
      (yyval.node) = create_type_identifier((IdentifierNode*)typeId, create_location((yyloc)));
    }
#line 3056 "parser.tab.c"
    break;

  case 168: /* funcid: identifier  */
#line 595 "parser/parser.y"
              { 
    (yyval.node) = update_identifier_node_kind((yyvsp[0].node), SYMBOL_FUNCTION);
  }
#line 3064 "parser.tab.c"
    break;

  case 169: /* funcid: CHR  */
#line 598 "parser/parser.y"
        { (yyval.node) = create_builtin_identifier("Chr", create_location((yyloc))); }
#line 3070 "parser.tab.c"
    break;

  case 170: /* procid: identifier  */
#line 602 "parser/parser.y"
             { 
    (yyval.node) = update_identifier_node_kind((yyvsp[0].node), SYMBOL_PROCEDURE);
  }
#line 3078 "parser.tab.c"
    break;

  case 171: /* procid: WRITE  */
#line 605 "parser/parser.y"
          { (yyval.node) = create_builtin_identifier("write", create_location((yyloc))); }
#line 3084 "parser.tab.c"
    break;

  case 172: /* procid: WRITELN  */
#line 606 "parser/parser.y"
            { (yyval.node) = create_builtin_identifier("writeln", create_location((yyloc))); }
#line 3090 "parser.tab.c"
    break;

  case 173: /* procid: READ  */
#line 607 "parser/parser.y"
         { (yyval.node) = create_builtin_identifier("read", create_location((yyloc))); }
#line 3096 "parser.tab.c"
    break;

  case 174: /* procid: READLN  */
#line 608 "parser/parser.y"
           { (yyval.node) = create_builtin_identifier("readln", create_location((yyloc))); }
#line 3102 "parser.tab.c"
    break;

  case 175: /* fieldid: identifier  */
#line 611 "parser/parser.y"
             { 
    (yyval.node) = update_identifier_node_kind((yyvsp[0].node), SYMBOL_FIELD);
  }
#line 3110 "parser.tab.c"
    break;

  case 176: /* varid: identifier  */
#line 616 "parser/parser.y"
             {
    (yyval.node) = update_identifier_node_kind((yyvsp[0].node), SYMBOL_VARIABLE);
  }
#line 3118 "parser.tab.c"
    break;

  case 177: /* identifier: IDENTIFIER  */
#line 621 "parser/parser.y"
              { (yyval.node) = create_identifier_node((yyvsp[0].string), create_location((yyloc))); }
#line 3124 "parser.tab.c"
    break;

  case 178: /* unsigned_integer: INTEGER_LITERAL  */
#line 624 "parser/parser.y"
                    {
      (yyval.node) = create_unsigned_integer_node((yyvsp[0].integer), create_location((yyloc)));
    }
#line 3132 "parser.tab.c"
    break;

  case 179: /* unsigned_real: REAL_LITERAL  */
#line 629 "parser/parser.y"
                 {
      (yyval.node) = create_unsigned_real_node((yyvsp[0].number), create_location((yyloc)));
    }
#line 3140 "parser.tab.c"
    break;

  case 180: /* integer_literal: INTEGER_LITERAL  */
#line 634 "parser/parser.y"
                    {
      (yyval.node) = create_integer_literal((yyvsp[0].integer), create_location((yyloc)));
    }
#line 3148 "parser.tab.c"
    break;

  case 181: /* real_literal: REAL_LITERAL  */
#line 639 "parser/parser.y"
                 {
      (yyval.node) = create_real_literal((yyvsp[0].number), create_location((yyloc)));
    }
#line 3156 "parser.tab.c"
    break;

  case 182: /* string_literal: STRING_LITERAL  */
#line 644 "parser/parser.y"
                   {
      (yyval.node) = create_string_literal((yyvsp[0].string), create_location((yyloc)));
    }
#line 3164 "parser.tab.c"
    break;

  case 183: /* char_literal: CHAR_LITERAL  */
#line 649 "parser/parser.y"
                 {
      (yyval.node) = create_char_literal((yyvsp[0].character), create_location((yyloc)));
    }
#line 3172 "parser.tab.c"
    break;

  case 184: /* boolean_literal: BOOLEAN_LITERAL  */
#line 654 "parser/parser.y"
                    {
      (yyval.node) = create_boolean_literal((yyvsp[0].boolean), create_location((yyloc)));
    }
#line 3180 "parser.tab.c"
    break;

  case 185: /* empty: %empty  */
#line 658 "parser/parser.y"
              { (yyval.node) = NULL; }
#line 3186 "parser.tab.c"
    break;


#line 3190 "parser.tab.c"

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

