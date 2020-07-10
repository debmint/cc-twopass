/* ******************************************************************** *
 * pass1_01.c - the first part of c.pass1 source                        *
 * $Id: p1_01.c 18 2008-05-19 21:54:22Z dlb $                           *
 * ******************************************************************** */

/* This file is an exact match to the original code
 * except for certain jumps to returns
 */

#ifndef COCO
#   define direct
#endif

char xexpcted[] = "x expected";

/* TenMults could be moved to printf.c, but it would rearrange the order of
 * the variables - we will probably not even use it with the cross compiler */

int TenMults[] = {10000, 1000, 100, 10};

char _chcodes[] =
{
   0x00,0x00,0x00,0x00,0x00,0x00,
   0x00,0x00,0x00,0x00,0x00,0x00,
   0x00,0x00,0x00,0x00,0x00,0x00,
   0x00,0x00,0x00,0x00,0x00,0x00,
   0x00,0x00,0x00,0x00,0x00,0x00,
   0x00,0x00,0x6d,0x40,0x69,0x00,
   0x00,0x54,0x41,0x68,0x2d,0x2e,
   0x42,0x50,0x30,0x43,0x45,0x53,
   0x6b,0x6b,0x6b,0x6b,0x6b,0x6b,
   0x6b,0x6b,0x6b,0x6b,0x2f,0x28,
   0x5d,0x78,0x5f,0x64,0x00,0x6a,
   0x6a,0x6a,0x6a,0x6a,0x6a,0x6a,
   0x6a,0x6a,0x6a,0x6a,0x6a,0x6a,
   0x6a,0x6a,0x6a,0x6a,0x6a,0x6a,
   0x6a,0x6a,0x6a,0x6a,0x6a,0x6a,
   0x6a,0x2b,0x66,0x2c,0x59,0x6a,
   0x00,0x6a,0x6a,0x6a,0x6a,0x6a,
   0x6a,0x6a,0x6a,0x6a,0x6a,0x6a,
   0x6a,0x6a,0x6a,0x6a,0x6a,0x6a,
   0x6a,0x6a,0x6a,0x6a,0x6a,0x6a,
   0x6a,0x6a,0x6a,0x29,0x58,0x2a,
   0x44,0x00
};

/*direct char *D0001 = _chcodes;*/
direct int *D0001 = &(TenMults[sizeof (TenMults)/sizeof (TenMults[0])]);

#include "pass1.h"

#define PARTLBL(v) sizeof (LBLDEF) - sizeof (v->cr_Nxt)


/* **************************************************************** *
 * null_lbldef () - Copies LBLDEF * to G18Current and nulls out     *
 *            everything in the original LBLDEF (passed as the      *
 *            parameter) - except for label name                    *
 * **************************************************************** */

/* I believe we are addressing a different 18-byte structure here */

void
#ifndef COCO
null_lbldef (register LBLDEF *srcdef)
#else
null_lbldef (srcdef)
register LBLDEF *srcdef;
#endif
{
    struct g18 *_olddef;
    struct g18 *_destdef;
    int __count;

    if (_destdef = G18Current)
    {
        G18Current = _destdef->g18Prev;
    }
    else
    {
        /* This may be a one-shot deal.. once G18Current has been established,
         * it may endure for the duration of the program
         */

        _destdef = addmem (sizeof (struct g18));
    }

#ifdef COCO
    mem_cp ((_olddef = srcdef), _destdef, sizeof (struct g18));
    __count = (sizeof (struct g18))/(sizeof (int));

    while (__count--)
    {
        /* orig code does clra clrb std ,u++ */
        /* this increments u, then stores d -2,u */
        *(((int *)srcdef)++) = 0;
    }
#else
    memmove (_destdef, (_olddef = srcdef), sizeof (struct g18));
    memset (srcdef, 0, sizeof (struct g18));
#endif

    _olddef->g18_14 = _destdef;
}

/* ********************************************************** *
 * fill_g18 () - This function _seems_ to move the LBLDEF     *
 *          passed as a parameter to the top of the tree..??  *
 * Exit Conditions:                                           *
 *      deftop->g18Prev points to G18Current contents         *
 * ********************************************************** */


void
#ifndef COCO
fill_g18 (register LBLDEF *dstdef)
#else
fill_g18 (dstdef)
register LBLDEF *dstdef;
#endif
{
    struct g18 *__def_top = dstdef->ftop;

    mem_cp (__def_top, dstdef, sizeof (struct g18));
    __def_top->g18Prev = G18Current;
    G18Current = __def_top;
}

void
#ifndef COCO
mem_cp (register char *_src, char *_dest, int siz)
#else
mem_cp (_src, _dest, siz)
    register char *_src;
    char *_dest;
    int siz;
#endif
{
    while (siz--)
    {
        *(_dest++) = *(_src++);
    }
}

void 
#ifndef COCO
prnt_filname (void)
#else
prnt_filname ()
#endif
{
    displerr ("%s : ", CurFilNam);
}

int 
#ifndef COCO
err_quit (char *p1)
#else
err_quit (p1)
char *p1;
#endif
{
    reprterr (p1);
    fflush (stderr);
    quitcc();
}


void 
#ifndef COCO
multdef (void)
#else
multdef ()
#endif
{
    reprterr ("multiple definition");
}

void
#ifndef COCO
reprterr (char *_str)
#else
reprterr (_str)
char *_str;
#endif
{
    showline (D0063 - inpbuf, _str, D003f);
}

void
#ifndef COCO
comperr (int *p1, char *_errmsg)
#else
comperr (p1, _errmsg)
int *p1;
char *_errmsg;
#endif
{
    /* 50 bytes storage */
    char _str[50];

    strcpy (_str, "compiler error - ");
    strcat (_str, _errmsg);
    err_lin (p1, _str);
}

void
#ifndef COCO
err_lin (register CMDREF *p1, char *_errmsg)
#else
    err_lin (p1, _errmsg)
    register CMDREF *p1;
    char *_errmsg;
#endif
{
    showline ((p1->_lpos) - (int)inpbuf, _errmsg, p1->_cline);
}

void
#ifndef COCO
showline (register int _linpos, char *txt, int _line)
#else
    showline (_linpos, txt, _line)
    register int _linpos;
    char *txt;
    int _line;
#endif
{
    prnt_filname ();
    displerr ("line %d  ", _line);
    displerr ("****  %s  ****\n", txt);

    if (_line == fileline)      /* else L02ec */
    {
        e_putlin (inpbuf);
        goto L0303;
    }
    else
    {
        if ((fileline - 1) == _line)    /* else _20 (L0323) */
        {
            e_putlin (prevlin);
L0303:
            while (_linpos > 0)     /* Space over to position in line */
            {
                e_putc (' ');
                --_linpos;
            }

            e_putlin ("^");
        }
    }

    /*++ErrCount;*/     /* _20 */   /* L0323 */

    if ((++ErrCount) > 30)
    {
        fflush (stderr);
        e_putlin ("too many errors - ABORT");
        quitcc();
    }

}

void
#ifndef COCO
displerr (char *pmpt, char *val)
#else
displerr (pmpt, val, p3)
    char *pmpt;
    char *val;
#endif
{

#ifndef COCO
    fprintf (stderr, pmpt, val);
#else
    fprintf (stderr, pmpt, val, p3);
#endif
}

void
#ifndef COCO
e_putlin (char *str)
#else
e_putlin (str)
char *str;
#endif
{
    fputs (str, stderr);
    e_putc ('\n');
}

void
#ifndef COCO
e_putc (char ch)
#else
e_putc (ch)
char ch;
#endif
{
    putc (ch, stderr);
}

/* NEED TO FIND OUT ABOUT THIS */

void
#ifndef COCO
L0393 (register CMDREF *p1)
#else
L0393 (p1)
    register CMDREF *p1;
#endif
{
    if (p1)
    {
        L0393 (p1->cr_Left);
        L0393 (p1->cr_Right);
        mak_curnt (p1);
    }
}

/* **************************************************** *
 * mak_curnt () - Makes the CMDREF passed the current   *
 *      cmd.  Moves the CMDREF in D002d to its Prev     *
 *      and stores this CMDREF into D002d               *
 * **************************************************** */

void
#ifndef COCO
mak_curnt (register CMDREF *p1)
#else
mak_curnt (p1)
    register CMDREF *p1;
#endif
{
    if (p1)
    {
        p1->cr_Left = D002d;
        D002d = p1;
    }
}

void
#ifndef COCO
CmdrefCpy (CMDREF *p1, int p2)
#else
CmdrefCpy (p1, p2)
    CMDREF *p1;
    CMDREF *p2;
#endif
{
    mem_cp (p1, p2, sizeof (CMDREF));
}

/* *************************************************** *
 * isvariable () - Returns TRUE if the definition is   *
 *          a variable and not a type definition.      *
 * *************************************************** */

int 
#ifndef COCO
isvariable (void)
#else
isvariable ()
#endif
{
    if (D005f == C_BUILTIN)    /* else L0428 */
    {
        switch (LblVal)
        {
            case FT_INT:
            case FT_CHAR:
            case FT_UNSIGNED:
            case FT_SHORT:
            case FT_LONG:
            case FT_STRUCT:
            case FT_UNION:
            case FT_DOUBLE:
            case FT_FLOAT:
                return 1;
            default:
                return 0;
        }
    }
    else        /* L0428 */
    {
        if (D005f == C_USRLBL)        /* else _67 (L04c8) */
        {
            if (((LBLDEF *)LblVal)->fnccode == FT_TYPEDEF)
            {
                return 1;
            }
        }
    }

    return 0;
}

/* ********************************************************** *
 * is_sc_specifier () - Returns true if a the word is a       *
 *      storage class specification                           *
 * ********************************************************** */

int 
#ifndef COCO
is_sc_specifier (void)
#else
is_sc_specifier()
#endif
{
    if (D005f == C_BUILTIN)
    {
        switch (LblVal)
        {
            case FT_EXTERN:
            case FT_AUTO:
            case FT_TYPEDEF:
            case FT_REGISTER:
            case FT_STATIC:
            case FT_DIRECT:
                return 1;
        }
    }

    return 0;
}

int
#ifndef COCO
MSBrshft2 (int p1)
#else
MSBrshft2 (p1)
int p1;
#endif
{
    return (((p1 >> 2) & 0xfff0) + (p1 & 0x0f));
}

int
#ifndef COCO
incptrdpth (int p1)
#else
incptrdpth (p1)
int p1;
#endif
{
    return ((((p1 & 0xfff0) << 2) + 0x10) + (p1 & 0x0f));
}

int 
#ifndef COCO
L049b (register int p1)
#else
L049b (p1)
register int p1;
#endif
{
    if ((p1 >= 76) && (p1 <= 99))   /* 'L'... 'c' */
    {
        return 1;
    }
        
    return 0;
}

int
#ifndef COCO
L04b0 (register int *p1)
#else
L04b0 (p1)
    register int *p1;
#endif
{
    if (p1)
    {
        return p1[1];
    }
        
    return 0;
}

/* ************************************************ *
 * lookfor () - if the current character in D005f   *
 *      is the parameter, process the input stream  *
 * Returns: 0 if char matches                       *
 *          1 if match fails and sends error msg    *
 * ************************************************ */

int
#ifndef COCO
lookfor (int needed)
#else
lookfor (needed)
int needed;
#endif
{
    register int _chr;

    if (D005f == needed)
    {
        nxt_word ();
        return 0;
    }
    else
    {
        _chr = 0;

        /* Scan _chcodes for ascii character to report */

        while (_chr < 128)
        {
            if (_chcodes[_chr] == needed)
            {
                break;
            }

            ++_chr;
        }

        xexpcted[0] = _chr;
        reprterr (xexpcted);
    }

    return 1;
}

/* ******************************************************** *
 * cmma_rbrkt () - Keep reading "words" from input stream   *
 *      until either a comma or RBracket is found           *
 * ******************************************************** */

void 
#ifndef COCO
cmma_rbrkt (void)
#else
cmma_rbrkt ()
#endif
{
    while ((D005f != C_SEMICOLON) && (D005f != C_RBRKET) && (D005f != -1))
    {
        nxt_word();
    }
}
