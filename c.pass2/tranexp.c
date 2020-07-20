/* ************************************************************************ *
 * p2_02.c - part 2 for c.pass2                                             *
 *                                                                          *
 * $Id: p2_02.c 18 2008-05-19 21:54:22Z dlb $::                                                                   *
 * ************************************************************************ */

#include "pass2.h"

#ifdef COCO
expnode *tranexp ();
#else
#endif

void
#ifdef COCO
lddexp (cref)
    register expnode *cref;
#else
lddexp (expnode *cref)
#endif
{
    loadexp (cref);

    if (cref->op != DREG)
    {
        gen (LOAD, DREG, NODE, cref);
        cref->op = DREG;
    }
}

void
#ifdef COCO
ldxexp (cref)
    register expnode *cref;
#else
ldxexp (expnode *cref)
#endif
{
    tranxexp (cref);

    if (cref->op != XREG)
    {
        gen (LOAD, XREG, NODE, cref);
        cref->op = XREG;
    }
}

void
#ifdef COCO
loadexp (cref)
    register expnode *cref;
#else
loadexp (expnode *cref)
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
            tranexp (cref);
            doload (cref);
    }
}

void
#ifdef COCO
doload (cref)
    register expnode *cref;
#else
doload ( expnode *cref)
#endif
{
    switch (cref->op)
    {
        case STRING:      /* L0c7c */
            gen (LOAD, XREG, NODE, cref);
            cref->op = XREG;
            cref->val.num = 0;
            break;
        case AMPER:    /* L0c9e */
            gen (LOADIM, XREG, NODE, cref->left);
            cref->op = XREG;
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
            cref->op = DREG;
            break;
    }
}

expnode *
#ifdef COCO
tranexp (cref)
    register expnode *cref;
#else
tranexp (expnode *cref)
#endif
{
    int _vartype;

    if ((_vartype = cref->op) == COMMA)       /* else L0d4d */
    {
        expnode *_vrRight = cref->right;

        L4a69 (tranexp (cref->left));
        L4acd (_vrRight, cref);
        L4a8a (_vrRight);
        tranexp ( cref);      /* go to L0ef7 */
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
                    tranbinop (_vartype, cref); /* go to L0ef7 */
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
                            doass (cref);
                            break;
                        case CTOI:    /* L0d9f */
                            tranexp (cref->left);
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
                            dostar (cref);
                            break;
                        case NOT:    /* L0de6 */
                        case DBLAND:
                        case DBLOR:
                            dobool (cref);
                            break;
                        case COMPL:      /* L0ded */
                        case NEG:
                            lddexp (cref->left);
#ifdef COCO
                            gen (_vartype);
#else
                            gen (_vartype, 0, 0,0);
#endif
                            cref->op = 112;
                            break;
                        case QUERY:    /* L0e01 */
                            doquery (cref, lddexp);
                            cref->op = 112;
                            break;
                        case INCBEF:    /* L0e16 */
                        case INCAFT:
                        case DECBEF:
                        case DECAFT:
                            dotoggle (cref, 112);
                            break;
                        case CALL:     /* L0e22 */
                            docall (cref);
                            break;
                        default:           /* L0e2c */
                            if (_vartype >= ASSPLUS)   /* 160 */
                            {
                                assop ( cref, _vartype);
                            }
                            else
                            {
                                comperr (cref, "translation");
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
tranbinop (op, node)
    int op;
    expnode *node;
#else
tranbinop (int op, expnode *node)
#endif
{
    /* 6 bytes static vars */
    register expnode *lhs;
    expnode *rhs;  /* v4 */
    int v2;
    unsigned int var0;

    
    lhs = node->left;
    rhs = node->right;

    /* First modify op if necessary */

    if (lhs->type == UNSIGN)
    {
        switch (op)
        {
            case DIV:      /* L0f1d */
                op = UDIV;
                break;
            case MOD:    /* L0f22 */
                op = UMOD;
                break;
            case SHR:     /* L0f27 */
                op = USHR;
                break;
            default:           /* L0f73 */
                break;
        }
    }
    else
    {
        switch (op)
        {
            case PLUS:       /* L0f43 */
            case MINUS:        /* L0f43 */
                if ((lhs->op == AMPER) && 
                            (rhs->op != CONST))
                {
                    tranxexp (node);
                    D0019 = 0;
                    return;
                }

                break;
        }
    }

    switch (op)
    {                   /* L120d = "break" */
        case MINUS:        /* L0f78 */
            if ( ! L22ca (rhs) )    /* else L0faa */
            {
                loadexp (rhs);
#ifdef COCO
                gen (122, rhs->op);
#else
                gen (122, rhs->op, 0, 0);
#endif
                rhs->op = 110;
                lddexp (lhs);
            }
            else
            {
                lddexp (lhs);      /* L0faa */
                tranexp (rhs);
            }

            gen (MINUS, DREG, NODE, rhs);
            break; /* go to L120d */
        case AND:
        case OR:
        case XOR:        /* L0fce */
        case PLUS:
            if ( ((L22ca (lhs)) && ! (L22ca (rhs))) || (lhs->op == CONST))
            {
                expnode *__tmpref = lhs;

                lhs = rhs;
                rhs = __tmpref;
            }

            if (is_regvar (lhs->op))      /* L0ff6 */   /* else L1021 */
            {
#ifdef COCO
                gen (122, lhs->op);     /* L1003 */
#else
                gen (122, lhs->op, 0, 0);
#endif
                lddexp ( rhs);
                rhs->op = 110;        /* go to 1052 */
            }
            else
            {
                lddexp (lhs);      /* L1021 */

                if ( ! L22ca (rhs))
                {
#ifdef COCO
                    gen (122, 112);
#else
                    gen (122, DREG, 0, 0);
#endif
                    lddexp ( rhs);
                    rhs->op = 110;        /* go to 1052 */
                }
                else
                {
                    tranexp (rhs);      /* L1038 */

                    if (op != PLUS)
                    {
                        getinx ( rhs);
                    }
                }
            }

            gen (op, DREG, NODE, rhs);
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
            dobool (node);
            break;
        case 77:           /* L1077 */
        case SHR:
        case SHL:
            if ((rhs->op) == CONST)      /* else L10db */
            {
                var0 = rhs->val.num;
L108b:
                if (var0 <= STRUCT)  /* 4 */     /* else L10db */
                {
                    lddexp ( lhs);

                    while (var0--)
                    {
                        switch (op)
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
            if (lhs->op == CONST)    /* else L10f3 */
            {
                expnode *_tmpref;

                _tmpref = lhs;
                lhs = rhs;
                rhs = _tmpref;
            }       /* fall through to next case */
        case UDIV:           /* L10f3 */
            if ((rhs->op == CONST) &&
                        (var0 = isashift ( rhs->val.num)))    /* else L112b */
            {
                rhs->val.num = var0;

                op = (op == TIMES) ? SHL : USHR;    /* L1122 */
                goto L108b;
            }
        case DIV:      /* L112b */
        case 76:           /* L112b */
        case MOD:    /* L112b */
L1129:
            loadexp (lhs);
#ifdef COCO
            gen (PUSH, lhs->op);
#else
            gen (PUSH, lhs->op, 0, 0);
#endif
            lddexp ( rhs);
#ifdef COCO
            gen (op);
#else
            gen (op, 0, 0, 0);
#endif
            break;
        default:           /* L1155 */
            comperr (node, "binary op.");
            break;
    }   /* end switch op */

#ifdef COCO
    /* Following jump-label is not needed - vestige from the old source */
L120d:
#endif
    D0019 = 0;
L1213:
    node->op = DREG;
}

int
#ifdef COCO
isashift (cmd_val)
    int cmd_val;
#else
isashift (int cmd_val)
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
dobool (cref)
    register expnode *cref;
#else
dobool (expnode *cref)
#endif
{
    int l1;
    int l2;

    L1f13 (cref, (l1 = ++D000b), (l2 = ++D000b), 1);
    L4414 (l1);
    gen (LOAD, DREG, CONST, 1);

#ifdef COCO
    gen (JMP, (l2 = ++D000b), 1);
#else
    gen (JMP, (l2 = ++D000b), 1, 0);
#endif
    L4414 (l2);

    gen (LOAD, DREG, CONST, 0);
    L4414 (l1);
    cref->op = DREG;
}

void
#ifdef COCO
doquery (cref, fnc)
    register expnode *cref;
    void (*fnc)();
#else
doquery (expnode *cref, void (*fnc)())
#endif
{
    int l1;
    int var2;
    int l2;

    L1f13 (cref->left, (l1 = ++D000b), (l2 = ++D000b), 1);
    cref = cref->right;
    L4414 (l1);
    (*fnc) (cref->left);
#ifdef COCO
    gen (JMP, (l1 = ++D000b), 0);
#else
    gen (JMP, (l1 = ++D000b), 0, 0);
#endif
    L4414 (l2);
    (*fnc) (cref->right);
    L4414 (var2);
}
void
#ifdef COCO
docall (node)
    expnode *node;
#else
docall (expnode *node)
#endif
{
    expnode *rhs;
    int var0;

    var0 = sp;
    rhs = node;

    while (rhs = rhs->right)
    {
        register expnode *lhs = rhs->left;    /* L1379 */;

        if (lhs->type == LONG)     /* else L13a8 */
        {
            if (lhs->op == LCONST)
            {
                L294b (lhs);  /* go to L1401 */
                continue;
            }
            else
            {
                L2505 (lhs);
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
            if ((lhs->type == FLOAT) || (lhs->type == DOUBLE))
            {
                L29fc (lhs);
#ifdef COCO
                gen (DBLOP, STACK);
#else
                gen (DBLOP, STACK, 0, 0);
#endif
            }
            else
            {
                tranexp (lhs);

                switch (lhs->op)
                {
                    case DREG:          /* L13f3 */
                    case XREG:
                    case UREG:
                    case YREG:
                        break;
                    default:           /* L13d4 */
                        doload (lhs);
                        break;
                }

                gen (PUSH, lhs->op NUL2);
            }

        }
    }       /* end while (rhs = cr->right)  ( L1401 ) */

    tranexp (node->left);
#ifdef COCO
    gen (CALL, NODE, node->left);
#else
    gen (CALL, NODE, node->left, 0);
#endif
    sp = modstk (var0);
    node->op = DREG;
}


int 
#ifdef COCO
isdleaf (cref)
    register expnode *cref;
#else
isdleaf (expnode *cref)
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
                    return regandcon (var0);
            }
    }

    return 0;
}

int 
#ifdef COCO
regandcon (cref)
    register expnode *cref;
#else
regandcon (expnode *cref)
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
isxleaf (cref)
    register expnode *cref;
#else
isxleaf (expnode *cref)
#endif
{
    return (cref->sux < CHAR);
}

int 
#ifdef COCO
isaddress (cref)
    register expnode *cref;
#else
isaddress (expnode *cref)
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
getinx (cref)
    register expnode *cref;
#else
getinx (expnode *cref)
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
doass (node)
    expnode *node;
#else
doass (expnode *node)
#endif
{
    int var2;
    expnode *rhs;

    register expnode *lhs;

    rhs = node->right;
    lhs = node->left;

    if (is_regvar ((node->left)->op))        /* else L15fd */
    {
        if (regandcon (rhs))
        {
            tranxexp (rhs);
        }
        else
        {
            tranexp (rhs);
        }

        switch (rhs->op)
        {
            case AMPER:  /* L15ab */
                gen (LOADIM, lhs->op, NODE, rhs->left); /* jump to L1794 */
                break;
            case CTOI:    /* L15bf */
                gen (LOAD, DREG, NODE, rhs);
                /* fall through to default */
            default:           /* L15d7 */
                gen (LOAD, lhs->op, NODE, rhs);
                break;
        }

        node->op = lhs->op;    /* L1794 */
        node->val.num = 0;
        return;
    }

    if ((isdleaf (lhs)) && (lhs->type != CHAR)) /* L15fd */ /* else L1635 */
    {
        if ((regandcon (rhs)) || ( isaddress (rhs)))      /* else L1635 */
        {
            tranexp (lhs);
            loadxexp (rhs);
            return;       /* L16ab */
        }
    }

    /* L1635 */
    if (is_regvar (rhs->op))   /* else L165c */
    {
        tranexp (lhs);

        if (lhs->type == CHAR)       /* else L16ad */
        {
            lddexp (rhs);
            return;
        }
    }

    if (isxleaf (lhs))
    {
        lddexp (rhs);
        return;
    }

    tranexp (lhs);     /* L1675 */

    if ( ! isdleaf (rhs))
    {
        switch (lhs->op & 0x7fff)
        {
            case UIND:       /* L16a4 */
            case YIND:
                break;
            default:        /* LL168f */
                stackx (lhs);
                break;
        }
    }

    gen (STORE, rhs->op, NODE, lhs);     /* L16a4 */
    node->op = rhs->op;                /* L1796 */
    node->val.num = 0;
    return;         /* L1a96 */
}

void
#ifdef COCO
assop (node, op)
    expnode *node;
    int op;
#else
assop (expnode *node, int op)
#endif
{
    register expnode *lhs;
    expnode *rhs;
    int var0;

    rhs = node->right;
    lhs = node->left;
    tranexp (lhs);
    op -= 80;      /* This may go back to the \*= thing in p1_08.c */

    if (lhs->type == UNSIGN)   /* else L1719 */
    {
        switch (op)
        {
            case DIV:      /* L16f9 */
                op = UDIV;
                break;
            case SHR:     /* L16fe */
                op = USHR;
                break;
            case MOD:    /* L1703 */
                op = UMOD;
                break;
        }
    }

    if (var0 = (lhs->op & 0x7fff))       /* else L17ef */
    {
        switch (op)
        {
            case PLUS:       /* L172f */
            case MINUS:        /* L172f */
                if (rhs->op == CONST)     /* else L1766 */
                {
                    gen (LEA, var0, CONST,
                            (op == PLUS) ? rhs->val.num :
                                                  -(rhs->val.num));
                }
                else
                {
                    lddexp (rhs);

                    if (op == MINUS)
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

                node->op = lhs->op;  /* L1794 */
                node->val.num = 0;
                return;
            case AND:        /* L17a3 */
            case OR:
            case XOR:
                goto L17ed;
            default:           /* L17a7 */
                gen (PUSH, lhs->op NUL2);
                lddexp (rhs);
                gen (op NUL3);
                break;  /* go to L18e4 */
        }
    }
    else
    {
L17ed:
        gen (LOAD, DREG, NODE NUL1);
        
        if (node->type == CHAR)
        {
            gen (CTOI NUL3);
        }

        switch (op)
        {
            case AND:        /* L181c */
            case OR:
            case XOR:
            case PLUS:
            case MINUS:
                if (isdleaf (rhs))   /* else L186d (default) */
                {
                    tranexp (rhs);

                    switch (op)
                    {
                        case AND:        /* L1834 */
                        case OR:
                        case XOR:
                            getinx (rhs);
                            break;
                    }

                    gen (op, DREG, NODE, rhs);
                    break;
                }
                /* Fall through to default */
            default:           /* L186d */
                if ((var0 != YIND) && (var0 != UIND))
                {
                    stackx (lhs);
                }

                gen (PUSH, DREG NUL2);
                lddexp (rhs);

                if (op == MINUS)
                {
                    op = RSUB;
                }

                gen (op, DREG, STACK NUL1);
                break;
        }           /* end switch */
    }           /* end else = (lhs->op & 0x7fff) == 0  */

    /* L18e4 */
    gen (STORE, DREG, NODE NUL1);
    node->op = DREG;
}

void
#ifdef COCO
stackx (cref)
    register expnode *cref;
#else
stackx (expnode *cref)
#endif
{
    if (cref->op != NAME)
    {
        getinx (cref);

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
dostar (cref)
    register expnode *cref;
#else
dostar (expnode *cref)
#endif
{
    expnode *var2;
    int var0;

    tranxexp (var2 = cref->left);

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
                comperr (var2, "indirection");
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
                cref->val.sp = var2->val.sp;
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
                comperr (cref, "indirection");
                var0 = XIND;
                break;
        }
    }       /* end else i.e. var2->op) & 0x8000 == 0 */

    /* L1a92 */
    cref->op = var0;
}

void
#ifdef COCO
dotoggle (node, dest)
    expnode *node;
    int dest;
#else
dotoggle (expnode *node, int dest)
#endif
{
    int size;
    int var4;
    int op;
    int reg;
    register expnode *lhs;

    lhs = node->left;

    tranexp (lhs);
    op = node->op;
    
    if (is_regvar (reg = lhs->op))        /* else L1afa */
    {
        switch (op)
        {
            case INCAFT:
            case DECAFT:
                if (dest == DREG)     /* else L1ae6 */
                {
                    gen (LOAD, dest, NODE, lhs);
                    break;
                }
            default:
                dest = reg;
                break;      /* go to L1b2b */
        }
    }
    else
    {
        if ((dest == XREG) && ((reg & 0x7fff) == NAME))     /* L1afa */
        {
            dest = DREG;
        }
        
        gen (LOAD, dest, NODE, lhs);
        reg = dest;
    }

    size = node->val.num;        /* L1b2b */

    switch (op)
    {
        case DECBEF:        /* L1b35 */
        case DECAFT:
            size = -size;

        default:                /* L1b3d */
            if (reg == DREG)
            {
                gen ( PLUS, reg, CONST, size);
                break;
            }
            gen (LEA, reg, CONST, size);
            break;
    }

    gen (STORE, reg, NODE, lhs);

    switch (op)
    {
        default:                /* L1b97 */
            node->val.num = 0;
            break;
        case INCAFT:       /* L1b9b */
        case DECAFT:
            if (reg == DREG)
            {
                gen (MINUS, DREG, CONST, size);
            }
            else
            {
                node->val.num = -size;
            }
            break;
    }

    node->op = dest;
    D0019 = 0;
}

void
#ifdef COCO
loadxexp (cref)
    register expnode *cref;
#else
loadxexp (expnode *cref)
#endif
{
    tranxexp (cref);

    if ((cref->op != XREG) || (cref->val.num != 0))    /* else L1c16 */
    {
        gen (LOAD, XREG, NODE, cref);
    }

    cref->op = XREG;
}

void
#ifdef COCO
tranxexp (node)
    expnode *node;
#else
tranxexp (expnode *node)
#endif
{
    register expnode *lhs;
    expnode *rhs;
    int var4;
    int op;
    int newop;

    lhs = node->left;
    rhs = node->right;
    newop = XREG;
    
    switch (op = node->op)
    {
        case STAR:   /* L1c41 */
            dostar (node);
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
            dotoggle (node, XREG);
            return;
        case AMPER:  /* L1c5c */
            gen (127, XREG, NODE, node);
            node->val.num = 0;
            break;
        case CTOI:    /* L1c77 */
            lddexp (node);
            return;
        case MINUS:        /* L1c81 */
            if ((lhs->op != AMPER) && (rhs->sux))
            {                                   /* go to L1d30 */
                goto L1e42;
            }
                /* Is this correct????  */
        case PLUS:       /* L1c92 */
            if ((is_regvar (lhs->op)) || (lhs->op == AMPER))
            {       /* else L1cf9 */
                if (rhs->op == CONST)   /* L1ca5 */ /* else L1cc1 */
                {
                    tranxexp (lhs);
                    newop = lhs->op;
                    var4 = rhs->val.num;
                    
                    /* jump to L1e26 */

                    /*if (op == PLUS)
                    {
                        lhs->val.num += var4;
                    }
                    else
                    {
                        lhs->val.num -= var4;
                    }

                    break;*/
                }
                else
                {
                    lddexp (rhs);       /* L1cc1 */
                    tranxexp (lhs);

                    if (op == MINUS)      /* else L1ce3 */
                    {
#ifdef COCO
                        gen (NEG);
#else
                        gen (NEG, 0, 0, 0);
#endif
                    }

#ifdef COCO
                    gen (LEAX, DREG, lhs->op);      /* L1ce3 */
#else
                    gen (LEAX, DREG, lhs->op, 0);
#endif
                    var4 = 0;
                }
            }
            else
            {                    /* L1cf9 */
                if ((op == PLUS) && (lhs->sux < rhs->sux))
                {
                    expnode *_tmpref = lhs;

                    lhs = rhs;
                    rhs = _tmpref;
                }

                if ( ! isdleaf (rhs))        /* L1d18 */     /* else L1d35 */
                {
                    if ( ! is_regvar (rhs->op))
                    {
                        goto L1e42;
                    }
                }

                tranxexp (lhs);        /* L1d35 */

                switch (lhs->op & 0x7fff)
                {
                    case DREG:          /* L1d45 */
                        if ((op == PLUS) &&     /* else L1d69 */
                                (rhs->op == CONST))
                        {
                            ldxexp (rhs);
                            lhs->val.num = 0;
                            goto L1e0a;
                        }


                    case NAME:
                    case STRING:
                    case XIND:          /* L1d69 */
                    case YIND:
                    case UIND:
                        gen (LOAD, XREG, NODE, lhs);
                        lhs->val.num = 0;
                        break;
                    case XREG:          /* L1dd5 */
                        break;
                    case YREG:    /* L1d85 */
                    case UREG:
                        newop = lhs->op;
                        break;
                    default:           /* L1d8b */
                        comperr ( lhs, "x translate");
                        break;
                }

                if (rhs->op == CONST)     /* L1dd5 */
                {
                    var4 = rhs->val.num;
                }
                else
                {
                    lddexp (rhs);
                    
                    if (op == MINUS)  /* else L1e0c */
                    {
#ifdef COCO
                        gen (NEG, 0, 0);
#else
                        gen (NEG, 0, 0, 0);
#endif
                    }

L1e0a:
#ifdef COCO
                    gen (LEAX, DREG, newop);
#else
                    gen (LEAX, DREG, newop, 0);
#endif
                    newop = XREG;
                    var4 = 0;
                }
            }

                /* L1e26 */
            /*if (op == PLUS)
            {
                node->val.num = lhs->val.num + var4;
            }
            else
            {
                node->val.num = lhs->val.num - var4;
            }*/
            node->val.num = lhs->val.num + ((op == PLUS) ? var4 : -var4);
            
            break;
        default:           /* L1e44 */
L1e42:
            tranexp (node);
            return;
    }

    node->op = newop;    /* L1ea9 */
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
