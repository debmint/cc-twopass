/* ************************************************************************ *
 * p2_06.c - part 6 for c.pass2                                             *
 *                                                                          *
 * $Id: p2_06.c 18 2008-05-19 21:54:22Z dlb $::                                                                   *
 * ************************************************************************ */

#include "pass2.h"

extern direct int D0023;

static int L31ae (
#ifndef COCO
    unsigned int parm1
#endif
);

static int add512mem (
#ifndef COCO
    unsigned int parm1
#endif
);
#ifdef COCO
char *br_rel_op ();
#endif

/* ************************************************************************ *
 * getmem () - Returns an area of memory.  Program maintains an array of    *
 *          storage areas.  getmem() searches for a block satisfying the    *
 *          requirement passed as a parameter.  If no adequate area is      *
 *          available, will attemt to allocate more.                        *
 * ************************************************************************ */

void *
#ifdef COCO
getmem (siz)
    int siz;
#else
getmem (int siz)
#endif
{
    struct val_data *_lastval;
    unsigned int _qrtrsz;

    register struct val_data *_curntval;

    if (_qrtrsz = L31ae (siz))       /* else L319f */
    {
        if ( ! (_lastval = D004b))  /* Never initialized */    /* else L313e */
        {
            D029a = D004b = _lastval = &D029a;
            D029c = 0;
        }

        _curntval = _lastval->valaddr;   /* Base of value tree */ /* L313e */

        /* Search for an allocated memory area with enough free space */

        for (;;)
        {
#ifndef COCO
            char *chptr;
#endif
            /* L3141 */
            if (_curntval->freemem >= _qrtrsz)  /* Found */ /* else L318a */
            {
                if (_curntval->freemem == _qrtrsz)  /* else L3156 */
                {
                    _lastval->valaddr = _curntval->valaddr;
                }
                else
                {     /* L3156 */
                    _curntval += (_curntval->freemem -= _qrtrsz);
                    _curntval->freemem = _qrtrsz;
                }

                D004b = _lastval;
#ifdef COCO
                _lastval = _curntval;
#else
                chptr = _curntval;
#endif

                /* Null out the applicable area */

                while (siz--)     /* L317a */
                {
#ifdef COCO
                    *((char *)_lastval)++ = 0;  /* L3170 */
#else
                    *(chptr++) = '\0';
#endif
                }

                return _curntval;
            }

            /* If not initialized? */

            if (_curntval == D004b)    /* L318a*/  /* else L31a3 */
            {
                if ( ! (_curntval = add512mem (_qrtrsz)))
                {
                    return 0;
                }
            }

            _lastval = _curntval;  /* L31a3 */
            _curntval = _curntval->valaddr;
        }   /* end for (;;) */
    }
    else
    {
        return 0;
    }
}

/* ************************************************************ *
 * L31ae () - basically returns  (x + 3) / 4                    *
 * ************************************************************ */

static int
#ifdef COCO
L31ae (parm1)
    unsigned int parm1;
#else
L31ae (unsigned int parm1)
#endif
{
    return ((parm1 + 3) >> 2);
}

/* **************************************************************** *
 * add512mem () - Allocates a 512-byte block of memory that will    *
 *          contain the requested size                              *
 * **************************************************************** */

static int
#ifdef COCO
add512mem (parm1)
    unsigned int parm1;
#else
add512mem (unsigned int parm1)
#endif
{
    unsigned int var0;
    register int regptr;

#ifdef COCO
    if ( (regptr = sbrk ((var0 = ((parm1 + 0x7f) >> 7) << 7) * 4)) == -1)
#else
    if ( ! (regptr = malloc (var0 = (((parm1 + 0x7f) >> 7) << 7) * 4)))
#endif
    {
        return 0;
    }

    L3203 (regptr, var0);
    return D004b;
}

/* I believe we need to do some work on getting these variables named right */
void
#ifdef COCO
L3203 (vdat, siz)
    struct val_data *vdat;
    int siz;
#else
L3203 (struct val_data *vdat, int siz)
#endif
{
    struct val_data *var0;
    register struct val_data *ptr;

    if ( ! (ptr = vdat))     /* Nothing to do for request for 0 mem */
    {
        return;
    }

    siz = L31ae (siz);      /* siz = 1/4 siz */

    var0 = D004b;       /* last ptr */

    while ((ptr <= var0) || (ptr >= var0->valaddr))
    {
        if (var0 >= var0->valaddr)
        {
            if ((ptr > var0) || (ptr < var0->valaddr))
            {
                break;
            }
        }

        var0 = var0->valaddr;
    }

    if ((ptr + siz) == var0->valaddr)   /* L323d */     /* else L325f */
    {
        siz += (var0->valaddr)->freemem;
        ptr->valaddr = (var0->valaddr)->valaddr;
    }
    else
    {
        /*((CMDREF *)ptr)->ft_Ty = (*(CMDREF **)var0)->ft_Ty;*/ /* L325f */
        ptr->valaddr = var0->valaddr;
    }

    if (((var0->freemem) + var0) == ptr)
    {
        var0->freemem += siz;
        var0->valaddr = ptr->valaddr;
    }
    else
    {
        var0->valaddr = ptr;
    }

    ptr->freemem = siz;
    D004b = var0;
}

void
#ifdef COCO
L3292 (parm1, parm2, parm3, parm4)
    int parm1;
    int parm2;
    int parm3;
    register CMDREF *parm4;
#else
L3292 (int parm1, int parm2, int parm3, CMDREF *parm4)
        /*  +12        +14        +16          +18 */
#endif
{
    int _reg_name;
    int var4;
    int var2;
    int var0;

    if (parm1 == 136)
    {
        L39d9 (parm2, parm3);
        return;
    }

    if (parm1 == 135)
    {
        L3bc2 (parm2, parm3);
        return;
    }

    switch (parm1)
    {
        case 122:          /* L32cd */
            fprintf (OutPath, " pshs %c\n", get_regname (parm2));
            
            if ((D000d -= INTSIZ) < D0017)
            {
                D0017 = D000d;
            }
            return;
        case 125:          /* L32fa */
            L3292 (129, 113, C_INTSQUOT, parm3);    /* recurse into self */
            parm3 = parm2;
            parm2 = C_EQEQ;
            /* fall through to next */
        case 130:          /* L331d */
            prt_bgnfld ("lb");
            prnt_strng (br_rel_op (parm2));  /* jumping to L3400 */
            L4414 (parm3);          /* jumping to L3785 */
            return;
        case FT_RETURN:           /* L3334 */
            L43d1 ("puls u,pc\n");  /* jumping to L34a1 */
            return;
        case C_AND:
        case C_VBAR:       /* L333b */
        case C_CARET:
            L3ea4 (parm1, parm3, parm4);
            return;
        case C_MULT:       /* L334f */
            L3e51 ("ccmult");
            return;
        case 78:           /* L3355 */
            L3e51 ("ccudiv");
            return;
        case C_SLASH:      /* L335b */
            L3e51 ("ccdiv");
            return;
        case C_LSHIFT:     /* L3361 */
            L3e51 ("ccasl");
            return;
        case C_RSHIFT:     /* L3367 */
            L3e51 ("ccasr");
            return;
        case 77:           /* L336d */
            L3e51 ("cclsr");
            return;
        case 76:           /* L3373 */
            L3e51 ("ccumod");
            return;
        case C_PERCENT:    /* L3379 */
            L3e51 ("ccmod");
            return;
        case C_MINUS:      /* L3385 */
            L43d1 ("nega\n negb\n sbca #0");
            return;
        case C_TILDE:      /* L338c */
            L43d1 ("coma\n comb");
            return;
        case 29:           /* L3393 */
            prt_bgnfld ("leax ");
            prnt_integer (-D000d);
            prnt_strng (D004f);
            L43dc ();
        case 124:          /* L33b9 */
            prt_bgnfld (D0053);
            L4414 (parm2);
            return;
        case 9:            /* L33c8 */
            prt_bgnfld (D0053);
            L4414 (parm3);
            L4414 (parm2);
            prt_bgnfld ("leas ");
            prnt_integer (D000d);
            prnt_strng (",x\n");
            L4414 (parm3);
            return;
        case C_PARENS:     /* L3410 */
            D000f = 4;

            if ( (((CMDREF *)parm3)->vartyp == C_USRLBL) &&
                   ((var4 = ((CMDREF *)parm3)->cmdval)) )   /* else L3445 */
            {
                prt_bgnfld (D0051);
                prt_label (var4 + 4, 0);
                return;
            }

            prt_bgnfld ("jsr ");
            L40d0 (parm2, parm3, 0);
            L43dc ();
            return;
        case C_CHR2INT:    /* L3466 */
            L43d1 ("sex");  /* jumping to L34a1 */
            return;
        case C_LNG2INT:    /* L346c */
            prt_bgnfld ("ld");
            L4085 ('d', parm2, parm3, INTSIZ);
            return;
        case 152:          /* L3491 */
            L43d1 ("aslb\n rola");  /* jumping to L34a1 */
            return;
        case 150:          /* L3497 */
            L43d1 ("asra\n rorb");  /* jumping to L34a1 */
            return;
        case 151:          /* L349d */
            L43d1 ("lsra\n rorb");
            return;
        case C_X_RGWRD:    /* L34a6 */
            prt_bgnfld ("ldy ");
            goto L34c2;
        case C_RGWRD:      /* L34b5 */
            prt_bgnfld ("ldu ");
L34c2:
            prnt_integer (parm2);
            prnt_strng (D004f);
            L43dc ();
            return;
        case 123:          /* L34de */
            prt_bgnfld ("leax ");

            switch (parm2)
            {
                case 119:   /* L34ed */
                    if ((_reg_name = ((CMDREF *)parm3)->vartyp) == 148)
                    {
                        _reg_name = 'y';
                    }
                    else
                    {
                        _reg_name = ((_reg_name == 149) ? 'u' : 'x');
                    }

                    fprintf (OutPath, "%d,%c\n", ((CMDREF *)parm3)->cmdval,
                                                    _reg_name);
                    return;
                case 112:   /* L352a */
                    fprintf (OutPath, "d,%c\n", get_regname (parm3));
                    return;
            }
    }

    _reg_name = get_regname (parm2);

    if (parm3 == 119)       /* else L36a1 */
    {
        if (((CMDREF *)parm4)->vartyp == 133)    /* else L3684 */
        {
            L3292 (parm1, 112, 119, ((CMDREF *)parm4)->cr_Left);

            switch (parm1)
            {
                case 117:          /* L364d */
                    L43d1 ("sex");
                    break;
                case 79:           /* L3653 */
                case C_PLUS:       /* L3653 */
                    L43d1 ("adca #0");
                    break;
                case C_NEG:        /* L3659 */
                    L43d1 ("sbca #0");
                    break;
            }

            parm4->vartyp = 112;
            return;
        }
        else
        {
            if ((parm4->ft_Ty == FT_CHAR) && (parm1 != 127) && (_reg_name != 'x'))
            {
                _reg_name = 'b';
            }
        }
    }

    switch (parm1)  /* L36a1 */
    {
        case 117:          /* L36a6 */
            if (parm3 == 119)       /* else L3765 */
            {
                var0 = parm4->cmdval;
                
                switch (var2 = parm4->vartyp)
                {
                    case 113:          /* L36be */
                    case C_X_RGWRD:    /* L36be */
                    case C_RGWRD:      /* L36be */
                        if (parm2 != 112)
                        {
                            lea_reg (_reg_name);
                            fprintf (OutPath, "%d,%c\n",
                                               var0, get_regname (var2));
                        }
                        else
                        {
                            L39be (get_regname (var2), C_QUESTION);  /* L36e3 */

                            if (var0 != 0)
                            {
                                L3292 (C_PLUS, 112, C_INTSQUOT, var0);
                            }
                        }

                        return;
                    case 112:          /* L3715 */
                        if (parm2 != 112)
                        {
                            L39be (C_QUESTION, _reg_name);
                        }

                        return;
                    case C_DQUOT:      /* L3729 */
                        lea_llblpcr (_reg_name, parm4->cmdval);
                        return;
                    case C_INTSQUOT:   /* L3737 */
                        parm3 = C_INTSQUOT;
                        parm4 = var0;
                        break;
                }
            }

            /* L3765 */
            if ((parm2 == 112) && (parm3 == C_INTSQUOT) && (parm4 == 0))
            {
                L43d1 ("clra\n clrb");
            }
            else
            {
                prt_bgnfld ("ld");
                goto L382a;
            }

            return;
        case 129:          /* L3791 */
            if ((parm3 == C_INTSQUOT) && (parm4 == 0))
            {
                fprintf (OutPath, " st%c -2,s\n", _reg_name);
                return;
            }

            prt_bgnfld ("cmp");

            if (_reg_name == 'b')
            {
                _reg_name = 'd';
            }

            goto L382a;
        case 121:          /* L37d0 */
            if ((parm3 == 119) && (is_regvar (var2 = parm4->vartyp)))
            {
                if (var2 != parm2)
                {
                    L39be (_reg_name, get_regname (var2));
                }

                return;
            }
            else
            {
                prt_bgnfld ("st");
                goto L382a;
            }

        case C_NEG:        /* L380a */
            prt_bgnfld ("sub");
            goto L382a;
        case 79:           /* L3819 */
            L3292 (C_MINUS NUL3);
        case C_PLUS:       /* L3823 */
            prt_bgnfld ("add");
L382a:
            L4085 (_reg_name, parm3, parm4, 0);
            break;
        case 127:          /* L382f */
            if (parm3 == 119)   /* else break */
            {
                switch (var2 = ((LBLDEF *)(parm4->cmdval))->gentyp)
                {
                    case FT_DIRECT:    /* L3843 */
                    case FT_DPXTRN:    /* L3843 */
                    case FT_DPSTATIC:  /* L3843 */
                        lea_reg (_reg_name);
                        prnt_chr (C_INCREMENT);

                        if (var2 == FT_DPSTATIC)
                        {
                            prt_loclbl (((CMDREF *)parm4->cmdval)->__cr4);
                        }
                        else
                        {
                            prt_lblnam (parm4->cmdval + 4);
                        }

                        L40af (parm4->cr_Nxt);
                        prnt_strng (D004d);
                        L43dc ();
                        return;
                }
            }

            prt_bgnfld ("lea");
            L4085 (_reg_name, parm3, parm4, 0);
            break;

        case 115:          /* L38bd */
            fprintf (OutPath, " exg %c,%c\n", _reg_name, get_regname (parm3));
            return;
        case 116:          /* L38dd */
            lea_reg (_reg_name);

            switch (parm3)
            {
                case 112:           /* L38eb */
                    prnt_strng ("d,");
                    goto L390d;
                case C_INTSQUOT:    /* L38fa */
                    prnt_integer (parm4);
                    prnt_chr (C_RBRACE);
L390d:
                    prnt_chr (_reg_name);
                    L43dc ();
                    return;
                default:            /* L391e */
                    L4823 ("LEA arg");
                    return;
            }
        default:           /* L3938 */
            L4823 (D0057);
            return;
    }
}

int
#ifdef COCO
get_regname (parm1)
    int parm1;
#else
get_regname (int parm1)
#endif
{
    switch (parm1)
    {
        case 112:          /* L398d */
            return 'd';
        case 113:          /* L3992 */
            return 'x';
        case C_X_RGWRD:    /* L3997 */
            return 'y';
        case C_RGWRD:      /* L399c */
            return 'u';
        default:           /* L39a1 */
            return ' ';
    }
}

void
#ifdef COCO
L39be (parm1, parm2)
    int parm1;
    int parm2;
#else
L39be (int parm1, int parm2)
#endif
{
    fprintf (OutPath, " tfr %c,%c\n", parm1, parm2);
}

/* ******************************************************************** *
 * L39d9 () - Seems to handle longs                                     *
 * ******************************************************************** */

void
#ifdef COCO
L39d9 (parm1, parm2)
    int parm1;
    int parm2;
#else
L39d9 (int parm1, int parm2)
#endif
{
    switch (parm1)
    {
        case 110:          /* L39e0 */
            L3292 (117, 112, 147, FT_CHAR);
#ifdef COCO
            L3292 (122, 112);
            L3292 (117, 112, 147, 0);
            L3292 (122, 112);
#else
            L3292 (122, 112, 0, 0);
            L3292 (117, 112, 147, 0);
            L3292 (122, 112, 0, 0);
#endif
            break;
        case 139:          /* L3a30 */
            L43d1 ("lda 0,x\n ora 1,x\n ora 2,x\n ora 3,x");
            break;
        case 137:          /* L3a3c */
            L3e6e ("_lmove");
            D000d -= INTSIZ; /* WARNING D000d _may_ be an int * */
            break;
        case C_PLUS:       /* L3a42 */
            L3e6e ("_ladd");
            break;
        case C_NEG:        /* L3a48 */
            L3e6e ("_lsub");
            break;
        case C_MULT:       /* L3a4e */
            L3e6e ("_lmul");
            break;
        case C_SLASH:      /* L3a54 */
            L3e6e ("_ldiv");
            break;
        case C_PERCENT:    /* L3a5a */
            L3e6e ("_lmod");
            break;
        case C_AND:        /* L3a60 */
            L3e6e ("_land");
            break;
        case C_VBAR:       /* L3a66 */
            L3e6e ("_lor");
            break;
        case C_CARET:      /* L3a6c */
            L3e6e ("_lxor");
            break;
        case C_LSHIFT:     /* L3a72 */
            L3e6e ("_lshl");
            D000d -= INTSIZ; /* WARNING D000d _may_ be an int * */
            break;
        case C_RSHIFT:     /* L3a78 */
            L3e6e ("_lshr");
            D000d -= INTSIZ; /* WARNING D000d _may_ be an int * */
            break;
        case C_EQEQ:
        case C_NOTEQ:
        case C_GT_EQ:
        case C_LT_EQ:      /* L3a8b */
        case C_GT:
        case C_LT:
            L3e6e ("_lcmpr");
            break;
        case C_MINUS:      /* L3a97 */
            L3e6e ("_lneg");
            D000d -= LONGSIZ;
            /*L3d90 (parm2, 2);*/
            break;
        case C_TILDE:      /* L3a9d */
            L3e6e ("_lcompl");
            D000d -= LONGSIZ;
            /*L3d90 (parm2, 2);*/
            break;
        case C_I2LNG:      /* L3aa3 */
            L3e6e ("_litol");
            D000d -= LONGSIZ;
            /*L3d90 (parm2, 2);*/
            break;
        case C_U2LNG:      /* L3aa9 */
            L3e6e ("_lutol");
            D000d -= LONGSIZ;
            /*L3d90 (parm2, 2);*/
            break;
        case C_PLUSPLUS:   /* L3aaf */
        case C_INCREMENT:  /* L3aaf */
            L3e6e ("_linc");
            D000d -= LONGSIZ;
            /*L3d90 (parm2, 2);*/
            break;
        case C_MINMINUS:   /* L3ab5 */
        case C_DECREMENT:  /* L3ab5 */
            L3e6e ("_ldec");
            /*L3d90 (parm2, 2);*/
            D000d -= LONGSIZ;
            break;
        case C_LONG:       /* L3ac8 */
            L3d90 (parm2, 2);
            break;
        default:           /* L3ad4 */
            L4823 ("codgen - longs");
            prnt_strng (D0057);
            prnt_integer (parm1);
            L43dc ();
            break;
    }
}

/* ******************************************************************** *
 * L3bc2 () - Seems to handle floats/doubles                            *
 * ******************************************************************** */

void
#ifdef COCO
L3bc2 (parm1, fttyp)
    int parm1;
    register int fttyp;
#else
L3bc2 (int parm1, int fttyp)
#endif
{
    switch (parm1)
    {
        case C_DOUBLE:     /* L3bcb */
            L3d90 (fttyp, DBLSIZ/2);
            break;
        case 110:          /* L3bd9 */
            L3e8d ("_dstack");
            D000d -= DBLSIZ;
            break;
        case 139:          /* L3bec */
            fprintf (OutPath, " lda %c,x\n",
                       ((fttyp == FT_FLOAT) ? '3' : '7'));
            break;
        case 137:          /* L3c0d */
            L3e8d ((fttyp == FT_FLOAT) ? "_fmove" : "_dmove");
            D000d += INTSIZ;    /* jump to L3e65 */
            break;
        case C_PLUS:       /* L3c27 */
            L3e8d ("_dadd");
            D000d += DBLSIZ;
            break;
        case C_NEG:        /* L3c2d */
            L3e8d ("_dsub");
            D000d += DBLSIZ;
            break;
        case C_MULT:       /* L3c33 */
            L3e8d ("_dmul");
            D000d += DBLSIZ;
            break;
        case C_SLASH:      /* L3c39 */
            L3e8d ("_ddiv");
            D000d += DBLSIZ;
            break;
        case C_EQEQ:       /* L3c3f */
        case C_NOTEQ:      /* L3c3f */
        case C_GT_EQ:      /* L3c3f */
        case C_LT_EQ:      /* L3c3f */
        case C_GT:         /* L3c3f */
        case C_LT:         /* L3c3f */
            L3e8d ("_dcmpr");
            D000d += DBLSIZ;
            break;
        case C_MINUS:      /* L3c52 */
            L3e8d ("_dneg");
            break;
        case C_PLUSPLUS:   /* L3c58 */
        case C_INCREMENT:  /* L3c58 */
            L3e8d ((fttyp == FT_FLOAT) ? "_finc" : "_dinc");
            break;
        case C_MINMINUS:   /* L3c6a */
        case C_DECREMENT:  /* L3c6a */
            L3e8d ((fttyp == FT_FLOAT) ? "_fdec" : "_ddec");
            break;
        case C_TOFLOAT:    /* L3c80 */
            L3e8d ("_dtof");
            break;
        case C_FLT2DBL:    /* L3c86 */
            L3e8d ("_ftod");
            break;
        case C_L2DBL:      /* L3c8c */
            L3e8d ("_ltod");
            break;
        case C_I2DBL:      /* L3c92 */
            L3e8d ("_itod");
            break;
        case C_U2DBL:      /* L3c98 */
            L3e8d ("_utod");
            break;
        case C_DBL2LNG:    /* L3c9e */
            L3e8d ("_dtol");
            break;
        case C_DBL2INT:    /* L3ca4 */
            L3e8d ("_dtoi");
            break;
        default:           /* L3cb0 */
            L4823 ("codgen - floats");
            prnt_strng (D0057);
            prnt_integer (parm1);
            L43dc ();
            break;
    }
}

void
#ifdef COCO
L3d90 (fttyp, siz)
    int fttyp;
    int siz;
#else
L3d90 (int fttyp, int siz)
#endif
{
    int _stkcount;

    prt_bgnfld ("bsr ");
    L4414 (_stkcount = ++D000b);
    L3dd0 (fttyp, siz);
    prt_loclbl (_stkcount);
    L43d1 ("puls x");
}

void
#ifdef COCO
L3dd0 (intarray, siz)
    register int *intarray;
    int siz;
#else
L3dd0 (int *intarray, int siz)
#endif
{
    int var0;

    prt_fdb ();

    if ( siz == 1)
    {
        prnt_integer ((int)intarray);
    }
    else
    {
        if (intarray == 0) /* L3deb */     /* else L3e1c */
        {
            var0 = 1;

            while (var0++ < siz)
            {
                prnt_strng ("0,");
            }

            prnt_chr ('0');
        }
        else
        {
            var0 = 0;       /* L3e1c */

            while (var0 < siz)
            {
                prnt_integer (*(intarray++));

                if ((siz - 1) != var0)
                {
                    prnt_chr (',');
                }

                ++var0;
            }
        }
    }

    L43dc ();
}

void
#ifdef COCO
L3e51 (strng)
    char *strng;
#else
L3e51 (char *strng)
#endif
{
    prt_bgnfld (D0051);
    L43d1 (strng);
    D000d += INTSIZ;
}

void
#ifdef COCO
L3e6e (strng)
    char *strng;
#else
L3e6e (char *strng)
#endif
{
    prt_bgnfld (D0051);
    L43d1 (strng);
    D000d += LONGSIZ;
}

void
#ifdef COCO
L3e8d (strng)
    char *strng;
#else
L3e8d (char *strng)
#endif
{
    prt_bgnfld (D0051);
    L43d1 (strng);
}

void
#ifdef COCO
L3ea4 (parm1, parm2, cref)
    register int parm1;
    int parm2;
    CMDREF *cref;
#else
L3ea4 (int parm1, int parm2, CMDREF *cref)
       /*   +10        +12            +14 */
#endif
{
    char *strng;
    int var2 = 0;
    int var0;

    if (parm2 == 119)       /* else L3ed4 */
    {
        var2 = (cref->ft_Ty == FT_CHAR) ? FT_INT : 0;
        parm2 = cref->vartyp;
        /* Need to fix this...  probably with a cast */
        cref = cref->cmdval;
    }

    /*switch (cref->ft_Ty)*/
    switch (parm1)
    {
        case C_AND:        /* L3ed8 */
            strng = "and";
            break;
        case C_VBAR:       /* L3ede */
            strng = "or";
            break;
        case C_CARET:      /* L3ee4 */
            strng = "eor";
            break;
    }

    switch (parm2)
    {
        case C_USRLBL:     /* L3f00 */
        case 148:          /* L3f00 */
        case 149:          /* L3f00 */
        case 147:          /* L3f00 */
            if (var2)
            {
                if (parm1 == C_AND)
                {
                    L43d1 (D0055);
                }

                prt_bgnfld (strng);
                L4085 ('b', parm2, cref, 0);
            }
            else
            {
                prt_bgnfld (strng);       /* L3f22 */
                L4085 ('a', parm2, cref, 0);
                prt_bgnfld (strng);
                L4085 ('b', parm2, cref, 1);
            }

            break;
        case C_INTSQUOT:   /* L3f68 */
            switch (var0 = ((int)cref >> 8) & 0xffff)
            {
                case 0:     /* L3f79 */
                    if (parm1 == C_AND)
                    {
                        L43d1 (D0055);
                    }

                    break;
                case 255:   /* L3f87 */
                    if (parm1 == C_AND)
                    {
                        break;
                    }

                    if (parm1 == C_CARET)
                    {
                        L43d1 ("coma");
                        break;
                    }

                    /* fall through to default */
                default:    /* L3fa0 */
                    prt_bgnfld (strng);       /* L3fa0 */
                    L4085 ('a', C_INTSQUOT, var0, 0);
                    break;
            }

            switch (var0 = ((int)cref & 0xff))        /* L3fcd */
            {
                case 0:     /* L3fd6 */
                    if (parm1 == C_AND)
                    {
                        L43d1 ("clrb");
                    }

                    break;
                case 255:   /* L3fe4 */
                    if (parm1 == C_AND)
                    {
                        break;
                    }

                    if (parm1 == C_CARET)
                    {
                        L43d1 ("comb");
                        break;
                    }

                default:    /* L4000 */
                    prt_bgnfld (strng);
                    L4085 ('b', C_INTSQUOT, var0, 0);
                    break;
            }

            break;
        case 110:          /* L402e */
            fprintf (OutPath, " %sa ,s+\n %sb ,s+\n", strng, strng);
            D000d += INTSIZ;
            break;
        default:           /* L404f */
            L4823 ("compiler trouble");
            break;
    }
}

void
#ifdef COCO
L4085 (ch, parm2, parm3, parm4)
    int ch;
    int parm2;
    int parm3;
    int parm4;
#else
L4085 (int ch, int parm2, int parm3, int parm4)
#endif
{
    prnt_chr (ch);
    prnt_chr (' ');
    L40d0 (parm2, parm3, parm4);
    L43dc ();
}

void
#ifdef COCO
L40af (parm1, parm2, parm3)
    register int parm1;
    int parm2;
    int parm3;
#else
L40af (int parm1)
#endif
{
    if (parm1)
    {
        if (parm1 > 0)
        {
            prnt_chr ('+');
        }

        prnt_integer (parm1);
    }
}

void
#ifdef COCO
L40d0 (parm1, parm2, parm3)
    int parm1;
    int parm2;
    int parm3;
#else
L40d0 (int parm1, int parm2, int parm3)
#endif
{
    int var4;
    int var2;
    struct nwref *L4d0_valu;

    if (parm1 & 0x8000)
    {
        prnt_chr ('[');
    }

    switch (parm1 & 0x7fff)
    {
        register CMDREF *cref;

        case 119:          /* L40ee */
            cref = parm2;

            if (cref->vartyp == C_AMPERSAND)
            {
                prnt_chr ('#');
                L40d0 (119, cref->cr_Left, parm3);
            }
            else
            {
                L40d0 (cref->vartyp, cref->cmdval, parm3 + cref->cr_Nxt);
            }

            return;
        case C_INTSQUOT:   /* L4125 */
            prnt_chr ('#');
            prnt_integer (parm2);
            break;
        case 128:          /* L4134 */
            prnt_strng ("_flacc");
            L40af (parm3);
            prnt_strng (D004d);
            break;
        case C_USRLBL:     /* L4154 */
            if (L4d0_valu = parm2)   /* else L4265 (= break) */
            {
                switch (var2 = L4d0_valu->ftyp)
                {
                    case FT_AUTO:      /* L4165 */
                        prnt_integer (parm2 =
                                L4d0_valu->rfdat.wrd - D000d + parm3);
                        prnt_strng (D004f);
                        break;
                    case FT_DPSTATIC:  /* L417d */
                        if ( ! D0023)
                        {
                            prnt_chr ((parm1 & 0x8000) ? '>' : '<');
                        }

                        /* fall through to next case */
                    case FT_STATIC:    /* L4199 */
                        prt_loclbl (L4d0_valu->rfdat.wrd);
                        goto L41d2;
                    case FT_DIRECT:    /* L41a8 */
                    case FT_DPXTRN:    /* L41a8 */
                        if ( ! D0023)
                        {
                            prnt_chr ((D0023 & 0x8000) ? '>' : '<');
                        }

                        /* fall through to next case */
                    case FT_EXTERN:    /* L41c4 */
                    case FT_LSEEK:     /* L41c4 */
                        prt_lblnam (L4d0_valu->rfdat.st);
L41d2:
                        L40af (parm3);

                        if ( ! (parm1 & 0x8000))
                        {
                            if ((D0023) || (var2 == FT_DIRECT) ||
                                    (var2 == FT_DPXTRN) ||
                                    (var2 == FT_DPSTATIC))
                            {
                                break;
                            }
                        }

                        if (inparentheses (L4d0_valu->nw02))
                        {
                            prnt_strng (",pcr");    /* L4225 */
                        }
                        else
                        {
                            prnt_strng (D004d);
                        }

                        break;
                    default:           /* L422b */
                        L4823 ("storage error");
                        break;
                }
            }       /* end initial "if" */
            else
            {
                prnt_integer (parm3);
            }

            break;
        case 147:          /* L426f */
        case 148:          /* L426f */
        case 149:          /* L426f */
            prnt_integer (parm2 += parm3);
            prnt_chr (',');

            switch (parm1 & 0x7fff)
            {
                case 147:   /* L428e */
                    prnt_chr ('x');
                    break;
                case 148:   /* L4293 */
                    prnt_chr ('y');
                    break;
                case 149:   /* L4298 */
                    prnt_chr ('u');
                    break;
                default:    /* L431a */
                    break;
            }

            break;
        case 110:          /* L42b6 */
            prnt_strng (D004f);
            prnt_strng ("++");
            D000d += INTSIZ;
            break;
        default:           /* L42d5 */
            L4823 ("dereference");
            break;
    }

    if (parm1 & 0x8000)
    {
        prnt_chr (']');
    }
}

char *
#ifdef COCO
br_rel_op (vtype)
    int vtype;
#else
br_rel_op (int vtype)
#endif
{
    switch (vtype)
    {
        default:           /* L4338 */
            L4823 ("rel op");
        case C_EQEQ:       /* L4343 */
            return "eq ";
        case C_NOTEQ:      /* L4349 */
            return "ne ";
        case C_LT_EQ:      /* L434f */
            return "le ";
        case C_LT:         /* L4355 */
            return "lt ";
        case C_GT_EQ:      /* L435b */
            return "ge ";
        case C_GT:         /* L4361 */
            return "gt ";
        case C_U_LTEQ:     /* L4367 */
            return "ls ";
        case C_U_LT:       /* L436d */
            return "lo ";
        case C_U_GTEQ:     /* L4373 */
            return "hs ";
        case C_U_GT:       /* L4379 */
            return "hi ";
    }
}

void
#ifdef COCO
prt_bgnfld (opcod)
    char *opcod;
#else
prt_bgnfld (char *opcod)
#endif
{
    putc (' ', OutPath);
    prnt_strng (opcod);
}

/* ******************************************************************** *
 * L43d1 () - 
 * ******************************************************************** */

void
#ifdef COCO
L43d1 (opcod)
    char *opcod;
#else
L43d1 (char *opcod)
#endif
{
    prt_bgnfld (opcod);
    L43dc ();
}

void
#ifdef COCO
L43dc ()
#else
L43dc (void)
#endif
{
    putc ('\n', OutPath);
}

/* **************************************************** *
 * prnt_chr () - a putchar() function for OutPath        *                 
 * **************************************************** */

void
#ifdef COCO
prnt_chr (ch)
    int ch;
#else
prnt_chr (int ch)
#endif
{
    putc (ch, OutPath);
}

/* **************************************************** *
 * prnt_strng () writes the string provided as a         *
 *              to the output file                      *
 * **************************************************** */

void
#ifdef COCO
prnt_strng (strng)
    char *strng;
#else
prnt_strng (char *strng)
#endif
{
    fprintf (OutPath, strng);
}

/* ************************************************************ *
 * prnt_integer () - writes the integer value passed as a        *
 *              to the output path                              *
 * ************************************************************ */

void
#ifdef COCO
prnt_integer (valu)
    int valu;
#else
prnt_integer (int valu)
#endif
{
    fprintf (OutPath, "%d", valu);
}

void
#ifdef COCO
L4414 (valu)
    int valu;
#else
L4414 (int valu)
#endif
{
    prt_loclbl (valu);
    L43dc ();
}

void
#ifdef COCO
prt_loclbl (valu)
    int valu;
#else
prt_loclbl (int valu)
#endif
{
    prnt_chr ('_');
    prnt_integer (valu);
}

void
#ifdef COCO
prt_lblnam (lblnam)
    char *lblnam;
#else
prt_lblnam (char *lblnam)
#endif
{
    fprintf (OutPath, "%.8s", lblnam);
}

int
#ifdef COCO
prt_rsrvstk (valu)
    int valu;
#else
prt_rsrvstk (int valu)
#endif
{
    int _stksz;

    if (_stksz = valu - D000d)
    {
        prt_bgnfld ("leas ");
        prnt_integer (_stksz);
        prnt_strng (D004f);
        L43dc ();
    }

    return valu;
}

/* **************************************************** *
 * prt_label () - prints a label in the label field     *
 * Passed: (1) - label name string                      *
 *         (2) - isglbl if TRUE, prints : after name    *
 * **************************************************** */

void
#ifdef COCO
prt_label (lblnam, isglbl)
    char *lblnam;
    int isglbl;
#else
prt_label (char *lblnam, int isglbl)
#endif
{
    prt_lblnam (lblnam);

    if (isglbl)
    {
        prnt_chr (':');
    }

    L43dc ();
}

void
#ifdef COCO
lea_reg (reg)
    int reg;
#else
lea_reg (int reg)
#endif
{
    fprintf (OutPath, " lea%c ", reg);
}

void
#ifdef COCO
lea_llblpcr (regnam, lblnum)
    int regnam;
    int lblnum;
#else
lea_llblpcr (int regnam, int lblnum)
#endif
{
    lea_reg (regnam);
    fprintf (OutPath, "%c%d,pcr\n", '_', lblnum);
}
