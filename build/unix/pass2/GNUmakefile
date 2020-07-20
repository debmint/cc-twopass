vpath %.c = ../../../c.pass2
vpath %.h = ../../../c.pass2

CFLAGS = -g -m32 -I../../..
PROG =   c.pass2
OBJS =   p2_01.o tranexp.o p2_03.o p2_04.o printf.o codgen.o p2_07.o p2_08.o
RM =     rm -f
LFLAGS = -g -m32

$(PROG): $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o$(PROG)

$(OBJS):

clean:
	$(RM) $(PROG) $(OBJS)

proto:
	cproto ../../../c.pass2/*.c >../../../c.pass2/proto.h
