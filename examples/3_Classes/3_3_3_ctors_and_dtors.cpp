// 3.3.3 Contructors and destructors. Initializer Lists and Default Constructors.

#include <iostream>

struct A {
    int& r;       // No Default Contructor for this type
    const int c;  // No Default Contructor for this type
};

int x = 0;

struct B {
    int& r = x;
    const int c = 5;
};

struct C {
    int& r = x;
    const int c = 5;  // Can't modify const variable in constructor

    C() = default;

    C(int y) {
        r = y;        // Variable x will be modified
    }
};

struct S {
    int& r = x;
    const int c = 5;
    
    S() = default;

    S(int y, int c): r(y), c(c) {};  // Now I can modify reference and const. But it's UB: dangling reference
};

struct D {
    const int& r;

    D(): r(5) {}  // UB: lifetime expansion won't work for fields of classes
};

int main() {
    // A a;  // Default Constructor is deleted

    B b;     // There is Default Constructor

    C c1;    // There is Default Constructor
    
    std::cout << x << " -> ";
    C c2(99);
    std::cout << x << std::endl;
    std::cout << std::endl;

    S s1;
    std::cout << s1.r << ' ' << s1.c << std::endl;
    std::cout << std::endl;
    
    std::cout << x << " -> ";
    S s2(100, 500);
    std::cout << x << std::endl;
    std::cout << s2.r << ' ' << s2.c << std::endl;  // UB
    std::cout << std::endl;

    D d;
    std::cout << d.r << std::endl; // UB
}