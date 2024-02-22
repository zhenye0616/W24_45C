#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"
#include <iostream>

class Rectangle : public Shape {
public:
    // Constructor
    Rectangle(Point center, std::string name, int width, int height);

    // Implement the area function
    double area() const override;
    // Implement the draw function
    
    void draw(std::ostream& out) const override;
    
    // Implement the clone function
    Rectangle* clone() const override;

protected:
    Rectangle(const Rectangle& other) = default;

private:
    int width, height;
};

#endif

