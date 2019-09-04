/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "Sintactico.y" /* yacc.c:339  */

    #include "scanner.h"
    #include "nodo.h"
    #include <iostream>

    extern int yylineno; //linea actual donde se encuentra el parser (analisis lexico) lo maneja BISON
    extern int columna; //columna actual donde se encuentra el parser (analisis lexico) lo maneja BISON
    extern char *yytext; //lexema actual donde esta el parser (analisis lexico) lo maneja BISON
    extern Nodo *raiz; // Raiz del arbol

    int yyerror(const char* mens){
        std::cout<<mens<<std::endl;
        return 0;
    }


#line 83 "parser.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.h".  */
#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    mkdisk = 258,
    rmdisk = 259,
    fdisk = 260,
    mount = 261,
    unmount = 262,
    rep = 263,
    exec = 264,
    size = 265,
    unit = 266,
    path = 267,
    fit = 268,
    name = 269,
    type = 270,
    del = 271,
    add = 272,
    id = 273,
    bf = 274,
    ff = 275,
    wf = 276,
    fast = 277,
    full = 278,
    mbr = 279,
    disk = 280,
    igual = 281,
    extension = 282,
    num = 283,
    caracter = 284,
    cadena = 285,
    identificador = 286,
    ruta = 287,
    mkfs = 288,
    login = 289,
    logout = 290,
    mkgrp = 291,
    rmgrp = 292,
    mkusr = 293,
    rmusr = 294,
    Rchmod = 295,
    mkfile = 296,
    cat = 297,
    rem = 298,
    edit = 299,
    ren = 300,
    Rmkdir = 301,
    cp = 302,
    mv = 303,
    find = 304,
    Rchown = 305,
    chgrp = 306,
    pausa = 307,
    recovery = 308,
    loss = 309,
    fs = 310,
    fs2 = 311,
    fs3 = 312,
    usr = 313,
    pwd = 314,
    grp = 315,
    ugo = 316,
    r = 317,
    p = 318,
    cont = 319,
    file = 320,
    dest = 321,
    rutaRep = 322,
    inode = 323,
    journaling = 324,
    block = 325,
    bm_inode = 326,
    bm_block = 327,
    tree = 328,
    sb = 329,
    fileRep = 330,
    ls = 331,
    password = 332
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 21 "Sintactico.y" /* yacc.c:355  */

        char text[400];
        class Nodo *nodito;
    

#line 207 "parser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 224 "parser.cpp" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  133
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   310

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  78
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  47
/* YYNRULES -- Number of rules.  */
#define YYNRULES  170
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  305

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   332

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   156,   156,   158,   162,   163,   167,   171,   172,   175,
     176,   180,   184,   185,   186,   187,   191,   192,   196,   200,
     201,   202,   206,   210,   214,   218,   222,   226,   230,   234,
     235,   236,   241,   245,   250,   251,   255,   256,   259,   264,
     269,   274,   278,   283,   284,   285,   286,   287,   288,   289,
     291,   295,   300,   301,   302,   303,   305,   311,   312,   313,
     316,   320,   325,   326,   327,   328,   329,   330,   331,   332,
     333,   334,   335,   336,   337,   338,   339,   340,   342,   347,
     353,   357,   362,   363,   364,   365,   366,   368,   372,   377,
     378,   379,   380,   381,   383,   388,   394,   399,   404,   408,
     413,   414,   415,   416,   417,   419,   424,   430,   434,   439,
     440,   441,   442,   444,   448,   454,   455,   456,   457,   458,
     459,   461,   466,   472,   477,   483,   487,   492,   493,   494,
     496,   500,   505,   506,   507,   512,   514,   518,   523,   524,
     525,   526,   528,   532,   537,   538,   539,   540,   542,   546,
     551,   555,   560,   561,   562,   567,   569,   573,   578,   579,
     580,   581,   582,   584,   588,   593,   594,   595,   596,   598,
     604
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "mkdisk", "rmdisk", "fdisk", "mount",
  "unmount", "rep", "exec", "size", "unit", "path", "fit", "name", "type",
  "del", "add", "id", "bf", "ff", "wf", "fast", "full", "mbr", "disk",
  "igual", "extension", "num", "caracter", "cadena", "identificador",
  "ruta", "mkfs", "login", "logout", "mkgrp", "rmgrp", "mkusr", "rmusr",
  "Rchmod", "mkfile", "cat", "rem", "edit", "ren", "Rmkdir", "cp", "mv",
  "find", "Rchown", "chgrp", "pausa", "recovery", "loss", "fs", "fs2",
  "fs3", "usr", "pwd", "grp", "ugo", "r", "p", "cont", "file", "dest",
  "rutaRep", "inode", "journaling", "block", "bm_inode", "bm_block",
  "tree", "sb", "fileRep", "ls", "password", "$accept", "INIT", "COMANDO",
  "MKDISK", "PARAMETRO_MK", "RMDISK", "FDISK", "PARAMETRO_FK", "MOUNT",
  "PARAMETRO_M", "UNMOUNT", "AJUSTE", "REP", "PARAMETRO_R", "SCRIPT",
  "MKFS", "PARAM_MKFS", "LOGIN", "PARAM_LOGIN", "MKGRP", "RMGRP", "MKUSR",
  "PARAM_MKUSR", "RMUSR", "CHMOD", "PARAM_CHMOD", "MKFILE", "PARAM_MKFILE",
  "CAT", "REM", "EDIT", "PARAM_EDIT", "REN", "PARAM_REN", "MKDIR",
  "PARAM_MKDIR", "CP", "PARAM_CP", "MV", "FIND", "PARAM_FIND", "CHOWN",
  "PARAM_CHOWN", "CHGRP", "PARAM_CHGRP", "RECOVERY", "LOSS", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332
};
# endif

#define YYPACT_NINF -41

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-41)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      36,    20,    41,    12,    -2,    87,   -11,   107,    -4,    75,
     -41,   130,   138,   -40,   115,    37,    -6,   111,   162,   -10,
       1,    34,    -7,    -7,    89,    38,    44,   -41,   157,   159,
     178,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,
     -41,   -41,   153,   154,   155,   156,    20,   -41,   158,   160,
     161,   163,   164,   -41,    12,   -41,   165,   166,    -2,   -41,
     167,   168,   169,   170,   171,   -11,   -41,   172,   173,   174,
     175,    -4,   -41,   176,   177,   179,    75,   -41,   180,   181,
     182,   183,   184,   -40,   -41,   185,   186,   187,   -41,    37,
     -41,   188,   189,   -41,   190,    -6,   -41,   191,   192,   193,
     194,   -10,   -41,   195,   196,     1,   -41,   197,   198,   -41,
      34,   -41,   199,   200,    -7,   -41,   -41,    -7,   201,   202,
      89,   -41,   203,   204,   -41,    38,   -41,   205,   206,    44,
     -41,   207,   208,   -41,   209,   210,    76,    15,   -41,    77,
       7,   211,   124,   213,   -41,    80,   118,   -41,   152,    81,
      -8,   212,    84,   -41,    85,   128,   214,    97,   -41,   215,
     125,   -22,   -41,   127,   129,   131,    18,   216,   -41,   133,
      88,   220,   -41,   221,    91,    92,   -41,    95,    96,    99,
     222,   -41,   100,   135,   -41,   105,   219,   -41,   106,   109,
     -41,   -41,   110,    -9,   -41,   113,   137,   -41,   139,   141,
     -41,   223,   224,   -41,   -41,   -41,   -41,   -41,   -41,   -41,
     -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,
     -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,
     -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,
     -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,
     -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,
     -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,
     -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,
     -41,   217,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,
     -41,   226,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,
     -41,   -41,   -41,   -41,   -41
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      12,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    29,     0,     0,
       0,     2,     4,     7,     9,    13,    14,    16,    19,    20,
      30,    31,     0,     0,     0,     0,     3,    33,     0,     0,
       0,     0,     0,    43,     5,    42,     0,     0,     6,    51,
       0,     0,     0,     0,     0,     8,    61,     0,     0,     0,
       0,    10,    81,     0,     0,     0,    11,    88,     0,     0,
       0,     0,     0,    15,    99,     0,     0,     0,   112,    17,
     108,     0,     0,   120,     0,    18,   114,     0,     0,     0,
       0,    21,   126,     0,     0,    22,   131,     0,     0,   141,
      23,   137,     0,     0,    24,   143,   149,    25,     0,     0,
      26,   151,     0,     0,   162,    27,   157,     0,     0,    28,
     164,     0,     0,     1,     0,     0,     0,     0,    32,     0,
       0,     0,     0,     0,    41,     0,     0,    50,     0,     0,
       0,     0,     0,    60,     0,     0,     0,     0,    80,     0,
       0,     0,    87,     0,     0,     0,     0,     0,    98,     0,
       0,     0,   107,     0,     0,     0,   113,     0,     0,     0,
       0,   125,     0,     0,   130,     0,     0,   136,     0,     0,
     142,   148,     0,     0,   150,     0,     0,   156,     0,     0,
     163,     0,     0,    34,    36,    37,    38,    57,    58,    59,
      35,    40,    39,    48,    47,    44,    45,    46,    49,    52,
      53,    55,    54,    56,    73,    74,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    75,    77,    76,
      78,    79,    83,    84,    82,    85,    86,    93,    90,    89,
      92,    91,    95,    94,    97,    96,   101,   100,   103,   102,
     104,   106,   105,   109,   110,   111,   117,   116,   115,   119,
     118,   122,   121,   124,   123,   128,   127,   129,   133,   132,
     135,     0,   139,   138,   140,   145,   144,   147,   146,   153,
     152,     0,   155,   159,   158,   161,   160,   166,   165,   168,
     167,   169,   170,   134,   154
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -41,   -41,   -41,   -41,    46,   -41,   -41,   134,   -41,   146,
     -41,   -41,   -41,   120,   -41,   -41,   218,   -41,   225,   -41,
     -41,   -41,   227,   -41,   -41,   147,   -41,   140,   -41,   -41,
     -41,   150,   -41,   151,   -41,   132,   -41,   -23,   -41,   -41,
     142,   -41,   136,   -41,   143,   -41,   -41
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    30,    31,    46,    53,    32,    54,    55,    58,    59,
      33,   210,    65,    66,    34,    71,    72,    76,    77,    35,
      36,    83,    84,    37,    89,    90,    95,    96,    38,    39,
     101,   102,   105,   106,   110,   111,   114,   115,   117,   120,
     121,   125,   126,   129,   130,    40,    41
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
     116,    61,    99,    62,    91,   112,    92,    63,   250,   291,
      56,    68,    57,   103,    69,   104,   226,   227,    80,    81,
      82,   292,    42,    43,    44,    45,    49,    50,    51,    52,
      42,    43,    44,    45,   207,   208,   209,   213,   214,     1,
       2,     3,     4,     5,     6,     7,   107,    47,   258,    86,
     122,    70,   108,    48,   100,   251,    64,    93,    94,   113,
     228,   229,   230,   231,   232,   233,   234,   235,   236,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,   190,   138,    73,   191,   259,   123,   109,    87,    88,
     124,   118,   127,   119,   128,    60,   205,   211,   206,   212,
     219,   224,   220,   225,   238,   240,   239,   241,   263,    67,
     264,   267,   269,   268,   270,   271,   273,   272,   274,   275,
     278,   276,   279,    74,    75,   282,   285,   283,   286,   287,
     289,   288,   290,   293,    78,   294,   216,   217,   221,   222,
     242,   243,    79,   245,   246,   248,   249,   252,   253,   254,
     255,   256,   257,   261,   262,   280,   281,   295,   296,   297,
     298,   299,   300,    85,    98,   131,    97,   132,   133,   134,
     135,   136,   137,   223,   139,   153,   140,   141,   144,   142,
     143,   145,   146,   148,   149,   150,   151,   152,   154,   155,
     156,   157,   159,   160,   147,   161,   163,   164,   165,   166,
     167,   169,   170,   171,   173,   174,   175,   177,   178,   179,
     180,   182,   183,   185,   186,   188,   189,   192,   193,   195,
     196,   198,   199,   201,   202,   176,   172,   203,     0,   204,
     215,   218,   187,   237,   303,   244,   247,   260,   265,   266,
     284,   181,   277,   304,   301,   302,   184,     0,     0,     0,
       0,   197,   194,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   200,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   158,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   162,     0,     0,     0,     0,     0,     0,     0,     0,
     168
};

static const yytype_int16 yycheck[] =
{
      23,    12,    12,    14,    10,    12,    12,    18,    30,    18,
      12,    15,    14,    12,    18,    14,    24,    25,    58,    59,
      60,    30,    10,    11,    12,    13,    14,    15,    16,    17,
      10,    11,    12,    13,    19,    20,    21,    30,    31,     3,
       4,     5,     6,     7,     8,     9,    12,     1,    30,    12,
      12,    55,    18,    12,    64,    77,    67,    63,    64,    66,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,   114,    46,    18,   117,    77,    58,    63,    61,    62,
      62,    12,    58,    14,    60,    18,    30,    30,    32,    32,
      30,    30,    32,    32,    30,    30,    32,    32,    30,    12,
      32,    30,    30,    32,    32,    30,    30,    32,    32,    30,
      30,    32,    32,    58,    59,    30,    30,    32,    32,    30,
      30,    32,    32,    30,    14,    32,    22,    23,    30,    31,
      22,    23,    14,    56,    57,    30,    31,    30,    31,    30,
      31,    30,    31,    30,    31,    30,    31,    30,    31,    30,
      31,    30,    31,    58,    12,    18,    65,    18,     0,    26,
      26,    26,    26,    31,    26,    65,    26,    26,    54,    26,
      26,    26,    26,    26,    26,    26,    26,    26,    26,    26,
      26,    26,    26,    26,    58,    26,    26,    26,    26,    26,
      26,    26,    26,    26,    26,    26,    26,    26,    26,    26,
      26,    26,    26,    26,    26,    26,    26,    26,    26,    26,
      26,    26,    26,    26,    26,    95,    89,    28,    -1,    29,
      29,    28,   110,    31,    27,    31,    31,    31,    28,    28,
      31,   101,    30,    27,    31,    31,   105,    -1,    -1,    -1,
      -1,   125,   120,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   129,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      83
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      79,    80,    83,    88,    92,    97,    98,   101,   106,   107,
     123,   124,    10,    11,    12,    13,    81,    82,    12,    14,
      15,    16,    17,    82,    84,    85,    12,    14,    86,    87,
      18,    12,    14,    18,    67,    90,    91,    12,    15,    18,
      55,    93,    94,    18,    58,    59,    95,    96,    14,    14,
      58,    59,    60,    99,   100,    58,    12,    61,    62,   102,
     103,    10,    12,    63,    64,   104,   105,    65,    12,    12,
      64,   108,   109,    12,    14,   110,   111,    12,    18,    63,
     112,   113,    12,    66,   114,   115,   115,   116,    12,    14,
     117,   118,    12,    58,    62,   119,   120,    58,    60,   121,
     122,    18,    18,     0,    26,    26,    26,    26,    82,    26,
      26,    26,    26,    26,    85,    26,    26,    87,    26,    26,
      26,    26,    26,    91,    26,    26,    26,    26,    94,    26,
      26,    26,    96,    26,    26,    26,    26,    26,   100,    26,
      26,    26,   103,    26,    26,    26,   105,    26,    26,    26,
      26,   109,    26,    26,   111,    26,    26,   113,    26,    26,
     115,   115,    26,    26,   118,    26,    26,   120,    26,    26,
     122,    26,    26,    28,    29,    30,    32,    19,    20,    21,
      89,    30,    32,    30,    31,    29,    22,    23,    28,    30,
      32,    30,    31,    31,    30,    32,    24,    25,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    31,    30,    32,
      30,    32,    22,    23,    31,    56,    57,    31,    30,    31,
      30,    77,    30,    31,    30,    31,    30,    31,    30,    77,
      31,    30,    31,    30,    32,    28,    28,    30,    32,    30,
      32,    30,    32,    30,    32,    30,    32,    30,    30,    32,
      30,    31,    30,    32,    31,    30,    32,    30,    32,    30,
      32,    18,    30,    30,    32,    30,    31,    30,    31,    30,
      31,    31,    31,    27,    27
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    78,    79,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    81,    81,    82,    82,    82,    82,    82,    83,
      83,    84,    84,    85,    85,    85,    85,    85,    85,    85,
      86,    86,    87,    87,    87,    87,    88,    89,    89,    89,
      90,    90,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    92,    92,
      93,    93,    94,    94,    94,    94,    94,    95,    95,    96,
      96,    96,    96,    96,    97,    97,    98,    98,    99,    99,
     100,   100,   100,   100,   100,   101,   101,   102,   102,   103,
     103,   103,   103,   104,   104,   105,   105,   105,   105,   105,
     105,   106,   106,   107,   107,   108,   108,   109,   109,   109,
     110,   110,   111,   111,   111,   111,   112,   112,   113,   113,
     113,   113,   114,   114,   115,   115,   115,   115,   116,   116,
     117,   117,   118,   118,   118,   118,   119,   119,   120,   120,
     120,   120,   120,   121,   121,   122,   122,   122,   122,   123,
     124
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     2,     2,     1,     2,     1,
       2,     2,     1,     1,     1,     2,     1,     2,     2,     1,
       1,     2,     2,     2,     2,     2,     2,     2,     2,     1,
       1,     1,     2,     1,     3,     3,     3,     3,     3,     4,
       4,     2,     1,     1,     3,     3,     3,     3,     3,     3,
       2,     1,     3,     3,     3,     3,     4,     1,     1,     1,
       2,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     4,     4,
       2,     1,     3,     3,     3,     3,     3,     2,     1,     3,
       3,     3,     3,     3,     4,     4,     4,     4,     2,     1,
       3,     3,     3,     3,     3,     4,     4,     2,     1,     3,
       3,     3,     1,     2,     1,     3,     3,     3,     3,     3,
       1,     4,     4,     4,     4,     2,     1,     3,     3,     3,
       2,     1,     3,     3,     4,     3,     2,     1,     3,     3,
       3,     1,     2,     1,     3,     3,     3,     3,     2,     1,
       2,     1,     3,     3,     4,     3,     2,     1,     3,     3,
       3,     3,     1,     2,     1,     3,     3,     3,     3,     4,
       4
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
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
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
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

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

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

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
      yychar = yylex ();
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
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
        case 2:
#line 156 "Sintactico.y" /* yacc.c:1646  */
    { raiz = (yyval.nodito); }
#line 1530 "parser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 158 "Sintactico.y" /* yacc.c:1646  */
    {
                         (yyval.nodito) = new Nodo("MKDISK","");
                         (yyval.nodito)->add(*(yyvsp[0].nodito));
                       }
#line 1539 "parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 162 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = (yyvsp[0].nodito); }
#line 1545 "parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 163 "Sintactico.y" /* yacc.c:1646  */
    {
                          (yyval.nodito) = new Nodo("FDISK","");
                          (yyval.nodito)->add(*(yyvsp[0].nodito));
                        }
#line 1554 "parser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 167 "Sintactico.y" /* yacc.c:1646  */
    {
                         (yyval.nodito) = new Nodo("MOUNT", "");
                         (yyval.nodito)->add(*(yyvsp[0].nodito));
                       }
#line 1563 "parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 171 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = (yyvsp[0].nodito); }
#line 1569 "parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 172 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("REP","");
                     (yyval.nodito)->add(*(yyvsp[0].nodito));
                   }
#line 1577 "parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 175 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = (yyvsp[0].nodito); }
#line 1583 "parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 176 "Sintactico.y" /* yacc.c:1646  */
    {
                        (yyval.nodito) = new Nodo("MKFS","");
                        (yyval.nodito)->add(*(yyvsp[0].nodito));
                     }
#line 1592 "parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 180 "Sintactico.y" /* yacc.c:1646  */
    {
                         (yyval.nodito) = new Nodo("LOGIN", "");
                         (yyval.nodito)->add(*(yyvsp[0].nodito));
                       }
#line 1601 "parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 184 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("LOGOUT",""); }
#line 1607 "parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 185 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = (yyvsp[0].nodito); }
#line 1613 "parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 186 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = (yyvsp[0].nodito); }
#line 1619 "parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 187 "Sintactico.y" /* yacc.c:1646  */
    {
                        (yyval.nodito) = new Nodo("MKUSR","");
                        (yyval.nodito)->add(*(yyvsp[0].nodito));
                       }
#line 1628 "parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 191 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = (yyvsp[0].nodito); }
#line 1634 "parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 192 "Sintactico.y" /* yacc.c:1646  */
    {
                         (yyval.nodito) = new Nodo("CHMOD","");
                         (yyval.nodito)->add(*(yyvsp[0].nodito));
                       }
#line 1643 "parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 196 "Sintactico.y" /* yacc.c:1646  */
    {
                            (yyval.nodito) = new Nodo("MKFILE","");
                            (yyval.nodito)->add(*(yyvsp[0].nodito));
                         }
#line 1652 "parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 200 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = (yyvsp[0].nodito); }
#line 1658 "parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 201 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = (yyvsp[0].nodito); }
#line 1664 "parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 202 "Sintactico.y" /* yacc.c:1646  */
    {
                       (yyval.nodito) = new Nodo("EDIT","");
                       (yyval.nodito)->add(*(yyvsp[0].nodito));
                     }
#line 1673 "parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 206 "Sintactico.y" /* yacc.c:1646  */
    {
                    (yyval.nodito) = new Nodo("REN","");
                    (yyval.nodito)->add(*(yyvsp[0].nodito));
                  }
#line 1682 "parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 210 "Sintactico.y" /* yacc.c:1646  */
    {
                        (yyval.nodito) = new Nodo("MKDIR","");
                        (yyval.nodito)->add(*(yyvsp[0].nodito));
                      }
#line 1691 "parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 214 "Sintactico.y" /* yacc.c:1646  */
    {
                  (yyval.nodito) = new Nodo("CP","");
                  (yyval.nodito)->add(*(yyvsp[0].nodito));
                }
#line 1700 "parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 218 "Sintactico.y" /* yacc.c:1646  */
    {
                  (yyval.nodito) = new Nodo("MV","");
                  (yyval.nodito)->add(*(yyvsp[0].nodito));
                }
#line 1709 "parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 222 "Sintactico.y" /* yacc.c:1646  */
    {
                      (yyval.nodito) = new Nodo("FIND","");
                      (yyval.nodito)->add(*(yyvsp[0].nodito));
                    }
#line 1718 "parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 226 "Sintactico.y" /* yacc.c:1646  */
    {
                        (yyval.nodito) = new Nodo("CHOWN","");
                        (yyval.nodito)->add(*(yyvsp[0].nodito));
                      }
#line 1727 "parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 230 "Sintactico.y" /* yacc.c:1646  */
    {
                        (yyval.nodito) = new Nodo("CHGRP","");
                        (yyval.nodito)->add(*(yyvsp[0].nodito));
                      }
#line 1736 "parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 234 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("PAUSE",""); }
#line 1742 "parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 235 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = (yyvsp[0].nodito); }
#line 1748 "parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 236 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = (yyvsp[0].nodito); }
#line 1754 "parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 241 "Sintactico.y" /* yacc.c:1646  */
    {
                             (yyval.nodito) = (yyvsp[-1].nodito);
                             (yyval.nodito)->add(*(yyvsp[0].nodito));
                            }
#line 1763 "parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 245 "Sintactico.y" /* yacc.c:1646  */
    {
                       (yyval.nodito) = new Nodo("PARAMETRO","");
                       (yyval.nodito)->add(*(yyvsp[0].nodito));
                     }
#line 1772 "parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 250 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito)= new Nodo("size",(yyvsp[0].text)); }
#line 1778 "parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 251 "Sintactico.y" /* yacc.c:1646  */
    {
                                (yyval.nodito) = new Nodo ("fit", "");
                                (yyval.nodito)->add(*(yyvsp[0].nodito));
                               }
#line 1787 "parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 255 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("unit",(yyvsp[0].text)); }
#line 1793 "parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 256 "Sintactico.y" /* yacc.c:1646  */
    {
                                 (yyval.nodito) = new Nodo("path",(yyvsp[0].text));
                                }
#line 1801 "parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 259 "Sintactico.y" /* yacc.c:1646  */
    {
                               (yyval.nodito) = new Nodo("path", (yyvsp[0].text));

                             }
#line 1810 "parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 264 "Sintactico.y" /* yacc.c:1646  */
    {
                                (yyval.nodito) = new Nodo("RMDISK","");
                                Nodo *n = new Nodo("path",(yyvsp[0].text));
                                (yyval.nodito)->add(*n);
                               }
#line 1820 "parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 269 "Sintactico.y" /* yacc.c:1646  */
    {
                                      (yyval.nodito) = new Nodo("RMDISK","");
                                      Nodo *ruta = new Nodo("path",(yyvsp[0].text));
                                      (yyval.nodito)->add(*ruta);
                                    }
#line 1830 "parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 274 "Sintactico.y" /* yacc.c:1646  */
    {
                            (yyval.nodito) = (yyvsp[-1].nodito);
                            (yyval.nodito)->add(*(yyvsp[0].nodito));
                          }
#line 1839 "parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 278 "Sintactico.y" /* yacc.c:1646  */
    {
                        (yyval.nodito) = new Nodo("PARAMETRO","");
                        (yyval.nodito)->add(*(yyvsp[0].nodito));
                      }
#line 1848 "parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 283 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = (yyvsp[0].nodito); }
#line 1854 "parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 284 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("type",(yyvsp[0].text)); }
#line 1860 "parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 285 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("delete", "fast"); }
#line 1866 "parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 286 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("delete", "full"); }
#line 1872 "parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 287 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("name", (yyvsp[0].text)); }
#line 1878 "parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 288 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("name", (yyvsp[0].text)); }
#line 1884 "parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 289 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("add", (yyvsp[0].text)); }
#line 1890 "parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 291 "Sintactico.y" /* yacc.c:1646  */
    {
                           (yyval.nodito) = (yyvsp[-1].nodito);
                           (yyval.nodito)->add(*(yyvsp[0].nodito));
                         }
#line 1899 "parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 295 "Sintactico.y" /* yacc.c:1646  */
    {
                        (yyval.nodito) = new Nodo("PARAMETRO","");
                        (yyval.nodito)->add(*(yyvsp[0].nodito));
                      }
#line 1908 "parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 300 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("path",(yyvsp[0].text)); }
#line 1914 "parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 301 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("path", (yyvsp[0].text)); }
#line 1920 "parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 302 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("name", (yyvsp[0].text)); }
#line 1926 "parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 303 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("name",(yyvsp[0].text)); }
#line 1932 "parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 305 "Sintactico.y" /* yacc.c:1646  */
    {
                                          (yyval.nodito) = new Nodo("UNMOUNT", "");
                                          Nodo *n = new Nodo("id",(yyvsp[0].text));
                                          (yyval.nodito)->add(*n);
                                        }
#line 1942 "parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 311 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("ajuste", "bf"); }
#line 1948 "parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 312 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("ajuste", "ff"); }
#line 1954 "parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 313 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("ajuste", "wf"); }
#line 1960 "parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 316 "Sintactico.y" /* yacc.c:1646  */
    {
                     (yyval.nodito) = (yyvsp[-1].nodito);
                     (yyval.nodito)->add(*(yyvsp[0].nodito));
                    }
#line 1969 "parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 320 "Sintactico.y" /* yacc.c:1646  */
    {
                    (yyval.nodito) = new Nodo("PARAMETRO", "");
                    (yyval.nodito)->add(*(yyvsp[0].nodito));
                  }
#line 1978 "parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 325 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("name","mbr"); }
#line 1984 "parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 326 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("name","disk"); }
#line 1990 "parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 327 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("name", "inode"); }
#line 1996 "parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 328 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("name", "journaling"); }
#line 2002 "parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 329 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("name", "block"); }
#line 2008 "parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 330 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("name", "bm_inode"); }
#line 2014 "parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 331 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("name", "bm_block"); }
#line 2020 "parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 332 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("name", "tree"); }
#line 2026 "parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 333 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("name", "sb"); }
#line 2032 "parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 334 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("name", "file"); }
#line 2038 "parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 335 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("name", "ls"); }
#line 2044 "parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 336 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("path", (yyvsp[0].text)); }
#line 2050 "parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 337 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("path",(yyvsp[0].text)); }
#line 2056 "parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 338 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("id", (yyvsp[0].text)); }
#line 2062 "parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 339 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("ruta", (yyvsp[0].text)); }
#line 2068 "parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 340 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("ruta", (yyvsp[0].text)); }
#line 2074 "parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 342 "Sintactico.y" /* yacc.c:1646  */
    {
                                (yyval.nodito) = new Nodo("EXEC","");
                                Nodo *path = new Nodo("path", (yyvsp[0].text));
                                (yyval.nodito)->add(*path);
                               }
#line 2084 "parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 347 "Sintactico.y" /* yacc.c:1646  */
    {
                                 (yyval.nodito) = new Nodo("EXEC","");
                                 Nodo *n = new Nodo("path", (yyvsp[0].text));
                                 (yyval.nodito)->add(*n);
                               }
#line 2094 "parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 353 "Sintactico.y" /* yacc.c:1646  */
    {
                        (yyval.nodito) = (yyvsp[-1].nodito);
                        (yyval.nodito)->add(*(yyvsp[0].nodito));
                      }
#line 2103 "parser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 357 "Sintactico.y" /* yacc.c:1646  */
    {
                      (yyval.nodito) = new Nodo("PARAMETRO", "");
                      (yyval.nodito)->add(*(yyvsp[0].nodito));
                   }
#line 2112 "parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 362 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("id",(yyvsp[0].text)); }
#line 2118 "parser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 363 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("type", "fast"); }
#line 2124 "parser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 364 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("type", "full"); }
#line 2130 "parser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 365 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("fs", "2fs"); }
#line 2136 "parser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 366 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("fs", "3fs"); }
#line 2142 "parser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 368 "Sintactico.y" /* yacc.c:1646  */
    {
                           (yyval.nodito) = (yyvsp[-1].nodito);
                           (yyval.nodito)->add(*(yyvsp[0].nodito));
                         }
#line 2151 "parser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 372 "Sintactico.y" /* yacc.c:1646  */
    {
                        (yyval.nodito) = new Nodo("PARAMETRO","");
                        (yyval.nodito)->add(*(yyvsp[0].nodito));
                     }
#line 2160 "parser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 377 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("user", (yyvsp[0].text)); }
#line 2166 "parser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 378 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("user", (yyvsp[0].text)); }
#line 2172 "parser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 379 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("password", (yyvsp[0].text)); }
#line 2178 "parser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 380 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("password", (yyvsp[0].text)); }
#line 2184 "parser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 381 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("id", (yyvsp[0].text)); }
#line 2190 "parser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 383 "Sintactico.y" /* yacc.c:1646  */
    {
                                        (yyval.nodito) = new Nodo("MKGRP","");
                                        Nodo *n = new Nodo("name",(yyvsp[0].text));
                                        (yyval.nodito)->add(*n);
                                      }
#line 2200 "parser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 388 "Sintactico.y" /* yacc.c:1646  */
    {
                                    (yyval.nodito) = new Nodo("MKGRP","");
                                    Nodo *n = new Nodo("name",(yyvsp[0].text));
                                    (yyval.nodito)->add(*n);
                                 }
#line 2210 "parser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 394 "Sintactico.y" /* yacc.c:1646  */
    {
                                        (yyval.nodito) = new Nodo("RMGRP","");
                                        Nodo *n = new Nodo("name", (yyvsp[0].text));
                                        (yyval.nodito)->add(*n);
                                     }
#line 2220 "parser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 399 "Sintactico.y" /* yacc.c:1646  */
    {
                                    (yyval.nodito) = new Nodo("RMGRP", "");
                                    Nodo *n = new Nodo("name",(yyvsp[0].text));
                                    (yyval.nodito)->add(*n);
                                 }
#line 2230 "parser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 404 "Sintactico.y" /* yacc.c:1646  */
    {
                           (yyval.nodito) = (yyvsp[-1].nodito);
                           (yyval.nodito)->add(*(yyvsp[0].nodito));
                         }
#line 2239 "parser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 408 "Sintactico.y" /* yacc.c:1646  */
    {
                        (yyval.nodito) = new Nodo("PARAMETRO", "");
                        (yyval.nodito)->add(*(yyvsp[0].nodito));
                     }
#line 2248 "parser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 413 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("user",(yyvsp[0].text)); }
#line 2254 "parser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 414 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("user",(yyvsp[0].text)); }
#line 2260 "parser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 415 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("password", (yyvsp[0].text)); }
#line 2266 "parser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 416 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("password",(yyvsp[0].text)); }
#line 2272 "parser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 417 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("group", (yyvsp[0].text)); }
#line 2278 "parser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 419 "Sintactico.y" /* yacc.c:1646  */
    {
                                        (yyval.nodito) = new Nodo("RMUSR","");
                                        Nodo *n = new Nodo("user",(yyvsp[0].text));
                                        (yyval.nodito)->add(*n);
                                     }
#line 2288 "parser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 424 "Sintactico.y" /* yacc.c:1646  */
    {
                                  (yyval.nodito) = new Nodo("RMUSR", "");
                                  Nodo *n = new Nodo("user",(yyvsp[0].text));
                                  (yyval.nodito)->add(*n);
                               }
#line 2298 "parser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 430 "Sintactico.y" /* yacc.c:1646  */
    {
                          (yyval.nodito) = (yyvsp[-1].nodito);
                          (yyval.nodito)->add(*(yyvsp[0].nodito));
                         }
#line 2307 "parser.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 434 "Sintactico.y" /* yacc.c:1646  */
    {
                       (yyval.nodito) = new Nodo("PARAMETRO","");
                       (yyval.nodito)->add(*(yyvsp[0].nodito));
                     }
#line 2316 "parser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 439 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("path",(yyvsp[0].text)); }
#line 2322 "parser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 440 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("path",(yyvsp[0].text)); }
#line 2328 "parser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 441 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("ugo",(yyvsp[0].text)); }
#line 2334 "parser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 442 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("r",""); }
#line 2340 "parser.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 444 "Sintactico.y" /* yacc.c:1646  */
    {
                              (yyval.nodito) = (yyvsp[-1].nodito);
                              (yyval.nodito)->add(*(yyvsp[0].nodito));
                            }
#line 2349 "parser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 448 "Sintactico.y" /* yacc.c:1646  */
    {
                        (yyval.nodito) = new Nodo("PARAMETRO","");
                        (yyval.nodito)->add(*(yyvsp[0].nodito));
                      }
#line 2358 "parser.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 454 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("path",(yyvsp[0].text)); }
#line 2364 "parser.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 455 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("path",(yyvsp[0].text)); }
#line 2370 "parser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 456 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("size",(yyvsp[0].text)); }
#line 2376 "parser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 457 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("cont",(yyvsp[0].text)); }
#line 2382 "parser.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 458 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("cont",(yyvsp[0].text)); }
#line 2388 "parser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 459 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("p",""); }
#line 2394 "parser.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 461 "Sintactico.y" /* yacc.c:1646  */
    {
                          (yyval.nodito) = new Nodo("CAT","");
                          Nodo *n = new Nodo("file",(yyvsp[0].text));
                          (yyval.nodito)->add(*n);
                        }
#line 2404 "parser.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 466 "Sintactico.y" /* yacc.c:1646  */
    {
                             (yyval.nodito) = new Nodo("CAT","");
                             Nodo *n = new Nodo("file",(yyvsp[0].text));
                             (yyval.nodito)->add(*n);
                           }
#line 2414 "parser.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 472 "Sintactico.y" /* yacc.c:1646  */
    {
                          (yyval.nodito) = new Nodo("REM","");
                          Nodo *n = new Nodo("path",(yyvsp[0].text));
                          (yyval.nodito)->add(*n);
                        }
#line 2424 "parser.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 477 "Sintactico.y" /* yacc.c:1646  */
    {
                               (yyval.nodito) = new Nodo("REM","");
                               Nodo *n = new Nodo("path",(yyvsp[0].text));
                               (yyval.nodito)->add(*n);
                            }
#line 2434 "parser.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 483 "Sintactico.y" /* yacc.c:1646  */
    {
                        (yyval.nodito) = (yyvsp[-1].nodito);
                        (yyval.nodito)->add(*(yyvsp[0].nodito));
                      }
#line 2443 "parser.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 487 "Sintactico.y" /* yacc.c:1646  */
    {
                     (yyval.nodito) = new Nodo("PARAMETRO","");
                     (yyval.nodito)->add(*(yyvsp[0].nodito));
                   }
#line 2452 "parser.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 492 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("path",(yyvsp[0].text)); }
#line 2458 "parser.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 493 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("path",(yyvsp[0].text)); }
#line 2464 "parser.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 494 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("cont", (yyvsp[0].text)); }
#line 2470 "parser.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 496 "Sintactico.y" /* yacc.c:1646  */
    {
                    (yyval.nodito) = (yyvsp[-1].nodito);
                    (yyval.nodito)->add(*(yyvsp[0].nodito));
                   }
#line 2479 "parser.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 500 "Sintactico.y" /* yacc.c:1646  */
    {
                   (yyval.nodito) = new Nodo("PARAMETRO","");
                   (yyval.nodito)->add(*(yyvsp[0].nodito));
                 }
#line 2488 "parser.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 505 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("path", (yyvsp[0].text)); }
#line 2494 "parser.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 506 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("path",(yyvsp[0].text)); }
#line 2500 "parser.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 507 "Sintactico.y" /* yacc.c:1646  */
    {
                                                  (yyval.nodito) = new Nodo("name","");
                                                  Nodo *n = new Nodo((yyvsp[-1].text),(yyvsp[0].text));
                                                  (yyval.nodito)->add(*n);
                                                }
#line 2510 "parser.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 512 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("name",(yyvsp[0].text)); }
#line 2516 "parser.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 514 "Sintactico.y" /* yacc.c:1646  */
    {
                           (yyval.nodito) = (yyvsp[-1].nodito);
                           (yyval.nodito)->add(*(yyvsp[0].nodito));
                         }
#line 2525 "parser.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 518 "Sintactico.y" /* yacc.c:1646  */
    {
                      (yyval.nodito) = new Nodo("PARAMETRO","");
                      (yyval.nodito)->add(*(yyvsp[0].nodito));
                    }
#line 2534 "parser.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 523 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("path",(yyvsp[0].text)); }
#line 2540 "parser.cpp" /* yacc.c:1646  */
    break;

  case 139:
#line 524 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("path",(yyvsp[0].text)); }
#line 2546 "parser.cpp" /* yacc.c:1646  */
    break;

  case 140:
#line 525 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("id",(yyvsp[0].text));}
#line 2552 "parser.cpp" /* yacc.c:1646  */
    break;

  case 141:
#line 526 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("p",""); }
#line 2558 "parser.cpp" /* yacc.c:1646  */
    break;

  case 142:
#line 528 "Sintactico.y" /* yacc.c:1646  */
    {
                 (yyval.nodito) = (yyvsp[-1].nodito);
                 (yyval.nodito)->add(*(yyvsp[0].nodito));
               }
#line 2567 "parser.cpp" /* yacc.c:1646  */
    break;

  case 143:
#line 532 "Sintactico.y" /* yacc.c:1646  */
    {
                (yyval.nodito) = new Nodo("PARAMETRO","");
                (yyval.nodito)->add(*(yyvsp[0].nodito));
              }
#line 2576 "parser.cpp" /* yacc.c:1646  */
    break;

  case 144:
#line 537 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("path",(yyvsp[0].text)); }
#line 2582 "parser.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 538 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("path",(yyvsp[0].text)); }
#line 2588 "parser.cpp" /* yacc.c:1646  */
    break;

  case 146:
#line 539 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("dest",(yyvsp[0].text)); }
#line 2594 "parser.cpp" /* yacc.c:1646  */
    break;

  case 147:
#line 540 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("dest",(yyvsp[0].text)); }
#line 2600 "parser.cpp" /* yacc.c:1646  */
    break;

  case 148:
#line 542 "Sintactico.y" /* yacc.c:1646  */
    {
                  (yyval.nodito) = (yyvsp[-1].nodito);
                  (yyval.nodito)->add(*(yyvsp[0].nodito));
                }
#line 2609 "parser.cpp" /* yacc.c:1646  */
    break;

  case 149:
#line 546 "Sintactico.y" /* yacc.c:1646  */
    {
                (yyval.nodito) = new Nodo("PARAMETRO","");
                (yyval.nodito)->add(*(yyvsp[0].nodito));
              }
#line 2618 "parser.cpp" /* yacc.c:1646  */
    break;

  case 150:
#line 551 "Sintactico.y" /* yacc.c:1646  */
    {
                        (yyval.nodito) =(yyvsp[-1].nodito);
                        (yyval.nodito)->add(*(yyvsp[0].nodito));
                      }
#line 2627 "parser.cpp" /* yacc.c:1646  */
    break;

  case 151:
#line 555 "Sintactico.y" /* yacc.c:1646  */
    {
                     (yyval.nodito) = new Nodo("PARAMETRO","");
                     (yyval.nodito)->add(*(yyvsp[0].nodito));
                   }
#line 2636 "parser.cpp" /* yacc.c:1646  */
    break;

  case 152:
#line 560 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("path",(yyvsp[0].text)); }
#line 2642 "parser.cpp" /* yacc.c:1646  */
    break;

  case 153:
#line 561 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("path",(yyvsp[0].text)); }
#line 2648 "parser.cpp" /* yacc.c:1646  */
    break;

  case 154:
#line 562 "Sintactico.y" /* yacc.c:1646  */
    {
                                        (yyval.nodito) = new Nodo("name","");
                                        Nodo *n = new Nodo((yyvsp[-1].text),(yyvsp[0].text));
                                        (yyval.nodito)->add(*n);
                                      }
#line 2658 "parser.cpp" /* yacc.c:1646  */
    break;

  case 155:
#line 567 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("name",(yyvsp[0].text)); }
#line 2664 "parser.cpp" /* yacc.c:1646  */
    break;

  case 156:
#line 569 "Sintactico.y" /* yacc.c:1646  */
    {
                           (yyval.nodito) = (yyvsp[-1].nodito);
                           (yyval.nodito)->add(*(yyvsp[0].nodito));
                         }
#line 2673 "parser.cpp" /* yacc.c:1646  */
    break;

  case 157:
#line 573 "Sintactico.y" /* yacc.c:1646  */
    {
                       (yyval.nodito) = new Nodo("PARAMETRO","");
                       (yyval.nodito)->add(*(yyvsp[0].nodito));
                     }
#line 2682 "parser.cpp" /* yacc.c:1646  */
    break;

  case 158:
#line 578 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("path",(yyvsp[0].text)); }
#line 2688 "parser.cpp" /* yacc.c:1646  */
    break;

  case 159:
#line 579 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("path", (yyvsp[0].text)); }
#line 2694 "parser.cpp" /* yacc.c:1646  */
    break;

  case 160:
#line 580 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("user",(yyvsp[0].text)); }
#line 2700 "parser.cpp" /* yacc.c:1646  */
    break;

  case 161:
#line 581 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("user",(yyvsp[0].text)); }
#line 2706 "parser.cpp" /* yacc.c:1646  */
    break;

  case 162:
#line 582 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("r",""); }
#line 2712 "parser.cpp" /* yacc.c:1646  */
    break;

  case 163:
#line 584 "Sintactico.y" /* yacc.c:1646  */
    {
                           (yyval.nodito) = (yyvsp[-1].nodito);
                           (yyval.nodito)->add(*(yyvsp[0].nodito));
                         }
#line 2721 "parser.cpp" /* yacc.c:1646  */
    break;

  case 164:
#line 588 "Sintactico.y" /* yacc.c:1646  */
    {
                      (yyval.nodito) = new Nodo("PARAMETRO","");
                      (yyval.nodito)->add(*(yyvsp[0].nodito));
                    }
#line 2730 "parser.cpp" /* yacc.c:1646  */
    break;

  case 165:
#line 593 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("user",(yyvsp[0].text)); }
#line 2736 "parser.cpp" /* yacc.c:1646  */
    break;

  case 166:
#line 594 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("user",(yyvsp[0].text)); }
#line 2742 "parser.cpp" /* yacc.c:1646  */
    break;

  case 167:
#line 595 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("group",(yyvsp[0].text));}
#line 2748 "parser.cpp" /* yacc.c:1646  */
    break;

  case 168:
#line 596 "Sintactico.y" /* yacc.c:1646  */
    { (yyval.nodito) = new Nodo("group", (yyvsp[0].text)); }
#line 2754 "parser.cpp" /* yacc.c:1646  */
    break;

  case 169:
#line 598 "Sintactico.y" /* yacc.c:1646  */
    {
                                            (yyval.nodito) = new Nodo("RECOVERY","");
                                            Nodo *n = new Nodo("id",(yyvsp[0].text));
                                            (yyval.nodito)->add(*n);
                                          }
#line 2764 "parser.cpp" /* yacc.c:1646  */
    break;

  case 170:
#line 604 "Sintactico.y" /* yacc.c:1646  */
    {
                                    (yyval.nodito) = new Nodo("LOSS","");
                                    Nodo *n = new Nodo("id",(yyvsp[0].text));
                                    (yyval.nodito)->add(*n);
                                 }
#line 2774 "parser.cpp" /* yacc.c:1646  */
    break;


#line 2778 "parser.cpp" /* yacc.c:1646  */
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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
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
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
