/* ****************************************************** *
 * pass1_04.c                                             *
 * ****************************************************** */

/* $Id: p1_04.c 18 2008-05-19 21:54:22Z dlb $ */

/* This file is an exact match with original */

#include "pass1.h"

#ifndef COCO

void
do_loops (void)
#else

void 
do_loops ()
#endif
{
    if (D005f != C_SEMICOLON)
    {
        D004f = 0;
    }

L27e6:
    switch (D005f)
    {
        case C_SEMICOLON:     /* L290b */  /* '(' */
            break;
        case C_BUILTIN:     /* L27ed */  /* '3' */
            switch (LblVal)
            {
                case FT_IF:     /* L27f1 */
                    do_if ();
                    return;
                case FT_WHILE:     /* L27f6 */
                    do_while ();
                    return;
                case FT_RETURN:     /* L27fb */
                    do_retrn ();
                    break;  /* go to L290b */
                case FT_CASE:     /* L2801 */
                    do_case ();
                    return;
                case FT_SWITCH:     /* L2806 */
                    do_swtch ();
                    return;
                case FT_BREAK:     /* L280b */
                    do_break ();
                    break;      /* go to L290b */
                case FT_CONTINUE:     /* L2811 */
                    do_contin ();
                    break;      /* go to L290b */
                case FT_DEFAULT:     /* L2817 */
                    do_deflt ();
                    return;
                case FT_FOR:     /* L281c */
                    do_for ();
                    return;
                case FT_DO:     /* L2821 */
                    do_do ();
                    break;      /* go to L290b */
                case FT_GOTO:     /* L2827 */
                    do_goto ();
                    break;      /* go to L290b */
                case FT_ELSE:     /* L282d */
                    reprterr ("no 'if' for 'else'");
                    nxt_word ();      /* go to L2897 */
                    goto L27e6;
                default:     /* L283e */
                    goto L28a0;
            }

            break;
        case C_LBRKET:     /* L2881 */  /* ')' */
            L3a4c ();
            nxt_word ();
            return;
        case -1:     /* L2889 */  /* ')' */
            return;
        case C_USRLBL:     /* L288b */  /* '4' */
            skipblank ();
            
            if (CurChr == ':')
            {
                L2fe9 ();
                goto L27e6;
            }
            else
            {
                goto L28c8;
            }
        default:     /* L28a2 */
L28a0:
            if (is_sc_specifier () || isvariable ())
            {
                reprterr ("illegal declaration");
                
                do
                {
                    nxt_word ();
                } while (D005f != C_SEMICOLON);

                break;
            }
            else
            {
L28c8:
                if (!(L3082 (0)))
                {
                    reprterr ("syntax error");
                    cmma_rbrkt ();
                    return;
                }
            }

            break;
    }

    lookfor (C_SEMICOLON);     /* L290b */
}

#ifndef COCO

void
do_if (void)
#else

void 
do_if ()
#endif
{
    int _lbnumHi;
    int v2;
    LBLDEF *v0;
    register int _lbnumLo;

    nxt_word ();
    v0 = L30e7 ();
    _lbnumLo = ++LblNum;
    _lbnumHi = ++LblNum;

    if (D005f == C_SEMICOLON)    /* else L2966 */
    {
        nxt_word ();
        L3140 (v0, _lbnumLo, _lbnumHi, 0);
        prntw_l (_lbnumHi);
        v2 = _lbnumLo;
    }
    else
    {
        L3140 (v0, _lbnumLo, _lbnumHi, 1);
        prntw_l (_lbnumLo);
        do_loops ();
        v2 = _lbnumHi;
    }

    /* L2988 */
    if ((D005f == C_BUILTIN) && (LblVal == 21))    /* else L29cd */
    {
        nxt_word ();

        if (D005f != C_SEMICOLON)        /* else L29cd */
        {
            if (_lbnumLo != v2)   /* else L29ca */
            {
                prt_4b5e (124, (v2 = ++LblNum), 0);
                prntw_l (_lbnumHi);
            }

            do_loops ();
        }
    }

    prntw_l (v2);   /* L29cd */
}

#ifndef COCO

void
do_while (void)
#else

void 
do_while ()
#endif
{
    int v8;
    int v6;
    int v4;
    int v2;
    LBLDEF *v0;
    register int regptr;

    v8 = D0053;
    v6 = D0055;
    v4 = D02d6;
    v2 = D02d8;
    nxt_word ();
    D0053 = ++LblNum;
    D02d6 = D02d8 = D002f;
    D0055 = ++LblNum;
    v0 = L30e7 ();

    if (D005f == C_SEMICOLON)
    {
        regptr = D0055;
    }
    else
    {
        prt_4b5e (124, D0055, 0);
        regptr = ++LblNum;
        prntw_l (regptr);
        do_loops ();
    }

    prntw_l (D0055);       /* L2a4d */
    L3140 (v0, regptr, D0053, 0);
    prntw_l (D0053);
    D0053 = v8;
    D0055 = v6;
    D02d6 = v4;
    D02d8 = v2;
}

#ifndef COCO

void
do_swtch (void)
#else

void 
do_swtch ()
#endif
{
    int v12;
    int v10;
    int v8;
    int v6;
    int v4;
    int v2;
    struct case_ref *_refsav;
    register CMDREF *regptr;

    nxt_word ();
    ++D0057;
    _refsav = CaseNow;
    v10 = CaseList;
    CaseList = 0;
    v12 = D0053;
    v8 = D02d4;
    v2 = D02d6;
    D0053 = ++LblNum;
    D02d6 = D002f;
    D02d4 = 0;

    /* get the case value */

    lookfor (C_LPAREN);
    
    if ((regptr = L0f18(L0580 (0))))       /* else L2b3e */
    {
        ck_declared (regptr);
        
        switch (regptr->ft_Ty)
        {
            case FT_CHAR:      /* L2af8 */
            case FT_LONG:
                do_cast (regptr, FT_INT);
                break;
            case FT_INT:      /* L2b2e */
            case FT_UNSIGNED:
                break;
            default:     /* L2b06 */
                notintegral (regptr);
                L25e6 (regptr);
                break;
        }

        prt_4c1b (regptr);
        L0393 (regptr);
    }
    else
    {
        exprmsng ();    /* L2b3e */
    }

    lookfor (C_RPAREN);
    prt_4b5e (124, (v6 = ++LblNum), 0);
    do_loops ();

    if (!D004f)
    {
        prt_4b5e (124, D0053, 0);
    }

    prntw_l (v6);       /* L2b7d */
    regptr = CaseList;

    while (regptr)     /* L2ba8 */
    {
        v4 = regptr->ft_Ty;
        prt_4b5e (125, regptr->__cr4, regptr->__cr2);
        regptr->ft_Ty = D0045;
        D0045 = regptr;
        regptr = v4;
    }

    if (D02d4)
    {
        prt_4b5e (124, D02d4, 0);
    }

    prntw_l (D0053);        /* L2bc6 */
    CaseList = v10;
    D02d4 = v8;
    --D0057;
    CaseNow = _refsav;
    D0053 = v12;
    D02d6 = v2;
}

#ifndef COCO

void
do_case (void)
#else

void 
do_case ()
#endif
{
    int v0;
    register struct case_ref *regptr;

    nxt_word ();
    v0 = L0a4f (0);
    lookfor (C_COLON);

    if (D0057)          /* else L2c55 */
    {
        if (regptr = D0045)
        {
            D0045 = regptr->case_nxt;
        }
        else
        {
            regptr = addmem (sizeof (struct case_ref));     /* L2c21 */
        }

        if (CaseList)      /* L2c2d */
        {
            CaseNow->case_nxt = regptr;
        }
        else
        {
            CaseList = regptr;
        }

        CaseNow = regptr;     /* L2c39 */

        /* Fix this!  regptr is a 6-byte structure */
        regptr->case_nxt = 0;
        regptr->cas04 = v0;
        prntw_l ((regptr->cas06 = ++LblNum));
    }
    else
    {
        no_switch ();
    }
}

#ifndef COCO

void
do_deflt (void)
#else

void 
do_deflt ()
#endif
{
    nxt_word ();

    if (!D0057)
    {
        no_switch ();
    }

    if (D02d4)
    {
        reprterr ("multiple defaults");
    }
    else
    {
        prntw_l ((D02d4 = ++LblNum));
    }

    lookfor (C_COLON);
}

#ifndef COCO

void
no_switch (void)
#else

void 
no_switch ()
#endif
{
    reprterr ("no switch statement");
}

#ifndef COCO

void
do_do (void)
#else

void 
do_do ()
#endif
{
    int v8;
    int v6;
    int v4;
    int v2;
    int v0;

    v8 = D0053;
    v6 = D0055;
    v0 = D02d8;
    v2 = D02d6;
    D02d8 = D02d6 = D002f;
    D0055 = ++LblNum;
    D0053 = ++LblNum;
    nxt_word ();
    prntw_l ((v4 = ++LblNum));
    do_loops ();

    if ((D005f != C_BUILTIN) || (LblVal != 20))
    {
        reprterr ("while expected");
    }

    nxt_word ();
    prntw_l (D0055);
    L3140 (L30e7 (), v4, D0053, 0);
    prntw_l (D0053);
    D0053 = v8;
    D0055 = v6;
    D02d6 = v2;
    D02d8 = v0;
}

#ifndef COCO

void
do_for (void)
#else

void 
do_for ()
#endif
{
    int v12;
    int v10;
    int v8;
    int v6;
    int v4;
    LBLDEF *v2;
    int v0;
    register int *regptr;

    v2 = 0;
    v0 = 0;
    regptr = D0053;
    v12 = D0055;
    v6 = D02d6;
    v4 = D02d8;
    D02d8 = D02d6 = D002f;
    v10 = ++LblNum;
    D0053 = ++LblNum;
    nxt_word ();
    lookfor (C_LPAREN);
    L3082 (0);
    lookfor (C_SEMICOLON);

    if (D005f != C_SEMICOLON)
    {
        v2 = L310e ();
        prt_4b5e (124, (v8 = ++LblNum), 0);
    }

    lookfor (C_SEMICOLON);     /* L2de0 */
    
    if (v0 = L0f18 (L0580 (0)))
    {
        ck_declared (v0);
        D0055 = ++LblNum;
    }
    else
    {
        D0055 = v10;
    }

    lookfor (C_RPAREN);
    prntw_l (v10);
    do_loops ();

    if (v0)
    {
        prntw_l (D0055);
        L30ab (v0);
    }

    if (v2)     /* L2e3e */
    {
        prntw_l (v8);
        L3140 (v2, v10, D0053, 0);
    }
    else
    {
        prt_4b5e (124, v10,0);
    }

    prntw_l (D0053);
    D0053 = regptr;
    D0055 = v12;
    D02d6 = v6;
    D02d8 = v4;
}

#ifndef COCO

void
do_retrn (void)
#else

void 
do_retrn ()
#endif
{
    register CMDREF *regptr;

    nxt_word ();

    if ((D005f != C_SEMICOLON) && (regptr = L0580 ((CMDREF *)0)))      /* else L2f00 */
    {
        regptr = L0f18 (regptr);
        ck_declared (regptr);
        get_ftty (regptr);

        do_cast (regptr, ((ispointer (D004d)) ? 1 : D004d));
#ifdef __linux__
        prt_4c68 (18, regptr, D004d, 0, 0);
#else
        prt_4c68 (18, regptr, D004d);
#endif
        L0393 (regptr);
    }

    wrt_M (0);
    prt_4b5e (FT_RETURN, 0, 0);
    D004f = FT_RETURN;
}

#ifndef COCO

void
do_break (void)
#else

void 
do_break ()
#endif
{
    nxt_word ();

    if (!D0053)
    {
        reprterr ("break error");
    }
    else
    {
        wrt_M (D02d6);
        prt_4b5e (124, D0053, 0);
    }
    
    D004f = FT_BREAK;
}

#ifndef COCO

void
do_contin (void)
#else

void 
do_contin ()
#endif
{
    nxt_word ();

    if (!D0055)
    {
        reprterr ("continue error");
    }
    else
    {
        wrt_M (D02d8);
        prt_4b5e (124, D0055, 0);
    }

    D004f = FT_CONTINUE;
}

#ifndef COCO

void
do_goto (void)
#else

void 
do_goto ()
#endif
{
    register LBLDEF *regptr;

    nxt_word ();

    if (D005f != C_USRLBL)
    {
        reprterr ("label required");
    }
    else
    {
        if ((regptr = L302b ()))
        {
            prt_4b5e (FT_GOTO, regptr->lbl_nbr, 0);
            regptr->p10 |= 2;
        }

        nxt_word();
    }

    D004f = FT_GOTO;
}

#ifndef COCO

void
L2fe9 (void)
#else

void 
L2fe9 ()
#endif
{
    register LBLDEF *regptr;

    if ((regptr = L302b ()))
    {
        if (regptr->fnccode == FT_STATIC)   /* FT_STATIC */
        {
            multdef ();
        }
        else
        {
            regptr->fnccode = FT_STATIC;
            prt_4b5e (9, regptr->lbl_nbr, 0);
            regptr->p10 |= 1;
        }
    }

    nxt_word ();
    nxt_word ();
}

#ifndef COCO

CMDREF *
L302b (void)
#else

CMDREF *
L302b ()
#endif
{
    register LBLDEF *regptr = LblVal;

    if (regptr->gentyp != 9)        /* else L313c */
    {
        if (regptr->gentyp)
        {
            if (regptr->p12)
            {
                reprterr ("already a local variable");
                return 0;
            }

            null_lbldef (regptr); /* copy regptr to G18Current, null regptr */
        }

        regptr->gentyp = 9;
        regptr->fnccode = FT_AUTO;
        regptr->lbl_nbr = ++LblNum;
        regptr->p10 = 0;
        regptr->p12 = D0051;
        regptr->w16 = D0049;
        D0049 = regptr;
    }

    return regptr;
}

#ifndef COCO

LBLDEF *
L3082 (int p1)
#else
LBLDEF *
L3082 (p1)
int p1;
#endif
{
    register LBLDEF *regptr;

    if ((regptr = L0580 (p1)))  /* else return regptr */
    {
        regptr = L30ab (L0f18 (regptr));
    }

    return regptr;
}

#ifndef COCO

CMDREF *
L30ab (register CMDREF *regptr)
#else

CMDREF *
L30ab (regptr)
register CMDREF *regptr;
#endif
{
    ck_declared (regptr);

    switch (regptr->vartyp)
    {
        case 62:     /* L30c0 */  /* '>' */
            regptr->vartyp = 60;
            break;
        case 63:     /* L30c5 */  /* '?' */
            regptr->vartyp = 61;
            break;
    }

    regptr = prt_4c4f (regptr);
    L0393 (regptr);
    return regptr;
}

#ifndef COCO

LBLDEF *
L30e7 (void)
#else

LBLDEF * 
L30e7 ()
#endif
{
    LBLDEF *v0;

    lookfor (C_LPAREN);
    v0 = L310e ();
    lookfor (C_RPAREN);
    return v0;
}

#ifndef COCO

LBLDEF *
L310e (void)
#else

LBLDEF * 
L310e ()
#endif
{
    register LBLDEF *regptr;

    if (regptr = L0f18 (L0580 (0)))
    {
        ck_declared (regptr);
    }
    else
    {
        reprterr ("condition needed");
    }

    return regptr;
}

#ifndef COCO

void
L3140 (register LBLDEF *regptr, int p2, int p3, int p4)
#else

void 
L3140 (regptr, p2, p3, p4)
register LBLDEF *regptr;
int p2;
int p3;
int p4;
#endif
{
    if (regptr)
    {
        prt_4c2c (regptr, p2, p3, p4);
        L0393 (regptr);
    }
}
