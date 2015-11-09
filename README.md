[![Build Status](https://travis-ci.org/RipcordSoftware/libscriptobject.svg?branch=master)](https://travis-ci.org/RipcordSoftware/libscriptobject)
[![Coverage Status](https://coveralls.io/repos/RipcordSoftware/libscriptobject/badge.svg)](https://coveralls.io/r/RipcordSoftware/libscriptobject)
[![License](http://img.shields.io/:license-gpl2-blue.svg)](http://doge.gpl2-license.org)

# libscriptobject
A C++ 11 library implementing scriptable/serializable objects for big-data map-reduce data stores.

This library handles complex object, array and value hierarchies in a memory efficient and performant
data structure. For example the following JS structure can easily be expressed:

```js
{ hello: "world", pi: 3.14159, the_answer: 42, child: { lorem: "ipsum" }, bored: true }
```

The library uses the standard libc memory allocator with std::shared_ptr<> for object and array reference counting.
In this example the object `b` refers to something declared in the scope of object `a`:
```js
var a = { great_rock_years: [ 1970, 1971, 1972, 1973, 1974, 1975, 1976, 1977, 1978, 1979 ] };
var b = { old_man_music_years: a.great_rock_years };
```

Since we are using malloc/free for all objects there is no garbage collector. This is critical for big-data
stores where the number of objects count in the hundreds of millions and multi-second collections are not
acceptable.

## Features:
* A single allocated memory block per object
* Fast member lookup (log N)
* Native type storage
* Support for arrays and nested objects
* Repeated string caching (TODO)
* Shared object definitions
* Script language agnostic - integrates with JavaScript, Python, etc.

# Building
Requires:
* GCC 4.9+
* GNU Make
* lcov, Ruby, python, python-pip (for test coverage)
* valgrind (for memory analysis)

To build type:
```bash
$ make
```

To build tests with coverage:
```bash
$ make test
```

To create a coverage report:
```bash
$ ./coverage.sh
```

To analyze memory:
```bash
$ ./grind.sh
```
