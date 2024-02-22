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

};

#endif // SQUARE_HPP
