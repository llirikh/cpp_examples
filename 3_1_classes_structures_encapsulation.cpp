// III. Basics of OOP.
// 3.1. Classes, structures and encapsulation

#include <iostream>

struct S {
    int x;
    double y;

    void f(int x);
};

void S::f(int x) {
    std::cout << x << std::endl;
    std::cout << (*this).x << ' ' << this->x << std::endl;
}

int main() {
    S s{1, 2.5};                                  // Aggregate initialization
    std::cout << sizeof(s) << std::endl;          // Not 4 + 8 = 12 bytes, but 16 bytes. Because of alignment.
    std::cout << s.x << ' ' << s.y << std::endl;
    std::cout << std::endl;

    s.f(5);
}