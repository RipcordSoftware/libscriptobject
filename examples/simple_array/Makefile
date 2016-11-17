CONF=Debug

.PHONY: all clean

VPATH:=$(CURDIR)
LIBROOT=../../src/libscriptobject
LIBPATH=$(LIBROOT)/dist/$(CONF)/GNU-Linux-x86/libscriptobject.a
OUTDIR=bin/$(CONF)
CPPFLAGS=--std=c++11 -I$(LIBROOT) $(LIBPATH)

ifeq ($(CONF), Debug)
	CPPFLAGS+=--coverage
endif

all: $(OUTDIR)/simple_array

$(OUTDIR)/simple_array: simple_array.cpp $(LIBPATH)
	-mkdir -p $(OUTDIR)
	$(CXX) -o $@ $< $(CPPFLAGS)

$(LIBPATH):
	cd $(LIBROOT) && $(MAKE) CONF=$(CONF)

clean:
	-rm -f $(OUTDIR)/simple_array
