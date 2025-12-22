#pragma once

#include "shape.hpp"

class Rectangle : public Shape
{
private:
    double width;
    double height;

protected:
    Rectangle() {}
    Rectangle(const Rectangle &) {}
    Rectangle &operator=(const Rectangle &)
    {
        return *this;
    }

public:
    Rectangle(double width, double height) : width(width), height(height) {}
    virtual ~Rectangle() {}

public:
    double area() const
    {
        return width * height;
    };
};
