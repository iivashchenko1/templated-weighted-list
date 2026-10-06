#pragma once

#include <cstddef>
#include <functional>
#include <list>
#include <stdexcept>
#include <utility>

// A simple frequency-weighted list. Each successful access increases an
// element's weight and moves it toward the front, so frequently used items
// become quicker to find with a linear search.
template <typename T, typename Equal = std::equal_to<T>>
class WeightedList {
public:
    struct Entry {
        T value;
        std::size_t weight = 0;
    };

    using size_type = typename std::list<Entry>::size_type;
    using const_iterator = typename std::list<Entry>::const_iterator;

    explicit WeightedList(Equal equal = Equal{}) : equal_(std::move(equal)) {}

    [[nodiscard]] bool empty() const noexcept { return entries_.empty(); }
    [[nodiscard]] size_type size() const noexcept { return entries_.size(); }

    void clear() noexcept { entries_.clear(); }

    // Inserts a value with weight zero. Duplicate values are allowed.
    void push_front(T value) { entries_.push_front(Entry{std::move(value), 0}); }
    void push_back(T value) { entries_.push_back(Entry{std::move(value), 0}); }

    // Finds the first matching entry, increases its weight and promotes it
    // ahead of entries with a lower weight. Returns nullptr if absent.
    T* access(const T& value) {
        auto it = find(value);
        if (it == entries_.end()) return nullptr;

        ++it->weight;
        auto position = it;
        while (position != entries_.begin()) {
            auto previous = std::prev(position);
            if (previous->weight >= position->weight) break;
            entries_.splice(previous, entries_, position);
        }
        return &it->value;
    }

    [[nodiscard]] const T* find_value(const T& value) const {
        for (const auto& entry : entries_) {
            if (equal_(entry.value, value)) return &entry.value;
        }
        return nullptr;
    }

    bool erase(const T& value) {
        for (auto it = entries_.begin(); it != entries_.end(); ++it) {
            if (equal_(it->value, value)) {
                entries_.erase(it);
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] const Entry& at(size_type index) const {
        if (index >= entries_.size()) throw std::out_of_range("WeightedList index out of range");
        auto it = entries_.begin();
        std::advance(it, static_cast<typename std::list<Entry>::difference_type>(index));
        return *it;
    }

    [[nodiscard]] const_iterator begin() const noexcept { return entries_.cbegin(); }
    [[nodiscard]] const_iterator end() const noexcept { return entries_.cend(); }

private:
    using iterator = typename std::list<Entry>::iterator;

    iterator find(const T& value) {
        for (auto it = entries_.begin(); it != entries_.end(); ++it) {
            if (equal_(it->value, value)) return it;
        }
        return entries_.end();
    }

    std::list<Entry> entries_;
    Equal equal_;
};
