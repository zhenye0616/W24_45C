#ifndef LIST_HPP
#define LIST_HPP

#include <iosfwd>

namespace list {

struct Node {
    char data;
    Node* next;
};

// returns a linked list from a c-string s
Node* from_string(const char* s); //done tested

// deletes all nodes of linked list
void free(Node* head); //done

// prints linked list to ostream out
void print(std::ostream& out, Node* head); //done not tested 

// returns an exact duplicate of linked list starting at head
Node* copy(Node* head); //done tested

// similar to strcmp but for lists
int compare(Node* lhs, Node* rhs); //done tested

// similar to strncmp but for lists
int compare(Node* lhs, Node* rhs, int n);//done failed 

// counts number of nodes in linked list
int length(Node* head); //done tested

// returns reversed copy of linked list
Node* reverse(Node* head); //done tested

// returns new list containing all nodes of lhs followed by all nodes of rhs
Node* append(Node* lhs, Node* rhs); //done tested 

// returns index of node in list starting at head
int index(Node* head, Node* node); //done tested

// similar to strchr but for a linked list
Node* find_char(Node* head, char c); //done tested

// similar to strstr but for two linked lists
Node* find_list(Node* haystack, Node* needle); 

// get the nth node of linked list
Node* nth(Node* head, int n); //done tested

// get the last node of linked list
Node* last(Node* head);  //done tested

};  // namespace list

#endif
