#include "process_numbers.hpp"
#include <vector>
#include <iterator>
#include <algorithm>
#include <iostream>

void split_odd_even(std::istream& numbers, std::ostream& odds, std::ostream& evens) {
    std::vector<int> numbersVec;

    // Read integers from the input stream and insert them into the vector
    std::copy(std::istream_iterator<int>(numbers), std::istream_iterator<int>(), std::back_inserter(numbersVec));

    // Sort the vector
    std::sort(numbersVec.begin(), numbersVec.end());

    // Flags to track whether odd numbers have been encountered
    //bool EvenEncountered = false;

    // Iterate over the vector and write numbers to the respective streams
    std::for_each(numbersVec.begin(), numbersVec.end(), [&](int i) {
        if (i % 2 == 0) {
            // Write even number followed by newline
            evens << i << "\n";
        } else {
            // Write odd number followed by space
            odds << i << " ";
            //oddEncountered = true; // Set flag to true if odd number encountered
        }
    });

    // If any odd numbers were encountered, append a newline at the end
    odds << "\n";

}
