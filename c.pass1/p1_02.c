/* *********************************************************** *
 * pass1_02.c                                                  *
 * *********************************************************** */

/* $Id: p1_02.c 18 2008-05-19 21:54:22Z dlb $ */

/* This file is an exact match with the original code
 * ( with non-critical variations
 */

#include "pass1.h"

/* ******************************************************** *
 * L0580 ()                                                 *
 * Passed : 
 * ******************************************************** */

#ifndef COCO

CMDREF *
L0580 (int p1)
#else

CMDREF * 
L0580 (p1)
int p1;
#endif
{
    /* 14 bytes of stack */
    CMDREF *v12;
    int _vrtyp;    /* vartype ??? */
    int cp_d61;
    CMDREF *v6;
    int v4;
    char *_strng;
    int v0;

    register CMDREF *regval;
    
    if (!(v12 = L0694 ()))  /* else return 0 */
    {
        return 0;
    }

    while ((is_math ()) && (p1 <= LblVal))    /* L0679 */
    {
        _vrtyp = sym;        /* L059b */
        v0 = cp_d61 = LblVal;    /* fix a = b = c ?????? */
        v4 = D003f;
        _strng = D0063;
        nxt_word();

        switch (_vrtyp)
        {
            case C_QUESTION:    /* _10 (L05d9) */
            case C_EQUAL:
                break;
            default:            /* _14 (L05b4) */
                /* Not <something>= (+=, -=, %=, etc) */

                if ((_vrtyp < 160) || (_vrtyp > 169))
                {
                    v0 = cp_d61 + 1;
                }

                break;
        }

        /* recurse into self */

        if ((regval = L0580 (v0)))      /* _10 (L05d9) else L066e */
        {
            /*  if ? then : else */

            if (_vrtyp == C_QUESTION)       /* else L064d */
            {
                if (need (C_COLON))     /* else L0642 */
                {
                    L0393 (regval);     /* L0642 */
                    goto L068c;     /* Wouldn't "break" work? */
                }
                else
                {
                    _strng = D0063;
                    v4 = D003f;
                    
                    if ((v6 = L0580 (3)))       /* else L0637 */
                    {
                        regval = add_cmdref (C_COLON, regval, v6,
                                                3, v4, _strng);
                        /* go to L064d */
                    }
                    else
                    {
                        reprterr ("third expression missing");  /* L0637 */

                        /* Same procedure as above if need (C_COLON)
                         * is true
                         */

                        L0393 (regval);
                        goto L068c;
                    }
                }
            }

            /* L064d */
            v12 = add_cmdref (_vrtyp, v12, regval, cp_d61, v4, _strng);
        }
        else
        {
            reprterr ("operand expected");  /* L066e */
        }
    }       /* end while() */

L068c:
    return v12;
}

CMDREF *
L0694 ()
{
    /* 12 bytes of stack */
    CMDREF *v10;
    int v8;
    int v6;
    char *v4;
    int v2;
    CMDREF *v0;

    register CMDREF *regval = 0;

    switch (sym)      /* L07fc */
    {
        case C_DQUOT:
        case C_USRLBL:
        case C_LONG:
        case C_DOUBLE:
        case C_INTSQUOT:    /* L06a6 */
            regval = add_cmdref (sym, 0, 0, LblVal, D003f, D0063);
            nxt_word ();
            break;

        case C_LPAREN:     /* L06cb */  /* '-' */
            nxt_word ();

            if (istype ())
            {
                regval = L0d47 ();
                need (C_RPAREN);

                /* Recurse into self */

                if (!(regval->cr_Left = L0694()))       /* else break */
                {
                    release (regval);
                    regval = 0;
                }

                break;
            }

            if (!(regval = L0580 (0)))  /* L06f9 */     /* else L072f */
            {
L070a:
                exprmsng ();
                regval = add_cmdref (C_INTSQUOT, (CMDREF *)0, 0, 0,
                                        D003f, D0063);
            }

            need (C_RPAREN);

            break;

        case C_EXCLAM:      /* L073a */
        case C_MINUS:
        case C_TILDE:
        case C_ASTERISK:
        case C_MINMINUS:
        case C_PLUSPLUS:
        case C_AMPERSAND:
            v8 = sym;
            v6 = D003f;
            v4 = D0063;
            nxt_word ();

            if (v10 = L0694 ()) /* self */     /* else L0775 */
            {
                regval = add_cmdref (v8, v10, 0, 14, v6, v4);
            }
            else {
                reprterr ("primary expected");
            }

            break;

                /* 59 = sizeof??? */
        case C_SIZEOF:     /* L0781 */
            v6 = D003f;
            v4 = D0063;
            nxt_word ();

            if (sym == C_LPAREN)        /* else L07c3 */
            {
                nxt_word ();

                if (istype ())          /* else L07a5 */
                {
                    v10 = L0d47 ();    /* go to L07b7 */
                }
                else
                {
                    if (!(v10 = L0580 (0)))
                    {
                        goto L070a;
                    }
                }

                need (C_RPAREN);     /* L07b7 */
            }
            else
            {
                v10 = L0694 ();     /* L07c3 */
            }

            v0 = v10;           /* L07c8 */
            regval = add_cmdref (C_INTSQUOT, 0, 0, L0e29 (&v0), v6, v4);
            L0393 (v0);

            break;
    }

    if (regval == 0)        /* _37 */
    {
        return 0;
    }

    for (;;)
    {
        switch (sym)      /* L098f */
        {
            case C_LPAREN:     /* L086e */  /* '-' */
                v4 = D0063;
                v6 = D003f;
                nxt_word ();
                regval = add_cmdref (101, regval, L09f4 (), 15, v6, v4);
                need (C_RPAREN);

                continue;

            case C_LBRACE:     /* L089f */  /* '+' */
                nxt_word ();
                
                if (!(v10 = L0580 (2)))     /* else L08d3 */
                {
                    exprmsng ();
                    v10 = add_cmdref (C_INTSQUOT, 0, 0, 0, D003f, D0063);
                }

                regval = add_cmdref (C_PLUS, regval, v10, 12, D003f, D0063);
                regval = add_cmdref (C_ASTERISK , regval, 0, 15, D003f, D0063);
                need (C_RBRACE);

                continue;

            case C_PERIOD:     /* L091f */
            case C_PTRREF:     /* L091f */
                v8 = sym;
                v6 = D003f;
                v4 = D0063;
                
                ++Struct_Union;
                nxt_word ();
                --Struct_Union;

                /* if not label... ?? */

                if (sym != C_USRLBL)
                {
                    noidentf ();           /* go to L09ab */
                    break;
                }
                else
                {
                    v10 = add_cmdref (sym, 0, 0, LblVal, D003f, D0063);
                    regval = add_cmdref (v8, regval, v10, 15, v6, v4);
                    nxt_word ();
                    continue;
                }

        }

        break;
    }

    /* L09ab */
    switch (sym)
    {
        case C_PLUSPLUS:   /* L09af */ /* 0x3c */
            sym = C_INCREMENT;
            goto L09bf;
        case C_MINMINUS:   /* L09b8 */ /* 0x3d */
            sym = C_DECREMENT;
L09bf:
            regval = add_cmdref (sym, regval,0, 14, D003f, D0063);
            nxt_word ();

            break;
    }

    return regval;
}

#ifndef COCO

CMDREF *
L09f4 (void)
#else

CMDREF * 
L09f4 ()
#endif
{
    CMDREF *var0;

    register CMDREF *regint = 0;

    /*for (;;)*/
    while (1)
    {
        if (sym == C_RPAREN)      /* else L0a4b */
        {
            break;
        }

        if (var0 = L0580 (2))   /* else L0a3e */
        {
            var0 = add_cmdref (11, var0, regint, 0, var0->_cline, var0->_lpos);
            regint = var0;
        }

        if (sym != C_COMMA)
        {
            break;
        }

        nxt_word ();
    }

    return regint;
}

#ifndef COCO

CMDREF *
L0a4f (int parm1)
#else

CMDREF * 
L0a4f (parm1)
int parm1;
#endif
{
    CMDREF *var0;
    register CMDREF *regref;

    if ((regref = L0f18 (L0580 (parm1))) && (regref->vartyp == C_INTSQUOT))
    {
        var0 = regref->cmdval;
    }
    else
    {
        var0 = 0;
        reprterr ("constant required");
    }

    if ( regref)
    {
        L0393 (regref);
    }

    return var0;
}

#ifndef COCO

int
is_math (void)
#else

int 
is_math ()
#endif
{
    switch (sym)
    {
        case C_AMPERSAND:  /* L0aa7 */
            sym = C_AND;
            LblVal = 8;
            return 1;
        case C_ASTERISK:   /* L0ab1 */
            sym = C_MULT;
            LblVal = 13;
            return 1;
        case C_MINUS:      /* L0abb */
            sym = C_NEG;
            LblVal = 12;
            /*return 1;*//* Fall through to next case */
        case C_COMMA:      /* L0ac5 */
        case C_EQUAL:
        case C_QUESTION:
            return 1;
        case C_COLON:      /* retrn0 */
            return 0;
        default:           /* L0aca */
         /*   if ((sym < C_ANDAND) || (sym > C_GT))
            {
                if ((sym < C_PLUSEQ) || (sym > C_EOREQ))
                {
                    return 0;
                }
            }*/
            if (((sym >= C_ANDAND) && (sym <= C_GT)) ||
                    (sym >= C_PLUSEQ) && (sym <= C_EOREQ))
            {
                return 1;
            }
            return 0;
    }

    /*return 1;*/
}

#ifndef COCO

int
do_math (int parm1, int parm2, int parm3)
#else

int 
do_math (parm1, parm2, parm3)
int parm1;
int parm2;
int parm3;
#endif
{
    switch (parm1)
    {
        case C_PLUS:       /* addem */
            return (parm2 + parm3);
        case C_NEG:        /* subtract */
            return (parm2 - parm3);
        case C_MULT:        /* multiply */
            return (parm2 * parm3);
        case C_SLASH:      /* divide */
            if (parm3 == 0)
            {
                divby_0 ();
                return 0;
            }

            return (parm2 / parm3);
        case C_PERCENT:    /* do_mod */
            if (parm3)
            {
                return (parm2 % parm3);
            }
            
            divby_0 ();
            return 0;

        case C_AND:        /* do_and */
            return (parm2 & parm3);
        case C_VBAR:       /* do_or */
            return (parm2 | parm3);
        case C_CARET:      /* do_eor */
            return (parm2 ^ parm3);
        case C_LSHIFT:     /* ashft_l */
            return (parm2 << parm3);
        case C_RSHIFT:     /* ashft_r */
            return (parm2 >> parm3);
        case C_EQEQ:       /* tst_eq */
            return (parm2 == parm3);
        case C_NOTEQ:      /* tst_neq */
            return (parm2 != parm3);
        case C_GT:         /* tst_gt */
            return ((parm2 > parm3) ? 1 : 0);
        case C_LT:         /* tst_lt */
            return ((parm2 < parm3) ? 1 : 0);
        case C_GT_EQ:      /* tst_le */
            return ((parm2 >= parm3) ? 1 : 0);
        case C_LT_EQ:      /* L0be2 */
            return ((parm2 <= parm3) ? 1 : 0);
        case C_MINUS:      /* negate */
            return (-parm2);
        case C_EXCLAM:     /* is_zero */
            return (!parm2);
        case C_TILDE:      /* do_com */
            return (~parm2);
        case C_ANDAND:     /* both_nul */
            return (parm2 && parm3);
        case C_OROR:       /* neit_nul */
            return (parm2 || parm3);

            /* The following deal with unsigned equality/inequality */

        case 96:        /* L0c2d */
        case 97:        /* L0c2d */
        case 98:        /* L0c2d */
        case 99:        /* L0c2d */
            {
                unsigned int vv2;
                unsigned int vv0;

                vv2 = parm3;
                vv0 = parm2;

                switch (parm1)
                {
                    case 96:           /* L0c3b */
                        return (vv0 <= vv2);
                    case 97:           /* L0c47 */
                        return (vv0 < vv2);
                    case 98:           /* L0c53 */
                        return (vv0 >= vv2);
                    default:           /* L0c5f */
                        return (vv0 > vv2);
                }
            }

        default:
            reprterr ("constant operator");
            return 0;
    }
}

#ifndef COCO

CMDREF *
L0d47 (void)
#else

CMDREF *
L0d47 ()
#endif
{
    int var12;
    int var10;
    int __ftTy;
    CMDREF *var6;
    int var4;
    char *var2;
    int var0;

    var4 = D003f;
    var2 = D0063;
    __ftTy = L3f8a (&var6, &var10,
                    (__ftTy = do_lblnam (&var12, &var10, &var0)));
    L4204 (&D0047);

    if (var6)
    {
         reprterr ("name in a cast");
    }

    var6 = add_cmdref (32, 0, 0, 0, var4, var2);
    var6->ft_Ty = __ftTy;
    L4100 (var6, var10, var12);

    return var6;
}

/* ************************************************************** *
 * add_cmdref () - Checks to see if D002d points to a CMDREF      *
 *      if so, points D002d to the previous cmdref                *
 *      Otherwise, creates a new CMDREF and initializes it        *
 * Returns: Either D002d or the new CMDREF                        *
 * ************************************************************** */

#ifndef COCO

CMDREF *
add_cmdref ( int __ccode,       /* Applicable C_type */
             CMDREF *_oldpt,
             CMDREF *p3,
             int myval,         /* This refers to the value, or LBLDEF */
             int __myline,
             char *_line_pos
           )
#else

CMDREF *
add_cmdref (__ccode, _oldpt, p3, myval, __myline, _line_pos)
int __ccode;
CMDREF *_oldpt;
CMDREF *p3;
int myval;
int __myline;
char *_line_pos;
#endif
{
    register CMDREF *regptr;

    if (D002d)
    {
        regptr = D002d;
        D002d = regptr->cr_Left;
    }
    else
    {
        regptr = addmem (sizeof (CMDREF));
    }

    regptr->vartyp = __ccode;
    regptr->cr_Left = _oldpt;
    regptr->cr_Right = p3;
    regptr->cmdval = myval;
    regptr->_cline = __myline;
    regptr->_lpos = _line_pos;
    regptr->cr_Nxt = 0;

    return regptr;
}

#ifndef COCO

void
exprmsng (void)
#else

void 
exprmsng ()
#endif
{
    reprterr ("expression missing");
}

#ifndef COCO

int
L0e29 (CMDREF **p1)
#else

int 
L0e29 (p1)
CMDREF **p1;
#endif
{
    register CMDREF *regptr = *p1;

    switch (regptr->vartyp)
    {
        default:     /* L0e38 */
            regptr = *p1 = L0f18 (regptr);
            goto L0e58;
        case C_USRLBL:     /* L0e48 */  /* '4' */
            /* Is this right??? */
            regptr->ft_Ty = *(int *)(regptr->cmdval);
            ck_declared (regptr);
            regptr = regptr->cmdval;
        case 32:     /* L0e5a */  /* ' ' */

L0e58:
            return (L418a (regptr->ft_Ty, regptr->__cr2, regptr->__cr4));
            break;
        case C_PERIOD:
        case C_PTRREF:     /* L0e6d */  /* 'E' */

            /* This is not correct for a CMDREF.  The bump is 12
             * regptr must be some other type struct
             */

            return L0e29 (&(regptr->cr_Right));
            break;
    }
}
