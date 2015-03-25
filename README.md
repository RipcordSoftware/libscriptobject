[![Build Status](https://travis-ci.org/RipcordSoftware/libscriptobject.svg?branch=master)](https://travis-ci.org/RipcordSoftware/libscriptobject)
[![Coverage Status](https://coveralls.io/repos/RipcordSoftware/libscriptobject/badge.svg)](https://coveralls.io/r/RipcordSoftware/libscriptobject)

# libscriptobject
A C++ 11 library implementing scriptable/serializable objects for big-data map-reduce data stores.

Features:
* A single allocated memory block per object
* Fast member lookup (log N)
* Native type storage
* Support for arrays and nested objects (TODO)
* Repeated string caching (TODO)
* Shared object definitions
* Script language agnostic - integrates with JavaScript, Python, etc.

# Building
Requires:
* GCC 4.8.1+
* GNU Make
* lcov and Ruby (for test coverage)

To build type:
```bash
$ make
````

To build tests with coverage:
```bash
$ make test
```

To create a coverage report:

```bash
./coverage.sh
```
