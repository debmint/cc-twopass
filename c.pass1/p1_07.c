/* ************************************************************ *
 * pass1_07.c                                                   *
 * This file deals with outputting data to the output stream    *
 * ************************************************************ */

/* $Id: p1_07.c 18 2008-05-19 21:54:22Z dlb $ */

/* This file is an exact match with the original code */

#include "pass1.h"

extern direct int datflag;

/* Print a label name & flag it ASM.  If it's global, add the ":" */

void
#ifndef COCO
prtlbl (char *lbnm, int isglbl)
#else
prtlbl (lbnm, isglbl)
    char *lbnm;
    int isglbl;
#endif
{
    prntstar ();    /* Flag it ASM */
    prtlbnm (lbnm);
    
    if (isglbl)
    {
        printchr (':');
    }

    prntCR ();
}

/* Print the passed string, preceded by a space */

void
#ifndef COCO
prtspstr (char *str)
#else
prtspstr (str)
    char *str;
#endif
{
    putc (' ', outpth);
    prntstring (str);
}

/* This was in cocd, but is not used.. we'll include it for comparison
 * to original source.. */

void
#ifndef COCO
prt_not_used (char *str)
#else
prt_not_used (str)
    char *str;
#endif
{
    prtspstr (str);
    prntCR ();
}

void
prntCR ()
{
    putc ('\n', outpth);
}

void
#ifndef COCO
printchr (int ch)
#else
printchr (ch)
    int ch;
#endif
{
    putc (ch, outpth);
}

void
#ifndef COCO
prntstring (char *str)
#else
prntstring (str)
    char *str;
#endif
{
    fprintf (outpth, str);
}

void
#ifndef COCO
prntdgt (int num)
#else
prntdgt (num)
    int num;
#endif
{
    fprintf (outpth, "%d", num);
}

void
#ifndef COCO
uselabel (int wrd)
#else
uselabel (wrd)
    int wrd;
#endif
{
    printchr ('l');
    putword (wrd, outpth);
     lastst = 0;
}

void
#ifndef COCO
prtlcllbl (int nbr)
#else
prtlcllbl (nbr)
    int nbr;
#endif
{
     lastst = 0;
    wrtunderscore (nbr);
    prntCR ();
}

/* ***************************************************** *
 * wrtunderscore () - Outputs a label name preceded      *
 *      by an underscore
 * ***************************************************** */

void
#ifndef COCO
wrtunderscore (int nbr)
#else
wrtunderscore (nbr)
    int nbr;
#endif
{
    printchr ('_');
    prntdgt (nbr);
}

/* Output a label name formatted to 8 spaces */

void
#ifndef COCO
prtlbnm (char *lbl)
#else
prtlbnm (lbl)
    char *lbl;
#endif
{
    fprintf (outpth, "%.8s", lbl);
}

int
#ifndef COCO
wrt_M (int nbr)
#else
wrt_M (nbr)
    int nbr;
#endif
{
    int lcl;

    if ((lcl = nbr - sp))
    {
        printchr ('M');
        putword (lcl, outpth);
    }

    return nbr;
}

void
#ifndef COCO
gen (int parm, int par2, int par3)
#else
gen (parm, par2, par3)
    int parm;
    int par2;
    int par3;
#endif
{
    register FILE *_opth = outpth;

    switch (parm)           /*L4bc5*/
    {
        case JMPEQ:    /* L4b6d */  /* '}' */
            printchr ('J');
            putword (par3, _opth);
            putword (par2, _opth);
            return;
        case RETURN:     /* L4b7d */
            printchr ('r');
            return;
        case GOTO:     /* L4b83 */
            printchr ('G');
            putword (par2, _opth);
            return;
        case JMP:    /* L4b88 */  /* '|' */
            printchr ('j');
            putword (par2, _opth);
            return;
        case LABEL:      /* L4b8d */
            printchr ('D');
#ifdef COCO
            putword (++LblNum,  _opth);
#else
            ++LblNum;
            putword (LblNum, _opth);
#endif
            putword (par2, _opth);
            return;
        case YREG:    /* L4ba9 */  /* 'v' */
            printchr ('Y');
            putword (par2, _opth);
            return;
        case UREG:    /* L4bae */  /* 'o' */
            printchr ('U');
            putword (par2, _opth);
            return;
    }
}

/* ******************************************************** *
 * prntstar () - output an asterisk - I think this flags    *
 * whatever follows as ASM code                             *
 * ******************************************************** */

void 
prntstar ()
{
    printchr ('*');
}

void
#ifndef COCO
prntfnam (char *str)
#else
prntfnam (str)
    char *str;
#endif
{
    fprintf (outpth, "F%s\n", str);
}

expnode *
#ifndef COCO
ld_exp (expnode *parm)
#else
ld_exp (parm)
    expnode *parm;
#endif
{
#ifdef __linux__
    prt_4c68 (1, parm, 0, 0, 0) ;
#else
    prt_4c68 (1, parm);
#endif
    return parm;
}

expnode *
#ifndef COCO
prt_4c2c (expnode *p1, int p2, int p3, int p4)
#else
prt_4c2c (p1, p2, p3, p4)
    expnode *p1;
    int p2;
    int p3;
    int p4;
#endif
{
    prt_4c68 (2, p1, p2, p3, p4);
    return p1;
}

expnode *
#ifndef COCO
transexp (expnode *cmdrf)
#else
transexp (cmdrf)
    expnode *cmdrf;
#endif
{
#ifdef __linux__
    prt_4c68 (4, cmdrf, 0, 0, 0) ;
#else
    prt_4c68 (4, cmdrf);
#endif
    return cmdrf;
}

void
#ifndef COCO
prt_4c68 (int addflg, expnode *cmdrf, int p3, int p4, int p5)
#else
prt_4c68 (addflg, cmdrf, p3, p4, p5)
    int addflg;
    expnode *cmdrf;
    int p3;
    int p4; 
    int p5;
#endif
{
    register FILE *_outp = outpth;
    putc ('T', _outp);      /* 84 */
    putword (addflg, _outp);
    putword (LblNum, _outp);
    putword (sp, _outp);

    switch (addflg)
    {
        case 2:      /* L4ca3 */
            putword (p3, _outp);
            putword (p4, _outp);
            putc (p5, _outp);
            break;
        case 5:      /* L4cc4 */
            putword (datflag, _outp);
            break;
        case 18:      /* L4cca */
            putword (p3, _outp);
            break;
    }

    LblNum += calc_value (cmdrf, ((addflg == 2) ? 1 : 0));
    wrtallinfo (cmdrf);
}

int
#ifndef COCO
calc_value (register expnode *wp, int _flg)
#else
calc_value (wp, _flg)
    register expnode *wp;
    int _flg;
#endif
{
    int _adder;
    int _frstflg;
    int _scndflg;

    if (wp)         /* else L4e13 */
    {
        switch (wp->op)
        {
            case DBLAND:  /* L4d23 */
            case DBLOR:    /* L4d23 */
                _adder = (_flg ? 1 : 4);
                _frstflg = _scndflg = 1;
                break;
            case NOT: /* L4d36 */
                _adder = 3;
                _frstflg = 1;
                break;
            case EQ:        /* L4d40 */
            case NEQ:
            case LEQ:
            case LT:
            case GEQ:
            case GT:
            case ULEQ:
            case ULT:
            case UGEQ:
            case UGT:
                _adder = (_flg ? 0 : 3);
                _frstflg = _scndflg = 0;
                break;
            case QUERY: /* L4d51 */
                _adder = 3;
                _frstflg = 1;
                _scndflg = 0;
                break;
            case CONST:      /* L4d62 */
            case LCONST:
                _adder = 1;
                _frstflg = _scndflg = _flg = 0;
                break;
            default:     /* L4d72 */
                _adder = _frstflg = _scndflg = _flg = 0;
                break;
        }

        return ((calc_value (wp->left, _frstflg) + _adder) +
                        (calc_value (wp->right, _scndflg)));
    }

    return 0;       /* struct wp not defined */
}

void
#ifndef COCO
wrtallinfo (register expnode *wp)
#else
wrtallinfo (wp)
    register expnode *wp;
#endif
{
    if (wp)
    {
        wrt_info (wp);
        wrtallinfo (wp->left);
        wrtallinfo (wp->right);
        }
    }

void
#ifndef COCO
wrt_info (register expnode *wp)
#else

#define ldf ((LBLDEF *)wp)
void 
wrt_info (wp)
    register expnode *wp;
#endif
{
    int v0;

    if ((wp->left) && (wp->right))
    {
        v0 = 'B';    /* 66 */   /* 0x42 */
    }
    else {
        if (wp->left)
        {
            v0 = 'L';    /* 76 */       /* 0x4c */
        }
        else {
            if (wp->right)
            {
                v0 = 'R';    /* 82 */   /* 0x52 */
            }
            else
            {
                v0 = 'N';    /* 78 */   /* 0x4e */
            }
        }
    }

    putc (v0, outpth);
    putword (wp->type, outpth);
    putword (wp->size, outpth);
    putword (wp->op, outpth);
    putword (wp->lno, outpth);

    /*putc (&(inpbuf[-(wp->pnt)]), outpth);*/
    putc ((int)((wp->pnt) - inpbuf), outpth);

    putc (wp->sux, outpth);
    putword (wp->modifier, outpth);

    if (wp->op == C_USRLBL)       /* '4' */   /* else L4f4f */
    {
#ifndef COCO
        symnode *ldf;
#endif
        /* Following will probably get an error without casting, but
         * leave it to examine later */
        /* I believe that here, wp will be a LBLDEF * */
        ldf = wp->val.sp;
        putc (ldf->type, outpth);
        putc (ldf->storage, outpth);

        switch (ldf->storage)
        {
            case EXTERN:     /* L4f0e */
            case EXTDEF:      /* 12 */
            case DIRECT:     /* 33 */
            case EXTERND:     /* 34 */
                prtlbnm (ldf->sname);
                putc ('\0', outpth);
                return;
            default:     /* L4f2a */
                /*putword (ldf->op, outpth);*/
                putword (ldf->storage, outpth);
                return;
        }
    }

    if (wp->op == LCONST)   /* 'J' */   /* else L4f8b */
    {
        long mylng = 0;

        /* wp assignment will probably give warning */
        fwrite (((wp = (expnode *)(wp->val.lp)) ? (long *)wp : &mylng),
                                sizeof (LONGTYPE), 1, outpth);
    }
    else
    {
        if (wp->op == CONST)   /* L4f8b */  /* else L4fce */
        {
            double mydbl = 0;

            fwrite (((wp = (expnode *)(wp->val.dp)) ? (double *)wp : &mydbl),
                                        sizeof (DBLETYPE), 1, outpth);
        }
        else
        {
            putword (wp->val.num, outpth);
        }
    }
}

/* prntnuls() - print a string of (or single) comma-separated string
 * of digits or zeros depending on the first param
 */

void
#ifndef COCO
prntnuls (register int *valu, int countflg)
#else
prntnuls (valu, countflg)
    register int *valu;
    int countflg;
#endif
{
    int v0;

    prnt_fdb ();

    if (countflg == 1)
    {
        prntdgt ((int)valu);           /* go to L505f */
    }
    else
    {
        if (valu == 0)        /* L4fff  else 5030 */
        {
            v0 = 1;

            while (v0++ < countflg)
            {
                prntstring ("0,");
            }

            printchr ('0');
        }
        else
        {
            v0 = 0;

            while (v0 < countflg)
            {
                prntdgt(*(valu++));  /* L5034 */
                
                if (countflg - 1 != v0)
                {
                    printchr (',');
                }

                v0++;
            }
        }
    }

    prntCR ();
}

/* ******************************************************** *
 * prt_float () - flags "float", writes type whether float  *
 *      or double, and writes the value to to output stream *
 * ******************************************************** */

int 
#ifndef COCO
prt_float (register char *data_val, int f_type)
#else
prt_float (data_val, f_type)
    register char *data_val;
    int f_type;
#endif
{
    printchr ('f'); /* C_BKSLSH */    /*0x66*/
    putword (f_type, outpth);
    fwrite (data_val, 8, 1, outpth);
}

int 
#ifndef COCO
prt_509e (register expnode *p1, int p2)
#else
prt_509e (p1, p2)
    register expnode *p1;
    int p2;
#endif
{
    p1->modifier += p2;
#ifdef COCO
    prt_4c68 (5, p1);
#else
    prt_4c68 (5, p1, 0, 0, 0);
#endif
}
