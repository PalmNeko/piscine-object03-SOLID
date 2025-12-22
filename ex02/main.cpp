#include "triangle.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include <typeinfo>
#include <iostream>
#include <cassert>

void test(const Shape &shape, double expected);

int main()
{
    test(Circle(3, 3.125), 28.125);
    test(Rectangle(5, 8), 40);
    test(Triangle(4, 8), 16);
    return (0);
}

void test(const Shape &shape, double expected)
{
    std::cout << "test: " << typeid(shape).name() << std::endl;

    assert(shape.area() == expected);
    std::cout << shape.area() << std::endl;
}
