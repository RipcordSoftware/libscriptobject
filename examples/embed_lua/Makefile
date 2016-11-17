CONF=Debug

.PHONY: all clean lua_check

# pkg-config is required to find lua (NB. you'll need to install the development paackage as well as the main package)
LUA_INCLUDE:=$(shell pkg-config --silence-errors --cflags lua5.3 || pkg-config --silence-errors --cflags lua5.2 || pkg-config --silence-errors --cflags lua5.1 || pkg-config --cflags lua)
LUA_LIB:=$(shell pkg-config --silence-errors --libs lua5.3 || pkg-config --silence-errors --libs lua5.2 || pkg-config --silence-errors --libs lua5.1 || pkg-config --libs lua)

VPATH:=$(CURDIR)
LIBROOT=../../src/libscriptobject
LIBPATH=$(LIBROOT)/dist/$(CONF)/GNU-Linux-x86/libscriptobject.a
OUTDIR=bin/$(CONF)
CPPFLAGS=--std=c++14 -I$(LIBROOT) -I. $(LUA_INCLUDE) $(LIBPATH) $(LUA_LIB)

ifeq ($(CONF), Debug)
	CPPFLAGS+=--coverage
endif

all: $(OUTDIR)/embed_lua

$(OUTDIR)/embed_lua: embed_lua.cpp $(LIBPATH)
	-mkdir -p $(OUTDIR)
	$(CXX) -o $@ $< $(CPPFLAGS)

$(LIBPATH):
	cd $(LIBROOT) && $(MAKE) CONF=$(CONF)

sol.hpp:
	wget https://github.com/ThePhD/sol2/releases/download/v2.15.1/sol.hpp

clean:
	-rm -f $(OUTDIR)/embed_lua
