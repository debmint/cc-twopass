
#ifdef MAIN
#   define GLOBAL
#else
#   define GLOBAL extern
#endif

#ifdef COCO
#   define void int
#   define getword(p) getw(p)
#else
#   define direct
#endif

/* coco calls gen with variable # of parameters,
 * define padding for gcc
 */
#ifdef COCO
#define NUL1
#define NUL2
#define NUL3
#else
#   define NUL1 , 0
#   define NUL2 , 0, 0
#   define NUL3 , 0, 0, 0
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../defines.h"

struct val_data
{
    struct val_data *valaddr;
    int freemem;
};

#ifdef COCO
#   include "protoc.h"
#else
#   include "proto.h"
#endif

GLOBAL direct int D0001
#ifdef MAIN
= 0
#endif
;
GLOBAL direct FILE *InPath,
                   *OutPath;
GLOBAL direct int D0007;
GLOBAL direct int errcount;
GLOBAL direct int D000b;
GLOBAL direct int sp;
GLOBAL direct int callflag;
GLOBAL direct int NoStkChk,
                  DoProfile;
GLOBAL direct int D0015;
GLOBAL direct int maxpush;
GLOBAL direct int shiftflag;
/*GLOBAL direct int D001b;*/ /* provided by "printf.c", I think */

GLOBAL int dpsz[]
#ifdef MAIN
= {
    0x0002, 0x0004, 0x0008, 0x0010,
    0x0020, 0x0040, 0x0080, 0x0100,
    0x0200, 0x0400, 0x0800, 0x1000,
    0x2000, 0x4000
}
#endif
;

GLOBAL int TenMults[]
#ifdef MAIN
= {10000, 1000, 100, 10}
#endif
;

GLOBAL int D004b
#ifdef MAIN
= 0
#endif
;

GLOBAL int D004d
#ifdef MAIN
= ",y"
#endif
;

GLOBAL int spind
#ifdef MAIN
= ",s"
#endif
;
GLOBAL int lbsr
#ifdef MAIN
= "lbsr "
#endif
;
GLOBAL int lbra
#ifdef MAIN
= "lbra "
#endif
;
GLOBAL int D0055
#ifdef MAIN
= "clra"
#endif
;
GLOBAL int unkopr
#ifdef MAIN
= "unknown operator : "
#endif
;

GLOBAL char SrcFilNam[30],
            *D0280;
GLOBAL CMDREF *D0282;     /* This _may_ be a struct * of some sort */
GLOBAL char *InFileName,
            D0286[10],
            D0290[10];
GLOBAL struct lng_something *D029a,
                            *D029c,
                            D029e[10];
GLOBAL int D02da;
GLOBAL int D02dc;
GLOBAL FILE *D02de;
GLOBAL int scount;

