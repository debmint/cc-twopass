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

