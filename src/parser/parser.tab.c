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
  YYSYMBOL_optional_parameter_list = 114,  /* optional_parameter_list  */
  YYSYMBOL_formal_parameter_list = 115,    /* formal_parameter_list  */
  YYSYMBOL_formal_parameter_section = 116, /* formal_parameter_section  */
  YYSYMBOL_parameterid_list = 117,         /* parameterid_list  */
  YYSYMBOL_statement_list = 118,           /* statement_list  */
  YYSYMBOL_optional_statement = 119,       /* optional_statement  */
  YYSYMBOL_statement = 120,                /* statement  */
  YYSYMBOL_variable = 121,                 /* variable  */
  YYSYMBOL_subscript_list = 122,           /* subscript_list  */
  YYSYMBOL_case_list = 123,                /* case_list  */
  YYSYMBOL_case_item = 124,                /* case_item  */
  YYSYMBOL_case_label_list = 125,          /* case_label_list  */
  YYSYMBOL_case_label = 126,               /* case_label  */
  YYSYMBOL_case_else = 127,                /* case_else  */
  YYSYMBOL_for_list = 128,                 /* for_list  */
  YYSYMBOL_optional_expression_list = 129, /* optional_expression_list  */
  YYSYMBOL_expression_list = 130,          /* expression_list  */
  YYSYMBOL_label = 131,                    /* label  */
  YYSYMBOL_record_variable_list = 132,     /* record_variable_list  */
  YYSYMBOL_expression = 133,               /* expression  */
  YYSYMBOL_additive_expression = 134,      /* additive_expression  */
  YYSYMBOL_multiplicative_expression = 135, /* multiplicative_expression  */
  YYSYMBOL_unary_expression = 136,         /* unary_expression  */
  YYSYMBOL_primary_expression = 137,       /* primary_expression  */
  YYSYMBOL_element_list = 138,             /* element_list  */
  YYSYMBOL_element_list_non_empty = 139,   /* element_list_non_empty  */
  YYSYMBOL_element = 140,                  /* element  */
  YYSYMBOL_constid = 141,                  /* constid  */
  YYSYMBOL_typeid = 142,                   /* typeid  */
  YYSYMBOL_funcid = 143,                   /* funcid  */
  YYSYMBOL_procid = 144,                   /* procid  */
  YYSYMBOL_fieldid = 145,                  /* fieldid  */
  YYSYMBOL_varid = 146,                    /* varid  */
  YYSYMBOL_identifier = 147,               /* identifier  */
  YYSYMBOL_unsigned_integer = 148,         /* unsigned_integer  */
  YYSYMBOL_unsigned_real = 149,            /* unsigned_real  */
  YYSYMBOL_integer_literal = 150,          /* integer_literal  */
  YYSYMBOL_real_literal = 151,             /* real_literal  */
  YYSYMBOL_string_literal = 152,           /* string_literal  */
  YYSYMBOL_char_literal = 153,             /* char_literal  */
  YYSYMBOL_boolean_literal = 154,          /* boolean_literal  */
  YYSYMBOL_empty = 155                     /* empty  */
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
#define YYLAST   682

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  81
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  75
/* YYNRULES -- Number of rules.  */
#define YYNRULES  187
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  363

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
     292,   297,   298,   299,   302,   303,   306,   307,   310,   311,
     314,   317,   318,   321,   322,   327,   328,   333,   334,   339,
     342,   347,   348,   351,   354,   355,   358,   359,   364,   367,
     370,   374,   380,   381,   386,   387,   390,   391,   394,   395,
     396,   397,   398,   399,   400,   401,   402,   403,   404,   405,
     406,   407,   410,   411,   412,   413,   416,   419,   424,   425,
     430,   435,   436,   441,   442,   447,   452,   455,   460,   461,
     464,   465,   468,   471,   472,   477,   480,   483,   486,   489,
     492,   495,   498,   501,   504,   507,   510,   513,   516,   519,
     522,   525,   528,   531,   534,   537,   540,   543,   544,   545,
     546,   547,   548,   549,   552,   555,   556,   559,   562,   567,
     570,   575,   578,   583,   588,   589,   590,   591,   592,   593,
     599,   602,   606,   609,   610,   611,   612,   615,   620,   625,
     628,   633,   638,   643,   648,   653,   658,   662
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
  "block_or_forward", "parameters", "optional_parameter_list",
  "formal_parameter_list", "formal_parameter_section", "parameterid_list",
  "statement_list", "optional_statement", "statement", "variable",
  "subscript_list", "case_list", "case_item", "case_label_list",
  "case_label", "case_else", "for_list", "optional_expression_list",
  "expression_list", "label", "record_variable_list", "expression",
  "additive_expression", "multiplicative_expression", "unary_expression",
  "primary_expression", "element_list", "element_list_non_empty",
  "element", "constid", "typeid", "funcid", "procid", "fieldid", "varid",
  "identifier", "unsigned_integer", "unsigned_real", "integer_literal",
  "real_literal", "string_literal", "char_literal", "boolean_literal",
  "empty", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-307)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-179)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      41,   -21,    57,     8,  -307,     9,    34,  -307,  -307,    40,
    -307,   660,     9,  -307,     9,     9,   181,    30,   214,   -26,
     508,     7,  -307,  -307,  -307,  -307,  -307,    29,    67,   101,
     125,   127,  -307,  -307,    84,  -307,   154,  -307,  -307,  -307,
    -307,  -307,  -307,   158,  -307,  -307,  -307,  -307,  -307,  -307,
    -307,   149,  -307,  -307,   149,  -307,   508,   489,     9,   489,
       9,   508,   489,    30,   -10,  -307,     0,   131,   156,  -307,
      47,  -307,  -307,   147,    30,    79,   425,    22,   157,     9,
     538,   406,   538,    15,   161,   163,     1,  -307,   489,   489,
     489,   489,   489,  -307,  -307,  -307,  -307,    52,   335,    74,
      44,  -307,  -307,   167,   168,  -307,  -307,  -307,  -307,  -307,
      52,    19,  -307,   396,   174,    18,   405,  -307,  -307,   508,
       9,  -307,   489,   489,   508,   489,  -307,  -307,  -307,   188,
    -307,   189,  -307,   118,  -307,  -307,  -307,   137,   173,    -9,
     216,   217,     9,     9,   181,     9,  -307,  -307,   186,  -307,
    -307,  -307,  -307,  -307,  -307,   190,  -307,  -307,  -307,  -307,
    -307,  -307,  -307,     9,     9,     9,   192,   198,  -307,   121,
    -307,  -307,   646,   181,  -307,  -307,  -307,  -307,   577,   601,
     195,   196,  -307,  -307,   508,   489,   489,   489,   489,   489,
     489,   489,   489,   489,   489,   489,   489,   489,   489,   489,
     489,   508,     9,   508,   489,   489,   406,  -307,  -307,  -307,
    -307,  -307,   628,   -30,   628,  -307,   200,   199,   628,  -307,
     406,   538,   538,  -307,   563,   181,   256,   206,  -307,   130,
    -307,  -307,  -307,   563,   538,  -307,  -307,  -307,    54,   406,
     136,   149,   149,  -307,    15,     9,   181,  -307,  -307,  -307,
     207,  -307,   489,  -307,   489,   260,    74,    74,    74,    74,
      74,    74,    44,    44,    44,  -307,  -307,  -307,  -307,  -307,
    -307,   210,  -307,    52,  -307,   261,   423,   628,   221,    17,
    -307,   141,  -307,   489,  -307,  -307,   489,  -307,  -307,  -307,
    -307,   -25,   255,  -307,   219,  -307,    -9,     9,   538,  -307,
    -307,  -307,  -307,   181,  -307,   223,  -307,  -307,  -307,   646,
     628,  -307,   508,  -307,   508,   489,   489,   406,  -307,   339,
     406,   508,   628,   628,   563,   267,   406,   181,  -307,  -307,
    -307,  -307,  -307,   181,  -307,  -307,  -307,   628,   628,  -307,
     508,  -307,   277,  -307,  -307,  -307,   538,   233,  -307,   162,
    -307,  -307,  -307,   234,  -307,  -307,   406,   236,  -307,  -307,
      -9,   237,  -307
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,   187,     1,     0,     0,     4,   179,     0,
       5,     0,     0,     3,     0,     0,     0,     0,     0,     0,
       0,     0,     7,     9,    11,    13,    15,     0,     0,     0,
       0,     0,    67,     6,     0,    26,     0,   163,   166,   167,
     165,   164,   168,     0,   169,   180,    18,   175,   173,   176,
     174,     0,   172,   171,     0,   170,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    84,     0,     0,    97,   102,
     172,   122,     2,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   187,     0,     0,     0,   153,     0,     0,
       0,     0,   187,   185,   181,   186,   184,   147,     0,   131,
     135,   142,   146,     0,   178,   148,   149,   150,   151,   152,
     123,     0,   178,     0,     0,     0,     0,    99,    17,   187,
       0,   105,     0,     0,     0,   187,     8,    19,    10,     0,
      12,     0,    14,     0,    16,    68,    27,     0,     0,   187,
       0,    47,     0,     0,     0,     0,   182,   183,     0,    24,
      36,    37,    42,    33,    41,   169,    28,    29,    30,    31,
      32,    20,    22,     0,     0,     0,     0,    75,    76,     0,
      82,    74,     0,     0,    89,   145,   143,   144,     0,   161,
       0,   158,   159,   157,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     187,     0,     0,     0,     0,     0,     0,    85,    86,    87,
     104,   177,    88,     0,   106,   101,     0,   119,   120,   118,
       0,     0,     0,    43,     0,     0,     0,    51,    54,     0,
      53,    58,    56,     0,     0,    34,    35,    38,     0,     0,
       0,     0,     0,    73,     0,     0,     0,    72,    71,    69,
       0,   156,     0,   155,     0,    90,   130,   129,   125,   126,
     128,   127,   134,   132,   133,   140,   136,   137,   138,   139,
     141,     0,   100,   124,    94,     0,     0,    95,   113,     0,
     108,     0,   111,     0,   103,    98,     0,    21,    23,    25,
      49,     0,     0,    61,   169,    45,   187,     0,     0,    46,
      48,    39,    40,     0,    80,     0,    77,    83,    78,     0,
     162,   160,     0,   154,     0,     0,     0,     0,    92,     0,
       0,     0,   107,   121,     0,     0,   187,     0,    55,    52,
      59,    57,    79,     0,    70,    91,    96,   116,   117,   114,
       0,   109,     0,   112,   110,    50,     0,    60,    63,     0,
      65,    62,    81,     0,    93,    44,   187,     0,   115,    64,
     187,     0,    66
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -307,  -307,  -307,   159,   291,   232,   235,   241,   246,   248,
    -307,  -307,  -307,  -307,   247,   -56,   -60,  -206,  -307,   176,
    -307,   -49,  -307,    35,  -307,    37,  -307,  -307,   -22,  -307,
     252,    27,   -50,  -307,  -307,    93,   177,   -14,  -307,   -90,
       6,  -307,  -307,    20,  -306,    23,  -307,  -307,   142,  -307,
     281,  -307,   303,   492,   -16,   -53,  -307,  -307,  -307,    91,
      -7,     5,   328,   332,  -117,   292,    -5,   -15,  -307,  -307,
    -307,    51,   166,   197,     3
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     2,     6,     9,   248,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    34,   148,   149,   150,   151,   152,
     291,   226,   227,   228,   229,   230,   292,   347,   348,    31,
      32,   249,    84,   166,   167,   168,   169,    64,   207,    65,
      97,   213,   279,   280,   281,   282,   342,   275,   216,   217,
      67,   111,   179,    99,   100,   101,   102,   180,   181,   182,
     153,   154,   103,    68,   231,    69,   104,   105,   106,   156,
     157,   107,   108,   109,   232
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      10,   118,    46,   210,    85,    71,     7,    33,    36,    35,
      37,    44,   174,    52,    55,    70,    53,   225,   290,   163,
     349,    43,   162,   164,   165,   161,    66,   299,   318,   208,
      18,    19,    20,   283,   215,   175,   176,   177,   324,   201,
     284,    71,    86,   205,     1,   325,    71,   115,    71,     8,
     349,    70,   119,   112,     3,   112,    70,     4,   120,   127,
     121,   122,    66,   119,   110,    72,     8,    66,   129,   123,
      37,    44,    35,     5,   136,   155,    37,   155,   170,   319,
     119,   131,   202,    14,     8,    16,   171,    18,    19,    20,
       8,    73,    74,   194,   255,   183,    11,     8,   195,   196,
     197,   198,    45,    12,    71,  -178,    13,  -178,  -178,    71,
     120,   272,   121,   274,    70,   211,  -178,    12,   345,    70,
     301,   123,   209,   199,   191,    66,   192,   193,   219,    75,
      66,   158,   158,   158,   211,   235,   236,    37,    37,    44,
      10,   265,   266,   267,   268,   269,   270,    79,    80,   237,
     278,    14,    15,    16,     8,    18,    19,    20,   170,   241,
     242,   288,   289,    76,   287,    18,    19,    20,    44,    71,
     138,   139,   140,   141,   300,   262,   263,   264,   250,    70,
     330,    79,   222,   302,   245,   246,    71,    77,    71,    78,
      66,   304,   305,   297,   298,   124,    70,   112,    70,   245,
     303,    37,    81,   219,   320,   321,    82,    66,   273,    66,
      38,    39,    40,    41,    83,    37,   155,   155,    42,   155,
     294,   125,   335,   172,   336,   320,   357,   173,   155,   155,
     293,   344,   200,  -170,    37,   204,   220,   221,   331,   170,
     307,    44,   224,   233,   234,   239,   159,   159,   159,  -163,
     353,   308,    47,    48,    49,    50,     8,   158,   243,   254,
     244,   339,   286,   278,   278,   253,   285,   295,   296,   309,
     278,   158,   158,   158,   312,   158,   313,   160,   160,   160,
     317,   314,   326,   327,   158,   158,   355,   333,   354,     8,
     158,   211,   211,   155,   346,   356,   358,    71,    44,    71,
     278,   360,    21,   362,   238,   126,    71,    70,   332,    70,
     128,   361,    37,   223,    37,    37,    70,   130,    66,   155,
      66,    37,    44,   132,   133,    71,   134,    66,    44,   350,
     135,   328,   351,   329,   359,    70,   334,   306,   352,   341,
     240,   155,   271,   343,   117,   311,    66,    54,   184,   158,
      51,    37,   114,   340,     0,   211,     0,     0,     0,   350,
      98,     0,   113,     0,     0,   116,     0,     0,   158,     0,
     158,   158,   159,     0,     0,   158,     0,   158,   185,   186,
     187,   188,   189,   190,     0,     0,   159,   159,   159,     0,
     159,   142,   143,     0,   178,     0,     0,   158,     0,   159,
     159,     0,     0,   160,     0,   159,     0,   158,     0,     0,
      93,   146,   147,    95,     8,    96,   203,   160,   160,   160,
       0,   160,     0,     0,     0,   212,   214,     0,   218,    14,
     160,   160,   206,    18,    19,    20,   160,     0,     0,   185,
     186,   187,   188,   189,   190,   315,   316,     0,   185,   186,
     187,   188,   189,   190,    38,    39,    40,    41,   142,   143,
       0,     0,    42,     0,   159,     0,   185,   186,   187,   188,
     189,   190,     0,     0,     0,     0,     0,    93,   146,   147,
      95,     8,    96,   159,     0,   159,   159,     0,     0,     0,
     159,     0,   159,     0,     0,   160,     0,     0,     0,     0,
       8,     0,     0,   218,    87,     0,     0,   276,   277,     0,
       0,     0,   159,     0,   160,     0,   160,   160,    56,     0,
      57,   160,   159,   160,    58,     0,     0,    59,     0,    60,
       0,    53,    61,     0,    62,     0,    63,     0,     0,     0,
      88,    89,    90,   160,     0,     0,    47,    48,    49,    50,
       0,     0,     0,   160,    91,   310,   137,     0,    92,     0,
      93,    45,    94,    95,     8,    96,     0,    38,    39,    40,
      41,   138,   139,   140,   141,    42,     0,     0,     0,     0,
      45,     0,     0,     8,     0,     0,   322,     0,     0,   323,
     142,   143,    38,    39,    40,    41,     0,     0,   144,     0,
      42,     0,     0,   145,     0,     0,     0,     0,     0,    93,
     146,   147,    95,     8,    96,   142,   143,     0,   337,   338,
     185,   186,   187,   188,   189,   190,     0,     0,   145,     0,
       0,     0,     0,     0,    93,   146,   147,    95,     8,    96,
       0,     0,     0,   251,   185,   186,   187,   188,   189,   190,
      14,    15,    16,    17,    18,    19,    20,     0,     0,     0,
     252,     0,     0,   247,    14,    15,    16,    17,    18,    19,
      20,   185,   186,   187,   188,   189,   190,   256,   257,   258,
     259,   260,   261
};

static const yytype_int16 yycheck[] =
{
       5,    11,    17,   120,    54,    20,     3,    12,    15,    14,
      15,    16,    11,    18,    19,    20,    42,    26,   224,     4,
     326,    16,    82,     8,     9,    81,    20,   233,    11,   119,
       8,     9,    10,    63,   124,    88,    89,    90,    63,    20,
      70,    56,    56,    25,     3,    70,    61,    61,    63,    75,
     356,    56,    62,    58,    75,    60,    61,     0,    58,    74,
      60,    61,    56,    62,    58,    58,    75,    61,    75,    69,
      75,    76,    77,    65,    79,    80,    81,    82,    83,    62,
      62,    76,    63,     4,    75,     6,    83,     8,     9,    10,
      75,    62,    63,    49,   184,    92,    62,    75,    54,    55,
      56,    57,    72,    63,   119,    58,    66,    60,    61,   124,
      58,   201,    60,   203,   119,   120,    69,    63,   324,   124,
      66,    69,   119,    79,    50,   119,    52,    53,   125,    62,
     124,    80,    81,    82,   139,   142,   143,   142,   143,   144,
     145,   194,   195,   196,   197,   198,   199,    63,    64,   144,
     206,     4,     5,     6,    75,     8,     9,    10,   163,   164,
     165,   221,   222,    62,   220,     8,     9,    10,   173,   184,
      33,    34,    35,    36,   234,   191,   192,   193,   173,   184,
     297,    63,    64,   239,    63,    64,   201,    62,   203,    62,
     184,   241,   242,    63,    64,    64,   201,   202,   203,    63,
      64,   206,    48,   200,    63,    64,    48,   201,   202,   203,
      29,    30,    31,    32,    65,   220,   221,   222,    37,   224,
     225,    65,   312,    62,   314,    63,    64,    64,   233,   234,
     225,   321,    65,    65,   239,    61,    48,    48,   298,   244,
     245,   246,    69,    27,    27,    59,    80,    81,    82,    59,
     340,   246,    38,    39,    40,    41,    75,   206,    66,    63,
      62,   317,    63,   319,   320,    70,    66,    11,    62,    62,
     326,   220,   221,   222,    14,   224,    66,    80,    81,    82,
      59,    20,    27,    64,   233,   234,   346,    64,    11,    75,
     239,   296,   297,   298,    27,    62,    62,   312,   303,   314,
     356,    65,    11,    66,   145,    73,   321,   312,   303,   314,
      75,   360,   317,   137,   319,   320,   321,    76,   312,   324,
     314,   326,   327,    77,    77,   340,    78,   321,   333,   326,
      78,   296,   327,   296,   356,   340,   309,   244,   333,   319,
     163,   346,   200,   320,    63,   254,   340,    19,    13,   298,
      18,   356,    60,    14,    -1,   360,    -1,    -1,    -1,   356,
      57,    -1,    59,    -1,    -1,    62,    -1,    -1,   317,    -1,
     319,   320,   206,    -1,    -1,   324,    -1,   326,    43,    44,
      45,    46,    47,    48,    -1,    -1,   220,   221,   222,    -1,
     224,    52,    53,    -1,    91,    -1,    -1,   346,    -1,   233,
     234,    -1,    -1,   206,    -1,   239,    -1,   356,    -1,    -1,
      71,    72,    73,    74,    75,    76,    20,   220,   221,   222,
      -1,   224,    -1,    -1,    -1,   122,   123,    -1,   125,     4,
     233,   234,    27,     8,     9,    10,   239,    -1,    -1,    43,
      44,    45,    46,    47,    48,    22,    23,    -1,    43,    44,
      45,    46,    47,    48,    29,    30,    31,    32,    52,    53,
      -1,    -1,    37,    -1,   298,    -1,    43,    44,    45,    46,
      47,    48,    -1,    -1,    -1,    -1,    -1,    71,    72,    73,
      74,    75,    76,   317,    -1,   319,   320,    -1,    -1,    -1,
     324,    -1,   326,    -1,    -1,   298,    -1,    -1,    -1,    -1,
      75,    -1,    -1,   200,    15,    -1,    -1,   204,   205,    -1,
      -1,    -1,   346,    -1,   317,    -1,   319,   320,    10,    -1,
      12,   324,   356,   326,    16,    -1,    -1,    19,    -1,    21,
      -1,    42,    24,    -1,    26,    -1,    28,    -1,    -1,    -1,
      51,    52,    53,   346,    -1,    -1,    38,    39,    40,    41,
      -1,    -1,    -1,   356,    65,   252,    18,    -1,    69,    -1,
      71,    72,    73,    74,    75,    76,    -1,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    -1,    -1,    -1,    -1,
      72,    -1,    -1,    75,    -1,    -1,   283,    -1,    -1,   286,
      52,    53,    29,    30,    31,    32,    -1,    -1,    60,    -1,
      37,    -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,    71,
      72,    73,    74,    75,    76,    52,    53,    -1,   315,   316,
      43,    44,    45,    46,    47,    48,    -1,    -1,    65,    -1,
      -1,    -1,    -1,    -1,    71,    72,    73,    74,    75,    76,
      -1,    -1,    -1,    66,    43,    44,    45,    46,    47,    48,
       4,     5,     6,     7,     8,     9,    10,    -1,    -1,    -1,
      59,    -1,    -1,    17,     4,     5,     6,     7,     8,     9,
      10,    43,    44,    45,    46,    47,    48,   185,   186,   187,
     188,   189,   190
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    82,    75,     0,    65,    83,   155,    75,    84,
     147,    62,    63,    66,     4,     5,     6,     7,     8,     9,
      10,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,   110,   111,   147,    95,   147,   141,   147,    29,    30,
      31,    32,    37,   142,   147,    72,   148,    38,    39,    40,
      41,   144,   147,    42,   143,   147,    10,    12,    16,    19,
      21,    24,    26,    28,   118,   120,   121,   131,   144,   146,
     147,   148,    58,    62,    63,    62,    62,    62,    62,    63,
      64,    48,    48,    65,   113,   113,   118,    15,    51,    52,
      53,    65,    69,    71,    73,    74,    76,   121,   133,   134,
     135,   136,   137,   143,   147,   148,   149,   152,   153,   154,
     121,   132,   147,   133,   146,   118,   133,   131,    11,    62,
      58,    60,    61,    69,    64,    65,    86,   148,    87,   141,
      88,   142,    89,    95,    90,   111,   147,    18,    33,    34,
      35,    36,    52,    53,    60,    65,    72,    73,    96,    97,
      98,    99,   100,   141,   142,   147,   150,   151,   152,   153,
     154,    96,    97,     4,     8,     9,   114,   115,   116,   117,
     147,   155,    62,    64,    11,   136,   136,   136,   133,   133,
     138,   139,   140,   155,    13,    43,    44,    45,    46,    47,
      48,    50,    52,    53,    49,    54,    55,    56,    57,    79,
      65,    20,    63,    20,    61,    25,    27,   119,   120,   155,
     145,   147,   133,   122,   133,   120,   129,   130,   133,   155,
      48,    48,    64,   100,    69,    26,   102,   103,   104,   105,
     106,   145,   155,    27,    27,   141,   141,   142,    84,    59,
     117,   147,   147,    66,    62,    63,    64,    17,    85,   112,
     142,    66,    59,    70,    63,   120,   134,   134,   134,   134,
     134,   134,   135,   135,   135,   136,   136,   136,   136,   136,
     136,   129,   120,   121,   120,   128,   133,   133,    96,   123,
     124,   125,   126,    63,    70,    66,    63,    96,    97,    97,
      98,   101,   107,   142,   147,    11,    62,    63,    64,    98,
      97,    66,    96,    64,   113,   113,   116,   147,   142,    62,
     133,   140,    14,    66,    20,    22,    23,    59,    11,    62,
      63,    64,   133,   133,    63,    70,    27,    64,   104,   106,
     145,    97,   142,    64,   112,   120,   120,   133,   133,    96,
      14,   124,   127,   126,   120,    98,    27,   108,   109,   125,
     155,   142,   142,   120,    11,    97,    62,    64,    62,   109,
      65,   102,    66
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    81,    82,    83,    83,    84,    84,    85,    85,    86,
      86,    87,    87,    88,    88,    89,    89,    90,    91,    91,
      92,    92,    93,    93,    94,    94,    95,    95,    96,    96,
      96,    96,    96,    96,    96,    96,    97,    97,    97,    98,
      98,    98,    99,    99,   100,   100,   100,   100,   100,   101,
     101,   102,   102,   102,   103,   103,   104,   104,   105,   105,
     106,   107,   107,   108,   108,   109,   109,   110,   110,   111,
     111,   112,   112,   113,   114,   114,   115,   115,   116,   116,
     116,   116,   117,   117,   118,   118,   119,   119,   120,   120,
     120,   120,   120,   120,   120,   120,   120,   120,   120,   120,
     120,   120,   121,   121,   121,   121,   122,   122,   123,   123,
     124,   125,   125,   126,   126,   127,   128,   128,   129,   129,
     130,   130,   131,   132,   132,   133,   133,   133,   133,   133,
     133,   133,   134,   134,   134,   134,   135,   135,   135,   135,
     135,   135,   135,   136,   136,   136,   136,   137,   137,   137,
     137,   137,   137,   137,   137,   137,   137,   138,   138,   139,
     139,   140,   140,   141,   142,   142,   142,   142,   142,   142,
     143,   143,   144,   144,   144,   144,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     6,     3,     1,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     3,     2,     3,
       4,     5,     4,     5,     4,     5,     1,     3,     1,     1,
       1,     1,     1,     1,     2,     2,     1,     1,     2,     3,
       3,     1,     1,     2,     6,     3,     3,     1,     3,     1,
       3,     1,     3,     1,     1,     3,     1,     3,     1,     3,
       4,     1,     3,     1,     3,     1,     5,     1,     3,     5,
       7,     1,     1,     3,     1,     1,     1,     3,     3,     4,
       3,     5,     1,     3,     1,     3,     1,     1,     3,     3,
       4,     6,     5,     7,     4,     4,     6,     1,     4,     2,
       4,     3,     1,     4,     3,     2,     1,     3,     1,     3,
       3,     1,     3,     1,     3,     3,     3,     3,     1,     1,
       1,     3,     1,     1,     3,     3,     3,     3,     3,     3,
       3,     1,     3,     3,     3,     1,     3,     3,     3,     3,
       3,     3,     1,     2,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     3,     3,     1,     1,     1,
       3,     1,     3,     1,     1,     1,     1,     1,     1,     1,
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
#line 137 "parser/parser.y"
                                                             {
      (yyval.node) = create_program_node((yyvsp[-4].string), (yyvsp[-3].node), (yyvsp[-1].node), create_location((yyloc)));
      root = (yyval.node);
    }
#line 1955 "parser/parser.tab.c"
    break;

  case 3: /* program_headingopt: L_PAREN identifier_list R_PAREN  */
#line 143 "parser/parser.y"
                                    {
      (yyval.node) = create_heading_node((yyvsp[-1].node), create_location((yyloc)));
    }
#line 1963 "parser/parser.tab.c"
    break;

  case 5: /* identifier_list: identifier  */
#line 149 "parser/parser.y"
               {
      (yyval.node) = create_identifier_list_node((yyvsp[0].node), create_location((yyloc)));
    }
#line 1971 "parser/parser.tab.c"
    break;

  case 6: /* identifier_list: identifier_list COMMA identifier  */
#line 152 "parser/parser.y"
                                     {
      (yyval.node) = append_identifier_list_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 1979 "parser/parser.tab.c"
    break;

  case 7: /* block: block1  */
#line 157 "parser/parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 1985 "parser/parser.tab.c"
    break;

  case 8: /* block: label_declaration SEMICOLON block1  */
#line 158 "parser/parser.y"
                                       {
      (yyval.node) = add_labels_to_block((yyvsp[0].node), (yyvsp[-2].node));
    }
#line 1993 "parser/parser.tab.c"
    break;

  case 9: /* block1: block2  */
#line 163 "parser/parser.y"
            { (yyval.node) = (yyvsp[0].node); }
#line 1999 "parser/parser.tab.c"
    break;

  case 10: /* block1: constant_declaration SEMICOLON block2  */
#line 164 "parser/parser.y"
                                          {
    (yyval.node) = add_constants_to_block((yyvsp[0].node), (yyvsp[-2].node));
  }
#line 2007 "parser/parser.tab.c"
    break;

  case 11: /* block2: block3  */
#line 169 "parser/parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 2013 "parser/parser.tab.c"
    break;

  case 12: /* block2: type_declaration SEMICOLON block3  */
#line 170 "parser/parser.y"
                                      {
     (yyval.node) = add_types_to_block((yyvsp[0].node), (yyvsp[-2].node));
  }
#line 2021 "parser/parser.tab.c"
    break;

  case 13: /* block3: block4  */
#line 175 "parser/parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 2027 "parser/parser.tab.c"
    break;

  case 14: /* block3: variable_declaration SEMICOLON block4  */
#line 176 "parser/parser.y"
                                          {
      (yyval.node) = add_variables_to_block((yyvsp[0].node), (yyvsp[-2].node));
    }
#line 2035 "parser/parser.tab.c"
    break;

  case 15: /* block4: block5  */
#line 181 "parser/parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 2041 "parser/parser.tab.c"
    break;

  case 16: /* block4: proc_and_func_declaration SEMICOLON block5  */
#line 182 "parser/parser.y"
                                               {
      (yyval.node) = add_procs_funcs_to_block((yyvsp[0].node), (yyvsp[-2].node));
    }
#line 2049 "parser/parser.tab.c"
    break;

  case 17: /* block5: BEGIN_TOK statement_list END  */
#line 187 "parser/parser.y"
                                 {
      (yyval.node) = create_block_node(NULL, NULL, NULL, NULL, NULL, (yyvsp[-1].node), create_location((yyloc)));
    }
#line 2057 "parser/parser.tab.c"
    break;

  case 18: /* label_declaration: LABEL unsigned_integer  */
#line 192 "parser/parser.y"
                           { (yyval.node) = create_label_declaration_node((yyvsp[0].node), create_location((yyloc))); }
#line 2063 "parser/parser.tab.c"
    break;

  case 19: /* label_declaration: label_declaration COMMA unsigned_integer  */
#line 193 "parser/parser.y"
                                             {
      (yyval.node) = append_label_declaration((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2071 "parser/parser.tab.c"
    break;

  case 20: /* constant_declaration: CONST constid EQ constant  */
#line 198 "parser/parser.y"
                              {
      (yyval.node) = create_constant_declaration_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2079 "parser/parser.tab.c"
    break;

  case 21: /* constant_declaration: constant_declaration SEMICOLON constid EQ constant  */
#line 201 "parser/parser.y"
                                                       {
      (yyval.node) = append_constant_declaration((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2087 "parser/parser.tab.c"
    break;

  case 22: /* type_declaration: TYPE typeid EQ type  */
#line 206 "parser/parser.y"
                        { (yyval.node) = create_type_declaration_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2093 "parser/parser.tab.c"
    break;

  case 23: /* type_declaration: type_declaration SEMICOLON typeid EQ type  */
#line 207 "parser/parser.y"
                                              {
      (yyval.node) = append_type_declaration((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2101 "parser/parser.tab.c"
    break;

  case 24: /* variable_declaration: VAR variableid_list COLON type  */
#line 212 "parser/parser.y"
                                   { (yyval.node) = create_variable_declaration_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2107 "parser/parser.tab.c"
    break;

  case 25: /* variable_declaration: variable_declaration SEMICOLON variableid_list COLON type  */
#line 213 "parser/parser.y"
                                                              {
      (yyval.node) = append_variable_declaration((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2115 "parser/parser.tab.c"
    break;

  case 26: /* variableid_list: identifier  */
#line 218 "parser/parser.y"
                { (yyval.node) = create_variable_identifier_list_node((yyvsp[0].node), create_location((yyloc))); }
#line 2121 "parser/parser.tab.c"
    break;

  case 27: /* variableid_list: variableid_list COMMA identifier  */
#line 219 "parser/parser.y"
                                     {
      (yyval.node) = append_variable_identifier_list((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2129 "parser/parser.tab.c"
    break;

  case 28: /* constant: integer_literal  */
#line 224 "parser/parser.y"
                    {
      (yyval.node) = create_constant_literal((yyvsp[0].node), create_location((yyloc)));
    }
#line 2137 "parser/parser.tab.c"
    break;

  case 29: /* constant: real_literal  */
#line 227 "parser/parser.y"
                 {
      (yyval.node) = create_constant_literal((yyvsp[0].node), create_location((yyloc)));
    }
#line 2145 "parser/parser.tab.c"
    break;

  case 30: /* constant: string_literal  */
#line 230 "parser/parser.y"
                   {
      (yyval.node) = create_constant_literal((yyvsp[0].node), create_location((yyloc)));
    }
#line 2153 "parser/parser.tab.c"
    break;

  case 31: /* constant: char_literal  */
#line 233 "parser/parser.y"
                 {
      (yyval.node) = create_constant_literal((yyvsp[0].node), create_location((yyloc)));
    }
#line 2161 "parser/parser.tab.c"
    break;

  case 32: /* constant: boolean_literal  */
#line 236 "parser/parser.y"
                    {
      (yyval.node) = create_constant_literal((yyvsp[0].node), create_location((yyloc)));
    }
#line 2169 "parser/parser.tab.c"
    break;

  case 33: /* constant: constid  */
#line 239 "parser/parser.y"
            { (yyval.node) = create_constant_identifier((yyvsp[0].node), create_location((yyloc))); }
#line 2175 "parser/parser.tab.c"
    break;

  case 34: /* constant: PLUS constid  */
#line 240 "parser/parser.y"
                 { (yyval.node) = create_constant_signed_identifier((yyvsp[0].node), "+", create_location((yyloc))); }
#line 2181 "parser/parser.tab.c"
    break;

  case 35: /* constant: MINUS constid  */
#line 241 "parser/parser.y"
                  { (yyval.node) = create_constant_signed_identifier((yyvsp[0].node), "-", create_location((yyloc))); }
#line 2187 "parser/parser.tab.c"
    break;

  case 36: /* type: simple_type  */
#line 244 "parser/parser.y"
                {
      (yyval.node) = create_simple_type_node((yyvsp[0].node), create_location((yyloc)));
    }
#line 2195 "parser/parser.tab.c"
    break;

  case 37: /* type: structured_type  */
#line 247 "parser/parser.y"
                    {
      (yyval.node) = create_structure_type_node((yyvsp[0].node), create_location((yyloc)));
    }
#line 2203 "parser/parser.tab.c"
    break;

  case 38: /* type: CARET typeid  */
#line 250 "parser/parser.y"
                 {
      (yyval.node) = create_pointer_type_node((yyvsp[0].node), create_location((yyloc)));
    }
#line 2211 "parser/parser.tab.c"
    break;

  case 39: /* simple_type: L_PAREN identifier_list R_PAREN  */
#line 255 "parser/parser.y"
                                     { (yyval.node) = create_enumerated_type_node((yyvsp[-1].node), create_location((yyloc))); }
#line 2217 "parser/parser.tab.c"
    break;

  case 40: /* simple_type: constant DOTDOT constant  */
#line 256 "parser/parser.y"
                             {
      (yyval.node) = create_constant_range_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2225 "parser/parser.tab.c"
    break;

  case 41: /* simple_type: typeid  */
#line 259 "parser/parser.y"
           {
      (yyval.node) = (yyvsp[0].node);
    }
#line 2233 "parser/parser.tab.c"
    break;

  case 42: /* structured_type: unpacked_structured_type  */
#line 264 "parser/parser.y"
                             {
      (yyval.node) = (yyvsp[0].node);
    }
#line 2241 "parser/parser.tab.c"
    break;

  case 43: /* structured_type: PACKED unpacked_structured_type  */
#line 267 "parser/parser.y"
                                      {
      (yyval.node) = create_packed_type((yyvsp[0].node), create_location((yyloc)));
    }
#line 2249 "parser/parser.tab.c"
    break;

  case 44: /* unpacked_structured_type: ARRAY L_BRACKET index_list R_BRACKET OF type  */
#line 272 "parser/parser.y"
                                                   {
        (yyval.node) = create_array_type_node((yyvsp[-3].node), (yyvsp[0].node), create_location((yyloc)));
      }
#line 2257 "parser/parser.tab.c"
    break;

  case 45: /* unpacked_structured_type: RECORD field_list END  */
#line 275 "parser/parser.y"
                            {
        (yyval.node) = create_record_type_node((yyvsp[-1].node), create_location((yyloc)));
      }
#line 2265 "parser/parser.tab.c"
    break;

  case 46: /* unpacked_structured_type: SET OF simple_type  */
#line 278 "parser/parser.y"
                         {
        (yyval.node) = create_set_of_type_node((yyvsp[0].node), create_location((yyloc)));
      }
#line 2273 "parser/parser.tab.c"
    break;

  case 47: /* unpacked_structured_type: FILE_TOK  */
#line 281 "parser/parser.y"
               {
        (yyval.node) = create_file_of_type_node(NULL, create_location((yyloc)));
      }
#line 2281 "parser/parser.tab.c"
    break;

  case 48: /* unpacked_structured_type: FILE_TOK OF type  */
#line 284 "parser/parser.y"
                       {
        (yyval.node) = create_file_of_type_node((yyvsp[0].node), create_location((yyloc)));
      }
#line 2289 "parser/parser.tab.c"
    break;

  case 49: /* index_list: simple_type  */
#line 289 "parser/parser.y"
                { 
      (yyval.node) = create_index_list_start((yyvsp[0].node), create_location((yyloc))); 
    }
#line 2297 "parser/parser.tab.c"
    break;

  case 50: /* index_list: index_list COMMA simple_type  */
#line 292 "parser/parser.y"
                                 {
      (yyval.node) = append_index_to_list((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2305 "parser/parser.tab.c"
    break;

  case 51: /* field_list: fixed_part  */
#line 297 "parser/parser.y"
               { (yyval.node) = create_field_list((yyvsp[0].node), NULL, create_location((yyloc))); }
#line 2311 "parser/parser.tab.c"
    break;

  case 52: /* field_list: fixed_part SEMICOLON variant_part  */
#line 298 "parser/parser.y"
                                      { (yyval.node) = create_field_list((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2317 "parser/parser.tab.c"
    break;

  case 53: /* field_list: variant_part  */
#line 299 "parser/parser.y"
                 { (yyval.node) = create_field_list(NULL, (yyvsp[0].node), create_location((yyloc))); }
#line 2323 "parser/parser.tab.c"
    break;

  case 54: /* fixed_part: record_field  */
#line 302 "parser/parser.y"
                 { (yyval.node) = create_fixed_part_node(NULL, (yyvsp[0].node), create_location((yyloc))); }
#line 2329 "parser/parser.tab.c"
    break;

  case 55: /* fixed_part: fixed_part SEMICOLON record_field  */
#line 303 "parser/parser.y"
                                      { (yyval.node) = create_fixed_part_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2335 "parser/parser.tab.c"
    break;

  case 57: /* record_field: fieldid_list COLON type  */
#line 307 "parser/parser.y"
                            { (yyval.node) = create_record_field_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2341 "parser/parser.tab.c"
    break;

  case 58: /* fieldid_list: fieldid  */
#line 310 "parser/parser.y"
            { (yyval.node) = create_field_identifier_list_node(NULL, (yyvsp[0].node), create_location((yyloc))); }
#line 2347 "parser/parser.tab.c"
    break;

  case 59: /* fieldid_list: fieldid_list COMMA fieldid  */
#line 311 "parser/parser.y"
                               { (yyval.node) = create_field_identifier_list_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2353 "parser/parser.tab.c"
    break;

  case 60: /* variant_part: CASE tag_field OF variant_list  */
#line 314 "parser/parser.y"
                                   { (yyval.node) = create_case_of_variant_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2359 "parser/parser.tab.c"
    break;

  case 61: /* tag_field: typeid  */
#line 317 "parser/parser.y"
           { (yyval.node) = create_tag_field_node(NULL, (yyvsp[0].node), create_location((yyloc))); }
#line 2365 "parser/parser.tab.c"
    break;

  case 62: /* tag_field: identifier COLON typeid  */
#line 318 "parser/parser.y"
                            { (yyval.node) = create_tag_field_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2371 "parser/parser.tab.c"
    break;

  case 63: /* variant_list: variant  */
#line 321 "parser/parser.y"
            { (yyval.node) = append_variant_list(NULL, (yyvsp[0].node), create_location((yyloc))); }
#line 2377 "parser/parser.tab.c"
    break;

  case 64: /* variant_list: variant_list SEMICOLON variant  */
#line 322 "parser/parser.y"
                                   {
      (yyval.node) = append_variant_list((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2385 "parser/parser.tab.c"
    break;

  case 66: /* variant: case_label_list COLON L_PAREN field_list R_PAREN  */
#line 328 "parser/parser.y"
                                                     {
      (yyval.node) = create_variant_node((yyvsp[-4].node), (yyvsp[-1].node), create_location((yyloc)));
    }
#line 2393 "parser/parser.tab.c"
    break;

  case 67: /* proc_and_func_declaration: proc_or_func  */
#line 333 "parser/parser.y"
                 { (yyval.node) = create_proc_and_func_declarations_node((yyvsp[0].node), create_location((yyloc))); }
#line 2399 "parser/parser.tab.c"
    break;

  case 68: /* proc_and_func_declaration: proc_and_func_declaration SEMICOLON proc_or_func  */
#line 334 "parser/parser.y"
                                                     {
      (yyval.node) = append_proc_and_func_declarations((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2407 "parser/parser.tab.c"
    break;

  case 69: /* proc_or_func: PROCEDURE procid parameters SEMICOLON block_or_forward  */
#line 339 "parser/parser.y"
                                                           { /* identifier of func/proc declaration */ 
      (yyval.node) = create_proc_declaration_node((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2415 "parser/parser.tab.c"
    break;

  case 70: /* proc_or_func: FUNCTION funcid parameters COLON typeid SEMICOLON block_or_forward  */
#line 342 "parser/parser.y"
                                                                       {
      (yyval.node) = create_func_declaration_node((yyvsp[-5].node), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2423 "parser/parser.tab.c"
    break;

  case 71: /* block_or_forward: block  */
#line 347 "parser/parser.y"
          { (yyval.node) = (yyvsp[0].node); }
#line 2429 "parser/parser.tab.c"
    break;

  case 72: /* block_or_forward: FORWARD  */
#line 348 "parser/parser.y"
             { (yyval.node) = create_forward_declaration_node(create_location((yyloc))); }
#line 2435 "parser/parser.tab.c"
    break;

  case 73: /* parameters: L_PAREN optional_parameter_list R_PAREN  */
#line 351 "parser/parser.y"
                                           { (yyval.node) = create_parameters_node((yyvsp[-1].node), create_location((yyloc))); }
#line 2441 "parser/parser.tab.c"
    break;

  case 75: /* optional_parameter_list: formal_parameter_list  */
#line 355 "parser/parser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 2447 "parser/parser.tab.c"
    break;

  case 76: /* formal_parameter_list: formal_parameter_section  */
#line 358 "parser/parser.y"
                             { (yyval.node) = create_formal_parameters_list_node(NULL, (yyvsp[0].node), create_location((yyloc))); }
#line 2453 "parser/parser.tab.c"
    break;

  case 77: /* formal_parameter_list: formal_parameter_list SEMICOLON formal_parameter_section  */
#line 359 "parser/parser.y"
                                                             {
      (yyval.node) = create_formal_parameters_list_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2461 "parser/parser.tab.c"
    break;

  case 78: /* formal_parameter_section: parameterid_list COLON typeid  */
#line 364 "parser/parser.y"
                                  { 
        (yyval.node) = create_formal_parameter_section_node(PARAM_VALUE, (yyvsp[-2].node), (yyvsp[0].node), NULL, NULL, create_location((yyloc))); 
      }
#line 2469 "parser/parser.tab.c"
    break;

  case 79: /* formal_parameter_section: VAR parameterid_list COLON typeid  */
#line 367 "parser/parser.y"
                                        { 
        (yyval.node) = create_formal_parameter_section_node(PARAM_VAR, (yyvsp[-2].node), (yyvsp[0].node), NULL, NULL, create_location((yyloc))); 
      }
#line 2477 "parser/parser.tab.c"
    break;

  case 80: /* formal_parameter_section: PROCEDURE identifier parameters  */
#line 370 "parser/parser.y"
                                      { 
        ASTNode* single_id = create_parameter_identifier_list_node(NULL, (yyvsp[-1].node), create_location((yylsp[-1])));
        (yyval.node) = create_formal_parameter_section_node(PARAM_PROCEDURE, single_id, NULL, (yyvsp[0].node), NULL, create_location((yyloc))); 
      }
#line 2486 "parser/parser.tab.c"
    break;

  case 81: /* formal_parameter_section: FUNCTION identifier parameters COLON typeid  */
#line 374 "parser/parser.y"
                                                  { 
        ASTNode* single_id = create_parameter_identifier_list_node(NULL, (yyvsp[-3].node), create_location((yylsp[-3])));
        (yyval.node) = create_formal_parameter_section_node(PARAM_FUNCTION, single_id, NULL, (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); 
      }
#line 2495 "parser/parser.tab.c"
    break;

  case 82: /* parameterid_list: identifier  */
#line 380 "parser/parser.y"
                { (yyval.node) = create_parameter_identifier_list_node(NULL, (yyvsp[0].node), create_location((yyloc))); }
#line 2501 "parser/parser.tab.c"
    break;

  case 83: /* parameterid_list: parameterid_list COMMA identifier  */
#line 381 "parser/parser.y"
                                       { 
      (yyval.node) = create_parameter_identifier_list_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 2509 "parser/parser.tab.c"
    break;

  case 84: /* statement_list: statement  */
#line 386 "parser/parser.y"
              { (yyval.node) = create_stmt_list_node((yyvsp[0].node), create_location((yyloc))); }
#line 2515 "parser/parser.tab.c"
    break;

  case 85: /* statement_list: statement_list SEMICOLON optional_statement  */
#line 387 "parser/parser.y"
                                                { (yyval.node) = append_stmt_list((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2521 "parser/parser.tab.c"
    break;

  case 86: /* optional_statement: statement  */
#line 390 "parser/parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 2527 "parser/parser.tab.c"
    break;

  case 88: /* statement: variable ASSIGN expression  */
#line 394 "parser/parser.y"
                               { (yyval.node) = create_assign_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2533 "parser/parser.tab.c"
    break;

  case 89: /* statement: BEGIN_TOK statement_list END  */
#line 395 "parser/parser.y"
                                  { (yyval.node) = create_stmt_list_node((yyvsp[-1].node), create_location((yyloc))); }
#line 2539 "parser/parser.tab.c"
    break;

  case 90: /* statement: IF expression THEN statement  */
#line 396 "parser/parser.y"
                                                       { (yyval.node) = create_if_stmt_node((yyvsp[-2].node), (yyvsp[0].node), NULL, create_location((yyloc))); }
#line 2545 "parser/parser.tab.c"
    break;

  case 91: /* statement: IF expression THEN statement ELSE statement  */
#line 397 "parser/parser.y"
                                                { (yyval.node) = create_if_stmt_node((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2551 "parser/parser.tab.c"
    break;

  case 92: /* statement: CASE expression OF case_list END  */
#line 398 "parser/parser.y"
                                     { (yyval.node) = create_case_stmt_node((yyvsp[-3].node), (yyvsp[-1].node), NULL, create_location((yyloc))); }
#line 2557 "parser/parser.tab.c"
    break;

  case 93: /* statement: CASE expression OF case_list SEMICOLON case_else END  */
#line 399 "parser/parser.y"
                                                         { (yyval.node) = create_case_stmt_with_else_node((yyvsp[-5].node), (yyvsp[-3].node), (yyvsp[-1].node), create_location((yyloc))); }
#line 2563 "parser/parser.tab.c"
    break;

  case 94: /* statement: WHILE expression DO statement  */
#line 400 "parser/parser.y"
                                  { (yyval.node) = create_while_stmt_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2569 "parser/parser.tab.c"
    break;

  case 95: /* statement: REPEAT statement_list UNTIL expression  */
#line 401 "parser/parser.y"
                                           { (yyval.node) = create_repeat_until_stmt_list_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2575 "parser/parser.tab.c"
    break;

  case 96: /* statement: FOR varid ASSIGN for_list DO statement  */
#line 402 "parser/parser.y"
                                           { (yyval.node) = create_for_stmt_node((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2581 "parser/parser.tab.c"
    break;

  case 97: /* statement: procid  */
#line 403 "parser/parser.y"
           { (yyval.node) = create_procedure_call_node((yyvsp[0].node), NULL, create_location((yyloc))); }
#line 2587 "parser/parser.tab.c"
    break;

  case 98: /* statement: procid L_PAREN optional_expression_list R_PAREN  */
#line 404 "parser/parser.y"
                                                    { (yyval.node) = create_procedure_call_node((yyvsp[-3].node), (yyvsp[-1].node), create_location((yyloc))); }
#line 2593 "parser/parser.tab.c"
    break;

  case 99: /* statement: GOTO label  */
#line 405 "parser/parser.y"
               { (yyval.node) = create_goto_label_node((yyvsp[0].node), create_location((yyloc))); }
#line 2599 "parser/parser.tab.c"
    break;

  case 100: /* statement: WITH record_variable_list DO statement  */
#line 406 "parser/parser.y"
                                           { (yyval.node) = create_with_record_list_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2605 "parser/parser.tab.c"
    break;

  case 101: /* statement: label COLON statement  */
#line 407 "parser/parser.y"
                          { (yyval.node) = create_label_stmt_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2611 "parser/parser.tab.c"
    break;

  case 102: /* variable: varid  */
#line 410 "parser/parser.y"
          { (yyval.node) = (yyvsp[0].node); }
#line 2617 "parser/parser.tab.c"
    break;

  case 103: /* variable: variable L_BRACKET subscript_list R_BRACKET  */
#line 411 "parser/parser.y"
                                                { (yyval.node) = create_array_access_node((yyvsp[-3].node), (yyvsp[-1].node), create_location((yyloc))); }
#line 2623 "parser/parser.tab.c"
    break;

  case 104: /* variable: variable DOT fieldid  */
#line 412 "parser/parser.y"
                         { (yyval.node) = create_record_access_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2629 "parser/parser.tab.c"
    break;

  case 105: /* variable: variable CARET  */
#line 413 "parser/parser.y"
                   { (yyval.node) = create_pointer_deref_node((yyvsp[-1].node), create_location((yyloc))); }
#line 2635 "parser/parser.tab.c"
    break;

  case 106: /* subscript_list: expression  */
#line 416 "parser/parser.y"
               { 
        (yyval.node) = create_subscript_list_node((yyvsp[0].node), create_location((yyloc))); 
    }
#line 2643 "parser/parser.tab.c"
    break;

  case 107: /* subscript_list: subscript_list COMMA expression  */
#line 419 "parser/parser.y"
                                    { 
        (yyval.node) = append_subscript_list_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2651 "parser/parser.tab.c"
    break;

  case 108: /* case_list: case_item  */
#line 424 "parser/parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 2657 "parser/parser.tab.c"
    break;

  case 109: /* case_list: case_list SEMICOLON case_item  */
#line 425 "parser/parser.y"
                                  { 
      (yyval.node) = append_case_item((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2665 "parser/parser.tab.c"
    break;

  case 110: /* case_item: case_label_list COLON statement  */
#line 430 "parser/parser.y"
                                    { 
      (yyval.node) = create_case_item_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2673 "parser/parser.tab.c"
    break;

  case 111: /* case_label_list: case_label  */
#line 435 "parser/parser.y"
               { (yyval.node) = create_case_label_list((yyvsp[0].node), create_location((yyloc))); }
#line 2679 "parser/parser.tab.c"
    break;

  case 112: /* case_label_list: case_label_list COMMA case_label  */
#line 436 "parser/parser.y"
                                     { 
      (yyval.node) = append_case_label_list((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2687 "parser/parser.tab.c"
    break;

  case 113: /* case_label: constant  */
#line 441 "parser/parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 2693 "parser/parser.tab.c"
    break;

  case 114: /* case_label: constant DOTDOT constant  */
#line 442 "parser/parser.y"
                             { 
      (yyval.node) = create_constant_range_node((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2701 "parser/parser.tab.c"
    break;

  case 115: /* case_else: ELSE statement SEMICOLON  */
#line 447 "parser/parser.y"
                             {
      (yyval.node) = create_case_else_node((yyvsp[-1].node), create_location((yyloc)));
    }
#line 2709 "parser/parser.tab.c"
    break;

  case 116: /* for_list: expression TO expression  */
#line 452 "parser/parser.y"
                             { 
      (yyval.node) = create_for_list_node((yyvsp[-2].node), (yyvsp[0].node), false, create_location((yyloc))); 
    }
#line 2717 "parser/parser.tab.c"
    break;

  case 117: /* for_list: expression DOWNTO expression  */
#line 455 "parser/parser.y"
                                 { 
      (yyval.node) = create_for_list_node((yyvsp[-2].node), (yyvsp[0].node), true, create_location((yyloc))); 
    }
#line 2725 "parser/parser.tab.c"
    break;

  case 119: /* optional_expression_list: expression_list  */
#line 461 "parser/parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 2731 "parser/parser.tab.c"
    break;

  case 120: /* expression_list: expression  */
#line 464 "parser/parser.y"
               { (yyval.node) = create_expression_list((yyvsp[0].node), create_location((yyloc))); }
#line 2737 "parser/parser.tab.c"
    break;

  case 121: /* expression_list: expression_list COMMA expression  */
#line 465 "parser/parser.y"
                                     { (yyval.node) = append_expression_list((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); }
#line 2743 "parser/parser.tab.c"
    break;

  case 122: /* label: unsigned_integer  */
#line 468 "parser/parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 2749 "parser/parser.tab.c"
    break;

  case 123: /* record_variable_list: variable  */
#line 471 "parser/parser.y"
             { (yyval.node) = create_record_variable_list_node((yyvsp[0].node), create_location((yyloc))); }
#line 2755 "parser/parser.tab.c"
    break;

  case 124: /* record_variable_list: record_variable_list COMMA variable  */
#line 472 "parser/parser.y"
                                        { 
      (yyval.node) = append_record_variable_list((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2763 "parser/parser.tab.c"
    break;

  case 125: /* expression: expression LT additive_expression  */
#line 477 "parser/parser.y"
                                      { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_LT, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2771 "parser/parser.tab.c"
    break;

  case 126: /* expression: expression LTE additive_expression  */
#line 480 "parser/parser.y"
                                       { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_LTE, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2779 "parser/parser.tab.c"
    break;

  case 127: /* expression: expression EQ additive_expression  */
#line 483 "parser/parser.y"
                                      { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_EQ, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2787 "parser/parser.tab.c"
    break;

  case 128: /* expression: expression NEQ additive_expression  */
#line 486 "parser/parser.y"
                                       { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_NEQ, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2795 "parser/parser.tab.c"
    break;

  case 129: /* expression: expression GTE additive_expression  */
#line 489 "parser/parser.y"
                                       { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_GTE, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2803 "parser/parser.tab.c"
    break;

  case 130: /* expression: expression GT additive_expression  */
#line 492 "parser/parser.y"
                                      { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_GT, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2811 "parser/parser.tab.c"
    break;

  case 131: /* expression: additive_expression  */
#line 495 "parser/parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 2817 "parser/parser.tab.c"
    break;

  case 132: /* additive_expression: additive_expression PLUS multiplicative_expression  */
#line 498 "parser/parser.y"
                                                       { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_PLUS, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2825 "parser/parser.tab.c"
    break;

  case 133: /* additive_expression: additive_expression MINUS multiplicative_expression  */
#line 501 "parser/parser.y"
                                                        { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_MINUS, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2833 "parser/parser.tab.c"
    break;

  case 134: /* additive_expression: additive_expression OR multiplicative_expression  */
#line 504 "parser/parser.y"
                                                     { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_OR, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2841 "parser/parser.tab.c"
    break;

  case 135: /* additive_expression: multiplicative_expression  */
#line 507 "parser/parser.y"
                              { (yyval.node) = (yyvsp[0].node); }
#line 2847 "parser/parser.tab.c"
    break;

  case 136: /* multiplicative_expression: multiplicative_expression TIMES unary_expression  */
#line 510 "parser/parser.y"
                                                     { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_TIMES, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2855 "parser/parser.tab.c"
    break;

  case 137: /* multiplicative_expression: multiplicative_expression DIVIDE unary_expression  */
#line 513 "parser/parser.y"
                                                      { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_DIVIDE, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2863 "parser/parser.tab.c"
    break;

  case 138: /* multiplicative_expression: multiplicative_expression DIV unary_expression  */
#line 516 "parser/parser.y"
                                                   { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_DIV, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2871 "parser/parser.tab.c"
    break;

  case 139: /* multiplicative_expression: multiplicative_expression MOD unary_expression  */
#line 519 "parser/parser.y"
                                                   { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_MOD, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2879 "parser/parser.tab.c"
    break;

  case 140: /* multiplicative_expression: multiplicative_expression AND unary_expression  */
#line 522 "parser/parser.y"
                                                   { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_AND, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2887 "parser/parser.tab.c"
    break;

  case 141: /* multiplicative_expression: multiplicative_expression IN unary_expression  */
#line 525 "parser/parser.y"
                                                  { 
      (yyval.node) = create_binary_expression((yyvsp[-2].node), BINOP_IN, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2895 "parser/parser.tab.c"
    break;

  case 142: /* multiplicative_expression: unary_expression  */
#line 528 "parser/parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2901 "parser/parser.tab.c"
    break;

  case 143: /* unary_expression: PLUS unary_expression  */
#line 531 "parser/parser.y"
                          { 
      (yyval.node) = create_unary_expression(UNOP_PLUS, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2909 "parser/parser.tab.c"
    break;

  case 144: /* unary_expression: MINUS unary_expression  */
#line 534 "parser/parser.y"
                                     { 
      (yyval.node) = create_unary_expression(UNOP_MINUS, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2917 "parser/parser.tab.c"
    break;

  case 145: /* unary_expression: NOT unary_expression  */
#line 537 "parser/parser.y"
                                   { 
      (yyval.node) = create_unary_expression(UNOP_NOT, (yyvsp[0].node), create_location((yyloc))); 
    }
#line 2925 "parser/parser.tab.c"
    break;

  case 146: /* unary_expression: primary_expression  */
#line 540 "parser/parser.y"
                       { (yyval.node) = (yyvsp[0].node); }
#line 2931 "parser/parser.tab.c"
    break;

  case 147: /* primary_expression: variable  */
#line 543 "parser/parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 2937 "parser/parser.tab.c"
    break;

  case 148: /* primary_expression: unsigned_integer  */
#line 544 "parser/parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2943 "parser/parser.tab.c"
    break;

  case 149: /* primary_expression: unsigned_real  */
#line 545 "parser/parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 2949 "parser/parser.tab.c"
    break;

  case 150: /* primary_expression: string_literal  */
#line 546 "parser/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 2955 "parser/parser.tab.c"
    break;

  case 151: /* primary_expression: char_literal  */
#line 547 "parser/parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 2961 "parser/parser.tab.c"
    break;

  case 152: /* primary_expression: boolean_literal  */
#line 548 "parser/parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 2967 "parser/parser.tab.c"
    break;

  case 153: /* primary_expression: NIL  */
#line 549 "parser/parser.y"
        {
      (yyval.node) = create_nil_literal(create_location((yyloc)));
    }
#line 2975 "parser/parser.tab.c"
    break;

  case 154: /* primary_expression: funcid L_PAREN optional_expression_list R_PAREN  */
#line 552 "parser/parser.y"
                                                    {
      (yyval.node) = create_function_call_node((yyvsp[-3].node), (yyvsp[-1].node), create_location((yyloc)));
    }
#line 2983 "parser/parser.tab.c"
    break;

  case 155: /* primary_expression: L_BRACKET element_list R_BRACKET  */
#line 555 "parser/parser.y"
                                     { (yyval.node) = (yyvsp[-1].node); }
#line 2989 "parser/parser.tab.c"
    break;

  case 156: /* primary_expression: L_PAREN expression R_PAREN  */
#line 556 "parser/parser.y"
                               { (yyval.node) = (yyvsp[-1].node); }
#line 2995 "parser/parser.tab.c"
    break;

  case 157: /* element_list: empty  */
#line 559 "parser/parser.y"
          { 
      (yyval.node) = create_set_literal(create_location((yyloc))); 
    }
#line 3003 "parser/parser.tab.c"
    break;

  case 158: /* element_list: element_list_non_empty  */
#line 562 "parser/parser.y"
                           { 
      (yyval.node) = (yyvsp[0].node); 
    }
#line 3011 "parser/parser.tab.c"
    break;

  case 159: /* element_list_non_empty: element  */
#line 567 "parser/parser.y"
            { 
      (yyval.node) = create_set_literal_with_element((yyvsp[0].node), create_location((yyloc))); 
    }
#line 3019 "parser/parser.tab.c"
    break;

  case 160: /* element_list_non_empty: element_list_non_empty COMMA element  */
#line 570 "parser/parser.y"
                                         {
      (yyval.node) = add_element_to_set_literal((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 3027 "parser/parser.tab.c"
    break;

  case 161: /* element: expression  */
#line 575 "parser/parser.y"
               { 
      (yyval.node) = create_set_element((yyvsp[0].node), create_location((yyloc))); 
    }
#line 3035 "parser/parser.tab.c"
    break;

  case 162: /* element: expression DOTDOT expression  */
#line 578 "parser/parser.y"
                                 {
      (yyval.node) = create_set_range_element((yyvsp[-2].node), (yyvsp[0].node), create_location((yyloc)));
    }
#line 3043 "parser/parser.tab.c"
    break;

  case 163: /* constid: identifier  */
#line 583 "parser/parser.y"
               {
      (yyval.node) = update_identifier_node_kind((yyvsp[0].node), SYMBOL_CONSTANT);
   }
#line 3051 "parser/parser.tab.c"
    break;

  case 164: /* typeid: CHAR  */
#line 588 "parser/parser.y"
         { (yyval.node) = create_builtin_type_identifier("char", create_location((yyloc))); }
#line 3057 "parser/parser.tab.c"
    break;

  case 165: /* typeid: BOOLEAN  */
#line 589 "parser/parser.y"
            { (yyval.node) = create_builtin_type_identifier("boolean", create_location((yyloc))); }
#line 3063 "parser/parser.tab.c"
    break;

  case 166: /* typeid: INTEGER  */
#line 590 "parser/parser.y"
            { (yyval.node) = create_builtin_type_identifier("integer", create_location((yyloc))); }
#line 3069 "parser/parser.tab.c"
    break;

  case 167: /* typeid: REAL  */
#line 591 "parser/parser.y"
         { (yyval.node) = create_builtin_type_identifier("real", create_location((yyloc))); }
#line 3075 "parser/parser.tab.c"
    break;

  case 168: /* typeid: STRING  */
#line 592 "parser/parser.y"
           { (yyval.node) = create_builtin_type_identifier("string", create_location((yyloc))); }
#line 3081 "parser/parser.tab.c"
    break;

  case 169: /* typeid: identifier  */
#line 593 "parser/parser.y"
               {
      ASTNode *typeId = update_identifier_node_kind((yyvsp[0].node), SYMBOL_TYPE);
      (yyval.node) = create_type_identifier((IdentifierNode*)typeId, create_location((yyloc)));
    }
#line 3090 "parser/parser.tab.c"
    break;

  case 170: /* funcid: identifier  */
#line 599 "parser/parser.y"
              { 
    (yyval.node) = update_identifier_node_kind((yyvsp[0].node), SYMBOL_FUNCTION);
  }
#line 3098 "parser/parser.tab.c"
    break;

  case 171: /* funcid: CHR  */
#line 602 "parser/parser.y"
        { (yyval.node) = create_builtin_identifier("Chr", create_location((yyloc))); }
#line 3104 "parser/parser.tab.c"
    break;

  case 172: /* procid: identifier  */
#line 606 "parser/parser.y"
             { 
    (yyval.node) = update_identifier_node_kind((yyvsp[0].node), SYMBOL_PROCEDURE);
  }
#line 3112 "parser/parser.tab.c"
    break;

  case 173: /* procid: WRITE  */
#line 609 "parser/parser.y"
          { (yyval.node) = create_builtin_identifier("write", create_location((yyloc))); }
#line 3118 "parser/parser.tab.c"
    break;

  case 174: /* procid: WRITELN  */
#line 610 "parser/parser.y"
            { (yyval.node) = create_builtin_identifier("writeln", create_location((yyloc))); }
#line 3124 "parser/parser.tab.c"
    break;

  case 175: /* procid: READ  */
#line 611 "parser/parser.y"
         { (yyval.node) = create_builtin_identifier("read", create_location((yyloc))); }
#line 3130 "parser/parser.tab.c"
    break;

  case 176: /* procid: READLN  */
#line 612 "parser/parser.y"
           { (yyval.node) = create_builtin_identifier("readln", create_location((yyloc))); }
#line 3136 "parser/parser.tab.c"
    break;

  case 177: /* fieldid: identifier  */
#line 615 "parser/parser.y"
             { 
    (yyval.node) = update_identifier_node_kind((yyvsp[0].node), SYMBOL_FIELD);
  }
#line 3144 "parser/parser.tab.c"
    break;

  case 178: /* varid: identifier  */
#line 620 "parser/parser.y"
             {
    (yyval.node) = update_identifier_node_kind((yyvsp[0].node), SYMBOL_VARIABLE);
  }
#line 3152 "parser/parser.tab.c"
    break;

  case 179: /* identifier: IDENTIFIER  */
#line 625 "parser/parser.y"
              { (yyval.node) = create_identifier_node((yyvsp[0].string), create_location((yyloc))); }
#line 3158 "parser/parser.tab.c"
    break;

  case 180: /* unsigned_integer: INTEGER_LITERAL  */
#line 628 "parser/parser.y"
                    {
      (yyval.node) = create_unsigned_integer_node((yyvsp[0].integer), create_location((yyloc)));
    }
#line 3166 "parser/parser.tab.c"
    break;

  case 181: /* unsigned_real: REAL_LITERAL  */
#line 633 "parser/parser.y"
                 {
      (yyval.node) = create_unsigned_real_node((yyvsp[0].number), create_location((yyloc)));
    }
#line 3174 "parser/parser.tab.c"
    break;

  case 182: /* integer_literal: INTEGER_LITERAL  */
#line 638 "parser/parser.y"
                    {
      (yyval.node) = create_integer_literal((yyvsp[0].integer), create_location((yyloc)));
    }
#line 3182 "parser/parser.tab.c"
    break;

  case 183: /* real_literal: REAL_LITERAL  */
#line 643 "parser/parser.y"
                 {
      (yyval.node) = create_real_literal((yyvsp[0].number), create_location((yyloc)));
    }
#line 3190 "parser/parser.tab.c"
    break;

  case 184: /* string_literal: STRING_LITERAL  */
#line 648 "parser/parser.y"
                   {
      (yyval.node) = create_string_literal((yyvsp[0].string), create_location((yyloc)));
    }
#line 3198 "parser/parser.tab.c"
    break;

  case 185: /* char_literal: CHAR_LITERAL  */
#line 653 "parser/parser.y"
                 {
      (yyval.node) = create_char_literal((yyvsp[0].character), create_location((yyloc)));
    }
#line 3206 "parser/parser.tab.c"
    break;

  case 186: /* boolean_literal: BOOLEAN_LITERAL  */
#line 658 "parser/parser.y"
                    {
      (yyval.node) = create_boolean_literal((yyvsp[0].boolean), create_location((yyloc)));
    }
#line 3214 "parser/parser.tab.c"
    break;

  case 187: /* empty: %empty  */
#line 662 "parser/parser.y"
              { (yyval.node) = NULL; }
#line 3220 "parser/parser.tab.c"
    break;


#line 3224 "parser/parser.tab.c"

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

