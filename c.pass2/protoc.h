/* codgen.c */
int *getmem();
int L3203();
int gen();
int get_regname();
int L39d9();
int L3bc2();
int L3d90();
int L3dd0();
int L3e51();
int L3e6e();
int L3e8d();
int L3ea4();
int doref();
int addoff();
int L40d0();
char *br_rel_op();
int ot();
int L43d1();
int newln();
int prnt_chr();
int prnt_strng();
int od();
int label();
int prt_loclbl();
int prt_lblnam();
int modstk();
int prt_label();
int lea_reg();
int outstr();
/* p2_01.c */
int main();
expnode *L0787();
int L095c();
int openoutpth();
int L0a16();
int psh_stk();
int err_exit();
/* p2_03.c */
int tranbool();
int L20ed();
int L22ca();
int p2_03_notused();
int L2323();
int L2466();
int L249e();
int L24e6();
int lload();
int tranlexp();
int L28fb();
int L294b();
/* p2_04.c */
int dload();
int trandexp();
/* p2_07.c */
int error();
int outofmemory();
int comperr();
int L487f();
int L4896();
long *lng2_flacc();
int showerr();
int reltree();
int release();
int L4acd();
int p051_notused();
int isbin();
int ncpystr();
/* p2_08.c */
int prt_fdb();
int prt_funcbegin();
int prtstkreq();
int prtvsctbgn();
int prtendsect();
int L4c61();
int L4c92();
/* printf.c */
int printf();
int fprintf();
int sprintf();
int L2d8c();
char *_dec2str();
int todigit();
char *_hex2str();
int outputfld();
int L5415();
int sendchar();
/* tranexp.c */
int lddexp();
int ldxexp();
int loadexp();
int doload();
expnode *tranexp();
int tranbinop();
int isashift();
int dobool();
int doquery();
int docall();
int isdleaf();
int regandcon();
int isxleaf();
int isaddress();
int getinx();
int doass();
int assop();
int stackx();
int dostar();
int dotoggle();
int loadxexp();
int tranxexp();
int is_regvar();
