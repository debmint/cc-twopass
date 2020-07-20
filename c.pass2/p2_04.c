/* ************************************************************************ *
 * p2_04.c - part 4 for c.pass2                                             *
 *                                                                          *
 * $Id: p2_04.c 18 2008-05-19 21:54:22Z dlb $::                                                                   *
 * ************************************************************************ */

#include "pass2.h"

void
#ifdef COCO
L29fc (cref)
    expnode *cref;
#else
L29fc (expnode *cref)
#endif
{
    L2a17 (cref);
    L28fb (cref);
}

void
#ifdef COCO
L2a17 (cref)
    register expnode *cref;
#else
L2a17 (expnode *cref)
#endif
{
    int var6;
    expnode *var4;
    int var2;
    int var0;

    var2 = cref->type;
    switch (var6 = cref->op)
    {
        case FREG:          /* L2d34 */
        case XIND:          /* L2d34 */
        case YIND:          /* L2d34 */
        case UIND:          /* L2d34 */
        case NAME:     /* L2d34 */
            break;
        case STAR:   /* L2a30 */
            L2520 (cref);
            break;
        case UTOD:      /* L2a3a */
        case ITOD:      /* L2a3a */
            lddexp (cref->left);
L2a45:
#ifdef COCO
            gen (DBLOP, var6);
#else
            gen (DBLOP, var6,0 ,0);
#endif
L2a57:
            cref->op = FREG;
            break;
        case LTOD:      /* L2a61 */
            L2505 (cref->left);
            goto L2a45;
        case DTOF:    /* L2a6a */
        case FTOD:    /* L2a6a */
            L29fc (cref->left);
            goto L2a45;
        case FCONST:     /* L2a77 */
#ifdef COCO
            gen (DBLOP, FCONST, cref->val.num);
#else
            gen (DBLOP, FCONST, cref->val.num, 0);
#endif
            cref->op = XIND;
            L3203 (cref->val.num, DBLSIZ);
            cref->val.num = 0;
            break;
        case QUERY:   /* L2aa0 */
            doquery (cref, L29fc);
            goto L2c34;
        case INCBEF:   /* L2aaf */
        case DECBEF:
        case NEG:
            L29fc (cref->left);
#ifdef COCO
            gen (DBLOP, var6, var2);
#else
            gen (DBLOP, var6, var2, 0);
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
            L29fc (cref->left);
#ifdef COCO
            gen (DBLOP, var6, var2);
            gen (DBLOP, MOVE, var2);
            gen (DBLOP, (var6 == INCAFT ? DECAFT : INCAFT),
                    var2);
#else
            gen (DBLOP, var6, var2, 0);
            gen (DBLOP, MOVE, var2, 0);
            gen (DBLOP, (var6 == INCAFT ? DECAFT : INCAFT),
                     var2, 0);
#endif
             goto L2a57;
        case CALL:     /* L2b42 */
            docall (cref);
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
            L29fc (cref->left);
#ifdef COCO
            gen (DBLOP, STACK);
#else
            gen (DBLOP, STACK, 0, 0);
#endif
            L29fc (cref->right);
#ifdef COCO
            gen (DBLOP, var6);
#else
            gen (DBLOP, var6, 0, 0);
#endif
            goto L2a57;
        case ASSIGN:      /* L2b7f */
            L29fc (cref->left);
#ifdef COCO
            gen (PUSH, XREG);
#else
            gen (PUSH, XREG, 0, 0);
#endif
            L29fc (cref->right);
            goto L2c1d;

L2ba5:
            var4 = cref->left;
             
            if (var2 == FLOAT)  /* else L2bd7 */
            {
                L29fc (var4->left);
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
                L29fc (var4);
#ifdef COCO
                gen (PUSH, XREG);
#else
                gen (PUSH, XREG, 0, 0);
#endif
            }

            cref->op = var6 - 80;
            var4->op = XIND;
            L2a17 (cref);

            if (var2 == FLOAT)
            {
#ifdef COCO
                gen (DBLOP, DTOF);
#else
                gen (DBLOP, DTOF, 0, 0);
#endif
            }
L2c1d:
#ifdef COCO
            gen (DBLOP, MOVE, var2);
#else
            gen (DBLOP, MOVE, var2, 0);
#endif
L2c34:
            cref->op = XIND;
            cref->val.num = 0;
            break;

        default:           /* L2c42 */
            if (var6 >= ASSPLUS)
            {
                goto L2ba5;
            }

            comperr (cref, "floats");
    }
}

