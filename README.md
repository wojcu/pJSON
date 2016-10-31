# pJSON

C++ library providing an implementation of JSON parser/serializer based on the persistent AVL tree implementation.

Warning:
===

This project is still in development and does not implement the full JSON standard for unicode characters.

Platforms:
===

The library can be build on any platform with a proper C++11 support. It
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

Why pJSON?
===

Because of the properties of the underlying data structure any pJSON object can be copied in constant time and share pieces of it's structure with those copies.
This property can be advantageous in scenarios where a number of different snapshots of the same data must be stored at the same time.

Consider the following example:
In a simple real-time game the player can use his weapon to fire a bullet at an enemy.
With a server-client scenario the information about the player's action will reach the server some time after the collision calculation should have taken place and the desired target might have already disappeared.
This can be avoided by storing multiple copies of the game world along with thier time stamps to allow for calculations in the past. 
With pJSON objects acting as the game state this approach allows the world states to share any data which hasn't been changed between ticks. 
Additionaly the current game state can quickly be copied and moved to another thread for saving to disk.

The trade-off of using pJSON is an increase in time required for some of the queries to the JSON arrays which go from constant to logarithmic with respect to the size of an array.
