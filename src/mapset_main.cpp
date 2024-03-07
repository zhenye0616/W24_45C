// mapset_main.cpp
#include "mapset.hpp"
#include <iostream>
#include <fstream>

int main() {
    std::ifstream stopwords_file("stopwords.txt");
    const auto stopwords = load_stopwords(stopwords_file);
    
    std::ifstream document_file("sample_doc.txt");
    const auto word_counts = count_words(document_file, stopwords);
    
    std::ofstream output_file("frequency.txt");
    output_word_counts(word_counts, output_file);

    return 0;
}
