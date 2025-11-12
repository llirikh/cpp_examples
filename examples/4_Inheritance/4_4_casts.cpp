// 4.4. Casts in case of inheritance

#include <iostream>

struct Base {
    int x = 1;
};

struct Derived: Base {
    int y = 2;
};

void f(Base& b) {
    std::cout << b.x << std::endl;
}

// Slicing: constructor Base(const Derived& other) will be auto-generated
void f1(Base b) {
    std::cout << b.x << std::endl;
}

int main() {
    Derived d;
    f(d);
    f1(d);
}