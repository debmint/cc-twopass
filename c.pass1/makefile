RMA = rma
RLINK = rlink
RDIR = ../build/coco/pass1
SRCDIR = $(PWD)
CC = cc3

$(RDIR)/%.r: %.c

$(RDIR)/%.r: %.a
	$(RMA) $*.a -o=$(RDIR)/$*.r

#CFLAGS = -dCOCO -v=/dd/defs
CFLAGS = -dCOCO
PROG = c.pass1
OBJS = misc.r p1_02.r p1_03.r p1_04.r p1_05.r p1_06.r \
	   p1_07.r printf.r pp8.r p1_08.r p1_09.r p1_10.r pf.r cmain.r

RELS = $(RDIR)/misc.r $(RDIR)/p1_02.r $(RDIR)/p1_03.r $(RDIR)/p1_04.r \
	   $(RDIR)/p1_05.r $(RDIR)/p1_06.r $(RDIR)/p1_07.r printf.r \
	   $(RDIR)/pp8.r $(RDIR)/p1_08.r $(RDIR)/p1_09.r $(RDIR)/p1_10.r \
	   $(RDIR)/pf.r $(RDIR)/cmain.r

STKS = $(RDIR)/p1_02.r $(RDIR)/p1_03.r $(RDIR)/p1_04.r \
	   $(RDIR)/p1_05.r $(RDIR)/p1_06.r $(RDIR)/p1_07.r  \
	   $(RDIR)/pp8.r $(RDIR)/p1_08.r $(RDIR)/pf.r

NOSTK = $(RDIR)/misc.r $(RDIR)/p1_09.r $(RDIR)/p1_10.r $(RDIR)/cmain.r \
		$(RDIR)/printf.r

$(PROG): $(STKS) $(NOSTK)
	cd $(RDIR);$(CC) $(LFLAGS) $(OBJS) -f=$(PROG); cd $(SRCDIR)

$(STKS):
	$(CC) $(CFLAGS) $(*F).c -r=$(RDIR)

$(NOSTK):
	$(CC) $(CFLAGS) -s $(*F).c -r=$(RDIR)

proto:
	cproto -f1 -DCOCO *.c >protoc.h
