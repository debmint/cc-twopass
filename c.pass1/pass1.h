/* Generic header file for c.pass1 files */

/* $Id: pass1.h 18 2008-05-19 21:54:22Z dlb $ */

/* Coco does not recognize type "void" */

#ifdef COCO
typedef int void;
#endif

/* Do this for coco.  Linux allows rereading stdio */
#ifndef GOTSTDIO
#   include <stdio.h>
#endif

#include <string.h>
#include "../defines.h"

#ifdef MAIN
#   define GLOBAL
#else
#   define GLOBAL extern
#endif

#ifndef COCO
#   ifndef direct
#       define direct
#   endif
#   ifndef register
#       define register
#   endif
#endif

#ifdef COCO
#   define putword(w,f) putw (w,f)
#else
#   define putword(w,f) putc ((w >> 8) & 0xff, f); putc (w & 0xff, f)
#endif


/* Include "proto.h" after all structs have been declared */

#ifdef COCO
#   include "protoc.h"
#else
#   include "proto.h"
#endif

/* The following were Direct Page variables */

GLOBAL direct char *D0017;
GLOBAL direct symnode *D0019;
GLOBAL direct FILE *strsFP;
GLOBAL direct int  D001d;
GLOBAL direct char *srcfile;
GLOBAL direct int  edition;
GLOBAL direct FILE *inpth,
                   *outpth;
GLOBAL direct int fileline,
                  ErrCount;
GLOBAL direct int LblNum;
GLOBAL direct expnode *D002d;
GLOBAL direct int D002f;
GLOBAL direct int D0031;
GLOBAL direct int D0033;
GLOBAL direct int nostkck;
GLOBAL direct int doprofil;
GLOBAL direct char *modname;
GLOBAL direct int D003b;
GLOBAL direct int D003d;
GLOBAL direct int D003f;
GLOBAL direct int Struct_Union;
GLOBAL direct symnode *G18Current;
GLOBAL direct int D0045;
GLOBAL direct symnode *D0047;
GLOBAL direct symnode *D0049;
GLOBAL direct symnode *D004b;
GLOBAL direct int D004d;
GLOBAL direct int D004f;
GLOBAL direct int D0051;
GLOBAL direct int D0053;
GLOBAL direct int D0055;
GLOBAL direct int D0057;
GLOBAL direct int CaseList;
GLOBAL direct struct case_ref *CaseNow;
GLOBAL direct int notusd5d;
GLOBAL direct int sym;
GLOBAL direct int LblVal;
GLOBAL direct char *D0063;
GLOBAL direct char CurChr;
GLOBAL direct symnode *LblPtrLow;
GLOBAL direct symnode *LblPtrEnd;
GLOBAL direct char *CurLine;
GLOBAL direct FILE *stmpFP;
GLOBAL direct long not_used;    /* Something not used ??? */
GLOBAL direct int D0072;
GLOBAL direct int D0074;        /* Not used either, AFAIK */

/* The following were non-dp variables */

GLOBAL char _chcod_2[]
#ifdef MAIN
= {
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x09,0x00,0x00,
    0x00,0x0d,0x0e,0x00,0x00,0x00,
    0x0e,0x0c,0x01,0x0e,0x0f,0x0d,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x03,0x00,
    0x0a,0x02,0x0a,0x03,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x07,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x06,0x00,
    0x0e,0x00
}
#endif
;

GLOBAL int D02d4;
GLOBAL int D02d6;
GLOBAL int D02d8;
GLOBAL char D02da[10];
GLOBAL char D02e4[10];
GLOBAL char D02ee[256],
            CurFilNam[30];
GLOBAL symnode *NStrLbls[128],
              *StrctLbls[128];
GLOBAL char inpbuf[256],
            prevlin[256];

GLOBAL char *
D0189
#ifdef MAIN
= &inpbuf[sizeof (inpbuf) - 1]
#endif
;

GLOBAL char
D018b[]
#ifdef MAIN
= {
    0,1,0,2,0,0,0,0,0,12,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0
}
#endif
;

GLOBAL char *
dummynm
#ifdef MAIN
= &(D018b[20])
#endif
;

GLOBAL char cstrtmp[]
#ifdef MAIN
#ifdef COCO
= "cstr.XXXXX"
#else
= "cstr.XXXXXX"
#endif
#endif
;
