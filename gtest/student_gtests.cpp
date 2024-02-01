#include <gtest/gtest.h>

#include "string.hpp"

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
    char destination[20] = "Hello, ";
    const char* source = "World!";
    size_t n = 3; // Maximum number of characters to concatenate
    strncat(destination, source, n);
    EXPECT_STREQ(destination, "Hello, Wor"); // Compare as C-strings
}

TEST(StringFunction, strcmp) {
    const char* str1 = "abc";
    const char* str2 = "abd";
    int result = strcmp(str1, str2);
    EXPECT_LT(result, 0); // Expect str1 < str2
}

TEST(StringFunction, strncmp) {
    const char* str1 = "abc";
    const char* str2 = "abd";
    int result = strncmp(str1, str2, 2); // Only compare first 2 characters
    EXPECT_EQ(result, 0); // Expect str1 and str2 to be equal for the first 2 characters
}

TEST(StringFunction, strchr) {
    const char* str = "Hello, World!";
    char c = 'W';
    const char* result = String::strchr(str, c);
    EXPECT_EQ(result, str + 7); // Expect result to point to 'W' in the string
}

TEST(StringFunction, strstr) {
    const char* haystack = "Hello, World!";
    const char* needle = "World";
    const char* result = String::strstr(haystack, needle);
    EXPECT_STREQ(result, "World!"); // Compare as C-strings
}

TEST(StringFunction, reverse_cpy) {
    const char* original = "Hello";
    char reversed[6];
    String::reverse_cpy(reversed, original);
    EXPECT_STREQ(reversed, "olleH"); // Compare as C-strings
}

