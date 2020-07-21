RDIR = ../build/coco/pass2
SRCDIR = $(PWD)
CC = cc3

$(RDIR)/%.r: %.c

#CFLAGS = -i -dCOCO -v=/dd/defs
CFLAGS = -dCOCO
PROG = c.pass2

OBJS = p2main.r tranexp.r bool.r longs.r floats.r \
	   printf.r codgen.r misc.r local.r

RELS = $(RDIR)/p2main.r $(RDIR)/tranexp.r $(RDIR)/bool.r \
	   $(RDIR)/longs.r $(RDIR)/floats.r $(RDIR)/printf.r \
	   $(RDIR)/codgen.r $(RDIR)/misc.r $(RDIR)/local.r

STKS = $(RDIR)/p2main.r $(RDIR)/tranexp.r $(RDIR)/bool.r \
	   $(RDIR)/longs.r $(RDIR)/floats.r
	   
NOSTK = $(RDIR)/printf.r $(RDIR)/codgen.r $(RDIR)/misc.r $(RDIR)/local.r

$(PROG): $(STKS) $(NOSTK)
	cd $(RDIR);$(CC) $(LFLAGS) $(OBJS) -f=$(PROG); cd $(SRCDIR)

$(STKS):
	$(CC) $(CFLAGS) $(*F).c -r=$(RDIR)

$(NOSTK):
	$(CC) $(CFLAGS) $(*F).c -s -r=$(RDIR)

proto:
	cproto -f1 -DCOCO *.c >protoc.h
