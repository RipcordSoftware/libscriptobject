CONF=Debug

.PHONY: all clean

VPATH:=$(CURDIR)
LIBROOT=../../src/libscriptobject
JSONLIBROOT=../../src/libscriptobject_gason
LIBPATH=$(LIBROOT)/dist/$(CONF)/GNU-Linux-x86/libscriptobject.a
JSONLIBPATH=$(JSONLIBROOT)/dist/$(CONF)/GNU-Linux-x86/libscriptobject_gason.a
OUTDIR=bin/$(CONF)
CPPFLAGS=--std=c++11 -I$(LIBROOT) -I$(JSONLIBROOT) $(JSONLIBPATH) $(LIBPATH)

ifeq ($(CONF), Debug)
	CPPFLAGS+=--coverage
endif

all: $(OUTDIR)/json

$(OUTDIR)/json: json.cpp $(LIBPATH)
	-mkdir -p $(OUTDIR)
	$(CXX) -o $@ $< $(CPPFLAGS)

$(LIBPATH):
	cd $(LIBROOT) && $(MAKE) CONF=$(CONF)

clean:
	-rm -f $(OUTDIR)/json
