#include <iostream>
#include <vector>
#include <string>
using namespace std;
#include "letter_count.hpp"

constexpr int N_CHARS = ('Z' - 'A' + 1); // will be 26

int main() {
    string input;
    int counts[N_CHARS] = {0}; // Initialize all elements to 0

    cout << "Enter a string: ";
    getline(cin, input);

    count(input, counts); // Use the count function correctly

    print_counts(counts, N_CHARS); // You can use the provided print function

    return 0;
}
