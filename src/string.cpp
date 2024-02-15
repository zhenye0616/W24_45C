#include "string.hpp"
#include <iostream> 
#include <compare>

String::String(const char *s) {
    head = list::from_string(s);
}

String::String(const String &s) {
    head = list::copy(s.head);
}


String::String(list::Node* newHead) : head(newHead) {
}


String::~String() {
    list::free(head);
}

void String::print(std::ostream &out) const {
    list::print(out, head);
}


std::ostream &operator<<(std::ostream &out, const String &s) {
    s.print(out);
    return out;  
}


int String::size() const {
    return list::length(head); 
}


String& String::operator=(String &&s) {
    if (this != &s) { // Self-assignment check
        list::free(head); // Free the current list
        head = s.head; // Transfer ownership
        s.head = nullptr; // Ensure moved-from object is in a safe state
    }
    return *this;
}



String& String::operator=(const String &s) {
    if (this != &s) { // Self-assignment check
        list::Node* newHead = list::copy(s.head); // Deep copy the list
        list::free(head); // Free the old list
        head = newHead; // Assign the copied list
    }
    return *this;
}


bool String::operator==(const String &s) const {
    return list::compare(head, s.head) == 0; // Utilizes the compare function
}


String String::reverse() const {
    return String(list::reverse(head)); // Utilizes the reverse function and private constructor
}


char String::operator[](int index) const {
    if (!in_bounds(index)) throw std::out_of_range("Index out of bounds");
    return list::nth(head, index)->data;
}

bool String::in_bounds(int index) const {
    int len = list::length(head); 
    return index >= 0 && index < len;
}

int String::indexOf(char c) const {
    list::Node* node = list::find_char(head, c);
    if (node == nullptr) {
        return -1;
    }

    int index = 0;
    for (list::Node* current = head; current != node; current = current->next, ++index);
    return index;
}

int String::indexOf(const String &s) const {
    list::Node* sublistStart = list::find_list(head, s.head);
    return list::index(head, sublistStart);
}



std::strong_ordering String::operator<=>(const String &s) const {
    int cmpResult = list::compare(this->head, s.head);

    if (cmpResult < 0) {
        return std::strong_ordering::less;
    } else if (cmpResult > 0) {
        return std::strong_ordering::greater;
    } else {
        return std::strong_ordering::equal;
    }
}

std::istream &operator>>(std::istream &in, String &s) {
    std::string temp;
    in >> temp;
    s = String(temp.c_str());
    return in;
}

String& String::operator+=(const String &s) {
    if (head == nullptr) {
        head = list::copy(s.head);
    } else {
        list::Node* last = head;
        for (; last->next != nullptr; last = last->next);
        last->next = list::copy(s.head);
    }
    return *this;
}
