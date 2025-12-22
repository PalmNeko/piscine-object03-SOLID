#pragma once

#include "shape.hpp"

class Circle : public Shape
{
private:
    double radius;
    double PI;

protected:
    Circle() {}
    Circle(const Circle &) {}
    Circle &operator=(const Circle &)
    {
        return *this;
    }

public:
    Circle(double radius, double PI = 3.141592653589793) : radius(radius), PI(PI) {}
    virtual ~Circle() {}

public:
    double area() const
    {
        return radius * radius * PI;
    };
};
