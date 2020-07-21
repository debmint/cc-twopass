/* ************************************************************************ *
 * p2_03.c - part 3 for c.pass2                                             *
 *                                                                          *
 * $Id: p2_03.c 18 2008-05-19 21:54:22Z dlb $                               *
 * ************************************************************************ */

#include "pass2.h"

void
#ifdef COCO
tranbool (node, tlab, flab, n)
    register expnode *node;
    int tlab, flab, n;
#else
tranbool (expnode *node, int tlab, int flab, int n)
#endif
{
    int op;
    int second;

    switch (op =  node->op)
    {           /* break = L20e9 */
        case DBLAND:     /* L1f28 */
            tranbool (node->left, (second = ++D000b), flab, 1);
            goto L1f66;
        case DBLOR:       /* L1f48 */
            tranbool (node->left, tlab, (second = ++D000b), 0);
L1f66:
            label (second);
            tranbool (node->right, tlab, flab, n);
            break;                      /* go to L20e9 */
        case NOT:     /* L1f72 */
            tranbool (node->left, flab, tlab, (1 - n));
            break;
        case EQ:
        case NEQ:
        case LEQ:
        case LT:
        case GEQ:      /* L1f87 */
        case GT:
        case ULEQ:
        case ULT:
        case UGEQ:
        case UGT:
            L20ed (op, node, tlab, flab, n);
            break;
        case CONST:
        case FCONST:     /* L1fa1 */
        case LCONST:
            if (node->val.num && !n)
            {
#ifdef COCO
                gen (JMP, tlab, 0);
#else
                gen (JMP, tlab, 0, 0);
#endif
            }
            else
            {
                if (n && ( ! node->val.num))
                {
#ifdef COCO
                    gen (JMP, flab, 0);
#else
                    gen (JMP, flab, 0, 0);
#endif
                }
            }
            break;
        case COMMA:      /* L1fcb */
            tranexp (node->left);
            tranbool (node->right, tlab, flab, n);
            break;
        default:           /* L1fec */
            if (node->type == LONG)
            {
                lload (node);
#ifdef COCO
                gen (LONGOP, TEST);
#else
                gen (LONGOP, TEST, 0, 0);
#endif
                /* go to L204d */
            }
            else
            {
                if ((node->type == FLOAT) || (node->type == DOUBLE))
                {               /* else L2042 */
                    if (node->op == FTOD)
                    {
                        node = node->left;
                    }

                    dload (node);           /* L2026 */
#ifdef COCO
                    gen (DBLOP, TEST, node->type);
#else
                    gen (DBLOP, TEST, node->type, 0);
#endif
                }
                else
                {
                    checkop (node);
                }
            }
#ifdef COCO
L204d:
#endif
            if (n)
            {
#ifdef COCO
                gen (CNDJMP, EQ, flab);
#else
                gen (CNDJMP, EQ, flab, 0);
#endif
            }
            else
            {
#ifdef COCO
                gen (CNDJMP, NEQ, tlab);
#else
                gen (CNDJMP, NEQ, tlab, 0);
#endif
            }

            break;
    }
}

void
#ifdef COCO
L20ed (op, node, tlab, flab, nj)
    int op;
    expnode *node;
    int tlab, flab, nj;
#else
L20ed (int op, expnode *node, int tlab, int flab, int nj)
        /* +10            +12        +14        +16        +18  */
#endif
{
    expnode *t;
    int destin;
    expnode *lhs = node->left;

    register expnode *rhs = node->right;

    destin = (nj ? flab : tlab);

    op = (nj ? invrel (op) : op);

    if (lhs->type == LONG)
    {
        tranlexp (node);       /* go to L214b */
        goto L22b2;
    }
    else
    {           /* L2134 */
        if ((lhs->type == FLOAT) || (lhs->type == DOUBLE))
        {
            trandexp (node);
            goto L22b2;

        }
    }

    /* Check out the logic for this block ... it's pretty complicated */
    /* L2152 */
    if ((zeroconst ( lhs)) ||
            ((isaleaf (lhs)) && ( ! isaleaf (rhs))) ||
            ((is_regvar (rhs->op)) &&
                        ( ! is_regvar (lhs->op))))  /* else L219c */
    {
        t = lhs;        /* L2189 */
        lhs = rhs;
        rhs = t;
        op = revrel (op);
    }

    t = lhs->op;        /* L219c */

    if (is_regvar (t))       /* else L221f */
    {
        tranexp (rhs);

        switch (rhs->op)
        {
            case AMPER:           /* L21b8 */
                loadexp (rhs);
                goto L21e0;
            case CTOI:    /* L21c3 */
                gen (LOAD, DREG, NODE, rhs);
                rhs->op = DREG;
                /* fall through to next case */
            case XREG:
            case YREG:
            case UREG:
            case DREG:      /* L21e2 */
L21e0:
#ifdef COCO
                gen (PUSH, rhs->op);
#else
                gen (PUSH, rhs->op, 0, 0);
#endif
                 rhs->op = STACK;    /* go to L229b */
            default:           /* L229b */
                 break;
        }
    }       /* end if (is_regvar...) */
    else
    {
        if ((zeroconst (rhs)) && (op < ULEQ))       /* L221f */
        {
            checkop (lhs);       /* go to L22b4 */
            /* this should probably have been goto L22b2; */
#ifdef COCO
            gen (CNDJMP, op, destin);
#else
            gen (CNDJMP, op, destin, 0);
#endif
            return;
        }
        else
        {
            loadexp (lhs);       /* L223c */
            t = lhs->op;
            
            if ((isdleaf (rhs)) || ((t == DREG) && isaleaf (rhs)))
            {
                tranexp (rhs);   /* go to L229b */
            }
            else
            {
#ifdef COCO
                gen (PUSH, t);
#else
                gen (PUSH, t, 0, 0);
#endif
                lhs->op = STACK;
                loadexp (rhs);
                t = rhs->op;
                rhs = lhs;
                op = revrel (op);
            }
        }
    }       /* end else => if ! is_regvar... */

    gen (COMPARE, t, NODE, rhs); /* L229b... */
L22b2:
#ifdef COCO
    gen (CNDJMP, op, destin);
#else
    gen (CNDJMP, op, destin, 0);
#endif
}

int
#ifdef COCO
isaleaf (cref)
    expnode *cref;
#else
isaleaf (expnode *cref)
#endif
{
    switch (cref->op)
    {
        case NAME:      /* L22d8 */
        case CONST:
            return 1;
        case STAR:    /* L22dd */
            return isxleaf (cref);
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
checkop (node)
    register expnode *node;
#else
checkop (expnode *node)
#endif
{
    expnode *lhs;
    int flag = 0;

    switch (node->op)
    {                                       /* break = L23fe */
        case AND:        /* L2337 */
            if ((((lhs = node->right)->op) != CONST) ||
                        ((unsigned int)(lhs->val.num) > (unsigned int)255))
            {
                    flag = 1;
            }

            break;

        case ASSIGN:      /* L2353 */
            if ((is_regvar ((node->left)->op)) &&
                                ( ! isaleaf (node->right)))
            {
                flag = 1;
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
            if ( ! is_regvar ((node->left)->op))
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
            flag = 1;
            break;
    }

    shiftflag = 0;
    tranexp (node);

    switch (node->op)
    {
        case XREG:
        case DREG:          /* L240d */
        case YREG:
        case UREG:
            if (flag || shiftflag)
            {
                gen (COMPARE, node->op, CONST, 0);
            }

            break;

        case CTOI:    /* L2427 */
            gen (LOAD, DREG, NODE, (node = node->left));
            break;
        default:           /* L2429 */
            gen (LOAD, DREG, NODE, node);
            break;
    }
}

int
#ifdef COCO
invrel (parm1)
    int parm1;
#else
invrel (int parm1)
#endif
{
    switch (parm1)
    {
        case EQ:        /* L2472 */
            return NEQ;
        case NEQ:       /* L2477 */
            return EQ;
        default:            /* L247c */
            return (((parm1 > GT) ? ULEQ+UGT : LEQ+GT) - parm1);
    }
}

int
#ifdef COCO
revrel (parm1)
    int parm1;
#else
revrel (int parm1)
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
        case ULT:           /* L24ae */
            return (parm1 + 2);
        default:           /* L24b5 */
            return (parm1 - 2);
    }
}

int
#ifdef COCO
zeroconst (cref)
    register expnode *cref;
#else
zeroconst (expnode *cref)
#endif
{
    return ((cref->op == CONST) && ( ! cref->val.num));
}

void
#ifdef COCO
lload (cref)
    expnode *cref;
#else
lload (expnode *cref)
#endif
{
    tranlexp (cref);
    getadd (cref);
}

void
#ifdef COCO
tranlexp (cref)
    register expnode *cref;
#else
tranlexp (expnode *cref)
#endif
{
    expnode *var4;
    int var2;
    int var0;

    switch (var2 = cref->op)
    {       /* break = L28f7 */
        case FREG:          /* L28f7 */
        case XIND:          /* L28f7 */
        case YIND:          /* L28f7 */
        case UIND:          /* L28f7 */
        case NAME:     /* L28f7 */
            break;
        case STAR:   /* L2535 */
            dostar (cref);
            getinx (cref);

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
            lddexp (cref->left);
            gen (LONGOP, UTOL NUL2);
            goto L25bf;
        case DTOL:    /* L2586 */
            dload (cref->left);
#ifdef COCO
            gen (DBLOP, DTOL, cref->left);
#else
            gen (DBLOP, DTOL, cref->left, 0);
#endif
            goto L25bf;
        case ITOL:      /* L25a5 */
            lddexp (cref->left);
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
            doquery (cref, lload);
            goto L27d4;
        case INCBEF:   /* L25f7 */
        case DECBEF:
        case COMPL:
        case NEG:
            lload (cref->left);
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
            lload (cref->left);
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
            docall (cref);
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
                if ( ! (var4->type) && (var0 = isashift (var4->size)))
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
                lload (var4);
#ifdef COCO
                gen (LONGOP, STACK);
#else
                gen (LONGOP, STACK, 0, 0);
#endif
            }

            lload (cref->right);
#ifdef COCO
            gen (LONGOP, var2);
#else
            gen (LONGOP, var2, 0, 0);
#endif
            goto L25bf;
        case SHL:     /* L2735 */
        case SHR:
L2733:
            lload (cref->left);
#ifdef COCO
            gen (PUSH, DREG);
#else
            gen (PUSH, DREG, 0, 0);
#endif
            lddexp ( cref->right);
#ifdef COCO
            gen (LONGOP, var2);
#else
            gen (LONGOP, var2, 0, 0);
#endif
            goto L25bf;
        case ASSIGN:      /* L2769 */
            lload (cref->left);
#ifdef COCO
            gen (PUSH, DREG);
#else
            gen (PUSH, DREG, 0, 0);
#endif
            lload (cref->right);
            goto L27c1;

            /* We'll put this here -- don't know at the moment why it was
             * put here, will investigate l8tr
             */
L278e:
            lload (var4 = cref->left);
#ifdef COCO
            gen (PUSH, DREG);
#else
            gen (PUSH, DREG, 0, 0);
#endif
            cref->op = var2 - 80;
            var4->op = XIND;
            tranlexp (cref);
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

            comperr (cref, "longs");
            break;
    }
}

void
#ifdef COCO
getadd (cref)
    expnode *cref;
#else
getadd (expnode *cref)
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
