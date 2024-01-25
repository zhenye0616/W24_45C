#include <gtest/gtest.h>

#include <sstream>
#include "word_count.hpp"

TEST(WordCount, ToLowercase) {
    std::string test = "hEllO wOrLd";
    to_lowercase(test);
    EXPECT_EQ(test, "hello world");
}

//TEST(WordCount, LoadStopWords) {
    //std::istringstream stopwords_stream("a\nan\nthe\nand");
    //auto stopwords = load_stopwords(stopwords_stream);
    //EXPECT_EQ(stopwords.size(), 4);
    //EXPECT_TRUE(stopwords.find("a") != stopwords.end());
    //EXPECT_TRUE(stopwords.find("an") != stopwords.end());
    //EXPECT_TRUE(stopwords.find("the") != stopwords.end());
    //EXPECT_TRUE(stopwords.find("and") != stopwords.end());}

TEST(WordCount, CountWords) {
    std::stringstream test("and the of");
    std::set<std::string> stopwords{"and", "the", "of"};
    auto counts = count_words(test, stopwords);
    EXPECT_TRUE(counts.empty());}

TEST(WordCount, LoadStopWords) {
    std::stringstream test("");
    auto stop_words = load_stopwords(test);
    EXPECT_TRUE(stop_words.empty());
}

TEST(WordCount, OutputWordCounts) {
    std::map<std::string, int> word_counts{{"apple", 2}, {"banana", 3}, {"cherry", 1}};
    std::stringstream output;
    output_word_counts(word_counts, output);
    EXPECT_EQ(output.str(), "apple 2\nbanana 3\ncherry 1\n");
}

