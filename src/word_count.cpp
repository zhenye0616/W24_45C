#include "word_count.hpp"
#include <algorithm>
#include <sstream>
#include <cctype>
#include <iterator>


std::string to_lowercase(const std::string& str) {
    std::string lower;
    std::transform(str.begin(), str.end(), std::back_inserter(lower),
                   [](unsigned char c) { return std::tolower(c); });
    return lower;
}
