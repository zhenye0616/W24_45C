#include "word_count.hpp"
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <algorithm>
#include <cctype>

void to_lowercase(std::string& str) {
    std::transform(str.begin(), str.end(), str.begin(),
                   [](unsigned char c) { return std::tolower(c); });
}

std::set<std::string> load_stopwords(std::istream& stopwords_stream) {
    std::set<std::string> stopwords;
    std::string word;
    while (stopwords_stream >> word) {
        to_lowercase(word);
        stopwords.insert(word);
    }
    return stopwords;
}


std::map<std::string, int> count_words(std::istream& document, const std::set<std::string>& stopwords) {
    std::map<std::string, int> word_count;
    std::string word;

    while (document >> word) {
        to_lowercase(word);

        // If the word is not a stopword, count it
        if (stopwords.find(word) == stopwords.end()) {
            ++word_count[word];
        }
    }

    return word_count;
}

void output_word_counts(const std::map<std::string, int>& word_counts, std::ostream& output) {
    for (const auto& pair : word_counts) {
        output << pair.first << " " << pair.second << std::endl;
    }
}