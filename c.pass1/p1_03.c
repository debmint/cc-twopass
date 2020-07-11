/* ************************************************************** *
 * pass1_03.c                                                     *
 * ************************************************************** */

/* $Id: p1_03.c 18 2008-05-19 21:54:22Z dlb $ */

#include "pass1.h"

CMDREF *
#ifndef COCO
L0f18 (register CMDREF *curntcmd)
#else
L0f18 (curntcmd)
    register CMDREF *curntcmd;
#endif
{
    /* 12 bytes stack */
    CMDREF *_cmdLeft;
    CMDREF *_cmdRight;
    int v6;
    int _varty;
    CMDREF *_cLeft_cRight;
    int v0;

    if (curntcmd)    /* else L0fff */
    {
        curntcmd->cr_Left = L0f18 (curntcmd->cr_Left);
        curntcmd->cr_Right = L0f18 (curntcmd->cr_Right);
        curntcmd = L1382 (curntcmd);

        /* L1323 is an "is<something>" */
        if (L1323 (curntcmd))
        {
            /*goto L0ffd;*/
            return curntcmd;
        }

        curntcmd = L1005 (curntcmd);        /* L0f56 */
        _cmdLeft = curntcmd->cr_Left;
        _cmdRight = curntcmd->cr_Right;
        
        if (((_varty = curntcmd->vartyp) == C_QUESTION) &&
                            (_cmdLeft->vartyp == C_INTSQUOT))   /* else L0fb4 */
        {
            if (_cmdLeft->cmdval)      /* else L0fd8 */
            {
                _cLeft_cRight = _cmdRight->cr_Left;
                L0393 (_cmdRight->cr_Right);
            }
            else
            {
                _cLeft_cRight = _cmdRight->cr_Right;       /* L0fd8 */
                L0393 (_cmdRight->cr_Left);
            }

            release (_cmdRight);
            release (_cmdLeft);
            release (curntcmd);
        }
        else
        {            /* L0fb4 */
            if ((_varty != C_ASTERISK) || (_cmdLeft->vartyp != C_AMPERSAND))
            {
                if ((_varty != C_AMPERSAND) || (_cmdLeft->vartyp != C_ASTERISK))
                {
                    /* not "**", "*&", "&*" or "&&" */
                    return curntcmd;
                }
            }

            _cLeft_cRight = _cmdLeft->cr_Left;      /* L0fd8 */
            _cLeft_cRight->ft_Ty = curntcmd->ft_Ty;
            _cLeft_cRight->__cr2 = curntcmd->__cr2;
            release (curntcmd);
            release (_cmdLeft);
        }
        curntcmd = _cLeft_cRight;      /* L0ff4 */
    }

L0ffd:
    return curntcmd;
}

CMDREF *
#ifndef COCO
L1005 (register CMDREF *regptr)
#else
L1005 (regptr)
    register CMDREF *regptr;
#endif
{
    CMDREF *_prevCMD;
    CMDREF *_cmdcr_Right;
    CMDREF *v8;
    int _curvartyp;
    int v4;
    int _prevvartyp;
    int _is_INT;

    if (!regptr)
    {
        return 0;
    }

    _prevCMD = regptr->cr_Left;      /* L101a */
    _cmdcr_Right = regptr->cr_Right;
    
    if (isbin (_curvartyp = regptr->vartyp) ||
                        (_curvartyp == C_ANDAND) || (_curvartyp == C_OROR))
    {                                       /* else L1258 */
        if ((_prevvartyp = (_prevCMD->vartyp == C_INTSQUOT)) &
                        (_is_INT = (_cmdcr_Right->vartyp == C_INTSQUOT) )) /* L1041 */
        {
            goto L1269;
        }

        if (_prevvartyp)     /* L1076 */     /* else L10b6 */
        {
            switch (_curvartyp)
            {
                case C_PLUS: /* L107e */    /* _44 */
                case C_MULT:  /* L107e */
                case C_AND:  /* L107e */
                case C_VBAR: /* L107e */
                case C_CARET: /* L107e */
                    v8 = _prevCMD;
                    regptr->cr_Left = _prevCMD = _cmdcr_Right;
                    regptr->cr_Right = _cmdcr_Right = v8;
                    _is_INT = 1;
                    break;
            }
        }

        switch (_curvartyp)
        {
            case C_VBAR:    /* L10bb (_51) */
            case C_CARET:   /* L10bb */
                if ((_is_INT) && !(_cmdcr_Right->cmdval))
                {
                    goto L10f7;
                }

                return regptr;
            case C_PLUS:    /* L10cc (_60) */
                if (!_is_INT)
                {
                    return regptr;
                }

                if (!(_cmdcr_Right->cmdval))
                {
                    goto L10f7;
                }

                switch (_prevCMD->vartyp)
                {
                    case C_AMPERSAND:   /* L10e1 */
                        (_prevCMD->cr_Left)->cr_Nxt += _cmdcr_Right->cmdval;
L10f7:
                        v8 = _prevCMD;
                        release (regptr);
                        release (_cmdcr_Right);
                        regptr = v8;
                        return regptr;
                    case C_PLUS:        /* L1112 */
                        if ((_prevCMD->cr_Right)->vartyp == C_INTSQUOT)
                        {
                            ((_prevCMD->cr_Right)->cmdval) += _cmdcr_Right->cmdval;
                            goto L10f7;
                        }

                        return regptr;
                    default:            /* L131d */
                        return regptr;
                }
            case C_NEG:     /* L1142 ( _71 ) */
                if (_is_INT)
                {
                    _cmdcr_Right->cmdval = -(_cmdcr_Right->cmdval);
                    regptr->vartyp = C_PLUS;
                    return (L1005 (regptr));
                }

                if (_prevvartyp)    /* L1161 */
                {
                    if (!_prevCMD->cmdval)
                    {
                        regptr->vartyp = C_MINUS;
                        regptr->cr_Left = _cmdcr_Right;
                        regptr->cr_Right = 0;
                        release (_prevCMD);
                    }
                }

                return regptr;
            case C_AND:     /* L1181 */
                if ((_is_INT) && !(_cmdcr_Right->cmdval))
                {
                    goto L11fe;
                    /*return 0;*/
                }
                else
                {
                    return regptr;
                }

            case C_MULT:     /* _97  (L1190) */
                if (!_is_INT)
                {
                    return regptr;
                }

                switch (_cmdcr_Right->cmdval)
                {
                    case 0:         /* L119c ( _106 ) */
                        goto L11fe;
                    default:        /* L11a1 */
                        if ((_prevCMD->vartyp != C_MULT) ||
                                    ((_prevCMD->cr_Right)->vartyp != C_INTSQUOT))
                        {
                            return regptr;
                        }

                        (_prevCMD->cr_Right)->cmdval *= _cmdcr_Right->cmdval;
                        /* Fall through to next case */
                    case 1:         /* L11e9 ( _113 ) */
                        goto L10f7;
                }
            case C_SLASH:   /* L11db ( _104 ) */
                if (_is_INT && (_cmdcr_Right->cmdval == 1))
                {
                    goto L10f7;
                }

                if (_prevvartyp && !(_prevCMD->cmdval))   /* L11ee */
                {
L11fe:
                    regptr->vartyp = C_INTSQUOT;    /* _96 or _122 */
                    regptr->cmdval = 0;   /* L1207 (storing some value here) */
                    regptr->cr_Left = regptr->cr_Right = (CMDREF *)0;
                    release (_prevCMD);
                    release (_cmdcr_Right);
                }

                break;
        }           /* end switch (_curvartype) */

        return regptr;      /* L131d */
    }

    /* L1258 */
    switch (_curvartyp)     /* L1308 ( _124 ) */
    {
        case C_EXCLAM: /* L125d ( _125 ) */
        case C_TILDE: /* L125d */
        case C_MINUS: /* L125d */
            if (_prevCMD->vartyp == C_INTSQUOT)     /* else L128d */
            {
L1269:
                regptr->vartyp = C_INTSQUOT;
                regptr->__cr18 = 0;
#ifdef COCO
                regptr->cmdval = do_math (_curvartyp, _prevCMD->cmdval, _cmdcr_Right->cmdval);
#else
                /* I believe making parm3 0 will work.  do_math doesn't
                 * appear to use it for these three cases
                 */
                /* Didn't work... it  trying "if" now... */

                regptr->cmdval = do_math (_curvartyp, _prevCMD->cmdval,
                                      _cmdcr_Right ? _cmdcr_Right->cmdval : 0);
#endif
                /* bra L1207 */
                regptr->cr_Left = regptr->cr_Right = (CMDREF *)0;
                release (_prevCMD);
                release (_cmdcr_Right);
                /*return regptr;*/
                /*break;*/  /* Don't need if following else works */
            }
            else
            {
            /* L128d */
            if (_prevCMD->vartyp == C_LONG)      /* else L12dc */
            {
                long *lngptr;

                if (!(lngptr = _prevCMD->cmdval))    /* else L12ad */
                {
                    lngptr = addmem (sizeof (long));
                }

                switch (_curvartyp)
                {
                    case C_MINUS:   /* L12b1 */
                        *lngptr = -(*lngptr);
                        break;
                    case C_TILDE:   /* L12bc */
                        *lngptr = ~(*lngptr);
                        break;
                }

                _prevCMD->cmdval = (int)lngptr;   /* go to L12fc */
                /* The following would work after the outer block,
                 * but trying to match code
                 */
            release (regptr);      /* L12fc */
            regptr = _prevCMD;
            }
            else
            {
                if (_prevCMD->vartyp == C_DOUBLE)        /* L12dc */
                {
                    double *dptr;

                    if (dptr = (double *)(_prevCMD->cmdval))     /* else L12fc */
                    {
                        *dptr = -(*dptr);
                    }
            release (regptr);      /* L12fc */
            regptr = _prevCMD;
                }
            }
            }   /* Inserted else at L128d */

            /*return regptr;*/
    }

    return regptr;
}

int
#ifndef COCO
L1323 (register CMDREF *regptr)
#else
L1323 (regptr)
    register CMDREF *regptr;
#endif
{
    if (regptr)
    {
        switch (regptr->vartyp)
        {
            case C_X_RGWRD:  /* L1335 */
            case C_RGWRD:  /* L1335 */
            case C_INTSQUOT: /* L1335 */
            case C_LONG: /* L1335 */
            case C_DOUBLE: /* L1335 */
            case C_USRLBL:  /* L1335 */
            case C_DQUOT: /* L1335 */
                return 1;
        }
    }

    return 0;
}

void
divby_0 ()
{
    reprterr ("divide by zero");
}

CMDREF *
#ifndef COCO
L1382 ( CMDREF *oldref)
#else
L1382 (oldref)
CMDREF *oldref;
#endif
{
    CMDREF *v18;
    CMDREF *v16;
    int v14;
    int _t_ft_Ty;
    int _t__cr2;
    int _t_cr_18;
    int _t__cr4;
    int v4;
    int v2;
    int v0;
    register CMDREF *regptr = oldref->cr_Left;

    v18 = oldref->cr_Right;
    _t_cr_18 = _t__cr2 =  2;
    _t__cr4 = 0;
    _t_ft_Ty = 1;
    
    switch (v14 = oldref->vartyp)
    {
        case C_USRLBL:         /* L13b6 */
            v16 = oldref->cmdval;
            
            if (v16->cmdval == FT_TYPEDEF)    /* else L13e6 */
            {
                terror (oldref, "typedef - not a variable");
                L25e6 (oldref);
                break;
            }

            _t_ft_Ty = v16->ft_Ty;      /* L13e6 */
            _t__cr4 = v16->__cr4;

            if ((_t_ft_Ty & 15) == 10)     /* else L1427 */
            {
                CMDREF *loc;

                loc = v16->__cr2;
                _t_ft_Ty = v16->ft_Ty = (_t_ft_Ty & 0xfff0) + loc->ft_Ty;
                L4100 (v16, _t__cr4, loc->__cr2);
            }

            _t__cr2 = v16->__cr2;

            if ((inbraces (_t_ft_Ty)) || (inparentheses (_t_ft_Ty))) /*else L14a9*/
            {
                regptr = oldref;
                regptr->__cr2 = _t__cr2;
                oldref = add_cmdref (C_AMPERSAND, regptr, 0, 0,
                                oldref-> _cline, oldref->_lpos);

                if (inbraces (_t_ft_Ty))       /* else L1494 */
                {
                    _t__cr4 = L04b0 (_t__cr4);
                    _t_ft_Ty = incref (regptr->ft_Ty = decref (_t_ft_Ty));
                }
                else
                {
                    _t_ft_Ty = incref (regptr->ft_Ty = _t_ft_Ty);
                }

                regptr->__cr18 = 1;
            }
            else
            {
                switch (v4 = v16->cmdval)      /* L14a9 */
                {
                    case C_X_RGWRD:
                    case C_RGWRD:       /* L14b4 */
                        oldref->vartyp = v4;
                        oldref->cmdval = 0;
                        break;
                }

            }

            _t_cr_18 = 1;        /* L14d0 */
            break;
        case C_INTSQUOT:    /* L14d5 */
            _t_cr_18 = 0;
            break;
        case C_LONG:        /* _182 */      /* L14dc */
            _t_ft_Ty = FT_LONG;
            _t_cr_18 = 1;
            _t__cr2 = LONGSIZ;
            break;
        case C_DOUBLE:      /* L14ec */
            _t_ft_Ty = FT_DOUBLE;
            _t_cr_18 = 1;
            _t__cr2 = DBLSIZ;
            break;
        case C_DQUOT:       /* L14fc */
            _t_ft_Ty = FT_RETURN;
            _t__cr2 = CHARSIZ;
            break;
        case 0x20:         /* L1507 */
            ck_declared (regptr);

            if ((inparentheses (_t_ft_Ty = oldref->ft_Ty)) ||
                        (inbraces (_t_ft_Ty)))
            {
                terror (oldref, "cannot cast");
                _t_ft_Ty = incref (_t_ft_Ty);
            }

            if (ispointer (_t_ft_Ty))
            {
                do_cast (regptr, FT_INT);
            }
            else
            {
                _t_ft_Ty = do_cast (regptr, _t_ft_Ty);
            }

            _t__cr4 = oldref->__cr4;        /* L1568 */
            _t__cr2 = oldref->__cr2;
            release (oldref);
            oldref = regptr;
            break;
        case C_AMPERSAND:   /* L1586 */
            L2463 (regptr, 1);
            
            if ((regptr->vartyp == 118) || (regptr->vartyp == 111))
            {
                terror (oldref, "can't take address");
                L25e6 (regptr);
            }

            _t_cr_18 = regptr->__cr18;
            _t__cr2 = regptr->__cr2;
            _t_ft_Ty = incref (regptr->ft_Ty);
            _t__cr4 = regptr->__cr4;
            break;
        case C_ASTERISK:    /* L15d4 */
            _t__cr4 = regptr->__cr4;
            
            if (ispointer (_t_ft_Ty = regptr->ft_Ty)) /* else L1618 */
            {
                _t_ft_Ty = decref (_t_ft_Ty);

                if (inbraces (_t_ft_Ty))  /* else L163a */
                {
                    _t_ft_Ty = incref (decref (_t_ft_Ty));
                    release (oldref);
                    oldref = regptr;
                }
            }
            else
            {
                terror (regptr, "pointer required");
                L25e6 (regptr);
                regptr->ft_Ty = 17;
                _t_ft_Ty = FT_INT;
                _t__cr4 = 0;
            }

            _t_cr_18 = regptr->__cr18;     /* L163a */
            _t__cr2 = regptr->__cr2;
            break;
        case C_PERIOD:      /* L1646 */
            _t__cr2 = L2502 (v18, &_t_ft_Ty, &v0);
            _t__cr4 = v18->__cr4;
            L2463 (regptr, 1);

            if (!(v18->cmdval) && !(v0))
            {
                release (v18);
                release (oldref);
                oldref = regptr;
                _t_cr_18 = oldref->__cr18;     /* go to L16fd */
            }
            else
            {
                _t_cr_18 = regptr->__cr18;     /* L169a */

                if (regptr->vartyp == C_ASTERISK)   /* else L16bf */
                {
                    v16 = regptr->cr_Left;
                    release (regptr);
                    oldref->cr_Left = (regptr = v16);
                }
                else
                {
                    v4 = regptr->ft_Ty;        /* L16bf */
                    regptr = oldref->cr_Left =
                        add_cmdref (C_AMPERSAND, regptr, 0, 0,
                                    regptr->_cline, regptr->_lpos);
                    regptr->ft_Ty = incref (v4);
                }

                regptr->__cr18 = _t_cr_18;
                goto L175b;
            }

            break;
        case C_PTRREF:      /* L1700 */
            _t__cr2 = L2502 (v18, &_t_ft_Ty, &v0);
            _t__cr4 = v18->__cr4;
            
            if (((v4 = regptr->ft_Ty) != FT_INT))   /* else L1754 */
            {
                if (!((ispointer (v4)) ? 1 : 0))   /* Trying to match code */
                {
                    terror (regptr, "pointer or integer required");
                    regptr->vartyp = C_INTSQUOT;
                    regptr->cmdval = 0;
                    regptr->__cr18 = 0;
                }
            }

            _t_cr_18 = regptr->__cr18;
L175b:
            oldref->vartyp = C_PLUS;
            oldref = L1005 (oldref);

            if (!v0)        /* else L17bb */
            {
                oldref->ft_Ty = incref (_t_ft_Ty);
                oldref->__cr18 = _t_cr_18;
                oldref->__cr2 = _t__cr2; 
                oldref = add_cmdref (C_ASTERISK, oldref, 0, 0,
                                    oldref-> _cline, oldref->_lpos);
            }

            break;
        case C_PARENS:         /* L17be */
            _t_ft_Ty = regptr->ft_Ty;

            if ((regptr->vartyp == C_AMPERSAND) &&
                    (inparentheses (decref (_t_ft_Ty))))
            {       /* else L17fa */
                v16 = oldref->cr_Left = regptr->cr_Left;
                release (regptr);
                _t_ft_Ty = decref (v16->ft_Ty);
                /* go to L185e */
            }
            else
            {
                if (inparentheses (_t_ft_Ty))
                {
                    _t_ft_Ty = decref (_t_ft_Ty);      /* go to L185e */
                }
                else
                {
                    if (!_t_ft_Ty)       /* else L184c */
                    {
                        v16 = regptr->cmdval;
                        v16->ft_Ty = 49;
                        v16->__cr2 = 2;
                        v16->__cr4 = 0;
                        v16->cmdval = FT_EXTERN;
                        v16->cr_Right = 0;
                        mem_cp (v16, regptr, sizeof (struct some_struct));
                        _t_ft_Ty = FT_INT;
                    }
                    else
                    {
                        terror (regptr, "not a function");
                        _t_ft_Ty &= 0x0f;
                    }
                }
            }

            _t__cr4 = regptr->__cr4;        /* L185e */
            _t__cr2 = regptr->__cr2;       /* Fall through to next case */
        case 11:         /* L1868 */
            ck_declared (regptr);
            get_ftty (regptr);

            switch (regptr->ft_Ty)
            {
                case FT_CHAR:     /* L187a */
                     do_cast (regptr, FT_INT);
                     break;
                case FT_FLOAT:     /* L187f */
                     do_cast (regptr, FT_DOUBLE);
                     break;
            }

            break;
        case C_COMMA:       /* L189a */
            _t__cr2 = v18->__cr2;
            _t_ft_Ty = v18->ft_Ty;
            _t__cr4 = v18->__cr4;
            break;
        case C_EXCLAM:      /* L18b0 */
            if (!(ispointer (regptr->ft_Ty)))
            {
                cktypnumeric (regptr);
            }

            _t_ft_Ty = FT_INT;
            break;
        case C_MINUS:       /* L18c8 */
            _t_ft_Ty = cktypnumeric (regptr);
            break;
        case C_TILDE:       /* L18d2 */
            if ((_t_ft_Ty = cktypnumeric (regptr)) == FT_DOUBLE)    /* else L18c3 */
            {
                notintegral (regptr);
                L25e6 (regptr);
            }

            break;
        case C_PLUSPLUS:    /* _269  (L18ef) */
        case C_INCREMENT:         /* _269 */
        case C_MINMINUS:    /* _269 */
        case C_DECREMENT:         /* _269 */
            L2463 (regptr, 0);
            _t__cr2 = regptr->__cr2;
            
            if ((_t_ft_Ty = regptr->ft_Ty) & 0x30)      /* else L1920 */
            {
                oldref->cmdval = L418a (decref (_t_ft_Ty),
                                         regptr->__cr2, regptr->__cr4);
            }
            else
            {
                oldref->cmdval = 1;       /* L1920 */
            }

            _t_cr_18 = regptr->__cr18;

            if (regptr->vartyp == C_ASTERISK)   /* else L1aa7 */
            {
                ++_t_cr_18;
            }

            break;
        case C_ANDAND:      /* _278  (L193f) */
        case C_OROR:        /* _278 */
            if (!ispointer (regptr->ft_Ty))
            {
                cktypnumeric (regptr);
            }

            if (!(ispointer (v18->ft_Ty))) /* L1951 */ /* else cktypnumeric */
            {
                cktypnumeric (v18);
            }

            break;
        case C_SLASH:       /* L1e01 */
        case C_MULT:         /* L1e01 */
            _t_ft_Ty = L2340 (regptr, v18);
            break;
        case C_AND:         /* _292  (L1969) */
        case C_VBAR:        /* _292 */
        case C_CARET:       /* _292 */
        case C_PERCENT:     /* _292 */
            if ((_t_ft_Ty = L2340 (regptr, v18)) == FT_DOUBLE)
            {
                goto L19a6;
            }

            break;
        case C_LSHIFT:      /* L1985 */
        case C_RSHIFT:      /* L1985 */
            if (((_t_ft_Ty = cktypnumeric (regptr)) == FT_DOUBLE) ||
                    (cktypnumeric (v18) == FT_DOUBLE))        /* else L19c6 */
            {
L19a6:
                terror (oldref, "both must be integral");
                L25e6 (oldref);
                break;
            }

            do_cast (v18, FT_INT);
            break;
        case C_LT:          /* L19d6 */
        case C_GT:
        case C_LT_EQ:
        case C_GT_EQ:
            if (((ispointer (regptr->ft_Ty)) &&
                        (ispointer (v18->ft_Ty))) ||
                        (L2340 (regptr, v18) == 7))
            {
                oldref->vartyp = v14 + 4;   /* L19ff */
            }
                

            break;
        case C_EQEQ:        /* L1a0c */
        case C_NOTEQ:       /* L1a0c */
            if (ispointer (regptr->ft_Ty))    /* else L1a45 */
            {
                /*if (!ispointer (v18->ft_Ty))*/      /* else L1a51 */
                if (!((ispointer (v18->ft_Ty)) ? 1 : 0))   /* code match ? */
                {
                    cktypnumeric (v18);        /* L1a2a + 1 line */
                    do_cast (v18, FT_INT);     /* go to L1a4f */
                }
            }
            else
            {
                L2340 (regptr, v18);    /* L1a45 */
            }
            
            break;      /* L1a51 */
        case C_PLUS:        /* L1a54 */
            if (ispointer (v18->ft_Ty))     /* else L1a73 */
            {
                {
                    int __tmp = regptr;

                    regptr = v18;
                    v18 = __tmp;
                }

                oldref->cr_Left = regptr;
            }

            _t__cr2 = regptr->__cr2;        /* L1a73 */
            _t_ft_Ty = regptr->ft_Ty;

            if (ispointer (_t_ft_Ty))
            {
                _t__cr4 = regptr->__cr4;
                goto L1b8d;
            }

            _t_ft_Ty = L2340 (regptr, v18);         /* L1a8e */
            /*_t_cr_18 = regptr->__cr18 + v18->__cr18;*/
            _t_cr_18 = regptr->__cr18 + v18->__cr18;
            break;
        case C_NEG:         /* L1aaa */
            _t_cr_18 = regptr->__cr18 + v18->__cr18;
            
            if (ispointer ((_t_ft_Ty = regptr->ft_Ty)))       /* else L1e01 */
            {
                _t__cr2 = regptr->__cr2;
                _t__cr4 = regptr->__cr4;

                if (ispointer (v18->ft_Ty))    /* else L1b90 */
                {
                    oldref->__cr18 = _t_cr_18;

                    if ((_t_ft_Ty != v18->ft_Ty) || (_t__cr2 != v18->__cr2))
                    {
                        terror (oldref, "pointer mismatch");
                        /* go to L1b7e */
                    }
                    else
                    {
                        _t_ft_Ty = decref (_t_ft_Ty);
                        
                        if ((_t__cr2 = L418a (_t_ft_Ty, _t__cr2, _t__cr4)) != 1) /* else L1b7e */
                        {
                            _t_cr_18 = 2;
                            v16 = add_cmdref (C_INTSQUOT, 0, 0, _t__cr2, 0, 0);
                            oldref = add_cmdref (C_SLASH, oldref, v16, 0,
                                                oldref->_cline, oldref->_lpos);
                        }
                    }

                    _t__cr2 = 2;
                    _t__cr4 = 0;
                    _t_ft_Ty = FT_INT;
                    break;
                }
L1b8d:
                cktypnumeric (v18);

                if (!iswordorlong (v18->ft_Ty))        /* else L1bba */
                {
                    notintegral (v18);
                    L25e6 (v18);
                }

                do_cast (v18, FT_INT);
                oldref->cr_Right = L23c4 (_t__cr2, _t_ft_Ty, _t__cr4, v18);
                _t_cr_18 = regptr->__cr18 + v18->__cr18;
            }
            else
            {
                _t_ft_Ty = L2340 (regptr, v18);     /* copy of L1e01 */
                /*goto L1d66;*/
            }
            
            break;
        case C_EQUAL:       /* L1bf4 */
            L2463 (regptr, 0);
            ck_declared (v18);
            v2 = get_ftty (v18);
            
            if (((ispointer ((_t_ft_Ty = regptr->ft_Ty)))) &&
                    !(ispointer (v2)) &&
                    !(iswordorlong (v2)))           /* else L1cba */
            {           /* Loop different - they go through L1cba we go
                         * straight to L1d66 */
                goto L1d66;
            }

            if (!(ispointer (v2)) || (ispointer (_t_ft_Ty)) ||  /* L1c3a */
                        (iswordorlong (_t_ft_Ty)))      /* else L1cba */
            {
                do_cast (v18, _t_ft_Ty);      /* L1c5d */
                goto L1d4f;
            }
            else
            {
                goto L1d66;
            }

L1c71:
            L2463(regptr, 0);
            cktypnumeric (v18);
            v2 = get_ftty (v18);
            
            if (ispointer ((_t_ft_Ty = regptr->ft_Ty)))
            {
                switch (v14)
                {
                    case C_MINEQU:       /* L1ca6 */
                    case C_PLUSEQ:       /* L1ca6 */
                        do_cast (v18, FT_INT);
                        goto L1cf0;
                    default:     /* L1cba */
                        goto L1d66;
                }
            }

            switch (v14)
            {
                default:     /* L1cd3 */
                    if (_t_ft_Ty == FT_FLOAT)
                    {
                        do_cast (v18, FT_DOUBLE);
                    }
                    else
                    {
                        do_cast (v18, _t_ft_Ty);
                    }
                case C_LSHEQ:    /* L1cf3 */
                case C_RSH_EQ:    /* L1cf3 */
L1cf0:
                    oldref->vartyp = v14 - 80;
                    oldref = L1382 (oldref);

                    if (_t_ft_Ty == FT_CHAR)    /* else L1d2a */
                    {
                        oldref->cr_Left = regptr->cr_Left;
                        release (regptr);
                        regptr = oldref->cr_Left;
                        _t_ft_Ty = FT_INT;
                    }

                    if ((v14 - 80) == oldref->vartyp)   /* else L1d52 */
                    {
                        oldref->vartyp = v14;
                    }
            }

L1d4f:
            _t__cr2 = regptr->__cr2;
            _t_cr_18 = regptr->__cr18 + v18->__cr18;
            _t__cr4 = regptr->__cr4;
            break;
            
            /*goto L1d66;*/     /* L1cba */
L1d66:
            terror (oldref, "type mismatch");  /* go to L1e44 */
            break;
        case C_COLON:       /* L1d7a */
            if (ispointer ((_t_ft_Ty = regptr->ft_Ty)))    /* else L1dd9 */
            {
                _t__cr2 = regptr->__cr2;
                _t_cr_18 = regptr->__cr18;
                _t__cr4 = regptr->__cr2;

                if (ispointer (v18->ft_Ty))       /* else L1dcc */
                {
                    if ((_t_ft_Ty != v18->ft_Ty) ||
                            (regptr->__cr2 != v18->__cr2))
                    {
                        terror (oldref, "pointer mismatch");
                        /*break;*/
                    }
                    else
                    {
                        _t__cr4 = 0;
                    }

                    break;
                }
                
                L1f8e (v18);
                break;
            }

            if (ispointer ((_t_ft_Ty = v18->ft_Ty))) /*L1dd9  else L1e01 */
            {
                _t__cr2 = v18->__cr2;
                _t_cr_18 = v18->__cr18;
                _t__cr4 = v18->__cr4;
                L1f8e (regptr);
                break;
            }

            _t_ft_Ty = L2340 (regptr, v18);     /* L1e01 */
            break;
        case C_QUESTION:    /* L1e12 */
            _t_ft_Ty = v18->ft_Ty;
            _t__cr2 = v18->__cr2;
            _t__cr4 = v18->__cr4;
            break;
        default:            /* L1e28 */
            if (v14 >= C_PLUSEQ)
            {
                goto L1c71;
            }

            comperr ( oldref, "type check");
            break;
    }

    oldref->ft_Ty = _t_ft_Ty;       /* L1f7b */
    oldref->__cr2 = _t__cr2;
    oldref->__cr18 = _t_cr_18;
    oldref->__cr4 = _t__cr4;
    return oldref;
}

/* *********************************************************** *
 * L1f8e () - Checks that 2nd & 3rd expressions of a           *
 *      "? ... :" term are of same type.                       *
 * *********************************************************** */

void
#ifndef COCO
L1f8e (register CMDREF *regptr)
#else
L1f8e (regptr)
register CMDREF *regptr;
#endif
{
    if ((regptr->vartyp != C_INTSQUOT) || (regptr->cmdval))
    {
        terror (regptr, "should be NULL");
        regptr->vartyp = C_INTSQUOT;        /* Store correct value */
        regptr->cmdval = 0;
    }
}

/* ******************************************************** *
 * cktypnumeric () - Checks that the type is some numeric   *
 *      type.  Promotes "char" to "int" and "float" to      *
 *      double.                                             *
 * Returns: ft_Ty (modified if applicable)                  *
 * ******************************************************** */

int
#ifndef COCO
cktypnumeric (register CMDREF *c_ref)
#else
cktypnumeric (c_ref)
    register CMDREF *c_ref;
#endif
{
    int _ttype;

    ck_declared (c_ref);
    
    switch (_ttype = c_ref->ft_Ty)
    {
        case FT_CHAR:      /* L1fd7 */
            _ttype = FT_INT;
            do_cast (c_ref, _ttype);
            break;
        case FT_FLOAT:      /* L1fdc */
            _ttype = FT_DOUBLE;
            do_cast (c_ref, _ttype);
            break;
        case FT_DOUBLE:      /* L201f */
        case FT_LONG:
        case FT_INT:
        case FT_UNSIGNED:
            break;
        default:     /* L1feb */
            terror (c_ref, "type error");
            _ttype = FT_INT;
            break;
    }

    return (c_ref->ft_Ty = _ttype);
}

/* ******************************************************** *
 * do_cast () - Performs casts                              *
 * Passed: (1) CMDREF * to variable to be cast              *
 *         (2) to_type - the type to convert to             *
 * ******************************************************** */

int
#ifndef COCO
do_cast (register CMDREF *ptr, int to_typ)
#else
do_cast (ptr, to_typ)
    register CMDREF *ptr;
    int to_typ;
#endif
{
    /* 4 bytes stack */
    void *_valptr;
    int _cast_type;

    _cast_type = 0;

    switch (ptr->ft_Ty)
    {
        case FT_CHAR:      /* L203c */
            switch (to_typ)
            {
                case FT_INT:      /* _434 (L2040) */
                case FT_UNSIGNED:
                    _cast_type = C_CHR2INT;           /* 0x85 */
                    break;      /* L2303 = break */
                case FT_LONG:      /* L2045 */
                    do_cast (ptr, FT_INT);
                    _cast_type = C_I2LNG;
                    break;
                case FT_DOUBLE:      /* _437  (L2058) */
                case FT_FLOAT:
                    do_cast (ptr, FT_INT);    /* First convert to int */
                    do_cast (ptr, to_typ);
                    break;
                default:     /* L2303 */
                    break;
            }

            break;
        default:
            if (!(ispointer (ptr->ft_Ty)))
            {
                break;
            }
            /* else fall through to case FT_INT */
        case FT_INT:      /* _442 (L209f) */
            switch (to_typ)
            {
                case FT_LONG:      /* L20a4 */
                    if ((ptr->vartyp == C_INTSQUOT))     /* else L20df */
                    {
                        /* NOTE:  We need to change this..  _valptr is a long
                         * here, so offsets are offsets into the long.
                         */

                        _valptr = addmem (sizeof (long));
                        
                        /* sign extend into MSB */

                        if ((((CMDREF *)_valptr)->__cr2 = ptr->cmdval) < 0)
                        {
                            ((CMDREF *)_valptr)->ft_Ty = -1;
                        }
                        else
                        {
                            ((CMDREF *)_valptr)->ft_Ty = 0;
                        }

                        ptr->cmdval = _valptr;
L20d0:
                        ptr->vartyp = C_LONG;
                        ptr->__cr2 = LONGSIZ;
                    }
                    else
                    {
                        _cast_type = C_I2LNG;
                    }

                    break;
                case FT_CHAR:      /* L20e4 */
                    to_typ = FT_INT;
                    break;
                case FT_FLOAT:      /* L20ec */
                    do_cast (ptr, FT_DOUBLE);
                    _cast_type = C_TOFLOAT;
                    break;
                case FT_DOUBLE:      /* L20fd */
                    if (ptr->vartyp == C_INTSQUOT)      /* else L212f */
                    {
                        _valptr = addmem (sizeof (double));

                        /* The following does not actually do a
                         * _valptr = (double)src thing, but
                         * rather simply stores abs (theint) at offset 5
                         * into the value, and at offset 0, 0 if positive
                         * or $80 if negative
                         */
#ifdef COCO
#asm
                        ldx 2,s
                        pshs x
                        ldd 8,u
                        lbsr L6a1c
                        lbsr _dmove
#endasm
#else
                        *((double *)_valptr) = (int)(ptr->cmdval);
#endif

L211f:
                        ptr->cmdval = _valptr;
                        ptr->vartyp = C_DOUBLE;
                        ptr->__cr2 = DBLSIZ;
                        break;
                    }

                    _cast_type = C_I2DBL;
                    break;
            }

            break;
        case FT_UNSIGNED:      /* L2152 */
            switch (to_typ)
            {
                case FT_LONG:      /* L2156 */
                    _cast_type = C_U2LNG;
                    break;
                case FT_FLOAT:      /* L215b */
                    do_cast (ptr, FT_DOUBLE);
                    _cast_type = C_TOFLOAT;
                    break;
                case FT_DOUBLE:      /* L216c */
                    _cast_type = C_U2DBL;
                    break;
                case FT_CHAR:      /* L2174 */
                    to_typ = FT_INT;
                    break;
            }

            break;
        case FT_LONG:      /* L2193 */
            switch (to_typ)
            {

                default:     /* L2198 */
                    if (!ispointer (to_typ))
                    {
                        break;
                    }
                    /* Fall through to next case */
                case FT_INT:      /* _477 (L21a5) */
                case FT_UNSIGNED:      /* L21a5 */
                case FT_CHAR:      /* L21a5 */
                    if (ptr->vartyp == C_LONG)
                    {
                        /* Discard MSB of long */
                        _valptr = ptr->cmdval;
#ifdef COCO
                        /*ptr->cmdval = ((CMDREF *)_valptr)->__cr2;*/
                        ptr->cmdval = ((int *)_valptr)[1];
#else
                        ptr->cmdval = *((long *)_valptr) & 0xffff;
#endif
L21b9:
                        ptr->vartyp = C_INTSQUOT;
                        ptr->__cr2 = INTSIZ;
                    }
                    else
                    {
                        _cast_type = C_LNG2INT;
                    }
                    
                    break;
                case FT_FLOAT:      /* L21cd */
                    do_cast (ptr, FT_DOUBLE);
                    _cast_type = C_TOFLOAT;
                    break;
                case FT_DOUBLE:      /* L21de */
                    if (ptr->vartyp == C_LONG)
                    {
                        _valptr = addmem (sizeof (double));
#ifdef COCO
#asm
                        ldx 2,s
                        pshs x
                        ldx 8,u
                        lbsr L6a3c
                        lbsr _dmove
#endasm
#else
                        *((double *)_valptr) = *(double *)(ptr->cmdval);
#endif
                        goto L211f;
                    }

                    _cast_type = C_L2DBL;       /* L2203 */
                    break;
            }

            break;
        case FT_FLOAT:      /* L222d */
            switch (to_typ)
            {
                case FT_LONG:      /* _496 (L2231) */
                case FT_UNSIGNED:
                case FT_CHAR:
                case FT_INT:
                    do_cast (ptr, FT_DOUBLE);
                    do_cast (ptr, to_typ);
                    break;
                case FT_DOUBLE:      /* L224b */
                    _cast_type = C_FLT2DBL;
                    break;
            }

            break;
        case FT_DOUBLE:      /* L2275 */
            switch (to_typ)
            {
                case FT_CHAR:      /* _504 (L2279) */
                case FT_UNSIGNED:      /* L2279 */
                case FT_INT:      /* L2279 */
                    if (ptr->vartyp == C_DOUBLE)        /* else L228d */
                    {
#ifdef COCO
#asm
                        ldx 8,u
                        lbsr L697c
                        std 8,u
#endasm
/*#else*/
                        /* Gotta figure out what L697c does */
#endif
                        goto L21b9;
                    }
                    else
                    {
                        _cast_type = C_DBL2INT;
                    }

                    break;
                case FT_LONG:      /* L2292 */
                    if (ptr->vartyp == C_DOUBLE)        /* else L22ab */
                    {
#ifdef COCO
#asm
                        ldx 8,u
                        pshs x
                        ldx 8,u
                        lbsr L6981
                        lbsr _lmove
#endasm
/*#else*/
#endif
                        goto L20d0;
                    }
                    else
                    {
                        _cast_type = C_DBL2LNG;
                    }

                    break;
                    
                case FT_FLOAT:      /* L22b0 */
                    _cast_type = C_TOFLOAT;

                    break;
            }
    }

    /* _429 (L2303) */
    if (_cast_type)     /* else L233b */
    {
        nodecopy (ptr, (_valptr = add_cmdref (0, 0, 0, 0, 0, 0)));
        ptr->vartyp = _cast_type;
        ptr->cr_Left = _valptr;
        ptr->cr_Right = 0;
    }

    return (ptr->ft_Ty = to_typ);
}

int
#ifndef COCO
L2340 (register CMDREF *cref_1, CMDREF *cref_2)
#else
L2340 (cref_1, cref_2)
    register CMDREF *cref_1;
    CMDREF *cref_2;
#endif
{
    int ref1_ty;
    int ref2_ty;

    ref1_ty = cktypnumeric (cref_1);
    ref2_ty = cktypnumeric (cref_2);

    if (ref1_ty == FT_DOUBLE)
    {
        return (do_cast (cref_2, FT_DOUBLE));
    }
    else
    {
        if (ref2_ty == FT_DOUBLE)
        {
            return (do_cast (cref_1, FT_DOUBLE));
        }
        else
        {
            if (ref1_ty == FT_LONG)
            {
                return (do_cast (cref_2, FT_LONG));
            }
            else
            {
                if (ref2_ty == FT_LONG)
                {
                    return (do_cast (cref_1, FT_LONG));
                }
                else
                {
                    if ((ref1_ty == FT_UNSIGNED) || (ref2_ty == FT_UNSIGNED))
                    {
                        return (cref_1->ft_Ty = cref_2->ft_Ty = FT_UNSIGNED);
                    }
                    else
                    {
                        return FT_INT;
                    }
                }
            }
        }
    }

    /* We get here only if none of the above apply */

    /* See if gcc barfs without the following line */
    /*return 1;*/
}

CMDREF *
#ifndef COCO
L23c4 (int p1, int p2/*gentyp*/, int p3/*w4*/, CMDREF *p4)
#else
L23c4 (p1, p2, p3, p4)
    int p1;
    int p2/*gentyp*/;
    int p3/*w4*/;
    CMDREF *p4;
#endif
{
    register CMDREF *regptr;

    if ((p1 = L418a (decref (p2), p1, p3)) == 1)
    {
        return p4;
    }

    /* L23ee */
    regptr = add_cmdref (C_INTSQUOT, 0, 0, p1, p4->_cline, p4->_lpos);
    regptr->ft_Ty = FT_INT;
    regptr = L1005 (add_cmdref (C_MULT, p4, regptr, 0, p4->_cline, p4->_lpos));

    if (regptr->vartyp == C_INTSQUOT)
    {
        regptr->__cr18 = 0;
    }
    else
    {
        regptr->__cr18 = 2;
    }

    regptr->ft_Ty = FT_INT;     /* L2452 */
    regptr->__cr2 = 2;

    return regptr;
}

void
#ifndef COCO
L2463 (register CMDREF *regptr, int p2)
#else
L2463 (regptr, p2)
    register CMDREF *regptr;
    int p2;
#endif
{
    int v0;

    switch (v0 = regptr->vartyp)
    {
        case C_X_RGWRD:         /* L25b1 */
        case C_RGWRD:         /* L25b1 */
        case C_ASTERISK:    /* L25b1 */
            return;
    }

    if (v0 == C_USRLBL)       /* else L24bc ("lvalue required") */
    {
        ck_declared (regptr);

        if (p2)
        {
            return;
        }

        if ((!(inbraces (regptr->ft_Ty))) && (regptr->ft_Ty != FT_STRUCT))
        {
            return;
        }
    }

    terror (regptr, "lvalue required");        /* L24bc */
    L25e6 (regptr);

}

void
#ifndef COCO
ck_declared (register CMDREF *regptr)
#else
ck_declared (regptr)
    register CMDREF *regptr;
#endif
{
    if ((regptr->vartyp == C_USRLBL) && !(regptr->ft_Ty))    /* else L25b3 */
    {
        terror (regptr, "undeclared variable");
        L25e6 (regptr);
    }
}

int
#ifndef COCO
L2502 (register CMDREF *regptr, int *p2, int *p3)
#else
L2502 (regptr, p2, p3)
    register CMDREF *regptr;
    int *p2;
    int *p3;
#endif
{
    CMDREF *v0;

    *p2 = regptr->ft_Ty;

    if ((regptr->vartyp) == C_AMPERSAND)       /* else L2541 */
    {
        *p3 = 1;
        v0 = regptr->cr_Left;
        v0->__cr4 = regptr->__cr4;
        nodecopy (v0, regptr);
        release (v0);
    }
    else
    {
        *p3 = 0;
    }

    ck_declared (regptr);

    if (regptr->vartyp == C_USRLBL)       /* else L2586 */
    {
        v0 = regptr->cmdval;

        if (v0->cmdval != 17)   /* else L2567 */
        {
            goto L2584;
        }

        regptr->vartyp = C_INTSQUOT;
        regptr->cmdval = v0->vartyp;
        regptr->__cr18 = 0;
        regptr->ft_Ty = FT_INT;
        return v0->__cr2;
    }

L2584:
    terror (regptr, "struct member required");
    L25e6 (regptr);
    regptr->vartyp = C_INTSQUOT;
    regptr->cmdval = 0;
    regptr->__cr18 = 0;
    *p2 = FT_INT;
    return 2;
}

int
#ifndef COCO
get_ftty (register CMDREF *regptr)
#else
get_ftty (regptr)
    register CMDREF *regptr;
#endif
{
    if ((regptr->ft_Ty == FT_STRUCT) || (regptr->ft_Ty == FT_UNION))
    {
        terror (regptr, "structure or union inappropriate");
        L25e6 (regptr);
    }

    return regptr->ft_Ty;
}

/* **************************************************** *
 * L25e6 ()                                             *
 *                                                      *
 * **************************************************** */

void
#ifndef COCO
L25e6 (register CMDREF *p1)
#else
L25e6 (p1)
register CMDREF *p1;
#endif
{
    mem_cp (D018b, p1, sizeof (struct some_struct));
    p1->__cr18 = 1;
    L0393 (p1->cr_Left);
    L0393 (p1->cr_Right);
    p1->cr_Left = p1->cr_Right = 0;
    p1->vartyp = C_USRLBL;    /* generic alpha??? */
    p1->cmdval = D018b;
}

/* ******************************************************** *
 * iswordorlong() - checks that a command is a word value   *
 * Returns: TRUE if it's an int, char, long, or unsigned    *
 *          FALSE on anything else                          *
 * ******************************************************** */

int
#ifndef COCO
iswordorlong (int tstval)
#else
iswordorlong (tstval)
int tstval;
#endif
{
    switch (tstval)
    {
        case FT_INT:
        case FT_CHAR:
        case FT_LONG:
        case FT_UNSIGNED:
            return 1;
    }

    return 0;
}

void
#ifndef COCO
notintegral (CMDREF *c_ref)
#else
notintegral (c_ref)
    CMDREF *c_ref;
#endif
{
    terror (c_ref, "must be integral");
}
