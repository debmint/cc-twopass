RDIR = ../build/coco/pass2
SRCDIR = $(PWD)
CC = cc3

$(RDIR)/%.r: %.c

#CFLAGS = -i -dCOCO -v=/dd/defs
CFLAGS = -dCOCO
PROG = c.pass2

OBJS = p2_01.r tranexp.r p2_03.r p2_04.r \
	   printf.r codgen.r p2_07.r p2_08.r

RELS = $(RDIR)/p2_01.r $(RDIR)/tranexp.r $(RDIR)/p2_03.r $(RDIR)/p2_04.r \
	   $(RDIR)/printf.r $(RDIR)/codgen.r $(RDIR)/p2_07.r $(RDIR)/p2_08.r

STKS = $(RDIR)/p2_01.r $(RDIR)/tranexp.r $(RDIR)/p2_03.r $(RDIR)/p2_04.r
	   
NOSTK = $(RDIR)/printf.r $(RDIR)/codgen.r $(RDIR)/p2_07.r $(RDIR)/p2_08.r

$(PROG): $(STKS) $(NOSTK)
	cd $(RDIR);$(CC) $(LFLAGS) $(OBJS) -f=$(PROG); cd $(SRCDIR)

$(STKS):
	$(CC) $(CFLAGS) $(*F).c -r=$(RDIR)

$(NOSTK):
	$(CC) $(CFLAGS) $(*F).c -s -r=$(RDIR)

proto:
	cproto -f1 -DCOCO *.c >protoc.h
