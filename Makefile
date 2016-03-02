GTEST_VER=1.7.0

build: force_true .googletest .gason
	cd src/libscriptobject && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) build
	cd src/libscriptobject_gason && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) build
	cd src/testlibscriptobject && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) build

all: force_true .googletest .gason
	cd src/libscriptobject && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) all
	cd src/libscriptobject_gason && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) all
	cd src/testlibscriptobject && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) all

test: force_true .googletest .gason
	cd src/libscriptobject && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) test
	cd src/testlibscriptobject && ./test.sh

clean: force_true
	cd src/libscriptobject && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) clean
	cd src/libscriptobject_gason && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) clean
	cd src/testlibscriptobject && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) clean

.googletest: force_true
	if [ "${CI}" = "true" ]; then \
		curl ftp://ftp.ripcordsoftware.com/pub/gtest-${GTEST_VER}-travis-ci-externals-installed.tar.xz -O && \
		tar xfJ gtest-*; \
	elif [ ! -d externals/gtest-${GTEST_VER}/lib/.libs ]; then \
		mkdir -p externals && \
		cd externals && \
		if [ ! -f gtest-${GTEST_VER}.zip ]; then curl https://googletest.googlecode.com/files/gtest-${GTEST_VER}.zip -O; fi && \
		unzip gtest-${GTEST_VER}.zip && \
		cd gtest-${GTEST_VER} && \
		./configure && \
		$(MAKE) -j 2 && \
		if [ ! -d "../installed/include" ]; then mkdir -p ../installed/include; fi && \
		if [ ! -d "../installed/lib" ]; then mkdir -p ../installed/lib; fi && \
		cp -Rf include/* ../installed/include && \
		cp -Rf lib/.libs/* ../installed/lib; \
	fi

.gason: force_true
	if ! `grep -q '\[submodule' .git/config`; then \
		git submodule init; \
	fi; \
	if [ ! -d externals/gason/.git ]; then \
		git submodule update; \
	fi

force_true:
	true
