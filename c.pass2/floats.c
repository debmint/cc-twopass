/* ************************************************************************ *
 * p2_04.c - part 4 for c.pass2                                             *
 *                                                                          *
 * $Id: p2_04.c 18 2008-05-19 21:54:22Z dlb $::                                                                   *
 * ************************************************************************ */

#include "pass2.h"

void
#ifdef COCO
dload (cref)
    expnode *cref;
#else
dload (expnode *cref)
#endif
{
    trandexp (cref);
    getadd (cref);
}

void
#ifdef COCO
trandexp (node)
    register expnode *node;
#else
trandexp (expnode *node)
#endif
{
    int op;
    expnode *var4;
    int type;
    int var0;

    type = node->type;
    switch (op = node->op)
    {
        case FREG:          /* L2d34 */
        case XIND:          /* L2d34 */
        case YIND:          /* L2d34 */
        case UIND:          /* L2d34 */
        case NAME:     /* L2d34 */
            break;
        case STAR:   /* L2a30 */
            tranlexp (node);
            break;
        case UTOD:      /* L2a3a */
        case ITOD:      /* L2a3a */
            lddexp (node->left);
L2a45:
#ifdef COCO
            gen (DBLOP, op);
#else
            gen (DBLOP, op,0 ,0);
#endif
L2a57:
            node->op = FREG;
            break;
        case LTOD:      /* L2a61 */
            lload (node->left);
            goto L2a45;
        case DTOF:    /* L2a6a */
        case FTOD:    /* L2a6a */
            dload (node->left);
            goto L2a45;
        case FCONST:     /* L2a77 */
#ifdef COCO
            gen (DBLOP, FCONST, node->val.num);
#else
            gen (DBLOP, FCONST, node->val.num, 0);
#endif
            node->op = XIND;
            L3203 (node->val.num, DBLSIZ);
            node->val.num = 0;
            break;
        case QUERY:   /* L2aa0 */
            doquery (node, dload);
            goto L2c34;
        case INCBEF:   /* L2aaf */
        case DECBEF:
        case NEG:
            dload (node->left);
#ifdef COCO
            gen (DBLOP, op, type);
#else
            gen (DBLOP, op, type, 0);
#endif
            goto L2c34;
        case INCAFT:  /* L2acf */
        case DECAFT:  /* L2acf */
#ifdef COCO
            gen (LOADIM, XREG, FREG);
            gen (PUSH, XREG);
#else
            gen (LOADIM, XREG, FREG, 0);
            gen (PUSH, XREG, 0, 0);
#endif
            dload (node->left);
#ifdef COCO
            gen (DBLOP, op, type);
            gen (DBLOP, MOVE, type);
            gen (DBLOP, (op == INCAFT ? DECAFT : INCAFT),
                    type);
#else
            gen (DBLOP, op, type, 0);
            gen (DBLOP, MOVE, type, 0);
            gen (DBLOP, (op == INCAFT ? DECAFT : INCAFT), type, 0);
#endif
             goto L2a57;
        case CALL:     /* L2b42 */
            docall (node);
            goto L2a57;
        case EQ:
        case NEQ:
        case GEQ:
        case LEQ:
        case GT:         /* L2b4b */
        case LT:
        case PLUS:
        case MINUS:
        case TIMES:
        case DIV:
            dload (node->left);
#ifdef COCO
            gen (DBLOP, STACK);
#else
            gen (DBLOP, STACK, 0, 0);
#endif
            dload (node->right);
#ifdef COCO
            gen (DBLOP, op);
#else
            gen (DBLOP, op, 0, 0);
#endif
            goto L2a57;
        case ASSIGN:      /* L2b7f */
            dload (node->left);
#ifdef COCO
            gen (PUSH, XREG);
#else
            gen (PUSH, XREG, 0, 0);
#endif
            dload (node->right);
            goto L2c1d;

L2ba5:
            var4 = node->left;
             
            if (type == FLOAT)  /* else L2bd7 */
            {
                dload (var4->left);
#ifdef COCO
                gen (PUSH, XREG);
                gen (DBLOP, FTOD);
#else
                gen (PUSH, XREG, 0, 0);
                gen (DBLOP, FTOD, 0, 0);
#endif
            }
            else
            {
                dload (var4);
#ifdef COCO
                gen (PUSH, XREG);
#else
                gen (PUSH, XREG, 0, 0);
#endif
            }

            node->op = op - 80;
            var4->op = XIND;
            trandexp (node);

            if (type == FLOAT)
            {
#ifdef COCO
                gen (DBLOP, DTOF);
#else
                gen (DBLOP, DTOF, 0, 0);
#endif
            }
L2c1d:
#ifdef COCO
            gen (DBLOP, MOVE, type);
#else
            gen (DBLOP, MOVE, type, 0);
#endif
L2c34:
            node->op = XIND;
            node->val.num = 0;
            break;

        default:           /* L2c42 */
            if (op >= ASSPLUS)
            {
                goto L2ba5;
            }

            comperr (node, "floats");
    }
}

