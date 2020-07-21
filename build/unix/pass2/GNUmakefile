vpath %.c = ../../../c.pass2
vpath %.h = ../../../c.pass2

CFLAGS = -g -m32 -I../../..
PROG =   c.pass2
OBJS =   p2main.o tranexp.o bool.o longs.o floats.o \
		 printf.o codgen.o misc.o local.o
RM =     rm -f
LFLAGS = -g -m32

$(PROG): $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o$(PROG)

$(OBJS):

clean:
	$(RM) $(PROG) $(OBJS)

proto:
	cproto ../../../c.pass2/*.c >../../../c.pass2/proto.h
