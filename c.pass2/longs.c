#include "pass2.h"

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
