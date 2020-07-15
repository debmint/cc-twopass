/* *********************************************************** *
 * pass1_02.c                                                  *
 * *********************************************************** */

/* $Id: p1_02.c 18 2008-05-19 21:54:22Z dlb $ */

/* This file is an exact match with the original code
 * ( with non-critical variations
 */

#include "pass1.h"

#ifdef COCO
static int elsize ();
#else
static int elsize (expnode **prim);
#endif

/* ******************************************************** *
 * parsexp ()                                                 *
 * Passed : 
 * ******************************************************** */

expnode *
#ifndef COCO
parsexp (int priority)
#else
parsexp (priority)
    int priority;
#endif
{
    /* 14 bytes of stack */
    expnode *lhs;
    int op;    /* vartype ??? */
    int priop;
    expnode *temp;
    int lno;
    char *errpnt;
    int rprec;

    register expnode *rhs;
    
    if (!(lhs = L0694 ()))  /* else return 0 */
    {
        return 0;
    }

    while ((isop ()) && (priority <= symval))    /* L0679 */
    {
        op = sym;        /* L059b */
        rprec = priop = symval;    /* fix a = b = c ?????? */
        lno = symline;
        errpnt = symptr;
        nxt_word();

        switch (op)
        {
            case C_QUESTION:    /* _10 (L05d9) */
            case C_EQUAL:
                break;
            default:            /* _14 (L05b4) */
                /* Not <something>= (+=, -=, %=, etc) */

                if ((op < 160) || (op > 169))
                {
                    rprec = priop + 1;
                }

                break;
        }

        /* recurse into self */

        if ((rhs = parsexp (rprec)))      /* _10 (L05d9) else L066e */
        {
            if (op == C_QUESTION)       /* else L064d */
            {
                if (need (C_COLON))     /* else L0642 */
                {
                    reltree (rhs);     /* L0642 */
                    goto L068c;     /* Wouldn't "break" work? */
                }
                else
                {
                    errpnt = symptr;
                    lno = symline;
                    
                    if ((temp = parsexp (3)))       /* else L0637 */
                    {
                        rhs = newnode (C_COLON, rhs, temp,
                                                3, lno, errpnt);
                        /* go to L064d */
                    }
                    else
                    {
                        reprterr ("third expression missing");  /* L0637 */

                        /* Same procedure as above if need (C_COLON)
                         * is true
                         */

                        reltree (rhs);
                        goto L068c;
                    }
                }
            }

            /* L064d */
            lhs = newnode (op, lhs, rhs, priop, lno, errpnt);
        }
        else
        {
            reprterr ("operand expected");  /* L066e */
        }
    }       /* end while() */

L068c:
    return lhs;
}

expnode *
L0694 ()
{
    /* 12 bytes of stack */
    expnode *prim;
    int op;
    int lno;
    char *errpnt;
    int v2;
    expnode *temp;

    register expnode *nodep = 0;

    switch (sym)      /* L07fc */
    {
        case C_DQUOT:
        case NAME:
        case LCONST:
        case FCONST:
        case CONST:    /* L06a6 */
            nodep = newnode (sym, 0, 0, symval, symline, symptr);
            nxt_word ();
            break;

        case LPAREN:     /* L06cb */  /* '-' */
            nxt_word ();

            if (istype ())
            {
                nodep = getcast ();
                need (RPAREN);

                /* Recurse into self */

                if (!(nodep->left = L0694()))       /* else break */
                {
                    release (nodep);
                    nodep = 0;
                }

                break;
            }

            if (!(nodep = parsexp (0)))  /* L06f9 */     /* else L072f */
            {
L070a:
                exprmsng ();
                nodep = newnode (CONST, 0, 0, 0, symline, symptr);
            }

            need (RPAREN);

            break;

        case NOT:      /* L073a */
        case NEG:
        case COMPL:
        case STAR:
        case DECBEF:
        case INCBEF:
        case AMPER:
            op = sym;
            lno = symline;
            errpnt = symptr;
            nxt_word ();

            if (prim = L0694 ()) /* self */     /* else L0775 */
            {
                nodep = newnode (op, prim, 0, 14, lno, errpnt);
            }
            else {
                reprterr ("primary expected");
            }

            break;

                /* 59 = sizeof??? */
        case SIZEOF:     /* L0781 */
            lno = symline;
            errpnt = symptr;
            nxt_word ();

            if (sym == LPAREN)        /* else L07c3 */
            {
                nxt_word ();

                if (istype ())          /* else L07a5 */
                {
                    prim = getcast ();    /* go to L07b7 */
                }
                else
                {
                    if (!(prim = parsexp (0)))
                    {
                        goto L070a;
                    }
                }

                need (RPAREN);     /* L07b7 */
            }
            else
            {
                prim = L0694 ();     /* L07c3 */
            }

            temp = prim;           /* L07c8 */
            nodep = newnode (CONST, 0, 0, elsize (&temp), lno, errpnt);
            reltree (temp);

            break;
    }

    if (nodep == 0)        /* _37 */
    {
        return 0;
    }

    for (;;)
    {
        switch (sym)      /* L098f */
        {
            case LPAREN:     /* L086e */  /* '-' */
                errpnt = symptr;
                lno = symline;
                nxt_word ();
                nodep = newnode (101, nodep, explist (), 15, lno, errpnt);
                need (RPAREN);

                continue;

            case C_LBRACE:     /* L089f */  /* '+' */
                nxt_word ();
                
                if (!(prim = parsexp (2)))     /* else L08d3 */
                {
                    exprmsng ();
                    prim = newnode (CONST, 0, 0, 0, symline, symptr);
                }

                nodep = newnode (PLUS, nodep, prim, 12, symline, symptr);
                nodep = newnode (STAR , nodep, 0, 15, symline, symptr);
                need (C_RBRACE);

                continue;

            case C_PERIOD:     /* L091f */
            case C_PTRREF:     /* L091f */
                op = sym;
                lno = symline;
                errpnt = symptr;
                
                ++Struct_Union;
                nxt_word ();
                --Struct_Union;

                /* if not label... ?? */

                if (sym != NAME)
                {
                    noidentf ();           /* go to L09ab */
                    break;
                }
                else
                {
                    prim = newnode (sym, 0, 0, symval, symline, symptr);
                    nodep = newnode (op, nodep, prim, 15, lno, errpnt);
                    nxt_word ();
                    continue;
                }

        }

        break;
    }

    /* L09ab */
    switch (sym)
    {
        case INCBEF:   /* L09af */ /* 0x3c */
            sym = C_INCREMENT;
            goto L09bf;
        case DECBEF:   /* L09b8 */ /* 0x3d */
            sym = C_DECREMENT;
L09bf:
            nodep = newnode (sym, nodep,0, 14, symline, symptr);
            nxt_word ();

            break;
    }

    return nodep;
}

expnode *
explist ()
{
    expnode *ptr;

    register expnode *list = 0;

    for (;;)
    {
        if (sym == RPAREN)      /* else L0a4b */
        {
            break;
        }

        if (ptr = parsexp (2))   /* else L0a3e */
        {
            ptr = newnode (ARG, ptr, list, 0, ptr->lno, ptr->pnt);
            list = ptr;
        }

        if (sym != C_COMMA)
        {
            break;
        }

        nxt_word ();
    }

    return list;
}

int
#ifndef COCO
constexp (int p)
#else
constexp (p)
int p;
#endif
{
    register expnode *ptr;
    int v;

    if ((ptr = optim (parsexp (p))) && (ptr->op == CONST))
    {
        v = ptr->val.num;
    }
    else
    {
        v = 0;
        reprterr ("constant required");
    }

    if ( ptr)
    {
        reltree (ptr);
    }

    return v;
}

int
isop ()
{
    switch (sym)
    {
        case AMPER:  /* L0aa7 */
            sym = C_AND;
            symval = 8;
            return 1;
        case STAR:   /* L0ab1 */
            sym = TIMES;
            symval = 13;
            return 1;
        case NEG:      /* L0abb */
            sym = MINUS;
            symval = 12;
            /*return 1;*//* Fall through to next case */
        case C_COMMA:      /* L0ac5 */
        case C_EQUAL:
        case C_QUESTION:
            return 1;
        case C_COLON:      /* retrn0 */
            return 0;
        default:           /* L0aca */
            return ((sym >= DBLAND) && (sym <= GT)) ||
                    (sym >= ASSPLUS) && (sym <= ASSXOR);
    }
}

int
#ifndef COCO
constop (int op, int r, int l)
#else
constop (op, r, l)
    int op;
    int r;
    int l;
#endif
{
    switch (op)
    {
        case PLUS:
            return (r + l);
        case MINUS:
            return (r - l);
        case TIMES:
            return (r * l);
        case DIV:
            if (l == 0)
            {
                divby_0 ();
                return 0;
            }

            return (r / l);
        case MOD:
            if (l)
            {
                return (r % l);
            }
            
            divby_0 ();
            return 0;

        case C_AND:        /* do_and */
            return (r & l);
        case C_VBAR:       /* do_or */
            return (r | l);
        case C_CARET:      /* do_eor */
            return (r ^ l);
        case C_LSHIFT:     /* ashft_l */
            return (r << l);
        case C_RSHIFT:     /* ashft_r */
            return (r >> l);
        case C_EQEQ:       /* tst_eq */
            return (r == l);
        case C_NOTEQ:      /* tst_neq */
            return (r != l);
        case C_GT:         /* tst_gt */
            return ((r > l) ? 1 : 0);
        case C_LT:         /* tst_lt */
            return ((r < l) ? 1 : 0);
        case C_GT_EQ:      /* tst_le */
            return ((r >= l) ? 1 : 0);
        case C_LT_EQ:      /* L0be2 */
            return ((r <= l) ? 1 : 0);
        case NEG:      /* negate */
            return (-r);
        case NOT:     /* is_zero */
            return (!r);
        case COMPL:      /* do_com */
            return (~r);
        case DBLAND:     /* both_nul */
            return (r && l);
        case DBLOR:       /* neit_nul */
            return (r || l);

            /* The following deal with unsigned equality/inequality */

        case ULEQ:        /* L0c2d */
        case ULT:        /* L0c2d */
        case UGEQ:        /* L0c2d */
        case UGT:        /* L0c2d */
            {
                unsigned int lp;
                unsigned int rp;

                lp = l;
                rp = r;

                switch (op)
                {
                    case ULEQ:           /* L0c3b */
                        return (rp <= lp);
                    case ULT:           /* L0c47 */
                        return (rp < lp);
                    case UGEQ:           /* L0c53 */
                        return (rp >= lp);
                    default:           /* L0c5f */
                        return (rp > lp);
                }
            }

        default:
            reprterr ("constant operator");
            return 0;
    }
}

expnode *
getcast ()
{
    int size;
    expnode *dptr;
    int type;
    expnode *ptr;
    int lno;
    char *errpt;
    int dummy;

    lno = symline;
    errpt = symptr;
    type = declarator (&ptr, &dptr,
                    (type = settype (&size, &dptr, &dummy)));
    clear (&arglist);

    if (ptr)
    {
         reprterr ("name in a cast");
    }

    ptr = newnode (CAST, 0, 0, 0, lno, errpt);
    ptr->type = type;
    sizeup (ptr, dptr, size);

    return ptr;
}

/* ************************************************************** *
 * newnode () - Checks to see if freenode points to a CMDREF      *
 *      if so, points freenode to the previous cmdref                *
 *      Otherwise, creates a new CMDREF and initializes it        *
 * Returns: Either freenode or the new CMDREF                        *
 * ************************************************************** */

expnode *
#ifndef COCO
newnode ( int op,       /* Applicable C_type */
             expnode *left,
             expnode *right,
             int value,         /* This refers to the value, or LBLDEF */
             int lno,
             char *errpnt
           )
#else
newnode (op, left, right, value, lno, errpnt)
    int op;
    expnode *left, *right;
    int value, lno;
    char *errpnt;
#endif
{
    register expnode *node;

    if (freenode)
    {
        node = freenode;
        freenode = node->left;
    }
    else
    {
        node = addmem (NODESIZE);
    }

    node->op = op;
    node->left = left;
    node->right = right;
    node->val.num = value;
    node->lno = lno;
    node->pnt = errpnt;
    node->modifier = 0;

    return node;
}

void
exprmsng ()
{
    reprterr ("expression missing");
}

static int
#ifndef COCO
elsize (expnode **prim)
#else
elsize (prim)
    expnode **prim;
#endif
{
    register expnode *p = *prim;

    switch (p->op)
    {
        default:     /* L0e38 */
            p = *prim = optim (p);
            goto L0e58;
        case NAME:     /* L0e48 */  /* '4' */
            p->type = p->val.sp->type;
            ck_declared (p);
            p = (expnode *)p->val.sp;
        case 32:     /* L0e5a */  /* ' ' */

L0e58:
            return (getsize (p->type, p->size, p->dimptr));
            break;
        case C_PERIOD:
        case C_PTRREF:     /* L0e6d */  /* 'E' */

            /* This is not correct for a CMDREF.  The bump is 12
             * p must be some other type struct
             */

            return elsize (&p->right);
            break;
    }
}
