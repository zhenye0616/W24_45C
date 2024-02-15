#include "string.hpp"
#include <iostream> 
#include <compare>

String::String(const char *s) {
    head = list::from_string(s);
}

String::String(const String &s) {
    head = list::copy(s.head);
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
