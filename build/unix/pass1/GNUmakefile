vpath %.c = ../../../c.pass1
vpath %.h = ../../../c.pass1

CFLAGS = -g -m32 -I../../..
#CFLAGS  = -g -m32 -DUNIX -DPTREE -DPROF -DREGCONTS \
        -Wall -Wno-incompatible-pointer-types -Wno-implicit-int \
        -Wno-implicit-function-declaration -Wno-parentheses \
        -Wno-return-type \
        -DCKEYSFILE=\"$(HOME)/.ckeys\"
PROG = c.pass1
OBJS = misc.o build.o optim.o stats.o declare.o inits.o \
	   p1_07.o printf.o lex.o get.o local.o cmain.o
RM = rm -f

$(PROG): $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o$(PROG)

$(OBJS): GNUmakefile

clean:
	$(RM) $(PROG) $(OBJS)

proto:
	cproto ../../../c.pass1/*.c >../../../c.pass1/proto.h
