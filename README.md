libeljson
=========

An easy-to-use C++ JSON library.

Usage example
-------------

```cpp
#include <iostream>

#include "json.hpp"

int main(int, char**)
{
  // Create a JSON object.
  auto obj = json::object{
    "Library Name", "libeljson",
    "Version", json::object{
      "Major", 0,
      "Minor", 0,
      "Patch", 1
    },
  };

  // Access an element within the object.
  std::cout << "Major version is: " << obj["Version"]["Major"].str() << std::endl;

  // Serialize the JSON object we created
  std::cout << obj.str() << std::endl;
}
```

See also https://github.com/slavc/libeljson/blob/master/test/test.cpp
