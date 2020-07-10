/* ******************************************** *
 * This is a custom printf routine for c.pass1  *
 *                                              *
 * It follows part 7 in the linkage             *
 * ******************************************** */

/* $Id: printf.c 14 2008-04-17 02:41:13Z dlb $ */
 
#ifndef COCO
#   ifndef direct
#       define direct
#   endif
#endif

#include <stdio.h>
#define GOTSTDIO    /* so we won't repeat reading stdio.h in "pass1.h" */

union mptr {
    FILE *FI;
    char *CR;
};

direct union mptr D000f;

direct int   LJust,     /* D0011 */
             FillChar,  /* D0013 */
             DestFlg;   /* D0015 */

/* We could move the definition for TenMults here except that it would
 * rearrange the order of the variables from the original source */

extern direct int *D0001;  /* d0001 */
extern int TenMults[];      /* D0081 */
extern char _chcodes[];

#include "pass1.h"

int
#ifndef COCO
_printf (char *fmt, int vals)
#else
printf (fmt, vals)
char *fmt;
int vals;
#endif
{
    D000f.FI = stdout;
    DestFlg = 1;
    L511b (fmt, &vals);
}

int
#ifndef COCO

_fprintf (FILE *fp, char *fmt, int vals)
#else
fprintf (fp, fmt, vals)
FILE *fp;
char *fmt;
int vals;
#endif
{
    D000f.FI = fp;
    DestFlg = 1;
    L511b (fmt, &vals);
}

int
#ifndef COCO

_sprintf (char *fp, char *fmt, int vals)
#else
sprintf (fp, fmt, vals)
char *fp;
char *fmt;
int vals;
#endif
{
    D000f.CR = fp;
    DestFlg = 2;      /* Flag that D000f is char * rather than CRLE * */
    L511b (fmt, &vals);
    *(D000f.CR) = '\0';
}

/* *********************************** *
 * Generic output routine...           *
 * Passed:  fmt   format string        *
 *          __vals ptr to first value  *
 * *********************************** */

#ifndef COCO

void
L511b (register char *fmt, int *_vals)
#else

void 
L511b (fmt, _vals)
register char *fmt;
int *_vals;
#endif
{
    /* 11 bytes local variables */

    char *_strng;
    char curchr;
    int _fldwdth;
    int _havedec;
    int _decwdth;
    int v0;

    /* Loop to process a single "%" (or entire string if none */

    for (;;)
    {
        /* Print chars directly till we come to a "%" */

        while ((curchr = *(fmt++)) != '%')
        {
            if (curchr == '\0')
            {
                return;
            }

            sendchar (curchr);
        }

        curchr = *(fmt++);
        _fldwdth = _decwdth = 0;

        if (curchr == '-')
        {
            LJust = 1;
            curchr = *(fmt++);
        }
        else
        {
            LJust = 0;
        }

        if (curchr == '0')
        {
            FillChar = '0';
        }
        else
        {
            FillChar = ' ';
        }

        /* Get field width */

        while (_chcodes[curchr] == 0x6b)
        {
            _fldwdth = (_fldwdth * 10) + (curchr - '0');
            curchr = *(fmt++);
        }

        /* Get decimal width if any */

        if (curchr == '.')
        {
            _havedec = 1;
            curchr = *(fmt++);

            while (_chcodes[curchr] == 0x6b)
            {
                _decwdth = (_decwdth * 10) + (curchr - '0');
                curchr = *(fmt++);
            }
        }
        else
        {
            _havedec = 0;
        }

        switch (curchr)
        {
            case 'd': /* L51d9 */
                outputfld (_dec2str (*(_vals++)), _fldwdth);
                break;
            case 'x': /* L51ee */
                outputfld (_hex2str (*(_vals++)), _fldwdth);
                break;
            case 'c': /* L5206 */
                sendchar (*(_vals++));
                break;
            case 's': /* L5213 */
                _strng = (char *)(*(_vals++));

                if (_havedec)     /* else L5256 */
                {
                    _havedec = (int)_strng; /* use "_havedec" as ptr to base */

                    while (_decwdth--)        /* L5335 */
                    {
                        if (*_strng == '\0')     /* L5229 */
                        {
                            break;
                        }

                        ++_strng;
                    }
                    
                    L5415 ((char *)_havedec, ((int)_strng - _havedec), _fldwdth);  /* L5241 */
                }
                else
                {
                    outputfld (_strng, _fldwdth);     /* L5256 */
                }

                break;
            default:        /* L5266 */
                sendchar (curchr);
                break;
        }
    }
}

/* **************************************************** *
 * _dec2str () - Process a string of decimal values     *
 * **************************************************** */

#ifndef COCO

char *
_dec2str (int _nmbr)
#else

char *
_dec2str (_nmbr)
int _nmbr;
#endif
{
    char *myptr = D02da;

    if (_nmbr < 0)     /* else L52ca */
    {
        if ((_nmbr = -_nmbr) < 0)       /* _dec2str  else L52bf */
        {
            return (strcpy (D02da, "-32768"));   /* goto L546c */
        }
        else
        {
            *(myptr++) = '-';
        }
    }

    todigit (myptr, _nmbr);
    return D02da;
}
  
/* ************************************************************ *
 * todigit () - Actually do the conversion for decimal values   *
 *          Works on string "str" passed as the first parameter *
 * ************************************************************ */

#ifndef COCO

void
todigit (char *str, int valu)
#else

void 
todigit (str, valu)
char *str;
int valu;
#endif
{

    int *__tens;
    int _havdigits;
    int _placeval;
    register char *_dststr = str;

    _havdigits = 0;
    _placeval = 0;

    /* If it's negative... */

    while ((valu) < 0)
    {
        ++_placeval;
        valu -= *TenMults;
    }

    __tens = TenMults;

    /* Recursively subtract powers of ten to get the
     * respective digit places
     */

    while (__tens != D0001)     /* until end of data list */    /* L533e */
    {
        while ((valu -= *__tens) >= 0)    /* L530f */
        {
            ++_placeval;       /* L5308 */
        }

        /* The preceding resulted in either a neg # or 0 */
        /* Actually.. should "valu" be incremented if __tens = 0?? */

        valu += *__tens;

        /* This is to signify that a value has been established
         * .. to prevent outputting of leading zeros (when not wanted )
         */

        if (_placeval)
        {
            _havdigits = 1;
        }

        if (_havdigits)         /*L5328 */
        {
            *(_dststr++) = _placeval + '0';
        }

        _placeval = 0;
        ++__tens;
    }

    /* One's place was not output in the above loop.  What we have
     * in "valu" at this point is the remainder from divide by 10
     */

    *(_dststr++) = valu + '0';
    *_dststr = '\0';              /* Terminating NULL */
    
#ifdef COCO     /* This isn't used... */
    return str;
#endif
}

/* ***************************************************** *
 * _hex2str () - Do hexadecimal output                   *
 * ***************************************************** */

#ifndef COCO

char *
_hex2str (unsigned int _nbr)
#else

char *
_hex2str (_nbr)
unsigned int _nbr;
#endif
{
    char *_finalstr = D02da;
    int v0;

    register char *regptr = D02e4;

    do
    {
        *(regptr++) = (v0 = _nbr & 0x0f) + ((v0 > 9) ? 'W' : '0');
    } while ((_nbr = ((_nbr >> 4) & 0x0fff)));

    while ((--regptr) >= D02e4)
    {
        *(_finalstr++) = *regptr;      /* L5391 */
    }

    *_finalstr = '\0';
    return D02da;
}

/* ***************************************************** *
 * outputfld () - output a field                         *
 *            after it has been processed                *
 * Passed: strng:    the string that is to be output     *
 *         fld_wdth: the width of the field              *
 * ***************************************************** */

#ifndef COCO

void
outputfld (char *strng, register int fld_wdth)
#else

void 
outputfld (strng, fld_wdth)
char *strng;
register int fld_wdth;
#endif
{
    int __chr;

    fld_wdth -= (strlen (strng));

    if (LJust == 0)
    {
        while (fld_wdth-- > 0)
        {
            sendchar (FillChar);
        }
    }
    
    while ( (__chr = *(strng++)) )
    {
        sendchar (__chr);
    }

    if (LJust)      /* else L546c */
    {
        while ((fld_wdth--) > 0)
        {
            sendchar (FillChar);
        }               /* go to L546c */
    }
}

/* ***************************************************** *
 * L5415 () - String field if max length has been        *
 *            specified.                                 *
 * Passed: strng:    the string that is to be output     *
 *         str_lngth: the length of the string           *
 *         fldwdth: the width of the field               *
 * ***************************************************** */

#ifndef COCO

void
L5415 (register char *regpt, int str_lngth, int __fldwdth)
#else

void 
L5415 (regpt, str_lngth, __fldwdth)
register char *regpt;
int str_lngth;
int __fldwdth;
#endif
{
    int _fil_lngth;

    _fil_lngth = __fldwdth - str_lngth;

    /* If right Justified, fill at begin */

    if (LJust == 0)     /* else L5446 */
    {
        while (_fil_lngth-- > 0)
        {
            sendchar (FillChar);       /* L5427 */
        }
    }

    /* Now send the string */

    while (str_lngth--)            /* L5446 */
    {
        sendchar (*(regpt++));      /* L543d */
    }

    /* Pad at end if Left justified */

    if (LJust)      /* else L546c */
    {

        while ((_fil_lngth--) > 0)
        {
            sendchar (FillChar);
        }
    }
}

#ifndef COCO

void
sendchar (int p1)
#else

void 
sendchar (p1)
int p1;
#endif
{
    if (DestFlg == 2)
    {
        *(D000f.CR++) = p1;
    }
    else
    {
        putc (p1, D000f.FI);
    }
}

