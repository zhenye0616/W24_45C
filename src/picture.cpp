#include "picture.hpp"
#include <iostream>
#include <utility>

// Constructor
Picture::Picture() : head(nullptr), tail(nullptr) {}

    // Add a shape to the picture
void Picture::add(const Shape& shape) {
    Shape* newShape = shape.clone();  // Assuming Shape has a clone() method
    ListNode* newNode = new ListNode{newShape, nullptr};
    if (head == nullptr) {
        head = newNode;
    } else {
        tail->next = newNode;
    }
    tail = newNode;
}

// Print all shapes in the picture
void Picture::print_all(std::ostream& out) const {
    ListNode* current = head;
    while (current != nullptr) {
        current->shape->print(out); 
        current = current->next;
    }
}

// Destructor
Picture::~Picture() {
    ListNode* current = head;
    while (current != nullptr) {
        ListNode* next = current->next;
        delete current->shape; 
        delete current;
        current = next;
    }
}

void Picture::draw_all(std::ostream& out) const {
    ListNode* current = head;  
    while (current != nullptr) {  
        current->shape->draw(out); 
        current = current->next;
    }
}

double Picture::total_area() const {
    double total = 0.0; 
    ListNode* current = head;
    while (current != nullptr) {
        total += current->shape->area();
        current = current->next; 
    }
    return total;
}

Picture::Picture(const Picture& other) : head(nullptr), tail(nullptr) {
    ListNode* current = other.head;
    while (current != nullptr) {
        this->add(*current->shape); 
        current = current->next;
    }
}


Picture::Picture(Picture&& other) : head(other.head), tail(other.tail) {
    other.head = nullptr;
    other.tail = nullptr;
}

Picture& Picture::operator=(const Picture& other) {
    Picture temp(other); 
    this->swap(temp);  
    return *this;
}

Picture& Picture::operator=(Picture&& other){
    Picture temp(std::move(other));
    swap(temp);
    return *this;
}

void Picture::swap(Picture& other) {
    using std::swap;
    swap(head, other.head);
    swap(tail, other.tail);
}

