GTEST_VER=1.7.0

build: force_true .googletest
	cd src/libscriptobject && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) build

all: force_true .googletest
	cd src/libscriptobject && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) all

test: force_true .googletest
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

force_true:
	true
