/* ****************************************************** *
 * pass1_08.c                                             *
 * ****************************************************** */

/* $Id: p1_08.c 18 2008-05-19 21:54:22Z dlb $ */

/* This file is _probably_ an exact match with original code
 * several brances, etc had to be altered, but none should matter
 */

#include <stdlib.h>
#include "pass1.h"

union data_tys {
        long l;
        double d;
        int i;
        char c[9];
};
typedef union {
    INTTYPE *ip;
    LONGTYPE *lp;
    FLOATYPE *fp;
    DBLETYPE *dp;
} numptrs;

#ifndef COCO
#   ifndef direct
#       define direct
#   endif
#endif

extern direct int datstring;
extern char _chcodes[];

typedef union {
    DBLETYPE *dpt;
    LONGTYPE *lpt;
    symnode * spt;
} rgpts;

/* ************************************************************ *
 * nxt_word() - Process a group of characters                   *
 *      Sets up sym and symval to appropriate codes            *
 *      If it's a valid Label, finds label or creates an entry  *
 *      If number, retrieves it and sets it up                  *
 *      If assignment or operator, sets up definition for it    *
 * Exit conditions:                                             *
 *      Builtin:                                                *
 *        sym = C_* type                                      *
 *        symval = fnccode (EXTERN if SIZEOF)                 *
 *      User Defined Label:                                     *
 *        sym = NAME                                      *
 *        symval = ptr to LBLDEF struct for this variable        *
 *      Numeric:                                                *
 *        sym = C_* type of number                            *
 *        symval = value itself if size <= sizeof (int)          *
 *                else ptr to the storage of the value          *
 *      Anything else:                                          *
 *        sym = C_* type                                      *
 *        symval = Info regarding any additional chars.  I.E.    *
 *                whether is is "+", "++", "+=", etc            *
 * ************************************************************ */

void 
nxt_word ()
{
    /* 21 bytes of static variables */

    register rgpts ptr;
    int numtype;
    char name[NAMESIZE + 1];
    numptrs np;
    DBLETYPE n;

    skipblank();

    if (CurChr == -1)
    {
        sym = -1;
        return;
    }

    symptr = CurLine - 1;
    symline = fileline;

    while ((sym = _chcodes[(int)CurChr]) == '\0')
    {
        reprterr ("bad character");
        getnxtch ();
        symptr = CurLine;
    }

    symval = _chcod_2[(int)CurChr];

    switch (sym)     /* at L5873 */
    {

        case LETTER:         /*alpha - must be label */   /* L5588 */

            fget_lbl (name);     /* Read in label name from file */
            ptr.spt = FindLbl (name);

            if ((sym = (ptr.spt->type == KEYWORD)))
            {
                /* All builtins except sizeof return unchanged */

                if ((symval = (ptr.spt->storage == SIZEOF)))
                {
                   sym = SIZEOF;
                   symval = EXTERN;        /* 14 */
                }
            }
            else
            {
               sym = NAME;
               symval = (int)ptr.spt;
            }

            break;         /* return */

        case DIGIT:                     /*digit */ /* L55c9 */
            numtype = number (INT, &n);
L55dc:
            np.dp = &n;
            
            switch (numtype)
            {
                case INT:    /* 1 */     /* L55e8 */
                    symval = *np.ip;
                    sym = CONST;
                    break;
                case LONG:  /* 8 */    /* L55ed */
                    ptr.lpt = addmem (sizeof (long));
                    *ptr.lpt = *np.lp;
                    symval = (int)(ptr.lpt);
                    sym = LCONST;    /* 'J' */
                    break;
                case DOUBLE:    /* L5609 */
                    ptr.dpt = (double *)addmem (sizeof (double));
                    *ptr.dpt = *np.dp;
                    symval = (int)(ptr.dpt);
                    sym = FCONST;    /* 'K' */
                    break;
                default:   /* L5625 */
                    reprterr ("constant overflow");
                    symval = 1;
                    sym = CONST;        /* '6' */
                    break;
            }

            break;

        case  PRIME: /* ' (single quote)*/  /* L564e */
            do_squot ();
            sym = CONST;
            break;
        case  QUOTE: /* " (double quote) */ /* L5656 */
            do_dquot ();
            sym = STRING;
            break;
        default:   /* L5661 */
            getnxtch ();

            switch (sym)
            {
                case DOT: /* '.' */       /* L5669 */
                    if (_chcodes[CurChr] == 0x6b)  /* Digit */
                    {
                        numtype = number (DOUBLE, &n);
                        goto L55dc;
                    }

                    break;

                case AMPER:          /* L5691 */
                    switch (CurChr)
                    {
                        case '&':          /* L5698 */
                            sym = DBLAND;
                            getnxtch ();
                            symval = 5;
                            break;
                        case '=':        /* L56a5 */
                            sym = ASSAND;
                            symval = 2;
                            getnxtch ();   /* 2008/04/15 fix &= error??? */
                            break;
                    }

                    break;
                case ASSIGN:              /* L56bd */
                    if (CurChr == '=')
                    {
                        sym = EQ;
                        symval = 9;
                        getnxtch ();
                    }

                    break;
                case OR:               /* L56d0 */
                    switch (CurChr)
                    {
                        case '|':          /* L56d7 */
                            sym = DBLOR;
                            getnxtch ();
                            symval = 4;
                            break;
                        case '=':          /* L56e4 */
                            sym = ASSOR;    /* +80 */
                            getnxtch ();
                            symval = 2;
                            break;
                    }

                    break;
                case NOT:              /* L5701 */
                    if (CurChr == '=')
                    {
                        sym = NEQ;
                        getnxtch ();
                        symval = 9;
                    }
                    
                    break;
                case STAR:             /* L5716 */
                    if (CurChr == '=')
                    {
                        sym = ASSMUL;
                        getnxtch ();
                        symval = 2;
                    }
                    
                    break;
                case DIV:
                case MOD:
                case XOR:              /* L5723 */
                    if (CurChr == '=')
                    {
                        sym += 80;
                        getnxtch ();
                        symval = 2;
                    }
                    
                    break;
                case LT:                 /* L5733 */
                    switch (CurChr)
                    {
                        case '<':          /* L573a */
                            sym = SHL;
                            symval = 11;
                            getnxtch ();

                            if (CurChr == '=')
                            {
                                sym = ASSSHL;   /* +80 */
                                symval = 2;
                                getnxtch ();
                            }
                            
                            break;
                        case '=':          /* L575a */
                            sym = LEQ;
                            symval = 10;
                            getnxtch ();
                            break;
                    }

                    break;
                case GT:                  /* L5772 */
                    switch (CurChr)
                    {
                        case '>':          /* L5779 */
                            sym = SHR;
                            symval = 11;
                            getnxtch ();

                            if (CurChr == '=')
                            {
                                sym = ASSSHR;  /*C_RSHFT + 80*/
                                symval = 2;
                                getnxtch ();
                            }

                            break;
                        case '=':              /* L5799 */
                            sym = GEQ;
                            symval = 10;
                            getnxtch ();
                            break;
                    }

                    break;
                case PLUS:                   /* L57b1 */
                    switch (CurChr)
                    {
                        case '+':              /* L57b8 */
                            sym = INCBEF;
                            symval = 14;
                            getnxtch ();
                            break;
                        case '=':              /* L57c2 */
                            sym = ASSPLUS;
                            symval = 2;
                            getnxtch ();
                            break;
                    }

                    break;
                case NEG:                  /* L57d9 */
                    switch (CurChr)
                    {
                        case '-':              /* L57e0 */
                            sym = DECBEF;
                            symval = 14;
                            getnxtch ();
                            break;

                        case '=':              /* L57ea */
                            sym = ASSMIN;  /* NEG + 80 */
                            symval = 2;
                            getnxtch ();
                            break;
                        case '>':              /* L57f4 */
                            sym = ARROW;  /* "->" */
                            symval = 15;
                            getnxtch ();
                            break;
                    }

                    break;
            }      /* end switch (sym) for default: */

            break;
    }       /* end outer switch (sym) */
}

void 
tblsetup ()
{
    register symnode *regptr;

    inizFTbl ("double", DOUBLE);
    inizFTbl ("float", FLOAT);
    inizFTbl ("typedef", TYPEDEF);
    inizFTbl ("static", STATIC);
    inizFTbl ("sizeof", SIZEOF);
    inizFTbl ("int", INT);
    Struct_Union = 1;
    inizFTbl ("int", INT);
    inizFTbl ("float", FLOAT);
    Struct_Union = 0;
    inizFTbl ("char", CHAR);
    inizFTbl ("short", SHORT);
    inizFTbl ("auto", AUTO);
    inizFTbl ("extern", EXTERN);
    inizFTbl ("direct", DIRECT);
    inizFTbl ("register", REG);
    inizFTbl ("goto", GOTO);
    inizFTbl ("return", RETURN);
    inizFTbl ("if", IF);
    inizFTbl ("while", WHILE);
    inizFTbl ("else", ELSE);
    inizFTbl ("switch", SWITCH);
    inizFTbl ("case", CASE);
    inizFTbl ("break", BREAK);
    inizFTbl ("continue", CONTIN);
    inizFTbl ("do", DO);
    inizFTbl ("default", DEFAULT);
    inizFTbl ("for", FOR);
    inizFTbl ("struct", STRUCT);
    inizFTbl ("union", UNION);
    inizFTbl ("unsigned", UNSIGN);
    inizFTbl ("long", LONG);
    
    regptr = FindLbl ("errno");
    regptr->type = INT;
    regptr->storage = EXTERN;
    regptr->size = 2;

    regptr = FindLbl("lseek");
    regptr->type = LONG | FUNCTION;
    regptr->storage = EXTDEF;
    regptr->size = 4;
}

/* ***************************************************************** *
 * fget_lbl () - read a label name from input stream int _dest.      *
 *      ( up to 8 chars), and set file position to end of the string *
 * ***************************************************************** */

void
#ifndef COCO
fget_lbl (register char *_dst)
#else
fget_lbl (_dst)
    register char *_dst;
#endif
{
    int _strln;

    _strln = 1;

    while (islblchr (CurChr) && (_strln <= NAMESIZE))
    {
        *(_dst++) = CurChr;
        getnxtch ();
        ++_strln;
    }

    if (_strln == 2)
    {
        *(_dst++) = UNIQUE;
    }
    
    *_dst = '\0';

    /* Now drop off any extra characters into the bit bucket */

    while (islblchr (CurChr))
    {
        getnxtch ();
    }
}

/* A _chcodes type function */

#ifndef COCO

int
islblchr (int pos)
#else

int 
islblchr (pos)
int pos;
#endif
{
    /*if ((_chcodes[pos] == '\x6a') || (_chcodes[pos] == '\x6b'))
    {
        return 1;
    }
    else
    {
        return 0;
    }*/
    return ((_chcodes[pos] == LETTER) || (_chcodes[pos] == DIGIT));
}

/* *********************************************** *
 * FindLbl () - Search for a label entry.          *
 *      return entry if found,  create one if none *
 *      found                                      *
 * *********************************************** */

symnode *
#ifndef COCO
FindLbl ( char *name)
#else
FindLbl ( name)
    char *name;
#endif
{
    symnode **tptr;
    symnode **tab;
    int v0;

    register symnode *nptr;

    /* The tree is divided up into two 128-byte trees
     * StrctLbls for structure/union labels, and NStrLbls for all the rest
     */

    tab = (Struct_Union ? StrctLbls : NStrLbls);

    tptr = &tab[str_sum (name)];   /* "lsl d" type thing */
    nptr = *(tptr);

    /* Search the list for a match, return entry if found */

    while (nptr)
    {
        if ((nptr->sname)[0] == name[0])    /* first chr of name match? */
        {
            if (!strncmp (name, nptr->sname, NAMESIZE))
            {
                return nptr;                  /* Found it... return */
            }
        }

        nptr = nptr->hlink;
    }

    if ((nptr = freesym) != 0)
    {
        freesym = nptr->hlink;
    }
    else
    {
        nptr = addmem (SYMSIZE);
    }

    strncpy (nptr->sname, name, NAMESIZE);
    nptr->type = 0;
    nptr->storage = 0;

    /* This entry will be inserted as the "first" entry in the list.
     * I. E. the base will point to this entry, this entry's ->hlink
     * will point to the previous "first"
     */

    nptr->hlink = *tptr;
    *tptr = nptr;
    nptr->downptr = (symnode *)tptr;     /* quick trip to the top? */

    return nptr;
}

void
#ifndef COCO
inizFTbl (char *name, int type)
#else
inizFTbl (name, type)
    char *name;
    int type;
#endif
{
    char neword[NAMESIZE + 1];
    register symnode *_ftbl;

    strncpy (neword, name, NAMESIZE);
    neword[NAMESIZE] = '\0';
    _ftbl = FindLbl (neword);
    _ftbl->type= KEYWORD;
    _ftbl->storage = type;
}

/* ***************************************** *
 * str_sum() - returns the sum of the values *
 *          of characters in a string        *
 * ***************************************** */

unsigned int
#ifndef COCO
str_sum (register char *nam)
#else
str_sum (nam)
    register char *nam;
#endif
{
    unsigned int _sum;
    int _curch;

    _sum = 0;

    while ((_curch = *(nam++)) != '\0')
    {
        _sum += _curch;
    }

    return (_sum & 0x7f);
}

void *
#ifndef COCO
addmem (int siz)
#else
addmem (siz)
    int siz;
#endif
{
#ifdef COCO
    int
#else
    void *
#endif
    memptr;

#ifdef COCO
    if ((memptr = sbrk(siz)) == -1)
    {
        fatal ("out of memory");
    }
#else
    if (!(memptr = calloc (1, siz)))
    {
        fatal ("out of memory");
    }
#endif

    if (!LblPtrLow)
    {
        LblPtrLow = memptr;
    }

    LblPtrEnd = memptr + siz;
    return memptr;
}


/* ******************************************************** *
 * number() - reads in a string from the file and converts *
 *      it to the appropriate number value                  *
 * Returns: the FT_* type on success, 0 on failure          *
 * ******************************************************** */
#ifndef COCO

int
number (int p1, void *dest_val)
{
    /* Copy source string to local storage.  This will keep
     * all global pointers updated correctly
     */

    char _tmpstr[50];
    char *_tmpptr,
         *_endptr;
    int cnt;
    double _dbl;
    int _ival,
        _ishex;

    cnt = sizeof (_tmpstr);
    _tmpptr = _tmpstr;
    *_tmpptr = '\0';
    _ishex = 0;

    if ((*_tmpptr = CurChr) == '0')
    {
        *(_tmpptr++) = CurChr;
        getnxtch ();
        --cnt;

        if (toupper (CurChr) == 'X')
        {
            _ishex = 1;
            *(_tmpptr++) = CurChr;
            getnxtch ();
            --cnt;
        }
    }

    while ((isxdigit (CurChr)) || (CurChr == '.') ||
            ((toupper (CurChr)) == 'E'))
    {
        *(_tmpptr++) = CurChr;

        if ((--cnt) <= 1)
        {
            break;
        }

        getnxtch ();
    }

    *_tmpptr = '\0';

    if (!(_ishex) && (index (_tmpstr, '.') || index (_tmpstr, 'e') ||
                    (index (_tmpstr, 'E'))))
    {
        *((double **)dest_val) = malloc (sizeof (double));
        **((double **)dest_val) = strtod (_tmpstr, &_endptr);
        return DOUBLE;
    }

    /**(long *)dest_val = (int)strtol (_tmpstr, &_endptr, 0);*/

    if ((toupper (CurChr)) == 'L')
    {
        *((long **)dest_val) = malloc (sizeof (long));
        **((long **)dest_val) = strtol (_tmpstr, &_endptr, 0);
        getnxtch ();
        return LONG;
    }
    else
    {
        *((int *)dest_val) = (int)strtol (_tmpstr, &_endptr, 0);
        return INT;
    }
}

#else

int 
number (p1, dest_val)
    int p1;
    register double *dest_val;
{
    double _number;
    int _expon;
    int _negflg;
    int v2;
    char *nptr;

    v2 = 0;
    _number = 0;

    nptr = (char *)(&_number);

    if (p1 == DOUBLE)
    {
        goto do_decimal;
    }

                            /*L5c89*/
    if (CurChr == '0')          /* '0' octal or "0x" ? */  /* else L5d96 */
    {
        long _my_nmbr;
        long *_xo_numptr;

        getnxtch ();

        if (CurChr == '.')
        {
            getnxtch ();
            goto do_decimal;
        }

        _my_nmbr = 0;       /*L5ca5*/

        if ((CurChr =='x') || (CurChr == 'X'))  /* 'x' hex */  /* else L5d38 */
        {
            int myint;

            getnxtch ();

            while ((myint = is_hex (CurChr)))       /* L5cfb */
            {
                _my_nmbr = ((_my_nmbr << 4) +
                        (myint - ((myint >= 'A') ? 'A' - 10 : '0')));
                getnxtch ();
            }
        }
        else        /* It's an octal # */        /*L5d38*/
        {
            while (is_octal (CurChr))
            {
                _my_nmbr = ((_my_nmbr << 3) + (CurChr - '0'));
                getnxtch ();
            }
        }

        /* L5d44 */
        _xo_numptr = &_my_nmbr;

        if ((CurChr == 'L') || (CurChr == 'l')) /* Long */   /* else L5d5c */
        {
            getnxtch ();
            goto retrnlong;
        }

        if ((*(int *)_xo_numptr) == 0)        /*L5d5c*/
        {
            *(int *)dest_val = (int)_my_nmbr;
            return INT;
        }

retrnlong:
        *(long *)dest_val = _my_nmbr;
        return LONG;
    }

    /* The following is a modified (?) version of atof
     * We'll try to follow the original code, but when we port,
     * we'll try to use std library routines
     */

    while (_chcodes[CurChr] == 0x6b)    /* isdigit(CurChr) */      /*L5d96 */
    {
        if (L549c (&(_number), CurChr))     /* else L5dda ?????? */
        {
            getnxtch ();
            return 0;
        }

        getnxtch ();
    }

    if ((CurChr == '.') || (CurChr == 'e') || (CurChr == 'E')) /* else L5e95 */
    {
        /*L5db9*/
        if (CurChr == '.')       /* else L5df9 */
        {
            getnxtch ();           /* go to L5dea */

do_decimal:
            while (_chcodes[CurChr] == 0x6b)    /* digit */ /*L5dea*/
            {
                if (L549c (&(_number), CurChr))
                {
                    getnxtch ();       /* go to L5ea5 */
                    return 0;
                }
                else
                {
                     getnxtch ();
                     ++v2;
                }
            }
        }

        /*L5df9*/
        if ((CurChr == 'E') || (CurChr == 'e'))   /* else L5e75 */
        {
            _negflg = 1;
            getnxtch ();

            if (CurChr == '+')
            {
                getnxtch ();
            }
            else
            {
                if (CurChr == '-')
                {
                    getnxtch ();
                    _negflg = 0;
                }
            }
            
            _expon = 0;

            while (_chcodes[CurChr] == 0x6b)    /* digit */
            {
                _expon = ((_expon * 10) + (CurChr - '0'));
                getnxtch ();
            }

            if (_expon >= 40)
            {
                return 0;
            }

            v2 += ((_negflg != 0) ? -_expon : _expon);
        }

        nptr[7] = -v2;                    /*L5e75*/
        nptr[0] &= 0x7f;
        *(double *)dest_val = _number;
        return DOUBLE;
    }

    /*L5e95*/
    if (((nptr)[0] != '\0') || ((nptr)[1] != '\0') ||
                                  ((nptr)[2] != '\0'))
    {
        return 0;
    }

    if ((CurChr == 'l') || (CurChr == 'L'))       /*L5eaa*/
    {
        char *e0;

        getnxtch ();
retlong2:
        e0 = &((nptr)[3]);
        *(long *)dest_val = *(long *)e0;
        return LONG;
    }

    /*L5ed5*/
    if (((nptr)[3]) || ((nptr)[4]))
    {
        goto retlong2;
    }
    else            /*L5ee6*/
    {
        /* This seems a round-about-way, but it's the first way I
         * got the code to come out like the source */
        union {
            char *cp;
            int *ip;
        } b0;

        b0.cp = (nptr)+5;
        /*dest_val->i = *(b0.ip);*/
        *(int *)dest_val = *(b0.ip);

        return INT;
    }
}
#endif

void 
do_squot ()
     /* L5f00 */
{
    getnxtch ();

    if (CurChr == '\\')
    {
        symval = dobkslsh ();
    }
    else
    {
        symval = CurChr;
        getnxtch();
    }

    if (CurChr != '\'')
    {
        reprterr ("unterminated character constant");
        return;
    }

    getnxtch ();
    return;
}

#ifndef COCO

void 
do_dquot (void)
#else

void
do_dquot ()
#endif
{
    switch (datstring)
    {
        case 0:     /* L5f36 */
        case 2:
            if (!stmpFP)
            {
                if (!(stmpFP = fopen (cstrtmp, "w+")))
                {
                    fatal ("can't open strings file");
                }
            }

            strsFP = stmpFP;
            break;
        case 1:     /* L5f5e */
            strsFP = outpth;
    }

    stringlen = 0;

    if (datstring != 1)
    {
        putc ('l', strsFP);  /* 108 = $6c */
#ifdef COCO
        putword ((symval = ++LblNum), strsFP);
#else
        /* The putword macro increments LblNum twice if this
         * is all done in one step
         */

        symval = ++LblNum;
        putword (LblNum, strsFP);
#endif
    }

    getnxtch();
    putc (115, strsFP); /* 's' = 0x73 */

    while (CurChr != '"')
    {
        /*if (CurLine == inpbuf)*/
        if (!(CurLine - inpbuf))
        {
            reprterr ("unterminated string");
            break;
        }
        else
        {
            if (CurChr == '\\')
            {
                addstrchr (dobkslsh ());
            }
            else
            {
                addstrchr (CurChr);
                getnxtch();
            }
        }
    }

    putc ('\0', strsFP);
    ++stringlen;
    getnxtch();
}

void
#ifndef COCO
addstrchr (int p1)
#else
addstrchr (p1)
    int p1;
#endif
{
    if ((p1 == 0) || (p1 == '\\'))
    {
        putc ('\\', strsFP);
    }

    putc ( p1, strsFP);
    ++stringlen;
}

void
#ifndef COCO
prnt_rzb (int valu)
#else
prnt_rzb (valu)
    int valu;
#endif
{
    prntstar ();
    fprintf (strsFP, " rzb %d\n", valu);
}

int 
#ifndef COCO
dobkslsh (void)
#else
dobkslsh ()
#endif
{
    int _lngth;
    register int _curch;

    getnxtch ();
    _curch = CurChr;
    getnxtch ();

    /* If it's a standard escape char, simply return */

    switch (_curch)     /* case @L6091 */
    {
        case 'n':       /* L607f */
            return 13;
        case 'l':       /* L6067 */
            return 10;
        case 't':       /* L606d */
            return 9;
        case 'b':       /* L6073 */
            return 8;
        case 'v':       /* L6079 */
            return 11;
        case 'r':       /* L607f */
            return 13;
        case 'f':       /* L6085 */
            return 12;
        case '\r':      /* L608b */
            return 32;
    }

    if (_curch == 'x')          /* else L6117 */
    {
        int pt;

        _curch = _lngth = 0;
        
        while ((pt = is_hex (CurChr)) && (_lngth++ < 2))
        {
            /* L60cd */ /* ????????????????? */
            /*_curch = (_curch << 4) + (pt - ((pt < 'A') ? '0' : ('A' - 10)));*/
            _curch = (_curch << 4) +
                        ((pt < 'A') ? (pt - '0') : pt - ('A' - 10));
            getnxtch ();
        }

        /*return _curch;*/
    }
    else
    {
        /*L6117*/
        if (_curch == 'd')          /* else L615f */
        {
            _curch = _lngth = 0;

            while ((_chcodes[CurChr] == 0x6b) && (_lngth++ < 3))
            {
                _curch = ((_curch * 10) + CurChr - '0');
                getnxtch ();
            }

/*            return _curch;*/
        }
        else
        {
            if (is_octal (_curch))
            {
                _curch -= '0';
                _lngth = 0;

                while ((is_octal(CurChr)) && (_lngth++ < 3))
                {
                    _curch = ((_curch << 3) + CurChr - '0');
                    getnxtch ();
                }
            }
        }
    }

    return _curch;
}

#ifndef COCO

int
is_octal (char ch)
#else

int 
is_octal (ch)
char ch;
#endif
{
    /*if ((ch <= '7') && (ch >= '0'))
    {
        return 1;
    }
    else
    {
        return 0;
    }*/
    return ((ch <= '7') && (ch >= '0'));
}

#ifndef COCO

is_hex (char ch)
#else

int 
is_hex (ch)
char ch;
#endif
{
    if ((_chcodes[ch] == 0x6b) ||
            (((ch &= 0x5f) >= 'A') && (ch <= 'F')))
    {
        return ch;
    }
    else
    {
        return 0;
    }
}
