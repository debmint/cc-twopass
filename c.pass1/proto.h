/* ../../../c.pass1/p1_01.c */
void null_lbldef(LBLDEF *srcdef);
void fill_g18(LBLDEF *dstdef);
void mem_cp(char *_src, char *_dest, int siz);
void prnt_filname(void);
int err_quit(char *p1);
void multdef(void);
void reprterr(char *_str);
void comperr(int *p1, char *_errmsg);
void err_lin(CMDREF *p1, char *_errmsg);
void showline(int _linpos, char *txt, int _line);
void displerr(char *pmpt, char *val);
void e_putlin(char *str);
void e_putc(char ch);
void L0393(CMDREF *p1);
void mak_curnt(CMDREF *p1);
void CmdrefCpy(CMDREF *p1, int p2);
int isvariable(void);
int is_sc_specifier(void);
int MSBrshft2(int p1);
int incptrdpth(int p1);
int L049b(int p1);
int L04b0(int *p1);
int lookfor(int needed);
void cmma_rbrkt(void);
/* ../../../c.pass1/p1_02.c */
CMDREF *L0580(int p1);
CMDREF *L0694(void);
CMDREF *L09f4(void);
CMDREF *L0a4f(int parm1);
int is_math(void);
int do_math(int parm1, int parm2, int parm3);
CMDREF *L0d47(void);
CMDREF *add_cmdref(int __ccode, CMDREF *_oldpt, CMDREF *p3, int myval, int __myline, char *_line_pos);
void exprmsng(void);
int L0e29(CMDREF **p1);
/* ../../../c.pass1/p1_03.c */
CMDREF *L0f18(CMDREF *curntcmd);
CMDREF *L1005(CMDREF *regptr);
int L1323(CMDREF *regptr);
void divby_0(void);
CMDREF *L1382(CMDREF *oldref);
void L1f8e(CMDREF *regptr);
int cktypnumeric(CMDREF *c_ref);
int do_cast(CMDREF *ptr, int to_typ);
int L2340(CMDREF *cref_1, CMDREF *cref_2);
CMDREF *L23c4(int p1, int p2, int p3, CMDREF *p4);
void L2463(CMDREF *regptr, int p2);
void ck_declared(CMDREF *regptr);
int L2502(CMDREF *regptr, int *p2, int *p3);
int get_ftty(CMDREF *regptr);
void L25e6(CMDREF *p1);
int iswordorlong(int tstval);
void notintegral(CMDREF *c_ref);
/* ../../../c.pass1/p1_04.c */
void do_loops(void);
void do_if(void);
void do_while(void);
void do_swtch(void);
void do_case(void);
void do_deflt(void);
void no_switch(void);
void do_do(void);
void do_for(void);
void do_retrn(void);
void do_break(void);
void do_contin(void);
void do_goto(void);
void L2fe9(void);
CMDREF *L302b(void);
LBLDEF *L3082(int p1);
CMDREF *L30ab(CMDREF *regptr);
LBLDEF *L30e7(void);
LBLDEF *L310e(void);
void L3140(LBLDEF *regptr, int p2, int p3, int p4);
/* ../../../c.pass1/p1_05.c */
void L3227(void);
void L34d6(void);
void L3628(void);
int declrcmp(LBLDEF *regptr, int p2, struct memberdef *p3);
int L38af(int sclass_result, int fty);
void dofunction(LBLDEF *my_lbl, int myftyp);
void L3a4c(void);
void do_parentheses(LBLDEF **p1);
int getSC_word(void);
int do_lblnam(int *siz, struct memberdef **p2, struct memberdef **lastmember);
int L3f8a(LBLDEF **lbl_def, struct memberdef **p2, int ft_type);
int L40ca(int p1, int p2);
int L4100(LBLDEF *regpt, struct memberdef *p2, int oldsize);
int L418a(int p1, int p2, CMDREF *regptr);
void L4204(LBLDEF **p1);
void sizundef(void);
void noidentf(void);
/* ../../../c.pass1/p1_06.c */
void L4432(LBLDEF *lblstruct, int _ftTyp, int p3);
int L4570(int ftType, LBLDEF *regptr, LBLDEF *p3, int readflg);
void L474e(int p1);
int L4772(int p1);
void L4913(int valu, int f_type);
void cant_init(void);
void find_sep(void);
/* ../../../c.pass1/p1_07.c */
void prtlbl(char *lbnm, int isglbl);
void prtspstr(char *str);
void prt_not_used(char *str);
void prntCR(void);
void printchr(int ch);
void prntstring(char *str);
void prntdgt(int num);
void prntw_l(int wrd);
void prtlcllbl(int nbr);
void wrtunderscore(int nbr);
void prtlbnm(char *lbl);
int wrt_M(int nbr);
void prt_4b5e(int parm, int par2, int par3);
void prntstar(void);
void prntfnam(char *str);
CMDREF *prt_4c1b(CMDREF *parm);
CMDREF *prt_4c2c(CMDREF *p1, int p2, int p3, int p4);
CMDREF *prt_4c4f(CMDREF *cmdrf);
void prt_4c68(int addflg, CMDREF *cmdrf, int p3, int p4, int p5);
int calc_value(CMDREF *wp, int _flg);
void wrtallinfo(CMDREF *wp);
void wrt_info(CMDREF *wp);
void prntnuls(int *valu, int countflg);
int prt_float(char *data_val, int f_type);
int prt_509e(CMDREF *p1, int p2);
/* ../../../c.pass1/p1_08.c */
void nxt_word(void);
void tblsetup(void);
void fget_lbl(char *_dst);
int islblchr(int pos);
LBLDEF *FindLbl(char *fnc);
void inizFTbl(char *name, int val);
unsigned int str_sum(char *nam);
void *addmem(int siz);
int str2num(int p1, void *dest_val);
void do_squot(void);
void do_dquot(void);
void addstrchr(int p1);
void prnt_rzb(int valu);
int dobkslsh(void);
int is_octal(char ch);
int is_hex(char ch);
/* ../../../c.pass1/p1_09.c */
void initbuf0(void);
void skipblank(void);
void getnxtch(void);
char prepln(void);
int a_toi(char *cptr);
char *gtnxtlin(void);
/* ../../../c.pass1/p1_10.c */
void dumpstrings(void);
void rmbnolbl(int p1, int valu, int p3);
void globldata(LBLDEF *p1, int p2, int p3);
void localdata(LBLDEF *p1, int p2, int p3);
int lbl_rmb(LBLDEF *p1, int p2, char _colon);
void prtstkchk(char *funcnam, int p2, int p3);
void prtprofil(char *p1, int p2);
void flgstkchk(void);
void prnt_fcb(void);
void prnt_fdb(void);
void pr2stars(void);
void wdataflag(int p1);
void putc_e(void);
int seek0_FP(FILE *_fp);
void dumpstrs(void);
void quitcc(void);
/* ../../../c.pass1/p1_11.c */
int main(int argc, char **argv);
void quit_cc(void);
/* ../../../c.pass1/printf.c */
int _printf(char *fmt, int vals);
int _fprintf(FILE *fp, char *fmt, int vals);
int _sprintf(char *fp, char *fmt, int vals);
void L511b(char *fmt, int *_vals);
char *_dec2str(int _nmbr);
void todigit(char *str, int valu);
char *_hex2str(unsigned int _nbr);
void outputfld(char *strng, int fld_wdth);
void L5415(char *regpt, int str_lngth, int __fldwdth);
void sendchar(int p1);