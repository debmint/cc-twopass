/* ************************************************************* *
 * defines.h - Contains definitions that may make things clearer *
 * ************************************************************* */

/* $Id: defines.h 25 2008-06-25 17:37:03Z dlb $ */

/* The following has been imported from cj.h - will eventually remove
 * most of the original
 */

#undef getline

/*  Machine/Operating System dependent definitions.
 *
 *  see also 'local.c'.
 */

#ifdef OS9
#define INTTYPE     int
#define LONGTYPE    long
#define FLOATYPE    float
#define DBLETYPE    double
#endif

#ifdef OSK
#define INTTYPE     short
#define LONGTYPE    long
#define FLOATYPE    float
#define DBLETYPE    double
#endif

#ifdef unix
#define direct
#define register
#define INTTYPE     short
#define LONGTYPE    long
#define FLOATYPE    float
#define DBLETYPE    double
#endif

#define MICRO               /* suppresses word boundary forcing */
#define DOFLOATS            /*  include floating point code */
#define FNAMESIZE   30      /* file name size */

#define LINESIZE    256
#define MODNAMSIZE  15      /* module name */

#define NAMESIZE    8       /* identifiers for assembler */
#define UNIQUE      '_'     /* for local labels etc. */
#define NEWLINE     13

typedef struct structstruct {
    struct structstruct *strnext;   /* next element in structure */
    struct symstr *element;         /* ptr to mos entry */
} elem;

typedef struct dimstr {
    short dim;              /* size of this dimension */
    struct dimstr *dptr;    /* ptr to next dimension */
} dimnode;

typedef struct downsym {
    short type;             /* type of entry */
    int size;               /* size of entry */
    dimnode *dimptr;        /* ptr to list of dimensions */
    int offset;             /* general purpose */
    int storage;            /* storage class */
    union {
        elem *elems;        /* chain of structure members */
        int labflg;         /* label flags */
    } x;
    short blklev;           /* block level of declaration */
    struct symstr *downptr, /* ptr to 'hidden' outer declaration */
                  *snext;   /* ptr to entry in various lists */
} pshnode;

#define DOWNSIZE sizeof(pshnode)

typedef struct symstr {
    short type;             /* type of entry */
    int size;               /* size of entry */
    dimnode *dimptr;        /* ptr to list of dimensions */
    int offset;             /* general purpose */
    int storage;            /* storage class */
    union {
        elem *elems;        /* chain of structure members */
        int labflg;         /* label flag */
    } x;
    short blklev;           /* block level of declaration */
    struct symstr *downptr, /* ptr to 'hidden' outer declaration */
                  *snext,   /* ptr to entry in various lists */
                  *hlink;   /* ptr to next symbol in hash chain */
    char sname[NAMESIZE+1]; /* name entry */
} symnode;

#define SYMSIZE sizeof(symnode)

typedef struct expstr {
    short type;             /* type of node */
    int size;               /* size of basic type */
    dimnode *dimptr;        /* ptr to list of dimensions */
    short op;               /* operator */
    union {
        int num;            /* numeric value */
        symnode *sp;        /* symbol pointer */
        long *lp;           /* long constant ptr */
#ifdef DOFLOATS
        FLOATYPE *fp;       /* float constant ptr */
        DBLETYPE *dp;       /* double constant ptr */
#endif
    } val;                  /* value or symbol ptr */
    struct expstr *left,    /* left node ptr */
                  *right;   /* right node ptr */
    short lno;              /* line # of token causing this node */
    char *pnt;              /* ptr to line position of token */
    short sux;              /* pseudo Sethi-Ullman number */
    short modifier;         /* added to NAME references */
} expnode;

#define NODESIZE sizeof(expnode)

typedef struct initstruct {
    struct initstruct *initnext;    /* next initializer */
    expnode *initp;                 /* ptr to initializer expression */
    symnode *initname;              /* ptr to dude being initialized */
} initnode;

/* object sizes - char is by definition 1 */
#define INTSIZE     2
#define LONGSIZE    4

#ifdef  DOFLOATS
#define FLOATSIZE   4
#define DOUBLESIZE  8
#endif

#define POINTSIZE   2

/*  symbols  */
#define POINTER     0x10
#define ARRAY       0x20
#define FUNCTION    0x30

#define XTYPE       0x30
#define BASICT      0x0F

#define INT         1
#define CHAR        2
#define UNION       3
#define STRUCT      4
#ifdef  DOFLOATS
#define FLOAT       5
#define DOUBLE      6
#endif
#define UNSIGN      7
#define LONG        8
#define LABEL       9
#define USTRUCT     10

#define STRTAG      8
#define SHORT       10
#define ARG         11
#define EXTDEF      12
#define AUTO        13
#define EXTERN      14
#define STATIC      15
#define REG         16
#define RETURN      18
#define MOS         17
#define IF          19
#define WHILE       20
#define ELSE        21
#define SWITCH      22
#define CASE        23
#define BREAK       24
#define CONTIN      25
#define DO          26
#define DEFAULT     27
#define FOR         28
#define GOTO        29
#define TYPEDEF     30
#define DEFTYPE     31
#define CAST        32
#define DIRECT      33   /* direct */
#define EXTERND     34   /* extern direct */
#define STATICD     35   /* static direct */

#define SEMICOL     40
#define LBRACE      41
#define RBRACE      42
#define LBRACK      43
#define RBRACK      44
#define LPAREN      45
#define RPAREN      46
#define COLON       47
#define COMMA       48
#define KEYWORD     51
#define NAME        52
#define CONST       54
#define STRING      55
#define SIZEOF      59
#define INCBEF      60
#define DECBEF      61
#define INCAFT      62
#define DECAFT      63
#define NOT         64
#define AMPER       65
#define STAR        66
#define NEG         67
#define COMPL       68
#define DOT         69
#define ARROW       70
#define DBLAND      71
#define DBLOR       72
#define LCONST      74
#ifdef DOFLOATS
#define FCONST      75
#endif
#define UMOD        76
#define USHR        77
#define UDIV        78
#define RSUB        79
#define PLUS        80
#define MINUS       81
#define TIMES       82
#define DIV         83
#define MOD         84
#define SHR         85
#define SHL         86
#define AND         87
#define OR          88
#define XOR         89

#define EQ          90
#define NEQ         91
#define LEQ         92
#define LT          93
#define GEQ         94
#define GT          95
#define ULEQ        96
#define ULT         97
#define UGEQ        98
#define UGT         99

#define ASSIGN      120

#define QUERY       100
#define CALL        101
#define BSLASH      102
#define SHARP       103
#define PRIME       104
#define QUOTE       105
#define LETTER      106
#define DIGIT       107
#define NEWLN       108
#define SPACE       109

/* code generator symbols */
#define STACK       110
#define UREG        111
#define DREG        112
#define XREG        113
#define EXG         115
#define LEA         116
#define LOAD        117
#define YREG        118
#define NODE        119
#define STORE       121
#define PUSH        122
#define LEAX        123
#define JMP         124
#define JMPEQ       125
#define JMPNE       126
#define LOADIM      127
#define FREG        128

#define COMPARE     129
#define CNDJMP      130
#define ITOL        131
#define LTOI        132
#define CTOI        133
#define UTOL        134
#define DBLOP       135
#define LONGOP      136
#define MOVE        137
#define STOI        138
#define TEST        139
#ifdef DOFLOATS
#define FTOD        140
#define DTOF        141
#define ITOD        142
#define DTOI        143
#define LTOD        144
#define DTOL        145
#define UTOD        146
#endif
#define XIND        147
#define YIND        148
#define UIND        149

#define HALVE       150
#define UHALVE      151
#define IDOUBLE     152

#define ASSPLUS     160
#define ASSMIN      161
#define ASSMUL      162
#define ASSDIV      163
#define ASSMOD      164
#define ASSSHR      165
#define ASSSHL      166
#define ASSAND      167
#define ASSOR       168
#define ASSXOR      169

/* indirection masks */
#define INDIRECT    0x8000
#define NOTIND      0x7FFF

/* label tests */
#define DEFINED     1
#define GONETO      2

/* dp indicators */
#define DDP         1  /* on dp */
#define NDP         0  /* not on dp */

#define UNKN        0
#define UNDECL      0

#ifdef TRUE
#undef TRUE
#undef FALSE
#endif

#define TRUE        1
#define FALSE       0
#define ERR         0xFFFF

#define TAB_CHAR    9
#define LINEFEED    10
#define FORMFEED    12
#define RET_CHAR    13
#define VTAB_CHAR   11
#define BACKSPACE   8

#define btype(t)    ((t) & BASICT)
#define isptr(t)    (((t) & XTYPE) == POINTER)
#define isary(t)    (((t) & XTYPE) == ARRAY)
#define isftn(t)    (((t) & XTYPE) == FUNCTION)
#define modtype(t,b) (((t) & (~BASICT)) + b)

#define getlabel(a) (++curlabel)

#define islong(t)   (t->type == LONG)
#ifdef DOFLOATS
#define isfloat(t)  (t->type == FLOAT || t->type == DOUBLE)
#endif


/* The below comes from the original, which, for the most part will
 * eventually be removed
 */

#ifndef COCO
#   ifndef direct
#       define direct
#   endif
#   ifndef register
#       define register
#   endif
#endif

#ifdef COCO
#   define putword(w,f) putw (w,f)
#else
#   define putword(w,f) putc ((w >> 8) & 0xff, f); putc (w & 0xff, f)
#endif


/* COCO variable sizes */

#define CHARSIZ 1
#define INTSIZ 2
#define UNSGNSIZ 2
#define LONGSIZ 4
#define FLOATSIZ 4
#define DBLSIZ 8

#define ispointer(s) (((s) & 0x30) == 0x10)
#define inbraces(s) (((s) & 0x30) == 0x20)
#define inparentheses(s) (((s) & 0x30) == 0x30)

/* Label definition structure (symnode) 30 bytes?? */

typedef struct lbl_def {
    int gentyp;
    int vsize;
    void *w4;            /* offset 04 */
    int lbl_nbr;
    int fnccode;
    /*void *w8;*/
    int p10;
    int p12;
    struct lbl_def **ftop;      /* offset 14 */
    struct lbl_def *w16;
    struct lbl_def *fnext;     /* offset 18 */
    char fnam[8];           /* offset 20 */
} LBLDEF;

/* This is a "cmdref" structure.  I believe that this is a structure
 * that is defined for the current cmd, and is distinct from the "lbl_def"
 * structure.  It is a 22(?) byte structure, as opposed to the 28-byte
 * "lbldef" structure */
/* expnode?? */

typedef struct cmd_ref {
    int ft_Ty;
    int __cr2;
    int __cr4;
    int vartyp;     /* +6 */
    /* cmdval MAY be a pointer to the value of the expression
     * See pass1_07.c around line 375 (after else L4f8b) */
    int cmdval;
    struct cmd_ref *cr_Left;
    struct cmd_ref *cr_Right;
    int _cline;     /* Current line # */            /* +14 */
    char *_lpos;      /* Current position in line */  /* +8 */
    int __cr18;
    int cr_Nxt;
} CMDREF;

/* Case reference - intnode?? */
struct case_ref {
    struct case_ref *case_nxt;
    int cas04;
    int cas06;
};

/* This probably replaces the above case_ref */
typedef struct casestct {
    struct casestct *clink;     /* next case in case list */
    int cval;                   /* case value */
    short clab;                 /* case label */
} casnode;

/* Storage for a double.  This structure stores a double in the native
 * format for the host, (native) plus a coco array stored as a set of
 * 4 ints.  This is _probably_ not a direct representation of a true
 * coco double, due to big-endian storages, and size of int, but in
 * the format we use, we can directly write the 4 int's as "fdb"'s
 */

struct dbltree {
    double native;      /* Host native value          */
    int cocoarr[4];     /* Coco version of the double */
};

/* Some structure found in pass1_05.c */
struct some_struct {
    struct some_struct *ss_prev;
    CMDREF *ss02;
    LBLDEF *mylbl;
};

/* Struct/union member definition */

struct memberdef
{
    struct memberdef *mbrPrev;
    LBLDEF *mmbrlbl;
};

/* Brace member definition */

struct bracedef
{
    CMDREF *brCmd;
    struct bracedef *brNxt;
};

/* Another structure of some sort found in p1_01.c
 * pshnode?? */
struct g18 {
    struct g18 *g18Nxt;
    int g18_2;
    int g18_4;
    int g18_6;
    int g18_8;
    int g18_10;
    int g18_12;
    struct g18 * g18_14;
    struct g18 *g18Prev;    /* +16 */
};

struct lng_something {
    int smptr;
    long sm_val;
};

/* The following is a structure found in p2_01.c */

struct nwref {
    int ftyp;
    int nw02;
    union {
        char st[9];
        int wrd;
    } rfdat;
};

/* lbltype->fnccodes */

#define FT_INT 1
#define FT_CHAR 2
#define FT_UNION 3
#define FT_STRUCT 4
#define FT_FLOAT 5
#define FT_DOUBLE 6
#define FT_UNSIGNED 7
#define FT_LONG 8
#define FT_SHORT 10
#define FT_LSEEK 12
#define FT_AUTO 13
#define FT_EXTERN 14
#define FT_STATIC 15
#define FT_REGISTER 16
#define FT_STRCMBR 17
#define FT_RETURN 18
#define FT_IF 19
#define FT_WHILE 20
#define FT_ELSE 21
#define FT_SWITCH 22
#define FT_CASE 23
#define FT_BREAK 24
#define FT_CONTINUE 25
#define FT_DO 26
#define FT_DEFAULT 27
#define FT_FOR 28
#define FT_GOTO 29
#define FT_TYPEDEF 30
#define FT_DIRECT 33
#define FT_DPXTRN 34
#define FT_DPSTATIC 35
#define FT_SIZEOF 59
/* the following defines _might_ be "C_" types */

/* _chcode values found in D005f */

#define C_SEMICOLON 40
#define C_LBRKET 41
#define C_RBRKET 42
#define C_LBRACE 43
#define C_RBRACE 44
#define C_LPAREN 45
#define C_RPAREN 46
#define C_COLON 47
#define C_COMMA 48
#define C_BUILTIN 51
#define C_USRLBL 52
#define C_INTSQUOT 54
#define C_DQUOT 55
#define C_SIZEOF 59
#define C_PLUSPLUS 60
#define C_MINMINUS 61
#define C_INCREMENT 62
#define C_DECREMENT 63
#define C_EXCLAM 64
#define C_AMPERSAND 65
#define C_ASTERISK 66
#define C_MINUS 67
#define C_TILDE 68
#define C_PERIOD 69
#define C_PTRREF 70
#define C_ANDAND 71
#define C_OROR 72
#define C_LONG 74
#define C_DOUBLE 75
#define C_PLUS 80
#define C_NEG 81
#define C_MULT 82
#define C_SLASH 83
#define C_PERCENT 84
#define C_RSHIFT 85
#define C_LSHIFT 86
#define C_AND 87
#define C_VBAR 88
#define C_CARET 89
#define C_EQEQ 90
#define C_NOTEQ 91
#define C_LT_EQ 92
#define C_LT 93
#define C_GT_EQ 94
#define C_GT 95
#define C_U_LTEQ 96
#define C_U_LT 97
#define C_U_GTEQ 98
#define C_U_GT 99
#define C_QUESTION 100
#define C_PARENS 101
#define C_BKSLSH 102
#define C_SQUOT 104
/*#define C_DQUOT 105*/
#define C_LBLCHR 106
#define C_DIGIT 107
#define C_SPACE 109
#define C_RGWRD 111
#define C_X_RGWRD 118
#define C_EQUAL 120
#define C_I2LNG 131
#define C_LNG2INT 132
#define C_CHR2INT 133
#define C_U2LNG 134
#define C_FLT2DBL 140
#define C_TOFLOAT 141
#define C_I2DBL 142
#define C_DBL2INT 143
#define C_L2DBL 144
#define C_DBL2LNG 145
#define C_U2DBL 146
#define C_PLUSEQ  160
#define C_MINEQU 161
#define C_X_EQ 162
#define C_DIV_EQ 163
#define C_PCT_EQ 164
#define C_RSH_EQ 165
#define C_LSHEQ 166
#define C_ANDEQ 167
#define C_OREQ 168
#define C_EOREQ 169

/* lbldef->gentype codes */

#define G_ERRNO 1
#define G_STRCT 4
#define G_STRCNAM 10
#define G_LSEEK 56

/* pointer depth/parenthesis masks */
#define P_POINTER 0x10
#define P_BRACE 0x20
#define P_PARENTHESES 0x30

