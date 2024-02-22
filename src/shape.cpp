#include "shape.hpp"
#include <iostream>


Shape::Shape(Point center, std::string name) : center(center), name(name) {
        std::cout << "Shape '" << name << "' created.\n";
    }

Shape::~Shape() {
        std::cout << "Shape '" << name << "' destroyed.\n";
    }

void Shape::print(std::ostream& out) const {
    out << name << " at (" << center.x << ", " << center.y << ") area = " << area() << "\n";
}
