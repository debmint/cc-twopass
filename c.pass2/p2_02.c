/* ************************************************************************ *
 * p2_02.c - part 2 for c.pass2                                             *
 *                                                                          *
 * $Id: p2_02.c 18 2008-05-19 21:54:22Z dlb $::                                                                   *
 * ************************************************************************ */

#include "pass2.h"

#ifdef COCO
expnode *L0d04 ();
#endif

void
#ifdef COCO
L0bc3 (cref)
    register expnode *cref;
#else
L0bc3 (expnode *cref)
#endif
{
    L0c2d (cref);

    if (cref->op != DREG)
    {
        gen (LOAD, DREG, NODE, cref);
        cref->op = DREG;
    }
}

void
#ifdef COCO
L0bf7 (cref)
    register expnode *cref;
#else
L0bf7 (expnode *cref)
#endif
{
    L1c1d (cref);

    if (cref->op != DREG)
    {
        gen (LOAD, DREG, NODE, cref);
        cref->op = DREG;
    }
}

void
#ifdef COCO
L0c2d (cref)
    register expnode *cref;
#else
L0c2d (expnode *cref)
#endif
{
    switch (cref->type)
    {
        case LONG:      /* L0c3b */
            L2505 (cref);
            break;
        case FLOAT:     /* L0c42 */
        case DOUBLE:
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
    register expnode *cref;
#else
L0c6d ( expnode *cref)
#endif
{
    switch (cref->op)
    {
        case STRING:      /* L0c7c */
            gen (LOAD, DREG, NODE, cref);
            cref->op = DREG;
            cref->val.num = 0;
            break;
        case AMPER:    /* L0c9e */
            gen (LOADIM, DREG, NODE, cref->left);
            cref->op = DREG;
            break;
        case XREG:          /* L0d02 */
        case DREG:          /* L0d02 */
        case UREG:      /* L0d02 */
        case YREG:    /* L0d02 */
            break;
        default:           /* L0cbf */
            gen (LOAD, DREG, NODE, cref);
#ifdef COCO
L0cd9:
#endif
            cref->op = 112;
            break;
    }
}

expnode *
#ifdef COCO
L0d04 (cref)
    register expnode *cref;
#else
L0d04 (expnode *cref)
#endif
{
    int _vartype;

    if ((_vartype = cref->op) == COMMA)       /* else L0d4d */
    {
        expnode *_vrRight = cref->right;

        L4a69 (L0d04 (cref->left));
        L4acd (_vrRight, cref);
        L4a8a (_vrRight);
        L0d04 ( cref);      /* go to L0ef7 */
    }
    else
    {
        if (cref->type == LONG)
        {
            L2520 (cref);       /* go to L0ef7 */
        }
        else
        {
            if ((cref->type == FLOAT) || (cref->type == DOUBLE))
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
                        case STRING:      /* L0ef7 */
                        case NAME:
                        case YREG:
                        case UREG:
                        case AMPER:
                        case CONST:
                            break;
                        case ASSIGN:      /* L0d97 */
                            L1567 (cref);
                            break;
                        case CTOI:    /* L0d9f */
                            L0d04 (cref->left);
                            break;
                        case LTOI:    /* L0da9 */
                            L2520 (cref->left);
#ifdef COCO
                            gen (LTOI, NODE, cref->left);
#else
                            gen (LTOI, NODE, cref->left, 0);
#endif
                            cref->op = DREG;
                            break;
                        case DTOI:    /* L0dc7 */
                            L29fc (cref->left);
#ifdef COCO
                            gen (DBLOP, DTOI);
#else
                            gen (DBLOP, DTOI, 0, 0);
#endif
                            cref->op = DREG;
                            break;
                        case STAR:   /* L0ddf */
                            L1953 (cref);
                            break;
                        case NOT:    /* L0de6 */
                        case DBLAND:
                        case DBLOR:
                            L124c (cref);
                            break;
                        case COMPL:      /* L0ded */
                        case NEG:
                            L0bc3 (cref->left);
#ifdef COCO
                            gen (_vartype);
#else
                            gen (_vartype, 0, 0,0);
#endif
                            cref->op = 112;
                            break;
                        case QUERY:    /* L0e01 */
                            L12e8 (cref, L0bc3);
                            cref->op = 112;
                            break;
                        case INCBEF:    /* L0e16 */
                        case INCAFT:
                        case DECBEF:
                        case DECAFT:
                            L1a9a (cref, 112);
                            break;
                        case CALL:     /* L0e22 */
                            L1364 (cref);
                            break;
                        default:           /* L0e2c */
                            if (_vartype >= ASSPLUS)   /* 160 */
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
    expnode *cref;
#else
L0efd (int vtyp, expnode *cref)
#endif
{
    /* 6 bytes static vars */
    expnode *_rfRt;  /* v4 */
    int v2;
    unsigned int var0;

    register expnode *rfLft;
    
    rfLft = cref->left;
    _rfRt = cref->right;

    /* First modify vtyp if necessary */

    if (rfLft->type == UNSIGN)
    {
        switch (vtyp)
        {
            case DIV:      /* L0f1d */
                vtyp = UDIV;
                break;
            case MOD:    /* L0f22 */
                vtyp = UMOD;
                break;
            case SHR:     /* L0f27 */
                vtyp = USHR;
                break;
            default:           /* L0f73 */
                break;
        }
    }
    else
    {
        switch (vtyp)
        {
            case PLUS:       /* L0f43 */
            case MINUS:        /* L0f43 */
                if ((rfLft->op == AMPER) && 
                            (_rfRt->op != CONST))
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
        case MINUS:        /* L0f78 */
            if ( ! L22ca (_rfRt) )    /* else L0faa */
            {
                L0c2d (_rfRt);
#ifdef COCO
                gen (122, _rfRt->op);
#else
                gen (122, _rfRt->op, 0, 0);
#endif
                _rfRt->op = 110;
                L0bc3 (rfLft);
            }
            else
            {
                L0bc3 (rfLft);      /* L0faa */
                L0d04 (_rfRt);
            }

            gen (MINUS, DREG, NODE, _rfRt);
            break; /* go to L120d */
        case AND:
        case OR:
        case XOR:        /* L0fce */
        case PLUS:
            if ( ((L22ca (rfLft)) && ! (L22ca (_rfRt))) ||
                    (rfLft->op == CONST))
            {
                expnode *__tmpref = rfLft;

                rfLft = _rfRt;
                _rfRt = __tmpref;
            }

            if (is_regvar (rfLft->op))      /* L0ff6 */   /* else L1021 */
            {
#ifdef COCO
                gen (122, rfLft->op);     /* L1003 */
#else
                gen (122, rfLft->op, 0, 0);
#endif
                L0bc3 ( _rfRt);
                _rfRt->op = 110;        /* go to 1052 */
            }
            else
            {
                L0bc3 (rfLft);      /* L1021 */

                if ( ! L22ca (_rfRt))
                {
#ifdef COCO
                    gen (122, 112);
#else
                    gen (122, DREG, 0, 0);
#endif
                    L0bc3 ( _rfRt);
                    _rfRt->op = 110;        /* go to 1052 */
                }
                else
                {
                    L0d04 (_rfRt);      /* L1038 */

                    if (vtyp != PLUS)
                    {
                        L152d ( _rfRt);
                    }
                }
            }

            gen (vtyp, DREG, NODE, _rfRt);
            break;
        case EQ:       /* L106d */
        case NEQ:
        case GT:
        case LT:
        case LEQ:
        case GEQ:
        case UGT:
        case ULT:
        case ULEQ:
        case UGEQ:
            L124c (cref);
            break;
        case 77:           /* L1077 */
        case SHR:
        case SHL:
            if ((_rfRt->op) == CONST)      /* else L10db */
            {
                var0 = _rfRt->val.num;
L108b:
                if (var0 <= STRUCT)  /* 4 */     /* else L10db */
                {
                    L0bc3 ( rfLft);

                    while (var0--)
                    {
                        switch (vtyp)
                        {
                            case SHL:      /* L10a2 */
#ifdef COCO
                                gen (152);
#else
                                gen (152, 0, 0, 0);
#endif
                                break;
                            case SHR:      /* L10a7 */
#ifdef COCO
                                gen (150);
#else
                                gen (150, 0, 0, 0);
#endif
                                break;
                            case 77:            /* L10ac */
#ifdef COCO
                                gen (151);
#else
                                gen (151, 0, 0, 0);
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
        case TIMES:       /* L10df */
            if (rfLft->op == CONST)    /* else L10f3 */
            {
                expnode *_tmpref;

                _tmpref = rfLft;
                rfLft = _rfRt;
                _rfRt = _tmpref;
            }       /* fall through to next case */
        case UDIV:           /* L10f3 */
            if ((_rfRt->op == CONST) &&
                        (var0 = L121f ( _rfRt->val.num)))    /* else L112b */
            {
                _rfRt->val.num = var0;

                vtyp = (vtyp == TIMES) ? SHL : USHR;    /* L1122 */
                goto L108b;
            }
        case DIV:      /* L112b */
        case 76:           /* L112b */
        case MOD:    /* L112b */
L1129:
            L0c2d (rfLft);
#ifdef COCO
            gen (PUSH, rfLft->op);
#else
            gen (PUSH, rfLft->op, 0, 0);
#endif
            L0bc3 ( _rfRt);
#ifdef COCO
            gen (vtyp);
#else
            gen (vtyp, 0, 0, 0);
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
    cref->op = DREG;
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
    register expnode *cref;
#else
L124c (expnode *cref)
#endif
{
    int var2;
    int var0;

    L1f13 (cref, (var2 = ++D000b), (var0 = ++D000b), 1);
    L4414 (var2);
    gen (LOAD, DREG, CONST, 1);

#ifdef COCO
    gen (JMP, (var0 = ++D000b), 1);
#else
    gen (JMP, (var0 = ++D000b), 1, 0);
#endif
    L4414 (var0);

    gen (LOAD, DREG, CONST, 0);
    L4414 (var2);
    cref->op = DREG;
}

void
#ifdef COCO
L12e8 (cref, fnc)
    register expnode *cref;
    void (*fnc)();
#else
L12e8 (expnode *cref, void (*fnc)())
#endif
{
    int var4;
    int var2;
    int var0;

    L1f13 (cref->left, (var4 = ++D000b), (var0 = ++D000b), 1);
    cref = cref->right;
    L4414 (var4);
    (*fnc) (cref->left);
#ifdef COCO
    gen (JMP, (var4 = ++D000b), 0);
#else
    gen (JMP, (var4 = ++D000b), 0, 0);
#endif
    L4414 (var0);
    (*fnc) (cref->right);
    L4414 (var2);
}
void
#ifdef COCO
L1364 (cref)
    expnode *cref;
#else
L1364 (expnode *cref)
#endif
{
    expnode *var2;
    int var0;

    var0 = D000d;
    var2 = cref;

    while (var2 = var2->right)
    {
        register expnode *regptr = var2->left;    /* L1379 */;

        if (regptr->type == LONG)     /* else L13a8 */
        {
            if (regptr->op == LCONST)
            {
                L294b (regptr);  /* go to L1401 */
                continue;
            }
            else
            {
                L2505 (regptr);
#ifdef COCO
                gen (LONGOP, STACK);
#else
                gen (LONGOP, STACK, 0, 0);
#endif
                continue;
            }
        }
        else
        {       /* L13a8 */
            if ((regptr->type == FLOAT) || (regptr->type == DOUBLE))
            {
                L29fc (regptr);
#ifdef COCO
                gen (DBLOP, STACK);
#else
                gen (DBLOP, STACK, 0, 0);
#endif
            }
            else
            {
                L0d04 (regptr);

                switch (regptr->op)
                {
                    case DREG:          /* L13f3 */
                    case XREG:
                    case UREG:
                    case YREG:
                        break;
                    default:           /* L13d4 */
                        L0c6d (regptr);
                        break;
                }

                gen (PUSH, regptr->op NUL2);
            }

        }
    }       /* end while (var2 = cr->right)  ( L1401 ) */

    L0d04 (cref->left);
#ifdef COCO
    gen (CALL, NODE, cref->left);
#else
    gen (CALL, NODE, cref->left, 0);
#endif
    D000d = prt_rsrvstk (var0);
    cref->op = DREG;
}


int 
#ifdef COCO
L1440 (cref)
    register expnode *cref;
#else
L1440 (expnode *cref)
#endif
{
    expnode *var0;

    switch (cref->op)
    {
        case NAME:     /* L145a */
        case CONST:
            return 1;
        case STAR:   /* L1450 */
            switch ((var0 = cref->left)->op)
            {
                case CONST:   /* L145a */
                case NAME:
                case YREG:
                case UREG:
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
    register expnode *cref;
#else
L149e (expnode *cref)
#endif
{
    switch (cref->op)
    {
        case PLUS:       /* L14ac */
        case MINUS:        /* L14ac */
            if ((is_regvar ((cref->left)->op)) &&
                    ((cref->right)->op == CONST))
            {
                return 1;
            }

    }

    return 0;
}

int 
#ifdef COCO
L14da (cref)
    register expnode *cref;
#else
L14da (expnode *cref)
#endif
{
    return (cref->sux < CHAR);
}

int 
#ifdef COCO
L14f2 (cref)
    register expnode *cref;
#else
L14f2 (expnode *cref)
#endif
{
    switch (cref->op)
    {
        case PLUS:       /* L1500 */
        case MINUS:        /* L1500 */
            return ((cref->left)->op == AMPER);
        case STRING:      /* L150a */
        case AMPER:  /* L150a */
            return 1;
    }

    return 0;
}

void 
#ifdef COCO
L152d (cref)
    register expnode *cref;
#else
L152d (expnode *cref)
#endif
{
    if (cref->op & 0x8000)
    {
        cref->op &= 0x7fff;
    }

    gen (LOAD, XREG, NODE, cref);
    cref->op = XIND;
    cref->val.num = 0;
}

void 
#ifdef COCO
L1567 (cref)
    expnode *cref;
#else
L1567 (expnode *cref)
#endif
{
    int var2;
    expnode *var0;

    register expnode *regptr;

    var0 = cref->right;
    regptr = cref->left;

    if (is_regvar ((cref->left)->op))        /* else L15fd */
    {
        if (L149e (var0))
        {
            L1c1d (var0);
        }
        else
        {
            L0d04 (var0);
        }

        switch (var0->op)
        {
            case AMPER:  /* L15ab */
                gen (LOADIM, regptr->op, NODE, var0->left); /* jump to L1794 */
                break;
            case CTOI:    /* L15bf */
                gen (LOAD, DREG, NODE, var0);
                /* fall through to default */
            default:           /* L15d7 */
                gen (LOAD, regptr->op, NODE, var0);
                break;
        }

        cref->op = regptr->op;    /* L1794 */
        cref->val.num = 0;
        return;
    }

    if ((L1440 (regptr)) && (regptr->type == CHAR)) /* L15fd */ /* else L1635 */
    {
        if ((L149e (var0)) || ( L14f2 (var0)))      /* else L1635 */
        {
            L0d04 (regptr);
            L1be4 (var0);
            return;       /* L16ab */
        }
    }

    /* L1635 */
    if (is_regvar (var0->op))   /* else L165c */
    {
        L0d04 (regptr);

        if (regptr->type == CHAR)       /* else L16ad */
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
        switch (regptr->op & 0x7fff)
        {
            case UIND:       /* L16a4 */
            case YIND:
                break;
            default:        /* LL168f */
                L1904 (regptr);
                break;
        }
    }

    gen (PUSH, var0->op, NODE, regptr);     /* L16a4 */
    cref->op = var0->op;                /* L1796 */
    cref->val.num = 0;
    return;         /* L1a96 */
}

void
#ifdef COCO
L16cb (cref, vartype)
    expnode *cref;
    int vartype;
#else
L16cb (expnode *cref, int vartype)
#endif
{
    expnode *var2;
    int var0;
    register expnode *regptr;

    var2 = cref->right;
    regptr = cref->left;
    L0d04 (regptr);
    vartype -= 80;      /* This may go back to the \*= thing in p1_08.c */

    if (regptr->type == UNSIGN)   /* else L1719 */
    {
        switch (vartype)
        {
            case DIV:      /* L16f9 */
                vartype = UDIV;
                break;
            case SHR:     /* L16fe */
                vartype = USHR;
                break;
            case MOD:    /* L1703 */
                vartype = UMOD;
                break;
        }
    }

    if (var0 = (regptr->op & 0x7fff))       /* else L17ef */
    {
        switch (vartype)
        {
            case PLUS:       /* L172f */
            case MINUS:        /* L172f */
                if (var2->op == CONST)     /* else L1766 */
                {
                    gen (LEA, var0, CONST,
                            (vartype == PLUS) ? var2->val.num :
                                                  -(var2->val.num));
                }
                else
                {
                    L0bc3 (var2);

                    if (vartype == MINUS)
                    {
#ifdef COCO
                        gen (NEG);
#else
                        gen (NEG, 0, 0, 0);
#endif
                    }

#ifdef COCO
                    gen ( LEA, var0, DREG);
#else
                    gen ( LEA, var0, DREG, 0);
#endif
                }

                cref->op = regptr->op;  /* L1794 */
                cref->val.num = 0;
                return;
            case AND:        /* L17a3 */
            case OR:
            case XOR:
                goto L17ed;
            default:           /* L17a7 */
                gen (PUSH, regptr->op NUL2);
                L0bc3 (var2);
                gen (vartype NUL3);
                break;  /* go to L18e4 */
        }
    }
    else
    {
L17ed:
        gen (LOAD, DREG, NODE NUL1);
        
        if (cref->type == CHAR)
        {
            gen (CTOI NUL3);
        }

        switch (vartype)
        {
            case AND:        /* L181c */
            case OR:
            case XOR:
            case PLUS:
            case MINUS:
                if (L1440 (var2))   /* else L186d (default) */
                {
                    L0d04 (var2);

                    switch (vartype)
                    {
                        case AND:        /* L1834 */
                        case OR:
                        case XOR:
                            L152d (var2);
                            break;
                    }

                    gen (vartype, DREG, NODE, var2);
                    break;
                }
                /* Fall through to default */
            default:           /* L186d */
                if ((var0 != YIND) && (var0 != UIND))
                {
                    L1904 (regptr);
                }

                gen (PUSH, DREG NUL2);
                L0bc3 (var2);

                if (vartype == MINUS)
                {
                    vartype = RSUB;
                }

                gen (vartype, DREG, STACK NUL1);
                break;
        }           /* end switch */
    }           /* end else = (regptr->op & 0x7fff) == 0  */

    /* L18e4 */
    gen (STORE, DREG, NODE NUL1);
    cref->op = DREG;
}

void
#ifdef COCO
L1904 (cref)
    register expnode *cref;
#else
L1904 (expnode *cref)
#endif
{
    if (cref->op != NAME)
    {
        L152d (cref);

        if (cref->val.num)
        {
            gen (LEA, XREG, CONST, cref->val.num);
        }

        gen (PUSH, XREG NUL2);
        cref->op = -32621;  /*0x806e;*/  /* wonder what this means? */
    }
}

void
#ifdef COCO
L1953 (cref)
    register expnode *cref;
#else
L1953 (expnode *cref)
#endif
{
    expnode *var2;
    int var0;

    L1c1d (var2 = cref->left);

    if ((var0 = var2->op) & 0x8000)     /* else L19d7 */
    {
        switch (var0 &= 0x7fff)
        {
            case NAME:     /* L1983 */
            case XIND:
            case YIND:
            case UIND:
                gen (LOAD, XREG, var0, var2->val.num);
                break;
            default:           /* L199e */
                L484b (var2, "indirection");
                break;
        }

        var0 = -32621;   /* ??? */       /* L19cb */
        cref->val.num = 0;
        /* go to L1a92 */
    }
    else
    {                /* L19d7 */
        switch (var0)
        {
            case UREG:      /* L19dc */
                var0 = UIND;
                goto L1a04;
            case YREG:    /* L19e1 */
                var0 = YIND;
                goto L1a04;
            case XREG:          /* L19e6 */
                var0 = XIND;
                goto L1a04;
            case XIND:          /* L19eb */
            case YIND:
            case UIND:
                var0 |= 0x80ff;
                goto L1a04;
            case NAME:     /* L19f5 */
                var0 = -32716;  /* -32716 */
                cref->modifier = var2->modifier;
L1a04:
                cref->val.num = var2->val.num;
                break;
            case DREG:          /* L1a0c */
                gen (LOAD, XREG, NODE, var2);
                var0 = XIND;
                cref->val.num = 0;
                break;
            case CONST:   /* L1a2f */
                cref->val.num = 0;
                cref->modifier = var2->val.num;
                var0 = NAME;
                break;
            default:           /* L1a3f */
                L484b (cref, "indirection");
                var0 = XIND;
                break;
        }
    }       /* end else i.e. var2->op) & 0x8000 == 0 */

    /* L1a92 */
    cref->op = var0;
}

void
#ifdef COCO
L1a9a (cref, val)
    expnode *cref;
    int val;
#else
L1a9a (expnode *cref, int val)
#endif
{
    /* 8 bytes static storage */
    int var6;
    int var4;
    int var2;
    int var0;
    register expnode *_leftref;

    _leftref = cref->left;

    L0d04 (_leftref);
    var2 = cref->op;
    
    if (is_regvar (var0 = _leftref->op))        /* else L1afa */
    {
        switch (var2)
        {
            case INCAFT:
            case DECAFT:
                if (val == DREG)     /* else L1ae6 */
                {
                    gen (LOAD, val, NODE, _leftref);
                    break;
                }
            default:
                val = var0;
                break;      /* go to L1b2b */
        }
    }
    else
    {
        if ((val == XREG) && ((var0 & 0x7fff) == NAME))     /* L1afa */
        {
            val = DREG;
        }
        
        gen (LOAD, val, NODE, _leftref);
        var0 = val;
    }

    var6 = cref->val.num;        /* L1b2b */

    switch (var2)
    {
        case DECBEF:        /* L1b35 */
        case DECAFT:
            var6 = -var6;

        default:                /* L1b3d */
            if (var0 == DREG)
            {
                gen ( PLUS, var0, CONST, var6);
                break;
            }
            gen (LEA, var0, CONST, var6);
            break;
    }

    gen (STORE, var0, NODE, _leftref);

    switch (var2)
    {
        default:                /* L1b97 */
            cref->val.num = 0;
            break;
        case INCAFT:       /* L1b9b */
        case DECAFT:
            if (var0 == DREG)
            {
                gen (MINUS, DREG, CONST, var6);
            }
            else
            {
                cref->val.num = -var6;
            }
            break;
    }

    cref->op = val;
    D0019 = 0;
}

void
#ifdef COCO
L1be4 (cref)
    register expnode *cref;
#else
L1be4 (expnode *cref)
#endif
{
    L1c1d (cref);

    if ((cref->op != XREG) || (cref->val.num != 0))    /* else L1c16 */
    {
        gen (LOAD, XREG, NODE, cref);
    }

    cref->op = XREG;
}

void
#ifdef COCO
L1c1d (cref)
    expnode *cref;
#else
L1c1d (expnode *cref)
#endif
{
    expnode *var6;
    int var4;
    int var2;
    int var0;

    register expnode *_crleft;

    _crleft = cref->left;
    var6 = cref->right;
    var0 = XREG;
    
    switch (var2 = cref->op)
    {
        case STAR:   /* L1c41 */
            L1953 (cref);
            return;
        case NAME:     /* L1eaf */
        case YREG:
        case UREG:
        case CONST:
        case STRING:
            return;
        case INCAFT:  /* L1c4b */
        case INCBEF:
        case DECBEF:
        case DECAFT:
            L1a9a (cref, XREG);
            return;
        case AMPER:  /* L1c5c */
            gen (127, XREG, NODE, cref);
            cref->val.num = 0;
            break;
        case CTOI:    /* L1c77 */
            L0bc3 (cref);
            return;
        case MINUS:        /* L1c81 */
            if ((_crleft->op != AMPER) && (var6->sux))
            {                                   /* go to L1d30 */
                goto L1e42;
            }
                /* Is this correct????  */
        case PLUS:       /* L1c92 */
            if ((is_regvar (_crleft->op)) || (_crleft->op == AMPER))
            {       /* else L1cf9 */
                if (var6->op == CONST)   /* L1ca5 */ /* else L1cc1 */
                {
                    L1c1d (_crleft);
                    var0 = _crleft->op;
                    var4 = var6->val.num;
                    
                    /* jump to L1e26 */

                    /*if (var2 == PLUS)
                    {
                        _crleft->val.num += var4;
                    }
                    else
                    {
                        _crleft->val.num -= var4;
                    }

                    break;*/
                }
                else
                {
                    L0bc3 (var6);       /* L1cc1 */
                    L1c1d (_crleft);

                    if (var2 == MINUS)      /* else L1ce3 */
                    {
#ifdef COCO
                        gen (NEG);
#else
                        gen (NEG, 0, 0, 0);
#endif
                    }

#ifdef COCO
                    gen (LEAX, DREG, _crleft->op);      /* L1ce3 */
#else
                    gen (LEAX, DREG, _crleft->op, 0);
#endif
                    var4 = 0;
                }
            }
            else
            {                    /* L1cf9 */
                if ((var2 == PLUS) && (_crleft->sux < var6->sux))
                {
                    expnode *_tmpref = _crleft;

                    _crleft = var6;
                    var6 = _tmpref;
                }

                if ( ! L1440 (var6))        /* L1d18 */     /* else L1d35 */
                {
                    if ( ! is_regvar (var6->op))
                    {
                        goto L1e42;
                    }
                }

                L1c1d (_crleft);        /* L1d35 */

                switch (_crleft->op & 0x7fff)
                {
                    case DREG:          /* L1d45 */
                        if ((var2 == PLUS) &&     /* else L1d69 */
                                (var6->op == CONST))
                        {
                            L0bf7 (var6);
                            _crleft->val.num = 0;
                            goto L1e0a;
                        }


                    case NAME:
                    case STRING:
                    case XIND:          /* L1d69 */
                    case YIND:
                    case UIND:
                        gen (LOAD, XREG, NODE, _crleft);
                        _crleft->val.num = 0;
                        break;
                    case XREG:          /* L1dd5 */
                        break;
                    case YREG:    /* L1d85 */
                    case UREG:
                        var0 = _crleft->op;
                        break;
                    default:           /* L1d8b */
                        L484b ( _crleft, "x translate");
                        break;
                }

                if (var6->op == CONST)     /* L1dd5 */
                {
                    var4 = var6->val.num;
                }
                else
                {
                    L0bc3 (var6);
                    
                    if (var2 == MINUS)  /* else L1e0c */
                    {
#ifdef COCO
                        gen (NEG, 0, 0);
#else
                        gen (NEG, 0, 0, 0);
#endif
                    }

L1e0a:
#ifdef COCO
                    gen (LEAX, DREG, var0);
#else
                    gen (LEAX, DREG, var0, 0);
#endif
                    var0 = XREG;
                    var4 = 0;
                }
            }

                /* L1e26 */
            /*if (var2 == PLUS)
            {
                cref->val.num = _crleft->val.num + var4;
            }
            else
            {
                cref->val.num = _crleft->val.num - var4;
            }*/
            cref->val.num = _crleft->val.num + ((var2 == PLUS) ? var4 : -var4);
            
            break;
        default:           /* L1e44 */
L1e42:
            L0d04 (cref);
            return;
    }

    cref->op = var0;    /* L1ea9 */
}

int
#ifdef COCO
is_regvar (vtyp)
    int vtyp;
#else
is_regvar (int vtyp)
#endif
{
    return ((vtyp == UREG) || (vtyp == YREG));
}
