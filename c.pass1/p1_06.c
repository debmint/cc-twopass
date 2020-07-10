/* ******************************************************** *
 * pass1_06.c                                               *
 * ******************************************************** */

/* $Id: p1_06.c 18 2008-05-19 21:54:22Z dlb $ */

/* This file is an exact match with original */

#ifndef COCO
#   ifndef direct
#       define direct
#   endif
#endif

direct int D000b,
           D000d;

#include "pass1.h"

/* ************************************************************ *
 * L4432 () - Outputs a label name when there is an assignment  *
 * Passed : (1) - LBLDEF * lblstruct (for the label)            *
 *          (2) - FT_type for label                             *
 *          (3) -                                               *
 * ************************************************************ */

#ifndef COCO

void
L4432 (register LBLDEF *lblstruct, int _ftTyp, int p3)
#else
L4432 (lblstruct, _ftTyp, p3)
register LBLDEF *lblstruct;
int _ftTyp;
int p3;
#endif
{
    /* _lbl_nam was char *.  Trying to fix error on "&=" */
    int *_lbl_nam;  /* Also char * */
    int v0;

    switch (_ftTyp)
    {
        case FT_TYPEDEF:     /* _4 */   /* L4442 */
        case FT_EXTERN:
        case FT_DPXTRN:
            cant_init ();
            return;
        case FT_DIRECT:     /* _7 */    /* L4448 */
        case FT_DPSTATIC:
            wdataflag (1);
            break;
        default:     /* any valid non-dp data ? */  /* _9 */   /* L444d */
            wdataflag (0);
            break;
    }

    /* Write label name to output stream */

    if (!D0051)     /* L4479 */ /* else L44ab */
    {
        _lbl_nam = lblstruct->fnam;

        if ((_ftTyp != FT_STATIC) && (_ftTyp != FT_DPSTATIC))
        {
            prtlbl (_lbl_nam, 1);     /* Global label */
        }
        else            /* Static variables */
        {
            lblstruct->fnccode = FT_LSEEK;      /* _16 */
            prtlbl (_lbl_nam, 0);
        }
    }
    else
    {
        /* Write ASM code for static label */
        prntstar ();
        wrtunderscore (lblstruct->lbl_nbr);
        prntCR ();
    }

    if (p3 == FT_DPXTRN)   /* _19 */    /* L44ba */     /* else l450e */
    {
        D000b = 1;
        nxt_word ();

        if (D005f == C_DQUOT)        /* else L4507 */
        {
            _lbl_nam = lblstruct->w4;

            if (*_lbl_nam == 0)        /* else L44e2 */
            {
                *_lbl_nam = D0017;
            }
            else
            {
                if ((v0 = *_lbl_nam - (int)D0017) >= 0)     /* L44e2 */
                {
                    prnt_rzb (v0);
                }
                else
                {
                    reprterr ("too long");
                }
            }

            nxt_word ();        /* L44ff */
            goto L4563;
        }

        D000b = 2;      /* L4507 */
    }
    else        /* Not DPEXTERN */
    {
        D000b = 2;      /* _21 */   /* L450e */
        nxt_word ();
    }

    if (p3 == FT_STRUCT)    /* else L4533 */
    {
        L4570 (p3, lblstruct, lblstruct->p10, 0); /* L4524 */  /* go to L4565 */
    }
    else
    {
        if (inbraces (p3))      /* L4533 */
        {
            L4570 ( p3, lblstruct, lblstruct->w4, 0);
        }
        else
        {
            if (!(L4570 (p3, lblstruct, lblstruct->w4, 1)))
            {
                find_sep ();    /* Look for comma or ";" */
            }
        }
    }

L4563:
    putc_e ();
    D000b = 0;
}

#ifndef COCO

int
L4570 (int ftType, register LBLDEF *regptr, LBLDEF *p3, int readflg)
#else
int
L4570 (ftType, regptr, p3, readflg)
int ftType;
register LBLDEF *regptr;
LBLDEF *p3;
int readflg;
#endif
{
    int v10;
    int v8;
    unsigned int v6;
    int v4;
    unsigned int v2;
    LBLDEF *v0;

    if (!readflg)
    {
        lookfor (C_LBRKET);
    }
    else
    {
        if (D005f == C_LBRKET)
        {
            v10 = 1;
            nxt_word ();
        }
        else
        {
            v10 = 0;
        }
    }

    if (inbraces (ftType))  /* L45a3 */     /* else L4691 */
    {
        if (!(v2 = p3->gentyp))
        {
            v2 = -1;
        }

        if ((v8 = MSBrshft2 (ftType)) == 4)     /* L45bd */
        {
            v4 = regptr->p10;
        }
        else
        {
            v4 = p3->vsize;     /* L45d3 */
        }

        v6 = 0;

        /* Process until a right bracket is found */

        while (D005f != C_RBRKET)     /* L4616 */
        {
            if (L4570 (v8, regptr, v4, (readflg + 1))) /*L45e0*/ /*else L4748*/
            {
                if ((++v6 >= v2) || (D005f != C_COMMA))
                {
                    break;
                }

                nxt_word ();
                continue;   /* useless, but trying to match their code */
            }
            else
            {
                return 0;
            }
        }

        if (v2 == -1)
        {
            p3->gentyp = v6;
            /* go to L465c */
        }
        else
        {
            if (v6 < v2)        /* L462d */
            {
                L474e (L418a (v8, regptr->vsize, p3->vsize) * (v2 - v6));
            }
        }

L465a:
        if ((readflg) && (!v10))
        {
            return 1;
        }

        if (D005f == C_COMMA)
        {
            nxt_word ();
        }

        if (D005f == C_RBRKET)
        {
            nxt_word ();
            return 1;
        }

        reprterr ("too many elements");
        find_sep ();
        return 1;
    }

    /* L4691 */
    if (ftType == FT_STRUCT)        /* else L471c */
    {
        if (!(v0 = p3)) /* else L46ea */
        {
            reprterr ("unions not allowed");
            find_sep ();
            return 0;
        }

        while (D005f != C_RBRKET)
        {
            regptr = v0->vsize;    /* L46aa */

            if (!L4570 (regptr->gentyp, regptr,
                        (regptr->gentyp == 4 ? regptr->p10 : (int)regptr->w4),
                         (readflg + 1)))
            {
                return 0;
            }

            if ((v0 = v0->gentyp) && (D005f == C_COMMA))       /* else L4713 */
            {
                nxt_word ();
                continue;   /* not needed */
            }
            else
            {
                break;
            }
        }

        while (v0)      /* L4713 */
        {
            L474e (L418a (regptr->gentyp, regptr->vsize, (regptr = v0->vsize)->w4));
            v0 = v0->gentyp;
        }

        goto L465a;
    }

    if (L4772 (ftType))     /* L471c */     /* else L473a */
    {
        if (v10)        /* else L4735 */
        {
            lookfor (C_RBRKET);
        }

        return 1;
    }
    else
    {
        reprterr ("constant expression required");
        find_sep ();
        return 0;
    }
}

#ifndef COCO

void
L474e (int p1)
#else

void 
L474e (p1)
int p1;
#endif
{
    prntstar ();
    prtspstr ("rzb ");
    prntdgt (p1);
    prntCR();
}

#ifndef COCO

int
L4772 (int p1)
#else

int 
L4772 (p1)
int p1;
#endif
{
    /* 8 bytes stack */
    CMDREF *v6;
    int v4;
    int v2;
    int t_ftTy;
    register CMDREF *regptr;

    /*
     * NEED TO FIND OUT WHAT regpt IS
     */

    if (!(regptr = L0f18 (L0580 (2))))   /* else return 0 */
    {
        return 0;
    }

    v4 = 0;
    v2 = 1;
    t_ftTy = regptr->ft_Ty;

    if (ispointer (p1))        /* else L47d5 */
    {
        switch (t_ftTy)
        {
            case 8:      /* L47b2 */
                do_cast (regptr, 1);   /* do this at L47fe */
                break;      /* jump to L4807 */
            default:     /* L47b7 */
                if (!ispointer (t_ftTy))
                {
                    goto L4827;
                }
            case 1:      /* L4807 */
            case 7:      /* L4807 */
                break;
        }
    }

    /* L47d5 */
    else
    {
        if (ispointer (t_ftTy))    /* else L47ef */
        {
            if (!iswordorlong (p1))      /* else L4807 */
            {
                goto L4827;
            }
        }
        else
        {
            do_cast (regptr, ((p1 == 5) ? 6 : p1));   /* L47ef */
        }
    }

    /* L4807 here */
    
    if ((regptr->vartyp == C_PLUS) || (regptr->vartyp == 81))    /* else L4860 */
    {
        
        if ((v6 = regptr->cr_Right)->vartyp != C_INTSQUOT)    /* else L4832 */
        {
L4827:
            v2 = 0;
            goto L4904;
        }

        if (regptr->vartyp == 81)
        {
            v4 = -(v6->cmdval);
        }
        else
        {
            v4 = v6->cmdval;       /* L4848 */
        }

        L0393 (v6);
        v6 = regptr;
        regptr = regptr->cr_Left;
        mak_curnt (v6);
    }

    /* L4860 */

    if (regptr->vartyp == C_AMPERSAND)   /* else L48b7 */
    {
        /* Check this out!  seems convoluted
         * We're having to fake it here */

        switch (((CMDREF *)((v6 = regptr->cr_Left)->cmdval))->cmdval)
        /*switch (((v6 = regptr->cr_Left)->cmdval)->cmdval)*/
        {
            default:     /* L4874 */
                v2 = 0;
                break;      /* go to L4906 */
            case 15:     /* L487b */
            case 14:     /* L487b */
            case 12:     /* L487b */
            case 33:     /* L487b */  /* '!' */
            case 34:     /* L487b */  /* '"' */
                D000d = 1;
                prt_509e (v6, v4);
                D000d = 0;
                break;      /* go to L4906 */
        }
    }
    else
    {       /* L48b7 */
        switch (regptr->vartyp)
        {
            case C_DOUBLE:     /* L48bb */  /* 'K' */
                if (p1 == 5)    /* else L48cf */
                {
#ifdef COCO
#asm
                    ldx 8,u
                    pshs x
                    ldx 8,u
                    lbsr to_flacc
                    lbsr _dmove
#endasm
#else
                    /* ?????????? */
                    *(double *)regptr->cmdval = *(double *)regptr->cmdval;
#endif
                }

            case C_INTSQUOT:     /* L48cf */  /* '6' */
            case C_LONG:     /* L48cf */  /* 'J' */
                L4913 (regptr->cmdval, p1);

                break;      /* go to L4906 */
            case C_DQUOT:     /* L48dd */  /* '7' */
                prnt_fdb ();
                prtlcllbl (regptr->cmdval);
                break;
            default:     /* L4874 */
                v2 = 0;
                break;      /* go to L4906 */
        }
    }

L4904:
    L0393 (regptr);
    return v2;
}

#ifndef COCO

void
L4913 (register int valu, int f_type)
#else

void 
L4913 (valu, f_type)
register int valu;
int f_type;
#endif
{
    int _siz;

    switch (f_type)
    {
        case FT_CHAR:      /* L4923 */
            prnt_fcb ();
#ifdef COCO
            prntdgt (valu);
#else
            prntdgt (valu & 0xff);
#endif
            prntCR ();
            return;
        case FT_INT:      /* L4932 */
        case FT_UNSIGNED:      /* L4932 */
        default:     /* L4932 */
            _siz = 1;
            break;
        case FT_LONG:      /* L4937 */
            _siz = 2;
            break;
        case FT_FLOAT:      /* L493e */
        case FT_DOUBLE:      /* L493e */
            prt_float (valu, f_type);
            return;
    }

    prntnuls (valu, _siz);
}

#ifndef COCO

void
cant_init (void)
#else

void 
cant_init ()
#endif
{
    reprterr ("cannot initialize");
    find_sep ();
}

/* ************************************************************ *
 * find_sep() - reads in input stream until ",", ";", or error  *
 * ************************************************************ */

#ifndef COCO

void
find_sep (void)
#else

void 
find_sep ()
#endif
{
    for (;;)
    {
        switch (D005f)
        {
            case C_COMMA:
            case C_SEMICOLON:
            case -1:    /* err */
                return;
            default:
                nxt_word ();
        }
    }
}
