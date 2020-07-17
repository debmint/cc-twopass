/* ****************************************************** *
 * pass1_05.c                                             *
 * ****************************************************** */

/* $Id: p1_05.c 18 2008-05-19 21:54:22Z dlb $ */

/* This file _should_ be an exact match with original code */

#ifndef COCO
#define direct
#endif

direct int RegClsDpth;
direct struct initstruct *initlist,
                         *initlast,
                         *SomeCurnt;

#include "pass1.h"

/* *************************************************************** *
 * extdef () - Process a function ??????                            *
 * We have already run nxt_word(), so we have at the very least    *
 * the first non-"^#" word in the file                             *
 * *************************************************************** */

void
extdef ()
{
    int size, ssize, tsc;
    dimnode *tdp;
    int sclass, type, temp;
    dimnode *dimptr;
    symnode *ptemp;
    elem *eptr;

    register symnode *ptr;     /* I'm sure this is correct */

    while (sym == RBRACE)
    {
        reprterr ("too many brackets");
        nxt_word();
    }

    if (sym == LBRACE)
    {
        reprterr ("function header missing");
        /* I believe the parameter 0 is invalid.  We'll leave it
         * like this till we get verify that we have correct code
         */
#ifdef __linux__
        block ();
#else
        block (0);
#endif
        clear (&labelist);
        nxt_word();
        return;
    }

    switch (sclass = setclass ())
    {
        /* At this point, we're still outside the function
         * we cannot have register or auto types */

        case REG:
        case AUTO:
            reprterr ("storage error");
            /* Fall through to next case */
            /* We didn't have a type definition, default to EXTDEF */
        case 0:
            sclass = EXTDEF;
    }

    /* Here, we should have _some_ kind of a data type - int, char, etc  */

    if (!(type = settype (&size, &dimptr, &eptr)))     /* else L32bd */
    {
        type = INT;
    }

    for (;;)        /* L32bd */
    {
        tdp = dimptr;
        temp = declarator (&ptemp, &tdp, type);

        if (!(ptr = ptemp))    /* else L32f1 */
        {
            if ((temp != STRUCT) && (temp != UNION))
            {
                noidentf ();
            }

            goto L34b1;
        }

        if (isftn (temp))      /* else L3316 */
        {
            if ((sym == COMMA) || (sym == SEMICOL))
            {
                tsc = EXTERN;
            }
            else
            {
                tsc = EXTDEF;
            }
        }
        else
        {
            tsc = sclass;          /* L3318 */
        }

        if (ptr->type)     /* else L3364 */
        {
            if (!(declrcmp (ptr, temp, eptr)) && (tsc != EXTERN))       /* else L3438 */
            {
                if ((ptr->storage != EXTERN) &&
                                 (ptr->storage != EXTERND))/*else L3353*/
                {
                    multdef();
                }
                else
                {
                    ptr->storage = tsc;       /* L3353 */
                    ptr->dimptr = tdp;
                    ptr->x.elems = eptr;   /* cast correct?? */
                    goto L3376;
                }
            }
        }
        else
        {       /* L3364 */
            ptr->type = temp;
            ptr->blklev = 0;
            ptr->storage = tsc;
            ptr->x.elems = eptr;       /* cast correct?? */
L3376:
            ssize = sizeup (ptr, tdp, size);

            if (!(isftn (temp)))      /* else L3438 */
            {
                if (sym == ASSIGN)       /* else L33b4 */
                {
                    initialize (ptr, tsc, temp);      /* go to L341e */
                }
                else
                {
                    if (!ssize && (tsc != EXTERN)) /* L33b4 */
                    {
                        sizundef ();       /* go to L341e */
                    }
                    else
                    {
                        switch (tsc)
                        {
                            case STATICD: /* L33cb */
                            case STATIC: /* L33cb */
                                localdata (ptr, ssize, (tsc == STATICD));
                                break;
                            case DIRECT: /* L33e8 */
                            case EXTDEF: /* L33e8 */
                                globldata (ptr, ssize, (tsc == DIRECT));
                                break;
                        }
                    }
                }

                /* L341e ( _68 ) */
                if (tsc == STATIC)
                {
                    ptr->storage = EXTDEF;  /* ??????????????? */
                }
                else
                {
                    if (tsc == STATICD)
                    {
                        ptr->storage = DIRECT;
                    }
                }
            }
        }

        /* L3438 ( _84 ) */
        if (isftn (temp))   /* else L34b4 */
        {
            temp = decref (temp);

            if ((isary (temp)) || (isftn (temp)) ||
                    (temp == STRUCT) || (temp == UNION))
            {
                reprterr ("function type error");
                ptr->type = INT | FUNCTION;
                temp = INT;
            }

            if (tsc == EXTERN)   /* L3489 */
            {
                clear (&arglist);
            }
            else
            {
                ftype = temp;     /* L349e */
                newfunc (ptr, sclass);
                return;
            }
        }
L34b1:
        if (sym == COMMA)
        {
            nxt_word();
        }
        else
        {
            break;
        }
    }       /* end of "for (;;)" at L32bd */

    if (need (SEMICOL))     /* _21 ( L34c2 ) */
    {
        junk ();
    }
}

void 
argdef ()
{
    /* 18 bytes storage */
    int sclass, type;
    dimnode *tdp, *dimptr;
    int size, stemp, temp;
    symnode *ptemp;
    elem *eptr;
    register symnode *ptr;

    switch ((sclass = setclass()))
    {
        case 0:         /* L34f6 */
            sclass = AUTO;      /* 13 */
            break;
        case REG:       /* 16 */
            break;
        default:        /* L34eb */
            reprterr ("argument storage");
            sclass = AUTO;      /* 13 */
            break;
    }

    if (!(type = settype (&size, &dimptr, &eptr)))        /* L3509 */
    {
        type = INT;
    }

    /* Don't know if this for loop is correct, but it's for the
     * go to L3523 preceding L3614
     */

    for (;;)
    {
        tdp = dimptr;                  /* L3523 */
        temp = declarator (&ptemp, &tdp, type);
        ptr = ptemp;
        
        if ((isftn (temp)) || (temp == STRUCT) || (temp == USTRUCT))
        {
            reprterr ("argument error");    /* go to L3595 */
            goto L35f8;
        }
        else
        {
            if (isary (temp))
            {
                temp = incref (decref (temp));   /* go to L358a */
            }
            else
            {
                if (temp == FLOAT)
                {
                    temp = DOUBLE;
                }
            }

            if (ptr == 0)
            {
                noidentf ();
                goto L35f8;
            }
        }

        stemp = chkreg (sclass, temp);       /* L359b */

        switch (ptr->storage)
        {
            case 11:    /* L35af */
                ptr->type = temp;
                ptr->storage = stemp;
                ptr->x.elems = eptr;       /* cast correct?? */
                
                if (!(sizeup (ptr, tdp, size)))
                {
                    sizundef ();
                }

                break;

            case AUTO:   /* L35d3 */ /*13*/
            case REG:   /* L35d3 */ /*16*/
                multdef ();
                break;

            default:
                reprterr ("not an argument");
                break;
        }

L35f8:
        if (sym == ASSIGN)
        {
            cant_init ();
        }

        if (sym == COMMA)
        {
            nxt_word ();
        }
        else
        {
            break;
        }
    }       /* end for (;;) loop */

    if (need (SEMICOL))     /* L3614 */     /* else L3876 */
    {
        junk ();
    }
}

/* ************************************************************** *
 * blkdef ()                                                       *
 * Apparently defines a label within a block                      *
 * ************************************************************** */

void 
blkdef ()
{
    int sclass, type, temp;
    dimnode *dimptr;
    int size;
    expnode *ep;
    symnode *ptemp;
    elem *eptr;
    initnode *i;
    register symnode *ptr;

    switch (sclass = setclass())
    {
        case DIRECT:      /* 33 */
            reprterr ("storage error");
        case 0:     /* Default type is "auto" */
            sclass = AUTO;     /* 13 */
    }

    if (!(type = settype(&size, &dimptr, &eptr)))
    {
        type = INT;
    }

    for (;;)        /* L3673 */
    {
        int stemp, ssize;
        dimnode *tdp;

        tdp = dimptr;
        temp = declarator (&ptemp, &tdp, type);
        
        if (!(ptr = ptemp))     /* else L36af */
        {
            if ((temp != STRUCT) && (temp != UNION))        /* else L371a */
            {
                noidentf ();       /* go to L371a */
            }

            goto L3855;
        }

        if ((isftn (temp)) || (sclass == EXTERN))  /*L36af*/  /*else L36fb*/
        {
            if (!ptr->type)    /* L36c4 */    /* else L36e9 */
            {
                ptr->type = temp;
                ptr->storage = EXTERN;    /* 14 */
                ptr->blklev = 0;
                ptr->x.elems = eptr;        /* cast correct?? */
                sizeup (ptr, tdp, size);
            }
            else
            {
                declrcmp (ptr, temp, eptr);    /* L36e9 */
            }
                
            goto L3855;
        }

        stemp = chkreg (sclass, temp);      /* L36fb */

        if (ptr->type)     /* else L3727 */
        {
            if (ptr->blklev == blklev)   /* else L3720 */
            {
                multdef ();
                goto L3855;
            }

            pushdown (ptr);     /* copy ptr to G18Current, null ptr */
        }

        ptr->type = temp;           /* L3727 */
        ptr->storage = stemp;       /* was EXTERN (switched from L36c4 */
        ptr->x.elems = eptr;    /* cast correct?? */
        ptr->blklev = blklev;            /* ??? Parentheses depth ??? */
        ptr->snext = vlist;
        vlist = ptr;
        
        if (!(ssize = sizeup (ptr, tdp, size)))
        {
            if (sym != ASSIGN)
            {
                sizundef ();
            }
        }

        switch (stemp)
        {
            case AUTO: /* L3761 */
                stlev -= ssize;
                ptr->offset = stlev;
                break;
            case STATICD: /* L376b */
            case STATIC: /* L376b */
                ptr->offset = ++LblNum;
                break;
        }

        if (sym == ASSIGN)   /* else L3824 */       /* L3787 */
        {
            if ((stemp == STATIC) || (stemp == STATICD))   /* else L37b4 */
            {
                initialize (ptr, stemp, temp);    /* go to L3858 */
            }
            else
            {
                nxt_word ();      /* L37b4 */

                if ((!(isary (temp))) && (temp != STRUCT) &&
                                    (ep = parsexp (2)))   /* else L381f */
                {
                    if (SomeCurnt)  /* else L37f3 */
                    {
                        SomeCurnt = (i = SomeCurnt)->initnext;
                        i->initnext = 0;
                    }
                    else
                    {
                        i = addmem (sizeof (initnode));
                    }

                    i->initp = ep;
                    i->initname = ptr;

                    if (initlist)
                    {
                        initlast->initnext = i;
                    }
                    else
                    {
                        initlist = i;
                    }

                    initlast = i;
                }
                else
                {
                    cant_init ();   /* L381f */
                }
            }
        }
        else
        {
            switch (stemp)
            {
                case STATIC:     /* L3828 */ /*15*/
                case STATICD:
                    rmbnolbl (ptr->offset, ssize, ((stemp == STATICD)));
                    break;
                default:            /* L3858 */
                    break;
            }
        }

L3855:
        if (sym != COMMA)    /* L3858 */
        {
            break;
        }

        nxt_word ();
    }       /* End of the for (;;) loop holding 6 bytes of data */

    need (SEMICOL);
}

int
#ifndef COCO
declrcmp (symnode *ptr, int type, elem *eptr)
#else
declrcmp (ptr, type, eptr)
    register symnode *ptr;
    int type;
    struct memberdef *eptr;
#endif
{
    if ((ptr->type != type) ||
            ((type == STRUCT) && (ptr->x.elems != eptr)))
    {
        reprterr ("declaration mismatch");
        return 1;
    }

    return 0;
}

int
#ifndef COCO
chkreg (int sclass_result, int fty)
#else
chkreg (sclass_result, fty)
    int sclass_result;
    int fty;
#endif
{
    if (sclass_result == REG)       /* else L3900 */
    {
        if (RegClsDpth < 1)  /* else L38fb */
        {
            switch (fty)
            {
                default:    /* L38cb */
                    if (!isptr (fty))
                    {
                        return AUTO;
                    }

                case INT:     /* L38d6 */
                case UNSIGN:
                    return ((++RegClsDpth == 1) ? UREG : YREG);
            }
        }

        return AUTO;
    }

    return sclass_result;
}

/* ************************************************************ *
 * newfunc () - Process a single function                    *
 * ************************************************************ */

void
#ifndef COCO
newfunc (symnode *fptr, int sclass)
#else
newfunc (fptr, sclass)
    symnode *fptr;
    int sclass;
#endif
{
    register symnode *p1;
    int offset;
    int stemp;
    symnode *p2;
    char *cp;
    int prlab;

    blklev = 1;
    D0033 = RegClsDpth = stlev = maxpush = sp = 0;

    /* Get parameter definitions */

    while (sym != LBRACE)     /* L3924 */
    {
        argdef ();
    }

    cp = fptr->sname;

    if (doprofil)
    {
        prtprofil (cp, (prlab = ++LblNum));
    }

    prtstkchk (cp, (sclass != STATIC), prlab);
    p1 = arglist;
    offset = 4;

    while (p1)
    {
        int size;     /* 3974 */

        p1->offset = offset;
        
        switch (p1->type)
        {
            case LONG:      /* L397e */
            case FLOAT:      /* L397e */
                size = 4;
                break;
            case DOUBLE:      /* L3983 */
                size = 8;
                break;
            case CHAR:      /* L3988 */
                ++(p1->offset);
            default:
                size = 2;
                break;
        }

        switch ((stemp = p1->storage))
        {
            case UREG:   /* L39b6 */
            case YREG:   /* L39b6 */
#ifdef __linux__
                gen (stemp, offset, 0);
#else
                gen (stemp, offset);
#endif
                break;
            case ARG:    /* L39c5 */
                p1->storage  = AUTO;     /* 13 */
                break;
        }

        offset += size;
        p1 = p1->snext;
    }

    p2 = arglist;
    arglist = 0;
    block ();

    clear (&p2);
    clear (&labelist);

    if ( lastst != RETURN)
    {
        gen ( RETURN, 0, 0);
    }

     lastst = 0;
    flgstkchk ();
    blklev = 0;

    if (sym == -1)
    {
        reprterr ("function unfinished");
    }

    nxt_word ();
}

void
block ()
{
    struct initstruct *i;
    symnode *varlist;
    int savlev;
    register expnode *p;

    varlist = vlist;
    vlist = 0;
    nxt_word ();
    ++blklev;
    savlev = stlev;

    while (issclass () || istype ())        /* L3a71 */
    {
        blkdef ();
    }

    if (maxpush > stlev)
    {
        maxpush = stlev;
    }

    sp = wrt_M (stlev);      /* L3a8c */

    while (initlist)       /* L3b0a */
    {
        i = initlist;     /* L3a9a */
        p = i->initp;
        p = newnode (NAME, 0, 0, i->initname, p->lno, p->pnt);
        p = newnode (ASSIGN, p, i->initp, 0, p->lno, p->pnt);
        reltree (transexp (optim (p)));
        i = i->initnext;
        initlist->initnext = SomeCurnt;
        SomeCurnt = initlist;
        initlist = i;
    }

    while ((sym != RBRACE) && (sym != -1))
    {
        statement ();
    }

    clear (&vlist);
    vlist = varlist;
    --blklev;
    stlev = savlev;

    sp = ( lastst != RETURN) ? wrt_M (savlev) : savlev;
}

void
#ifndef COCO
declist (symnode **list)
#else
declist (list)
    symnode **list;
#endif
{
    symnode *last;
    register symnode *ptr;

    *list = 0;

    /* Loop for each comma-separated variable defined on this "line" */
    do
    {
        nxt_word ();

        if (sym == RPAREN)        /* else L3bda */
        {
            break;
        }

        if (sym == NAME)      /* else L3bcd */
        {
            ptr = (symnode *)symval;

            if (ptr->storage == ARG)
            {
                reprterr ("named twice");
            }
            else
            {
                if (ptr->type)
                {
                    /* copy ptr to G18Current, null ptr */
                    pushdown (ptr);
                }
            }

            ptr->type = INT;     /* L3b9e */
            ptr->storage = ARG;
            ptr->blklev = 1;
            ptr->size = 2;
            
            if (*list)
            {
                /* Just to get it to compile */
                last->snext = ptr;
            }
            else
            {
                *list = ptr;    /* L3bbe */
            }

            ptr->snext = 0;
            last = ptr;
            nxt_word ();
        }
        else
        {
            noidentf ();
        }

    } while (sym == COMMA);          /* end for (;;) loop */

    need (RPAREN);     /* L3bda */
}

/* ************************************************************ *
 * setclass () - Get the word following a storage class       *
 *      definition.  I.E. if it's a storage class, (extern,     *
 *      static, auto, etc,), get the following word(s), which   *
 *      define the variable name                                *
 * Returns: If a storage class, the original FT_type            *
 *              (modified if DP)                                *
 *          NULL if not a type definition                       *
 *          DP data = old FT_ + 2                               *
 * nxt_word () has also been run to retrieve the data type      *
 * ************************************************************ */

int 
setclass ()
{
    int class;

    /* If it's a storage class, i.e. extern, static, auto, etc */

    if (issclass ())     /* else L3c2f */
    {
        class = symval;
        nxt_word ();

        /* Direct Page reference = old FT_ + 2 */

        if ((sym == KEYWORD) && (symval == DIRECT))    /* else L3c2b */
        {
            switch (class)
            {
                case STATIC:    /* L3c12 */
                    class =  STATICD;
                    break;
                case EXTERN:    /* L3c17 */
                    class = EXTERND;
                    break;
            }

            nxt_word ();
        }

        return class;
    }
    else
    {
        return 0;
    }
}

/* ******************************************************************** *
 * settype () - process a variable definition                         *
 * On entry, we have the first word in a variable definition.  It could *
 * be something like "short", or "long", (optionally followed by "int"  *
 * or simply "int", or "char", or a user-defined type                   *
 *                                                                      *
 * Returns: Updated FT_type for the variable (lbl_fttyp)                *
 *          sets siz (in calling function) to size of variable          *
 *          sets p2  (in calling function) to 0                         *
 * On return, we have the variable name                                 *
 * ******************************************************************** */

int 
#ifndef COCO
settype (int *siz, dimnode **dimptr, elem **ellist)
#else
settype (siz, dimptr, ellist)
    int *siz;
    dimnode **dimptr;
    elem **ellist;
#endif
{
    symnode *tagptr;
    int offset, msize, mtype, savflg, dtype;
    dimnode *dptr;
    int s;
    elem *eptr, *elast, *elocal;
    int type = 0;
    int tsize = INTSIZ;

    register symnode *ptr;

    *ellist = 0;

    /* On entry here, we have some type of label.  It's either a
     * data type (int, char, etc), or a function name */

    if (sym == KEYWORD)             /* else L3f51 */
    {
        switch ((type = symval))    /* L3f0f */
        {
            case SHORT:              /* L3c61 */
                type = INT; /* Promote to "int" fall through to next */

            case UNSIGN:           /* L3c66 */
                nxt_word ();

                
                if ((sym == KEYWORD) && (symval == INT))  /* else L3f79 */
                {
                    nxt_word ();
                }

                break;

            case CHAR:      /* L3c7f */
                tsize = CHARSIZ;
            case INT:      /* L3cb7 */
                nxt_word ();
                break;

            case LONG:      /* L3c84 */
                nxt_word ();
                tsize = LONGSIZ;
                
                /* Check for "long int" or "long float" */

                if (sym == KEYWORD)
                {
                    if (symval == INT)
                    {
                        nxt_word ();
                    }
                    else
                    {
                        if (symval == FLOAT)
                        {
                            /* "long float" means double */
                            type = DOUBLE;
                            tsize = DBLSIZ;
                            nxt_word ();
                        }
                    }
                }
                break;

            case DOUBLE:      /* L3ca8 */
                type = DOUBLE;
                tsize = DBLSIZ;
                nxt_word ();
                break;

            case FLOAT:      /* L3cb2 */
                tsize = FLOATSIZ;
                nxt_word ();
                break;

                /* They had "default" up here.  See what happens */
            default:     /* L3cbd */
                type = 0;
                break;

                /* Begin struct */
            case UNION:      /* L3cc4 */
            case STRUCT:
                tsize = offset = 0;
                ++Struct_Union;     /* Go into "struct mode" for FindLbl() */
                tagptr = 0;
                nxt_word ();        /* get struct name or "{" */
                --Struct_Union;     /* Get back out of "struct mode" */

                /* Process struct name if applicable */

                if (sym == NAME)    /* else L3d5d */
                {           /* We have a struct name */
                    tagptr = (symnode *)symval;      /* Pointer to LBLDEF */

                    /* FindLbl sets type to 0 for new labels */

                    if (!(tagptr->type))
                    {
                        tagptr->type = USTRUCT;
                        tagptr->storage = STRTAG;     /* 8 */
                    }
                    else
                    {
                        /* "struct <non-struct>"  */

                        if (tagptr->storage != STRTAG)
                        {
                            reprterr ("name clash");
                        }
                    }
                    
                    nxt_word ();        /* L3d1b */

                    if (sym != LBRACE)
                    {
                        if (tagptr->type == STRUCT)
                        {
                            *siz = tagptr->size;
                            *ellist = tagptr->x.elems;
                            return STRUCT;
                        }                        

                        *siz = (int)tagptr;   /* L3d45 */
                        return USTRUCT;
                    }

                    /* Cannot have a definition name matching member name */
                    /* How does this differ from above ??? */

                    if (tagptr->type == STRUCT)
                    {
                        multdef ();
                    }
                }       /* end process struct name */

                if (sym != LBRACE)    /* L3d5d */
                {
                    reprterr ("struct syntax");
                    break;
                }

                ++Struct_Union;        /* L3d73 */

                do           /* Loop for each struct member */
                {
                    savflg = Struct_Union;    /* L3d7a */
                    Struct_Union = 0;
                    nxt_word ();
                    Struct_Union = savflg;

                    if (sym == RBRACE)    /* else L3ee2 */
                    {
                        break;
                    }

                    /* Process member - recurse into self (this function) */

                    mtype = settype ( &msize, &dptr, &elocal);

                    /* At this point, mtype = FT_code for member variable
                     * sym contains C_type for the character or name
                     */

                    while (1)
                    {
                        dimnode *tdptr;
                        symnode *ptemp;

                        tdptr = dptr;

                        if (sym == SEMICOL)    /* else L3ecc */
                        {
                            break;
                        }

                        ++blklev;
                        dtype = declarator (&ptemp, &tdptr, mtype);
                        ptr = ptemp;
                        --blklev;

                        if (ptr == 0) /* else L3df1 */
                        {
                            noidentf ();
                            goto L3ec1;
                        }

                        if (ptr->type)     /* L3df1 */   /* else L3e26 */
                        {
                            if (ptr->blklev == blklev)   /*else L3e1f */
                            {
                                if ((ptr->type != dtype) ||
                                    (ptr->storage != MOS) ||
                                    (ptr->offset != offset))
                                {
                                    reprterr ("struct member mismatch");
                                }
                            }
                            else
                            {
                                pushdown (ptr);     /* L3e1f */
                            }
                        }

                        if ( dtype == USTRUCT) /* L3e26 */
                        {
                            reprterr ("undefined structure");
                        }

                        ptr->type = dtype;
                        ptr->storage = MOS;
                        ptr->offset = offset;
                        ptr->x.elems = elocal;     /* cast correct?? */
                        
                        if (s = sizeup (ptr, tdptr, msize))
                        {       /* else L3e84 */
                            if (type == STRUCT)
                            {
                                tsize = (offset += s);
                            }
                            else
                            {
                                tsize = (s > tsize ? s : tsize);
                            }
                        }
                        else
                        {
                            sizundef ();
                        }

                        ptr->blklev = blklev;    /* L3e87 */
                        ptr->snext = vlist;
                        vlist = ptr;

                        if (type == STRUCT)    /* else L3ec4 */
                        {
                            eptr = addmem (sizeof (elem));
                            eptr->element = ptr;
                            
                            if (*ellist)
                            {
                                elast->strnext = eptr;
                            }
                            else
                            {
                                *ellist = eptr;    /* L3eb6 */
                            }

                            elast = eptr;
                        }
L3ec1:
                        if (sym != COMMA)
                        {
                            break;
                        }

                        nxt_word ();
                        continue;

                    }   /* End of while (1) loop */
                } while (sym == SEMICOL);  /* L3ed8 */

                --Struct_Union;    /* L3ee2 */

                if (tagptr)
                {
                    tagptr->size = tsize;
                    tagptr->type = STRUCT;
                    tagptr->x.elems = *ellist;
                }

                need (RBRACE);
                break;              /* End struct def */
        }
    }
    else        /* NOT BUILTIN */
    {
        /* L3f51 */
        if ((sym == NAME) && (((ptr = (symnode *)symval)->storage) == TYPEDEF))
        {
            *siz = ptr->size;
            *dimptr = ptr->dimptr;
            *ellist = ptr->x.elems;

            nxt_word ();
            return ptr->type;
        }
    }

    *siz = tsize;
    *dimptr = 0;
    return type;
}

/* ************************************************************** *
 * declarator () -                                                *
 * Passed:  p1 - POINTER to variable's LBLDEF *                   *
 *          p2 - pointer to                                       *
 *          FT_type of current "word" (for local use)             *
 * Returns: FT_type                                               *
 * ************************************************************** */

int
#ifndef COCO
declarator (symnode **ptr, dimnode **dptr, int bastype)
#else
declarator (ptr, dptr, bastype)
    symnode **ptr;
    dimnode **dptr;
    int bastype;
#endif
{
    register dimnode *tempdim;
    int dtype,
        savmos;
    dimnode *p1;
    int count;
    dimnode *p;
    auto dimnode *dummy;

#ifdef COCO
    dtype = *ptr = 0;
#else
    dtype = 0;
    *ptr = 0;
#endif

    /* Get past any pointer states (if any) */

    while (sym == STAR)    /* ??? Increase pointer count */
    {
        dtype = incref (dtype);
        nxt_word ();
    }

    if (sym == NAME)
    {
        *ptr = (symnode *)symval;        /* variable name's LBLDEF * */
        nxt_word ();
    }
    else
    {
        if (sym == LPAREN)
        {
            nxt_word ();
            ++blklev;
            bastype = declarator (ptr, dptr, bastype);      /* call self */
            --blklev;
            need (RPAREN);
        }
    }

    if (sym == LPAREN)        /* else L4036 */
    {
        dtype = ((dtype << 2) + FUNCTION);

        if (blklev == 0)
        {
            declist (&arglist);
        }
        else
        {   /* We are inside a set of parentheses */
            declist (&dummy);
            clear (&dummy);        /* go to L40b9 */
        }
    }
    else
    {
#ifdef COCO
        tempdim = count = p1 = 0;       /* L4036 */
#else
        tempdim = p1 = 0;
        count = 0;
#endif

        savmos = Struct_Union;
        Struct_Union = 0;

        while (sym == LBRACK)     /* L409d */
        {
            dtype = (dtype << 2) + ARRAY;      /* L4049 */
            nxt_word ();
            p = (dimnode *)addmem (sizeof (dimnode));

            if ((count == 0) && (sym == RBRACK))
            {
                p->dim = 0;  
            }
            else
            {
                p->dim = constexp (0);  /* L4073 */
            }

            if (p1)     /* L407c + 1 */
            {
                p1->dptr = p;
            }
            else
            {
                tempdim = p;    /* L4088 */
            }

            p1 = p;
            need (RBRACK);
            ++count;
        }

        Struct_Union = savmos;

        if (tempdim)
        {
            p->dptr = *dptr;
            *dptr = tempdim;
        }
    }

    return (shiftin (bastype, dtype));
}

int
#ifndef COCO
shiftin(int p1, int p2)
#else
shiftin (p1, p2)
    int p1;
int p2;
#endif
{
    int v0 = p1;

    while (v0 & XTYPE)
    {
        v0 >>= 2;
        p2 <<= 2;
    }

    return (p1 + p2);
}

int
#ifndef COCO
sizeup (register symnode *ptr, dimnode *dimptr, int size)
#else
sizeup (ptr, dimptr, size)
    register symnode *ptr;
    dimnode *dimptr;
    int size;
#endif
{
    int temp;
    int n;

    switch ((temp = ptr->type) & 0x0f)
    {
        case CHAR:      /* L4117 */
            n = CHARSIZ;
            break;
        case INT:      /* L411c */
        case UNSIGN:      /* L411c */
            n = INTSIZ;
            break;
        case LONG:      /* L4121 */
        case FLOAT:      /* L4121 */
            n = LONGSIZ;
            break;
        case DOUBLE:      /* L4126 */
            n = DBLSIZ;
            break;
        case UNION:      /* L412b */
        case STRUCT:      /* L412b */
            n = size;
            break;
        case 10:     /* L412f */
            n = 0;
            break;
    }

    ptr->size = n ? n : size;
    return getsize (temp, n, (ptr->dimptr = dimptr));
}

int
#ifndef COCO
getsize (int t, int size, register dimnode *dptr)
#else
getsize (t, size, dptr)
    int t;
    int size;
    register dimnode *dptr;
#endif
{
    int n;

    if ((isptr (t)) || (isftn (t)))
    {
        return 2;   /* L41ac */
    }

    if (isary (t))        /* L41b2 */   /* else L41ff */
    {
        n = 1;

        do
        {
            n *= dptr->dim;    /* L41c2 */
            dptr = dptr->dptr;
        } while (isary (t = (decref (t))));     /* FIXED I think */

        return (n * ((isptr (t)) ? POINTSIZE : size));
    }
    else
    {
        return size;
    }
}

void
#ifndef COCO
clear (symnode **list)
#else
clear (list)
    symnode **list;
#endif
{
    symnode  *p, **pp;
    symnode  *next;
    char      err[60];

    register symnode *this = *list;

    while (this)      /* L42c1 */
    {
        next = this->snext;

        if ((this->type == LABEL) && !(this->x.labflg & DEFINED))
        {
            reprterr (strncat (strcpy (err, "label undefined : "),
                        (this->sname), 8));
        }

        switch (this->storage)
        {
            case UREG:    /* L4259 */  /* 'o' */
            case YREG:    /* L4259 */  /* 'v' */
                --RegClsDpth;
                break;
        }

        pp = (symnode **)this->downptr;     /* L426e */

        if ((pp > LblPtrLow) && (pp < LblPtrEnd))  /* else L4289 */
        {
            /* Make this the base of the current LblTree ?? */
            pullup (this);      /* go to L42be */
        }
        else
        {
            if ((this == *pp))          /* L4289 */
            {
                *pp = this->hlink;
            }
            else
            {
                for (p = *pp; p->hlink != this; p = p->hlink);
            
                p->hlink = this->hlink;    /*L42a2 */
            }

            this->hlink = freesym;      /* L42b7 */
            freesym = this;
        }

        this = next;
    }       /* end "while" */

    *list = 0;
}

void
sizundef ()
{
    reprterr ("cannot evaluate size");
}

void
noidentf ()
{
    reprterr ("identifier missing");
}
