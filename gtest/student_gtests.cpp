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


//TEST(StringFunction, strcat) {
    //EXPECT_TRUE(false);
//}

//TEST(StringFunction, strncat) {
//    EXPECT_TRUE(false);
//}

//TEST(StringFunction, strcmp) {
  //  EXPECT_TRUE(false);
//}

//TEST(StringFunction, strncmp) {
//    EXPECT_TRUE(false);
//}

//TEST(StringFunction, reverse_cpy) {
//    EXPECT_TRUE(false);
//}

//TEST(StringFunction, strchr) {
//    EXPECT_TRUE(false);
//}

//TEST(StringFunction, strstr) {
//    EXPECT_TRUE(false);
//}
