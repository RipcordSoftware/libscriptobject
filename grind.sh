!#/bin/sh
make test

for f in src/libscriptobject/build/Debug/GNU-Linux-x86/tests/TestFiles/*; do
	valgrind $f
done
