GTEST_VER=1.7.0

build: force_true .googletest .jsoncpp
	cd src/libscriptobject && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) build

all: force_true .googletest .jsoncpp
	cd src/libscriptobject && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) all

test: force_true .googletest .jsoncpp
	cd src/libscriptobject && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) test

clean: force_true
	cd src/libscriptobject && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) clean

.googletest: force_true
	if [ ! -d externals/gtest-${GTEST_VER}/lib/.libs ]; then \
		mkdir -p externals && \
		cd externals && \
		if [ ! -f gtest-${GTEST_VER}.zip ]; then curl https://googletest.googlecode.com/files/gtest-${GTEST_VER}.zip -O; fi && \
		unzip gtest-${GTEST_VER}.zip && \
		cd gtest-${GTEST_VER} && \
		./configure && \
		make -j 2 && \
		if [ ! -d "../installed/include" ]; then mkdir -p ../installed/include; fi && \
		if [ ! -d "../installed/lib" ]; then mkdir -p ../installed/lib; fi && \
		cp -Rf include/* ../installed/include && \
		cp -Rf lib/.libs/* ../installed/lib; \
	fi

.jsoncpp: force_true
	if ! `grep -q '\[submodule' .git/config`; then \
		git submodule init; \
	fi; \
	if [ ! -d externals/jsoncpp/.git ]; then \
		git submodule update; \
	fi; \
	if [ ! -d externals/jsoncpp/build/debug ]; then \
		mkdir -p externals/jsoncpp/build/debug && \
		cd externals/jsoncpp/build/debug && \
		cmake -DCMAKE_BUILD_TYPE=debug -DJSONCPP_LIB_BUILD_STATIC=ON -DJSONCPP_LIB_BUILD_SHARED=OFF -G "Unix Makefiles" ../.. && \
		make -j 2 && \
		cp -f src/lib_json/libjsoncpp.a ../../../installed/lib/libjsoncpp_debug.a && \
		cd ../../../..; \
	fi; \
	if [ ! -d externals/jsoncpp/build/release ]; then \
		mkdir -p externals/jsoncpp/build/release && \
		cd externals/jsoncpp/build/release && \
		cmake -DJSONCPP_LIB_BUILD_STATIC=ON -DJSONCPP_LIB_BUILD_SHARED=OFF -G "Unix Makefiles" ../.. && \
		make -j 2 && \
		cp -f src/lib_json/libjsoncpp.a ../../../installed/lib && \
		cd ../../../..; \
	fi; \
	if [ ! -f externals/installed/include/json ]; then \
		mkdir -p externals/installed/include/json && \
		cp -Rf externals/jsoncpp/include/json/* externals/installed/include/json/; \
	fi

force_true:
	true
