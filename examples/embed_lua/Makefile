CONF=Debug

.PHONY: all clean lua_check

# massive assumption about the Lua that is installed
# works on Debian 8 but will probably need to change elsewhere
LUA_INCLUDE=/usr/include/lua5.2
LUA_LIB=lua5.2

LIBROOT=../../src/libscriptobject
LIBPATH=$(LIBROOT)/dist/$(CONF)/GNU-Linux-x86/libscriptobject.a
CPPFLAGS=--std=c++14 -I$(LIBROOT) -I. -I$(LUA_INCLUDE) $(LIBPATH) -l$(LUA_LIB)

ifeq ($(CONF), Debug)
	CPPFLAGS+=--coverage
endif

all: lua_check embed_lua

embed_lua: embed_lua.cpp $(LIBPATH)
	-mkdir -p bin/$(CONF)
	$(CXX) -o bin/$(CONF)/$@ $< $(CPPFLAGS)

$(LIBPATH):
	cd $(LIBROOT) && $(MAKE) CONF=$(CONF)

sol.hpp:
	wget https://github.com/ThePhD/sol2/releases/download/v2.15.1/sol.hpp

lua_check:
	@test -d $(LUA_INCLUDE) || (echo "Unable to find Lua 5.2, expected to find it at '$(LUA_INCLUDE)'"; false)

clean:
	-rm -f bin/$(CONF)/embed_lua
