/* ************************************************************************ *
 * p2_03.c - part 3 for c.pass2                                             *
 *                                                                          *
 * $Id: p2_03.c 18 2008-05-19 21:54:22Z dlb $                               *
 * ************************************************************************ */

#include "pass2.h"

void
#ifdef COCO
L1f13 (cref, parm2, parm3, parm4)
    register expnode *cref;
    int parm2, parm3, parm4;
#else
L1f13 (expnode *cref, int parm2, int parm3, int parm4)
#endif
{
    int var2;
    int var0;

    switch (var2 =  cref->op)
    {           /* break = L20e9 */
        case DBLAND:     /* L1f28 */
            L1f13 (cref->left, (var0 = ++D000b), parm3, 1);
            goto L1f66;
        case DBLOR:       /* L1f48 */
            L1f13 (cref->left, parm2, (var0 = ++D000b), 0);
L1f66:
            L4414 (var0);
            L1f13 (cref->right, parm2, parm3, parm4);
            break;                      /* go to L20e9 */
        case NOT:     /* L1f72 */
            L1f13 (cref->left, parm3, parm2, (1 - parm4));
            break;
        case EQ:
        case NEQ:
        case LEQ:
        case LT:
        case GEQ:      /* L1f87 */
        case 95:
        case ULEQ:
        case 97:
        case 98:
        case 99:
            L20ed (var2, cref, parm2, parm3, parm4);
            break;
        case CONST:
        case FCONST:     /* L1fa1 */
        case LCONST:
            if (cref->val.num && ! parm4)
            {
#ifdef COCO
                gen (JMP, parm2, 0);
#else
                gen (JMP, parm2, 0, 0);
#endif
            }
            else
            {
                if (parm4 && ( ! cref->val.num))
                {
#ifdef COCO
                    gen (JMP, parm3, 0);
#else
                    gen (JMP, parm3, 0, 0);
#endif
                }
            }
            break;
        case COMMA:      /* L1fcb */
            L0d04 (cref->left);
            L1f13 (cref->right, parm2, parm3, parm4);
            break;
        default:           /* L1fec */
            if (cref->type == LONG)
            {
                L2505 (cref);
#ifdef COCO
                gen (LONGOP, TEST);
#else
                gen (LONGOP, TEST, 0, 0);
#endif
                /* go to L204d */
            }
            else
            {
                if ((cref->type == FLOAT) || (cref->type == DOUBLE))
                {               /* else L2042 */
                    if (cref->op == FTOD)
                    {
                        cref = cref->left;
                    }

                    L29fc (cref);           /* L2026 */
#ifdef COCO
                    gen (DBLOP, TEST, cref->type);
#else
                    gen (DBLOP, TEST, cref->type, 0);
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
                gen (CNDJMP, EQ, parm3);
#else
                gen (CNDJMP, EQ, parm3, 0);
#endif
            }
            else
            {
#ifdef COCO
                gen (CNDJMP, NEQ, parm2);
#else
                gen (CNDJMP, NEQ, parm2, 0);
#endif
            }

            break;
    }
}

void
#ifdef COCO
L20ed (parm1, cref, parm3, parm4, parm5)
    int parm1;
    expnode *cref;
    int parm3, parm4, parm5;
#else
L20ed (int parm1, expnode *cref, int parm3, int parm4, int parm5)
        /* +10            +12        +14        +16        +18  */
#endif
{
    expnode *var4;
    int var2;
    expnode *var0 = cref->left;

    register expnode *_crRight = cref->right;

    var2 = (parm5 ? parm4 : parm3);

    parm1 = (parm5 ? L2466 (parm1) : parm1);

    if (var0->type == LONG)
    {
        L2520 (cref);       /* go to L214b */
        goto L22b2;
    }
    else
    {           /* L2134 */
        if ((var0->type == FLOAT) || (var0->type == DOUBLE))
        {
            L2a17 (cref);
            goto L22b2;

        }
    }

    /* Check out the logic for this block ... it's pretty complicated */
    /* L2152 */
    if ((L24e6 ( var0)) ||
            ((L22ca (var0)) && ( ! L22ca (_crRight))) ||
            ((is_regvar (_crRight->op)) &&
                        ( ! is_regvar (var0->op))))  /* else L219c */
    {
        var4 = var0;        /* L2189 */
        var0 = _crRight;
        _crRight = var4;
        parm1 = L249e (parm1);
    }

    var4 = var0->op;        /* L219c */

    if (is_regvar (var4))       /* else L221f */
    {
        L0d04 (_crRight);

        switch (_crRight->op)
        {
            case AMPER:           /* L21b8 */
                L0c2d (_crRight);
                goto L21e0;
            case CTOI:    /* L21c3 */
                gen (LOAD, DREG, NODE, _crRight);
                _crRight->op = DREG;
                /* fall through to next case */
            case XREG:      /* L21e2 */
            case YREG:      /* L21e2 */
            case UREG:      /* L21e2 */
            case DREG:      /* L21e2 */
L21e0:
#ifdef COCO
                gen (PUSH, _crRight->op);
#else
                gen (PUSH, _crRight->op, 0, 0);
#endif
                 _crRight->op = STACK;    /* go to L229b */
            default:           /* L229b */
                 break;
        }
    }       /* end if (is_regvar...) */
    else
    {
        if ((L24e6 (_crRight)) && (parm1 < ULEQ))       /* L221f */
        {
            L2323 (var0);       /* go to L22b4 */
            /* this should probably have been goto L22b2; */
#ifdef COCO
            gen (CNDJMP, parm1, var2);
#else
            gen (CNDJMP, parm1, var2, 0);
#endif
            return;
        }
        else
        {
            L0c2d (var0);       /* L223c */
            var4 = var0->op;
            
            if ((L1440 (_crRight)) || ((var4 == DREG) && L22ca (_crRight)))
            {
                L0d04 (_crRight);   /* go to L229b */
            }
            else
            {
#ifdef COCO
                gen (PUSH, var4);
#else
                gen (PUSH, var4, 0, 0);
#endif
                var0->op = STACK;
                L0c2d (_crRight);
                var4 = _crRight->op;
                _crRight = var0;
                parm1 = L249e (parm1);
            }
        }
    }       /* end else => if ! is_regvar... */

    gen (COMPARE, var4, NODE, _crRight); /* L229b... */
L22b2:
#ifdef COCO
    gen (CNDJMP, parm1, var2);
#else
    gen (CNDJMP, parm1, var2, 0);
#endif
}

int
#ifdef COCO
L22ca (cref)
    expnode *cref;
#else
L22ca (expnode *cref)
#endif
{
    switch (cref->op)
    {
        case NAME:      /* L22d8 */
        case CONST:
            return 1;
        case STAR:    /* L22dd */
            return L14da (cref);
        default:
            return 0;
    }
}

#ifdef COCO
p2_03_notused (parm1, parm2)
    expnode *parm1;
    int parm2;
{
    if ((parm1->op == NAME) &&
                    ((LBLDEF *)(parm1->val.num)->gentyp == AUTO))
    {
        return 1;
    }

    return 0;
}
#endif

void
#ifdef COCO
L2323 (cref)
    register expnode *cref;
#else
L2323 (expnode *cref)
#endif
{
    expnode *var2;
    int var0 = 0;

    switch (cref->op)
    {                                       /* break = L23fe */
        case AND:        /* L2337 */
            if ((((var2 = cref->right)->op) != CONST) ||
                        ((unsigned int)(var2->val.num) > (unsigned int)255))
            {
                    var0 = 1;
            }

            break;

        case ASSIGN:      /* L2353 */
            if ((is_regvar ((cref->left)->op)) &&
                                ( ! L22ca (cref->right)))
            {
                var0 = 1;
            }

            break;

        case INCAFT:
        case DECAFT:
        case DECBEF:
        case INCBEF:
        case ASSPLUS:
        case ASSMIN:     /* L2371 */
        case ASSAND:
        case ASSOR:
        case ASSXOR:
            if ( ! is_regvar ((cref->left)->op))
            {
                break;
            }
        case YREG:
        case UREG:
        case OR:
        case XOR:      /* L2380 */
        case COMPL:
        case NEG:
        case CALL:
            var0 = 1;
            break;
    }

    D0019 = 0;
    L0d04 (cref);

    switch (cref->op)
    {
        case XREG:
        case DREG:          /* L240d */
        case YREG:
        case UREG:
            if (var0 || D0019)
            {
                gen (COMPARE, cref->op, CONST, 0);
            }

            break;

        case CTOI:    /* L2427 */
            gen (LOAD, DREG, NODE, (cref = cref->left));
            break;
        default:           /* L2429 */
            gen (LOAD, DREG, NODE, cref);
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
        case EQ:        /* L2472 */
            return NEQ;
        case NEQ:       /* L2477 */
            return EQ;
        default:            /* L247c */
            return (((parm1 > GT) ? 195 : 187) - parm1);
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
        case EQ:       /* L24aa */
        case NEQ:      /* L24aa */
            return parm1;
        case LEQ:      /* L24ae */
        case LT:         /* L24ae */
        case ULEQ:           /* L24ae */
        case 97:           /* L24ae */
            return (parm1 + 2);
        default:           /* L24b5 */
            return (parm1 - 2);
    }
}

int
#ifdef COCO
L24e6 (cref)
    register expnode *cref;
#else
L24e6 (expnode *cref)
#endif
{
    return ((cref->op == CONST) && ( ! cref->val.num));

    /*if ((cref->op == CONST) && ( ! cref->val.num))
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
    expnode *cref;
#else
L2505 (expnode *cref)
#endif
{
    L2520 (cref);
    L28fb (cref);
}

void
#ifdef COCO
L2520 (cref)
    register expnode *cref;
#else
L2520 (expnode *cref)
#endif
{
    expnode *var4;
    int var2;
    int var0;

    switch (var2 = cref->op)
    {       /* break = L28f7 */
        case 128:          /* L28f7 */
        case XIND:          /* L28f7 */
        case YIND:          /* L28f7 */
        case UIND:          /* L28f7 */
        case NAME:     /* L28f7 */
            break;
        case STAR:   /* L2535 */
            L1953 (cref);
            L152d (cref);

            switch (cref->op)
            {
                case XIND:          /* L2547 */
                case YIND:          /* L2547 */
                case UIND:          /* L2547 */
                    if (cref->val.num)
                    {
#ifdef COCO
                        gen (LEAX, NODE, cref);
#else
                        gen (LEAX, NODE, cref, 0);
#endif
                        cref->op = XIND;
                        cref->val.num = 0;
                    }

                    /* fall through to break */
                default:           /* L28f7 */
                    break;
            }

            break;

        case UTOL:      /* L2577 */
            L0bc3 (cref->left);
            gen (LONGOP, UTOL NUL2);
            goto L25bf;
        case DTOL:    /* L2586 */
            L29fc (cref->left);
#ifdef COCO
            gen (DBLOP, DTOL, cref->left);
#else
            gen (DBLOP, DTOL, cref->left, 0);
#endif
            goto L25bf;
        case ITOL:      /* L25a5 */
            L0bc3 (cref->left);
            gen (LONGOP, ITOL NUL2);
L25bf:
            cref->op = 128;
            break;
        case LCONST:       /* L25c9 */
#ifdef COCO
            gen (LONGOP, LCONST, cref->val.num);
#else
            gen (LONGOP, LCONST, cref->val.num, 0);
#endif
            L3203 (cref->val.num, 4);
            goto L27d4;
        case QUERY:   /* L25ea */
            L12e8 (cref, L2505);
            goto L27d4;
        case INCBEF:   /* L25f7 */
        case DECBEF:
        case COMPL:
        case NEG:
            L2505 (cref->left);
#ifdef COCO
            gen (LONGOP, var2);
#else
            gen (LONGOP, var2, 0, 0);
#endif
            goto L27d4;
        case INCAFT:  /* L2613 */
        case DECAFT:
            gen (LOADIM, DREG, 128, 0);
#ifdef COCO
            gen (PUSH, DREG);
#else
            gen (PUSH, DREG, 0, 0);
#endif
            L2505 (cref->left);
#ifdef COCO
            gen (LONGOP, var2);
            gen (LONGOP, MOVE);
#else
            gen (LONGOP, var2, 0, 0);
            gen (LONGOP, MOVE, 0, 0);
#endif

            gen (LONGOP, ((var2 == INCAFT) ? DECAFT : INCAFT)
#ifndef COCO
                    , 0, 0
#endif
                  );
            goto L25bf;

        case CALL:     /* L2674 */
            L1364 (cref);
            goto L25bf;
        case TIMES:       /* L267e */
            if (((cref->left)->op) == LCONST)
            {
                expnode *_tmpref;

                _tmpref = cref->left;
                cref->left = cref->right;
                cref->right = _tmpref;
            }

            if (((cref->right)->op) == LCONST)       /* L2698 */
            {
                var4 = ((expnode *)(cref->right)->val.num);

                    /* L26f9 */
                if ( ! (var4->type) && (var0 = L121f (var4->size)))
                {
                    L3203 (var4, STRUCT);
                    var4 = cref->right;
                    var4->val.num = var0;
                    var4->op = CONST;
                    var4->type = INT;
                    var2 = (var2 == TIMES) ? SHL : SHR;
                    goto L2733;
                }
            }

            /* fall through to next case */
        case DIV:      /* L26f9 */
        case EQ:
        case NEQ:
        case GEQ:
        case LEQ:
        case GT:
        case LT:
        case PLUS:
        case MINUS:
        case MOD:
        case AND:
        case OR:
        case XOR:
            var4 = cref->left;

            if (var4->op == LCONST)
            {
                L294b (var4);
            }
            else
            {
                L2505 (var4);
#ifdef COCO
                gen (LONGOP, STACK);
#else
                gen (LONGOP, STACK, 0, 0);
#endif
            }

            L2505 (cref->right);
#ifdef COCO
            gen (LONGOP, var2);
#else
            gen (LONGOP, var2, 0, 0);
#endif
            goto L25bf;
        case SHL:     /* L2735 */
        case SHR:
L2733:
            L2505 (cref->left);
#ifdef COCO
            gen (PUSH, DREG);
#else
            gen (PUSH, DREG, 0, 0);
#endif
            L0bc3 ( cref->right);
#ifdef COCO
            gen (LONGOP, var2);
#else
            gen (LONGOP, var2, 0, 0);
#endif
            goto L25bf;
        case ASSIGN:      /* L2769 */
            L2505 (cref->left);
#ifdef COCO
            gen (PUSH, DREG);
#else
            gen (PUSH, DREG, 0, 0);
#endif
            L2505 (cref->right);
            goto L27c1;

            /* We'll put this here -- don't know at the moment why it was
             * put here, will investigate l8tr
             */
L278e:
            L2505 (var4 = cref->left);
#ifdef COCO
            gen (PUSH, DREG);
#else
            gen (PUSH, DREG, 0, 0);
#endif
            cref->op = var2 - 80;
            var4->op = XIND;
            L2520 (cref);
L27c1:
#ifdef COCO
            gen (LONGOP, MOVE);
#else
            gen (LONGOP, MOVE, 0, 0);
#endif
L27d4:
            cref->op = XIND;
            cref->val.num = 0;
            break;
        default:           /* L27e2 */
            if (var2 >= ASSPLUS)
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
    expnode *cref;
#else
L28fb (expnode *cref)
#endif
{
    switch (cref->op)
    {
        case NAME:      /* L2909 */
            gen (LOADIM, DREG, NODE, cref);
            break;
        case YIND:           /* L2923 */
        case UIND:
#ifdef COCO
            gen (LEAX, NODE, cref);
#else
            gen (LEAX, NODE, cref, 0);
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
    register expnode *cref;
#else
L294b (expnode *cref)
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

    _lng.l = cref->val.lp;

    if (*(_lng.l))
    {           /* elsee L29aa */
        gen (LOAD, DREG, CONST, _lng.i[1]);
#ifdef COCO
        gen (PUSH, DREG);
#else
        gen (PUSH, DREG, 0, 0);
#endif
        gen (LOAD, DREG, CONST, _lng.i[0]);    /* go to L29d1 */
    }
    else
    {
        gen (LOAD, DREG, CONST, 0);
#ifdef COCO
        gen (PUSH, DREG);
#else
        gen (PUSH, DREG, 0, 0);
#endif
    }

#ifdef COCO
    gen (PUSH, DREG);
#else
    gen (PUSH, DREG, 0, 0);
#endif
    L3203 (_lng.l, 4);
    cref->val.num = 0;
}
