/* ****************************************************** *
 * pass1_08.c                                             *
 * ****************************************************** */

/* $Id: p1_08.c 18 2008-05-19 21:54:22Z dlb $ */

/* This file is _probably_ an exact match with original code
 * several brances, etc had to be altered, but none should matter
 */

#include <stdlib.h>

union data_tys {
        long l;
        double d;
        int i;
        char c[9];
};

#ifndef COCO
#   ifndef direct
#       define direct
#   endif
#endif

extern direct int D000b;
extern char _chcodes[];

#include "pass1.h"

/* ************************************************************ *
 * nxt_word() - Process a group of characters                   *
 *      Sets up sym and LblVal to appropriate codes            *
 *      If it's a valid Label, finds label or creates an entry  *
 *      If number, retrieves it and sets it up                  *
 *      If assignment or operator, sets up definition for it    *
 * Exit conditions:                                             *
 *      Builtin:                                                *
 *        sym = C_* type                                      *
 *        LblVal = fnccode (FT_EXTERN if SIZEOF)                 *
 *      User Defined Label:                                     *
 *        sym = C_USRLBL                                      *
 *        LblVal = ptr to LBLDEF struct for this variable        *
 *      Numeric:                                                *
 *        sym = C_* type of number                            *
 *        LblVal = value itself if size <= sizeof (int)          *
 *                else ptr to the storage of the value          *
 *      Anything else:                                          *
 *        sym = C_* type                                      *
 *        LblVal = Info regarding any additional chars.  I.E.    *
 *                whether is is "+", "++", "+=", etc            *
 * ************************************************************ */

#ifndef COCO

void 
nxt_word (void)
#else

void
nxt_word ()
#endif
{
    /* 21 bytes of static variables */

    int _ftcode;
    union data_tys _buf;
    double *_valptr;
    double my_dbl;

    skipblank();

    if (CurChr == -1)
    {
        sym = -1;
        return;
    }

    D0063 = CurLine - 1;
    D003f = fileline;

    while ((sym = _chcodes[CurChr]) == '\0')
    {
        reprterr ("bad character");
        getnxtch ();
        D0063 = CurLine;
    }

    LblVal = _chcod_2[CurChr];

    switch (sym)     /* at L5873 */
    {
        /*register union data_tys *_treept;*/
        register void *_treept;

        case 0x6a:         /*alpha - must be label */   /* L5588 */

            fget_lbl (_buf.c);     /* Read in label name from file */
            _treept = FindLbl (_buf.c);

            /* gentyp = 51 ==> "builtin" ?? */

            if ((sym = ((LBLDEF *)_treept)->gentyp) == C_BUILTIN)
            {
                /* All builtins except sizeof return unchanged */

                if ((LblVal = ((LBLDEF *)_treept)->fnccode) == FT_SIZEOF)
                {
                   sym = C_SIZEOF;
                   LblVal = FT_EXTERN;        /* 14 */
                }
            }
            else
            {
               sym = C_USRLBL;
               LblVal = (int)_treept;
            }

            break;         /* return */

        case 0x6b:                     /*digit */ /* L55c9 */
            _ftcode = str2num (1, &(my_dbl));
L55dc:
            _valptr = &(my_dbl);
            
            switch (_ftcode)
            {
                case FT_INT:    /* 1 */     /* L55e8 */
                    LblVal = *(int *)_valptr;
                    sym = C_INTSQUOT;    /* '6' */
                    break;
                case FT_LONG:  /* 8 */    /* L55ed */
                    _treept = addmem (sizeof (long));
                    *(long *)_treept = *(long *)_valptr;
                    LblVal = (int)_treept;
                    sym = C_LONG;    /* 'J' */
                    break;
                case FT_DOUBLE:    /* L5609 */
                    _treept = addmem (sizeof (double));
                    *(double *)_treept = *(double *)_valptr;
                    LblVal = (int)_treept;
                    sym = C_DOUBLE;    /* 'K' */
                    break;
                default:   /* L5625 */
                    reprterr ("constant overflow");
                    LblVal = 1;
                    sym = C_INTSQUOT;        /* '6' */
                    break;
            }

            break;

        case  0x68: /* ' (single quote)*/  /* L564e */
            do_squot ();
            sym = C_INTSQUOT;
            break;
        case  0x69: /* " (double quote) */ /* L5656 */
            do_dquot ();
            sym = C_DQUOT;
            break;
        default:   /* L5661 */
            getnxtch ();

            switch (sym)
            {
                case C_PERIOD: /* '.' */       /* L5669 */
                    if (_chcodes[CurChr] == 0x6b)  /* Digit */
                    {
                        _ftcode = str2num (6, &my_dbl);
                        goto L55dc;
                    }

                    break;

                case C_AMPERSAND:          /* L5691 */
                    switch (CurChr)
                    {
                        case '&':          /* L5698 */
                            sym = C_ANDAND;
                            getnxtch ();
                            LblVal = 5;
                            break;
                        case '=':        /* L56a5 */
                            sym = C_ANDEQ;
                            LblVal = 2;
                            getnxtch ();   /* 2008/04/15 fix &= error??? */
                            break;
                    }

                    break;
                case C_EQUAL:              /* L56bd */
                    if (CurChr == '=')
                    {
                        sym = C_EQEQ;
                        LblVal = 9;
                        getnxtch ();
                    }

                    break;
                case C_VBAR:               /* L56d0 */
                    switch (CurChr)
                    {
                        case '|':          /* L56d7 */
                            sym = C_OROR;
                            getnxtch ();
                            LblVal = 4;
                            break;
                        case '=':          /* L56e4 */
                            sym = C_OREQ;    /* +80 */
                            getnxtch ();
                            LblVal = 2;
                            break;
                    }

                    break;
                case C_EXCLAM:              /* L5701 */
                    if (CurChr == '=')
                    {
                        sym = C_NOTEQ;
                        getnxtch ();
                        LblVal = 9;
                    }
                    
                    break;
                case C_ASTERISK:             /* L5716 */
                    if (CurChr == '=')
                    {
                        sym = C_X_EQ;
                        getnxtch ();
                        LblVal = 2;
                    }
                    
                    break;
                case C_SLASH:
                case C_PERCENT:
                case C_CARET:              /* L5723 */
                    if (CurChr == '=')
                    {
                        sym += 80;
                        getnxtch ();
                        LblVal = 2;
                    }
                    
                    break;
                case C_LT:                 /* L5733 */
                    switch (CurChr)
                    {
                        case '<':          /* L573a */
                            sym = C_LSHIFT;
                            LblVal = 11;
                            getnxtch ();

                            if (CurChr == '=')
                            {
                                sym = C_LSHEQ;   /* +80 */
                                LblVal = 2;
                                getnxtch ();
                            }
                            
                            break;
                        case '=':          /* L575a */
                            sym = C_LT_EQ;
                            LblVal = 10;
                            getnxtch ();
                            break;
                    }

                    break;
                case C_GT:                  /* L5772 */
                    switch (CurChr)
                    {
                        case '>':          /* L5779 */
                            sym = C_RSHIFT;
                            LblVal = 11;
                            getnxtch ();

                            if (CurChr == '=')
                            {
                                sym = C_RSH_EQ;  /*C_RSHFT + 80*/
                                LblVal = 2;
                                getnxtch ();
                            }

                            break;
                        case '=':              /* L5799 */
                            sym = C_GT_EQ;
                            LblVal = 10;
                            getnxtch ();
                            break;
                    }

                    break;
                case C_PLUS:                   /* L57b1 */
                    switch (CurChr)
                    {
                        case '+':              /* L57b8 */
                            sym = C_PLUSPLUS;
                            LblVal = 14;
                            getnxtch ();
                            break;
                        case '=':              /* L57c2 */
                            sym = C_PLUSEQ;
                            LblVal = 2;
                            getnxtch ();
                            break;
                    }

                    break;
                case C_MINUS:                  /* L57d9 */
                    switch (CurChr)
                    {
                        case '-':              /* L57e0 */
                            sym = C_MINMINUS;
                            LblVal = 14;
                            getnxtch ();
                            break;

                        case '=':              /* L57ea */
                            sym = C_MINEQU;  /* C_MINUS + 80 */
                            LblVal = 2;
                            getnxtch ();
                            break;
                        case '>':              /* L57f4 */
                            sym = C_PTRREF;  /* "->" */
                            LblVal = 15;
                            getnxtch ();
                            break;
                    }

                    break;
            }      /* end switch (sym) for default: */

            break;
    }       /* end outer switch (sym) */
}

#ifndef COCO

void 
tblsetup (void)
#else

void
tblsetup ()
#endif
{
    register LBLDEF *regptr;

    inizFTbl ("double", 6);
    inizFTbl ("float", 5);
    inizFTbl ("typedef", 30);
    inizFTbl ("static", 15);
    inizFTbl ("sizeof", 59);
    inizFTbl ("int", 1);
    Struct_Union = 1;
    inizFTbl ("int", 1);
    inizFTbl ("float", 5);
    Struct_Union = 0;
    inizFTbl ("char", 2);
    inizFTbl ("short", 10);
    inizFTbl ("auto", 13);
    inizFTbl ("extern", 14);
    inizFTbl ("direct", 33);
    inizFTbl ("register", 16);
    inizFTbl ("goto", 29);
    inizFTbl ("return", 18);
    inizFTbl ("if", 19);
    inizFTbl ("while", 20);
    inizFTbl ("else", 21);
    inizFTbl ("switch", 22);
    inizFTbl ("case", 23);
    inizFTbl ("break", 24);
    inizFTbl ("continue", 25);
    inizFTbl ("do", 26);
    inizFTbl ("default", 27);
    inizFTbl ("for", 28);
    inizFTbl ("struct", 4);
    inizFTbl ("union", 3);
    inizFTbl ("unsigned", 7);
    inizFTbl ("long", 8);
    
    regptr = FindLbl ("errno");
    regptr->gentyp = 1;
    regptr->fnccode = 14;
    regptr->vsize = 2;

    regptr = FindLbl("lseek");
    regptr->gentyp = 56;
    regptr->fnccode = 12;
    regptr->vsize = 4;
}

/* ***************************************************************** *
 * fget_lbl () - read a label name from input stream int _dest.      *
 *      ( up to 8 chars), and set file position to end of the string *
 * ***************************************************************** */

#ifndef COCO

void
fget_lbl (register char *_dst)
#else

void 
fget_lbl (_dst)
register char *_dst;
#endif
{
    int _strln;

    _strln = 1;

    while (islblchr (CurChr) && (_strln <= 8))
    {
        *(_dst++) = CurChr;
        getnxtch ();
        ++_strln;
    }

    if (_strln == 2)
    {
        *(_dst++) = '_';
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
    return ((_chcodes[pos] == '\x6a') || (_chcodes[pos] == '\x6b'));
}

/* *********************************************** *
 * FindLbl () - Search for a label entry.          *
 *      return entry if found,  create one if none *
 *      found                                      *
 * *********************************************** */

#ifndef COCO

LBLDEF *
FindLbl ( char *fnc)
#else
LBLDEF *
FindLbl ( fnc)
char *fnc;
#endif
{
    LBLDEF **_fnclst;
    LBLDEF **_fncbase;
    int v0;

    register LBLDEF *_myfnc;

    /* The tree is divided up into two 128-byte trees
     * StrctLbls for structure/union labels, and NStrLbls for all the rest
     */

    _fncbase = (Struct_Union ? StrctLbls : NStrLbls);

    _fnclst = &(_fncbase[str_sum (fnc)]);   /* "lsl d" type thing */
    _myfnc = *(_fnclst);

    /* Search the list for a match, return entry if found */

    while (_myfnc)
    {
        if ((_myfnc->fnam)[0] == fnc[0])    /* first chr of name match? */
        {
            if (!strncmp (fnc, _myfnc->fnam, 8)) /* Check complete name */
            {
                return _myfnc;                  /* Found it... return */
            }
        }

        _myfnc = _myfnc->fnext;
    }

    if ((_myfnc = D0019) != 0)
    {
        D0019 = _myfnc->fnext;
    }
    else
    {
        _myfnc = addmem (sizeof (LBLDEF));
    }

    strncpy (_myfnc->fnam, fnc, 8);
    _myfnc->gentyp = 0;
    _myfnc->fnccode = 0;

    /* This entry will be inserted as the "first" entry in the list.
     * I. E. the base will point to this entry, this entry's ->fnext
     * will point to the previous "first"
     */

    _myfnc->fnext = *(_fnclst);
    *(_fnclst) = _myfnc;
    _myfnc->ftop = _fnclst;     /* quick trip to the top? */

    return _myfnc;
}

#ifndef COCO

void
inizFTbl (char *name, int val)
#else

void 
inizFTbl (name, val)
char *name;
int val;
#endif
{
    char _lblnam[9];
    register LBLDEF *_ftbl;

    strncpy (_lblnam, name, 8);
    _lblnam[8] = '\0';
    _ftbl = FindLbl (_lblnam);
    _ftbl->gentyp= C_BUILTIN;
    _ftbl->fnccode = val;
}

/* ***************************************** *
 * str_sum() - returns the sum of the values *
 *          of characters in a string        *
 * ***************************************** */

#ifndef COCO

unsigned int
str_sum (register char *nam)
#else

unsigned int 
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

#ifndef COCO

void *
addmem (int siz)
#else

void *
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
    return (void *)memptr;
}


/* ******************************************************** *
 * str2num() - reads in a string from the file and converts *
 *      it to the appropriate number value                  *
 * Returns: the FT_* type on success, 0 on failure          *
 * ******************************************************** */

#ifndef COCO

int
str2num (int p1, void *dest_val)
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
        return FT_DOUBLE;
    }

    /**(long *)dest_val = (int)strtol (_tmpstr, &_endptr, 0);*/

    if ((toupper (CurChr)) == 'L')
    {
        *((long **)dest_val) = malloc (sizeof (long));
        **((long **)dest_val) = strtol (_tmpstr, &_endptr, 0);
        getnxtch ();
        return FT_LONG;
    }
    else
    {
        *((int *)dest_val) = (int)strtol (_tmpstr, &_endptr, 0);
        return FT_INT;
    }
}

#else

int 
str2num (p1, dest_val)
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

    if (p1 == 6)
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
            return FT_INT;
        }

retrnlong:
        *(long *)dest_val = _my_nmbr;
        return FT_LONG;
    }

    /* The following is a modified (?) version of atof
     * We'll try to follow the original code, but when we port,
     * we'll try to use std library routines
     */

    while (_chcodes[CurChr] == 0x6b)    /* digit */      /*L5d96 */
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
        return FT_DOUBLE;
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
        return FT_LONG;
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

        return FT_INT;
    }
}
#endif

#ifndef COCO

void 
do_squot (void)
#else

void
do_squot ()
#endif
     /* L5f00 */
{
    getnxtch ();

    if (CurChr == '\\')
    {
        LblVal = dobkslsh ();
    }
    else
    {
        LblVal = CurChr;
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
    switch (D000b)
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

    D0017 = 0;

    if (D000b != 1)
    {
        putc ('l', strsFP);  /* 108 = $6c */
#ifdef COCO
        putword ((LblVal = ++LblNum), strsFP);
#else
        /* The putword macro increments LblNum twice if this
         * is all done in one step
         */

        LblVal = ++LblNum;
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
    ++D0017;
    getnxtch();
}

#ifndef COCO

void
addstrchr (int p1)
#else

void 
addstrchr (p1)
int p1;
#endif
{
    if ((p1 == 0) || (p1 == '\\'))
    {
        putc ('\\', strsFP);
    }

    putc ( p1, strsFP);
    ++D0017;
}

#ifndef COCO

void
prnt_rzb (int valu)
#else

void 
prnt_rzb (valu)
int valu;
#endif
{
    prntstar ();
    fprintf (strsFP, " rzb %d\n", valu);
}

#ifndef COCO

int 
dobkslsh (void)
#else

int
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
