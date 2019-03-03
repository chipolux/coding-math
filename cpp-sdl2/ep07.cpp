#include <iostream>

#include "vector.h"


void show(const vec2& v)
{
    std::cout << "X: " << v.x << std::endl;
    std::cout << "Y: " << v.y << std::endl;
    std::cout << "Angle: " << v.get_angle() << std::endl;
    std::cout << "Length: " << v.get_length() << std::endl;
}

int main(int argc, char* args[])
{
    std::cout << "Initial Vector 10, 5:" << std::endl;
    vec2 v1(10, 5);
    show(v1);
    std::cout << std::endl;

    std::cout << "Vector, Angle pi / 6, Length 100:" << std::endl;
    v1.set_angle(3.14 / 6);
    v1.set_length(100);
    show(v1);
    std::cout << std::endl;

    std::cout << "Vector Addition (10, 5) + (3, 4):" << std::endl;
    v1.x = 10;
    v1.y = 5;
    vec2 v2(3, 4);
    show(v1 + v2);
    std::cout << std::endl;

    std::cout << "Vector Multiplication (10, 5) * 2:" << std::endl;
    std::cout << "Length 1: " << v1.get_length() << std::endl;
    std::cout << "Length 2: " << (v1 * 2).get_length() << std::endl;
    std::cout << std::endl;

    std::cout << "Vector, Angle pi / 6, Length 3:" << std::endl;
    vec2 v3(0, 0, 3, 3.14 / 6);
    show(v3);

    return 0;
}
