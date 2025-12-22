#pragma once

class Shape
{
protected:
    Shape(const Shape &) {}
    Shape &operator=(const Shape &)
    {
        return *this;
    }

public:
    Shape() {}
    virtual ~Shape() {}

public:
    virtual double area() const = 0;
};
