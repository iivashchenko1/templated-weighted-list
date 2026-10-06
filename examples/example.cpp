#include "weighted_list.hpp"

#include <iostream>
#include <string>

int main() {
    WeightedList<std::string> recently_used;
    recently_used.push_back("readme.md");
    recently_used.push_back("main.cpp");
    recently_used.push_back("notes.txt");

    recently_used.access("notes.txt");
    recently_used.access("main.cpp");
    recently_used.access("main.cpp");

    for (const auto& entry : recently_used) {
        std::cout << entry.value << " (weight " << entry.weight << ")\n";
    }
}
