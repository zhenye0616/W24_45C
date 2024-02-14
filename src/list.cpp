#include "list.hpp" 
#include <iostream> 


list::Node* list::from_string(const char* s) {
    if (s == nullptr || *s == '\0') {
        return nullptr; // Return nullptr for empty string
    }

    Node* head = new Node(*s, nullptr); // Create head node using constructor
    Node* current = head;

    for (const char* p = s + 1; *p != '\0'; ++p) {
        current->next = new Node(*p, nullptr); // Use constructor for new nodes
        current = current->next; // Move to the new node
    }

    return head; // Return the head of the list
}

int list::length(Node* head) {
    int count = 0; // Use count as the variable name for consistency
    for (Node* temp = head; temp != nullptr; temp = temp->next) {
        ++count; // Increment count for each node
    }
    return count; // Return the total count
}

void list::free(Node* head) {
    Node* temp = nullptr; // Temporary pointer to hold the next node
    for (Node* current = head; current != nullptr; current = temp) {
        temp = current->next;
        delete current; 
    }
}

void list::print(std::ostream& out, Node* head){
    for(Node* temp = head; temp != nullptr; temp = temp -> next){
        out << temp -> data;
        if (temp -> next != nullptr){
            out << "->";
        }
    }
}

list::Node* list::copy(Node* head){
    if (head == nullptr){
        return nullptr;
    }
    
    Node* newHead = new Node(head->data, nullptr);
    Node* newTail = newHead; 
    
    for (Node* temp = head -> next; temp != nullptr; temp = temp -> next){
        newTail->next = new Node(temp->data, nullptr);
        newTail = newTail->next; 
    }
    return newHead;
}

int list::compare(Node* lhs, Node* rhs){
    while (lhs != nullptr && rhs != nullptr) {
        if (lhs->data != rhs->data) {
            return lhs->data < rhs->data ? -1 : 1;
        }
        lhs = lhs->next;
        rhs = rhs->next;
    }
    if (lhs == nullptr && rhs == nullptr) {
        return 0;
    }
    return lhs == nullptr ? -1 : 1;
}

int list::compare(Node* lhs, Node* rhs, int n) {
    for (int i = 0; lhs != nullptr && rhs != nullptr && i < n; ++i, lhs = lhs->next, rhs = rhs->next) {
        if (lhs->data != rhs->data) {
            // Return -1 if lhs data is less than rhs data, 1 otherwise
            return lhs->data < rhs->data ? -1 : 1;
        }
    }
    return 0;
}
