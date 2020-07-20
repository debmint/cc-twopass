/* ************************************************************************ *
 * codgen.c - part 6 for c.pass2                                            *
 *                                                                          *
 * $Id: p2_06.c 18 2008-05-19 21:54:22Z dlb $::                             *
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
static void transfer ();
#else
static void transfer (int parm1, int parm2);
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
 * L31ae () - basically returns  (x + 3) / 4  (mod(4)???        *
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

    var0 = ((parm1 + 0x7f) >> 7) << 7;
#ifdef COCO
    if ( (regptr = sbrk (var0 *= 4)) == -1)
#else
    if ( ! (regptr = sbrk (var0 *= 4)))
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
gen (op, rtype, arg, val)
    register expnode *val;
    int op, rtype, arg;
#else
gen (int op, int rtype, int arg, expnode *val)
        /*  +12        +14        +16          +18 */
#endif
{
    int reg;
    expnode *ptr;
    int temp, value;

    if (op == LONGOP)
    {
        L39d9 (rtype, arg);
        return;
    }

    if (op == DBLOP)
    {
        L3bc2 (rtype, arg);
        return;
    }

    switch (op)
    {
        case PUSH:          /* L32cd */
            fprintf (OutPath, " pshs %c\n", get_regname (rtype));
            
            if ((sp -= INTSIZ) < D0017)
            {
                D0017 = sp;
            }
            return;
        case JMPEQ:          /* L32fa */
            gen (COMPARE, XREG, CONST, arg);    /* recurse into self */
            arg = rtype;
            rtype = EQ;
            /* fall through to next */
        case CNDJMP:          /* L331d */
            ot ("lb");
            prnt_strng (br_rel_op (rtype));  /* jumping to L3400 */
            L4414 (arg);          /* jumping to L3785 */
            return;
        case RETURN:           /* L3334 */
            L43d1 ("puls u,pc\n");  /* jumping to L34a1 */
            return;
        case AND:
        case OR:       /* L333b */
        case XOR:
            L3ea4 (op, arg, val);
            return;
        case TIMES:       /* L334f */
            L3e51 ("ccmult");
            return;
        case UDIV:           /* L3355 */
            L3e51 ("ccudiv");
            return;
        case DIV:      /* L335b */
            L3e51 ("ccdiv");
            return;
        case SHL:     /* L3361 */
            L3e51 ("ccasl");
            return;
        case SHR:     /* L3367 */
            L3e51 ("ccasr");
            return;
        case USHR:           /* L336d */
            L3e51 ("cclsr");
            return;
        case UMOD:           /* L3373 */
            L3e51 ("ccumod");
            return;
        case MOD:    /* L3379 */
            L3e51 ("ccmod");
            return;
        case NEG:      /* L3385 */
            L43d1 ("nega\n negb\n sbca #0");
            return;
        case COMPL:      /* L338c */
            L43d1 ("coma\n comb");
            return;
        case GOTO:           /* L3393 */
            ot ("leax ");
            od (-sp);
            prnt_strng (spind);
            newln ();
        case JMP:          /* L33b9 */
            ot (D0053);
            L4414 (rtype);
            return;
        case LABEL:            /* L33c8 */
            ot (D0053);
            L4414 (arg);
            L4414 (rtype);
            ot ("leas ");
            od (sp);
            prnt_strng (",x\n");
            L4414 (arg);
            return;
        case CALL:     /* L3410 */
            D000f = 4;

            if ( (((expnode *)arg)->op == NAME) &&
                   ((ptr = ((expnode *)arg)->val.sp)) )   /* else L3445 */
            {
                ot (D0051);
                prt_label (&ptr->dimptr, 0);
                return;
            }

            ot ("jsr ");
            L40d0 (rtype, arg, 0);
            newln ();
            return;
        case CTOI:    /* L3466 */
            L43d1 ("sex");  /* jumping to L34a1 */
            return;
        case LTOI:    /* L346c */
            ot ("ld");
            doref ('d', rtype, arg, INTSIZ);
            return;
        case IDOUBLE:          /* L3491 */
            L43d1 ("aslb\n rola");  /* jumping to L34a1 */
            return;
        case HALVE:          /* L3497 */
            L43d1 ("asra\n rorb");  /* jumping to L34a1 */
            return;
        case UHALVE:          /* L349d */
            L43d1 ("lsra\n rorb");
            return;
        case YREG:    /* L34a6 */
            ot ("ldy ");
            goto dooff;
        case UREG:      /* L34b5 */
            ot ("ldu ");
dooff:
            od (rtype);
            prnt_strng (spind);
            newln ();
            return;
        case LEAX:          /* L34de */
            ot ("leax ");

            switch (rtype)
            {
                case NODE:   /* L34ed */
                    if ((reg = ((expnode *)arg)->op) == YIND)
                    {
                        reg = 'y';
                    }
                    else
                    {
                        reg = ((reg == UIND) ? 'u' : 'x');
                    }

                    fprintf (OutPath, "%d,%c\n", ((expnode *)arg)->val.num,
                                                    reg);
                    return;
                case DREG:   /* L352a */
                    fprintf (OutPath, "d,%c\n", get_regname (arg));
                    return;
            }
    }

    reg = get_regname (rtype);

    if (arg == NODE)       /* else L36a1 */
    {
        if (val->op == CTOI)    /* else L3684 */
        {
            gen (op, DREG, NODE, val->left);

            switch (op)
            {
                case LOAD:          /* L364d */
                    L43d1 ("sex");
                    break;
                case RSUB:           /* L3653 */
                case PLUS:       /* L3653 */
                    L43d1 ("adca #0");
                    break;
                case MINUS:        /* L3659 */
                    L43d1 ("sbca #0");
                    break;
            }

            val->op = DREG;
            return;
        }
        else
        {
            if ((val->type == CHAR) && (op != LOADIM) && (reg != 'x'))
            {
                reg = 'b';
            }
        }
    }

    switch (op)  /* L36a1 */
    {
        case LOAD:          /* L36a6 */
            if (arg == NODE)       /* else L3765 */
            {
                value = val->val.num;
                
                switch (temp = val->op)
                {
                    case XREG:          /* L36be */
                    case YREG:    /* L36be */
                    case UREG:      /* L36be */
                        if (rtype != DREG)
                        {
                            lea_reg (reg);
                            fprintf (OutPath, "%d,%c\n",
                                               value, get_regname (temp));
                        }
                        else
                        {
                            transfer (get_regname (temp), QUERY);  /* L36e3 */

                            if (value != 0)
                            {
                                gen (PLUS, DREG, CONST, value);
                            }
                        }

                        return;
                    case DREG:          /* L3715 */
                        if (rtype != DREG)
                        {
                            transfer ('d', reg);
                        }

                        return;
                    case STRING:      /* L3729 */
                        outstr (reg, val->val.num);
                        return;
                    case CONST:   /* L3737 */
                        arg = CONST;
                        val = (expnode *)value;
                        break;
                }
            }

            /* L3765 */
            if ((rtype == DREG) && (arg == CONST) && (val == 0))
            {
                L43d1 ("clra\n clrb");
            }
            else
            {
                ot ("ld");
                goto L382a;
            }

            return;
        case COMPARE:          /* L3791 */
            if ((arg == CONST) && (val == 0))
            {
                fprintf (OutPath, " st%c -2,s\n", reg);
                return;
            }

            ot ("cmp");

            if (reg == 'b')
            {
                reg = 'd';
            }

            goto L382a;
        case STORE:          /* L37d0 */
            if ((arg == NODE) && (is_regvar (temp = val->op)))
            {
                if (temp != rtype)
                {
                    transfer (reg, get_regname (temp));
                }

                return;
            }
            else
            {
                ot ("st");
                goto L382a;
            }

        case MINUS:        /* L380a */
            ot ("sub");
            goto L382a;
        case RSUB:           /* L3819 */
            gen (NEG NUL3);
        case PLUS:       /* L3823 */
            ot ("add");
L382a:
            doref (reg, arg, val, 0);
            break;
        case LOADIM:          /* L382f */
            if (arg == NODE)   /* else break */
            {
                switch (temp = val->val.sp->storage)
                {
                    case DIRECT:    /* L3843 */
                    case EXTERND:    /* L3843 */
                    case STATICD:  /* L3843 */
                        lea_reg (reg);
                        prnt_chr (INCAFT);

                        if (temp == STATICD)
                        {
                            prt_loclbl (val->val.sp->offset);
                        }
                        else
                        {
                            prt_lblnam (val->val.sp + 4);
                        }

                        addoff (val->modifier);
                        prnt_strng (D004d);
                        newln ();
                        return;
                }
            }

            ot ("lea");
            doref (reg, arg, val, 0);
            break;

        case EXG:          /* L38bd */
            fprintf (OutPath, " exg %c,%c\n", reg, get_regname (arg));
            return;
        case LEA:          /* L38dd */
            lea_reg (reg);

            switch (arg)
            {
                case DREG:           /* L38eb */
                    prnt_strng ("d,");
                    goto L390d;
                case CONST:    /* L38fa */
                    od (val);
                    prnt_chr (',');
L390d:
                    prnt_chr (reg);
                    newln ();
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
        case DREG:          /* L398d */
            return 'd';
        case XREG:          /* L3992 */
            return 'x';
        case YREG:    /* L3997 */
            return 'y';
        case UREG:      /* L399c */
            return 'u';
        default:           /* L39a1 */
            return ' ';
    }
}

static void
#ifdef COCO
transfer (parm1, parm2)
    int parm1;
    int parm2;
#else
transfer (int parm1, int parm2)
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
            gen (117, 112, 147, CHAR);
#ifdef COCO
            gen (122, 112);
            gen (117, 112, 147, 0);
            gen (122, 112);
#else
            gen (122, 112, 0, 0);
            gen (117, 112, 147, 0);
            gen (122, 112, 0, 0);
#endif
            break;
        case 139:          /* L3a30 */
            L43d1 ("lda 0,x\n ora 1,x\n ora 2,x\n ora 3,x");
            break;
        case 137:          /* L3a3c */
            L3e6e ("_lmove");
            sp -= INTSIZ; /* WARNING sp _may_ be an int * */
            break;
        case PLUS:       /* L3a42 */
            L3e6e ("_ladd");
            break;
        case MINUS:        /* L3a48 */
            L3e6e ("_lsub");
            break;
        case TIMES:       /* L3a4e */
            L3e6e ("_lmul");
            break;
        case DIV:      /* L3a54 */
            L3e6e ("_ldiv");
            break;
        case MOD:    /* L3a5a */
            L3e6e ("_lmod");
            break;
        case AND:        /* L3a60 */
            L3e6e ("_land");
            break;
        case OR:       /* L3a66 */
            L3e6e ("_lor");
            break;
        case XOR:      /* L3a6c */
            L3e6e ("_lxor");
            break;
        case SHL:     /* L3a72 */
            L3e6e ("_lshl");
            sp -= INTSIZ; /* WARNING sp _may_ be an int * */
            break;
        case SHR:     /* L3a78 */
            L3e6e ("_lshr");
            sp -= INTSIZ; /* WARNING sp _may_ be an int * */
            break;
        case EQ:
        case NEQ:
        case GEQ:
        case LEQ:      /* L3a8b */
        case GT:
        case LT:
            L3e6e ("_lcmpr");
            break;
        case NEG:      /* L3a97 */
            L3e6e ("_lneg");
            sp -= LONGSIZ;
            /*L3d90 (parm2, 2);*/
            break;
        case COMPL:      /* L3a9d */
            L3e6e ("_lcompl");
            sp -= LONGSIZ;
            /*L3d90 (parm2, 2);*/
            break;
        case ITOL:      /* L3aa3 */
            L3e6e ("_litol");
            sp -= LONGSIZ;
            /*L3d90 (parm2, 2);*/
            break;
        case UTOL:      /* L3aa9 */
            L3e6e ("_lutol");
            sp -= LONGSIZ;
            /*L3d90 (parm2, 2);*/
            break;
        case INCBEF:    /* L3aaf */
        case INCAFT:    /* L3aaf */
            L3e6e ("_linc");
            sp -= LONGSIZ;
            /*L3d90 (parm2, 2);*/
            break;
        case DECBEF:   /* L3ab5 */
        case DECAFT:  /* L3ab5 */
            L3e6e ("_ldec");
            /*L3d90 (parm2, 2);*/
            sp -= LONGSIZ;
            break;
        case LCONST:       /* L3ac8 */
            L3d90 (parm2, 2);
            break;
        default:           /* L3ad4 */
            L4823 ("codgen - longs");
            prnt_strng (D0057);
            od (parm1);
            newln ();
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
        case FCONST:     /* L3bcb */
            L3d90 (fttyp, DBLSIZ/2);
            break;
        case STACK:          /* L3bd9 */
            L3e8d ("_dstack");
            sp -= DBLSIZ;
            break;
        case TEST:          /* L3bec */
            fprintf (OutPath, " lda %c,x\n",
                       ((fttyp == FLOAT) ? '3' : '7'));
            break;
        case MOVE:          /* L3c0d */
            L3e8d ((fttyp == FLOAT) ? "_fmove" : "_dmove");
            sp += INTSIZ;    /* jump to L3e65 */
            break;
        case PLUS:       /* L3c27 */
            L3e8d ("_dadd");
            sp += DBLSIZ;
            break;
        case MINUS:        /* L3c2d */
            L3e8d ("_dsub");
            sp += DBLSIZ;
            break;
        case TIMES:       /* L3c33 */
            L3e8d ("_dmul");
            sp += DBLSIZ;
            break;
        case DIV:      /* L3c39 */
            L3e8d ("_ddiv");
            sp += DBLSIZ;
            break;
        case EQ:       /* L3c3f */
        case NEQ:      /* L3c3f */
        case GEQ:      /* L3c3f */
        case LEQ:      /* L3c3f */
        case GT:         /* L3c3f */
        case LT:         /* L3c3f */
            L3e8d ("_dcmpr");
            sp += DBLSIZ;
            break;
        case NEG:      /* L3c52 */
            L3e8d ("_dneg");
            break;
        case INCBEF:   /* L3c58 */
        case INCAFT:  /* L3c58 */
            L3e8d ((fttyp == FLOAT) ? "_finc" : "_dinc");
            break;
        case DECBEF:   /* L3c6a */
        case DECAFT:  /* L3c6a */
            L3e8d ((fttyp == FLOAT) ? "_fdec" : "_ddec");
            break;
        case DTOF:    /* L3c80 */
            L3e8d ("_dtof");
            break;
        case FTOD:    /* L3c86 */
            L3e8d ("_ftod");
            break;
        case LTOD:      /* L3c8c */
            L3e8d ("_ltod");
            break;
        case ITOD:      /* L3c92 */
            L3e8d ("_itod");
            break;
        case UTOD:      /* L3c98 */
            L3e8d ("_utod");
            break;
        case DTOL:    /* L3c9e */
            L3e8d ("_dtol");
            break;
        case DTOI:    /* L3ca4 */
            L3e8d ("_dtoi");
            break;
        default:           /* L3cb0 */
            L4823 ("codgen - floats");
            prnt_strng (D0057);
            od (parm1);
            newln ();
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

    ot ("bsr ");
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
        od ((int)intarray);
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
                od (*(intarray++));

                if ((siz - 1) != var0)
                {
                    prnt_chr (',');
                }

                ++var0;
            }
        }
    }

    newln ();
}

void
#ifdef COCO
L3e51 (strng)
    char *strng;
#else
L3e51 (char *strng)
#endif
{
    ot (D0051);
    L43d1 (strng);
    sp += INTSIZ;
}

void
#ifdef COCO
L3e6e (strng)
    char *strng;
#else
L3e6e (char *strng)
#endif
{
    ot (D0051);
    L43d1 (strng);
    sp += LONGSIZ;
}

void
#ifdef COCO
L3e8d (strng)
    char *strng;
#else
L3e8d (char *strng)
#endif
{
    ot (D0051);
    L43d1 (strng);
}

void
#ifdef COCO
L3ea4 (parm1, parm2, cref)
    register int parm1;
    int parm2;
    expnode *cref;
#else
L3ea4 (int parm1, int parm2, expnode *cref)
       /*   +10        +12            +14 */
#endif
{
    char *strng;
    int var2 = 0;
    int var0;

    if (parm2 == NODE)       /* else L3ed4 */
    {
        var2 = (cref->type == CHAR) ? INT : 0;
        parm2 = cref->op;
        /* Need to fix this...  probably with a cast */
        cref = cref->val.num;
    }

    /*switch (cref->type)*/
    switch (parm1)
    {
        case AND:        /* L3ed8 */
            strng = "and";
            break;
        case OR:       /* L3ede */
            strng = "or";
            break;
        case XOR:      /* L3ee4 */
            strng = "eor";
            break;
    }

    switch (parm2)
    {
        case NAME:     /* L3f00 */
        case YIND:          /* L3f00 */
        case UIND:          /* L3f00 */
        case XIND:          /* L3f00 */
            if (var2)
            {
                if (parm1 == AND)
                {
                    L43d1 (D0055);
                }

                ot (strng);
                doref ('b', parm2, cref, 0);
            }
            else
            {
                ot (strng);       /* L3f22 */
                doref ('a', parm2, cref, 0);
                ot (strng);
                doref ('b', parm2, cref, 1);
            }

            break;
        case CONST:   /* L3f68 */
            switch (var0 = ((int)cref >> 8) & 0xffff)
            {
                case 0:     /* L3f79 */
                    if (parm1 == AND)
                    {
                        L43d1 (D0055);
                    }

                    break;
                case 255:   /* L3f87 */
                    if (parm1 == AND)
                    {
                        break;
                    }

                    if (parm1 == XOR)
                    {
                        L43d1 ("coma");
                        break;
                    }

                    /* fall through to default */
                default:    /* L3fa0 */
                    ot (strng);       /* L3fa0 */
                    doref ('a', CONST, var0, 0);
                    break;
            }

            switch (var0 = ((int)cref & 0xff))        /* L3fcd */
            {
                case 0:     /* L3fd6 */
                    if (parm1 == AND)
                    {
                        L43d1 ("clrb");
                    }

                    break;
                case 255:   /* L3fe4 */
                    if (parm1 == AND)
                    {
                        break;
                    }

                    if (parm1 == XOR)
                    {
                        L43d1 ("comb");
                        break;
                    }

                default:    /* L4000 */
                    ot (strng);
                    doref ('b', CONST, var0, 0);
                    break;
            }

            break;
        case 110:          /* L402e */
            fprintf (OutPath, " %sa ,s+\n %sb ,s+\n", strng, strng);
            sp += INTSIZ;
            break;
        default:           /* L404f */
            L4823 ("compiler trouble");
            break;
    }
}

void
#ifdef COCO
doref (ch, parm2, parm3, parm4)
    int ch;
    int parm2;
    int parm3;
    int parm4;
#else
doref (int ch, int parm2, int parm3, int parm4)
#endif
{
    prnt_chr (ch);
    prnt_chr (' ');
    L40d0 (parm2, parm3, parm4);
    newln ();
}

void
#ifdef COCO
addoff (offset, parm2, parm3)
    register int offset;
    int parm2;
    int parm3;
#else
addoff (int offset)
#endif
{
    if (offset)
    {
        if (offset > 0)
        {
            prnt_chr ('+');
        }

        od (offset);
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
        register expnode *cref;

        case NODE:          /* L40ee */
            cref = parm2;

            if (cref->op == AMPER)
            {
                prnt_chr ('#');
                L40d0 (NODE, cref->left, parm3);
            }
            else
            {
                L40d0 (cref->op, cref->val.num, parm3 + cref->modifier);
            }

            return;
        case CONST:   /* L4125 */
            prnt_chr ('#');
            od (parm2);
            break;
        case FREG:          /* L4134 */
            prnt_strng ("_flacc");
            addoff (parm3);
            prnt_strng (D004d);
            break;
        case NAME:     /* L4154 */
            if (L4d0_valu = parm2)   /* else L4265 (= break) */
            {
                switch (var2 = L4d0_valu->ftyp)
                {
                    case AUTO:      /* L4165 */
                        od (parm2 =
                                L4d0_valu->rfdat.wrd - sp + parm3);
                        prnt_strng (spind);
                        break;
                    case STATICD:  /* L417d */
                        if ( ! D0023)
                        {
                            prnt_chr ((parm1 & 0x8000) ? '>' : '<');
                        }

                        /* fall through to next case */
                    case STATIC:    /* L4199 */
                        prt_loclbl (L4d0_valu->rfdat.wrd);
                        goto L41d2;
                    case DIRECT:    /* L41a8 */
                    case EXTERND:    /* L41a8 */
                        if ( ! D0023)
                        {
                            prnt_chr ((D0023 & 0x8000) ? '>' : '<');
                        }

                        /* fall through to next case */
                    case EXTERN:    /* L41c4 */
                    case EXTDEF:     /* L41c4 */
                        prt_lblnam (L4d0_valu->rfdat.st);
L41d2:
                        addoff (parm3);

                        if ( ! (parm1 & 0x8000))
                        {
                            if ((D0023) || (var2 == DIRECT) ||
                                    (var2 == EXTERND) ||
                                    (var2 == STATICD))
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
                od (parm3);
            }

            break;
        case XIND:          /* L426f */
        case YIND:          /* L426f */
        case UIND:          /* L426f */
            od (parm2 += parm3);
            prnt_chr (',');

            switch (parm1 & 0x7fff)
            {
                case XIND:   /* L428e */
                    prnt_chr ('x');
                    break;
                case YIND:   /* L4293 */
                    prnt_chr ('y');
                    break;
                case UIND:   /* L4298 */
                    prnt_chr ('u');
                    break;
                default:    /* L431a */
                    break;
            }

            break;
        case STACK:          /* L42b6 */
            prnt_strng (spind);
            prnt_strng ("++");
            sp += INTSIZ;
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
        case EQ:       /* L4343 */
            return "eq ";
        case NEQ:      /* L4349 */
            return "ne ";
        case LEQ:      /* L434f */
            return "le ";
        case LT:         /* L4355 */
            return "lt ";
        case GEQ:      /* L435b */
            return "ge ";
        case GT:         /* L4361 */
            return "gt ";
        case ULEQ:     /* L4367 */
            return "ls ";
        case ULT:       /* L436d */
            return "lo ";
        case UGEQ:     /* L4373 */
            return "hs ";
        case UGT:       /* L4379 */
            return "hi ";
    }
}

void
#ifdef COCO
ot(opcod)
    char *opcod;
#else
ot(char *opcod)
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
    ot (opcod);
    newln ();
}

void
newln ()
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
 * od () - writes the integer value passed as a        *
 *              to the output path                              *
 * ************************************************************ */

void
#ifdef COCO
od (valu)
    int valu;
#else
od (int valu)
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
    newln ();
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
    od (valu);
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
modstk (valu)
    int valu;
#else
modstk (int valu)
#endif
{
    int _stksz;

    if (_stksz = valu - sp)
    {
        ot ("leas ");
        od (_stksz);
        prnt_strng (spind);
        newln ();
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
    char *lblnam; int isglbl;
#else
prt_label (char *lblnam, int isglbl)
#endif
{
    prt_lblnam (lblnam);

    if (isglbl)
    {
        prnt_chr (':');
    }

    newln ();
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
outstr (regnam, lblnum)
    int regnam; int lblnum;
#else
outstr (int regnam, int lblnum)
#endif
{
    lea_reg (regnam);
    fprintf (OutPath, "%c%d,pcr\n", '_', lblnum);
}
