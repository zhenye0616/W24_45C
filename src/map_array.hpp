#ifndef MAP_ARRAY_HPP
#define MAP_ARRAY_HPP

#include <algorithm>
#include <iterator>
#include <ranges>
#include <utility>
#include <vector>

template <typename Key, typename Value>
class MapArray {
public:
    class ArrayIterator {
    public:
        // Iterator traits:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = std::pair<const Key, Value>;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        explicit ArrayIterator(std::pair<Key, Value>* ptr = nullptr): ptr(ptr) {}

        ArrayIterator& operator++(){
            ++ptr;
            return *this;
        }
        ArrayIterator& operator--(){
            --ptr;
            return *this;
        }
            
        ArrayIterator operator++(int){
            ArrayIterator temp= *this;
            ++(*this);
            return temp;
        }
        ArrayIterator operator--(int){
            ArrayIterator temp= *this;
            --(*this);
            return temp;
        }
        ArrayIterator& operator+=(difference_type d){
            ptr += d;
            return *this;
        }
        ArrayIterator& operator-=(difference_type d){
            ptr -= d;
            return *this;
        }
        friend ArrayIterator operator+(ArrayIterator it, difference_type d){               ArrayIterator temp = it;
            temp += d;
            return temp;
        }
        friend ArrayIterator operator-(ArrayIterator it, difference_type d){
            ArrayIterator temp = it;
            temp -= d;
            return temp;
        }
        friend difference_type operator-(ArrayIterator lhs, ArrayIterator rhs)         {
            return lhs.ptr - rhs.ptr;
        }
        auto operator<=>(const ArrayIterator& other) const = default;
        std::pair<Key, Value>& operator*() const{
            return *ptr;
        }
        std::pair<Key, Value>* operator->() const{
            return ptr;
        }
        std::pair<Key, Value>& operator[](difference_type d) const{
            return *(ptr + d);
        }

    private:
        std::pair<Key, Value>* ptr;
    };

    using value_type = std::pair<Key, Value>;
    using iterator = ArrayIterator;
    // Normally there would also be a const_iterator

    ArrayIterator begin(){
        return ArrayIterator(data.data());
    }
    
    ArrayIterator end(){
        return ArrayIterator(data.data() + data.size());
    }
    
    Value& operator[](const Key& key) {
    // Try to find the key in the existing data
    auto it = std::find_if(data.begin(), data.end(),
                           [&](const auto& pair) { return pair.first == key; });
    
    // If the key is found, return a reference to its value
    if (it != data.end()) {
        return it->second;
    } else {
        // If the key is not found, add a new pair with a default-constructed value
        data.emplace_back(key, Value{});
        // Sort the container to maintain order
        std::sort(data.begin(), data.end(), [](const auto& a, const auto& b) {
            return a.first < b.first;
        });
        // After sorting, find the newly added pair again to return a valid reference
        it = std::find_if(data.begin(), data.end(),
                         [&](const auto& pair) { return pair.first == key; });
        return it->second;
    }
}



    

private:
    std::vector<std::pair<Key, Value>> data;
};

#endif
