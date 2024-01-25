#include <gtest/gtest.h>

#include <sstream>
#include "word_count.hpp"

TEST(WordCount, ToLowercase) {
    std::string test_str = "HeLLo WoRLD";
    to_lowercase(test_str);
    EXPECT_EQ(test_str, "hello world");
}


TEST(WordCount, LoadStopWords) {
    std::istringstream stopwords_stream("a\nan\nthe\nand");
    auto stopwords = load_stopwords(stopwords_stream);
    EXPECT_EQ(stopwords.size(), 4);
    EXPECT_TRUE(stopwords.find("a") != stopwords.end());
    EXPECT_TRUE(stopwords.find("an") != stopwords.end());
    EXPECT_TRUE(stopwords.find("the") != stopwords.end());
    EXPECT_TRUE(stopwords.find("and") != stopwords.end());
}

TEST(WordCount, CountWords) {
    std::istringstream document("apple banana apple orange banana apple");
    std::set<std::string> stopwords{"and", "the", "of", "a", "an"};
    auto word_counts = count_words(document, stopwords);
    EXPECT_EQ(word_counts["apple"], 3);
    EXPECT_EQ(word_counts["banana"], 2);
    EXPECT_EQ(word_counts["orange"], 1);
}


TEST(WordCount, OutputWordCounts) {
    std::map<std::string, int> word_counts{{"apple", 3}, {"banana", 2}, {"orange", 1}};
    std::ostringstream output_stream;
    output_word_counts(word_counts, output_stream);
    std::string expected_output = "apple 3\nbanana 2\norange 1\n";
    EXPECT_EQ(output_stream.str(), expected_output);
}

