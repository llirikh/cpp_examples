// 3.5.1 Const methods and mutable fields

#include <iostream>

struct A {
    void f() {
        std::cout << "A: Hello" << std::endl;
    }
};

struct B {
    void f() const {
        std::cout << "B: Hello" << std::endl;
    }
};

struct C {
    mutable int x = 0;
    void f() const {
        ++x;
    }
};

int main() {
    const A a1;
    // a.f();              // CE: Non-const method

    A a2;
    const A& ref_a2 = a2;
    // ref_a2.f();         // CE: Non-const method

    const B b1;
    b1.f();                // OK

    B b2;
    const B& ref_b2 = b2;
    ref_b2.f();            // OK

    C c;
    c.f();
    std::cout << "C: " << c.x << std::endl;

}