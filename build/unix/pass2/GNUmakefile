vpath %.c = ../../../c.pass2
vpath %.h = ../../../c.pass2

CFLAGS = -I../../..
PROG = c.pass2
OBJS = p2_01.o p2_02.o p2_03.o p2_04.o printf.o p2_06.o \
	   p2_07.o p2_08.o
RM = rm -f

$(PROG): $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o$(PROG)

$(OBJS):

clean:
	$(RM) $(PROG) $(OBJS)

proto:
	cproto ../../../c.pass2/*.c >../../../c.pass2/proto.h
