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
OBJS = misc.r build.r optim.r stats.r declare.r inits.r \
	   p1_07.r printf.r pp8.r lex.r get.r local.r pf.r cmain.r

RELS = $(RDIR)/misc.r $(RDIR)/build.r $(RDIR)/optim.r $(RDIR)/stats.r \
	   $(RDIR)/declare.r $(RDIR)/inits.r $(RDIR)/p1_07.r printf.r \
	   $(RDIR)/pp8.r $(RDIR)/lex.r $(RDIR)/get.r $(RDIR)/local.r \
	   $(RDIR)/pf.r $(RDIR)/cmain.r

STKS = $(RDIR)/build.r $(RDIR)/optim.r $(RDIR)/stats.r \
	   $(RDIR)/declare.r $(RDIR)/inits.r $(RDIR)/p1_07.r  \
	   $(RDIR)/pp8.r $(RDIR)/lex.r $(RDIR)/pf.r

NOSTK = $(RDIR)/misc.r $(RDIR)/get.r $(RDIR)/local.r $(RDIR)/cmain.r \
		$(RDIR)/printf.r

$(PROG): $(STKS) $(NOSTK)
	cd $(RDIR);$(CC) $(LFLAGS) $(OBJS) -f=$(PROG); cd $(SRCDIR)

$(STKS):
	$(CC) $(CFLAGS) $(*F).c -r=$(RDIR)

$(NOSTK):
	$(CC) $(CFLAGS) -s $(*F).c -r=$(RDIR)

proto:
	cproto -f1 -DCOCO *.c >protoc.h
