/* ******************************************************** *
 * pass1_06.c                                               *
 * ******************************************************** */

/* $Id: p1_06.c 18 2008-05-19 21:54:22Z dlb $ */

/* This file is an exact match with original */

#ifdef COCO
static int ilist (int type, register symnode *ptr, symnode *list, int level);
#else
#   ifndef direct
#       define direct
#   endif
static int ilist ();
#endif

direct int datstring,
           datflag;

#include "pass1.h"

/* ************************************************************ *
 * initialize () - Outputs a label name when there is an assignment  *
 * Passed : (1) - LBLDEF * lblstruct (for the label)            *
 *          (2) - FT_type for label                             *
 *          (3) -                                               *
 * ************************************************************ */

void
#ifndef COCO
initialize (register symnode *ptr, int tsc, int type)
#else
initialize (ptr, tsc, type)
    register symnode *ptr;
    int tsc;
    int type;
#endif
{
    /* p was char *.  Trying to fix error on "&=" */
    union {
        char *cp;
        dimnode *dp;
    } p;  /* Also char * */
    int   count;

    switch (tsc)
    {
        case TYPEDEF:     /* _4 */   /* L4442 */
        case EXTERN:
        case EXTERND:
            cant_init ();
            return;
        case DIRECT:     /* _7 */    /* L4448 */
        case STATICD:
            wdataflag (1);
            break;
        default:     /* any valid non-dp data ? */  /* _9 */   /* L444d */
            wdataflag (0);
            break;
    }

    /* Write label name to output stream */

    if (!blklev)     /* L4479 */ /* else L44ab */
    {
        p.cp = ptr->sname;

        if ((tsc != STATIC) && (tsc != STATICD))
        {
            prtlbl (p.cp, 1);     /* Global label */
        }
        else            /* Static variables */
        {
            ptr->storage = EXTDEF;      /* _16 */
            prtlbl (p.cp, 0);
        }
    }
    else
    {
        /* Write ASM code for static label */
        prntstar ();
        wrtunderscore (ptr->offset);
        prntCR ();
    }

    if (type == (CHAR | ARRAY))   /* _19 */    /* L44ba */     /* else l450e */
    {
        datstring = 1;
        nxt_word ();

        if (sym == STRING)        /* else L4507 */
        {
            p.dp = ptr->dimptr;

            if (p.dp->dim == 0)        /* else L44e2 */
            {
                p.dp->dim = stringlen;
            }
            else
            {
                if ((count = p.dp->dim - stringlen) >= 0)     /* L44e2 */
                {
                    prnt_rzb (count);
                }
                else
                {
                    reprterr ("too long");
                }
            }

            nxt_word ();        /* L44ff */
            goto L4563;
        }

        datstring = 2;      /* L4507 */
    }
    else        /* Not DPEXTERN */
    {
        datstring = 2;      /* _21 */   /* L450e */
        nxt_word ();
    }

    if (type == STRUCT)    /* else L4533 */
    {
        ilist (type, ptr, ptr->x.elems, 0); /* L4524 */  /* go to L4565 */
    }
    else
    {
        if (isary (type))      /* L4533 */
        {
            ilist ( type, ptr, ptr->dimptr, 0);
        }
        else
        {
            if (!(ilist (type, ptr, ptr->dimptr, 1)))
            {
                find_sep ();    /* Look for comma or ";" */
            }
        }
    }

L4563:
    putc_e ();
    datstring = 0;
}

static int
#ifndef COCO
ilist (int type, register symnode *ptr, dimnode *list, int level)
#else
ilist (type, ptr, list, level)
    int type;
    register symnode *ptr;
    dimnode *list;
    int level;
#endif
{
    int flag, t, i;
    dimnode *newlist;
    unsigned int n;
    elem *e;

    if (!level)
    {
        need (LBRACE);
    }
    else
    {
        if (sym == LBRACE)
        {
            flag = 1;
            nxt_word ();
        }
        else
        {
            flag = 0;
        }
    }

    if (isary (type))  /* L45a3 */     /* else L4691 */
    {
        if (!(n = list->dim))
        {
            n = -1;
        }

        if ((t = decref (type)) == STRUCT)     /* LSTRUCT5bd */
        {
            newlist = (dimnode *)ptr->x.elems;
        }
        else
        {
            newlist = list->dptr;     /* L45d3 */
        }

        i = 0;

        /* Process until a right bracket is found */

        while (sym != RBRACE)     /* L4616 */
        {
            if (ilist (t, ptr, newlist, (level + 1))) /*L45e0*/ /*else L4748*/
            {
                if ((++i >= n) || (sym != COMMA))
                {
                    break;
                }

                nxt_word ();
                continue;   /* useless, but trying to match their code */
            }
            else
            {
                return 0;
            }
        }

        if (n == -1)
        {
            list->dim = i;
            /* go to L465c */
        }
        else
        {
            if (i < n)        /* L462d */
            {
                zero (getsize (t, ptr->size, list->dptr) * (n - i));
            }
        }

L465a:
        if ((level) && (!flag))
        {
            return 1;
        }

        if (sym == COMMA)
        {
            nxt_word ();
        }

        if (sym == RBRACE)
        {
            nxt_word ();
            return 1;
        }

        reprterr ("too many elements");
        find_sep ();
        return 1;
    }

    /* L4691 */
    if (type == STRUCT)        /* else L471c */
    {
        if (!(e = list)) /* else L46ea */
        {
            reprterr ("unions not allowed");
            find_sep ();
            return 0;
        }

        while (sym != RBRACE)
        {
            ptr = e->element;    /* L46aa */
            list = (ptr->type == STRUCT) ? (dimnode *)ptr->x.elems
                : ptr->dimptr;

            if (!ilist (ptr->type, ptr, list , level + 1))
            {
                return 0;
            }

            if ((e = e->strnext) && (sym == COMMA))       /* else L4713 */
            {
                nxt_word ();
                continue;   /* not needed */
            }
            else
            {
                break;
            }
        }

        while (e)      /* L4713 */
        {
            ptr = e->element;
            zero (getsize (ptr->type, ptr->size, (ptr->dimptr)));
            e = e->strnext;
        }

        goto L465a;
    }

    if (defobject (type))     /* L471c */     /* else L473a */
    {
        if (flag)        /* else L4735 */
        {
            need (RBRACE);
        }

        return 1;
    }
    else
    {
        reprterr ("constant expression required");
        find_sep ();
        return 0;
    }
}

void
#ifndef COCO
zero (int p1)
#else
zero (p1)
    int p1;
#endif
{
    prntstar ();
    prtspstr ("rzb ");
    prntdgt (p1);
    prntCR();
}

int
#ifndef COCO
defobject (int type)
#else
defobject (type)
    int type;
#endif
{
    /* 8 bytes stack */
    expnode *p2;
    int addon, done, t;
    register expnode *p;

    /*
     * NEED TO FIND OUT WHAT regpt IS
     */

    if (!(p = optim (parsexp (2))))   /* else return 0 */
    {
        return 0;
    }

    addon = 0;
    done = 1;
    t = p->type;

    if (isptr (type))        /* else L47d5 */
    {
        switch (t)
        {
            case LONG:      /* L47b2 */
                do_cast (p, INT);   /* do this at L47fe */
                break;      /* jump to L4807 */
            default:     /* L47b7 */
                if (!isptr (t))
                {
                    goto L4827;
                }
            case INT:      /* L4807 */
            case UNSIGN:      /* L4807 */
                break;
        }
    }

    /* L47d5 */
    else
    {
        if (isptr (t))    /* else L47ef */
        {
            if (!iswordorlong (type))      /* else L4807 */
            {
                goto L4827;
            }
        }
        else
        {
            do_cast (p, ((type == FLOAT) ? DOUBLE : type));   /* L47ef */
        }
    }

    /* L4807 here */
    
    if ((p->op == PLUS) || (p->op == MINUS))    /* else L4860 */
    {
        
        if ((p2 = p->right)->op != CONST)    /* else L4832 */
        {
L4827:
            done = 0;
            goto L4904;
        }

        addon = (p->op == MINUS) ? -(p2->val.num) : (p2->val.num);
        reltree (p2);
        p2 = p;
        p = p->left;
        release (p2);
    }

    /* L4860 */

    if (p->op == AMPER)   /* else L48b7 */
    {
        switch (((p2 = p->left)->val.sp)->storage)
        {
            default:     /* L4874 */
                done = 0;
                break;      /* go to L4906 */
            case STATIC:     /* L487b */
            case EXTERN:     /* L487b */
            case EXTDEF:     /* L487b */
            case DIRECT:     /* L487b */  /* '!' */
            case EXTERND:     /* L487b */  /* '"' */
                datflag = 1;
                prt_509e (p2, addon);
                datflag = 0;
                break;      /* go to L4906 */
        }
    }
    else
    {       /* L48b7 */
        switch (p->op)
        {
            case FCONST:     /* L48bb */  /* 'K' */
                if (type == FLOAT)    /* else L48cf */
                {
/*#ifdef COCO
#asm
                    ldx 8,u
                    pshs x
                    ldx 8,u
                    lbsr to_flacc
                    lbsr _dmove
#endasm
#else*/
                    /* ?????????? */
                    *p->val.fp = *p->val.dp;
/*#endif*/
                }

            case CONST:     /* L48cf */  /* '6' */
            case LCONST:     /* L48cf */  /* 'J' */
                datdef (p->val.num, type);

                break;      /* go to L4906 */
            case STRING:     /* L48dd */  /* '7' */
                prnt_fdb ();
                prtlcllbl (p->val.num);
                break;
            default:     /* L4874 */
                done = 0;
                break;      /* go to L4906 */
        }
    }

L4904:
    reltree (p);
    return done;
}

void
#ifndef COCO
datdef (register int valu, int f_type)
#else
datdef (valu, f_type)
    register int valu;
    int f_type;
#endif
{
    int _siz;

    switch (f_type)
    {
        case CHAR:      /* L4923 */
            prnt_fcb ();
#ifdef COCO
            prntdgt (valu);
#else
            prntdgt (valu & 0xff);
#endif
            prntCR ();
            return;
        case INT:      /* L4932 */
        case UNSIGN:      /* L4932 */
        default:     /* L4932 */
           _siz = (INTSIZE/2);
            break;
        case LONG:      /* L4937 */
            _siz = (LONGSIZE/2);
            break;
        case FLOAT:      /* L493e */
        case DOUBLE:      /* L493e */
            prt_float (valu, f_type);
            return;
    }

    prntnuls (valu, _siz);
}

void
cant_init ()
{
    reprterr ("cannot initialize");
    find_sep ();
}

/* ************************************************************ *
 * find_sep() - reads in input stream until ",", ";", or error  *
 * ************************************************************ */

void
find_sep ()
{
    for (;;)
    {
        switch (sym)
        {
            case COMMA:
            case SEMICOL:
            case -1:    /* err */
                return;
            default:
                nxt_word ();
        }
    }
}
