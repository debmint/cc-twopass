/* ************************************************************************ *
 * p2_02.c - part 2 for c.pass2                                             *
 *                                                                          *
 * $Id: p2_02.c 18 2008-05-19 21:54:22Z dlb $::                                                                   *
 * ************************************************************************ */

#include "pass2.h"

#ifdef COCO
CMDREF *L0d04 (cref);
#endif

void
#ifdef COCO
L0bc3 (cref)
    register CMDREF *cref;
#else
L0bc3 (CMDREF *cref)
#endif
{
    L0c2d (cref);

    if (cref->vartyp != 112)
    {
        L3292 (117, 112, 119, cref);
        cref->vartyp = 112;
    }
}

void
#ifdef COCO
L0bf7 (cref)
    register CMDREF *cref;
#else
L0bf7 (CMDREF *cref)
#endif
{
    L1c1d (cref);

    if (cref->vartyp != 113)
    {
        L3292 (117, 113, 119, cref);
        cref->vartyp = 113;
    }
}

void
#ifdef COCO
L0c2d (cref)
    register CMDREF *cref;
#else
L0c2d (CMDREF *cref)
#endif
{
    switch (cref->ft_Ty)
    {
        case FT_LONG:      /* L0c3b */
            L2505 (cref);
            break;
        case FT_FLOAT:     /* L0c42 */
        case FT_DOUBLE:
            L29fc (cref);
            break;
        default:           /* L0c49 */
            L0d04 (cref);
            L0c6d (cref);
    }
}

void
#ifdef COCO
L0c6d (cref)
    register CMDREF *cref;
#else
L0c6d ( CMDREF *cref)
#endif
{
    switch (cref->vartyp)
    {
        case C_DQUOT:      /* L0c7c */
            L3292 (117, 113, 119, cref);
            cref->vartyp = 113;
            cref->cmdval = 0;
            break;
        case C_AMPERSAND:    /* L0c9e */
            L3292 (127, 113, 119, cref->cr_Left);
            cref->vartyp = 113;
            break;
        case 113:          /* L0d02 */
        case 112:          /* L0d02 */
        case C_RGWRD:      /* L0d02 */
        case C_X_RGWRD:    /* L0d02 */
            break;
        default:           /* L0cbf */
            L3292 (117, 112, 119, cref);
#ifdef COCO
L0cd9:
#endif
            cref->vartyp = 112;
            break;
    }
}

CMDREF *
#ifdef COCO
L0d04 (cref)
    register CMDREF *cref;
#else
L0d04 (CMDREF *cref)
#endif
{
    int _vartype;

    if ((_vartype = cref->vartyp) == C_COMMA)       /* else L0d4d */
    {
        CMDREF *_vrRight = cref->cr_Right;

        L4a69 (L0d04 (cref->cr_Left));
        L4acd (_vrRight, cref);
        L4a8a (_vrRight);
        L0d04 ( cref);      /* go to L0ef7 */
    }
    else
    {
        if (cref->ft_Ty == FT_LONG)
        {
            L2520 (cref);       /* go to L0ef7 */
        }
        else
        {
            if ((cref->ft_Ty == FT_FLOAT) || (cref->ft_Ty == FT_DOUBLE))
            {
                L2a17 (cref);       /* go to L0ef7 */
            }
            else
            {
                if (L4af7 (_vartype))
                {
                    L0efd (_vartype, cref); /* go to L0ef7 */
                }
                else
                {               /* L0d92 */
                    switch (_vartype)
                    {
                        case C_DQUOT:      /* L0ef7 */
                        case C_USRLBL:
                        case C_X_RGWRD:
                        case C_RGWRD:
                        case C_AMPERSAND:
                        case C_INTSQUOT:
                            break;
                        case C_EQUAL:      /* L0d97 */
                            L1567 (cref);
                            break;
                        case C_CHR2INT:    /* L0d9f */
                            L0d04 (cref->cr_Left);
                            break;
                        case C_LNG2INT:    /* L0da9 */
                            L2520 (cref->cr_Left);
#ifdef COCO
                            L3292 (C_LNG2INT, 119, cref->cr_Left);
#else
                            L3292 (C_LNG2INT, 119, cref->cr_Left, 0);
#endif
                            cref->vartyp = 112;
                            break;
                        case C_DBL2INT:    /* L0dc7 */
                            L29fc (cref->cr_Left);
#ifdef COCO
                            L3292 (135, C_DBL2INT);
#else
                            L3292 (135, C_DBL2INT, 0, 0);
#endif
                            cref->vartyp = 112;
                            break;
                        case C_ASTERISK:   /* L0ddf */
                            L1953 (cref);
                            break;
                        case C_EXCLAM:     /* L0de6 */
                        case C_ANDAND:
                        case C_OROR:
                            L124c (cref);
                            break;
                        case C_TILDE:      /* L0ded */
                        case C_MINUS:
                            L0bc3 (cref->cr_Left);
#ifdef COCO
                            L3292 (_vartype);
#else
                            L3292 (_vartype, 0, 0,0);
#endif
                            cref->vartyp = 112;
                            break;
                        case C_QUESTION:    /* L0e01 */
                            L12e8 (cref, L0bc3);
                            cref->vartyp = 112;
                            break;
                        case C_PLUSPLUS:    /* L0e16 */
                        case C_INCREMENT:
                        case C_MINMINUS:
                        case C_DECREMENT:
                            L1a9a (cref, 112);
                            break;
                        case C_PARENS:     /* L0e22 */
                            L1364 (cref);
                            break;
                        default:           /* L0e2c */
                            if (_vartype >= C_PLUSEQ)   /* 160 */
                            {
                                L16cb ( cref, _vartype);
                            }
                            else
                            {
                                L484b (cref, "translation");
                                printf ("%x\n", _vartype);
                            }

                            break;
                    }
                }
            }
        }
    }

    return cref;        /* L0ef7 */
}

void
#ifdef COCO
L0efd (vtyp, cref)
    int vtyp;
    CMDREF *cref;
#else
L0efd (int vtyp, CMDREF *cref)
#endif
{
    /* 6 bytes static vars */
    CMDREF *_rfRt;  /* v4 */
    int v2;
    unsigned int var0;

    register CMDREF *rfLft;
    
    rfLft = cref->cr_Left;
    _rfRt = cref->cr_Right;

    /* First modify vtyp if necessary */

    if (rfLft->ft_Ty == FT_UNSIGNED)
    {
        switch (vtyp)
        {
            case C_SLASH:      /* L0f1d */
                vtyp = 78;
                break;
            case C_PERCENT:    /* L0f22 */
                vtyp = 76;
                break;
            case C_RSHIFT:     /* L0f27 */
                vtyp = 77;
                break;
            default:           /* L0f73 */
                break;
        }
    }
    else
    {
        switch (vtyp)
        {
            case C_PLUS:       /* L0f43 */
            case C_NEG:        /* L0f43 */
                if ((rfLft->vartyp == C_AMPERSAND) && 
                            (_rfRt->vartyp != C_INTSQUOT))
                {
                    L1c1d (cref);
                    D0019 = 0;
                    return;
                }

                break;
        }
    }

    switch (vtyp)
    {                   /* L120d = "break" */
        case C_NEG:        /* L0f78 */
            if ( ! L22ca (_rfRt) )    /* else L0faa */
            {
                L0c2d (_rfRt);
#ifdef COCO
                L3292 (122, _rfRt->vartyp);
#else
                L3292 (122, _rfRt->vartyp, 0, 0);
#endif
                _rfRt->vartyp = 110;
                L0bc3 (rfLft);
            }
            else
            {
                L0bc3 (rfLft);      /* L0faa */
                L0d04 (_rfRt);
            }

            L3292 (C_NEG, 112, 119, _rfRt);
            break; /* go to L120d */
        case C_AND:
        case C_VBAR:
        case C_CARET:        /* L0fce */
        case C_PLUS:
            if ( ((L22ca (rfLft)) && ! (L22ca (_rfRt))) ||
                    (rfLft->vartyp == C_INTSQUOT))
            {
                CMDREF *__tmpref = rfLft;

                rfLft = _rfRt;
                _rfRt = __tmpref;
            }

            if (is_regvar (rfLft->vartyp))      /* L0ff6 */   /* else L1021 */
            {
#ifdef COCO
                L3292 (122, rfLft->vartyp);     /* L1003 */
#else
                L3292 (122, rfLft->vartyp, 0, 0);
#endif
                L0bc3 ( _rfRt);
                _rfRt->vartyp = 110;        /* go to 1052 */
            }
            else
            {
                L0bc3 (rfLft);      /* L1021 */

                if ( ! L22ca (_rfRt))
                {
#ifdef COCO
                    L3292 (122, 112);
#else
                    L3292 (122, 112, 0, 0);
#endif
                    L0bc3 ( _rfRt);
                    _rfRt->vartyp = 110;        /* go to 1052 */
                }
                else
                {
                    L0d04 (_rfRt);      /* L1038 */

                    if (vtyp != C_PLUS)
                    {
                        L152d ( _rfRt);
                    }
                }
            }

            L3292 (vtyp, 112, 119, _rfRt);
            break;
        case C_EQEQ:       /* L106d */
        case C_NOTEQ:
        case C_GT:
        case C_LT:
        case C_LT_EQ:
        case C_GT_EQ:
        case C_U_GT:
        case C_U_LT:
        case C_U_LTEQ:
        case C_U_GTEQ:
            L124c (cref);
            break;
        case 77:           /* L1077 */
        case C_RSHIFT:
        case C_LSHIFT:
            if ((_rfRt->vartyp) == C_INTSQUOT)      /* else L10db */
            {
                var0 = _rfRt->cmdval;
L108b:
                if (var0 <= FT_STRUCT)  /* 4 */     /* else L10db */
                {
                    L0bc3 ( rfLft);

                    while (var0--)
                    {
                        switch (vtyp)
                        {
                            case C_LSHIFT:      /* L10a2 */
#ifdef COCO
                                L3292 (152);
#else
                                L3292 (152, 0, 0, 0);
#endif
                                break;
                            case C_RSHIFT:      /* L10a7 */
#ifdef COCO
                                L3292 (150);
#else
                                L3292 (150, 0, 0, 0);
#endif
                                break;
                            case 77:            /* L10ac */
#ifdef COCO
                                L3292 (151);
#else
                                L3292 (151, 0, 0, 0);
#endif
                                break;
                        }
                    }       /* end while (var0--) (@ L10c5) */ 

                    D0019 = 1;      /* D0019 _may_ be IsStruct, or the like */
                    goto L1213;
                }
                goto L1213;
            }

            goto L1129;
        case C_MULT:       /* L10df */
            if (rfLft->vartyp == C_INTSQUOT)    /* else L10f3 */
            {
                CMDREF *_tmpref;

                _tmpref = rfLft;
                rfLft = _rfRt;
                _rfRt = _tmpref;
            }       /* fall through to next case */
        case 78:           /* L10f3 */
            if ((_rfRt->vartyp == C_INTSQUOT) &&
                        (var0 = L121f ( _rfRt->cmdval)))    /* else L112b */
            {
                _rfRt->cmdval = var0;

                vtyp = (vtyp == C_MULT) ? C_LSHIFT : 77;    /* L1122 */
                goto L108b;
            }
        case C_SLASH:      /* L112b */
        case 76:           /* L112b */
        case C_PERCENT:    /* L112b */
L1129:
            L0c2d (rfLft);
#ifdef COCO
            L3292 (122, rfLft->vartyp);
#else
            L3292 (122, rfLft->vartyp, 0, 0);
#endif
            L0bc3 ( _rfRt);
#ifdef COCO
            L3292 (vtyp);
#else
            L3292 (vtyp, 0, 0, 0);
#endif
            break;
        default:           /* L1155 */
            L484b (cref, "binary op.");
            break;
    }   /* end switch vtyp */

#ifdef COCO
    /* Following jump-label is not needed - vestige from the old source */
L120d:
#endif
    D0019 = 0;
L1213:
    cref->vartyp = 112;
}

int
#ifdef COCO
L121f (cmd_val)
    int cmd_val;
#else
L121f (int cmd_val)
#endif
{
    register int _count = 0;

    while (_count < 14)
    {
        if ( dpsz[_count++] == cmd_val)
        {
            return _count;
        }
    }

    return 0;
}

void
#ifdef COCO
L124c (cref)
    register CMDREF *cref;
#else
L124c (CMDREF *cref)
#endif
{
    int var2;
    int var0;

    L1f13 (cref, (var2 = ++D000b), (var0 = ++D000b), 1);
    L4414 (var2);
    L3292 (117, 112, C_INTSQUOT, 1);

#ifdef COCO
    L3292 (124, (var0 = ++D000b), 1);
#else
    L3292 (124, (var0 = ++D000b), 1, 0);
#endif
    L4414 (var0);

    L3292 (117, 112, C_INTSQUOT, 0);
    L4414 (var2);
    cref->vartyp = 112;
}

void
#ifdef COCO
L12e8 (cref, fnc)
    register CMDREF *cref;
    void (*fnc)();
#else
L12e8 (CMDREF *cref, void (*fnc)())
#endif
{
    int var4;
    int var2;
    int var0;

    L1f13 (cref->cr_Left, (var4 = ++D000b), (var0 = ++D000b), 1);
    cref = cref->cr_Right;
    L4414 (var4);
    (*fnc) (cref->cr_Left);
#ifdef COCO
    L3292 (124, (var4 = ++D000b), 0);
#else
    L3292 (124, (var4 = ++D000b), 0, 0);
#endif
    L4414 (var0);
    (*fnc) (cref->cr_Right);
    L4414 (var2);
}
void
#ifdef COCO
L1364 (cref)
    CMDREF *cref;
#else
L1364 (CMDREF *cref)
#endif
{
    CMDREF *var2;
    int var0;

    var0 = D000d;
    var2 = cref;

    while (var2 = var2->cr_Right)
    {
        register CMDREF *regptr = var2->cr_Left;    /* L1379 */;

        if (regptr->ft_Ty == FT_LONG)     /* else L13a8 */
        {
            if (regptr->vartyp == C_LONG)
            {
                L294b (regptr);  /* go to L1401 */
                continue;
            }
            else
            {
                L2505 (regptr);
#ifdef COCO
                L3292 (136, 110);
#else
                L3292 (136, 110, 0, 0);
#endif
                continue;
            }
        }
        else
        {       /* L13a8 */
            if ((regptr->ft_Ty == FT_FLOAT) || (regptr->ft_Ty == FT_DOUBLE))
            {
                L29fc (regptr);
#ifdef COCO
                L3292 (135, 110);
#else
                L3292 (135, 110, 0, 0);
#endif
            }
            else
            {
                L0d04 (regptr);

                switch (regptr->vartyp)
                {
                    case 112:          /* L13f3 */
                    case 113:
                    case C_RGWRD:
                    case C_X_RGWRD:
                        break;
                    default:           /* L13d4 */
                        L0c6d (regptr);
                        break;
                }

                L3292 (122, regptr->vartyp NUL2);
            }

        }
    }       /* end while (var2 = cr->right)  ( L1401 ) */

    L0d04 (cref->cr_Left);
#ifdef COCO
    L3292 (C_PARENS, 119, cref->cr_Left);
#else
    L3292 (C_PARENS, 119, cref->cr_Left, 0);
#endif
    D000d = prt_rsrvstk (var0);
    cref->vartyp = 112;
}


int 
#ifdef COCO
L1440 (cref)
    register CMDREF *cref;
#else
L1440 (CMDREF *cref)
#endif
{
    CMDREF *var0;

    switch (cref->vartyp)
    {
        case C_USRLBL:     /* L145a */
        case C_INTSQUOT:
            return 1;
        case C_ASTERISK:   /* L1450 */
            switch ((var0 = cref->cr_Left)->vartyp)
            {
                case C_INTSQUOT:   /* L145a */
                case C_USRLBL:
                case C_X_RGWRD:
                case C_RGWRD:
                    return 1;
                default:           /* L145f */
                    return L149e (var0);
            }
    }

    return 0;
}

int 
#ifdef COCO
L149e (cref)
    register CMDREF *cref;
#else
L149e (CMDREF *cref)
#endif
{
    switch (cref->vartyp)
    {
        case C_PLUS:       /* L14ac */
        case C_NEG:        /* L14ac */
            if ((is_regvar ((cref->cr_Left)->vartyp)) &&
                    ((cref->cr_Right)->vartyp == C_INTSQUOT))
            {
                return 1;
            }

    }

    return 0;
}

int 
#ifdef COCO
L14da (cref)
    register CMDREF *cref;
#else
L14da (CMDREF *cref)
#endif
{
    return (cref->__cr18 < FT_CHAR);
}

int 
#ifdef COCO
L14f2 (cref)
    register CMDREF *cref;
#else
L14f2 (CMDREF *cref)
#endif
{
    switch (cref->vartyp)
    {
        case C_PLUS:       /* L1500 */
        case C_NEG:        /* L1500 */
            return ((cref->cr_Left)->vartyp == C_AMPERSAND);
        case C_DQUOT:      /* L150a */
        case C_AMPERSAND:  /* L150a */
            return 1;
    }

    return 0;
}

void 
#ifdef COCO
L152d (cref)
    register CMDREF *cref;
#else
L152d (CMDREF *cref)
#endif
{
    if (cref->vartyp & 0x8000)
    {
        cref->vartyp &= 0x7fff;
    }

    L3292 (117, 113, 119, cref);
    cref->vartyp = 147;
    cref->cmdval = 0;
}

void 
#ifdef COCO
L1567 (cref)
    CMDREF *cref;
#else
L1567 (CMDREF *cref)
#endif
{
    int var2;
    CMDREF *var0;

    register CMDREF *regptr;

    var0 = cref->cr_Right;
    regptr = cref->cr_Left;

    if (is_regvar ((cref->cr_Left)->vartyp))        /* else L15fd */
    {
        if (L149e (var0))
        {
            L1c1d (var0);
        }
        else
        {
            L0d04 (var0);
        }

        switch (var0->vartyp)
        {
            case C_AMPERSAND:  /* L15ab */
                L3292 (127, regptr->vartyp, 119, var0->cr_Left); /* jump to L1794 */
                break;
            case C_CHR2INT:    /* L15bf */
                L3292 (117, 112, 119, var0);
                /* fall through to default */
            default:           /* L15d7 */
                L3292 (117, regptr->vartyp, 119, var0);
                break;
        }

        cref->vartyp = regptr->vartyp;    /* L1794 */
        cref->cmdval = 0;
        return;
    }

    if ((L1440 (regptr)) && (regptr->ft_Ty == FT_CHAR)) /* L15fd */ /* else L1635 */
    {
        if ((L149e (var0)) || ( L14f2 (var0)))      /* else L1635 */
        {
            L0d04 (regptr);
            L1be4 (var0);
            return;       /* L16ab */
        }
    }

    /* L1635 */
    if (is_regvar (var0->vartyp))   /* else L165c */
    {
        L0d04 (regptr);

        if (regptr->ft_Ty == FT_CHAR)       /* else L16ad */
        {
            L0bc3 (var0);
            return;
        }
    }

    if (L14da (regptr))
    {
        L0bc3 (var0);
        return;
    }

    L0d04 (regptr);     /* L1675 */

    if ( ! L1440 (var0))
    {
        switch (regptr->vartyp & 0x7fff)
        {
            case 149:       /* L16a4 */
            case 148:
                break;
            default:        /* LL168f */
                L1904 (regptr);
                break;
        }
    }

    L3292 (122, var0->vartyp, 119, regptr);     /* L16a4 */
    cref->vartyp = var0->vartyp;                /* L1796 */
    cref->cmdval = 0;
    return;         /* L1a96 */
}

void
#ifdef COCO
L16cb (cref, vartype)
    CMDREF *cref;
    int vartype;
#else
L16cb (CMDREF *cref, int vartype)
#endif
{
    CMDREF *var2;
    int var0;
    register CMDREF *regptr;

    var2 = cref->cr_Right;
    regptr = cref->cr_Left;
    L0d04 (regptr);
    vartype -= 80;      /* This may go back to the \*= thing in p1_08.c */

    if (regptr->ft_Ty == FT_UNSIGNED)   /* else L1719 */
    {
        switch (vartype)
        {
            case C_SLASH:      /* L16f9 */
                vartype = 78;
                break;
            case C_RSHIFT:     /* L16fe */
                vartype = 77;
                break;
            case C_PERCENT:    /* L1703 */
                vartype = 76;
                break;
        }
    }

    if (var0 = (regptr->vartyp & 0x7fff))       /* else L17ef */
    {
        switch (vartype)
        {
            case C_PLUS:       /* L172f */
            case C_NEG:        /* L172f */
                if (var2->vartyp == C_INTSQUOT)     /* else L1766 */
                {
                    L3292 (116, var0, C_INTSQUOT,
                            (vartype == C_PLUS) ? var2->cmdval :
                                                  -(var2->cmdval));
                }
                else
                {
                    L0bc3 (var2);

                    if (vartype == C_NEG)
                    {
#ifdef COCO
                        L3292 (C_MINUS);
#else
                        L3292 (C_MINUS, 0, 0, 0);
#endif
                    }

#ifdef COCO
                    L3292 ( 116, var0, 112);
#else
                    L3292 ( 116, var0, 112, 0);
#endif
                }

                cref->vartyp = regptr->vartyp;  /* L1794 */
                cref->cmdval = 0;
                return;
            case C_AND:        /* L17a3 */
            case C_VBAR:
            case C_CARET:
                goto L17ed;
            default:           /* L17a7 */
                L3292 (122, regptr->vartyp NUL2);
                L0bc3 (var2);
                L3292 (vartype NUL3);
                break;  /* go to L18e4 */
        }
    }
    else
    {
L17ed:
        L3292 (117, 112, 119 NUL1);
        
        if (cref->ft_Ty == FT_CHAR)
        {
            L3292 (133 NUL3);
        }

        switch (vartype)
        {
            case C_AND:        /* L181c */
            case C_VBAR:
            case C_CARET:
            case C_PLUS:
            case C_NEG:
                if (L1440 (var2))   /* else L186d (default) */
                {
                    L0d04 (var2);

                    switch (vartype)
                    {
                        case C_AND:        /* L1834 */
                        case C_VBAR:
                        case C_CARET:
                            L152d (var2);
                            break;
                    }

                    L3292 (vartype, 112, 119, var2);
                    break;
                }
                /* Fall through to default */
            default:           /* L186d */
                if ((var0 != 148) && (var0 != 149))
                {
                    L1904 (regptr);
                }

                L3292 (122, 112 NUL2);
                L0bc3 (var2);

                if (vartype == C_NEG)
                {
                    vartype = 79;
                }

                L3292 (vartype, 112, 110 NUL1);
                break;
        }           /* end switch */
    }           /* end else = (regptr->vartyp & 0x7fff) == 0  */

    /* L18e4 */
    L3292 (121, 112, 119 NUL1);
    cref->vartyp = 112;
}

void
#ifdef COCO
L1904 (cref)
    register CMDREF *cref;
#else
L1904 (CMDREF *cref)
#endif
{
    if (cref->vartyp != C_USRLBL)
    {
        L152d (cref);

        if (cref->cmdval)
        {
            L3292 (116, 113, C_INTSQUOT, cref->cmdval);
        }

        L3292 (122, 113 NUL2);
        cref->vartyp = -32621;  /*0x806e;*/  /* wonder what this means? */
    }
}

void
#ifdef COCO
L1953 (cref)
    register CMDREF *cref;
#else
L1953 (CMDREF *cref)
#endif
{
    CMDREF *var2;
    int var0;

    L1c1d (var2 = cref->cr_Left);

    if ((var0 = var2->vartyp) & 0x8000)     /* else L19d7 */
    {
        switch (var0 &= 0x7fff)
        {
            case C_USRLBL:     /* L1983 */
            case 147:
            case 148:
            case 149:
                L3292 (117, 113, var0, var2->cmdval);
                break;
            default:           /* L199e */
                L484b (var2, "indirection");
                break;
        }

        var0 = -32621;   /* ??? */       /* L19cb */
        cref->cmdval = 0;
        /* go to L1a92 */
    }
    else
    {                /* L19d7 */
        switch (var0)
        {
            case C_RGWRD:      /* L19dc */
                var0 = 149;
                goto L1a04;
            case C_X_RGWRD:    /* L19e1 */
                var0 = 148;
                goto L1a04;
            case 113:          /* L19e6 */
                var0 = 147;
                goto L1a04;
            case 147:          /* L19eb */
            case 148:
            case 149:
                var0 |= 0x80ff;
                goto L1a04;
            case C_USRLBL:     /* L19f5 */
                var0 = -32716;  /* -32716 */
                cref->cr_Nxt = var2->cr_Nxt;
L1a04:
                cref->cmdval = var2->cmdval;
                break;
            case 112:          /* L1a0c */
                L3292 (117, 113, 119, var2);
                var0 = 147;
                cref->cmdval = 0;
                break;
            case C_INTSQUOT:   /* L1a2f */
                cref->cmdval = 0;
                cref->cr_Nxt = var2->cmdval;
                var0 = C_USRLBL;
                break;
            default:           /* L1a3f */
                L484b (cref, "indirection");
                var0 = 147;
                break;
        }
    }       /* end else i.e. var2->vartyp) & 0x8000 == 0 */

    /* L1a92 */
    cref->vartyp = var0;
}

void
#ifdef COCO
L1a9a (cref, val)
    CMDREF *cref;
    int val;
#else
L1a9a (CMDREF *cref, int val)
#endif
{
    /* 8 bytes static storage */
    int var6;
    int var4;
    int var2;
    int var0;
    register CMDREF *_leftref;

    _leftref = cref->cr_Left;

    L0d04 (_leftref);
    var2 = cref->vartyp;
    
    if (is_regvar (var0 = _leftref->vartyp))        /* else L1afa */
    {
        switch (var2)
        {
            case C_INCREMENT:
            case C_DECREMENT:
                if (val == 112)     /* else L1ae6 */
                {
                    L3292 (117, val, 119, _leftref);
                    break;
                }
            default:
                val = var0;
                break;      /* go to L1b2b */
        }
    }
    else
    {
        if ((val == 113) && ((var0 & 0x7fff) == C_USRLBL))     /* L1afa */
        {
            val = 112;
        }
        
        L3292 (117, val, 119, _leftref);
        var0 = val;
    }

    var6 = cref->cmdval;        /* L1b2b */

    switch (var2)
    {
        case C_MINMINUS:        /* L1b35 */
        case C_DECREMENT:
            var6 = -var6;

        default:                /* L1b3d */
            if (var0 == 112)
            {
                L3292 ( C_PLUS, var0, C_INTSQUOT, var6);
                break;
            }
            L3292 (116, var0, C_INTSQUOT, var6);
            break;
    }

    L3292 (121, var0, 119, _leftref);

    switch (var2)
    {
        default:                /* L1b97 */
            cref->cmdval = 0;
            break;
        case C_INCREMENT:       /* L1b9b */
        case C_DECREMENT:
            if (var0 == 112)
            {
                L3292 (C_NEG, 112, C_INTSQUOT, var6);
            }
            else
            {
                cref->cmdval = -var6;
            }
            break;
    }

    cref->vartyp = val;
    D0019 = 0;
}

void
#ifdef COCO
L1be4 (cref)
    register CMDREF *cref;
#else
L1be4 (CMDREF *cref)
#endif
{
    L1c1d (cref);

    if ((cref->vartyp != 113) || (cref->cmdval != 0))    /* else L1c16 */
    {
        L3292 (117, 113, 119, cref);
    }

    cref->vartyp = 113;
}

void
#ifdef COCO
L1c1d (cref)
    CMDREF *cref;
#else
L1c1d (CMDREF *cref)
#endif
{
    CMDREF *var6;
    int var4;
    int var2;
    int var0;

    register CMDREF *_crleft;

    _crleft = cref->cr_Left;
    var6 = cref->cr_Right;
    var0 = 113;
    
    switch (var2 = cref->vartyp)
    {
        case C_ASTERISK:   /* L1c41 */
            L1953 (cref);
            return;
        case C_USRLBL:     /* L1eaf */
        case C_X_RGWRD:
        case C_RGWRD:
        case C_INTSQUOT:
        case C_DQUOT:
            return;
        case C_INCREMENT:  /* L1c4b */
        case C_PLUSPLUS:
        case C_MINMINUS:
        case C_DECREMENT:
            L1a9a (cref, 113);
            return;
        case C_AMPERSAND:  /* L1c5c */
            L3292 (127, 113, 119, cref);
            cref->cmdval = 0;
            break;
        case C_CHR2INT:    /* L1c77 */
            L0bc3 (cref);
            return;
        case C_NEG:        /* L1c81 */
            if ((_crleft->vartyp != C_AMPERSAND) && (var6->__cr18))
            {                                   /* go to L1d30 */
                goto L1e42;
            }
                /* Is this correct????  */
        case C_PLUS:       /* L1c92 */
            if ((is_regvar (_crleft->vartyp)) || (_crleft->vartyp == C_AMPERSAND))
            {       /* else L1cf9 */
                if (var6->vartyp == C_INTSQUOT)   /* L1ca5 */ /* else L1cc1 */
                {
                    L1c1d (_crleft);
                    var0 = _crleft->vartyp;
                    var4 = var6->cmdval;
                    
                    /* jump to L1e26 */

                    /*if (var2 == C_PLUS)
                    {
                        _crleft->cmdval += var4;
                    }
                    else
                    {
                        _crleft->cmdval -= var4;
                    }

                    break;*/
                }
                else
                {
                    L0bc3 (var6);       /* L1cc1 */
                    L1c1d (_crleft);

                    if (var2 == C_NEG)      /* else L1ce3 */
                    {
#ifdef COCO
                        L3292 (C_MINUS);
#else
                        L3292 (C_MINUS, 0, 0, 0);
#endif
                    }

#ifdef COCO
                    L3292 (123, 112, _crleft->vartyp);      /* L1ce3 */
#else
                    L3292 (123, 112, _crleft->vartyp, 0);
#endif
                    var4 = 0;
                }
            }
            else
            {                    /* L1cf9 */
                if ((var2 == C_PLUS) && (_crleft->__cr18 < var6->__cr18))
                {
                    CMDREF *_tmpref = _crleft;

                    _crleft = var6;
                    var6 = _tmpref;
                }

                if ( ! L1440 (var6))        /* L1d18 */     /* else L1d35 */
                {
                    if ( ! is_regvar (var6->vartyp))
                    {
                        goto L1e42;
                    }
                }

                L1c1d (_crleft);        /* L1d35 */

                switch (_crleft->vartyp & 0x7fff)
                {
                    case 112:          /* L1d45 */
                        if ((var2 == C_PLUS) &&     /* else L1d69 */
                                (var6->vartyp == C_INTSQUOT))
                        {
                            L0bf7 (var6);
                            _crleft->cmdval = 0;
                            goto L1e0a;
                        }


                    case C_USRLBL:
                    case C_DQUOT:
                    case 147:          /* L1d69 */
                    case 148:
                    case 149:
                        L3292 (117, 113, 119, _crleft);
                        _crleft->cmdval = 0;
                        break;
                    case 113:          /* L1dd5 */
                        break;
                    case C_X_RGWRD:    /* L1d85 */
                    case C_RGWRD:
                        var0 = _crleft->vartyp;
                        break;
                    default:           /* L1d8b */
                        L484b ( _crleft, "x translate");
                        break;
                }

                if (var6->vartyp == C_INTSQUOT)     /* L1dd5 */
                {
                    var4 = var6->cmdval;
                }
                else
                {
                    L0bc3 (var6);
                    
                    if (var2 == C_NEG)  /* else L1e0c */
                    {
#ifdef COCO
                        L3292 (C_MINUS, 0, 0);
#else
                        L3292 (C_MINUS, 0, 0, 0);
#endif
                    }

L1e0a:
#ifdef COCO
                    L3292 (123, 112, var0);
#else
                    L3292 (123, 112, var0, 0);
#endif
                    var0 = 113;
                    var4 = 0;
                }
            }

                /* L1e26 */
            /*if (var2 == C_PLUS)
            {
                cref->cmdval = _crleft->cmdval + var4;
            }
            else
            {
                cref->cmdval = _crleft->cmdval - var4;
            }*/
            cref->cmdval = _crleft->cmdval + ((var2 == C_PLUS) ? var4 : -var4);
            
            break;
        default:           /* L1e44 */
L1e42:
            L0d04 (cref);
            return;
    }

    cref->vartyp = var0;    /* L1ea9 */
}

int
#ifdef COCO
is_regvar (vtyp)
    int vtyp;
#else
is_regvar (int vtyp)
#endif
{
    return ((vtyp == C_RGWRD) || (vtyp == C_X_RGWRD));
}
