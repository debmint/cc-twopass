/* ************************************************************** *
 * pass1_03.c                                                     *
 * ************************************************************** */

/* $Id: p1_03.c 18 2008-05-19 21:54:22Z dlb $ */

#include "pass1.h"

expnode *
#ifndef COCO
optim (register expnode *tree)
#else
optim (tree)
    register expnode *tree;
#endif
{
    /* 12 bytes stack */
    expnode *lhs, *rhs;
    int v6;
    int op;
    expnode *tptr;
    int v0;

    if (tree)    /* else L0fff */
    {
        tree->left = optim (tree->left);
        tree->right = optim (tree->right);
        tree = chtype (tree);

        if (isleaf (tree))
        {
      
            return tree;      /*goto L0ffd;*/
        }

        tree = fold (tree);        /* L0f56 */
        lhs = tree->left;
        rhs = tree->right;
        
        if (((op = tree->op) == QUERY) && (lhs->op == CONST)) /* else L0fb4 */
        {
            if (lhs->val.num)      /* else L0fd8 */
            {
                tptr = rhs->left;
                reltree (rhs->right);
            }
            else
            {
                tptr = rhs->right;       /* L0fd8 */
                reltree (rhs->left);
            }

            release (rhs);
            release (lhs);
            release (tree);
        }
        else
        {            /* L0fb4 */
            if ((op != STAR) || (lhs->op != AMPER))
            {
                if ((op != AMPER) || (lhs->op != STAR))
                {
                    /* not "**", "*&", "&*" or "&&" */
                    return tree;
                }
            }

            tptr = lhs->left;      /* L0fd8 */
            tptr->type = tree->type;
            tptr->size = tree->size;
            release (tree);
            release (lhs);
        }
        tree = tptr;      /* L0ff4 */
    }

L0ffd:
    return tree;
}

expnode *
#ifndef COCO
fold (register expnode *tree)
#else
fold (tree)
    register expnode *tree;
#endif
{
    expnode *lhs;
    expnode *rhs;
    expnode *ptr;
    int op;
    int v4;
    int op1;
    int opr;

    if (!tree)
    {
        return 0;
    }

    lhs = tree->left;      /* L101a */
    rhs = tree->right;
    
    if (isbin (op = tree->op) || (op == DBLAND) || (op == DBLOR))
    {                                       /* else L1258 */
        if ((op1 = (lhs->op == CONST)) & (opr = (rhs->op == CONST))) /* L1041 */
        {
            goto doop;
        }

        if (op1)     /* L1076 */     /* else L10b6 */
        {
            switch (op)
            {
                case PLUS: /* L107e */    /* _44 */
                case TIMES:  /* L107e */
                case AND:  /* L107e */
                case OR: /* L107e */
                case XOR: /* L107e */
                    ptr = lhs;
                    tree->left = lhs = rhs;
                    tree->right = rhs = ptr;
                    opr = 1;
                    break;
            }
        }

        switch (op)
        {
            case OR:    /* L10bb (_51) */
            case XOR:   /* L10bb */
                if ((opr) && !(rhs->val.num))
                {
                    goto justleft;
                }

                return tree;
            case PLUS:    /* L10cc (_60) */
                if (!opr)
                {
                    return tree;
                }

                if (!(rhs->val.num))
                {
                    goto justleft;
                }

                switch (lhs->op)
                {
                    case AMPER:   /* L10e1 */
                        (lhs->left)->modifier += rhs->val.num;
justleft:
                        ptr = lhs;
                        release (tree);
                        release (rhs);
                        tree = ptr;
                        return tree;
                    case PLUS:        /* L1112 */
                        if ((lhs->right)->op == CONST)
                        {
                            ((lhs->right)->val.num) += rhs->val.num;
                            goto justleft;
                        }

                        return tree;
                    default:            /* L131d */
                        return tree;
                }
            case MINUS:     /* L1142 ( _71 ) */
                if (opr)
                {
                    rhs->val.num = -(rhs->val.num);
                    tree->op = PLUS;
                    return (fold (tree));
                }

                if (op1)    /* L1161 */
                {
                    if (!lhs->val.num)
                    {
                        tree->op = NEG;
                        tree->left = rhs;
                        tree->right = 0;
                        release (lhs);
                    }
                }

                return tree;
            case AND:     /* L1181 */
                if ((opr) && !(rhs->val.num))
                {
                    goto makezero;
                    /*return 0;*/
                }
                else
                {
                    return tree;
                }

            case TIMES:     /* _97  (L1190) */
                if (!opr)
                {
                    return tree;
                }

                switch (rhs->val.num)
                {
                    case 0:         /* L119c ( _106 ) */
                        goto makezero;
                    default:        /* L11a1 */
                        if ((lhs->op != TIMES) ||
                                    ((lhs->right)->op != CONST))
                        {
                            return tree;
                        }

                        (lhs->right)->val.num *= rhs->val.num;
                        /* Fall through to next case */
                    case 1:         /* L11e9 ( _113 ) */
                        goto justleft;
                }
            case DIV:   /* L11db ( _104 ) */
                if (opr && (rhs->val.num == 1))
                {
                    goto justleft;
                }

                if (op1 && !(lhs->val.num))   /* L11ee */
                {
makezero:
                    tree->op = CONST;    /* _96 or _122 */
                    tree->val.num = 0;   /* L1207 (storing some value here) */
                    tree->left = tree->right = 0;
                    release (lhs);
                    release (rhs);
                }

                break;
        }           /* end switch (ope) */

        return tree;      /* L131d */
    }

    /* L1258 */
    switch (op)     /* L1308 ( _124 ) */
    {
        case NOT: /* L125d ( _125 ) */
        case COMPL: /* L125d */
        case NEG: /* L125d */
            if (lhs->op == CONST)     /* else L128d */
            {
doop:
                tree->op = CONST;
                tree->sux = 0;
#ifdef COCO
                tree->val.num = constop (op, lhs->val.num, rhs->val.num);
#else
                /* I believe making parm3 0 will work.  constop doesn't
                 * appear to use it for these three cases
                 */
                /* Didn't work... it  trying "if" now... */

                tree->val.num = constop (op, lhs->val.num,
                                      rhs ? rhs->val.num : 0);
#endif
                /* bra L1207 */
                tree->left = tree->right = 0;
                release (lhs);
                release (rhs);
                /*return tree;*/
                /*break;*/  /* Don't need if following else works */
            }
            else
            {
            /* L128d */
            if (lhs->op == LCONST)      /* else L12dc */
            {
                long *p;

                if (!(*p = lhs->val.num))    /* else L12ad */
                {
                    p = (long *)addmem (sizeof (long));
                }

                switch (op)
                {
                    case NEG:   /* L12b1 */
                        *p = -(*p);
                        break;
                    case COMPL:   /* L12bc */
                        *p = ~(*p);
                        break;
                }

                lhs->val.num = (int)p;   /* go to L12fc */
                /* The following would work after the outer block,
                 * but trying to match code
                 */
            release (tree);      /* L12fc */
            tree = lhs;
            }
            else
            {
                if (lhs->op == FCONST)        /* L12dc */
                {
                    double *dptr;

                    if (dptr = (double *)(lhs->val.num))     /* else L12fc */
                    {
                        *dptr = -(*dptr);
                    }
            release (tree);      /* L12fc */
            tree = lhs;
                }
            }
            }   /* Inserted else at L128d */

            /*return tree;*/
    }

    return tree;
}

int
#ifndef COCO
isleaf (register expnode *node)
#else
isleaf (node)
    register expnode *node;
#endif
{
    if (node)
    {
        switch (node->op)
        {
            case YREG:  /* L1335 */
            case UREG:  /* L1335 */
            case CONST: /* L1335 */
            case LCONST: /* L1335 */
            case FCONST: /* L1335 */
            case NAME:  /* L1335 */
            case STRING: /* L1335 */
                return 1;
        }
    }

    return 0;
}

void
divby_0 ()
{
    reprterr ("divide by zero");
}

expnode *
#ifndef COCO
chtype ( expnode *node)
#else
chtype (node)
    expnode *node;
#endif
{
    register expnode *lhs = node->left;
    expnode *rhs;
    
    union {
        symnode *sptr;
        expnode *eptr;
    } ep;
    
    int op;
    int t;
    int size;
    int xtype;
    dimnode *dptr;
    int t1;
    int tr;
    int mosar;

    rhs = node->right;
    xtype = size =  2;
    dptr = 0;
    t = INT;
    
    switch (op = node->op)
    {
        case NAME:         /* L13b6 */
            ep.sptr = node->val.sp;
            
            if (ep.sptr->storage == TYPEDEF)    /* else L13e6 */
            {
                terror (node, "typedef - not a variable");
                makedummy (node);
                break;
            }

            t = ep.sptr->type;      /* L13e6 */
            dptr = ep.sptr->dimptr;

            if ((t & 0x0f) == USTRUCT)     /* else L1427 */
            {
                symnode *p;

                p = (symnode *)ep.sptr->size;
                t = ep.sptr->type = (t & 0xfff0) + p->type;
                sizeup (ep.sptr, dptr, p->size);
            }

            size = ep.sptr->size;

            if ((isary (t)) || (isftn (t))) /*else L14a9*/
            {
                lhs = node;
                lhs->size = size;
                node = newnode (AMPER, lhs, 0, 0, node->lno, node->pnt);

                if (isary (t))       /* else L1494 */
                {
                    dptr = dimwalk (dptr);
                    t = incref (lhs->type = decref (t));
                }
                else
                {
                    t = incref (lhs->type = t);
                }

                lhs->sux = 1;
            }
            else
            {
                switch (t1 = ep.sptr->storage)      /* L14a9 */
                {
                    case YREG:
                    case UREG:       /* L14b4 */
                        node->op = t1;
                        node->val.num = 0;
                        break;
                }

            }

            xtype = 1;        /* L14d0 */
            break;
        case CONST:    /* L14d5 */
            xtype = 0;
            break;
        case LCONST:        /* _182 */      /* L14dc */
            t = LONG;
            xtype = 1;
            size = LONGSIZ;
            break;
        case FCONST:      /* L14ec */
            t = DOUBLE;
            xtype = 1;
            size = DBLSIZ;
            break;
        case STRING:       /* L14fc */
            t = POINTER | CHAR  ;
            size = CHARSIZ;
            break;
        case CAST:         /* L1507 */
            ck_declared (lhs);

            if ((isftn (t = node->type)) || (isary (t)))
            {
                terror (node, "cannot cast");
                t = incref (t);
            }

            if (isptr (t))
            {
                do_cast (lhs, INT);
            }
            else
            {
                t = do_cast (lhs, t);
            }

            dptr = node->dimptr;        /* L1568 */
            size = node->size;
            release (node);
            node = lhs;
            break;
        case AMPER:   /* L1586 */
            needlval (lhs, 1);
            
            if ((lhs->op == YREG) || (lhs->op == UREG))
            {
                terror (node, "can't take address");
                makedummy (lhs);
            }

            xtype = lhs->sux;
            size = lhs->size;
            t = incref (lhs->type);
            dptr = lhs->dimptr;
            break;
        case STAR:    /* L15d4 */
            dptr = lhs->dimptr;
            
            if (isptr (t = lhs->type)) /* else L1618 */
            {
                t = decref (t);

                if (isary (t))  /* else L163a */
                {
                    t = incref (decref (t));
                    release (node);
                    node = lhs;
                }
            }
            else
            {
                terror (lhs, "pointer required");
                makedummy (lhs);
                lhs->type = 17;
                t = INT;
                dptr = 0;
            }

            xtype = lhs->sux;     /* L163a */
            size = lhs->size;
            break;
        case DOT:      /* L1646 */
            size = needmos (rhs, &t, &mosar);
            dptr = rhs->dimptr;
            needlval (lhs, 1);

            if (!(rhs->val.num) && !(mosar))
            {
                release (rhs);
                release (node);
                node = lhs;
                xtype = node->sux;     /* go to L16fd */
            }
            else
            {
                xtype = lhs->sux;     /* L169a */

                if (lhs->op == STAR)   /* else L16bf */
                {
                    ep.eptr = lhs->left;
                    release (lhs);
                    node->left = (lhs = ep.eptr);
                }
                else
                {
                    t1 = lhs->type;        /* L16bf */
                    lhs = node->left =
                        newnode (AMPER, lhs, 0, 0,
                                    lhs->lno, lhs->pnt);
                    lhs->type = incref (t1);
                }

                lhs->sux = xtype;
                goto strcommon;
            }

            break;
        case ARROW:      /* L1700 */
            size = needmos (rhs, &t, &mosar);
            dptr = rhs->dimptr;
            
            if (((t1 = lhs->type) != INT))   /* else L1754 */
            {
                if (!isptr (t1))   /* Trying to match code */
                {
                    terror (lhs, "pointer or integer required");
                    lhs->op = CONST;
                    lhs->val.num = 0;
                    lhs->sux = 0;
                }
            }

            xtype = lhs->sux;
strcommon:
            node->op = PLUS;
            node = fold (node);

            if (!mosar)        /* else L17bb */
            {
                node->type = incref (t);
                node->sux = xtype;
                node->size = size; 
                node = newnode (STAR, node, 0, 0, node->lno, node->pnt);
            }

            break;
        case CALL:         /* L17be */
            t = lhs->type;

            if ((lhs->op == AMPER) &&
                    (isftn (decref (t))))
            {       /* else L17fa */
                ep.eptr = node->left = lhs->left;
                release (lhs);
                t = decref (ep.eptr->type);
                /* go to L185e */
            }
            else
            {
                if (isftn (t))
                {
                    t = decref (t);      /* go to L185e */
                }
                else
                {
                    if (!t)       /* else L184c */
                    {
                        ep.sptr = lhs->val.sp;
                        ep.sptr->type = INT | FUNCTION;
                        ep.sptr->size = 2;
                        ep.sptr->dimptr = 0;
                        ep.sptr->storage = EXTERN;
                        ep.sptr->blklev = 0;
                        mem_cp (ep.sptr, lhs, 6);
                        t = INT;
                    }
                    else
                    {
                        terror (lhs, "not a function");
                        t &= 0x0f;
                    }
                }
            }

            dptr = lhs->dimptr;        /* L185e */
            size = lhs->size;       /* Fall through to next case */
        case ARG:         /* L1868 */
            ck_declared (lhs);
            get_ftty (lhs);

            switch (lhs->type)
            {
                case CHAR:     /* L187a */
                     do_cast (lhs, INT);
                     break;
                case FLOAT:     /* L187f */
                     do_cast (lhs, DOUBLE);
                     break;
            }

            break;
        case C_COMMA:       /* L189a */
            size = rhs->size;
            t = rhs->type;
            dptr = rhs->dimptr;
            break;
        case NOT:      /* L18b0 */
            if (!(isptr (lhs->type)))
            {
                cktypnumeric (lhs);
            }

            t = INT;
            break;
        case NEG:       /* L18c8 */
            t = cktypnumeric (lhs);
            break;
        case COMPL:       /* L18d2 */
            if ((t = cktypnumeric (lhs)) == DOUBLE)    /* else L18c3 */
            {
                notintegral (lhs);
                makedummy (lhs);
            }

            break;
        case INCBEF:    /* _269  (L18ef) */
        case INCAFT:         /* _269 */
        case DECBEF:    /* _269 */
        case DECAFT:         /* _269 */
            needlval (lhs, 0);
            size = lhs->size;
            
            if ((t = lhs->type) & 0x30)      /* else L1920 */
            {
                node->val.num = getsize (decref (t),
                                         lhs->size, lhs->dimptr);
            }
            else
            {
                node->val.num = 1;       /* L1920 */
            }

            xtype = lhs->sux;

            if (lhs->op == STAR)   /* else L1aa7 */
            {
                ++xtype;
            }

            break;
        case DBLAND:      /* _278  (L193f) */
        case DBLOR:        /* _278 */
            if (!isptr (lhs->type))
            {
                cktypnumeric (lhs);
            }

            if (!(isptr (rhs->type))) /* L1951 */ /* else cktypnumeric */
            {
                cktypnumeric (rhs);
            }

            break;
        case DIV:       /* L1e01 */
        case TIMES:         /* L1e01 */
            t = tymatch (lhs, rhs);
            break;
        case AND:         /* _292  (L1969) */
        case OR:        /* _292 */
        case XOR:       /* _292 */
        case C_PERCENT:     /* _292 */
            if ((t = tymatch (lhs, rhs)) == DOUBLE)
            {
                goto L19a6;
            }

            break;
        case SHL:      /* L1985 */
        case SHR:      /* L1985 */
            if (((t = cktypnumeric (lhs)) == DOUBLE) ||
                    (cktypnumeric (rhs) == DOUBLE))        /* else L19c6 */
            {
L19a6:
                terror (node, "both must be integral");
                makedummy (node);
                break;
            }

            do_cast (rhs, INT);
            break;
        case LT:          /* L19d6 */
        case GT:
        case LEQ:
        case GEQ:
            if (((isptr (lhs->type)) &&
                        (isptr (rhs->type))) ||
                        (tymatch (lhs, rhs) == UNSIGN))
            {
                node->op = op + 4;   /* L19ff */
            }
                

            break;
        case EQ:        /* L1a0c */
        case NEQ:       /* L1a0c */
            if (isptr (lhs->type))    /* else L1a45 */
            {
                /*if (!isptr (rhs->type))*/      /* else L1a51 */
                if (!((isptr (rhs->type)) ? 1 : 0))   /* code match ? */
                {
                    cktypnumeric (rhs);        /* L1a2a + 1 line */
                    do_cast (rhs, INT);     /* go to L1a4f */
                }
            }
            else
            {
                tymatch (lhs, rhs);    /* L1a45 */
            }
            
            break;      /* L1a51 */
        case PLUS:        /* L1a54 */
            if (isptr (rhs->type))     /* else L1a73 */
            {
                {
                    expnode *__tmp = lhs;

                    lhs = rhs;
                    rhs = __tmp;
                }

                node->left = lhs;
            }

            size = lhs->size;        /* L1a73 */
            t = lhs->type;

            if (isptr (t))
            {
                dptr = lhs->dimptr;
                goto L1b8d;
            }

            t = tymatch (lhs, rhs);         /* L1a8e */
            /*xtype = lhs->sux + rhs->sux;*/
            xtype = lhs->sux + rhs->sux;
            break;
        case MINUS:         /* L1aaa */
            xtype = lhs->sux + rhs->sux;
            
            if (isptr ((t = lhs->type)))       /* else L1e01 */
            {
                size = lhs->size;
                dptr = lhs->dimptr;

                if (isptr (rhs->type))    /* else L1b90 */
                {
                    node->sux = xtype;

                    if ((t != rhs->type) || (size != rhs->size))
                    {
                        terror (node, "pointer mismatch");
                        /* go to L1b7e */
                    }
                    else
                    {
                        t = decref (t);
                        
                        if ((size = getsize (t, size, dptr)) != 1) /* else L1b7e */
                        {
                            xtype = 2;
                            ep.eptr = newnode (CONST, 0, 0, size, 0, 0);
                            node = newnode (DIV, node, ep.eptr, 0,
                                                node->lno, node->pnt);
                        }
                    }

                    size = 2;
                    dptr = 0;
                    t = INT;
                    break;
                }
L1b8d:
                cktypnumeric (rhs);

                if (!iswordorlong (rhs->type))        /* else L1bba */
                {
                    notintegral (rhs);
                    makedummy (rhs);
                }

                do_cast (rhs, INT);
                node->right = fixup (size, t, dptr, rhs);
                xtype = lhs->sux + rhs->sux;
            }
            else
            {
                t = tymatch (lhs, rhs);     /* copy of L1e01 */
                /*goto L1d66;*/
            }
            
            break;
        case ASSIGN:       /* L1bf4 */
            needlval (lhs, 0);
            ck_declared (rhs);
            tr = get_ftty (rhs);
            
            if (((isptr ((t = lhs->type)))) &&
                    !(isptr (tr)) &&
                    !(iswordorlong (tr)))           /* else L1cba */
            {           /* Loop different - they go through L1cba we go
                         * straight to L1d66 */
                goto L1d66;
            }

            if (!(isptr (tr)) || (isptr (t)) ||  /* L1c3a */
                        (iswordorlong (t)))      /* else L1cba */
            {
                do_cast (rhs, t);      /* L1c5d */
                goto L1d4f;
            }
            else
            {
                goto L1d66;
            }

L1c71:
            needlval(lhs, 0);
            cktypnumeric (rhs);
            tr = get_ftty (rhs);
            
            if (isptr ((t = lhs->type)))
            {
                switch (op)
                {
                    case ASSMIN:       /* L1ca6 */
                    case ASSPLUS:       /* L1ca6 */
                        do_cast (rhs, INT);
                        goto L1cf0;
                    default:     /* L1cba */
                        goto L1d66;
                }
            }

            switch (op)
            {
                default:     /* L1cd3 */
                    if (t == FLOAT)
                    {
                        do_cast (rhs, DOUBLE);
                    }
                    else
                    {
                        do_cast (rhs, t);
                    }
                case ASSSHL:    /* L1cf3 */
                case ASSSHR:    /* L1cf3 */
L1cf0:
                    node->op = op - 80;
                    node = chtype (node);

                    if (t == CHAR)    /* else L1d2a */
                    {
                        node->left = lhs->left;
                        release (lhs);
                        lhs = node->left;
                        t = INT;
                    }

                    if ((op - 80) == node->op)   /* else L1d52 */
                    {
                        node->op = op;
                    }
            }

L1d4f:
            size = lhs->size;
            xtype = lhs->sux + rhs->sux;
            dptr = lhs->dimptr;
            break;
            
            /*goto L1d66;*/     /* L1cba */
L1d66:
            terror (node, "type mismatch");  /* go to L1e44 */
            break;
        case C_COLON:       /* L1d7a */
            if (isptr ((t = lhs->type)))    /* else L1dd9 */
            {
                size = lhs->size;
                xtype = lhs->sux;
                dptr = lhs->size;

                if (isptr (rhs->type))       /* else L1dcc */
                {
                    if ((t != rhs->type) ||
                            (lhs->size != rhs->size))
                    {
                        terror (node, "pointer mismatch");
                        /*break;*/
                    }
                    else
                    {
                        dptr = 0;
                    }

                    break;
                }
                
                cknull (rhs);
                break;
            }

            if (isptr ((t = rhs->type))) /*L1dd9  else L1e01 */
            {
                size = rhs->size;
                xtype = rhs->sux;
                dptr = rhs->dimptr;
                cknull (lhs);
                break;
            }

            t = tymatch (lhs, rhs);     /* L1e01 */
            break;
        case QUERY:    /* L1e12 */
            t = rhs->type;
            size = rhs->size;
            dptr = rhs->dimptr;
            break;
        default:            /* L1e28 */
            if (op >= ASSPLUS)
            {
                goto L1c71;
            }

            comperr ( node, "type check");
            break;
    }

    node->type = t;       /* L1f7b */
    node->size = size;
    node->sux = xtype;
    node->dimptr = dptr;
    return node;
}

/* *********************************************************** *
 * cknull () - Checks that 2nd & 3rd expressions of a           *
 *      "? ... :" term are of same type.                       *
 * *********************************************************** */

void
#ifndef COCO
cknull (register expnode *regptr)
#else
cknull (regptr)
register expnode *regptr;
#endif
{
    if ((regptr->op != CONST) || (regptr->val.num))
    {
        terror (regptr, "should be NULL");
        regptr->op = CONST;        /* Store correct value */
        regptr->val.num = 0;
    }
}

/* ******************************************************** *
 * cktypnumeric () - Checks that the type is some numeric   *
 *      type.  Promotes "char" to "int" and "float" to      *
 *      double.                                             *
 * Returns: ft_Ty (modified if applicable)                  *
 * ******************************************************** */

int
#ifndef COCO
cktypnumeric (register expnode *c_ref)
#else
cktypnumeric (c_ref)
    register expnode *c_ref;
#endif
{
    int _ttype;

    ck_declared (c_ref);
    
    switch (_ttype = c_ref->type)
    {
        case CHAR:      /* L1fd7 */
            _ttype = INT;
            do_cast (c_ref, _ttype);
            break;
        case FLOAT:      /* L1fdc */
            _ttype = DOUBLE;
            do_cast (c_ref, _ttype);
            break;
        case DOUBLE:      /* L201f */
        case LONG:
        case INT:
        case UNSIGN:
            break;
        default:     /* L1feb */
            terror (c_ref, "type error");
            _ttype = INT;
            break;
    }

    return (c_ref->type = _ttype);
}

/* ******************************************************** *
 * do_cast () - Performs casts                              *
 * Passed: (1) CMDREF * to variable to be cast              *
 *         (2) to_type - the type to convert to             *
 * ******************************************************** */

int
#ifndef COCO
do_cast (register expnode *node, int t)
#else
do_cast (node, t)
    register expnode *node;
    int t;
#endif
{
    /* 4 bytes stack */
    union {
        long    *lp;
        double  *dp;
        expnode *ep;
    } _valnode;
    int op;

    op = 0;

    switch (node->type)
    {
        case CHAR:      /* L203c */
            switch (t)
            {
                case INT:      /* _434 (L2040) */
                case UNSIGN:
                    op = C_CHR2INT;           /* 0x85 */
                    break;      /* L2303 = break */
                case LONG:      /* L2045 */
                    do_cast (node, INT);
                    op = CTOI;
                    break;
                case DOUBLE:      /* _437  (L2058) */
                case FLOAT:
                    do_cast (node, INT);    /* First convert to int */
                    do_cast (node, t);
                    break;
                default:     /* L2303 */
                    break;
            }

            break;
        default:
            if (!(isptr (node->type)))
            {
                break;
            }
            /* else fall through to case INT */
        case INT:      /* _442 (L209f) */
            switch (t)
            {
                case LONG:      /* L20a4 */
                    if ((node->op == CONST))     /* else L20df */
                    {
                        /* NOTE:  We need to change this..  _valnode.lp is a long
                         * here, so offsets are offsets into the long.
                         */

                        _valnode.lp = addmem (LONGSIZE);
                        
                        /* sign extend into MSB */

                        if ((_valnode.lp[1] = node->val.num) < 0)
                        {
                            _valnode.lp[0] = -1;
                        }
                        else
                        {
                            _valnode.lp[0] = 0;
                        }

                        node->val.lp = _valnode.lp;
L20d0:
                        node->op = LCONST;
                        node->size = LONGSIZE;
                    }
                    else
                    {
                        op = CTOI;
                    }

                    break;
                case CHAR:      /* L20e4 */
                    t = INT;
                    break;
                case FLOAT:      /* L20ec */
                    do_cast (node, DOUBLE);
                    op = DTOF;
                    break;
                case DOUBLE:      /* L20fd */
                    if (node->op == CONST)      /* else L212f */
                    {
                        _valnode.dp = addmem (DOUBLESIZE);

                        /* The following does not actually do a
                         * _valnode.dp = (double)src thing, but
                         * rather simply stores abs (theint) at offset 5
                         * into the value, and at offset 0, 0 if positive
                         * or $80 if negative
                         */
                        *_valnode.dp = node->val.num;

L211f:
                        node->val.dp = _valnode.dp;
                        node->op = FCONST;
                        node->size = DBLSIZ;
                        break;
                    }

                    op = ITOD;
                    break;
            }

            break;
        case UNSIGN:      /* L2152 */
            switch (t)
            {
                case LONG:      /* L2156 */
                    op = UTOL;
                    break;
                case FLOAT:      /* L215b */
                    do_cast (node, DOUBLE);
                    op = DTOF;
                    break;
                case DOUBLE:      /* L216c */
                    op = UTOD;
                    break;
                case CHAR:      /* L2174 */
                    t = INT;
                    break;
            }

            break;
        case LONG:      /* L2193 */
            switch (t)
            {

                default:     /* L2198 */
                    if (!isptr (t))
                    {
                        break;
                    }
                    /* Fall through to next case */
                case INT:      /* _477 (L21a5) */
                case UNSIGN:      /* L21a5 */
                case CHAR:      /* L21a5 */
                    if (node->op == LCONST)
                    {
                        /* Discard MSB of long */
                        _valnode.lp = node->val.lp;
/*#ifdef COCO*/
                        /*node->val.num = ((CMDREF *)_valnode)->size;*/
                        node->val.num = _valnode.lp[1];
/*#else
                        node->val.num = *((long *)_valnode) & 0xffff;
#endif*/
L21b9:
                        node->op = CONST;
                        node->size = INTSIZ;
                    }
                    else
                    {
                        op = LTOI;
                    }
                    
                    break;
                case FLOAT:      /* L21cd */
                    do_cast (node, DOUBLE);
                    op = DTOF;
                    break;
                case DOUBLE:      /* L21de */
                    if (node->op == LCONST)
                    {
                        _valnode.dp = addmem (DOUBLESIZE);
/*#ifdef COCO
#asm
                        ldx 2,s
                        pshs x
                        ldx 8,u
                        lbsr L6a3c
                        lbsr _dmove
#endasm
#else*/
                        *_valnode.lp = *node->val.lp;
/*#endif*/
                        goto L211f;
                    }

                    op = LTOD;       /* L2203 */
                    break;
            }

            break;
        case FLOAT:      /* L222d */
            switch (t)
            {
                case LONG:      /* _496 (L2231) */
                case UNSIGN:
                case CHAR:
                case INT:
                    do_cast (node, DOUBLE);
                    do_cast (node, t);
                    break;
                case DOUBLE:      /* L224b */
                    op = FTOD;
                    break;
            }

            break;
        case DOUBLE:      /* L2275 */
            switch (t)
            {
                case CHAR:      /* _504 (L2279) */
                case UNSIGN:      /* L2279 */
                case INT:      /* L2279 */
                    if (node->op == FCONST)        /* else L228d */
                    {
                        node->val.num = *(double *)(node->val.sp);
/*#ifdef COCO
#asm
                        ldx 8,u
                        lbsr L697c
                        std 8,u
#endasm*/
/*#else*/
                        /* Gotta figure out what L697c does */
/*#endif*/
                        goto L21b9;
                    }
                    else
                    {
                        op = DTOI;
                    }

                    break;
                case LONG:      /* L2292 */
                    if (node->op == FCONST)        /* else L22ab */
                    {
                        *node->val.lp = *node->val.dp;
/*#ifdef COCO
#asm
                        ldx 8,u
                        pshs x
                        ldx 8,u
                        lbsr L6981
                        lbsr _lmove
#endasm
#else
#endif*/
                        goto L20d0;
                    }
                    else
                    {
                        op = DTOL;
                    }

                    break;
                    
                case FLOAT:      /* L22b0 */
                    op = DTOF;

                    break;
            }
    }

    /* _429 (L2303) */
    if (op)     /* else L233b */
    {
        nodecopy (node, (_valnode.ep = newnode (0, 0, 0, 0, 0, 0)));
        node->op = op;
        node->left = _valnode.ep;
        node->right = 0;
    }

    return (node->type = t);
}

int
#ifndef COCO
tymatch (register expnode *lhs, expnode *rhs)
#else
tymatch (lhs, rhs)
    register expnode *lhs;
    expnode *rhs;
#endif
{
    int tl;
    int tr;

    tl = cktypnumeric (lhs);
    tr = cktypnumeric (rhs);

    if (tl == DOUBLE)
    {
        return (do_cast (rhs, DOUBLE));
    }
    else
    {
        if (tr == DOUBLE)
        {
            return (do_cast (lhs, DOUBLE));
        }
        else
        {
            if (tl == LONG)
            {
                return (do_cast (rhs, LONG));
            }
            else
            {
                if (tr == LONG)
                {
                    return (do_cast (lhs, LONG));
                }
                else
                {
                    if ((tl == UNSIGN) || (tr == UNSIGN))
                    {
                        return (lhs->type = rhs->type = UNSIGN);
                    }
                    else
                    {
                        return INT;
                    }
                }
            }
        }
    }
}

expnode *
#ifndef COCO
fixup (int size, int t, expnode *dptr, expnode *rhs)
#else
fixup (size, t, dptr, rhs)
    int size, t;
    expnode *dptr, *rhs;
#endif
{
    register expnode *regptr;

    if ((size = getsize (decref (t), size, dptr)) == 1)
    {
        return rhs;
    }

    /* L23ee */
    regptr = newnode (CONST, 0, 0, size, rhs->lno, rhs->pnt);
    regptr->type = INT;
    regptr = fold (newnode (TIMES, rhs, regptr, 0, rhs->lno, rhs->pnt));
    regptr->sux = (regptr->op == CONST) ? 0 : 2;
    regptr->type = INT;     /* L2452 */
    regptr->size = 2;

    return regptr;
}

void
#ifndef COCO
needlval (register expnode *node, int flag)
#else
needlval (node, flag)
    register expnode *node;
    int flag;
#endif
{
    int op;

    switch (op = node->op)
    {
        case YREG:         /* L25b1 */
        case UREG:         /* L25b1 */
        case STAR:    /* L25b1 */
            return;
    }

    if (op == NAME)       /* else L24bc ("lvalue required") */
    {
        ck_declared (node);

        if (flag || (!(isary (node->type)) && (node->type != STRUCT)))
        {
            return;
        }
    }

    terror (node, "lvalue required");        /* L24bc */
    makedummy (node);

}

void
#ifndef COCO
ck_declared (register expnode *regptr)
#else
ck_declared (regptr)
    register expnode *regptr;
#endif
{
    if ((regptr->op == NAME) && !(regptr->type))    /* else L25b3 */
    {
        terror (regptr, "undeclared variable");
        makedummy (regptr);
    }
}

int
#ifndef COCO
needmos (register expnode *node, int *t, int *mosar)
#else
needmos (node, t, mosar)
    register expnode *node;
    int *t;
    int *mosar;
#endif
{
    union {
        expnode *eptr;
        symnode *sptr;
    } ep;

    *t = node->type;

    if ((node->op) == AMPER)       /* else L2541 */
    {
        *mosar = 1;
        ep.eptr = node->left;
        ep.eptr->dimptr = node->dimptr;
        nodecopy (ep.eptr, node);
        release (ep.eptr);
    }
    else
    {
        *mosar = 0;
    }

    ck_declared (node);

    if (node->op == NAME)       /* else L2586 */
    {
        ep.sptr = node->val.sp;

        if (ep.sptr->storage != MOS)   /* else L2567 */
        {
            goto L2584;
        }

        node->op = CONST;
        node->val.num = ep.sptr->offset;
        node->sux = 0;
        node->type = INT;
        return ep.sptr->size;
    }

L2584:
    terror (node, "struct member required");
    makedummy (node);
    node->op = CONST;
    node->val.num = 0;
    node->sux = 0;
    *t = INT;
    return 2;
}

int
#ifndef COCO
get_ftty (register expnode *regptr)
#else
get_ftty (regptr)
    register expnode *regptr;
#endif
{
    if ((regptr->type == STRUCT) || (regptr->type == UNION))
    {
        terror (regptr, "structure or union inappropriate");
        makedummy (regptr);
    }

    return regptr->type;
}

/* **************************************************** *
 * makedummy ()                                             *
 *                                                      *
 * **************************************************** */

void
#ifndef COCO
makedummy (register expnode *p1)
#else
makedummy (p1)
    register expnode *p1;
#endif
{
    mem_cp (&sdummy, p1, 6);
    p1->sux = 1;
    reltree (p1->left);
    reltree (p1->right);
    p1->left = p1->right = 0;
    p1->op = NAME;    /* generic alpha??? */
    p1->val.sp = &sdummy;
}

/* ******************************************************** *
 * iswordorlong() - checks that a command is a word value   *
 * Returns: TRUE if it's an int, char, long, or unsigned    *
 *          FALSE on anything else                          *
 * ******************************************************** */

int
#ifndef COCO
iswordorlong (int tstval)
#else
iswordorlong (tstval)
int tstval;
#endif
{
    switch (tstval)
    {
        case INT:
        case CHAR:
        case LONG:
        case UNSIGN:
            return 1;
    }

    return 0;
}

void
#ifndef COCO
notintegral (expnode *c_ref)
#else
notintegral (c_ref)
    expnode *c_ref;
#endif
{
    terror (c_ref, "must be integral");
}
