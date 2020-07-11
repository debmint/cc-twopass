/* ****************************************************** *
 * pass1_05.c                                             *
 * ****************************************************** */

/* $Id: p1_05.c 18 2008-05-19 21:54:22Z dlb $ */

/* This file _should_ be an exact match with original code */

#ifndef COCO
#define direct
#endif

direct int RegClsDpth;
direct struct some_struct *D0005,
                          *D0007,
                          *SomeCurnt;

#include "pass1.h"

/* *************************************************************** *
 * L3227 () - Process a function ??????                            *
 * We have already run nxt_word(), so we have at the very least    *
 * the first non-"^#" word in the file                             *
 * *************************************************************** */

#ifndef COCO

void
L3227 (void)
#else

void 
L3227 ()
#endif
{
    /* 20 bytes storage */
    int _varsize;
    int v16;
    int v14;
    struct memberdef *v12;
    int _vt_ftyp;
    int varclass;
    int v6;
    struct memberdef *v4;
    LBLDEF *v2;
    struct memberdef *mdf_v0;

    register LBLDEF *regpt;     /* I'm sure this is correct */

    while (sym == C_RBRKET)
    {
        reprterr ("too many brackets");
        nxt_word();
    }

    if (sym == C_LBRKET)
    {
        reprterr ("function header missing");
        /* I believe the parameter 0 is invalid.  We'll leave it
         * like this till we get verify that we have correct code
         */
#ifdef __linux__
        L3a4c ();
#else
        L3a4c (0);
#endif
        L4204 (&D0049);
        nxt_word();
        return;
    }

    switch (_vt_ftyp = getSC_word ())
    {
        /* At this point, we're still outside the function
         * we cannot have register or auto types */

        case FT_REGISTER:
        case FT_AUTO:
            reprterr ("storage error");
            /* Fall through to next case */
            /* We didn't have a type definition, default to FT_LSEEK */
        case 0:
            _vt_ftyp = FT_LSEEK;
    }

    /* Here, we should have _some_ kind of a data type - int, char, etc  */

    if (!(varclass = do_lblnam (&_varsize, &v4, &mdf_v0)))     /* else L32bd */
    {
        varclass = FT_INT;
    }

    for (;;)        /* L32bd */
    {
        v12 = v4;
        v6 = L3f8a (&v2, &v12, varclass);

        if (!(regpt = v2))    /* else L32f1 */
        {
            if ((v6 != 4) && (v6 != 3))
            {
                noidentf ();
            }

            goto L34b1;
        }

        if (inparentheses (v6))      /* else L3316 */
        {
            if ((sym == C_COMMA) || (sym == C_SEMICOLON))
            {
                v14 = FT_EXTERN;
            }
            else
            {
                v14 = FT_LSEEK;
            }
        }
        else
        {
            v14 = _vt_ftyp;          /* L3318 */
        }

        if (regpt->gentyp)     /* else L3364 */
        {
            if (!(declrcmp (regpt, v6, mdf_v0)) && (v14 != 14))       /* else L3438 */
            {
                if ((regpt->fnccode != FT_EXTERN) &&
                                 (regpt->fnccode != FT_DPXTRN))/*else L3353*/
                {
                    multdef();
                }
                else
                {
                    regpt->fnccode = v14;       /* L3353 */
                    regpt->w4 = v12;
                    regpt->p10 = (int)mdf_v0;   /* cast correct?? */
                    goto L3376;
                }
            }
        }
        else
        {       /* L3364 */
            regpt->gentyp = v6;
            regpt->p12 = 0;
            regpt->fnccode = v14;
            regpt->p10 = (int)mdf_v0;       /* cast correct?? */
L3376:
            v16 = L4100 (regpt, v12, _varsize);

            if (!(inparentheses (v6)))      /* else L3438 */
            {
                if (sym == C_EQUAL)       /* else L33b4 */
                {
                    L4432 (regpt, v14, v6);      /* go to L341e */
                }
                else
                {
                    if (!v16 && (v14 != 14)) /* L33b4 */
                    {
                        sizundef ();       /* go to L341e */
                    }
                    else
                    {
                        switch (v14)
                        {
                            case FT_DPSTATIC: /* L33cb */
                            case FT_STATIC: /* L33cb */
                                localdata (regpt, v16,
                                        (v14 == FT_DPSTATIC) ? 1 : 0);
                                break;
                            case FT_DIRECT: /* L33e8 */
                            case FT_LSEEK: /* L33e8 */
                                globldata (regpt, v16,
                                            (v14 == FT_DIRECT) ? 1 : 0);
                                break;
                        }
                    }
                }

                /* L341e ( _68 ) */
                if (v14 == FT_STATIC)
                {
                    regpt->fnccode = FT_LSEEK;  /* ??????????????? */
                }
                else
                {
                    if (v14 == FT_DPSTATIC)
                    {
                        regpt->fnccode = FT_DIRECT;
                    }
                }
            }
        }

        /* L3438 ( _84 ) */
        if (inparentheses (v6))   /* else L34b4 */
        {
            v6 = decref (v6);

            if ((inbraces (v6)) || (inparentheses (v6)) ||
                    (v6 == 4) || (v6 == 3))
            {
                reprterr ("function type error");
                regpt->gentyp = 49;
                v6 = 1;
            }

            if (v14 == FT_EXTERN)   /* L3489 */
            {
                L4204 (&D0047);
            }
            else
            {
                D004d = v6;     /* L349e */
                dofunction (regpt, _vt_ftyp);
                return;
            }
        }
L34b1:
        if (sym == C_COMMA)
        {
            nxt_word();
        }
        else
        {
            break;
        }
    }       /* end of "for (;;)" at L32bd */

    if (need (C_SEMICOLON))     /* _21 ( L34c2 ) */
    {
        junk ();
    }
}

#ifndef COCO

void 
L34d6 (void)
#else

void
L34d6 ()
#endif
{
    /* 18 bytes storage */
    int _strgclass;
    int v14;
    struct memberdef *v12;
    struct memberdef *v10;
    int v8;
    int v6;
    int v4;
    LBLDEF *v2;
    struct memberdef *v0;
    register LBLDEF *regpt;

    switch ((_strgclass = getSC_word()))
    {
        case 0:         /* L34f6 */
            _strgclass = FT_AUTO;      /* 13 */
            break;
        case FT_REGISTER:       /* 16 */
            break;
        default:        /* L34eb */
            reprterr ("argument storage");
            _strgclass = FT_AUTO;      /* 13 */
            break;
    }

    if (!(v14 = do_lblnam (&v8, &v10, &v0)))        /* L3509 */
    {
        v14 = FT_INT;
    }

    /* Don't know if this for loop is correct, but it's for the
     * go to L3523 preceding L3614
     */

    for (;;)
    {
        v12 = v10;                  /* L3523 */
        v4 = L3f8a (&v2, &v12, v14);
        regpt = v2;
        
        if ((inparentheses (v4)) || (v4 == 4) || (v4 == 10))
        {
            reprterr ("argument error");    /* go to L3595 */
            goto L35f8;
        }
        else
        {
            if (inbraces (v4))
            {
                v4 = incref (decref (v4));   /* go to L358a */
            }
            else
            {
                if (v4 == 5)
                {
                    v4 = 6;
                }
            }

            if (regpt == 0)
            {
                noidentf ();
                goto L35f8;
            }
        }

        v6 = L38af (_strgclass, v4);       /* L359b */

        switch (regpt->fnccode)
        {
            case 11:    /* L35af */
                regpt->gentyp = v4;
                regpt->fnccode = v6;
                regpt->p10 = (int)v0;       /* cast correct?? */
                
                if (!(L4100 (regpt, v12, v8)))
                {
                    sizundef ();
                }

                break;

            case FT_AUTO:   /* L35d3 */ /*13*/
            case FT_REGISTER:   /* L35d3 */ /*16*/
                multdef ();
                break;

            default:
                reprterr ("not an argument");
                break;
        }

L35f8:
        if (sym == C_EQUAL)
        {
            cant_init ();
        }

        if (sym == C_COMMA)
        {
            nxt_word ();
        }
        else
        {
            break;
        }
    }       /* end for (;;) loop */

    if (need (C_SEMICOLON))     /* L3614 */     /* else L3876 */
    {
        junk ();
    }
}

/* ************************************************************** *
 * L3628 ()                                                       *
 * Apparently defines a label within a block                      *
 * ************************************************************** */

#ifndef COCO

void 
L3628 (void)
#else

void
L3628 ()
#endif
{
    int _frst_fty;
    int _new_fty;
    int v12;
    struct memberdef *v10;
    int _newsiz;
    CMDREF *v6;
    LBLDEF *v4;
    struct memberdef *_oldsize;
    struct some_struct *v0;
    register LBLDEF *regptr;

    switch (_frst_fty =  getSC_word())
    {
        case FT_DIRECT:      /* 33 */
            reprterr ("storage error");
        case 0:     /* Default type is "auto" */
            _frst_fty = FT_AUTO;     /* 13 */
    }

    if (!(_new_fty = do_lblnam(&_newsiz, &v10, &_oldsize)))
    {
        _new_fty = FT_INT;
    }

    for (;;)        /* L3673 */
    {
        int l4;
        int l2;
        struct memberdef *l0;

        l0 = v10;
        v12 = L3f8a (&v4, &l0, _new_fty);
        
        if (!(regptr = v4))     /* else L36af */
        {
            if ((v12 != 4) && (v12 != 3))        /* else L371a */
            {
                noidentf ();       /* go to L371a */
            }

            goto L3855;
        }

        if ((inparentheses (v12)) || (_frst_fty == FT_EXTERN))  /*L36af*/  /*else L36fb*/
        {
            if (!regptr->gentyp)    /* L36c4 */    /* else L36e9 */
            {
                regptr->gentyp = v12;
                regptr->fnccode = FT_EXTERN;    /* 14 */
                regptr->p12 = 0;
                regptr->p10 = (int)_oldsize;        /* cast correct?? */
                L4100 (regptr, l0, _newsiz);
            }
            else
            {
                declrcmp (regptr, v12, _oldsize);    /* L36e9 */
            }
                
            goto L3855;
        }

        l4 = L38af (_frst_fty, v12);      /* L36fb */

        if (regptr->gentyp)     /* else L3727 */
        {
            if (regptr->p12 == D0051)   /* else L3720 */
            {
                multdef ();
                goto L3855;
            }

            pushdown (regptr);     /* copy regptr to G18Current, null regptr */
        }

        regptr->gentyp = v12;           /* L3727 */
        regptr->fnccode = l4;       /* was FT_EXTERN (switched from L36c4 */
        regptr->p10 = (int)_oldsize;    /* cast correct?? */
        regptr->p12 = D0051;            /* ??? Parentheses depth ??? */
        regptr->w16 = D004b;
        D004b = regptr;
        
        if (!(l2 = L4100 (regptr, l0, _newsiz)))
        {
            if (sym != C_EQUAL)
            {
                sizundef ();
            }
        }

        switch (l4)
        {
            case FT_AUTO: /* L3761 */
                D0031 -= l2;
                regptr->lbl_nbr = D0031;
                break;
            case FT_DPSTATIC: /* L376b */
            case FT_STATIC: /* L376b */
                regptr->lbl_nbr = (++LblNum);
                break;
        }

        if (sym == C_EQUAL)   /* else L3824 */       /* L3787 */
        {
            if ((l4 == FT_STATIC) || (l4 == FT_DPSTATIC))   /* else L37b4 */
            {
                L4432 (regptr, l4, v12);    /* go to L3858 */
            }
            else
            {
                nxt_word ();      /* L37b4 */

                if ((!(inbraces (v12))) && (v12 != 4) &&
                                    (v6 = L0580 (2)))   /* else L381f */
                {
                    if (SomeCurnt)  /* else L37f3 */
                    {
                        SomeCurnt = (v0 = SomeCurnt)->ss_prev;
                        v0->ss_prev = 0;
                    }
                    else
                    {
                        /*v0 = addmem (6);*/
                        v0 = addmem (sizeof (struct some_struct));
                    }

                    v0->ss02 = v6;
                    v0->mylbl = regptr;

                    if (D0005)
                    {
                        D0007->ss_prev = v0;
                    }
                    else
                    {
                        D0005 = v0;
                    }

                    D0007 = v0;
                }
                else
                {
                    cant_init ();   /* L381f */
                }
            }
        }
        else
        {
            switch (l4)
            {
                case FT_STATIC:     /* L3828 */ /*15*/
                case FT_DPSTATIC:
                    rmbnolbl (regptr->lbl_nbr, l2, ((l4 == FT_DPSTATIC) ? 1 : 0));
                    break;
                default:            /* L3858 */
                    break;
            }
        }

L3855:
        if (sym != C_COMMA)    /* L3858 */
        {
            break;
        }

        nxt_word ();
    }       /* End of the for (;;) loop holding 6 bytes of data */

    need (C_SEMICOLON);
}

#ifndef COCO

int
declrcmp (register LBLDEF *regptr, int p2, struct memberdef *p3)
#else
int
declrcmp (regptr, p2, p3)
register LBLDEF *regptr;
int p2;
struct memberdef *p3;
#endif
{
    /*if (regptr->gentyp == p2)
    {
        if ((p2 == 4) || (regptr->p10 == p3))
        {
            return 0;
        }
    }*/
    /* cast correct??  for p3?*/
    if ((regptr->gentyp != p2) || ((p2 == 4) && (regptr->p10 != (int)p3)))
    {
        reprterr ("declaration mismatch");
        return 1;
    }

    return 0;
}

#ifndef COCO

int
L38af (int sclass_result, int fty)
#else

int 
L38af (sclass_result, fty)
int sclass_result;
int fty;
#endif
{
    if (sclass_result == FT_REGISTER)       /* else L3900 */
    {
        if (RegClsDpth < 1)  /* else L38fb */
        {
            switch (fty)
            {
                default:    /* L38cb */
                    if (!ispointer (fty))
                    {
                        return FT_AUTO;
                    }

                case FT_INT:     /* L38d6 */
                case FT_UNSIGNED:
                    /*if (++RegClsDpth == 1)
                    {
                        return 111;
                    }
                    
                    return 118;
                    break;*/
                    /* The above may be clearer, but try to match code */
                    return ((++RegClsDpth == 1) ? 111 : 118);
            }
        }

        return FT_AUTO;
    }

    return sclass_result;
}

/* ************************************************************ *
 * dofunction () - Process a single function                    *
 * ************************************************************ */

#ifndef COCO

void
dofunction (LBLDEF *my_lbl, int myftyp)
#else
dofunction (my_lbl, myftyp)
LBLDEF *my_lbl;
int myftyp;
#endif
{
    int v8;
    int v6;
    LBLDEF *L3904_v4;
    char *_lbl_nam;
    int v0;
    register LBLDEF *regptr;

    D0051 = 1;
    D0033 = RegClsDpth = D0031 = D003b = D002f = 0;

    /* Get parameter definitions */

    while (sym != C_LBRKET)     /* L3924 */
    {
        L34d6 ();
    }

    _lbl_nam = my_lbl->fnam;

    if (doprofil)
    {
        prtprofil (_lbl_nam, (v0 = ++LblNum));
    }

    prtstkchk (_lbl_nam, ((myftyp != FT_STATIC) ? 1 : 0), v0);
    regptr = D0047;
    v8 = 4;

    while (regptr)
    {
        int __subvar;     /* 3974 */

        regptr->lbl_nbr = v8;
        
        switch (regptr->gentyp)
        {
            case 8:      /* L397e */
            case 5:      /* L397e */
                __subvar = 4;
                break;
            case 6:      /* L3983 */
                __subvar = 8;
                break;
            case 2:      /* L3988 */
                ++(regptr->lbl_nbr);
            default:
                __subvar = 2;
                break;
        }

        switch ((v6 = regptr->fnccode))
        {
            case C_RGWRD:   /* L39b6 */
            case C_X_RGWRD:   /* L39b6 */
#ifdef __linux__
                prt_4b5e (v6, v8, 0);
#else
                prt_4b5e (v6, v8);
#endif
                break;
            case 11:    /* L39c5 */
                regptr->fnccode  = FT_AUTO;     /* 13 */
                break;
        }

        v8 += __subvar;
        regptr = regptr->w16;
    }

    L3904_v4 = D0047;
    D0047 = 0;
    L3a4c ();

    L4204 (&L3904_v4);
    L4204 (&D0049);

    if (D004f != 18)
    {
        prt_4b5e ( 18, 0, 0);
    }

    D004f = 0;
    flgstkchk ();
    D0051 = 0;

    if (sym == -1)
    {
        reprterr ("function unfinished");
    }

    nxt_word ();
}

#ifndef COCO

void
L3a4c (void)
#else

void 
L3a4c ()
#endif
{
    struct some_struct *v4;
    LBLDEF *v2;
    int v0;
    register CMDREF *regptr;

    v2 = D004b;
    D004b = 0;
    nxt_word ();
    ++D0051;
    v0 = D0031;

    while (issclass () || istype ())        /* L3a71 */
    {
        L3628 ();
    }

    if (D003b > D0031)
    {
        D003b = D0031;
    }

    D002f = wrt_M (D0031);      /* L3a8c */

    while (D0005)       /* L3b0a */
    {
        v4 = D0005;     /* L3a9a */
        regptr = v4->ss02;
        /* cast correct?? for v4->mylbl*/
        regptr = add_cmdref (C_USRLBL, 0, 0, (int)v4->mylbl,
                             regptr->_cline, regptr->_lpos);
        regptr = add_cmdref (C_EQUAL, regptr, v4->ss02, 0,
                             regptr->_cline, regptr->_lpos);
        L0393 (prt_4c4f (L0f18 (regptr)));
        v4 = v4->ss_prev;
        D0005->ss_prev = SomeCurnt;
        SomeCurnt = D0005;
        D0005 = v4;
    }

    while ((sym != C_RBRKET) && (sym != -1))
    {
        do_loops ();
    }

    L4204 (&D004b);
    D004b = v2;
    --D0051;
    D0031 = v0;

    D002f = (D004f != 18) ? wrt_M (v0) : v0;
}

#ifndef COCO

void
do_parentheses (LBLDEF **p1)
#else
do_parentheses (p1)
LBLDEF **p1;
#endif
{
    LBLDEF *L35ba_v0;
    register LBLDEF *regptr;

    *p1 = 0;

    /* Loop for each comma-separated variable defined on this "line" */
    do
    {
        nxt_word ();

        if (sym == C_RPAREN)        /* else L3bda */
        {
            break;
        }

        if (sym == C_USRLBL)      /* else L3bcd */
        {
            regptr = (LBLDEF *)LblVal;

            if (regptr->fnccode == 11)
            {
                reprterr ("named twice");
            }
            else
            {
                if (regptr->gentyp)
                {
                    /* copy regptr to G18Current, null regptr */
                    pushdown (regptr);
                }
            }

            regptr->gentyp = 1;     /* L3b9e */
            regptr->fnccode = 11;
            regptr->p12 = 1;
            regptr->vsize = 2;
            
            if (*p1)
            {
                /* Just to get it to compile */
                L35ba_v0->w16 = regptr;
            }
            else
            {
                *p1 = regptr;    /* L3bbe */
            }

            regptr->w16 = 0;
            L35ba_v0 = regptr;
            nxt_word ();
        }
        else
        {
            noidentf ();
        }

    } while (sym == C_COMMA);          /* end for (;;) loop */

    need (C_RPAREN);     /* L3bda */
}

/* ************************************************************ *
 * getSC_word () - Get the word following a storage class       *
 *      definition.  I.E. if it's a storage class, (extern,     *
 *      static, auto, etc,), get the following word(s), which   *
 *      define the variable name                                *
 * Returns: If a storage class, the original FT_type            *
 *              (modified if DP)                                *
 *          NULL if not a type definition                       *
 *          DP data = old FT_ + 2                               *
 * nxt_word () has also been run to retrieve the data type      *
 * ************************************************************ */

#ifndef COCO
int 
getSC_word (void)
#else

int
getSC_word ()
#endif
{
    int _sc_fty;

    /* If it's a storage class, i.e. extern, static, auto, etc */

    if (issclass ())     /* else L3c2f */
    {
        _sc_fty = LblVal;      /* FT_type */
        nxt_word ();

        /* Direct Page reference = old FT_ + 2 */

        if ((sym == C_BUILTIN) && (LblVal == FT_DIRECT))    /* else L3c2b */
        {
            switch (_sc_fty)
            {
                case FT_STATIC:    /* L3c12 */
                    _sc_fty =  FT_DPSTATIC;
                    break;
                case FT_EXTERN:    /* L3c17 */
                    _sc_fty = FT_DPXTRN;
                    break;
            }

            nxt_word ();
        }

        return _sc_fty;
    }
    else
    {
        return 0;
    }
}

/* ******************************************************************** *
 * do_lblnam () - process a variable definition                         *
 * On entry, we have the first word in a variable definition.  It could *
 * be something like "short", or "long", (optionally followed by "int"  *
 * or simply "int", or "char", or a user-defined type                   *
 *                                                                      *
 * Returns: Updated FT_type for the variable (lbl_fttyp)                *
 *          sets siz (in calling function) to size of variable          *
 *          sets p2  (in calling function) to 0                         *
 * On return, we have the variable name                                 *
 * ******************************************************************** */

#ifndef COCO

do_lblnam (int *siz, struct memberdef **p2, struct memberdef **lastmember)
#else

int 
do_lblnam (siz, p2, lastmember)
int *siz;
struct memberdef **p2;
struct memberdef **lastmember;
#endif
{
    LBLDEF *_strctdef;
    int _strtotsz;
    int _mmbrsiz;
    int __mbr_fty;
    int _old_struct;
    int v14;
    struct memberdef *v12;
    int v10;
    struct memberdef *nwstruct;
    struct memberdef *v6;
    struct memberdef *_lst_sz;
    int lbl_fttyp = 0;
    int _varsiz = INTSIZ;

    register LBLDEF *regptr;

    *lastmember = 0;

    /* On entry here, we have some type of label.  It's either a
     * data type (int, char, etc), or a function name */

    if (sym == C_BUILTIN)             /* else L3f51 */
    {
        switch ((lbl_fttyp = LblVal))    /* L3f0f */
        {
            case FT_SHORT:              /* L3c61 */
                lbl_fttyp = FT_INT; /* Promote to "int" fall through to next */

            case FT_UNSIGNED:           /* L3c66 */
                nxt_word ();

                
                if ((sym == C_BUILTIN) && (LblVal == FT_INT))  /* else L3f79 */
                {
                    nxt_word ();
                }

                break;

            case FT_CHAR:      /* L3c7f */
                _varsiz = CHARSIZ;
            case FT_INT:      /* L3cb7 */
                nxt_word ();
                break;

            case FT_LONG:      /* L3c84 */
                nxt_word ();
                _varsiz = LONGSIZ;
                
                /* Check for "long int" or "long float" */

                if (sym == C_BUILTIN)
                {
                    if (LblVal == FT_INT)
                    {
                        nxt_word ();
                    }
                    else
                    {
                        if (LblVal == FT_FLOAT)
                        {
                            /* "long float" means double */
                            lbl_fttyp = FT_DOUBLE;
                            _varsiz = DBLSIZ;
                            nxt_word ();
                        }
                    }
                }
                break;

            case FT_DOUBLE:      /* L3ca8 */
                lbl_fttyp = FT_DOUBLE;
                _varsiz = DBLSIZ;
                nxt_word ();
                break;

            case FT_FLOAT:      /* L3cb2 */
                _varsiz = FLOATSIZ;
                nxt_word ();
                break;

                /* They had "default" up here.  See what happens */
            default:     /* L3cbd */
                lbl_fttyp = 0;
                break;

                /* Begin struct */
            case FT_UNION:      /* L3cc4 */
            case FT_STRUCT:
                _varsiz = _strtotsz = 0;
                ++Struct_Union;     /* Go into "struct mode" for FindLbl() */
                _strctdef = 0;
                nxt_word ();        /* get struct name or "{" */
                --Struct_Union;     /* Get back out of "struct mode" */

                /* Process struct name if applicable */

                if (sym == C_USRLBL)    /* else L3d5d */
                {           /* We have a struct name */
                    _strctdef = (LBLDEF *)LblVal;      /* Pointer to LBLDEF */

                    /* FindLbl sets gentyp to 0 for new labels */

                    if (!(_strctdef->gentyp))
                    {
                        _strctdef->gentyp = G_STRCNAM;
                        _strctdef->fnccode = FT_LONG;     /* 8 */
                    }
                    else
                    {
                        /* "struct <non-struct>"  */

                        if (_strctdef->fnccode != FT_LONG)
                        {
                            reprterr ("name clash");
                        }
                    }
                    
                    /* Next "word" is either variable name or "{" */
                    
                    nxt_word ();        /* L3d1b */

                    if (sym != C_LBRKET)
                    {
                        /* something like "struct somestruct structname" */
                        if (_strctdef->gentyp == G_STRCT)
                        {
                            *siz = _strctdef->vsize;
                            /* cast correct?? */
                            *lastmember = (struct memberdef *)_strctdef->p10;
                            return FT_STRUCT;
                        }                        
                        else
                        {
                            /* cast correct?? */
                            *siz = (int)_strctdef;   /* L3d45 */
                            return G_STRCNAM;
                        }
                    }

                    /* Cannot have a definition name matching member name */
                    /* How does this differ from above ??? */

                    if (_strctdef->gentyp == G_STRCT)
                    {
                        multdef ();
                    }
                }       /* end process struct name */

                if (sym != C_LBRKET)    /* L3d5d */
                {
                    reprterr ("struct syntax");
                    break;
                }

                ++Struct_Union;        /* L3d73 */

                do           /* Loop for each struct member */
                {
                    _old_struct = Struct_Union;    /* L3d7a */
                    Struct_Union = 0;
                    nxt_word ();
                    Struct_Union = _old_struct;

                    if (sym == C_RBRKET)    /* else L3ee2 */
                    {
                        break;
                    }

                    /* Process member - recurse into self (this function) */

                    __mbr_fty = do_lblnam ( &_mmbrsiz, &v12, &_lst_sz);

                    /* At this point, __mbr_fty = FT_code for member variable
                     * sym contains C_type for the character or name
                     */

                    while (1)
                    {
                        struct memberdef *l2;
                        LBLDEF *membrlbl;

                        l2 = v12;

                        if (sym == C_SEMICOLON)    /* else L3ecc */
                        /* Done */
                        {
                            break;
                        }

                        ++D0051;
                        v14 = L3f8a (&membrlbl, &l2, __mbr_fty);
                        regptr = membrlbl;
                        --D0051;

                        if (regptr == 0) /* else L3df1 */
                        {
                            noidentf ();
                            goto L3ec1;
                        }

                        if (regptr->gentyp)     /* L3df1 */   /* else L3e26 */
                        {
                            if (regptr->p12 == D0051)   /*else L3e1f */
                            {
                                if ((regptr->gentyp != v14) ||
                                    (regptr->fnccode  != FT_STRCMBR) ||
                                    (regptr->lbl_nbr != _strtotsz))
                                {
                                    reprterr ("struct member mismatch");
                                }
                            }
                            else
                            {
                                /* copy regptr to G18Current, null regptr */
                                pushdown (regptr);     /* L3e1f */
                            }
                        }

                        if ( v14 == G_STRCNAM) /* L3e26 */
                        {
                            reprterr ("undefined structure");
                        }

                        regptr->gentyp = v14;
                        regptr->fnccode = FT_STRCMBR;
                        regptr->lbl_nbr = _strtotsz;
                        regptr->p10 = (int)_lst_sz;     /* cast correct?? */
                        
                        if (v10 = L4100 (regptr, l2, _mmbrsiz))
                        {       /* else L3e84 */
                            if (lbl_fttyp == FT_STRUCT)
                            {
                                _varsiz = (_strtotsz += v10);
                            }
                            else
                            {
                                _varsiz = (v10 > _varsiz ? v10 : _varsiz);
                            }
                        }
                        else
                        {
                            sizundef ();
                        }

                        regptr->p12 = D0051;    /* L3e87 */
                        regptr->w16 = D004b;
                        D004b = regptr;

                        if (lbl_fttyp == FT_STRUCT)    /* else L3ec4 */
                        {
                            nwstruct = addmem (sizeof (struct memberdef));
                            nwstruct->mmbrlbl = regptr;
                            
                            if (*lastmember)
                            {
                                v6->mbrPrev = nwstruct;
                            }
                            else
                            {
                                *lastmember = nwstruct;    /* L3eb6 */
                            }

                            v6 = nwstruct;
                        }
L3ec1:
                        if (sym != C_COMMA)
                        {
                            break;
                        }

                        nxt_word ();
                        continue;

                    }   /* End of while (1) loop */
                } while (sym == C_SEMICOLON);  /* L3ed8 */

                --Struct_Union;    /* L3ee2 */

                if (_strctdef)
                {
                    _strctdef->vsize = _varsiz;
                    _strctdef->gentyp = G_STRCT;
                    _strctdef->p10 = (int)(*lastmember);
                }

                need (C_RBRKET);
                break;              /* End struct def */
        }
    }
    else        /* NOT BUILTIN */
    {
        /* typedef */

        /* L3f51 */
        if ((sym == C_USRLBL) && (((regptr = (LBLDEF *)LblVal)->fnccode) == FT_TYPEDEF))
        {
            *siz = regptr->vsize;
            *p2 = regptr->w4;
            *lastmember = (struct memberdef *)(regptr->p10);/* cast correct?? */

            nxt_word ();
            return regptr->gentyp;
        }
    }

    *siz = _varsiz;     /* First parameter */
    *p2 = 0;

    return lbl_fttyp;
}

/* ************************************************************** *
 * L3f8a () -                                                     *
 * Passed:  p1 - POINTER to variable's LBLDEF *                   *
 *          p2 - pointer to                                       *
 *          FT_type of current "word" (for local use)             *
 * Returns: FT_type                                               *
 * ************************************************************** */

#ifndef COCO

int
L3f8a (LBLDEF **lbl_def, struct memberdef **p2, int ft_type)
#else

int 
L3f8a (lbl_def, p2, ft_type)
LBLDEF **lbl_def;
struct memberdef **p2;
int ft_type;
#endif
{
    int __ptrdpth,
        _strctstate;
    struct memberdef *v6;
    int _bracdpth;
    struct memberdef *v2;
    LBLDEF *_lblptr;
    register struct memberdef *__member;

#ifdef COCO
    __ptrdpth = *lbl_def = 0;
#else
    __ptrdpth = 0;
    *lbl_def = 0;
#endif

    /* Get past any pointer states (if any) */

    while (sym == C_ASTERISK)    /* ??? Increase pointer count */
    {
        __ptrdpth = incref (__ptrdpth);
        nxt_word ();
    }

    if (sym == C_USRLBL)
    {
        *lbl_def = (LBLDEF *)LblVal;        /* variable name's LBLDEF * */
        nxt_word ();
    }
    else
    {
        if (sym == C_LPAREN)
        {
            nxt_word ();
            ++D0051;
            ft_type = L3f8a (lbl_def, p2, ft_type);      /* call self */
            --D0051;
            need (C_RPAREN);
        }
    }

    if (sym == C_LPAREN)        /* else L4036 */
    {
        __ptrdpth = ((__ptrdpth << 2) + 0x30);

        if (D0051 == 0)
        {
            do_parentheses (&D0047);
        }
        else
        {   /* We are inside a set of parentheses */
            do_parentheses (&_lblptr);
            L4204 (&_lblptr);        /* go to L40b9 */
        }
    }
    else
    {
#ifdef COCO
        v2 = _bracdpth = v6 = 0;       /* L4036 */
#else
        v2 = v6 = 0;
        _bracdpth = 0;
#endif

        _strctstate = Struct_Union;
        Struct_Union = 0;

        while (sym == C_LBRACE)     /* L409d */
        {
            __ptrdpth = (__ptrdpth << 2) + 0x20;      /* L4049 */
            nxt_word ();
            __member = addmem (sizeof (struct bracedef));

            if ((_bracdpth == 0) && (sym == C_RBRACE))
            {
                ((struct bracedef *)(__member))->brCmd = 0;  
            }
            else
            {
                ((struct bracedef *)(__member))->brCmd = L0a4f (0);  /* L4073 */
            }

            if (v6)     /* L407c + 1 */
            {
                ((struct bracedef *)(v6))->brNxt = __member;
            }
            else
            {
                v2 = __member;    /* L4088 */
            }

            /* bugfix 2008-04-08 15:03 */
            /* moved following line from inside preceding brace */
            v6 = (struct bracedef *)__member;
            need (C_RBRACE);
            ++_bracdpth;
        }

        Struct_Union = _strctstate;

        if (v2)
        {
            __member->mmbrlbl = *p2;
            *p2 = v2;
        }
    }

    return (L40ca (ft_type, __ptrdpth));
}

#ifndef COCO

int
L40ca(int p1, int p2)
#else

int 
L40ca (p1, p2)
int p1;
int p2;
#endif
{
    int v0 = p1;

    while (v0 & 0x30)
    {
        v0 >>= 2;
        p2 <<= 2;
    }

    return (p1 + p2);
}

#ifndef COCO

int
L4100 (register LBLDEF *regpt, struct memberdef *p2, int oldsize)
#else
int
L4100 (regpt, p2, oldsize)
register LBLDEF *regpt;
struct memberdef *p2;
int oldsize;
#endif
{
    int _gentyp;
    int _vsize;

    switch ((_gentyp = regpt->gentyp) & 0x0f)
    {
        case FT_CHAR:      /* L4117 */
            _vsize = CHARSIZ;
            break;
        case FT_INT:      /* L411c */
        case FT_UNSIGNED:      /* L411c */
            _vsize = INTSIZ;
            break;
        case FT_LONG:      /* L4121 */
        case FT_FLOAT:      /* L4121 */
            _vsize = LONGSIZ;
            break;
        case FT_DOUBLE:      /* L4126 */
            _vsize = DBLSIZ;
            break;
        case FT_UNION:      /* L412b */
        case FT_STRUCT:      /* L412b */
            _vsize = oldsize;
            break;
        case 10:     /* L412f */
            _vsize = 0;
            break;
    }

    if (_vsize)     /* L4168 */
    {
        regpt->vsize = _vsize;
    }
    else
    {
        regpt->vsize = oldsize;
    }

    return L418a (_gentyp, _vsize, (regpt->w4 = p2));
}

#ifndef COCO

int
L418a (int p1, int p2, register CMDREF *regptr)
#else

int 
L418a (p1, p2, regptr)
int p1;
int p2;
register CMDREF *regptr;
#endif
{
    int v0;

    if ((ispointer (p1)) || (inparentheses (p1)))
    {
        return 2;   /* L41ac */
    }

    if (inbraces (p1))        /* L41b2 */   /* else L41ff */
    {
        v0 = 1;

        do
        {
            v0 *= regptr->ft_Ty;    /* L41c2 */
            regptr = regptr->__cr2;
        /*} while (((p1 = decref (p1)) & 0x30) == 0x20);*/
        } while (inbraces (p1 = (decref (p1))));     /* FIXED I think */

        return (v0 * ((ispointer (p1)) ? 2 : p2));
    }
    else
    {
        return p2;
    }
}

#ifndef COCO

void
L4204 (LBLDEF **p1)
#else
L4204 (p1)
LBLDEF **p1;
#endif
{
    LBLDEF *v62;   /* Some type of pointer to a structure */
    LBLDEF *v60;
    char __tmpstr[60];

    register LBLDEF *regptr = *p1;

    while (regptr)      /* L42c1 */
    {
        v60 = regptr->w16;

        if ((regptr->gentyp == 9) && !(regptr->p10 & 1))
        {
            reprterr (strncat (strcpy (__tmpstr, "label undefined : "),
                        (regptr->fnam), 8));
        }

        switch (regptr->fnccode)
        {
            case C_RGWRD:    /* L4259 */  /* 'o' */
            case C_X_RGWRD:    /* L4259 */  /* 'v' */
                --RegClsDpth;
                break;
        }

        /* L426e */
        if (((v62 = (LBLDEF *)(regptr->ftop)) >
                    LblPtrLow) && (v62 < LblPtrEnd))  /* else L4289 */
        {
            /* Make regptr the base of the current LblTree ?? */
            pullup (regptr);      /* go to L42be */
        }
        else
        {
            if (regptr == *((LBLDEF **)v62))          /* L4289 */
            {
                *((LBLDEF **)v62) = regptr->fnext;
            }
            else
            {
                /* Just to get it to compile */
                v62 = *((LBLDEF **)v62);     /* L4297 */

                /* WHOLE LOOP STILL NOT RIGHT !!!!! */

                while (regptr != v62->fnext)
                {
                    /* Just to get it to compile */
                    v62 = v62->fnext;
                }
            
                v62->fnext = regptr->fnext;
            }

            regptr->fnext = D0019;      /* L42b7 */
            D0019 = regptr;
        }

        regptr = v60;
    }       /* end "while" */

    *p1 = 0;
}

#ifndef COCO

void
sizundef (void)
#else

sizundef ()
#endif
{
    reprterr ("cannot evaluate size");
}

#ifndef COCO

void
noidentf (void)
#else

noidentf ()
#endif
{
    reprterr ("identifier missing");
}
