/* ************************************************************************ *
 * p2_03.c - part 3 for c.pass2                                             *
 *                                                                          *
 * $Id: p2_03.c 18 2008-05-19 21:54:22Z dlb $                               *
 * ************************************************************************ */

#include "pass2.h"

void
#ifdef COCO
L1f13 (cref, parm2, parm3, parm4)
    register CMDREF *cref;
    int parm2, parm3, parm4;
#else
L1f13 (CMDREF *cref, int parm2, int parm3, int parm4)
#endif
{
    int var2;
    int var0;

    switch (var2 =  cref->vartyp)
    {           /* break = L20e9 */
        case C_ANDAND:     /* L1f28 */
            L1f13 (cref->cr_Left, (var0 = ++D000b), parm3, 1);
            goto L1f66;
        case C_OROR:       /* L1f48 */
            L1f13 (cref->cr_Left, parm2, (var0 = ++D000b), 0);
L1f66:
            L4414 (var0);
            L1f13 (cref->cr_Right, parm2, parm3, parm4);
            break;                      /* go to L20e9 */
        case C_EXCLAM:     /* L1f72 */
            L1f13 (cref->cr_Left, parm3, parm2, (1 - parm4));
            break;
        case C_EQEQ:
        case C_NOTEQ:
        case C_LT_EQ:
        case C_LT:
        case C_GT_EQ:      /* L1f87 */
        case 95:
        case 96:
        case 97:
        case 98:
        case 99:
            L20ed (var2, cref, parm2, parm3, parm4);
            break;
        case C_INTSQUOT:
        case C_DOUBLE:     /* L1fa1 */
        case C_LONG:
            if (cref->cmdval && ! parm4)
            {
#ifdef COCO
                L3292 (124, parm2, 0);
#else
                L3292 (124, parm2, 0, 0);
#endif
            }
            else
            {
                if (parm4 && ( ! cref->cmdval))
                {
#ifdef COCO
                    L3292 (124, parm3, 0);
#else
                    L3292 (124, parm3, 0, 0);
#endif
                }
            }
            break;
        case C_COMMA:      /* L1fcb */
            L0d04 (cref->cr_Left);
            L1f13 (cref->cr_Right, parm2, parm3, parm4);
            break;
        default:           /* L1fec */
            if (cref->ft_Ty == FT_LONG)
            {
                L2505 (cref);
#ifdef COCO
                L3292 (136, 139);
#else
                L3292 (136, 139, 0, 0);
#endif
                /* go to L204d */
            }
            else
            {
                if ((cref->ft_Ty == FT_FLOAT) || (cref->ft_Ty == FT_DOUBLE))
                {               /* else L2042 */
                    if (cref->vartyp == 140)
                    {
                        cref = cref->cr_Left;
                    }

                    L29fc (cref);           /* L2026 */
#ifdef COCO
                    L3292 (135, 139, cref->ft_Ty);
#else
                    L3292 (135, 139, cref->ft_Ty, 0);
#endif
                }
                else
                {
                    L2323 (cref);
                }
            }
#ifdef COCO
L204d:
#endif
            if (parm4)
            {
#ifdef COCO
                L3292 (130, C_EQEQ, parm3);
#else
                L3292 (130, C_EQEQ, parm3, 0);
#endif
            }
            else
            {
#ifdef COCO
                L3292 (130, C_NOTEQ, parm2);
#else
                L3292 (130, C_NOTEQ, parm2, 0);
#endif
            }

            break;
    }
}

void
#ifdef COCO
L20ed (parm1, cref, parm3, parm4, parm5)
    int parm1;
    CMDREF *cref;
    int parm3, parm4, parm5;
#else
L20ed (int parm1, CMDREF *cref, int parm3, int parm4, int parm5)
        /* +10            +12        +14        +16        +18  */
#endif
{
    CMDREF *var4;
    int var2;
    CMDREF *var0 = cref->cr_Left;

    register CMDREF *_crRight = cref->cr_Right;

    var2 = (parm5 ? parm4 : parm3);

    parm1 = (parm5 ? L2466 (parm1) : parm1);

    if (var0->ft_Ty == FT_LONG)
    {
        L2520 (cref);       /* go to L214b */
        goto L22b2;
    }
    else
    {           /* L2134 */
        if ((var0->ft_Ty == FT_FLOAT) || (var0->ft_Ty == FT_DOUBLE))
        {
            L2a17 (cref);
            goto L22b2;

        }
    }

    /* Check out the logic for this block ... it's pretty complicated */
    /* L2152 */
    if ((L24e6 ( var0)) ||
            ((L22ca (var0)) && ( ! L22ca (_crRight))) ||
            ((is_regvar (_crRight->vartyp)) &&
                        ( ! is_regvar (var0->vartyp))))  /* else L219c */
    {
        var4 = var0;        /* L2189 */
        var0 = _crRight;
        _crRight = var4;
        parm1 = L249e (parm1);
    }

    var4 = var0->vartyp;        /* L219c */

    if (is_regvar (var4))       /* else L221f */
    {
        L0d04 (_crRight);

        switch (_crRight->vartyp)
        {
            case 65:           /* L21b8 */
                L0c2d (_crRight);
                goto L21e0;
            case C_CHR2INT:    /* L21c3 */
                L3292 (117, 112, 119, _crRight);
                _crRight->vartyp = 112;
                /* fall through to next case */
            case 113:          /* L21e2 */
            case C_X_RGWRD:    /* L21e2 */
            case C_RGWRD:      /* L21e2 */
            case 112:          /* L21e2 */
L21e0:
#ifdef COCO
                L3292 (122, _crRight->vartyp);
#else
                L3292 (122, _crRight->vartyp, 0, 0);
#endif
                 _crRight->vartyp = 110;    /* go to L229b */
            default:           /* L229b */
                 break;
        }
    }       /* end if (is_regvar...) */
    else
    {
        if ((L24e6 (_crRight)) && (parm1 < 96))       /* L221f */
        {
            L2323 (var0);       /* go to L22b4 */
            /* this should probably have been goto L22b2; */
#ifdef COCO
            L3292 (130, parm1, var2);
#else
            L3292 (130, parm1, var2, 0);
#endif
            return;
        }
        else
        {
            L0c2d (var0);       /* L223c */
            var4 = var0->vartyp;
            
            if ((L1440 (_crRight)) || ((var4 == 112) && L22ca (_crRight)))
            {
                L0d04 (_crRight);   /* go to L229b */
            }
            else
            {
#ifdef COCO
                L3292 (122, var4);
#else
                L3292 (122, var4, 0, 0);
#endif
                var0->vartyp = 110;
                L0c2d (_crRight);
                var4 = _crRight->vartyp;
                _crRight = var0;
                parm1 = L249e (parm1);
            }
        }
    }       /* end else => if ! is_regvar... */

    L3292 (129, var4, 119, _crRight); /* L229b... */
L22b2:
#ifdef COCO
    L3292 (130, parm1, var2);
#else
    L3292 (130, parm1, var2, 0);
#endif
}

int
#ifdef COCO
L22ca (cref)
    CMDREF *cref;
#else
L22ca (CMDREF *cref)
#endif
{
    switch (cref->vartyp)
    {
        case C_USRLBL:      /* L22d8 */
        case C_INTSQUOT:
            return 1;
        case C_ASTERISK:    /* L22dd */
            return L14da (cref);
        default:
            return 0;
    }
}

#ifdef COCO
p2_03_notused (parm1, parm2)
    CMDREF *parm1;
    int parm2;
{
    if ((parm1->vartyp == C_USRLBL) &&
                    ((LBLDEF *)(parm1->cmdval)->gentyp == FT_AUTO))
    {
        return 1;
    }

    return 0;
}
#endif

void
#ifdef COCO
L2323 (cref)
    register CMDREF *cref;
#else
L2323 (CMDREF *cref)
#endif
{
    CMDREF *var2;
    int var0 = 0;

    switch (cref->vartyp)
    {                                       /* break = L23fe */
        case C_AND:        /* L2337 */
            if ((((var2 = cref->cr_Right)->vartyp) != C_INTSQUOT) ||
                        ((unsigned int)(var2->cmdval) > (unsigned int)255))
            {
                    var0 = 1;
            }

            break;

        case C_EQUAL:      /* L2353 */
            if ((is_regvar ((cref->cr_Left)->vartyp)) &&
                                ( ! L22ca (cref->cr_Right)))
            {
                var0 = 1;
            }

            break;

        case C_INCREMENT:
        case C_DECREMENT:
        case C_MINMINUS:
        case C_PLUSPLUS:
        case C_PLUSEQ:
        case C_MINEQU:     /* L2371 */
        case C_ANDEQ:
        case C_OREQ:
        case C_EOREQ:
            if ( ! is_regvar ((cref->cr_Left)->vartyp))
            {
                break;
            }
        case C_X_RGWRD:
        case C_RGWRD:
        case C_VBAR:
        case C_CARET:      /* L2380 */
        case C_TILDE:
        case C_MINUS:
        case C_PARENS:
            var0 = 1;
            break;
    }

    D0019 = 0;
    L0d04 (cref);

    switch (cref->vartyp)
    {
        case 113:
        case 112:          /* L240d */
        case C_X_RGWRD:
        case C_RGWRD:
            if (var0 || D0019)
            {
                L3292 (129, cref->vartyp, C_INTSQUOT, 0);
            }

            break;

        case C_CHR2INT:    /* L2427 */
            L3292 (117, 112, 119, (cref = cref->cr_Left));
            break;
        default:           /* L2429 */
            L3292 (117, 112, 119, cref);
            break;
    }
}

int
#ifdef COCO
L2466 (parm1)
    int parm1;
#else
L2466 (int parm1)
#endif
{
    switch (parm1)
    {
        case C_EQEQ:        /* L2472 */
            return C_NOTEQ;
        case C_NOTEQ:       /* L2477 */
            return C_EQEQ;
        default:            /* L247c */
            return (((parm1 > C_GT) ? 195 : 187) - parm1);
    }
}

int
#ifdef COCO
L249e (parm1)
    int parm1;
#else
L249e (int parm1)
#endif
{
    switch (parm1)
    {
        case C_EQEQ:       /* L24aa */
        case C_NOTEQ:      /* L24aa */
            return parm1;
        case C_LT_EQ:      /* L24ae */
        case C_LT:         /* L24ae */
        case 96:           /* L24ae */
        case 97:           /* L24ae */
            return (parm1 + 2);
        default:           /* L24b5 */
            return (parm1 - 2);
    }
}

int
#ifdef COCO
L24e6 (cref)
    register CMDREF *cref;
#else
L24e6 (CMDREF *cref)
#endif
{
    return ((cref->vartyp == C_INTSQUOT) && ( ! cref->cmdval));

    /*if ((cref->vartyp == C_INTSQUOT) && ( ! cref->cmdval))
    {
        return 1;
    }
    else
    {
        return 0;
    }*/
}

void
#ifdef COCO
L2505 (cref)
    CMDREF *cref;
#else
L2505 (CMDREF *cref)
#endif
{
    L2520 (cref);
    L28fb (cref);
}

void
#ifdef COCO
L2520 (cref)
    register CMDREF *cref;
#else
L2520 (CMDREF *cref)
#endif
{
    CMDREF *var4;
    int var2;
    int var0;

    switch (var2 = cref->vartyp)
    {       /* break = L28f7 */
        case 128:          /* L28f7 */
        case 147:          /* L28f7 */
        case 148:          /* L28f7 */
        case 149:          /* L28f7 */
        case C_USRLBL:     /* L28f7 */
            break;
        case C_ASTERISK:   /* L2535 */
            L1953 (cref);
            L152d (cref);

            switch (cref->vartyp)
            {
                case 147:          /* L2547 */
                case 148:          /* L2547 */
                case 149:          /* L2547 */
                    if (cref->cmdval)
                    {
#ifdef COCO
                        L3292 (123, 119, cref);
#else
                        L3292 (123, 119, cref, 0);
#endif
                        cref->vartyp = 147;
                        cref->cmdval = 0;
                    }

                    /* fall through to break */
                default:           /* L28f7 */
                    break;
            }

            break;

        case C_U2LNG:      /* L2577 */
            L0bc3 (cref->cr_Left);
            L3292 (136, C_U2LNG NUL2);
            goto L25bf;
        case C_DBL2LNG:    /* L2586 */
            L29fc (cref->cr_Left);
#ifdef COCO
            L3292 (135, C_DBL2LNG, cref->cr_Left);
#else
            L3292 (135, C_DBL2LNG, cref->cr_Left, 0);
#endif
            goto L25bf;
        case C_I2LNG:      /* L25a5 */
            L0bc3 (cref->cr_Left);
            L3292 (136, C_I2LNG NUL2);
L25bf:
            cref->vartyp = 128;
            break;
        case C_LONG:       /* L25c9 */
#ifdef COCO
            L3292 (136, C_LONG, cref->cmdval);
#else
            L3292 (136, C_LONG, cref->cmdval, 0);
#endif
            L3203 (cref->cmdval, 4);
            goto L27d4;
        case C_QUESTION:   /* L25ea */
            L12e8 (cref, L2505);
            goto L27d4;
        case C_PLUSPLUS:   /* L25f7 */
        case C_MINMINUS:
        case C_TILDE:
        case C_MINUS:
            L2505 (cref->cr_Left);
#ifdef COCO
            L3292 (136, var2);
#else
            L3292 (136, var2, 0, 0);
#endif
            goto L27d4;
        case C_INCREMENT:  /* L2613 */
        case C_DECREMENT:
            L3292 (127, 113, 128, 0);
#ifdef COCO
            L3292 (122, 113);
#else
            L3292 (122, 113, 0, 0);
#endif
            L2505 (cref->cr_Left);
#ifdef COCO
            L3292 (136, var2);
            L3292 (136, 137);
#else
            L3292 (136, var2, 0, 0);
            L3292 (136, 137, 0, 0);
#endif

            L3292 (136, ((var2 == C_INCREMENT) ? C_DECREMENT : C_INCREMENT)
#ifndef COCO
                    , 0, 0
#endif
                  );
            goto L25bf;

        case C_PARENS:     /* L2674 */
            L1364 (cref);
            goto L25bf;
        case C_MULT:       /* L267e */
            if (((cref->cr_Left)->vartyp) == C_LONG)
            {
                CMDREF *_tmpref;

                _tmpref = cref->cr_Left;
                cref->cr_Left = cref->cr_Right;
                cref->cr_Right = _tmpref;
            }

            if (((cref->cr_Right)->vartyp) == C_LONG)       /* L2698 */
            {
                var4 = ((CMDREF *)(cref->cr_Right)->cmdval);

                    /* L26f9 */
                if ( ! (var4->ft_Ty) && (var0 = L121f (var4->__cr2)))
                {
                    L3203 (var4, FT_STRUCT);
                    var4 = cref->cr_Right;
                    var4->cmdval = var0;
                    var4->vartyp = C_INTSQUOT;
                    var4->ft_Ty = FT_INT;
                    var2 = (var2 == C_MULT) ? C_LSHIFT : C_RSHIFT;
                    goto L2733;
                }
            }

            /* fall through to next case */
        case C_SLASH:      /* L26f9 */
        case C_EQEQ:
        case C_NOTEQ:
        case C_GT_EQ:
        case C_LT_EQ:
        case C_GT:
        case C_LT:
        case C_PLUS:
        case C_NEG:
        case C_PERCENT:
        case C_AND:
        case C_VBAR:
        case C_CARET:
            var4 = cref->cr_Left;

            if (var4->vartyp == C_LONG)
            {
                L294b (var4);
            }
            else
            {
                L2505 (var4);
#ifdef COCO
                L3292 (136, 110);
#else
                L3292 (136, 110, 0, 0);
#endif
            }

            L2505 (cref->cr_Right);
#ifdef COCO
            L3292 (136, var2);
#else
            L3292 (136, var2, 0, 0);
#endif
            goto L25bf;
        case C_LSHIFT:     /* L2735 */
        case C_RSHIFT:
L2733:
            L2505 (cref->cr_Left);
#ifdef COCO
            L3292 (122, 113);
#else
            L3292 (122, 113, 0, 0);
#endif
            L0bc3 ( cref->cr_Right);
#ifdef COCO
            L3292 (136, var2);
#else
            L3292 (136, var2, 0, 0);
#endif
            goto L25bf;
        case C_EQUAL:      /* L2769 */
            L2505 (cref->cr_Left);
#ifdef COCO
            L3292 (122, 113);
#else
            L3292 (122, 113, 0, 0);
#endif
            L2505 (cref->cr_Right);
            goto L27c1;

            /* We'll put this here -- don't know at the moment why it was
             * put here, will investigate l8tr
             */
L278e:
            L2505 (var4 = cref->cr_Left);
#ifdef COCO
            L3292 (122, 113);
#else
            L3292 (122, 113, 0, 0);
#endif
            cref->vartyp = var2 - 80;
            var4->vartyp = 147;
            L2520 (cref);
L27c1:
#ifdef COCO
            L3292 (136, 137);
#else
            L3292 (136, 137, 0, 0);
#endif
L27d4:
            cref->vartyp = 147;
            cref->cmdval = 0;
            break;
        default:           /* L27e2 */
            if (var2 >= C_PLUSEQ)
            {
                goto L278e;
            }

            L484b (cref, "longs");
            break;
    }
}

void
#ifdef COCO
L28fb (cref)
    CMDREF *cref;
#else
L28fb (CMDREF *cref)
#endif
{
    switch (cref->vartyp)
    {
        case C_USRLBL:      /* L2909 */
            L3292 (127, 113, 119, cref);
            break;
        case 148:           /* L2923 */
        case 149:
#ifdef COCO
            L3292 (123, 119, cref);
#else
            L3292 (123, 119, cref, 0);
#endif
            break;
    }
}

/* **************************************************************** *
 * L294b () - Deals with longs                                      *
 * **************************************************************** */

void
#ifdef COCO
L294b (cref)
    register CMDREF *cref;
#else
L294b (CMDREF *cref)
#endif
{
    union {
        long *l;
        int *i;
    } _lng;
    
    /* I believe the or'ing in the following simply determines if
     * the variable is not NULL???
     * If so, we can do better with the cross compiler
     */

    _lng.l = (long *)(cref->cmdval);

    if (*(_lng.l))
    {           /* elsee L29aa */
        L3292 (117, 112, C_INTSQUOT, _lng.i[1]);
#ifdef COCO
        L3292 (122, 112);
#else
        L3292 (122, 112, 0, 0);
#endif
        L3292 (117, 112, C_INTSQUOT, _lng.i[0]);    /* go to L29d1 */
    }
    else
    {
        L3292 (117, 112, C_INTSQUOT, 0);
#ifdef COCO
        L3292 (122, 112);
#else
        L3292 (122, 112, 0, 0);
#endif
    }

#ifdef COCO
    L3292 (122, 112);
#else
    L3292 (122, 112, 0, 0);
#endif
    L3203 (_lng.l, 4);
    cref->cmdval = 0;
}
