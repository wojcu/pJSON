# pJSON

C++ library providing an implementation of JSON parser/serializer based on the persistent AVL tree implementation.

Warning:
===

This project is still in development and does not implement the full JSON standard for unicode characters.

Platforms:
===

The library can be build on any platform which has a proper C++11 support. It
was tested under the following operating systems:

* Ubuntu 16.04

Building:
===

The generic way to build and install the required files is:
```
./bootstrap
./configure
make
sudo make install
```

Examples:
===

The interface for json objects can be included with the following macro:
```c++
#include <pjson/json.h>

using json = persistent::json;
```
C++ iostreams should be used to serialize values between the internal and textual representation.
```c++
#include <iostream>
#include <sstream>
#include <cassert>
#include <pjson/json.h>

using json = persistent::json;

int main() {
  json j;
  j.insert("key", 5);
  std::cout << j << std::endl;
  //{"key":5}
  std::istringstream input("[\"text\\n\", 3, false]");
  input >> j;
  assert(j.size() == 3);
  assert(j.is_array());
  assert(j.at(0).is_string());
  assert(j.at(0).string() == "text\n");
}
```
