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
 * pushdown () - Copies LBLDEF * to G18Current and nulls out     *
 *            everything in the original LBLDEF (passed as the      *
 *            parameter) - except for label name                    *
 * **************************************************************** */

/* I believe we are addressing a different 18-byte structure here */

void
#ifndef COCO
pushdown (register symnode *sptr)
#else
pushdown (sptr)
    register symnode *sptr;
#endif
{
    symnode *tmpdef;
    symnode *nptr;
    int __count;

    if (nptr = G18Current)
    {
        G18Current = nptr->snext;
    }
    else
    {
        /* This may be a one-shot deal.. once G18Current has been established,
         * it may endure for the duration of the program
         */

        nptr = (symnode *)addmem (DOWNSIZE);
    }

#ifdef COCO
    mem_cp ((tmpdef = sptr), nptr, DOWNSIZE);
    __count = (sizeof (struct g18))/(sizeof (int));

    while (__count--)
    {
        /* orig code does clra clrb std ,u++ */
        /* this increments u, then stores d -2,u */
        *(((int *)sptr)++) = 0;
    }
#else
    memmove (nptr, (tmpdef = sptr), DOWNSIZE);
    memset (sptr, 0, DOWNSIZE);
#endif

    tmpdef->downptr = nptr;
}

/* ********************************************************** *
 * pullup () - This function _seems_ to move the LBLDEF     *
 *          passed as a parameter to the top of the tree..??  *
 * Exit Conditions:                                           *
 *      deftop->g18Prev points to G18Current contents         *
 * ********************************************************** */


void
#ifndef COCO
pullup (register symnode *sptr)
#else
pullup (sptr)
register symnode *sptr;
#endif
{
    symnode *nptr = sptr->downptr;

    mem_cp (nptr, sptr, DOWNSIZE);
    nptr->snext = G18Current;
    G18Current = nptr;
}

void
#ifndef COCO
mem_cp (register void *_src, void *_dest, int siz)
#else
mem_cp (_src, _dest, siz)
    register char *_src;
    char *_dest;
    int siz;
#endif
{
    while (siz--)
    {
        *(char *)(_dest++) = *(char *)(_src++);
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
fatal (char *p1)
#else
fatal (p1)
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
    doerr (symptr - inpbuf, _str, symline);
}

void
#ifndef COCO
comperr (expnode *p1, char *_errmsg)
#else
comperr (p1, _errmsg)
    register expnode *p1;
    char *_errmsg;
#endif
{
    /* 50 bytes storage */
    char newstr[50];

    strcpy (newstr, "compiler error - ");
    strcat (newstr, _errmsg);
    terror (p1, newstr);
}

void
#ifndef COCO
terror (register expnode *p1, char *_errmsg)
#else
terror (p1, _errmsg)
    register expnode *p1;
    char *_errmsg;
#endif
{
    doerr ((int)(p1->pnt) - (int)inpbuf, _errmsg, p1->lno);
}

void
#ifndef COCO
doerr (register int _linpos, char *txt, int _line)
#else
doerr (_linpos, txt, _line)
    register int _linpos;
    char *txt;
    int _line;
#endif
{
    prnt_filname ();
    displerr ("line %d  ", (void *)_line);
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

    if ((++ErrCount) > 30)
    {
        fflush (stderr);
        e_putlin ("too many errors - ABORT");
        quitcc();
    }

}

void
#ifndef COCO
displerr (char *pmpt, void *val)
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
reltree (register expnode *tree)
#else
reltree (tree)
    register expnode *tree;
#endif
{
    if (tree)
    {
        reltree (tree->left);
        reltree (tree->right);
        release (tree);
    }
}

/* **************************************************** *
 * release () - Makes the CMDREF passed the current   *
 *      cmd.  Moves the CMDREF in freenode to its Prev     *
 *      and stores this CMDREF into freenode               *
 * **************************************************** */

void
#ifndef COCO
release (register expnode *p1)
#else
release (p1)
    register expnode *p1;
#endif
{
    if (p1)
    {
        p1->left = freenode;
        freenode = p1;
    }
}

void
#ifndef COCO
nodecopy (char *p1, char *p2)
#else
nodecopy (p1, p2)
    char *p1;
    char *p2;
#endif
{
    mem_cp (p1, p2, NODESIZE);
}

/* *************************************************** *
 * istype () - Returns TRUE if the definition is   *
 *          a variable and not a type definition.      *
 * *************************************************** */

int 
#ifndef COCO
istype (void)
#else
istype ()
#endif
{
    if (sym == C_BUILTIN)    /* else L0428 */
    {
        switch (symval)
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
        if (sym == C_USRLBL)        /* else _67 (L04c8) */
        {
            if (((symnode *)symval)->storage == FT_TYPEDEF)
            {
                return 1;
            }
        }
    }

    return 0;
}

/* ********************************************************** *
 * issclass () - Returns true if a the word is a       *
 *      storage class specification                           *
 * ********************************************************** */

int 
issclass()
{
    if (sym == C_BUILTIN)
    {
        switch (symval)
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
decref (int p1)
#else
decref (p1)
int p1;
#endif
{
    return (((p1 >> 2) & 0xfff0) + (p1 & 0x0f));
}

int
#ifndef COCO
incref (int p1)
#else
incref (p1)
int p1;
#endif
{
    return ((((p1 & 0xfff0) << 2) + 0x10) + (p1 & 0x0f));
}

int 
#ifndef COCO
isbin (int p1)
#else
isbin (p1)
register int p1;
#endif
{
    if ((p1 >= 76) && (p1 <= 99))
    {
        return 1;
    }
        
    return 0;
}

dimnode *
#ifndef COCO
dimwalk (register dimnode *dptr)
#else
dimwalk (dptr)
    register dimnode *dptr;
#endif
{
    return dptr ? dptr->dptr : 0;
}

/* ************************************************ *
 * need () - if the current character in sym   *
 *      is the parameter, process the input stream  *
 * Returns: 0 if char matches                       *
 *          1 if match fails and sends error msg    *
 * ************************************************ */

int
#ifndef COCO
need (int needed)
#else
need (needed)
int needed;
#endif
{
    register int _chr;

    if (sym == needed)
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
 * junk () - Keep reading "words" from input stream   *
 *      until either a comma or RBracket is found           *
 * ******************************************************** */

void 
#ifndef COCO
junk (void)
#else
junk ()
#endif
{
    while ((sym != C_SEMICOLON) && (sym != C_RBRKET) && (sym != -1))
    {
        nxt_word();
    }
}
