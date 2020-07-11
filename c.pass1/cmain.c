/* ****************************************************** *
 * pass1_11.c - contains main()                           *
 * ****************************************************** */

/* $Id: p1_11.c 14 2008-04-17 02:41:13Z dlb $ */

/* Cause "pass1.h" to not define variables "extern"*/
#define MAIN

#include "pass1.h"
#include <stdlib.h>
#include <signal.h>
#ifdef unix
#   include <unistd.h>
#endif

int
#ifndef COCO
main (int argc, char **argv)
#else
main (argc, argv)
    int argc;
    char **argv;
#endif
{
    /* Initialization routines */

#ifdef __linux
    signal(2, (__sighandler_t)quitcc);
#else
    intercept (quitcc);
#endif
    mktemp (cstrtmp);
    strcpy (dummynm, "_dummy_");
    tblsetup();
    inpth = stdin;
    outpth = stdout;

    /* Process arguments */

    while (--argc > 0)                  /*  L6b9d */
    {
        register char *argstr;

        if (*(argstr = *(++argv)) == '-')   /* L6aab */    /* else L6b68 */
        {
            while (*(++argstr) != '\0')   /*  L6b5a */
            {
                switch (*argstr)
                {
                    case 'e': /* L6ac6 */
                        edition = 1;
                        break;
                    case 's': /* L6ace */
                        nostkck = 1;
                        break;
                    case 'n': /* L6ad6 */
                        ++modname;
                        break;
                    case 'o': /* L6ae0 */
                        if (*(++argstr) == '=')
                        {
                            if (!(outpth = fopen (++argstr,"w")))
                            {
                                fprintf (stderr, "can't open %s\n", argstr);
                                quit_cc();
                            }
                        }

                        goto L6b64;
                    case 'p': /* L6b15 */
                        doprofil = 1;
                        break;
                    default:
                        fprintf (stderr, "unknown flag : -%c\n", *argstr);
                        quit_cc();
                        break;
                }
            }       /* end while *argv != 0 ( L6b5a ) */

L6b64:
            continue;
        }
        else
        {
            if (!D0072)         /* L6b68 */
            {
                ++D0072;
                if (!(inpth = freopen (*argv, "r", stdin)))
                {
                    fatal ("can't open input file");
                }

                srcfile = *argv;      /* L6b98 */
            }
        }
    }       /* end while argc != 0 */

    initbuf0 ();
    nxt_word ();

    while (sym != -1)
    {
        L3227 ();
    }

    dumpstrings ();

    if (ferror(outpth))
    {
        fatal ("error writing assembly code file");
    }

    fflush (stdout);

    if (ErrCount)
    {
        fprintf ( stderr, "errors in compilation : %d\n", ErrCount);
        quit_cc();
    }
}

void 
quit_cc()
{
    if (srcfile)
    {
        unlink(srcfile);
    }

    exit (1);
}
