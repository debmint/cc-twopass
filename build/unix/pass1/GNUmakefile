vpath %.c = ../../../c.pass1
vpath %.h = ../../../c.pass1

CFLAGS = -I../../..
PROG = c.pass1
OBJS = misc.o p1_02.o p1_03.o p1_04.o p1_05.o p1_06.o \
	   p1_07.o printf.o p1_08.o p1_09.o p1_10.o cmain.o
RM = rm -f

$(PROG): $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o$(PROG)

$(OBJS):

clean:
	$(RM) $(PROG) $(OBJS)

proto:
	cproto ../../../c.pass1/*.c >../../../c.pass1/proto.h
