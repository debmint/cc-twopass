vpath %.c = ../../../c.pass1
vpath %.h = ../../../c.pass1

CFLAGS = -I../../..
PROG = c.pass1
OBJS = p1_01.o p1_02.o p1_03.o p1_04.o p1_05.o p1_06.o \
	   p1_07.o printf.o p1_08.o p1_09.o p1_10.o p1_11.o
RM = rm -f

$(PROG): $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o$(PROG)

$(OBJS):

clean:
	$(RM) $(PROG) $(OBJS)

proto:
	cproto ../../../c.pass1/*.c >../../../c.pass1/proto.h
