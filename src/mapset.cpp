// mapset.cpp
#include "mapset.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cctype>

// Function to convert a string to lowercase
std::string to_lowercase(const std::string& str) {
    std::string lower_str;
    std::transform(str.begin(), str.end(), std::back_inserter(lower_str), ::tolower);
    return lower_str;
}

// Function to load stopwords into a set
std::set<std::string> load_stopwords(std::istream& stopwords_stream) {
    std::set<std::string> stopwords;
    std::string word;
    while (stopwords_stream >> word) {
        stopwords.insert(to_lowercase(word));
    }
    return stopwords;
}

// Function to count the frequency of words in the document
std::map<std::string, int> count_words(std::istream& document_stream, const std::set<std::string>& stopwords) {
    std::map<std::string, int> word_count;
    std::string word;
    while (document_stream >> word) {
        word = to_lowercase(word);
        // Remove punctuation from the end of the word
        word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());
        if (stopwords.find(word) == stopwords.end()) {
            ++word_count[word];
        }
    }
    return word_count;
}

// Function to output the word counts to a file
void output_word_counts(const std::map<std::string, int>& word_counts, std::ostream& output_stream) {
    for (const auto& [word, count] : word_counts) {
        output_stream << word << " " << count << '\n';
    }
}
