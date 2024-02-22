#include "rectangle.hpp"
#include "shape.hpp"

#ifndef SQUARE_HPP
#define SQUARE_HPP


class Square : public Rectangle {
public:
    Square(Point center, std::string name, int side);

    Square* clone() const override;

protected:

    Square(const Square& other) = default;

    // You might also want to define a protected move constructor if needed
    // Square(Square&& other) = default;
};

#endif // SQUARE_HPP
