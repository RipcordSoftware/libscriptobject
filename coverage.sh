#!/bin/bash

GCOV_TOOL=
if [ "$1" != "" ]; then
    GCOV_TOOL="--gcov-tool $1"
else
    which lcov > /dev/null
    if [ $? -ne 0 ]; then
       echo "You must have lcov installed to run this script."
       echo "Install with 'yum install lcov' or 'apt-get install lcov'"
       exit 1
    fi
fi

lcov -b src/libscriptobject --directory src/libscriptobject/build/Debug/GNU-Linux-x86/ --capture --output-file libscriptobject.coverage.info ${GCOV_TOOL}
lcov -b src/testlibscriptobject --directory src/testlibscriptobject/build/Debug/GNU-Linux-x86/ --capture --output-file testlibscriptobject.coverage.info ${GCOV_TOOL}
lcov -a libscriptobject.coverage.info -a testlibscriptobject.coverage.info -o coverage.info ${GCOV_TOOL}
lcov --remove coverage.info 'tests/*' '/usr/*' '*/externals/*' 'md5.*' --output-file coverage.info ${GCOV_TOOL}
lcov --list coverage.info ${GCOV_TOOL}
if [ "$CI" = "true" ] && [ "$TRAVIS" = "true" ]; then
    coveralls-lcov coverage.info
else
    rm -rf coverage
    mkdir -p coverage
    cd coverage
    genhtml ../coverage.info
    cd ..
fi
