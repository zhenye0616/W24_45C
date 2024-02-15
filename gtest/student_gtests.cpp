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


TEST(ListReverse, ReverseTest) {
    // Test reversing an empty list
    list::Node* emptyList = nullptr;
    list::Node* reversedEmptyList = list::reverse(emptyList);
    EXPECT_EQ(reversedEmptyList, nullptr);

    // Test reversing a list with a single node
    list::Node* singleNodeList = list::from_string("a");
    list::Node* reversedSingleNodeList = list::reverse(singleNodeList);
    ASSERT_NE(reversedSingleNodeList, nullptr);
    EXPECT_EQ(reversedSingleNodeList->data, 'a');
    EXPECT_EQ(reversedSingleNodeList->next, nullptr);
    list::free(reversedSingleNodeList);

    // Test reversing a list with multiple nodes
    list::Node* multiNodeList = list::from_string("abc");
    list::Node* reversedMultiNodeList = list::reverse(multiNodeList);
    ASSERT_NE(reversedMultiNodeList, nullptr);

    // Check if the reversed list is "cba"
    char expectedData[] = {'c', 'b', 'a'};
    list::Node* currentNode = reversedMultiNodeList;
    for (char expectedChar : expectedData) {
        ASSERT_NE(currentNode, nullptr);
        EXPECT_EQ(currentNode->data, expectedChar);
        currentNode = currentNode->next;
    }
    EXPECT_EQ(currentNode, nullptr);  // Ensure the list ends here
    list::free(reversedMultiNodeList);

    // Clean up the original lists
    list::free(singleNodeList);
    list::free(multiNodeList);
}


TEST(ListAppend, AppendsNonEmptyListsCorrectly) {
    // Create two non-empty lists
    list::Node* lhs = list::from_string("123");
    list::Node* rhs = list::from_string("456");

    // Append rhs to lhs
    list::Node* result = list::append(lhs, rhs);

    // Expected result after appending
    const char* expected = "123456";

    // Verify the result list matches the expected string
    list::Node* current = result;
    for (const char* p = expected; *p != '\0' && current != nullptr; ++p, current = current->next) {
        EXPECT_EQ(*p, current->data) << "Lists do not match at character " << *p;
    }

    // Verify we've reached the end of the result list
    EXPECT_EQ(nullptr, current) << "Result list is longer than expected";

    // Clean up
    list::free(lhs);  // Assuming append does not alter lhs
    list::free(rhs);  // Assuming append creates a deep copy of rhs, original rhs needs to be freed
    list::free(result);  // Free the result list
}




TEST(ListIndex, ListTest) {
    // Create a test list
    list::Node* head = list::from_string("abcd");  // Assuming from_string creates a list: a -> b -> c -> d

    // Test finding the index of the head node
    EXPECT_EQ(list::index(head, head), 0);

    // Test finding the index of a middle node
    list::Node* middleNode = head->next;  // Assuming this is 'b'
    EXPECT_EQ(list::index(head, middleNode), 1);

    // Test finding the index of the last node
    list::Node* lastNode = head->next->next->next;  // Assuming this is 'd'
    EXPECT_EQ(list::index(head, lastNode), 3);

    // Clean up
    list::free(head);
}

TEST(ListFindChar, FindCharTest) {
    // Create a test list
    list::Node* head = list::from_string("abcde");  // Assuming from_string creates a list: a -> b -> c -> d -> e

    // Test finding a character at the beginning of the list
    list::Node* foundNode = list::find_char(head, 'a');
    ASSERT_NE(foundNode, nullptr);
    EXPECT_EQ(foundNode->data, 'a');

    // Test finding a character in the middle of the list
    foundNode = list::find_char(head, 'c');
    ASSERT_NE(foundNode, nullptr);
    EXPECT_EQ(foundNode->data, 'c');

    // Test finding a character at the end of the list
    foundNode = list::find_char(head, 'e');
    ASSERT_NE(foundNode, nullptr);
    EXPECT_EQ(foundNode->data, 'e');

    // Test searching for a character that doesn't exist in the list
    foundNode = list::find_char(head, 'z');
    EXPECT_EQ(foundNode, nullptr);

    // Clean up
    list::free(head);
}
TEST(ListNth, NthTest) {
    list::Node* head = list::from_string("abcde");  // Assuming from_string creates a list: a -> b -> c -> d -> e

    // Test accessing valid indices
    EXPECT_EQ(list::nth(head, 0)->data, 'a');  // First element
    EXPECT_EQ(list::nth(head, 2)->data, 'c');  // Middle element
    EXPECT_EQ(list::nth(head, 4)->data, 'e');  // Last element

    // Since the behavior for out-of-bounds access is undefined, we do not test it

    // Clean up
    list::free(head);
}


TEST(ListLast, LastTest) {
    // Create a test list
    list::Node* head = list::from_string("abcde");  // Assuming from_string creates a list: a -> b -> c -> d -> e

    // Test finding the last node in a non-empty list
    EXPECT_EQ(list::last(head)->data, 'e');

    // Clean up
    list::free(head);
}

TEST(ListFindList, FindListTest) {
    // Create a test list (haystack)
    list::Node* haystack = list::from_string("abcdef");  // Assuming from_string creates a list: a -> b -> c -> d -> e -> f

    // Test finding a sublist at the beginning of the list
    list::Node* needle1 = list::from_string("abc");
    EXPECT_EQ(list::find_list(haystack, needle1), haystack);  // Should find at the beginning

    // Test finding a sublist in the middle of the list
    list::Node* needle2 = list::from_string("cde");
    list::Node* expected2 = haystack->next->next;  // 'c' node
    EXPECT_EQ(list::find_list(haystack, needle2), expected2);  // Should find in the middle

    // Test finding a sublist at the end of the list
    list::Node* needle3 = list::from_string("ef");
    list::Node* expected3 = haystack->next->next->next->next;  // 'e' node
    EXPECT_EQ(list::find_list(haystack, needle3), expected3);  // Should find at the end

    // Test searching for a sublist that doesn't exist in the list
    list::Node* needle4 = list::from_string("xyz");
    EXPECT_EQ(list::find_list(haystack, needle4), nullptr);  // Should not find

    // Test searching for an empty sublist in a non-empty list
    list::Node* needle5 = nullptr;  // Empty sublist
    EXPECT_EQ(list::find_list(haystack, needle5), haystack);  // Should find at the beginning (empty sublist)

    // Clean up
    list::free(haystack);
    list::free(needle1);
    list::free(needle2);
    list::free(needle3);
    list::free(needle4);
}