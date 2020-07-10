/* ******************************************************************** *
 * p2_08.c                                                              *
 * $Id: p2_08.c 18 2008-05-19 21:54:22Z dlb $::                                                               *
 * ******************************************************************** */

#include "pass2.h"

direct int D0023;
direct int D0025;
void
#ifdef COCO
prt_fdb ()
#else
prt_fdb (void)
#endif
{
    prt_bgnfld ("fdb ");
}

void
#ifdef COCO
prt_funcbegin (title, funcnam, parm3, parm4)
    register char *title;
    char *funcnam;
    int parm3;
    int parm4;
#else
prt_funcbegin (char *title, char *funcnam, int parm3, int parm4)
#endif
{
    fprintf (OutPath, " ttl %.8s\n", title);
    prt_label (title, funcnam);
    D0017 = D000f = D000d = 0;
    L43d1 ("pshs u");

    if ( ! NoStkChk)
    {
        fprintf (OutPath, " ldd #_%d\n lbsr _stkcheck\n", D0025 = parm3);
    }

    if (DoProfile)
    {
        prt_bgnfld ("leax ");
        prt_loclbl (parm4);
        prnt_strng (",pcr\n pshs x\n leax ");
        prt_lblnam (title);
        prnt_strng (",pcr\n pshs x\n lbsr _prof\n leas 4,s\n");
    }
}

void
#ifdef COCO
prtstkreq ()
#else
prtstkreq (void)
#endif
{
    if ( ! NoStkChk)
    {
        fprintf (OutPath, "_%d equ %d\n\n", D0025, (D0017 - D000f - 64));
    }
}

void
#ifdef COCO
prtvsctbgn (isdp)
    int isdp;
{
    if (isdp)
        L43d1 ("vsect dp");
    else
        L43d1 ("vsect");
}
#else
prtvsctbgn (int isdp)
{
    L43d1 (isdp ? "vsect dp" : "vsect");
}
#endif

void
#ifdef COCO
prtendsect ()
#else
prtendsect (void)
#endif
{
    L43d1 ("endsect");
}

void
#ifdef COCO
L4c61 ()
#else
L4c61 (void)
#endif
{
    int _curch;

    prt_loclbl (getword (InPath));

    while (_curch = getc (InPath))
    {
        L4c92 (_curch);
    }

    L4c92 ('\0');
}

void
#ifdef COCO
L4c92 (parm)
    int parm;
#else
L4c92 (int parm)
#endif
{
    if ( ! D02e0)
    {
        fprintf (OutPath,  " fcc \"");
    }

    if ((parm < ' ') || (parm == '"'))
    {
        fprintf (OutPath, "\"\n fcb $%x\n", parm);
    }
    else
    {
        putc (parm, OutPath);

        if ( D02e0++ < 75)
        {
            return;
        }
    
        fprintf (OutPath, "\"\n");
    }

    D02e0 = 0;
}
