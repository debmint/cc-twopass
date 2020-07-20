/* **************************************************************** *
 * p2_07.c                                                          *
 * $Id: p2_07.c 18 2008-05-19 21:54:22Z dlb $::                                                           *
 * **************************************************************** */


#include "pass2.h"

#ifdef COCO
extern long _flacc;     /* Hope we can fake it here */
#else
long _flacc;
#endif

/* ************************************************************ *
 * L4896 () - Copies a Long definition to the lng_something     *
 *            structure                                         *
 * ************************************************************ */

void
#ifdef COCO
L4823 (strng)
    char *strng;
#else
L4823 (char *strng)
#endif
{
    comperr (D0282, strng);
}

void
#ifdef COCO
outofmemory ()
#else
outofmemory (void)
#endif
{
    L487f (D0282, "out of memory");
    err_exit ();
}

void
#ifdef COCO
comperr (cref, strng)
    expnode *cref;
    char *strng;
#else
comperr (expnode *cref, char *strng)
#endif
{
    /* 50 bytes static data */
    char buf[50];

    strcpy (buf, "compiler error - ");
    strcat (buf, strng);
    L487f (cref, buf);
}

void
#ifdef COCO
L487f (cref, parm2)
    register expnode *cref;
    char *parm2;
#else
L487f ( expnode *cref, char *parm2)
#endif
{
    showerr (cref->pnt, parm2, cref->lno);
}

void
#ifdef COCO
L4896 (parm1, lng)
    int parm1; long lng;
#else
L4896 (int parm1, long lng)
#endif
{
    register struct lng_something *lngptr;

    if ((D02da = ((D02da + 1) % 10)) == D02dc)    /* else LL48c5 */
    {
        D02dc = (D02dc + 1) % 10;
    }

    lngptr = &(D029e[D02da]);
    lngptr->smptr = parm1;
    lngptr->sm_val = lng;
}

/* ******************************************************** *
 * lng2_flacc () - Moves long value stored in long struct   *
 *              to _flacc.                                  *
 * Passed:  The desired smptr                               *
 * Returns: pointer to _flacc (original didn't, _lmove      *
 *          exits with x pointing to dest, but I think this *
 *          is the only way to do things without resorting  *
 *          to asm code.                                    *)
 * Return condition: (long)_flacc contains the value        *
 *      where the smptr is found, or -1 if no match         *
 * ******************************************************** */

#ifdef COCO
long *
lng2_flacc (parm1)
    int parm1;
#else
/* May need to modify for non-COCO... */
long *
lng2_flacc (int parm1)
#endif
{
    int _ofst;
    register struct lng_something *lngptr;

    _ofst = D02da;

    while (_ofst != D02dc)
    {
        if ((lngptr = &(D029e[_ofst]))->smptr == parm1)
        {
            _flacc = lngptr->sm_val;
            return &_flacc;
        }

        if (--_ofst < 0)
        {
            _ofst = 9;
        }
    }

    _flacc = -1;
    return &_flacc;
}

#ifdef COCO
showerr (linpos, errstr, fpos)
    int linpos;
    char *errstr;
    long *fpos;
#else
showerr (int linpos, char *errstr, long *fpos)
#endif
{
    long pos;
    char c;

    printf ("%s: ", SrcFilNam);
    /* What's the 3rd parameter?  Probably gcc will give warning */
    printf ("line %d  ", fpos, linpos);
    printf ("****  %s  ****\n", errstr);
    
    if ((!(D02de) && !(D02de = fopen (D0280, "r"))) || 
            ((pos = *lng2_flacc (fpos)) == -1))
    {
            goto L4a30;
    }

#ifdef COCO
    fseek (D02de, pos,0);
#else
    fseek (D02de, pos, SEEK_SET);
#endif

    do
    {
        putc ((c = getc (D02de)), stdout);       /* L49cf */
    } while (c != '\n');

    while ((linpos--) > 0)
    {
        putc (' ', stdout);         /* L49f2 */
    }

    putc ('^', stdout);
    putc ('\n', stdout);

L4a30:
    if (++errcount > 30)
    {
        fflush (stdout);
        fprintf (stderr, "too many errors - ABORT\n");
        exit (1);
    }
}

void
#ifdef COCO
L4a69 (cref)
    register expnode *cref;
#else
L4a69 (expnode *cref)
#endif
{
    if (cref)
    {
        L4a69 (cref->left);
        L4a69 (cref->right);
        L4a8a (cref);
    }
}

void
#ifdef COCO
L4a8a (cref)
    register expnode *cref;
#else
L4a8a (expnode *cref)
#endif
{
    if (cref)
    {
        switch (cref->op)
        {
            case NAME:     /* L4a96 */
                L3203 (cref->val.num, 13);
                break;
            case FCONST:     /* L4a9b */
                L3203 (cref->val.num, 8);
                break;
            case LCONST:       /* L4aa0 */
                L3203 (cref->val.num, 4);
                break;
        }

        L3203 (cref, 22);
    }
}

void
#ifdef COCO
L4acd (parm1, parm2)
    expnode *parm1;
    expnode *parm2;
#else
L4acd (expnode *parm1, expnode *parm2)
#endif
{
    ncpystr (parm1, parm2, 22);
}

#ifdef COCO
int
p051_notused (parm1, parm2)
    int parm1; int parm2;
{
    return (((parm1 >> 2) & 0xfff0) + (parm1 & 0x0f));
}
#endif

int
#ifdef COCO
L4af7 (parm1)
    register int parm1;
#else
L4af7 (int parm1)
#endif
{
    return ((parm1 >= 76) && (parm1 <= 99));   /* between 'L' and 'c' */
}

/* ************************************************************ *
 * ncpystr () - Identical to strncpy except src and dest        *
 *              are reversed                                    *
 * ************************************************************ */

void
#ifdef COCO
ncpystr (src, dest, count)
    register char *src;
    char *dest;
    int count;
#else
ncpystr (char *src, char *dest, int count)
#endif
{
    while (count--)
    {
        *(dest++) = *(src++);
    }
}
