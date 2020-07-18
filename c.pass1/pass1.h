/* Generic header file for c.pass1 files */

/* $Id: pass1.h 18 2008-05-19 21:54:22Z dlb $ */

/* Coco does not recognize type "void" */

#ifdef COCO
#define void int
#endif

/* Do this for coco.  Linux allows rereading stdio */
#ifndef GOTSTDIO
#   include <stdio.h>
#endif

#include <string.h>
#include "../defines.h"

/* Include "proto.h" after all structs have been declared */

#ifdef COCO
#   include "protoc.h"
#else
#   include "proto.h"
#endif

#ifdef MAIN
#   define GLOBAL
#else
#   define GLOBAL extern
#endif

/* The following were Direct Page variables */

GLOBAL direct int stringlen;
GLOBAL direct symnode *freesym;
GLOBAL direct FILE *strsFP;
GLOBAL direct int  D001d;
GLOBAL direct char *srcfile;
GLOBAL direct int  edition;
GLOBAL direct FILE *inpth,
                   *outpth;
GLOBAL direct int fileline,
                  ErrCount;
GLOBAL direct int LblNum;
GLOBAL direct expnode *freenode;
GLOBAL direct int sp;
GLOBAL direct int stlev;
GLOBAL direct int D0033;
GLOBAL direct int nostkck;
GLOBAL direct int doprofil;
GLOBAL direct char *modname;
GLOBAL direct int maxpush;
GLOBAL direct int D003d;
GLOBAL direct int symline;
GLOBAL direct int Struct_Union;
GLOBAL direct symnode *G18Current;
GLOBAL direct casnode *freecase;
GLOBAL direct symnode *arglist;
GLOBAL direct symnode *labelist;
GLOBAL direct symnode *vlist;
GLOBAL direct int ftype;
GLOBAL direct int lastst;
GLOBAL direct int blklev;
GLOBAL direct int D0053;
GLOBAL direct int contptr;
GLOBAL direct int swflag;       /* D0057 */
GLOBAL direct casnode *caseptr;
GLOBAL direct casnode *lastcase;
GLOBAL direct int notusd5d;
GLOBAL direct int sym;
GLOBAL direct int symval;
GLOBAL direct char *symptr;
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

GLOBAL int deflabel;
GLOBAL int D02d6;
GLOBAL int D02d8;
GLOBAL char D02da[10];
GLOBAL char D02e4[10];
GLOBAL char temp[256],
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

GLOBAL symnode
sdummy
#ifdef MAIN
= {
    1,2,0,0,12,0,0,0,0,0,
    {'\0','\0','\0','\0','\0','\0','\0','\0'}
}
#endif
;

GLOBAL char *
dummynm
#ifdef MAIN
= sdummy.sname
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
