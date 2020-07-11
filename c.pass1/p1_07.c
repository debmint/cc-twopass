/* ************************************************************ *
 * pass1_07.c                                                   *
 * This file deals with outputting data to the output stream    *
 * ************************************************************ */

/* $Id: p1_07.c 18 2008-05-19 21:54:22Z dlb $ */

/* This file is an exact match with the original code */

#include "pass1.h"

extern direct int D000d;

/* Print a label name & flag it ASM.  If it's global, add the ":" */

#ifndef COCO

void
prtlbl (char *lbnm, int isglbl)
#else

void 
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

#ifndef COCO

void
prtspstr (char *str)
#else

void 
prtspstr (str)
char *str;
#endif
{
    putc (' ', outpth);
    prntstring (str);
}

/* This was in cocd, but is not used.. we'll include it for comparison
 * to original source.. */

#ifndef COCO

void
prt_not_used (char *str)
#else

void 
prt_not_used (str)
char *str;
#endif
{
    prtspstr (str);
    prntCR ();
}

#ifndef COCO

void
prntCR (void)
#else

void 
prntCR ()
#endif
{
    putc ('\n', outpth);
}

#ifndef COCO

void
printchr (int ch)
#else

void 
printchr (ch)
int ch;
#endif
{
    putc (ch, outpth);
}

#ifndef COCO

void
prntstring (char *str)
#else

void 
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

#ifndef COCO

void
prntw_l (int wrd)
#else

void 
prntw_l (wrd)
int wrd;
#endif
{
    printchr ('l');
    putword (wrd, outpth);
    D004f = 0;
}

#ifndef COCO

void
prtlcllbl (int nbr)
#else

void 
prtlcllbl (nbr)
int nbr;
#endif
{
    D004f = 0;
    wrtunderscore (nbr);
    prntCR ();
}

/* ***************************************************** *
 * wrtunderscore () - Outputs a label name preceded      *
 *      by an underscore
 * ***************************************************** */

#ifndef COCO

void
wrtunderscore (int nbr)
#else

void 
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

#ifndef COCO

int
wrt_M (int nbr)
#else

int 
wrt_M (nbr)
int nbr;
#endif
{
    int lcl;

    if ((lcl = nbr - D002f))
    {
        printchr ('M');
        putword (lcl, outpth);
    }

    return nbr;
}

#ifndef COCO

void
prt_4b5e (int parm, int par2, int par3)
#else

void 
prt_4b5e (parm, par2, par3)
int parm;
int par2;
int par3;
#endif
{
    register FILE *_opth = outpth;

    switch (parm)           /*L4bc5*/
    {
        case 125:    /* L4b6d */  /* '}' */
            printchr ('J');
            putword (par3, _opth);
            putword (par2, _opth);
            return;
        case 18:     /* L4b7d */
            printchr ('r');
            return;
        case 29:     /* L4b83 */
            printchr ('G');
            putword (par2, _opth);
            return;
        case 124:    /* L4b88 */  /* '|' */
            printchr ('j');
            putword (par2, _opth);
            return;
        case 9:      /* L4b8d */
            printchr ('D');
#ifdef COCO
            putword (++LblNum,  _opth);
#else
            ++LblNum;
            putword (LblNum, _opth);
#endif
            putword (par2, _opth);
            return;
        case C_X_RGWRD:    /* L4ba9 */  /* 'v' */
            printchr ('Y');
            putword (par2, _opth);
            return;
        case C_RGWRD:    /* L4bae */  /* 'o' */
            printchr ('U');
            putword (par2, _opth);
            return;
    }
}

/* ******************************************************** *
 * prntstar () - output an asterisk - I think this flags    *
 * whatever follows as ASM code                             *
 * ******************************************************** */

#ifndef COCO

void 
prntstar (void)
#else

void
prntstar ()
#endif
{
    printchr ('*');
}

#ifndef COCO

void
prntfnam (char *str)
#else

void 
prntfnam (str)
char *str;
#endif
{
    fprintf (outpth, "F%s\n", str);
}

#ifndef COCO

CMDREF *
prt_4c1b (CMDREF *parm)
#else

CMDREF *
prt_4c1b (parm)
CMDREF *parm;
#endif
{
#ifdef __linux__
    prt_4c68 (1, parm, 0, 0, 0) ;
#else
    prt_4c68 (1, parm);
#endif
    return parm;
}

#ifndef COCO

CMDREF *
prt_4c2c (CMDREF *p1, int p2, int p3, int p4)
#else

CMDREF * 
prt_4c2c (p1, p2, p3, p4)
CMDREF *p1;
int p2;
int p3;
int p4;
#endif
{
    prt_4c68 (2, p1, p2, p3, p4);
    return p1;
}

#ifndef COCO

CMDREF *
prt_4c4f (CMDREF *cmdrf)
#else

CMDREF *
prt_4c4f (cmdrf)
CMDREF *cmdrf;
#endif
{
#ifdef __linux__
    prt_4c68 (4, cmdrf, 0, 0, 0) ;
#else
    prt_4c68 (4, cmdrf);
#endif
    return cmdrf;
}

#ifndef COCO

void
prt_4c68 (int addflg, CMDREF *cmdrf, int p3, int p4, int p5)
#else
prt_4c68 (addflg, cmdrf, p3, p4, p5)
int addflg;
CMDREF *cmdrf;
int p3;
int p4; 
int p5;
#endif
{
    register FILE *_outp = outpth;
    putc ('T', _outp);      /* 84 */
    putword (addflg, _outp);
    putword (LblNum, _outp);
    putword (D002f, _outp);

    switch (addflg)
    {
        case 2:      /* L4ca3 */
            putword (p3, _outp);
            putword (p4, _outp);
            putc (p5, _outp);
            break;
        case 5:      /* L4cc4 */
            putword (D000d, _outp);
            break;
        case 18:      /* L4cca */
            putword (p3, _outp);
            break;
    }

    LblNum += calc_value (cmdrf, ((addflg == 2) ? 1 : 0));
    wrtallinfo (cmdrf);
}

#ifndef COCO

int
calc_value (register CMDREF *wp, int _flg)
#else
calc_value (wp, _flg)
register CMDREF *wp;
int _flg;
#endif

{
    int _adder;
    int _frstflg;
    int _scndflg;

    if (wp)         /* else L4e13 */
    {
        switch (wp->vartyp)
        {
            case C_ANDAND:  /* L4d23 */
            case C_OROR:    /* L4d23 */
                _adder = (_flg ? 1 : 4);
                _frstflg = _scndflg = 1;
                break;
            case C_EXCLAM: /* L4d36 */
                _adder = 3;
                _frstflg = 1;
                break;
            case C_EQEQ:        /* L4d40 */
            case C_NOTEQ:
            case C_LT_EQ:
            case C_LT:
            case C_GT_EQ:
            case C_GT:
            case 96:
            case 97:
            case 98:
            case 99:
                _adder = (_flg ? 0 : 3);
                _frstflg = _scndflg = 0;
                break;
            case C_QUESTION: /* L4d51 */
                _adder = 3;
                _frstflg = 1;
                _scndflg = 0;
                break;
            case C_DOUBLE:      /* L4d62 */
            case C_LONG:
                _adder = 1;
                _frstflg = _scndflg = _flg = 0;
                break;
            default:     /* L4d72 */
                _adder = _frstflg = _scndflg = _flg = 0;
                break;
        }

        return ((calc_value (wp->cr_Left, _frstflg) + _adder) +
                        (calc_value (wp->cr_Right, _scndflg)));
    }

    return 0;       /* struct wp not defined */
}

#ifndef COCO

void
wrtallinfo (register CMDREF *wp)
#else
wrtallinfo (wp)
register CMDREF *wp;
#endif
{
    if (wp)
    {
        wrt_info (wp);
        wrtallinfo (wp->cr_Left);
        wrtallinfo (wp->cr_Right);
    }
}

#ifndef COCO

void
wrt_info (register CMDREF *wp)
#else

#define ldf ((LBLDEF *)wp)
void 
wrt_info (wp)
register CMDREF *wp;
#endif
{
    int v0;

    if ((wp->cr_Left) && (wp->cr_Right))
    {
        v0 = 'B';    /* 66 */   /* 0x42 */
    }
    else {
        if (wp->cr_Left)
        {
            v0 = 'L';    /* 76 */       /* 0x4c */
        }
        else {
            if (wp->cr_Right)
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
    putword (wp->ft_Ty, outpth);
    putword (wp->__cr2, outpth);
    putword (wp->vartyp, outpth);
    putword (wp->_cline, outpth);

    /*putc (&(inpbuf[-(wp->_lpos)]), outpth);*/
    putc ((int)((wp->_lpos) - inpbuf), outpth);

    putc (wp->__cr18, outpth);
    putword (wp->cr_Nxt, outpth);

    if (wp->vartyp == C_USRLBL)       /* '4' */   /* else L4f4f */
    {
#ifndef COCO
        LBLDEF *ldf;
#endif
        /* Following will probably get an error without casting, but
         * leave it to examine later */
        /* I believe that here, wp will be a LBLDEF * */
        ldf = (LBLDEF *)(wp->cmdval);  /* LBLDEF *, actually */
        putc (ldf->gentyp, outpth);
        putc (ldf->fnccode, outpth);

        switch (ldf->fnccode)
        {
            case FT_EXTERN:     /* L4f0e */
            case FT_LSEEK:      /* 12 */
            case FT_DIRECT:     /* 33 */
            case FT_DPXTRN:     /* 34 */
                prtlbnm (ldf->fnam);
                putc ('\0', outpth);
                return;
            default:     /* L4f2a */
                /*putword (wp->vartyp, outpth);*/
                putword (ldf->lbl_nbr, outpth);
                return;
        }
    }

    if (wp->vartyp == C_LONG)   /* 'J' */   /* else L4f8b */
    {
        long mylng = 0;

        /* wp assignment will probably give warning */
        fwrite (((wp = (CMDREF *)(wp->cmdval)) ? (long *)wp : &mylng),
                                sizeof (long), 1, outpth);
    }
    else
    {
        if (wp->vartyp == C_DOUBLE)   /* L4f8b */  /* else L4fce */
        {
            double mydbl = 0;

            fwrite (((wp = (CMDREF *)(wp->cmdval)) ? (double *)wp : &mydbl),
                                        sizeof (double), 1, outpth);
        }
        else
        {
            putword (wp->cmdval, outpth);
        }
    }
}

/* prntnuls() - print a string of (or single) comma-separated string
 * of digits or zeros depending on the first param
 */

#ifndef COCO

void
prntnuls (register int *valu, int countflg)
#else

void 
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
#ifndef COCO

prt_float (register char *data_val, int f_type)
#else

int 
prt_float (data_val, f_type)
register char *data_val;
int f_type;
#endif
{
    printchr ('f'); /* C_BKSLSH */    /*0x66*/
    putword (f_type, outpth);
    fwrite (data_val, 8, 1, outpth);
}

#ifndef COCO

prt_509e (register CMDREF *p1, int p2)
#else

int 
prt_509e (p1, p2)
register CMDREF *p1;
int p2;
#endif
{
    p1->cr_Nxt += p2;
#ifdef COCO
    prt_4c68 (5, p1);
#else
    prt_4c68 (5, p1, 0, 0, 0);
#endif
}
