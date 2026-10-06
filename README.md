# Templated Weighted List

A small header-only C++17 container that stores values with access weights. Calling `access(value)` increases the first matching entry's weight and promotes it before entries with a lower weight. This makes frequently accessed items appear earlier in the list.

## Features

- Templated over the stored value type
- Configurable equality comparator
- Insert at the front or back
- Access-based weight updates and promotion
- Search, erase, indexed read-only access, and iteration
- Header-only implementation using `std::list`

## Build and run

Requires CMake 3.16+ and a C++17 compiler.

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/weighted_list_example
```

## Example

```cpp
#include "weighted_list.hpp"

WeightedList<std::string> files;
files.push_back("readme.md");
files.push_back("main.cpp");
files.access("main.cpp"); // increments its weight and promotes it
```

## Complexity

Search and erase are O(n). Access is O(n) for lookup plus O(d) list-node promotions, where d is the number of entries it passes. Insertions at either end are O(1).

## Current scope

This is an educational project to explore templates, linked lists, iterators, and access-frequency ordering. It is single-threaded and allows duplicate values; access and erase affect the first matching value. `find_value()` does not change weights.
