/* ****************************************************** *
 * pass1_10.c                                             *
 * Deals with outputting data to the output stream        *
 * ****************************************************** */

/* $Id: p1_10.c 18 2008-05-19 21:54:22Z dlb $ */


/* This file is an exact match with the original code
 * Note that there is an error in the original code at seek0_FP,
 * where we have a comment "ERROR IN ORIGINAL CODE" We won't fix this
 * just yet
 */

#include "pass1.h"
#include <errno.h>

#ifndef COCO
#   include <unistd.h>
#endif

#ifndef COCO

void
dumpstrings (void)
#else

void 
dumpstrings ()
#endif
{
    dumpstrs ();
    putc_e ();
}

#ifndef COCO

void
rmbnolbl (int p1, int valu, int p3)
#else

void 
rmbnolbl (p1, valu, p3)
int p1;
int valu;
int p3;
#endif
{
    wdataflag (p3);
    prntstar ();
    wrtunderscore (p1);
    fprintf (outpth, " rmb %d\n", valu);
    putc_e ();
}

#ifndef COCO

void
globldata (LBLDEF *p1, int p2, int p3)
#else

void 
globldata (p1, p2, p3)
LBLDEF *p1;
int p2;
int p3;
#endif
{
    wdataflag (p3);
    lbl_rmb (p1, p2, ':');
    putc_e ();
}

#ifndef COCO

void
localdata (LBLDEF *p1, int p2, int p3)
#else
localdata (p1, p2, p3)
LBLDEF *p1;
int p2;
int p3;
#endif
{
    wdataflag (p3);
    lbl_rmb (p1, p2, ' ');
    putc_e ();
}

#ifndef COCO

lbl_rmb (LBLDEF *p1, int p2, char _colon)
#else
lbl_rmb (p1, p2, _colon)
LBLDEF *p1;
int p2;
char _colon;
#endif
{
    prntstar ();
    fprintf (outpth, "%.8s%c rmb %d\n", p1->fnam, _colon, p2);
}

#ifndef COCO

void
prtstkchk (char *funcnam, int p2, int p3)
#else

void 
prtstkchk (funcnam, p2, p3)
char *funcnam;
int p2;
int p3;
#endif
{
    putc ('S', outpth); /* 0x53 */
    putc (p2, outpth);
    
    if (!nostkck)
    {
#ifdef COCO
        putword (++LblNum, outpth);
#else
        ++LblNum;   /* separate because macro will inc twice */
        putword (LblNum, outpth);
#endif
    }

    fprintf (outpth, "%.8s%c", funcnam, 0);

    if (doprofil)
    {
        putword (p3, outpth);
    }
}

#ifndef COCO

void
prtprofil (char *p1, int p2)
#else

void 
prtprofil (p1, p2)
char *p1;
int p2;
#endif
{
    printchr ('p');     /* 0x70 */
    putword (p2, outpth);
    fprintf (outpth, "%.8s%c", p1, 0);
}

#ifndef COCO

void
flgstkchk(void)
#else

void 
flgstkchk ()
#endif
{
    if (!nostkck)
    {
        putc ('E', outpth);     /* 0x45 */
    }
}

#ifndef COCO

void
prnt_fcb (void)
#else

void 
prnt_fcb ()
#endif
{
    prntstar ();
    prtspstr ("fcb ");
}

#ifndef COCO

void
prnt_fdb (void)
#else

void 
prnt_fdb ()
#endif
{
    prntstar ();
    prtspstr ("fdb ");
}

#ifndef COCO

void
pr2stars (void)
#else

void 
pr2stars ()
#endif
{
    prntstar ();
    prntstring ("* ");
}

/* ************************************************************* *
 * wdataflag () - Write the dataflag to the output stream         *
 * Passed: 1 if DP else 0                                        *
 * ************************************************************* */

#ifndef COCO

void wdataflag (int p1)
#else

void 
wdataflag (p1)
int p1;
#endif
{
    if (p1)
    {
        printchr ('d');     /* 0x64 */
    }
    else
    {
        printchr ('v');     /* 0x76 */
    }
}

#ifndef COCO

void
putc_e (void)
#else

void 
putc_e ()
#endif
{
    printchr ('e');     /* 0x65 */
}

/* ******************************************************** *
 * seek0_FP () - repositions the buffers to the end of the  *
 *          current data, it seems                          *
 * ******************************************************** */

#ifndef COCO

int
seek0_FP (FILE *_fp)
#else
int
seek0_FP (_fp)
FILE *_fp;
#endif
{
    fflush (_fp);

    /* We need to fix this for cross compiler */

#ifdef COCO
    /* Set buffer ptr to end of buffer */   /* fixed ??? */
    _fp->_ptr = _fp->_end = &(_fp->_base[_fp->_bufsiz]);
    /*_fp->_flag &= 0xfeef;*/   /*!( _EOF | _WRITTEN) */
    _fp->_flag &= ~( _EOF | _WRITTEN);
    lseek (fileno (_fp), 0l, 0);
    /* we need only the LS word */
#asm
    ldd _flacc+2,y
#endasm
#else
        fseek (_fp, 0, SEEK_SET);
#endif
}

#ifndef COCO

void
dumpstrs (void)
#else

void 
dumpstrs ()
#endif
{
    if (stmpFP)
    {
        register int ch;

        seek0_FP (stmpFP);

        while ((ch = getc (stmpFP)) != -1)
        {
            putc (ch, outpth);
        }

#ifdef COCO
        if (ferror(stmpFP))
        {
            /*clearerr ("dumpstrings");*/
            /* ERROR IN ORIGINAL CODE */
            ferror ("dumpstrings");
            /* The below is totally nonsensical to me... */
/*#asm
L694d: fcc "dumpstrings"
       fcb 0
            leax L694d,pcr
            ldd 6,x
            clra
            andb #$20
#endasm*/
        }
#endif
        
        fclose (stmpFP);
        unlink (cstrtmp);
    }
}

#ifndef COCO

void
quitcc (void)
#else

void 
quitcc ()
#endif
 
{
    int v0 = (errno ? errno : 1);

    fflush (stdout);

    if (stmpFP)
    {
        fclose (stmpFP);
        unlink (cstrtmp);
    }

    if (srcfile)
    {
        fclose (inpth);
        unlink (srcfile);
    }

    _exit(v0);
}
