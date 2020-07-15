/* ****************************************************** *
 * pass1_04.c                                             *
 * ****************************************************** */

/* $Id: p1_04.c 18 2008-05-19 21:54:22Z dlb $ */

/* This file is an exact match with original */

#include "pass1.h"

/*******************************
 *                             *
 *   statement parser          *
 *                             *
 *******************************/

/*static swcherr();*/

/*typedef struct casestct {
    struct casestct *clink;*/     /* next case in case list */
    /*int cval;*/                   /* case value */
    /*short clab;*/                 /* case label */
/*} casnode;*/

#define CASESIZE    sizeof(casnode)

/*direct  casnode *caseptr,*/   /* list of cases */
                /**lastcase,*/  /* last case in current list */
                /**freecase;*/  /* list of spare case nodes */

#if 0
static int  swflag,         /* current switch level */
#else
/*static int*/
#endif
            /*deflabel;*/       /* switch default label */

/*static labstruc *breakptr,*/      /* break label */
                /**contptr;*/       /* continue label */

#ifdef REGCONTS
extern  expnode *dregcont,      /* D register content */
                *xregcont;      /* X register content */
#endif

static symnode *checklabel ();
static expnode *getptest ();
static expnode *gettest ();
static void dolabel ();

#ifdef COCO
static expnode *sidexp (int p1);
static expnode *emit (register expnode *ptr);
void dotest (register expnode *regptr, int p2, int p3, int p4);
#else
static expnode *sidexp ();
static expnode *emit ();
void dotest ();
#endif

void
statement ()
{
    if (sym != SEMICOL)
    {
         lastst = 0;
    }

contin:
    switch (sym)
    {
        case SEMICOL:     /* L290b */  /* '(' */
            break;
        case KEYWORD:     /* L27ed */  /* '3' */
            switch (symval)
            {
                case IF:     /* L27f1 */
                    do_if ();
                    return;
                case WHILE:     /* L27f6 */
                    do_while ();
                    return;
                case RETURN:     /* L27fb */
                    do_retrn ();
                    break;  /* go to L290b */
                case CASE:     /* L2801 */
                    do_case ();
                    return;
                case SWITCH:     /* L2806 */
                    do_swtch ();
                    return;
                case BREAK:     /* L280b */
                    do_break ();
                    break;      /* go to L290b */
                case CONTIN:     /* L2811 */
                    do_contin ();
                    break;      /* go to L290b */
                case DEFAULT:     /* L2817 */
                    do_deflt ();
                    return;
                case FOR:     /* L281c */
                    do_for ();
                    return;
                case DO:     /* L2821 */
                    do_do ();
                    break;      /* go to L290b */
                case GOTO:     /* L2827 */
                    do_goto ();
                    break;      /* go to L290b */
                case ELSE:     /* L282d */
                    reprterr ("no 'if' for 'else'");
                    nxt_word ();      /* go to L2897 */
                    goto contin;
                default:     /* L283e */
                    goto what;
            }

            break;
        case LBRACE:     /* L2881 */  /* ')' */
            block ();
            nxt_word ();
            return;
        case -1:     /* L2889 */  /* ')' */
            return;
        case NAME:     /* L288b */  /* '4' */
            skipblank ();
            
            if (CurChr == ':')
            {
                dolabel ();
                goto contin;
            }
            else
            {
                goto tryexp;
            }
        default:     /* L28a2 */
what:
            if (issclass () || istype ())
            {
                reprterr ("illegal declaration");
                
                do
                {
                    nxt_word ();
                } while (sym != SEMICOL);

                break;
            }
            else
            {
tryexp:
                if (!(sidexp (0)))
                {
                    reprterr ("syntax error");
                    junk ();
                    return;
                }
            }

            break;
    }

    need (SEMICOL);     /* L290b */
}

void
do_if ()
{
    register int t1, f1, v2;
    expnode *ptr;

    nxt_word ();
    ptr = getptest ();
    t1 = ++LblNum;
    f1 = ++LblNum;

    if (sym == SEMICOL)    /* else L2966 */
    {
        nxt_word ();
        dotest (ptr, t1, f1, 0);
        uselabel (f1);
        v2 = t1;
    }
    else
    {
        dotest (ptr, t1, f1, 1);
        uselabel (t1);
        statement ();
        v2 = f1;
    }

    /* L2988 */
    if ((sym == KEYWORD) && (symval == ELSE))    /* else L29cd */
    {
        nxt_word ();

        if (sym != SEMICOL)        /* else L29cd */
        {
            if (t1 != v2)   /* else L29ca */
            {
                gen (JMP, (v2 = ++LblNum), 0);
                uselabel (f1);
            }

            statement ();
        }
    }

    uselabel (v2);   /* L29cd */
}

void
do_while ()
{
    int v8;
    int v6;
    int v4;
    int v2;
    expnode *ptr;
    register int cnt;

    v8 = D0053;
    v6 = contptr;
    v4 = D02d6;
    v2 = D02d8;
    nxt_word ();
    D0053 = ++LblNum;
    D02d6 = D02d8 = sp;
    contptr = ++LblNum;
    ptr = getptest ();

    if (sym == SEMICOL)
    {
        cnt = contptr;
    }
    else
    {
        gen (JMP, contptr, 0);
        cnt = ++LblNum;
        uselabel (cnt);
        statement ();
    }

    uselabel (contptr);       /* L2a4d */
    dotest (ptr, cnt, D0053, 0);
    uselabel (D0053);
    D0053 = v8;
    contptr = v6;
    D02d6 = v4;
    D02d8 = v2;
}

void
do_swtch ()
{
    int v12;
    casnode *savcas;
    int savdef;
    int tests;
    int temp;
    int v2;
    struct casnode *_refsav;
    register expnode *ptr;

    nxt_word ();
    ++swflag;
    _refsav = lastcase;
    savcas = caseptr;
    caseptr = 0;
    v12 = D0053;
    savdef = deflabel;
    v2 = D02d6;
    D0053 = ++LblNum;
    D02d6 = sp;
    deflabel = 0;

    /* get the case value */

    need (LPAREN);
    
    if ((ptr = optim(parsexp (0))))       /* else L2b3e */
    {
        ck_declared (ptr);
        
        switch (ptr->type)
        {
            case CHAR:      /* L2af8 */
            case LONG:
                do_cast (ptr, INT);
                break;
            case INT:      /* L2b2e */
            case UNSIGN:
                break;
            default:     /* L2b06 */
                notintegral (ptr);
                makedummy (ptr);
                break;
        }

        ld_exp (ptr);
        reltree (ptr);
    }
    else
    {
        exprmsng ();    /* L2b3e */
    }

    need (RPAREN);
    gen (JMP, (tests = ++LblNum), 0);
    statement ();

    if (! lastst)
    {
        gen (JMP, D0053, 0);
    }

    uselabel (tests);       /* L2b7d */
    ptr = caseptr;

    while (ptr)     /* L2ba8 */
    {
        temp = ptr->type;
        gen (JMPEQ, ptr->dimptr, ptr->size);
        ptr->type = freecase;
        freecase = ptr;
        ptr = temp;
    }

    if (deflabel)
    {
        gen (JMP, deflabel, 0);
    }

    uselabel (D0053);        /* L2bc6 */
    caseptr = savcas;
    deflabel = savdef;
    --swflag;
    lastcase = _refsav;
    D0053 = v12;
    D02d6 = v2;
}

void
do_case ()
{
    int val;
    register casnode *ptr;

    nxt_word ();
    val = constexp (0);
    need (COLON);

    if (swflag)          /* else L2c55 */
    {
        if (ptr = freecase)
        {
            freecase = ptr->clink;
        }
        else
        {
            ptr = addmem (CASESIZE);     /* L2c21 */
        }

        if (caseptr)      /* L2c2d */
        {
            lastcase->clink = ptr;
        }
        else
        {
            caseptr = ptr;
        }

        lastcase = ptr;     /* L2c39 */

        /* Fix this!  ptr is a 6-byte structure */
        ptr->clink = 0;
        ptr->cval = val;
        uselabel ((ptr->clab = ++LblNum));
    }
    else
    {
        no_switch ();
    }
}

void
do_deflt ()
{
    nxt_word ();

    if (!swflag)
    {
        no_switch ();
    }

    if (deflabel)
    {
        reprterr ("multiple defaults");
    }
    else
    {
        uselabel ((deflabel = ++LblNum));
    }

    need (COLON);
}

void
no_switch ()
{
    reprterr ("no switch statement");
}

void
do_do ()
{
    int v8;
    int v6;
    int looptop;
    int tptr;
    int uptr;

    v8 = D0053;
    v6 = contptr;
    uptr = D02d8;
    tptr = D02d6;
    D02d8 = D02d6 = sp;
    contptr = ++LblNum;
    D0053 = ++LblNum;
    nxt_word ();
    uselabel ((looptop = ++LblNum));
    statement ();

    if ((sym != KEYWORD) || (symval != WHILE))
    {
        reprterr ("while expected");
    }

    nxt_word ();
    uselabel (contptr);
    dotest (getptest (), looptop, D0053, 0);
    uselabel (D0053);
    D0053 = v8;
    contptr = v6;
    D02d6 = tptr;
    D02d8 = uptr;
}

void
do_for ()
{
    int v12;
    int cnt;
    int v8;
    int v6;
    int v4;
    expnode *tptr;
    int uptr;
    register int *regptr;

    tptr = 0;
    uptr = 0;
    regptr = D0053;
    v12 = contptr;
    v6 = D02d6;
    v4 = D02d8;
    D02d8 = D02d6 = sp;
    cnt = ++LblNum;
    D0053 = ++LblNum;
    nxt_word ();
    need (LPAREN);
    sidexp (0);
    need (SEMICOL);

    if (sym != SEMICOL)
    {
        tptr = gettest ();
        gen (JMP, (v8 = ++LblNum), 0);
    }

    need (SEMICOL);     /* L2de0 */
    
    if (uptr = optim (parsexp (0)))
    {
        ck_declared (uptr);
        contptr = ++LblNum;
    }
    else
    {
        contptr = cnt;
    }

    need (RPAREN);
    uselabel (cnt);
    statement ();

    if (uptr)
    {
        uselabel (contptr);
        emit (uptr);
    }

    if (tptr)     /* L2e3e */
    {
        uselabel (v8);
        dotest (tptr, cnt, D0053, 0);
    }
    else
    {
        gen (JMP, cnt,0);
    }

    uselabel (D0053);
    D0053 = regptr;
    contptr = v12;
    D02d6 = v6;
    D02d8 = v4;
}

void
do_retrn ()
{
    register CMDREF *regptr;

    nxt_word ();

    if ((sym != SEMICOL) && (regptr = parsexp ((CMDREF *)0)))      /* else L2f00 */
    {
        regptr = optim (regptr);
        ck_declared (regptr);
        get_ftty (regptr);

        do_cast (regptr, ((isptr (ftype)) ? 1 : ftype));
#ifdef __linux__
        prt_4c68 (RETURN, regptr, ftype, 0, 0);
#else
        prt_4c68 (RETURN, regptr, ftype);
#endif
        reltree (regptr);
    }

    wrt_M (0);
    gen (RETURN, 0, 0);
     lastst = RETURN;
}

void
do_break ()
{
    nxt_word ();

    if (!D0053)
    {
        reprterr ("break error");
    }
    else
    {
        wrt_M (D02d6);
        gen (JMP, D0053, 0);
    }
    
     lastst = BREAK;
}

void
do_contin ()
{
    nxt_word ();

    if (!contptr)
    {
        reprterr ("continue error");
    }
    else
    {
        wrt_M (D02d8);
        gen (JMP, contptr, 0);
    }

     lastst = CONTIN;
}

void
do_goto ()
{
    register symnode *regptr;

    nxt_word ();

    if (sym != NAME)
    {
        reprterr ("label required");
    }
    else
    {
        if ((regptr = checklabel ()))
        {
            gen (GOTO, regptr->offset, 0);
            regptr->x.labflg |= GONETO;
        }

        nxt_word();
    }

     lastst = GOTO;
}

static void
dolabel ()
{
    register symnode *regptr;

    if ((regptr = checklabel ()))
    {
        if (regptr->storage == STATIC)   /* STATIC */
        {
            multdef ();
        }
        else
        {
            regptr->storage = STATIC;
            gen (LABEL, regptr->offset, 0);
            regptr->x.labflg |= DEFINED;
        }
    }

    nxt_word ();
    nxt_word ();
}

static symnode *
checklabel ()
{
    register symnode *ptr = symval;

    if (ptr->type != LABEL)        /* else L313c */
    {
        if (ptr->type)
        {
            if (ptr->blklev)
            {
                reprterr ("already a local variable");
                return 0;
            }

            pushdown (ptr); /* copy ptr to G18Current, null ptr */
        }

        ptr->type = LABEL;
        ptr->storage = FT_AUTO;
        ptr->offset = ++LblNum;
        ptr->x.labflg = 0;
        ptr->blklev = blklev;
        ptr->snext = labelist;
        labelist = ptr;
    }

    return ptr;
}

static expnode *
#ifndef COCO
sidexp (int p1)
#else
sidexp (p1)
    int p1;
#endif
{
    register expnode *regptr;

    if ((regptr = parsexp (p1)))  /* else return regptr */
    {
        regptr = emit (optim (regptr));
    }

    return regptr;
}

static expnode *
#ifndef COCO
emit (register expnode *ptr)
#else
emit (ptr)
    register expnode *ptr;
#endif
{
    ck_declared (ptr);

    switch (ptr->op)
    {
        case INCAFT:     /* L30c0 */  /* '>' */
            ptr->op = INCBEF;
            break;
        case DECAFT:     /* L30c5 */  /* '?' */
            ptr->op = DECBEF;
            break;
    }

    ptr = transexp (ptr);
    reltree (ptr);
    return ptr;
}

static expnode *
getptest ()
{
    expnode *v0;

    need (LPAREN);
    v0 = gettest ();
    need (RPAREN);
    return v0;
}

static expnode *
gettest ()
{
    register expnode *regptr;

    if (regptr = optim (parsexp (0)))
    {
        ck_declared (regptr);
    }
    else
    {
        reprterr ("condition needed");
    }

    return regptr;
}

void
#ifndef COCO
dotest (register expnode *regptr, int p2, int p3, int p4)
#else
dotest (regptr, p2, p3, p4)
    register expnode *regptr;
    int p2;
    int p3;
    int p4;
#endif
{
    if (regptr)
    {
        prt_4c2c (regptr, p2, p3, p4);
        reltree (regptr);
    }
}
