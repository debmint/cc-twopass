/* ************************************************************************ *
 * p2_04.c - part 4 for c.pass2                                             *
 *                                                                          *
 * $Id: p2_04.c 18 2008-05-19 21:54:22Z dlb $::                                                                   *
 * ************************************************************************ */

#include "pass2.h"

void
#ifdef COCO
L29fc (cref)
    CMDREF *cref;
#else
L29fc (CMDREF *cref)
#endif
{
    L2a17 (cref);
    L28fb (cref);
}

void
#ifdef COCO
L2a17 (cref)
    register CMDREF *cref;
#else
L2a17 (CMDREF *cref)
#endif
{
    int var6;
    CMDREF *var4;
    int var2;
    int var0;

    var2 = cref->ft_Ty;
    switch (var6 = cref->vartyp)
    {
        case 128:          /* L2d34 */
        case 147:          /* L2d34 */
        case 148:          /* L2d34 */
        case 149:          /* L2d34 */
        case C_USRLBL:     /* L2d34 */
            break;
        case C_ASTERISK:   /* L2a30 */
            L2520 (cref);
            break;
        case C_U2DBL:      /* L2a3a */
        case C_I2DBL:      /* L2a3a */
            L0bc3 (cref->cr_Left);
L2a45:
#ifdef COCO
            L3292 (135, var6);
#else
            L3292 (135, var6,0 ,0);
#endif
L2a57:
            cref->vartyp = 128;
            break;
        case C_L2DBL:      /* L2a61 */
            L2505 (cref->cr_Left);
            goto L2a45;
        case C_TOFLOAT:    /* L2a6a */
        case C_FLT2DBL:    /* L2a6a */
            L29fc (cref->cr_Left);
            goto L2a45;
        case C_DOUBLE:     /* L2a77 */
#ifdef COCO
            L3292 (135, C_DOUBLE, cref->cmdval);
#else
            L3292 (135, C_DOUBLE, cref->cmdval, 0);
#endif
            cref->vartyp = 147;
            L3203 (cref->cmdval, DBLSIZ);
            cref->cmdval = 0;
            break;
        case C_QUESTION:   /* L2aa0 */
            L12e8 (cref, L29fc);
            goto L2c34;
        case C_PLUSPLUS:   /* L2aaf */
        case C_MINMINUS:
        case C_MINUS:
            L29fc (cref->cr_Left);
#ifdef COCO
            L3292 (135, var6, var2);
#else
            L3292 (135, var6, var2, 0);
#endif
            goto L2c34;
        case C_INCREMENT:  /* L2acf */
        case C_DECREMENT:  /* L2acf */
#ifdef COCO
            L3292 (127, 113, 128);
            L3292 (122, 113);
#else
            L3292 (127, 113, 128, 0);
            L3292 (122, 113, 0, 0);
#endif
            L29fc (cref->cr_Left);
#ifdef COCO
            L3292 (135, var6, var2);
            L3292 (135, 137, var2);
            L3292 (135, (var6 == C_INCREMENT ? C_DECREMENT : C_INCREMENT),
                    var2);
#else
            L3292 (135, var6, var2, 0);
            L3292 (135, 137, var2, 0);
            L3292 (135, (var6 == C_INCREMENT ? C_DECREMENT : C_INCREMENT),
                     var2, 0);
#endif
             goto L2a57;
        case C_PARENS:     /* L2b42 */
            L1364 (cref);
            goto L2a57;
        case C_EQEQ:
        case C_NOTEQ:
        case C_GT_EQ:
        case C_LT_EQ:
        case C_GT:         /* L2b4b */
        case C_LT:
        case C_PLUS:
        case C_NEG:
        case C_MULT:
        case C_SLASH:
            L29fc (cref->cr_Left);
#ifdef COCO
            L3292 (135, 110);
#else
            L3292 (135, 110, 0, 0);
#endif
            L29fc (cref->cr_Right);
#ifdef COCO
            L3292 (135, var6);
#else
            L3292 (135, var6, 0, 0);
#endif
            goto L2a57;
        case C_EQUAL:      /* L2b7f */
            L29fc (cref->cr_Left);
#ifdef COCO
            L3292 (122, 113);
#else
            L3292 (122, 113, 0, 0);
#endif
            L29fc (cref->cr_Right);
            goto L2c1d;

L2ba5:
            var4 = cref->cr_Left;
             
            if (var2 == FT_FLOAT)  /* else L2bd7 */
            {
                L29fc (var4->cr_Left);
#ifdef COCO
                L3292 (122, 113);
                L3292 (135, C_FLT2DBL);
#else
                L3292 (122, 113, 0, 0);
                L3292 (135, C_FLT2DBL, 0, 0);
#endif
            }
            else
            {
                L29fc (var4);
#ifdef COCO
                L3292 (122, 113);
#else
                L3292 (122, 113, 0, 0);
#endif
            }

            cref->vartyp = var6 - 80;
            var4->vartyp = 147;
            L2a17 (cref);

            if (var2 == FT_FLOAT)
            {
#ifdef COCO
                L3292 (135, C_TOFLOAT);
#else
                L3292 (135, C_TOFLOAT, 0, 0);
#endif
            }
L2c1d:
#ifdef COCO
            L3292 (135, 137, var2);
#else
            L3292 (135, 137, var2, 0);
#endif
L2c34:
            cref->vartyp = 147;
            cref->cmdval = 0;
            break;

        default:           /* L2c42 */
            if (var6 >= C_PLUSEQ)
            {
                goto L2ba5;
            }

            L484b (cref, "floats");
    }
}

