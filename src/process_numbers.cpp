#include "process_numbers.hpp"
#include <vector>
#include <algorithm>
#include <iterator>
#include <ranges>
#include <iostream>

void split_odd_even(std::istream& numbers, std::ostream& odds, std::ostream& evens) {
    std::istream_iterator<int> start(numbers), end;
    std::vector<int> nums(start, end);

    // Sort the numbers
    std::ranges::sort(nums);

    // Use copy_if with ostream_iterator to directly write odd numbers to odds, each followed by '\n'
    std::ranges::copy_if(nums.begin(), nums.end(), std::ostream_iterator<int>(odds, "\n"),
                         [](int n) { return n % 2 != 0; });

    // To handle even numbers and ensure a newline only at the end,
    // first collect them using copy_if into a temporary vector
    std::vector<int> evens_temp;
    std::ranges::copy_if(nums.begin(), nums.end(), std::back_inserter(evens_temp),
                         [](int n) { return n % 2 == 0; });

    // Use ranges to iterate over even numbers and ostream_iterator for output
    // ensuring not to add a space after the last number
    if (!evens_temp.empty()) {
        auto last = evens_temp.end() - 1;
        for (auto it = evens_temp.begin(); it != last; ++it) {
            evens << *it << " ";
        }
        evens << *last << "\n"; // Write the last even number followed by a newline
    }
}
