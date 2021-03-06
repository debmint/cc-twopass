/* ******************************************************** *
 * pass1_09.c - Functions dealing with reading input file   *
 * ******************************************************** */

/* $Id: p1_09.c 14 2008-04-17 02:41:13Z dlb $ */

/* This file is an exact match with original source */

#include "pass1.h"

extern char _chcodes[];

/* initbuf0() - startup routine to initialize certain buffers */

void
initbuf0 ()
{
    CurLine = inpbuf;
    inpbuf[0] = '\0';
    CurChr = ' ';
}

/* ************************************************************* *
 * skipblank () a getnxtch() function that bypasses whitespaces  *
 * ************************************************************* */

void 
skipblank ()
{
    while ((CurChr == ' ') || (CurChr == '\t'))
    {
        getnxtch ();
    }
}

/* ***************************************************************** *
 * getnxtch () - places next character into the variable CurChr.     *
 *    gets next applicable line if current line is exhausted..       *
 * ***************************************************************** */

void
getnxtch ()
{
    if ((CurChr = *(CurLine++)) == '\0')
    {
        CurChr = prepln ();
    }
}

/* ********************************************************** *
 * prepln() - Processes control lines  (those beginning with  *
 *           "#".                                             *
 * ********************************************************** */

char
prepln ()
{
    int lno;
    int _prepcod;
    int x;
    int v0;

    if (D001d == 0)
    {
        D001d = 1;
        CurLine = "";     /* go to L6566 */
        return ' ';
    }

    D001d = 0;      /*L6385*/
    strcpy (prevlin, inpbuf);     /* Save current line */
    
    for (;;)    /*L639a*/
    {
        if (!(CurLine = gtnxtlin()))
        {
            return -1;
        }
        
        if (*CurLine == '#')          /* else L655f */
        {
            _prepcod = CurLine[1];

            if (!(gtnxtlin()))        /* else L64a4 */
            {
                return -1;
            }
                
            switch (_prepcod)     /* at $63BD */
            {
                case '5':                   /* Line # */     /* L63c2 */
                    fileline = a_toi (inpbuf);
                    continue;                       /* L639a */
                case '6':     /* L63d1 */
                    pr2stars ();
                case '2':           /* raw asm */     /* L63d4 */
                    prntstar ();
                    fprintf (outpth, "%s\n", inpbuf);
                    continue;
                case '7':           /* Line ## "filename" */
                    /* L63e4 */
                    strcpy (CurFilNam, inpbuf);
                    prntfnam (CurFilNam);
                     
                    if ( gtnxtlin())
                    {
                        continue;
                    }
                    else
                    {
                        return -1;
                    }
                    
                case 'P':   /* root startup*/     /* L640c */
                    strcpy (temp, inpbuf);

                    if ( !gtnxtlin())
                    {
                        return -1;
                    }

                    prntstar ();
                    fprintf (outpth, " psect %s,0,0,%d,0,0\n",
                                        temp, a_toi (inpbuf)) ;
                    prntstar ();
                    fprintf (outpth, " nam %s\n", temp);
                    continue;
                case '0':     /* L6464 */  /* '0' */
                case '1':     /* L6464 */  /* '1' */
                    strcpy (temp, inpbuf);

                    if ( !gtnxtlin())
                    {
                        return -1;
                    }

                    lno = a_toi(inpbuf);

                    if ( !gtnxtlin())
                    {
                        return -1;
                    }

                    x = a_toi(inpbuf);

                    if ( !gtnxtlin())
                    {
                        return -1;
                    }

                    if (lno)
                    {
                        printf ("%s : line %d ", CurFilNam, lno);
                    }
                    else
                    {
                        printf ("argument : ");
                    }

                    printf ("**** %s ****\n", inpbuf);

                    if (temp[0])
                    {
                        puts (temp);

                        while ( x--)
                        {
                            putc (' ', stdout);
                        }

                        puts ("^");
                    }

                    if (_prepcod == '1')
                    {
                        quitcc ();
                    }

                    continue;
            }
        }
        else
        {
                /* L655f here */
            ++fileline;
            return ' ';
        }
    }
}

#ifndef COCO

int
a_toi (register char *cptr)
#else

int 
a_toi (cptr)
register char *cptr;
#endif
{
    int c_cod;
    int n;

    n = 0;

    while ((_chcodes[(c_cod =*(cptr++))]) == '\x6b')
    {
        n = (n * 10) + (c_cod - '0');
    }

    return n;
}

/* *********************************************************** *
 * gtnxtlin() - reads in the next line from and normalizes it. *
 *      Stores it in data area "inpbuf"                        *
 * Returns: ptr to inpbuf on anything but a true read error.   *
 *          NULL on true read error                            *
 * *********************************************************** */

char *
gtnxtlin ()
{
    int _curch;
    register char *_line = inpbuf;

    if ((_curch = getc (inpth)) == -1)     /* else L660c */
    {
        if (ferror (inpth))
        {
            fputs ("INPUT FILE ERROR : TEMPORARY FILE\n", stderr);
            quitcc ();
        }

        return 0;
    }

    while (_line != D0189)
    {
        switch (_curch)
        {
            case '\n':
            case -1:
                *_line = '\0';
                return inpbuf;
            default:
                *(_line++) = _curch;
                _curch = getc (inpth);
        }
    }

    symline = ++fileline;
    symptr = inpbuf;
    fatal ("input line too long");
}

