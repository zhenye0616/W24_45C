#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iomanip>
#include <iostream>
#include <sstream>
#include <utility>
#include <algorithm> // Include this for std::fill

template <typename T>
class Array {
public:
    Array() : len(0), buf(nullptr) {}

    explicit Array(int length) : len(length), buf(new T[length]) {}

    Array(const Array& other) : len(other.len), buf(new T[other.len]) {
        std::copy(other.buf, other.buf + other.len, buf);
    }

    Array(Array&& other) noexcept : len(other.len), buf(other.buf) {
        other.len = 0;
        other.buf = nullptr;
    }

    Array& operator=(Array other) {
        swap(*this, other);
        return *this;
    }

    ~Array() {
        delete[] buf;
    }

    T& operator[](int index) {
        if (!in_bounds(index)) {
            throw std::out_of_range("Index out of bounds");
        }
        return buf[index];
    }

    const T& operator[](int index) const {
        if (!in_bounds(index)) {
            throw std::out_of_range("Index out of bounds");
        }
        return buf[index];
    }

    int length() const {
        return len;
    }

    void fill(const T& value) {
        std::fill(buf, buf + len, value);
    }

    template <typename Fn>
    void fill_with_fn(Fn fn) {
        for (int i = 0; i < len; ++i) {
            buf[i] = fn(i);
        }
    }

    friend void swap(Array& first, Array& second) noexcept {
        using std::swap;
        swap(first.len, second.len);
        swap(first.buf, second.buf);
    }

private:
    int len;
    T* buf;

    bool in_bounds(int index) const {
        return index >= 0 && index < len;
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const Array<T>& array) {
    for (int i = 0; i < array.length(); ++i) {
        if (i > 0) out << ' ';
        out << array[i];
    }
    return out;
}

template <typename T>
std::istream& operator>>(std::istream& in, Array<T>& array) {
    for (int i = 0; i < array.length(); ++i) {
        in >> array[i];
    }
    return in;
}

#endif // ARRAY_HPP
