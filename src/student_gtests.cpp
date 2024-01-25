#include <gtest/gtest.h>

#include <sstream>
#include "word_count.hpp"

TEST(WordCount, ToLowercase) {
    std::string test = "hEllO wOrLd";
    to_lowercase(test);
    EXPECT_EQ(test, "hello world");
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
    std::stringstream test("hello, world! hello-world.");
    std::set<std::string> stopwords;
    auto counts = count_words(test, stopwords);

    EXPECT_EQ(counts["hello,"], 1);
    EXPECT_EQ(counts["world!"], 1);
    EXPECT_EQ(counts["hello-world."], 1);
}

TEST(WordCount, OutputWordCounts) {
    std::map<std::string, int> word_counts{{"apple", 2}, {"banana", 3}, {"cherry", 1}};
    std::stringstream output;
    output_word_counts(word_counts, output);
    EXPECT_EQ(output.str(), "apple 2\nbanana 3\ncherry 1\n");
}

