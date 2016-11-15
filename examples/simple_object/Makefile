CONF=Debug

.PHONY: all clean

LIBROOT=../../src/libscriptobject
LIBPATH=$(LIBROOT)/dist/$(CONF)/GNU-Linux-x86/libscriptobject.a
CPPFLAGS=--std=c++11 -I$(LIBROOT) $(LIBPATH)

ifeq ($(CONF), Debug)
	CPPFLAGS+=--coverage
endif

all: simple_object

simple_object: simple_object.cpp $(LIBPATH)
	-mkdir -p bin/$(CONF)
	$(CXX) -o bin/$(CONF)/$@ $< $(CPPFLAGS)

$(LIBPATH):
	cd $(LIBROOT) && $(MAKE) CONF=$(CONF)

clean:
	-rm -f bin/$(CONF)/simple_object
