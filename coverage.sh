#!/bin/bash

which lcov > /dev/null
if [ $? -ne 0 ]; then
   echo "You must have lcov installed to run this script."
   echo "Install with 'yum install lcov' or 'apt-get install lcov'"
   exit 1
fi

lcov -b src/libscriptobject --directory src/libscriptobject/build/Debug/GNU-Linux-x86/ --capture --output-file libscriptobject.coverage.info
lcov -b src/testlibscriptobject --directory src/testlibscriptobject/build/Debug/GNU-Linux-x86/ --capture --output-file testlibscriptobject.coverage.info
lcov -a libscriptobject.coverage.info -a testlibscriptobject.coverage.info -o coverage.info
lcov --remove coverage.info 'tests/*' '/usr/*' '*/externals/*' 'md5.*' --output-file coverage.info
lcov --list coverage.info
if [ "$CI" = "true" ] && [ "$TRAVIS" = "true" ]; then
    coveralls-lcov coverage.info
else
    rm -rf coverage
    mkdir -p coverage
    cd coverage
    genhtml ../coverage.info
    cd ..
fi
