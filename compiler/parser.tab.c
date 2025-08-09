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
#line 1 "src/parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/ASTNodes.h"

void yyerror(const char *s);
int yylex(void);

block_item_t *ast_root = NULL;

static int indent_level = 0;
void indent() {
    for (int i=0; i < indent_level; i++)
        fprintf(stderr, "  ");
}

#line 89 "parser.tab.c"

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
  YYSYMBOL_FUNCTION = 3,                   /* FUNCTION  */
  YYSYMBOL_CHAR = 4,                       /* CHAR  */
  YYSYMBOL_SHORT = 5,                      /* SHORT  */
  YYSYMBOL_INT = 6,                        /* INT  */
  YYSYMBOL_LONG = 7,                       /* LONG  */
  YYSYMBOL_STATIC = 8,                     /* STATIC  */
  YYSYMBOL_MUT = 9,                        /* MUT  */
  YYSYMBOL_IMMUT = 10,                     /* IMMUT  */
  YYSYMBOL_RETURN = 11,                    /* RETURN  */
  YYSYMBOL_TYPE = 12,                      /* TYPE  */
  YYSYMBOL_STRUCT = 13,                    /* STRUCT  */
  YYSYMBOL_ENUM = 14,                      /* ENUM  */
  YYSYMBOL_UNION = 15,                     /* UNION  */
  YYSYMBOL_IF = 16,                        /* IF  */
  YYSYMBOL_FOR = 17,                       /* FOR  */
  YYSYMBOL_EQ = 18,                        /* EQ  */
  YYSYMBOL_NEQ = 19,                       /* NEQ  */
  YYSYMBOL_ARROW = 20,                     /* ARROW  */
  YYSYMBOL_INTEGER_LITERAL = 21,           /* INTEGER_LITERAL  */
  YYSYMBOL_IDENTIFIER = 22,                /* IDENTIFIER  */
  YYSYMBOL_23_ = 23,                       /* '+'  */
  YYSYMBOL_24_ = 24,                       /* '-'  */
  YYSYMBOL_25_ = 25,                       /* '*'  */
  YYSYMBOL_26_ = 26,                       /* '/'  */
  YYSYMBOL_27_ = 27,                       /* ';'  */
  YYSYMBOL_28_ = 28,                       /* '('  */
  YYSYMBOL_29_ = 29,                       /* ')'  */
  YYSYMBOL_30_ = 30,                       /* ','  */
  YYSYMBOL_31_ = 31,                       /* '{'  */
  YYSYMBOL_32_ = 32,                       /* '}'  */
  YYSYMBOL_33_ = 33,                       /* '='  */
  YYSYMBOL_34_ = 34,                       /* ':'  */
  YYSYMBOL_YYACCEPT = 35,                  /* $accept  */
  YYSYMBOL_input = 36,                     /* input  */
  YYSYMBOL_block_item_list = 37,           /* block_item_list  */
  YYSYMBOL_block_item = 38,                /* block_item  */
  YYSYMBOL_function_call = 39,             /* function_call  */
  YYSYMBOL_arg_list = 40,                  /* arg_list  */
  YYSYMBOL_arg = 41,                       /* arg  */
  YYSYMBOL_statement = 42,                 /* statement  */
  YYSYMBOL_if_statement = 43,              /* if_statement  */
  YYSYMBOL_for_statement = 44,             /* for_statement  */
  YYSYMBOL_type_definition = 45,           /* type_definition  */
  YYSYMBOL_variable_declaration = 46,      /* variable_declaration  */
  YYSYMBOL_initializer = 47,               /* initializer  */
  YYSYMBOL_static_var = 48,                /* static_var  */
  YYSYMBOL_mutable_var = 49,               /* mutable_var  */
  YYSYMBOL_function_definition = 50,       /* function_definition  */
  YYSYMBOL_primitive = 51,                 /* primitive  */
  YYSYMBOL_type = 52,                      /* type  */
  YYSYMBOL_enum_type = 53,                 /* enum_type  */
  YYSYMBOL_enum_members = 54,              /* enum_members  */
  YYSYMBOL_enum_member = 55,               /* enum_member  */
  YYSYMBOL_struct_type = 56,               /* struct_type  */
  YYSYMBOL_union_type = 57,                /* union_type  */
  YYSYMBOL_lamda_type = 58,                /* lamda_type  */
  YYSYMBOL_struct_members = 59,            /* struct_members  */
  YYSYMBOL_struct_member = 60,             /* struct_member  */
  YYSYMBOL_union_members = 61,             /* union_members  */
  YYSYMBOL_union_member = 62,              /* union_member  */
  YYSYMBOL_parameter_list = 63,            /* parameter_list  */
  YYSYMBOL_parameter = 64,                 /* parameter  */
  YYSYMBOL_lamda = 65,                     /* lamda  */
  YYSYMBOL_expression = 66,                /* expression  */
  YYSYMBOL_numeric_expression = 67         /* numeric_expression  */
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
typedef yytype_uint8 yy_state_t;

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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   143

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  74
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  136

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   277


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
      28,    29,    25,    23,    30,    24,     2,    26,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    34,    27,
       2,    33,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    31,     2,    32,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    76,    76,    82,    83,    99,   100,   101,   102,   103,
     104,   108,   112,   113,   114,   130,   134,   135,   136,   137,
     141,   145,   149,   153,   157,   158,   162,   163,   167,   168,
     172,   176,   177,   178,   179,   183,   184,   185,   186,   187,
     188,   192,   196,   197,   213,   214,   218,   223,   227,   231,
     235,   236,   237,   256,   260,   261,   262,   281,   285,   286,
     287,   306,   310,   314,   315,   316,   322,   326,   332,   333,
     336,   339,   342,   345,   346
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "FUNCTION", "CHAR",
  "SHORT", "INT", "LONG", "STATIC", "MUT", "IMMUT", "RETURN", "TYPE",
  "STRUCT", "ENUM", "UNION", "IF", "FOR", "EQ", "NEQ", "ARROW",
  "INTEGER_LITERAL", "IDENTIFIER", "'+'", "'-'", "'*'", "'/'", "';'",
  "'('", "')'", "','", "'{'", "'}'", "'='", "':'", "$accept", "input",
  "block_item_list", "block_item", "function_call", "arg_list", "arg",
  "statement", "if_statement", "for_statement", "type_definition",
  "variable_declaration", "initializer", "static_var", "mutable_var",
  "function_definition", "primitive", "type", "enum_type", "enum_members",
  "enum_member", "struct_type", "union_type", "lamda_type",
  "struct_members", "struct_member", "union_members", "union_member",
  "parameter_list", "parameter", "lamda", "expression",
  "numeric_expression", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-86)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-3)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -86,    11,    51,   -86,    13,   -86,    -9,    33,    15,   -86,
     -86,    -5,   -86,    -1,   -86,   -86,   -86,   -86,   -86,   -86,
     -13,    18,    21,   -86,   -86,    37,   101,    32,    50,    47,
      65,    -9,    -9,    63,    12,   -86,    41,    87,    73,   -86,
     -86,   -86,   -86,    66,   -86,    65,    65,    65,    65,    70,
     -86,    43,    65,    94,    23,   -86,   -86,   -86,    43,    68,
      70,   -86,   -86,   -86,    74,    49,    49,   -86,   -86,    80,
      69,   -86,   -86,   -86,   -86,    72,    84,    90,   -86,    70,
     -86,   -86,   -86,   -86,   -86,   -86,    87,    -7,   -86,    -9,
     -86,    43,   -86,    43,    88,   106,   107,   108,    77,   -86,
     -86,   111,    99,    43,   100,   -16,   -86,   -86,   -15,   -86,
     102,   -14,   -86,   113,    -7,    -9,   -86,    -7,    43,   -86,
     -86,   107,   -86,    43,   -86,   -86,    43,   -86,   -86,   -86,
     110,   -86,   112,   -86,   -86,   -86
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,    26,     1,     0,    27,     0,     0,     0,    21,
      66,    67,     5,    58,     3,     4,    68,     6,    17,    18,
       0,     0,     0,     8,    64,     0,    63,     0,     0,     0,
       0,    12,     0,    67,     0,    59,     0,     0,    26,    10,
       9,    28,    29,     0,     7,     0,     0,     0,     0,    58,
      16,     0,     0,     0,     0,    13,    15,    73,     0,     0,
       0,    65,    74,    19,     0,    69,    70,    71,    72,     0,
       0,    31,    32,    33,    34,     0,     0,     0,    36,    58,
      35,    22,    40,    38,    39,    37,     0,     0,    11,     0,
      61,     0,    60,     0,     0,    50,    42,    54,     0,    20,
      14,     0,    24,     0,     0,     0,    51,    46,     0,    44,
       0,     0,    55,     0,     0,     0,    23,     0,     0,    47,
      52,    45,    41,     0,    48,    56,     0,    62,    25,    30,
       0,    43,     0,    49,    53,    57
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -86,   -86,   121,   -86,   -86,   -86,    52,   -85,   -86,   -86,
     -86,   -86,   -86,   -86,   -86,   -86,   -86,   -57,   -86,   -86,
      17,   -86,   -86,   -86,   -86,    35,   -86,    31,   -46,    83,
     -86,    -6,    -8
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,    15,    16,    54,    55,    17,    18,    19,
      20,    21,   116,    22,    43,    23,    80,    81,    82,   108,
     109,    83,    84,    85,   105,   106,   111,   112,    34,    35,
      24,    25,    26
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      28,    90,    99,    70,     6,    37,   104,    36,   110,     8,
       9,     3,    10,    11,    39,   121,   119,   122,   124,    13,
      10,    33,    53,    31,    14,    56,    57,    13,    32,   127,
      41,    42,   129,    98,   101,    27,   102,    65,    66,    67,
      68,    59,    60,    30,    86,    40,   117,    71,    72,    73,
      74,    -2,    88,    89,     4,    29,    75,    76,    77,     5,
      49,   130,     6,     7,    44,    78,   132,     8,     9,   133,
      61,    79,    10,    11,    47,    48,     4,    50,    12,    13,
      51,     5,    14,    56,     6,     7,    10,    11,    64,     8,
       9,    31,    69,    52,    10,    11,    32,    58,    94,    60,
      12,    13,    91,    95,    14,    63,   113,    60,    93,   128,
      45,    46,    47,    48,    58,    96,    62,    45,    46,    47,
      48,    97,   103,    87,    45,    46,    47,    48,   104,   107,
     110,   114,   115,   126,   118,    38,   123,   134,   131,   135,
     120,   100,   125,    92
};

static const yytype_int8 yycheck[] =
{
       6,    58,    87,    49,    11,    13,    22,    13,    22,    16,
      17,     0,    21,    22,    27,    30,    32,    32,    32,    28,
      21,    22,    30,    28,    31,    31,    32,    28,    33,   114,
       9,    10,   117,    79,    91,    22,    93,    45,    46,    47,
      48,    29,    30,    28,    52,    27,   103,     4,     5,     6,
       7,     0,    29,    30,     3,    22,    13,    14,    15,     8,
      28,   118,    11,    12,    27,    22,   123,    16,    17,   126,
      29,    28,    21,    22,    25,    26,     3,    27,    27,    28,
      33,     8,    31,    89,    11,    12,    21,    22,    22,    16,
      17,    28,    22,    28,    21,    22,    33,    34,    29,    30,
      27,    28,    34,    31,    31,    32,    29,    30,    34,   115,
      23,    24,    25,    26,    34,    31,    29,    23,    24,    25,
      26,    31,    34,    29,    23,    24,    25,    26,    22,    22,
      22,    20,    33,    20,    34,    14,    34,    27,   121,    27,
     105,    89,   111,    60
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    36,    37,     0,     3,     8,    11,    12,    16,    17,
      21,    22,    27,    28,    31,    38,    39,    42,    43,    44,
      45,    46,    48,    50,    65,    66,    67,    22,    66,    22,
      28,    28,    33,    22,    63,    64,    66,    67,    37,    27,
      27,     9,    10,    49,    27,    23,    24,    25,    26,    28,
      27,    33,    28,    67,    40,    41,    66,    66,    34,    29,
      30,    29,    29,    32,    22,    67,    67,    67,    67,    22,
      63,     4,     5,     6,     7,    13,    14,    15,    22,    28,
      51,    52,    53,    56,    57,    58,    67,    29,    29,    30,
      52,    34,    64,    34,    29,    31,    31,    31,    63,    42,
      41,    52,    52,    34,    22,    59,    60,    22,    54,    55,
      22,    61,    62,    29,    20,    33,    47,    52,    34,    32,
      60,    30,    32,    34,    32,    62,    20,    42,    66,    42,
      52,    55,    52,    52,    27,    27
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    35,    36,    37,    37,    38,    38,    38,    38,    38,
      38,    39,    40,    40,    40,    41,    42,    42,    42,    42,
      43,    44,    45,    46,    47,    47,    48,    48,    49,    49,
      50,    51,    51,    51,    51,    52,    52,    52,    52,    52,
      52,    53,    54,    54,    54,    54,    55,    56,    57,    58,
      59,    59,    59,    60,    61,    61,    61,    62,    63,    63,
      63,    64,    65,    66,    66,    66,    67,    67,    67,    67,
      67,    67,    67,    67,    67
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     1,     2,     1,     2,
       2,     4,     0,     1,     3,     1,     3,     1,     1,     3,
       5,     1,     4,     6,     0,     2,     0,     1,     1,     1,
       8,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     4,     0,     3,     1,     2,     1,     4,     4,     5,
       0,     1,     2,     4,     0,     1,     2,     4,     0,     1,
       3,     3,     7,     1,     1,     3,     1,     1,     1,     3,
       3,     3,     3,     3,     3
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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
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

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* input: block_item_list  */
#line 76 "src/parser.y"
                    {
        ast_root = (yyvsp[0].block_item);
    }
#line 1238 "parser.tab.c"
    break;

  case 3: /* block_item_list: %empty  */
#line 82 "src/parser.y"
    { (yyval.block_item) = NULL; }
#line 1244 "parser.tab.c"
    break;

  case 4: /* block_item_list: block_item_list block_item  */
#line 83 "src/parser.y"
                                 {  // Proper recursion (supports 1, 2, 3, ... items
        if ((yyvsp[-1].block_item) == NULL) {
            (yyval.block_item) = (yyvsp[0].block_item);  // First item in the list
        } else {
            // Append $2 to the end of the list
            struct block_item_t *last = (yyvsp[-1].block_item);
            while (last->next != NULL) {
                last = last->next;
            }
            last->next = (yyvsp[0].block_item);
            (yyval.block_item) = (yyvsp[-1].block_item);
        }
      }
#line 1262 "parser.tab.c"
    break;

  case 5: /* block_item: ';'  */
#line 99 "src/parser.y"
        { (yyval.block_item) = NULL; }
#line 1268 "parser.tab.c"
    break;

  case 6: /* block_item: statement  */
#line 100 "src/parser.y"
                { (yyval.block_item) = create_block_statement((yyvsp[0].statement)); }
#line 1274 "parser.tab.c"
    break;

  case 7: /* block_item: expression ';'  */
#line 101 "src/parser.y"
                     { (yyval.block_item) = create_block_expression((yyvsp[-1].expression)); }
#line 1280 "parser.tab.c"
    break;

  case 8: /* block_item: function_definition  */
#line 102 "src/parser.y"
                          { (yyval.block_item) = create_block_function_definition((yyvsp[0].function_definition)); }
#line 1286 "parser.tab.c"
    break;

  case 9: /* block_item: variable_declaration ';'  */
#line 103 "src/parser.y"
                               { (yyval.block_item) = create_block_variable_declaration((yyvsp[-1].variable_declaration)); }
#line 1292 "parser.tab.c"
    break;

  case 10: /* block_item: type_definition ';'  */
#line 104 "src/parser.y"
                          { (yyval.block_item) = create_block_type_definition((yyvsp[-1].type_definition)); }
#line 1298 "parser.tab.c"
    break;

  case 11: /* function_call: IDENTIFIER '(' arg_list ')'  */
#line 108 "src/parser.y"
                                { (yyval.function_call) = create_function_call((yyvsp[-3].str_val), (yyvsp[-1].arg)); }
#line 1304 "parser.tab.c"
    break;

  case 12: /* arg_list: %empty  */
#line 112 "src/parser.y"
    { (yyval.arg) = NULL; }
#line 1310 "parser.tab.c"
    break;

  case 13: /* arg_list: arg  */
#line 113 "src/parser.y"
          { (yyval.arg) = (yyvsp[0].arg); }
#line 1316 "parser.tab.c"
    break;

  case 14: /* arg_list: arg_list ',' arg  */
#line 114 "src/parser.y"
                       {  // Proper recursion (supports 1, 2, 3, ... items
        if ((yyvsp[-2].arg) == NULL) {
            (yyval.arg) = (yyvsp[0].arg);  // First item in the list
        } else {
            // Append $2 to the end of the list
            struct argument_list_t *last = (yyvsp[-2].arg);
            while (last->next != NULL) {
                last = last->next;
            }
            last->next = (yyvsp[0].arg);
            (yyval.arg) = (yyvsp[-2].arg);
        }
      }
#line 1334 "parser.tab.c"
    break;

  case 15: /* arg: expression  */
#line 130 "src/parser.y"
               { (yyval.arg) = create_argument_list((yyvsp[0].expression)); }
#line 1340 "parser.tab.c"
    break;

  case 16: /* statement: RETURN expression ';'  */
#line 134 "src/parser.y"
                          { (yyval.statement) = create_statement_return((yyvsp[-1].expression)); }
#line 1346 "parser.tab.c"
    break;

  case 17: /* statement: if_statement  */
#line 135 "src/parser.y"
                   { (yyval.statement) = create_statement_if((yyvsp[0].if_statement)); }
#line 1352 "parser.tab.c"
    break;

  case 18: /* statement: for_statement  */
#line 136 "src/parser.y"
                    { (yyval.statement) = create_statement_for((yyvsp[0].for_statement)); }
#line 1358 "parser.tab.c"
    break;

  case 19: /* statement: '{' block_item_list '}'  */
#line 137 "src/parser.y"
                              { (yyval.statement) = create_statement_block((yyvsp[-1].block_item)); }
#line 1364 "parser.tab.c"
    break;

  case 20: /* if_statement: IF '(' numeric_expression ')' statement  */
#line 141 "src/parser.y"
                                            { (yyval.if_statement) = create_if_statement((yyvsp[-2].expression), (yyvsp[0].statement)); }
#line 1370 "parser.tab.c"
    break;

  case 21: /* for_statement: FOR  */
#line 145 "src/parser.y"
        { (yyval.for_statement) = NULL; }
#line 1376 "parser.tab.c"
    break;

  case 22: /* type_definition: TYPE IDENTIFIER '=' type  */
#line 149 "src/parser.y"
                             { (yyval.type_definition) = create_type_definition((yyvsp[-2].str_val), (yyvsp[0].type)); }
#line 1382 "parser.tab.c"
    break;

  case 23: /* variable_declaration: static_var mutable_var IDENTIFIER ':' type initializer  */
#line 153 "src/parser.y"
                                                           { (yyval.variable_declaration) = create_variable_declaration((yyvsp[-5].primitive), (yyvsp[-4].primitive), (yyvsp[-3].str_val), (yyvsp[-1].type), (yyvsp[0].expression)); }
#line 1388 "parser.tab.c"
    break;

  case 24: /* initializer: %empty  */
#line 157 "src/parser.y"
    { (yyval.expression) = NULL; }
#line 1394 "parser.tab.c"
    break;

  case 25: /* initializer: '=' expression  */
#line 158 "src/parser.y"
                     { (yyval.expression) = (yyvsp[0].expression); }
#line 1400 "parser.tab.c"
    break;

  case 26: /* static_var: %empty  */
#line 162 "src/parser.y"
    { (yyval.primitive) = 0; }
#line 1406 "parser.tab.c"
    break;

  case 27: /* static_var: STATIC  */
#line 163 "src/parser.y"
             { (yyval.primitive) = 1; }
#line 1412 "parser.tab.c"
    break;

  case 28: /* mutable_var: MUT  */
#line 167 "src/parser.y"
        { (yyval.primitive) = 1; }
#line 1418 "parser.tab.c"
    break;

  case 29: /* mutable_var: IMMUT  */
#line 168 "src/parser.y"
            { (yyval.primitive) = 0; }
#line 1424 "parser.tab.c"
    break;

  case 30: /* function_definition: FUNCTION IDENTIFIER '(' parameter_list ')' ':' type statement  */
#line 172 "src/parser.y"
                                                                  { (yyval.function_definition) = create_function_definition((yyvsp[-6].str_val), (yyvsp[-4].parameters), (yyvsp[0].statement), (yyvsp[-1].type)); }
#line 1430 "parser.tab.c"
    break;

  case 31: /* primitive: CHAR  */
#line 176 "src/parser.y"
         { (yyval.primitive) = PRIMITIVE_CHAR; }
#line 1436 "parser.tab.c"
    break;

  case 32: /* primitive: SHORT  */
#line 177 "src/parser.y"
            { (yyval.primitive) = PRIMITIVE_SHORT; }
#line 1442 "parser.tab.c"
    break;

  case 33: /* primitive: INT  */
#line 178 "src/parser.y"
          { (yyval.primitive) = PRIMITIVE_INT; }
#line 1448 "parser.tab.c"
    break;

  case 34: /* primitive: LONG  */
#line 179 "src/parser.y"
           { (yyval.primitive) = PRIMITIVE_LONG; }
#line 1454 "parser.tab.c"
    break;

  case 35: /* type: primitive  */
#line 183 "src/parser.y"
              { (yyval.type) = create_primitive_type((yyvsp[0].primitive)); }
#line 1460 "parser.tab.c"
    break;

  case 36: /* type: IDENTIFIER  */
#line 184 "src/parser.y"
                 { (yyval.type) = create_identifier_type((yyvsp[0].str_val)); }
#line 1466 "parser.tab.c"
    break;

  case 37: /* type: lamda_type  */
#line 185 "src/parser.y"
                 { (yyval.type) = create_lamda_type((yyvsp[0].lamda_type)); }
#line 1472 "parser.tab.c"
    break;

  case 38: /* type: struct_type  */
#line 186 "src/parser.y"
                  { (yyval.type) = create_struct_type((yyvsp[0].struct_member)); }
#line 1478 "parser.tab.c"
    break;

  case 39: /* type: union_type  */
#line 187 "src/parser.y"
                 { (yyval.type) = create_union_type((yyvsp[0].union_member)); }
#line 1484 "parser.tab.c"
    break;

  case 40: /* type: enum_type  */
#line 188 "src/parser.y"
                { (yyval.type) = create_enum_type((yyvsp[0].enum_member)); }
#line 1490 "parser.tab.c"
    break;

  case 41: /* enum_type: ENUM '{' enum_members '}'  */
#line 192 "src/parser.y"
                              { (yyval.enum_member) = (yyvsp[-1].enum_member); }
#line 1496 "parser.tab.c"
    break;

  case 42: /* enum_members: %empty  */
#line 196 "src/parser.y"
    { (yyval.enum_member) = NULL; }
#line 1502 "parser.tab.c"
    break;

  case 43: /* enum_members: enum_members ',' enum_member  */
#line 197 "src/parser.y"
                                   { 
        if ((yyvsp[-2].enum_member) == NULL)
        {
            (yyval.enum_member) = (yyvsp[0].enum_member);
        }
        else
        {
            struct enum_member_t* last = (yyvsp[-2].enum_member);
            while (last->next != NULL)
            {
                last = last->next;
            }
            last->next = (yyvsp[0].enum_member);
            (yyval.enum_member) = (yyvsp[-2].enum_member);
        }
      }
#line 1523 "parser.tab.c"
    break;

  case 44: /* enum_members: enum_member  */
#line 213 "src/parser.y"
                  { (yyval.enum_member) = (yyvsp[0].enum_member); }
#line 1529 "parser.tab.c"
    break;

  case 45: /* enum_members: enum_members ','  */
#line 214 "src/parser.y"
                       { (yyval.enum_member) = (yyvsp[-1].enum_member); }
#line 1535 "parser.tab.c"
    break;

  case 46: /* enum_member: IDENTIFIER  */
#line 218 "src/parser.y"
               { (yyval.enum_member) = create_enum_member((yyvsp[0].str_val), NULL); }
#line 1541 "parser.tab.c"
    break;

  case 47: /* struct_type: STRUCT '{' struct_members '}'  */
#line 223 "src/parser.y"
                                  { (yyval.struct_member) = (yyvsp[-1].struct_member); }
#line 1547 "parser.tab.c"
    break;

  case 48: /* union_type: UNION '{' union_members '}'  */
#line 227 "src/parser.y"
                                { (yyval.union_member) = (yyvsp[-1].union_member); }
#line 1553 "parser.tab.c"
    break;

  case 49: /* lamda_type: '(' parameter_list ')' ARROW type  */
#line 231 "src/parser.y"
                                      { (yyval.lamda_type) = create_type_lamda((yyvsp[-3].parameters), (yyvsp[0].type)); }
#line 1559 "parser.tab.c"
    break;

  case 50: /* struct_members: %empty  */
#line 235 "src/parser.y"
    { (yyval.struct_member) = NULL; }
#line 1565 "parser.tab.c"
    break;

  case 51: /* struct_members: struct_member  */
#line 236 "src/parser.y"
                    { (yyval.struct_member) = (yyvsp[0].struct_member); }
#line 1571 "parser.tab.c"
    break;

  case 52: /* struct_members: struct_members struct_member  */
#line 237 "src/parser.y"
                                   { 
        if ((yyvsp[-1].struct_member) == NULL)
        {
            (yyval.struct_member) = (yyvsp[0].struct_member);
        }
        else
        {
            struct struct_member_t* last = (yyvsp[-1].struct_member);
            while (last->next != NULL)
            {
                last = last->next;
            }
            last->next = (yyvsp[0].struct_member);
            (yyval.struct_member) = (yyvsp[-1].struct_member);
        }
     }
#line 1592 "parser.tab.c"
    break;

  case 53: /* struct_member: IDENTIFIER ':' type ';'  */
#line 256 "src/parser.y"
                            { (yyval.struct_member) = create_struct_member((yyvsp[-3].str_val), (yyvsp[-1].type), NULL); }
#line 1598 "parser.tab.c"
    break;

  case 54: /* union_members: %empty  */
#line 260 "src/parser.y"
    { (yyval.union_member) = NULL; }
#line 1604 "parser.tab.c"
    break;

  case 55: /* union_members: union_member  */
#line 261 "src/parser.y"
                   { (yyval.union_member) = (yyvsp[0].union_member); }
#line 1610 "parser.tab.c"
    break;

  case 56: /* union_members: union_members union_member  */
#line 262 "src/parser.y"
                                 { 
        if ((yyvsp[-1].union_member) == NULL)
        {
            (yyval.union_member) = (yyvsp[0].union_member);
        }
        else
        {
            struct union_member_t* last = (yyvsp[-1].union_member);
            while (last->next != NULL)
            {
                last = last->next;
            }
            last->next = (yyvsp[0].union_member);
            (yyval.union_member) = (yyvsp[-1].union_member);
        }
     }
#line 1631 "parser.tab.c"
    break;

  case 57: /* union_member: IDENTIFIER ':' type ';'  */
#line 281 "src/parser.y"
                            { (yyval.union_member) = create_union_member((yyvsp[-3].str_val), (yyvsp[-1].type), NULL); }
#line 1637 "parser.tab.c"
    break;

  case 58: /* parameter_list: %empty  */
#line 285 "src/parser.y"
    { (yyval.parameters) = NULL; }
#line 1643 "parser.tab.c"
    break;

  case 59: /* parameter_list: parameter  */
#line 286 "src/parser.y"
                { (yyval.parameters) = (yyvsp[0].parameters); }
#line 1649 "parser.tab.c"
    break;

  case 60: /* parameter_list: parameter_list ',' parameter  */
#line 287 "src/parser.y"
                                   {
        if ((yyvsp[-2].parameters) == NULL)
        {
            (yyval.parameters) = (yyvsp[0].parameters);
        }
        else
        {
            struct parameter_list_t* last = (yyvsp[-2].parameters);
            while (last->next != NULL)
            {
                last = last->next;
            }
            last->next = (yyvsp[0].parameters);
            (yyval.parameters) = (yyvsp[-2].parameters);
        }
      }
#line 1670 "parser.tab.c"
    break;

  case 61: /* parameter: IDENTIFIER ':' type  */
#line 306 "src/parser.y"
                        { (yyval.parameters) = create_parameter((yyvsp[-2].str_val), (yyvsp[0].type), NULL); }
#line 1676 "parser.tab.c"
    break;

  case 62: /* lamda: '(' parameter_list ')' ':' type ARROW statement  */
#line 310 "src/parser.y"
                                                    { (yyval.lamda) = create_lamda((yyvsp[-5].parameters), (yyvsp[-2].type), (yyvsp[0].statement)); }
#line 1682 "parser.tab.c"
    break;

  case 63: /* expression: numeric_expression  */
#line 314 "src/parser.y"
                       { (yyval.expression) = (yyvsp[0].expression); }
#line 1688 "parser.tab.c"
    break;

  case 64: /* expression: lamda  */
#line 315 "src/parser.y"
            { (yyval.expression) = create_expression_lamda((yyvsp[0].lamda)); }
#line 1694 "parser.tab.c"
    break;

  case 65: /* expression: '(' expression ')'  */
#line 316 "src/parser.y"
                         {
        (yyval.expression) = (yyvsp[-1].expression);  // Just return inner expression
    }
#line 1702 "parser.tab.c"
    break;

  case 66: /* numeric_expression: INTEGER_LITERAL  */
#line 322 "src/parser.y"
                      {
        literal_t* lit = create_literal_int((yyvsp[0].int_val));
        (yyval.expression) = create_expression_literal(lit);
    }
#line 1711 "parser.tab.c"
    break;

  case 67: /* numeric_expression: IDENTIFIER  */
#line 326 "src/parser.y"
                 {
        // For now, treat identifiers as strings in literals or extend expression_t to support identifiers properly
        // To fully support identifiers, you'd want a separate AST node type for them
        (yyval.expression) = create_expression_identifier(strdup((yyvsp[0].str_val)));
        free((yyvsp[0].str_val));
    }
#line 1722 "parser.tab.c"
    break;

  case 68: /* numeric_expression: function_call  */
#line 332 "src/parser.y"
                    { (yyval.expression) = create_expression_function_call((yyvsp[0].function_call));  }
#line 1728 "parser.tab.c"
    break;

  case 69: /* numeric_expression: numeric_expression '+' numeric_expression  */
#line 333 "src/parser.y"
                                                {
        (yyval.expression) = create_expression_compound((yyvsp[-2].expression), OPERATOR_PLUS, (yyvsp[0].expression));
    }
#line 1736 "parser.tab.c"
    break;

  case 70: /* numeric_expression: numeric_expression '-' numeric_expression  */
#line 336 "src/parser.y"
                                                {
        (yyval.expression) = create_expression_compound((yyvsp[-2].expression), OPERATOR_MINUS, (yyvsp[0].expression));
    }
#line 1744 "parser.tab.c"
    break;

  case 71: /* numeric_expression: numeric_expression '*' numeric_expression  */
#line 339 "src/parser.y"
                                                {
        (yyval.expression) = create_expression_compound((yyvsp[-2].expression), OPERATOR_MULTIPLY, (yyvsp[0].expression));
    }
#line 1752 "parser.tab.c"
    break;

  case 72: /* numeric_expression: numeric_expression '/' numeric_expression  */
#line 342 "src/parser.y"
                                                {
        (yyval.expression) = create_expression_compound((yyvsp[-2].expression), OPERATOR_DIVIDE, (yyvsp[0].expression));
    }
#line 1760 "parser.tab.c"
    break;

  case 73: /* numeric_expression: IDENTIFIER '=' expression  */
#line 345 "src/parser.y"
                                { (yyval.expression) = create_expression_assignment((yyvsp[-2].str_val), (yyvsp[0].expression)); }
#line 1766 "parser.tab.c"
    break;

  case 74: /* numeric_expression: '(' numeric_expression ')'  */
#line 346 "src/parser.y"
                                 { (yyval.expression) = (yyvsp[-1].expression); }
#line 1772 "parser.tab.c"
    break;


#line 1776 "parser.tab.c"

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
      yyerror (YY_("syntax error"));
    }

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
                      yytoken, &yylval);
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


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 349 "src/parser.y"


void yyerror(const char *s) {
    fprintf(stderr, "Parse error: %s\n", s);
}
