#include <gtest/gtest.h>

#include "list.hpp"

using namespace std;
using list::Node;

TEST(ListTests, FromStringBasic) {
    Node* const foo_list_head = list::from_string("foo");
    Node* foo_list = foo_list_head;

    EXPECT_EQ(foo_list->data, 'f');
    // ASSERT instead of EXPECT means: end the test here if this fails, do not try to continue
    // running. This is useful to prevent early crashes.
    ASSERT_NE(foo_list->next, nullptr);

    foo_list = foo_list->next;
    EXPECT_EQ(foo_list->data, 'o');
    ASSERT_NE(foo_list->next, nullptr);

    foo_list = foo_list->next;
    EXPECT_EQ(foo_list->data, 'o');
    ASSERT_EQ(foo_list->next, nullptr);

    list::free(foo_list_head);
}

TEST(ListTests, Length) {
    Node* const head = list::from_string("foo");
    EXPECT_EQ(list::length(head), 3);
    list::free(head);
}

// Add remaining tests below. All tests should follow
// the format of `TEST(ListTests, <TestName>){}`.


TEST(ListCopy, CopyTest) {
    // Test copying an empty list
    Node* emptyList = list::from_string("");
    Node* copiedEmptyList = list::copy(emptyList);
    EXPECT_EQ(copiedEmptyList, nullptr);
    list::free(emptyList);  // Clean up if from_string allocates for empty strings

    // Test copying a list with a single item
    Node* singleItemList = list::from_string("a");
    Node* copiedSingleItemList = list::copy(singleItemList);
    ASSERT_NE(copiedSingleItemList, nullptr);
    EXPECT_EQ(copiedSingleItemList->data, 'a');
    EXPECT_EQ(copiedSingleItemList->next, nullptr);
    list::free(singleItemList);
    list::free(copiedSingleItemList);

    // Test copying a list with multiple items
    Node* multiItemList = list::from_string("abc");  // Assuming from_string creates a node for each char
    Node* copiedMultiItemList = list::copy(multiItemList);
    Node* currentOriginal = multiItemList;
    Node* currentCopy = copiedMultiItemList;
    while (currentOriginal != nullptr) {
        ASSERT_NE(currentCopy, nullptr);
        EXPECT_EQ(currentCopy->data, currentOriginal->data);
        currentOriginal = currentOriginal->next;
        currentCopy = currentCopy->next;
    }
    EXPECT_EQ(currentCopy, nullptr);
    list::free(multiItemList);
    list::free(copiedMultiItemList);

    // Test ensuring a deep copy
    Node* originalList = list::from_string("xy");
    Node* copiedList = list::copy(originalList);
    originalList->data = 'a';  // Modify original list
    originalList->next->data = 'b';
    EXPECT_EQ(copiedList->data, 'x');  // Copied list should remain unchanged
    EXPECT_EQ(copiedList->next->data, 'y');
    list::free(originalList);
    list::free(copiedList);
}
   



TEST(ListCompare, CompareTest) {
    // Equal lists
    list::Node* lhs = list::from_string("abc");
    list::Node* rhs = list::from_string("abc");
    EXPECT_EQ(list::compare(lhs, rhs), 0);
    list::free(lhs);
    list::free(rhs);

    // Unequal lists of equal length
    lhs = list::from_string("abc");
    rhs = list::from_string("abd");
    EXPECT_LT(list::compare(lhs, rhs), 0);
    list::free(lhs);
    list::free(rhs);

    // Lhs shorter than Rhs
    lhs = list::from_string("ab");
    rhs = list::from_string("abc");
    EXPECT_LT(list::compare(lhs, rhs), 0);
    list::free(lhs);
    list::free(rhs);

    // Lhs longer than Rhs
    lhs = list::from_string("abcd");
    rhs = list::from_string("abc");
    EXPECT_GT(list::compare(lhs, rhs), 0);
    list::free(lhs);
    list::free(rhs);

    // Empty lists
    lhs = list::from_string("");
    rhs = list::from_string("");
    EXPECT_EQ(list::compare(lhs, rhs), 0);
    list::free(lhs);
    list::free(rhs);
}

TEST(ListCompareWithLimit, CompareNTest) {
    // Equal lists within limit
    list::Node* lhs = list::from_string("abc");
    list::Node* rhs = list::from_string("abc");
    EXPECT_EQ(list::compare(lhs, rhs, 3), 0);
    list::free(lhs);
    list::free(rhs);

    // Unequal lists within limit
    lhs = list::from_string("abc");
    rhs = list::from_string("abd");
    EXPECT_LT(list::compare(lhs, rhs, 3), 0);
    list::free(lhs);
    list::free(rhs);

    // Equal lists exceeding limit
    lhs = list::from_string("abcdef");
    rhs = list::from_string("abcdef");
    EXPECT_EQ(list::compare(lhs, rhs, 3), 0);
    list::free(lhs);
    list::free(rhs);

    // Unequal lists exceeding limit
    lhs = list::from_string("abcXYZ");
    rhs = list::from_string("abcDEF");
    EXPECT_EQ(list::compare(lhs, rhs, 3), 0);  // Equal within the limit
    EXPECT_GT(list::compare(lhs, rhs, 6), 0);  // Unequal beyond the limit
    list::free(lhs);
    list::free(rhs);

    // Lhs shorter than limit
    lhs = list::from_string("ab");
    rhs = list::from_string("abc");
    EXPECT_LT(list::compare(lhs, rhs, 3), 0);  // Lhs is shorter, even within the limit
    list::free(lhs);
    list::free(rhs);
}