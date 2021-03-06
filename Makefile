GTEST_VER=1.7.0

.PHONY: build all clean docs publish_docs .googletest

.NOTPARALLEL: test

build all clean: .googletest
	cd src/libscriptobject && $(MAKE) $@
	cd src/libscriptobject_gason && $(MAKE) $@
	cd src/testlibscriptobject && $(MAKE) $@

test: .googletest
	cd src/libscriptobject && $(MAKE) $@
	cd src/testlibscriptobject && ./test.sh

docs:
	doxygen Doxyfile

publish_docs: docs
	cd docs && \
	rm -rf libscriptobject-docs && \
	git clone https://github.com/RipcordSoftware/libscriptobject-docs.git && \
	cd libscriptobject-docs && \
	rm -rf ./* && \
	cp -R ../html/* . && \
	git add . && \
	git commit -m "Update `date`" && \
	git push

.googletest:
	if [ "${CI}" = "true" ] && [ "${TRAVIS_OS_NAME}" = "linux" ]; then \
		curl http://cdn.ripcordsoftware.com/gtest-${GTEST_VER}-travis-ci-externals-installed.tar.xz -O && \
		tar xfJ gtest-*; \
	elif [ ! -d externals/gtest-${GTEST_VER}/lib/.libs ]; then \
		mkdir -p externals && \
		cd externals && \
		if [ ! -f gtest-${GTEST_VER}.zip ]; then curl http://cdn.ripcordsoftware.com/gtest-${GTEST_VER}.zip -O; fi && \
		unzip gtest-${GTEST_VER}.zip && \
		cd gtest-${GTEST_VER} && \
		./configure && \
		$(MAKE) && \
		if [ ! -d "../installed/include" ]; then mkdir -p ../installed/include; fi && \
		if [ ! -d "../installed/lib" ]; then mkdir -p ../installed/lib; fi && \
		cp -Rf include/* ../installed/include && \
		cp -Rf lib/.libs/* ../installed/lib; \
	fi
