#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "shape.hpp"
#include <iostream>

class Triangle : public Shape {
public:
    // Constructor
    Triangle(Point center, std::string name, int base, int height);

    // Implement the area function
    double area() const override;

    // Implement the draw function
    void draw(std::ostream& out) const override;
    
    Triangle* clone() const override;

protected:
    // Copy constructor (protected to prevent slicing)
    Triangle(const Triangle& other) = default;

private:
    int base, height;  // Base and height of the triangle
};

#endif // TRIANGLE_HPP
