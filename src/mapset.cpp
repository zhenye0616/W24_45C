// mapset.cpp
#include "mapset.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cctype>
#include <vector>

// Function to convert a string to lowercase
std::string to_lowercase(const std::string& str) {
    std::string lower_str;
    std::transform(str.begin(), str.end(), std::back_inserter(lower_str),
                   [](unsigned char c) { return std::tolower(c); });
    return lower_str;
}

// Function to load stopwords into a set
std::set<std::string> load_stopwords(std::istream& stopwords_stream) {
    std::set<std::string> stopwords;
    std::istream_iterator<std::string> it(stopwords_stream);
    std::istream_iterator<std::string> end;
    std::vector<std::string> words(it, end);
    
    std::transform(words.begin(), words.end(), std::inserter(stopwords, stopwords.end()),
                   [](const std::string& word) { return to_lowercase(word); });
    
    return stopwords;
}

// Remaining implementations of count_words and output_word_counts go here.


// Function to count the frequency of words in the document
std::map<std::string, int> count_words(std::istream& document_stream, const std::set<std::string>& stopwords) {
    std::map<std::string, int> word_count;
    std::istream_iterator<std::string> it(document_stream);
    std::istream_iterator<std::string> eof;
    std::ranges::for_each(it, eof, [&](const std::string& word) {
        std::string lw = to_lowercase(word);
        lw.erase(std::remove_if(lw.begin(), lw.end(), ispunct), lw.end());
        if (!stopwords.contains(lw)) {
            word_count[lw]++;
        }
    });
    return word_count;
}

// Function to output the word counts to a file
void output_word_counts(const std::map<std::string, int>& word_counts, std::ostream& output_stream) {
    std::ranges::for_each(word_counts, [&](const auto& pair) {
        output_stream << pair.first << " " << pair.second << '\n';
    });
}
