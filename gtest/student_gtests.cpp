#include <gtest/gtest.h>
#include <string.h>

#include <algorithm>

#include "string.hpp"
#include "alloc.hpp"

TEST(StringFunction, strlen) {
    EXPECT_EQ(String::strlen(""), 0);
    EXPECT_EQ(String::strlen("foo"), 3);
}

TEST(StringFunction, strcpy) {
    char result[10];
    EXPECT_EQ(String::strcpy(result, "foo"), result);
    EXPECT_STREQ(result, "foo");

    EXPECT_EQ(String::strcpy(result, "a"), result);
    EXPECT_STREQ(result, "a");

    EXPECT_EQ(String::strcpy(result, ""), result);
    EXPECT_STREQ(result, "");
}

TEST(StringFunction, strdup) {
    const char* original = "Test string";
    char* duplicated = String::strdup(original);
    EXPECT_STREQ(original, duplicated) << "The duplicated string does not match the original";
    EXPECT_NE(original, duplicated) << "The duplicated string points to the same memory as the original";
    delete[] duplicated;
}


TEST(StringFunction, strncpy) {
    char destination[10]; // Initialize a destination buffer
    const char* source = "Hello, World!";
    size_t n = 5; // Maximum number of characters to copy
    strncpy(destination, source, n);
    destination[n] = '\0'; // Null-terminate the destination string
    EXPECT_STREQ(destination, "Hello"); // Compare as C-strings
    std::cout << "Destination: " << destination << std::endl;
}

TEST(StringFunction, strcat) {
    char destination[20] = "Hello, ";
    const char* source = "World!";
    strcat(destination, source);
    EXPECT_STREQ(destination, "Hello, World!");
}

TEST(StringFunction, strncat) {
    char str1[20];
    char str2[20];
    String::strcpy (str1, "To be ");
    String::strcpy (str2, "or not to be");
    String::strncat (str1, str2, 6);
    EXPECT_STREQ(str1, "To be or not");
}



TEST(StringFunction, strcmp) {
    /*char s1[] = "apple";
    char s2[] = "banana";
    char s3[] = "hello";
    char s4[] = "hello";
    EXPECT_EQ(strcmp(s3, s4), String::strcmp(s3, s4));
    EXPECT_EQ(String::strcmp(s3, s4), 0);
    EXPECT_EQ(strcmp(s1, s2), String::strcmp(s1, s2));
    EXPECT_LT(String::strcmp(s1, s2), 0);
    EXPECT_GT(String::strcmp(s2, s1), 0);*/
    //compare nullptr leads to undefined behavior
    char str1[] = "answer1";
    char str2[] = "answer2";
    char str3[] = "answer3";
    EXPECT_EQ(String::strcmp(str2, str2), 0);
    EXPECT_LT(String::strcmp(str2, str3), 0);
    EXPECT_GT(String::strcmp(str2, str1), 0);
}

TEST(StringFunction, strncmp) {
    const char* s1 = "";
    const char* s2 = "";
    const char* s3 = "hello";
    const char* s4 = "hello";
    const char* s5 = "world";
    const char* s6 = "hello world";
    const char* s7 = "jello";
    const char* s8 = "hejlo";
    EXPECT_EQ(String::strncmp(s1, s2, 5), 0);
    EXPECT_EQ(String::strncmp(s3, s4, 5), 0);
    EXPECT_NE(String::strncmp(s3, s5, 5), 0);
    EXPECT_EQ(String::strncmp(s4, s6, 5), 0);
    EXPECT_LT(String::strncmp(s4, s6, 11), 0);
    EXPECT_EQ(String::strncmp(s4, s6, 3), 0);
    EXPECT_LT(String::strncmp(s3, s7, 5), 0);
    EXPECT_GT(String::strncmp(s3, s8, 5), 0);
}

TEST(StringFunction, strchr) {
    const char* str = "Hello, World!";
    char c = 'W';
    const char* result = String::strchr(str, c);
    EXPECT_EQ(result, str + 7); // Expect result to point to 'W' in the string
}

TEST(StringFunction, strstr) {
    // Test strings and substrings
    const char *str1 = "hello world";
    const char *sub1 = "world";
    const char *sub2 = "foo";
    const char *sub3 = "";
    const char *sub4 = "hello world";
    const char *str2 = "hello hello world";
    const char *sub6 = "hello";
    const char *str3 = "hello hellhello world";
    const char *sub7 = "hellhello";

    // Test cases
    const char* res1 = String::strstr(str1, sub1);
    const char* res2 = String::strstr(str1, sub2);
    const char* res3 = String::strstr(str1, sub3);
    const char* res4 = String::strstr(sub3, sub2);
    const char* res5 = String::strstr(str1, sub4);
    const char* res6 = String::strstr(str2, sub6);
    const char* res7 = String::strstr(str3, sub7);

    // Assertions to compare with the standard strstr results
    EXPECT_EQ(res1, strstr(str1, sub1));
    EXPECT_EQ(res2, strstr(str1, sub2));
    EXPECT_EQ(res3, strstr(str1, sub3));
    EXPECT_EQ(res4, strstr(sub3, sub2));
    EXPECT_EQ(res5, strstr(str1, sub4));
    EXPECT_EQ(res6, strstr(str2, sub6));
    EXPECT_EQ(res7, strstr(str3, sub7));

    // Additional checks for the complex case
    const char *res = String::strstr(str3, sub7);
    EXPECT_NE(res, nullptr);  // Ensure a match was found
    EXPECT_EQ(strcmp(res, "hellhello world"), 0);  // Verify the match is correct
}

TEST(StringFunction, reverse_cpy) {
    const char* original = "Hello";
    char reversed[6];
    String::reverse_cpy(reversed, original);
    EXPECT_STREQ(reversed, "olleH"); // Compare as C-strings
}
