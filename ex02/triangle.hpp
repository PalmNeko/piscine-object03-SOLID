#pragma once

#include "shape.hpp"

class Triangle : public Shape
{
private:
    double base;
    double height;

protected:
    Triangle() {}
    Triangle(const Triangle &) {}
    Triangle &operator=(const Triangle &)
    {
        return *this;
    }

public:
    Triangle(double base, double height) : base(base), height(height) {}
    virtual ~Triangle() {}

public:
    double area() const
    {
        return base * height / 2.0;
    };
};
