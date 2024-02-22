#ifndef PICTURE_HPP
#define PICTURE_HPP

#include <iosfwd>
#include "shape.hpp"

// class Picture
class Picture{
    
public:
    
    Picture(); //done
    
    Picture(const Picture& other);
    
    Picture(Picture&& other);
    
    void swap(Picture& other);
    
    Picture& operator=(const Picture& other);
    Picture& operator =(Picture&& other);
    
    void add(const Shape& shape); //done
    
    void print_all(std::ostream& out) const; //done
    
    void draw_all(std::ostream& out) const;//done
    
    double total_area() const; //done
    
    ~Picture(); //done
    
private:
    
    struct ListNode{
        Shape* shape;
        ListNode* next;
    };
    
    ListNode * head;
    ListNode * tail;
    
};

#endif
