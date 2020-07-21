/* ******************************************************************** *
 * local.c - part 8                                                     *
 * $Id: p2_08.c 18 2008-05-19 21:54:22Z dlb $::                         *
 * ******************************************************************** */

#include "pass2.h"

direct int D0023;
direct int D0025;

void
prt_fdb ()
{
    ot ("fdb ");
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
    maxpush = callflag = sp = 0;
    ol ("pshs u");

    if ( ! NoStkChk)
    {
        fprintf (OutPath, " ldd #_%d\n lbsr _stkcheck\n", D0025 = parm3);
    }

    if (DoProfile)
    {
        ot ("leax ");
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
        fprintf (OutPath, "_%d equ %d\n\n", D0025, (maxpush - callflag - 64));
    }
}

void
#ifdef COCO
prtvsctbgn (isdp)
    int isdp;
{
    if (isdp)
        ol ("vsect dp");
    else
        ol ("vsect");
}
#else
prtvsctbgn (int isdp)
{
    ol (isdp ? "vsect dp" : "vsect");
}
#endif

void
#ifdef COCO
prtendsect ()
#else
prtendsect (void)
#endif
{
    ol ("endsect");
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
        oc (_curch);
    }

    oc ('\0');
}

void
#ifdef COCO
oc (parm)
    int parm;
#else
oc (int parm)
#endif
{
    if ( ! scount)
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

        if ( scount++ < 75)
        {
            return;
        }
    
        fprintf (OutPath, "\"\n");
    }

    scount = 0;
}
