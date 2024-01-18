int char_to_index(char ch) {
    ch = std::toupper(ch); // Convert to uppercase for case insensitivity
    return ch - 'A';
}

char index_to_char(int i) {
    return static_cast<char>('A' + i);
}

void count(const std::string& s, int counts[]) {
    for (char ch : s) {
        if (std::isalpha(ch)) {
            int index = char_to_index(ch);
            counts[index]++;
        }
    }
}

void print_counts(int counts[], int len) {
    for (int i = 0; i < len; i++) {
        char letter = index_to_char(i);
        int count = counts[i];
        std::cout << letter << ' ' << count << '\n';
    }
}

}
