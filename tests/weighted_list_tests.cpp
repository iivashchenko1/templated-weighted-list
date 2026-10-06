#include "weighted_list.hpp"

#include <cassert>
#include <stdexcept>
#include <string>

int main() {
    WeightedList<std::string> list;
    assert(list.empty());

    list.push_back("alpha");
    list.push_back("beta");
    list.push_back("gamma");
    assert(list.size() == 3);
    assert(list.at(0).value == "alpha");

    auto* found = list.access("gamma");
    assert(found && *found == "gamma");
    assert(list.at(0).value == "gamma");
    assert(list.at(0).weight == 1);

    list.access("beta");
    // Equal weights keep their prior relative order.
    assert(list.at(0).value == "gamma");
    list.access("beta");
    assert(list.at(0).value == "beta");
    assert(list.at(0).weight == 2);

    assert(list.find_value("alpha") && *list.find_value("alpha") == "alpha");
    assert(list.find_value("missing") == nullptr);
    assert(list.access("missing") == nullptr);

    assert(list.erase("gamma"));
    assert(!list.erase("gamma"));
    assert(list.size() == 2);

    bool threw = false;
    try { (void)list.at(5); }
    catch (const std::out_of_range&) { threw = true; }
    assert(threw);

    list.clear();
    assert(list.empty());
}
