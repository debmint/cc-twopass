RDIR = ../build/coco/pass2
SRCDIR = $(PWD)
CC = cc3

$(RDIR)/%.r: %.c

CFLAGS = -i -dCOCO -v=/dd/defs
PROG = c.pass2

OBJS = p2_01.r p2_02.r p2_03.r p2_04.r \
	   printf.r p2_06.r p2_07.r p2_08.r

RELS = $(RDIR)/p2_01.r $(RDIR)/p2_02.r $(RDIR)/p2_03.r $(RDIR)/p2_04.r \
	   $(RDIR)/printf.r $(RDIR)/p2_06.r $(RDIR)/p2_07.r $(RDIR)/p2_08.r

$(PROG): $(RELS)
	cd $(RDIR);$(CC) $(LFLAGS) $(OBJS) -f=$(PROG); cd $(SRCDIR)

$(RELS):
	$(CC) $(CFLAGS) $*.c -r=$(RDIR)

proto:
	cproto -f1 -DCOCO *.c >protoc.h
