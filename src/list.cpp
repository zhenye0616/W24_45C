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
    for (int i = 0; i < n; ++i) {
        if (lhs == nullptr) {
            return -1;
        }
        if (rhs == nullptr) {
            return 1;
        }
        if (lhs->data != rhs->data) {
            return lhs->data < rhs->data ? -1 : 1;
        }
        lhs = lhs->next;
        rhs = rhs->next;
    }
    return 0;
}


list::Node* list::reverse(Node* head){
    Node* newHead = list::copy(head);
    Node* prev = nullptr;
    Node* next = nullptr; 
    for (Node* current = newHead; current != nullptr; current = next){
        next = current -> next;
        current -> next = prev;
        prev = current;
    }
    return prev;
}


list::Node* list::append(Node* lhs, Node* rhs) {
    if (lhs == nullptr) {
        return rhs;
    }
    if (rhs == nullptr) {
        return lhs;
    }
    Node* lastNode = nullptr;
    for (lastNode = lhs; lastNode->next != nullptr; lastNode = lastNode->next) {
    }
    lastNode->next = rhs;
    return lhs;
}

int list::index(Node* head, Node* node){
    int count = 0;
    for (Node* temp = head; temp != nullptr; temp = temp -> next, count++){
        if (temp == node){
            return count;
            }
    }
    return -1;
}

list::Node* list::find_char(Node* head, char c){
    for (Node* temp = head; temp != nullptr; temp = temp -> next){
        if (temp -> data == c){
            return temp;
        }
    }
    return nullptr;
}

list::Node* list::nth(Node* head, int n) {
    Node* temp = head;
    int index;

    // Use a for loop to traverse up to the nth node or the end of the list
    for (index = 0; temp != nullptr && index < n; index++) {
        temp = temp->next;
    }

    // If index equals n, current points to the nth node; otherwise, n was out of bounds, and current is nullptr
    return temp;
}

list::Node* list::last(Node* head) {
    if (head == nullptr) {
        return nullptr;
    }

    Node* temp = head;
    for (; temp->next != nullptr; temp = temp->next) {
    }
    return temp;
}

list::Node* list::find_list(Node* haystack, Node* needle) {
    // If needle is empty, it is considered found at the beginning of haystack
    if (!needle) {
        return haystack;
    }

    for (Node* haystackTemp = haystack; haystackTemp != nullptr; haystackTemp = haystackTemp->next) {
        Node* currentHaystack = haystackTemp;
        Node* currentNeedle = needle;

        // Use a nested for loop to check if the sequence starting from currentHaystack matches needle
        for (; currentNeedle != nullptr && currentHaystack != nullptr && currentHaystack->data == currentNeedle->data; currentHaystack = currentHaystack->next, currentNeedle = currentNeedle->next) {
        }
        
        if (!currentNeedle) {
            return haystackTemp;
        }
    }
    return nullptr;
}
