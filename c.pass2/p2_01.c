/* ************************************************************************ *
 * p2_01.c                                                                  *
 * $Id: p2_01.c 18 2008-05-19 21:54:22Z dlb $::                                                                   *
 * ************************************************************************ */

#define MAIN
#include "pass2.h"

extern direct int D0023;
#ifdef COCO
expnode *L0787 ();
#endif

int
#ifdef COCO
main (argc, argv)
    int argc;
    char **argv;
#else
main (int argc, char **argv)
#endif
{
    /* 36 bytes static variables */
    int var34;
    int var32;
    int var30;
    int var28;
    int _curntchr;
    int var24;
    long var20;

    char var0[20];

    register char *argp;

    while (--argc)          /* L028e */
    {
        if (*(argp = *(++argv)) == '-')      /* L018b */     /* else L023a */
        {
            while ((*(++argp)) != '\0')     /* L0230 */
            {
                switch (*argp)
                {/* L01a0 */
                    case 's':           /* L01a8 */
                        NoStkChk = 1;
                        break;
                    case 'n':           /* L01b0 */
                        D0015 = 1;
                        openoutpth ("/dev/null");
                        break;
                    case 'o':           /* L01c3 */
                        if (*(++argp) == '=')
                        {
                            openoutpth (++argp);
                            goto L028b;
                        }

                        fprintf (stderr, "bad argument: %s", --argp);
                        err_exit ();
                    case 'p':           /* L01f2 */
                        DoProfile = 1;
                        break;
                    default:           /* L01f9 */
                        fprintf (stderr, "bad option flag: +%c\n", *argp);
                        err_exit ();
                        break;
                }
            }       /* end "while (*argp)" */
        }           /* end "if (*argp == '-') */
        else
        {
            if (InPath)      /* L023a */ /* else L025e */
            {
                if (D0280)
                {
                    fprintf (stderr, "too many files");
                    err_exit ();
                }

                D0280 = argp;   /* L0258 */     /* go to L028e */
            }
            else
            {
                if (!(InPath = fopen (argp, "r")))
                {
                    fprintf (stderr, "can't open %s\n", argp);
                    err_exit ();
                }

                InFileName = argp;
            }
        }       /* end filename processing */
L028b:
        if (1) {}   /* To allow label at end of block? */
    }       /* end "while (--argc)" */

    if (!OutPath)
    {
        OutPath = stdout;
    }

    if (!InPath)
    {
        InPath = stdin;
    }

    if (!D0280)
    {
        D0280 = "";
    }

    while ((_curntchr = getc (InPath)) != -1)   /* at L076e */
    {
        switch (_curntchr)          /* L02c0 */
        {
            case '*':          /* L02c6 */
                do {
                    if ((_curntchr = getc (InPath)) == -1)
                    {
                        break;
                    }

                    putc (_curntchr, OutPath);
                } while (_curntchr != '\n');
                
                break;
            case 'O':          /* L02f2 */
                D0007 = getword (InPath);
                /*var20 = (((long)(getc (InPath) & 0xff)) << 16) +
                                    (getword (InPath));*/
                var20 = (((long)(getc (InPath) & 0xff)) << 16);
                var20 += (getword (InPath));
                L4896 (D0007, var20);
                break;
            case 'T':          /* see prt_4c68 in p1_07.c */    /* L0350 */
                var34 = getword (InPath);
                D000b = getword (InPath);   /* LblNum */
                D000d = getword (InPath);

                if (D0017 > D000d)
                {
                    D0017 = D000d;
                }

                switch (var34)
                {       /* L03d2 = break */
                    case 2:            /* L0382 */
                        var30 = getword (InPath);
                        var32 = getword (InPath);
                        var28 = getc (InPath);
                        break;
                    case 5:            /* L03a8 */
                        D0023 = getword (InPath);
                        break;
                    case 18:           /* L03b5 */
                        var24 = getword (InPath);
                        break;
                }

                D0282 = L0787 ();

                switch (var34)
                {       /* L048d = break */
                    case 2:            /* L03df */
                        L1f13 (D0282, var30, var32, var28);
                        break;
                    case 18:           /* L03fc */
                        L0a16 (D0282, var24);
                        break;
                    case 4:            /* L040f */
                        D0282 = L0d04 (D0282);
                        break;
                    case 1:            /* L0421 */
                        L0bf7 (D0282);
                        break;
                    case 5:            /* L042f */
                        prt_fdb ();
                        L40d0 (119, D0282, 0);
                        L43dc ();
                        D0023 = 0;
                        break;
                    default:
                        fprintf (stderr, "bad action code: %d\n", var34);
                        err_exit ();
                        break;
                }

                L4a69 (D0282);      /* L048d */
                break;

            case 'l':          /* L0499 */
                L4414 (getword (InPath));
                break;
            case 'v':          /* L04a8 */
            case 'd':          /* L04a8 */
                prtvsctbgn (_curntchr == 'd');
                exit (0);
                break;
            case 'e':          /* L04bf */
                prtendsect ();
                break;
            case 's':          /* L04ed */
                while (_curntchr = getc (InPath))
                {
                    if (_curntchr == -1)
                    {
                        break;
                    }

                    if (_curntchr == '\\')
                    {
                        _curntchr = getc (InPath);
                    }

                    L4c92 (_curntchr);
                }

                L4c92 (0);
                break;
            case 'M':          /* L0504 */
                psh_stk (getword (InPath));
                break;
            case 'r':          /* L0515 */
                gen (18, 0, 0 NUL1);
                break;
            case 'J':          /* L0523 */
                
                gen (125, getword (InPath), (var24 = getword (InPath)) NUL1);
                break;
            case 'G':          /* L053f */
                gen (29, getword (InPath), 0 NUL1);
                break;
            case 'j':          /* L0551 */
                gen (124, getword (InPath), 0 NUL1);
                break;
            case 'D':          /* L0563 */
                gen (9, getword (InPath), (var24 = getword (InPath)) NUL1);
                break;
            case 'Y':          /* L0587 */
                gen (118, getword (InPath) NUL2);
                break;
            case 'U':          /* L0595 */
                gen ( 111, getword (InPath) NUL2);
                break;
            case 'S':          /* L05ab */
                var24 = getc (InPath);

                if (!NoStkChk)
                {
                    D000b = getword (InPath);
                }

                argp = var0;

                while ((_curntchr = getc (InPath)) != '\0')
                {
                    *(argp++) = _curntchr;
                }

                *argp = '\0';

                if (DoProfile)
                {
                    _curntchr = getword (InPath);
                }
                
                prt_funcbegin (var0, var24, D000b, _curntchr);
                break;
            case 'E':          /* L060b */
                prtstkreq ();
                break;
            case 'f':          /* L0611 */
                {
                    double _fdbl;
                    int _fval;

                    _fval = getword (InPath);
                    fread (&(_fdbl), DOUBLESIZE, 1, InPath);
                    L095c (&(_fdbl));

                    if (_fval == DOUBLE)
                    {
                        L3dd0 (&_fdbl, DOUBLESIZE/2);
                    }
                    else
                    {
                        float _myflot;

                        _myflot = _fdbl;
                        L3dd0 (&_myflot, FLOATSIZE/2);
                    }

                    break;
                }

            case 'p':          /* L0679 */
                L4c61 ();
                break;
            case 'F':          /* L067f */
                argp = SrcFilNam;

                while ((_curntchr = getc (InPath)) != '\n')
                {
                    if (_curntchr == -1)
                    {
                        break;
                    }

                    /* Store character if not overflow, else
                     * read and discard
                     */

                    if ( argp != &(SrcFilNam[29]))
                    {
                        *(argp++) = _curntchr;
                    }
                }

                *argp = '\0';
                break;
            case '\n':         /* L076e */
                break;
            default:           /* L06b7 */
                fprintf (stderr, "bad code in intermediate file: %02x\n",
                                  _curntchr);
                err_exit ();
                break;
        }   /* end switch type */
    }       /* end while <read input> */
}           /* end main () */

expnode *
#ifdef COCO
L0787 ()
#else
L0787 (void)
#endif
{
    /* 10 bytes static vars */

    struct nwref *_nwrf;
    int _cmdty;
    char *_lblnamptr;
    long *_mylong;
    double *_mydbl;

    register expnode *cref;

    _cmdty = getc (InPath);

    if (!(cref = getmem (sizeof (expnode))))
    {
        outofmemory ();
    }

    cref->type = getword (InPath);       /* L07af */
    cref->size = getword (InPath);
    cref->op = getword (InPath);
    cref->lno = getword (InPath);
    cref->pnt = getc (InPath);
    cref->sux = getc (InPath);
    cref->modifier = getword (InPath);

    switch (cref->op)
    {
        case NAME:     /* L0805 */
            /* Create a 13-byte struct ? */
            cref->val.num = _nwrf = getmem (sizeof (struct nwref));

            if ( _nwrf == 0)
            {
                outofmemory ();
            }

            _nwrf->nw02 = getc (InPath);        /* L081a */
            _nwrf->ftyp = getc (InPath);

            switch (_nwrf->ftyp)
            {
                case EXTERN:    /* L0838 */
                case EXTDEF:     /* L0838 */
                case DIRECT:    /* L0838 */
                case EXTERND:    /* L0838 */
                    _lblnamptr = _nwrf->rfdat.st;
                    
                    while (*(_lblnamptr++) = getc (InPath));
                    *_lblnamptr = '\0';
                    break;
                default:           /* L085a */
                    _nwrf->rfdat.wrd = getword (InPath);
                    break;
            }

            break;
        case LCONST:       /* L0886 */
            if ( ! (_mylong = getmem (LONGSIZE)))
            {
                outofmemory ();
            }

            fread (_mylong, LONGSIZE, 1, InPath);
            cref->val.num = _mylong;
            break;
        case FCONST:     /* L08b2 */
            if ( ! (_mydbl = getmem (DOUBLESIZE)))
            {
                outofmemory ();
            }

            fread (_mydbl, DOUBLESIZE, 1, InPath);
            L095c (_mydbl);
            cref->val.num = _mydbl;
            break;
        default:           /* L08e7 */
            cref->val.num = getword (InPath);
            break;
    }

    cref->left = 0;

    switch (_cmdty)
    {
        case 'B':           /* L0911 */
            cref->left = L0787 ();
        case 'R':           /* L0916 */
            cref->right = L0787 ();
            break;
        case 'L':           /* L091b */
            cref->left = L0787 ();
        case 'N':           /* L0920 */
            cref->right = 0;
            break;
        default:           /* L0926 */
            fprintf (stderr, "bad node type: %02x\n", _cmdty);
            err_exit ();
            break;
    }

    return cref;
}

#ifdef COCO
void
L095c (dblptr)
    register double *dblptr;
{
    char *var6;
    int var4;
    int var2;
    int var0;

    var6 = (char *)dblptr;

    var2 = var6[7];
    var6[7] = 0xb8;

    if (var0 = (var6[0] & 0x80))
    {
        var6[0] &= 0x7f;
    }

    /* This isn't right.  We need to do something to normalize it */
    /*dptr = dptr;*/        /* L098b */
comehere1: /* Trying to get a reference for the above if to jump to */
#asm
    leax 0,u
    pshs x
    pshs u
    lbsr _dnorm
    leas 2,s
    lbsr _dmove
#endasm

    if (var2 < 0)
    {
        var2 = -var2;
        /*var4 = 0;*/
    }
    /*else
    {
        var4 = 1;
    }*/
    var4 = (var2 >= 0);
   
    /* L09ac + 1 */
#asm
    leax 0,u
    pshs x
    ldd 6,s
    pshs d
    ldd 6,s
    pshs d
    leax 0,u
    lbsr _dstack
    lbsr scale
    leas 12,s
    lbsr _dmove
#endasm

    if (var0)
    {
        *dblptr = -(*dblptr);
    }
}
#else
void
L095c (double *dblptr)
{
    return; /* I think any system we use this on will have native longs */
}

#endif

void
#ifndef COCO
openoutpth (char *fnam)
#else
openoutpth (fnam)
    char *fnam;
#endif
{
    if (OutPath)
    {
        return;
    }

    if (!(OutPath = fopen (fnam, "w")))
    {
        fprintf (stderr, "can't open %s", fnam);
        err_exit ();
    }
}

void
#ifdef COCO
L0a16 (cref, parm2)
    register expnode *cref;
    int parm2;
#else
L0a16 (expnode *cref, int parm2)
#endif
{
    switch (parm2)
    {
        case LONG:      /* L0a25 */
            L2505 (cref);
            goto L0a39;
        case FLOAT:     /* L0a30 */
        case DOUBLE:    /* L0a30 */
            L29fc (cref);
L0a39:
            if (cref->op != FREG)
            {
#ifdef COCO
                gen (LOADIM, UREG, FREG);
                gen (PUSH, UREG);
#else
                gen (LOADIM, UREG, FREG, 0);
                gen (PUSH, UREG, 0, 0);
#endif
                switch (parm2)
                {
                    case FLOAT:  /* L0a6c */
                    case DOUBLE: /* L0a6c */
#ifdef COCO
                        gen (DBLOP, MOVE, parm2);
#else
                        gen (DBLOP, MOVE, parm2, 0);
#endif
                        break;
                    default:        /* L0a81 */
#ifdef COCO
                        gen (LONGOP, MOVE);
#else
                        gen (LONGOP, MOVE, 0, 0);
#endif
                        break;
                }
            }
            
            break;
        default:           /* L0aa0 */
            L0bc3 (cref);
    }
}

void
#ifdef COCO
psh_stk (parm)
#else
psh_stk ( char *parm)
#endif
{
    fprintf (OutPath, " leas %d,s\n", parm);
}


void
#ifdef COCO
err_exit ()
#else
err_exit (void)
#endif
{
    if (InFileName)
    {
        unlink (InFileName);
    }

    exit (1);
}

/* ******************************************************** *
 * getword () - retrieves a little-endian value stored in   *
 *          file and converts it to a native int (signed)   *
 * ******************************************************** */

#ifndef COCO
int
getword (FILE *fp)
{
    int val;

    val = (getc (fp) << 8) + (getc (fp) & 0xff);

    if ((sizeof (int) == 4) && (val & 0x8000))
    {
        val |= 0xffff0000;
    }

    return val;
}
#endif
