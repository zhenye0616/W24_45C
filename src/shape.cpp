#include "shape.hpp"
#include <iostream>


Shape::Shape(Point center, std::string name) : center(center), name(name) {
        std::cout << "Shape '" << name << "' created.\n";
    }

Shape::~Shape() {
        std::cout << "Shape '" << name << "' destroyed.\n";
    }

void Shape::print(std::ostream& out) const {
        out << "Shape Name: " << name << "\n";
        out << "Center Position: (" << center.x << ", " << center.y << ")\n";
    }