/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "tiger.y"


#include <stdio.h>
#include "util.h"
#include "symbol.h"
#include "absyn.h"
#include "errormsg.h"

int yylex(void); /* function prototype */

A_exp absyn_root;

void yyerror(char *s)
{
	EM_error(EM_tokPos, "%s", s);
}



/* Line 268 of yacc.c  */
#line 91 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ID = 258,
     STRING = 259,
     INT = 260,
     DOUBLE = 261,
     ASSIGN = 262,
     OR = 263,
     AND = 264,
     GE = 265,
     GT = 266,
     LE = 267,
     LT = 268,
     NEQ = 269,
     EQ = 270,
     MINUS = 271,
     PLUS = 272,
     DIVIDE = 273,
     TIMES = 274,
     UMINUS = 275,
     COMMA = 276,
     COLON = 277,
     SEMICOLON = 278,
     LPAREN = 279,
     RPAREN = 280,
     LBRACK = 281,
     RBRACK = 282,
     LBRACE = 283,
     RBRACE = 284,
     DOT = 285,
     ARRAY = 286,
     IF = 287,
     THEN = 288,
     ELSE = 289,
     WHILE = 290,
     FOR = 291,
     TO = 292,
     DO = 293,
     LET = 294,
     IN = 295,
     END = 296,
     OF = 297,
     BREAK = 298,
     NIL = 299,
     FUNCTION = 300,
     VAR = 301,
     TYPE = 302
   };
#endif
/* Tokens.  */
#define ID 258
#define STRING 259
#define INT 260
#define DOUBLE 261
#define ASSIGN 262
#define OR 263
#define AND 264
#define GE 265
#define GT 266
#define LE 267
#define LT 268
#define NEQ 269
#define EQ 270
#define MINUS 271
#define PLUS 272
#define DIVIDE 273
#define TIMES 274
#define UMINUS 275
#define COMMA 276
#define COLON 277
#define SEMICOLON 278
#define LPAREN 279
#define RPAREN 280
#define LBRACK 281
#define RBRACK 282
#define LBRACE 283
#define RBRACE 284
#define DOT 285
#define ARRAY 286
#define IF 287
#define THEN 288
#define ELSE 289
#define WHILE 290
#define FOR 291
#define TO 292
#define DO 293
#define LET 294
#define IN 295
#define END 296
#define OF 297
#define BREAK 298
#define NIL 299
#define FUNCTION 300
#define VAR 301
#define TYPE 302




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 21 "tiger.y"

	int pos;
	int ival;
	double dval;
	string sval;
	S_symbol sym;
	A_var var;
	A_exp exp;
    A_dec dec;
	A_decList declist;
	A_expList explist;
	A_efieldList efieldlist;
	A_ty ty;
	A_fieldList fieldlist;
	A_fundec fundec;
	A_namety namety;
	/* et cetera */



/* Line 293 of yacc.c  */
#line 242 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 254 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  37
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   319

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  69
/* YYNRULES -- Number of states.  */
#define YYNSTATES  141

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   302

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
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
      45,    46,    47
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    13,    15,    17,    19,
      21,    23,    29,    36,    41,    45,    49,    53,    57,    61,
      64,    68,    72,    76,    80,    84,    88,    92,    94,    96,
     101,   110,   112,   116,   121,   127,   131,   132,   139,   142,
     143,   145,   147,   149,   152,   154,   159,   161,   165,   169,
     175,   179,   180,   185,   192,   195,   197,   205,   215,   219,
     221,   222,   224,   228,   233,   238,   243,   247,   249,   250
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      49,     0,    -1,    50,    -1,    65,    -1,    66,    -1,    65,
       7,    50,    -1,    44,    -1,    51,    -1,     5,    -1,     6,
      -1,     4,    -1,    39,    55,    40,    64,    41,    -1,    32,
      50,    33,    50,    34,    50,    -1,    32,    50,    33,    50,
      -1,    50,    17,    50,    -1,    50,    16,    50,    -1,    50,
      19,    50,    -1,    50,    18,    50,    -1,    50,    15,    50,
      -1,    16,    50,    -1,    50,    14,    50,    -1,    50,    11,
      50,    -1,    50,    13,    50,    -1,    50,    10,    50,    -1,
      50,    12,    50,    -1,    50,     9,    50,    -1,    50,     8,
      50,    -1,    52,    -1,    54,    -1,    35,    50,    38,    50,
      -1,    36,    68,     7,    50,    37,    50,    38,    50,    -1,
      43,    -1,    24,    64,    25,    -1,    68,    28,    53,    29,
      -1,    68,    15,    50,    21,    53,    -1,    68,    15,    50,
      -1,    -1,    68,    26,    50,    27,    42,    50,    -1,    56,
      55,    -1,    -1,    57,    -1,    61,    -1,    62,    -1,    58,
      57,    -1,    58,    -1,    47,    68,    15,    59,    -1,    68,
      -1,    28,    60,    29,    -1,    31,    42,    68,    -1,    68,
      22,    68,    21,    60,    -1,    68,    22,    68,    -1,    -1,
      46,    68,     7,    50,    -1,    46,    68,    22,    68,     7,
      50,    -1,    63,    62,    -1,    63,    -1,    45,    68,    24,
      60,    25,    15,    50,    -1,    45,    68,    24,    60,    25,
      22,    68,    15,    50,    -1,    50,    23,    64,    -1,    50,
      -1,    -1,    68,    -1,    65,    30,    68,    -1,    68,    26,
      50,    27,    -1,    65,    26,    50,    27,    -1,    68,    24,
      67,    25,    -1,    50,    21,    67,    -1,    50,    -1,    -1,
       3,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    79,    79,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   111,   113,   115,   116,   117,   119,   122,   123,
     125,   126,   127,   129,   130,   132,   134,   135,   136,   138,
     139,   140,   142,   143,   145,   146,   148,   149,   151,   152,
     153,   155,   156,   157,   158,   160,   162,   163,   164,   166
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "STRING", "INT", "DOUBLE",
  "ASSIGN", "OR", "AND", "GE", "GT", "LE", "LT", "NEQ", "EQ", "MINUS",
  "PLUS", "DIVIDE", "TIMES", "UMINUS", "COMMA", "COLON", "SEMICOLON",
  "LPAREN", "RPAREN", "LBRACK", "RBRACK", "LBRACE", "RBRACE", "DOT",
  "ARRAY", "IF", "THEN", "ELSE", "WHILE", "FOR", "TO", "DO", "LET", "IN",
  "END", "OF", "BREAK", "NIL", "FUNCTION", "VAR", "TYPE", "$accept",
  "program", "exp", "seq", "record", "refields", "array", "decs", "dec",
  "tydecs", "tydec", "ty", "typefields", "vardec", "fundecs", "fundec",
  "explist", "lvalue", "funcall", "args", "id", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    48,    49,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    51,    52,    53,    53,    53,    54,    55,    55,
      56,    56,    56,    57,    57,    58,    59,    59,    59,    60,
      60,    60,    61,    61,    62,    62,    63,    63,    64,    64,
      64,    65,    65,    65,    65,    66,    67,    67,    67,    68
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     3,     1,     1,     1,     1,
       1,     5,     6,     4,     3,     3,     3,     3,     3,     2,
       3,     3,     3,     3,     3,     3,     3,     1,     1,     4,
       8,     1,     3,     4,     5,     3,     0,     6,     2,     0,
       1,     1,     1,     2,     1,     4,     1,     3,     3,     5,
       3,     0,     4,     6,     2,     1,     7,     9,     3,     1,
       0,     1,     3,     4,     4,     4,     3,     1,     0,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    69,    10,     8,     9,     0,    60,     0,     0,     0,
      39,    31,     6,     0,     2,     7,    27,    28,     3,     4,
      61,    19,    59,     0,     0,     0,     0,     0,     0,     0,
       0,    39,    40,    44,    41,    42,    55,     1,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    68,     0,    36,    60,    32,     0,     0,
       0,     0,     0,     0,    60,    38,    43,    54,    26,    25,
      23,    21,    24,    22,    20,    18,    15,    14,    17,    16,
       5,     0,    62,    67,     0,     0,     0,     0,    58,    13,
      29,     0,    51,     0,     0,     0,     0,    64,    68,    65,
      63,    33,     0,     0,     0,     0,     0,    52,     0,    51,
       0,    45,    46,    11,    66,     0,    35,    12,     0,     0,
       0,     0,     0,     0,    37,    36,     0,     0,     0,    50,
      53,    47,    48,    34,    30,    56,     0,    51,     0,    49,
      57
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    13,    22,    15,    16,    86,    17,    30,    31,    32,
      33,   111,   105,    34,    35,    36,    23,    18,    19,    84,
      20
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -104
static const yytype_int16 yypact[] =
{
      73,  -104,  -104,  -104,  -104,    73,    73,    73,    73,    18,
     -44,  -104,  -104,     4,   280,  -104,  -104,  -104,    66,  -104,
     104,  -104,   236,    11,   170,    14,    77,    18,    18,    18,
      45,   -44,  -104,    48,  -104,  -104,    54,  -104,    73,    73,
      73,    73,    73,    73,    73,    73,    73,    73,    73,    73,
      73,    73,    18,    73,    73,    18,    73,  -104,    73,    73,
      73,    76,    68,    86,    73,  -104,  -104,  -104,   290,   290,
     300,   300,   300,   300,   300,   300,    69,    69,  -104,  -104,
     280,   196,  -104,   252,    81,   216,    82,    98,  -104,     1,
     280,   158,    18,    73,    18,    79,    78,  -104,    73,  -104,
      72,  -104,    73,    73,    73,    93,   102,   280,   118,    18,
      87,  -104,  -104,  -104,  -104,    73,   266,   280,    53,    59,
      18,    73,   105,    18,   280,    18,    73,    73,    18,   110,
     280,  -104,  -104,  -104,   280,   280,   120,    18,    73,  -104,
     280
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -104,  -104,     0,  -104,  -104,     8,  -104,   108,  -104,   103,
    -104,  -104,  -103,  -104,   106,  -104,    30,  -104,  -104,    42,
      28
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_int16 yytable[] =
{
      14,    27,    28,    29,    37,    21,   122,    24,    25,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,     1,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,   139,   103,    57,    26,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    59,    83,    85,    61,    62,    63,    89,    90,
      91,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,   127,    93,     1,     2,     3,     4,
      82,   128,     1,    87,    60,    64,    88,    48,    49,     5,
      94,   126,    51,   107,    96,    29,    52,     6,    83,    27,
      92,    95,   116,   117,   118,     7,    99,   109,     8,     9,
     110,   101,    10,   102,   115,   124,    11,    12,   119,   113,
     106,   130,   108,   112,   120,   121,   134,   135,    53,   123,
      54,   137,    55,   133,   131,   138,    66,   106,   140,    65,
     114,     0,    67,     0,     0,     0,     0,     0,   129,     0,
       0,   132,     0,    87,     0,     0,   136,     0,     0,     0,
       0,     0,     0,     0,     0,   106,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
       0,     0,     0,     0,     0,   104,     0,     0,     0,     0,
       0,     0,     0,    58,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,     0,     0,     0,     0,
       0,     0,     0,    97,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,     0,     0,     0,     0,
       0,     0,     0,   100,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,     0,     0,     0,    56,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,     0,    98,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,     0,   125,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      -1,    -1,    -1,    -1,    -1,    -1,    46,    47,    48,    49
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-104))

#define yytable_value_is_error(yytable_value) \
  ((yytable_value) == (-1))

static const yytype_int16 yycheck[] =
{
       0,    45,    46,    47,     0,     5,   109,     7,     8,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,     3,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,   137,    34,    25,     9,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    38,    53,    54,    27,    28,    29,    58,    59,
      60,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,     7,    15,     7,     3,     4,     5,     6,
      52,    22,     3,    55,     7,    40,    56,    18,    19,    16,
      22,    38,    26,    93,    64,    47,    30,    24,    98,    45,
      24,    15,   102,   103,   104,    32,    25,    28,    35,    36,
      31,    29,    39,    15,    42,   115,    43,    44,    25,    41,
      92,   121,    94,    95,    22,     7,   126,   127,    24,    42,
      26,    21,    28,   125,    29,    15,    33,   109,   138,    31,
      98,    -1,    36,    -1,    -1,    -1,    -1,    -1,   120,    -1,
      -1,   123,    -1,   125,    -1,    -1,   128,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   137,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    -1,    -1,    -1,    -1,    37,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    33,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    27,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    27,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    -1,    -1,    23,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,    16,    24,    32,    35,    36,
      39,    43,    44,    49,    50,    51,    52,    54,    65,    66,
      68,    50,    50,    64,    50,    50,    68,    45,    46,    47,
      55,    56,    57,    58,    61,    62,    63,     0,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
       7,    26,    30,    24,    26,    28,    23,    25,    33,    38,
       7,    68,    68,    68,    40,    55,    57,    62,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    68,    50,    67,    50,    53,    68,    64,    50,
      50,    50,    24,     7,    22,    15,    64,    27,    21,    25,
      27,    29,    15,    34,    37,    60,    68,    50,    68,    28,
      31,    59,    68,    41,    67,    42,    50,    50,    50,    25,
      22,     7,    60,    42,    50,    21,    38,    15,    22,    68,
      50,    29,    68,    53,    50,    50,    68,    21,    15,    60,
      50
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
	    /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
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
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
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
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1806 of yacc.c  */
#line 79 "tiger.y"
    {absyn_root=(yyvsp[(1) - (1)].exp);}
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 81 "tiger.y"
    {(yyval.exp) = A_VarExp(EM_tokPos, (yyvsp[(1) - (1)].var));}
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 82 "tiger.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);}
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 83 "tiger.y"
    {(yyval.exp) = A_AssignExp(EM_tokPos, (yyvsp[(1) - (3)].var), (yyvsp[(3) - (3)].exp));}
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 84 "tiger.y"
    {(yyval.exp) = A_NilExp(EM_tokPos);}
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 85 "tiger.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);}
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 86 "tiger.y"
    {(yyval.exp) = A_IntExp(EM_tokPos, (yyvsp[(1) - (1)].ival));}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 87 "tiger.y"
    {(yyval.exp) = A_DoubleExp(EM_tokPos, (yyvsp[(1) - (1)].dval));}
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 88 "tiger.y"
    {(yyval.exp) = A_StringExp(EM_tokPos, (yyvsp[(1) - (1)].sval));}
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 89 "tiger.y"
    {(yyval.exp) = A_LetExp(EM_tokPos, (yyvsp[(2) - (5)].declist), A_SeqExp(EM_tokPos, (yyvsp[(4) - (5)].explist)));}
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 90 "tiger.y"
    {(yyval.exp) = A_IfExp(EM_tokPos, (yyvsp[(2) - (6)].exp), (yyvsp[(4) - (6)].exp), (yyvsp[(6) - (6)].exp));}
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 91 "tiger.y"
    {(yyval.exp) = A_IfExp(EM_tokPos, (yyvsp[(2) - (4)].exp), (yyvsp[(4) - (4)].exp), NULL);}
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 92 "tiger.y"
    {(yyval.exp) = A_OpExp(EM_tokPos, A_plusOp, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp));}
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 93 "tiger.y"
    {(yyval.exp) = A_OpExp(EM_tokPos, A_minusOp, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp));}
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 94 "tiger.y"
    {(yyval.exp) = A_OpExp(EM_tokPos, A_timesOp, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp));}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 95 "tiger.y"
    {(yyval.exp) = A_OpExp(EM_tokPos, A_divideOp, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp));}
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 96 "tiger.y"
    {(yyval.exp) = A_OpExp(EM_tokPos, A_eqOp, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp));}
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 97 "tiger.y"
    {(yyval.exp) = A_OpExp(EM_tokPos, A_minusOp, A_IntExp(EM_tokPos, 0), (yyvsp[(2) - (2)].exp));}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 98 "tiger.y"
    {(yyval.exp) = A_OpExp(EM_tokPos, A_neqOp, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp));}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 99 "tiger.y"
    {(yyval.exp) = A_OpExp(EM_tokPos, A_gtOp, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp));}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 100 "tiger.y"
    {(yyval.exp) = A_OpExp(EM_tokPos, A_ltOp, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp));}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 101 "tiger.y"
    {(yyval.exp) = A_OpExp(EM_tokPos, A_geOp, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp));}
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 102 "tiger.y"
    {(yyval.exp) = A_OpExp(EM_tokPos, A_leOp, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp));}
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 103 "tiger.y"
    {(yyval.exp) = A_IfExp(EM_tokPos, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp), A_IntExp(EM_tokPos, 0));}
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 104 "tiger.y"
    {(yyval.exp) = A_IfExp(EM_tokPos, (yyvsp[(1) - (3)].exp), A_IntExp(EM_tokPos,1), (yyvsp[(3) - (3)].exp));}
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 105 "tiger.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);}
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 106 "tiger.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);}
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 107 "tiger.y"
    {(yyval.exp) = A_WhileExp(EM_tokPos, (yyvsp[(2) - (4)].exp), (yyvsp[(4) - (4)].exp));}
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 108 "tiger.y"
    {(yyval.exp) = A_ForExp(EM_tokPos, (yyvsp[(2) - (8)].sym), (yyvsp[(4) - (8)].exp), (yyvsp[(6) - (8)].exp), (yyvsp[(8) - (8)].exp));}
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 109 "tiger.y"
    {(yyval.exp) = A_BreakExp(EM_tokPos);}
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 111 "tiger.y"
    {(yyval.exp) = A_SeqExp(EM_tokPos, (yyvsp[(2) - (3)].explist));}
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 113 "tiger.y"
    {(yyval.exp) = A_RecordExp(EM_tokPos, (yyvsp[(1) - (4)].sym), (yyvsp[(3) - (4)].efieldlist));}
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 115 "tiger.y"
    {(yyval.efieldlist) = A_EfieldList(A_Efield((yyvsp[(1) - (5)].sym), (yyvsp[(3) - (5)].exp)), (yyvsp[(5) - (5)].efieldlist));}
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 116 "tiger.y"
    {(yyval.efieldlist) = A_EfieldList(A_Efield((yyvsp[(1) - (3)].sym), (yyvsp[(3) - (3)].exp)), NULL);}
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 117 "tiger.y"
    {(yyval.efieldlist) = NULL;}
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 119 "tiger.y"
    {(yyval.exp) = A_ArrayExp(EM_tokPos, (yyvsp[(1) - (6)].sym), (yyvsp[(3) - (6)].exp), (yyvsp[(6) - (6)].exp));}
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 122 "tiger.y"
    {(yyval.declist) = A_DecList((yyvsp[(1) - (2)].dec), (yyvsp[(2) - (2)].declist));}
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 123 "tiger.y"
    {(yyval.declist) = NULL;}
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 125 "tiger.y"
    {(yyval.dec) = (yyvsp[(1) - (1)].dec);}
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 126 "tiger.y"
    {(yyval.dec) = (yyvsp[(1) - (1)].dec);}
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 127 "tiger.y"
    {(yyval.dec) = (yyvsp[(1) - (1)].dec);}
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 129 "tiger.y"
    {(yyval.dec) = A_TypeDec(EM_tokPos, A_NametyList((yyvsp[(1) - (2)].namety), (yyvsp[(2) - (2)].dec)->u.type));}
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 130 "tiger.y"
    {(yyval.dec) = A_TypeDec(EM_tokPos, A_NametyList((yyvsp[(1) - (1)].namety), NULL));}
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 132 "tiger.y"
    {(yyval.namety) = A_Namety((yyvsp[(2) - (4)].sym), (yyvsp[(4) - (4)].ty));}
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 134 "tiger.y"
    {(yyval.ty) = A_NameTy(EM_tokPos, (yyvsp[(1) - (1)].sym));}
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 135 "tiger.y"
    {(yyval.ty) = A_RecordTy(EM_tokPos, (yyvsp[(2) - (3)].fieldlist));}
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 136 "tiger.y"
    {(yyval.ty) = A_ArrayTy(EM_tokPos, (yyvsp[(3) - (3)].sym));}
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 138 "tiger.y"
    {(yyval.fieldlist) = A_FieldList(A_Field(EM_tokPos, (yyvsp[(1) - (5)].sym), (yyvsp[(3) - (5)].sym)), (yyvsp[(5) - (5)].fieldlist));}
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 139 "tiger.y"
    {(yyval.fieldlist) = A_FieldList(A_Field(EM_tokPos, (yyvsp[(1) - (3)].sym), (yyvsp[(3) - (3)].sym)), NULL);}
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 140 "tiger.y"
    {(yyval.fieldlist) = NULL;}
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 142 "tiger.y"
    {/*printf("\n$%s$\n", $2);*/ (yyval.dec) = A_VarDec(EM_tokPos, (yyvsp[(2) - (4)].sym), NULL, (yyvsp[(4) - (4)].exp));}
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 143 "tiger.y"
    {(yyval.dec) = A_VarDec(EM_tokPos, (yyvsp[(2) - (6)].sym), (yyvsp[(4) - (6)].sym), (yyvsp[(6) - (6)].exp));}
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 145 "tiger.y"
    {(yyval.dec) = A_FunctionDec(EM_tokPos, A_FundecList((yyvsp[(1) - (2)].fundec), (yyvsp[(2) - (2)].dec)->u.function));}
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 146 "tiger.y"
    {(yyval.dec) = A_FunctionDec(EM_tokPos, A_FundecList((yyvsp[(1) - (1)].fundec), NULL));}
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 148 "tiger.y"
    {(yyval.fundec) = A_Fundec(EM_tokPos, (yyvsp[(2) - (7)].sym), (yyvsp[(4) - (7)].fieldlist), NULL, (yyvsp[(7) - (7)].exp));}
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 149 "tiger.y"
    {(yyval.fundec) = A_Fundec(EM_tokPos, (yyvsp[(2) - (9)].sym), (yyvsp[(4) - (9)].fieldlist), (yyvsp[(7) - (9)].sym), (yyvsp[(9) - (9)].exp));}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 151 "tiger.y"
    {(yyval.explist) = A_ExpList((yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].explist));}
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 152 "tiger.y"
    {(yyval.explist) = A_ExpList((yyvsp[(1) - (1)].exp), NULL);}
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 153 "tiger.y"
    {(yyval.explist) = NULL;}
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 155 "tiger.y"
    {/*printf("\nf$%s$f\n", S_name($1));*/ (yyval.var) = A_SimpleVar(EM_tokPos, (yyvsp[(1) - (1)].sym));}
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 156 "tiger.y"
    {(yyval.var) = A_FieldVar(EM_tokPos, (yyvsp[(1) - (3)].var), (yyvsp[(3) - (3)].sym));}
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 157 "tiger.y"
    {(yyval.var) = A_SubscriptVar(EM_tokPos, A_SimpleVar(EM_tokPos, (yyvsp[(1) - (4)].sym)), (yyvsp[(3) - (4)].exp));}
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 158 "tiger.y"
    {(yyval.var) = A_SubscriptVar(EM_tokPos, (yyvsp[(1) - (4)].var), (yyvsp[(3) - (4)].exp));}
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 160 "tiger.y"
    {(yyval.exp) = A_CallExp(EM_tokPos, (yyvsp[(1) - (4)].sym), (yyvsp[(3) - (4)].explist));}
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 162 "tiger.y"
    {(yyval.explist) = A_ExpList((yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].explist));}
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 163 "tiger.y"
    {(yyval.explist) = A_ExpList((yyvsp[(1) - (1)].exp), NULL);}
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 164 "tiger.y"
    {(yyval.explist) = NULL;}
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 166 "tiger.y"
    {/*printf("\n$%s$\n",$1);*/(yyval.sym) = S_Symbol((yyvsp[(1) - (1)].sval)); /*printf("\nt$%s$t\n", S_name($$));*/}
    break;



/* Line 1806 of yacc.c  */
#line 2112 "y.tab.c"
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



