CONF=Debug

.PHONY: libscriptobject all clean

LIBROOT=../../src/libscriptobject
LIBPATH=$(LIBROOT)/dist/$(CONF)/GNU-Linux-x86/libscriptobject.a
CPPFLAGS=--std=c++11 -I$(LIBROOT) $(LIBPATH)

ifeq ($(CONF), Debug)
	CPPFLAGS+=--coverage
endif

all: simple_object

simple_object: simple_object.cpp libscriptobject
	$(CXX) -o $@ $< $(CPPFLAGS)

libscriptobject:
	cd $(LIBROOT) && $(MAKE)

clean:
	-rm -f simple_object
