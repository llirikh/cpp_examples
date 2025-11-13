// V. Polymorphism and virtual functions
// 5.1. Idea of virtual functions

#include <iostream>

struct Base {                                     // Polymorphic Type
    void f() { std::cout << 1 << '\n'; }
    virtual void v() { std::cout << 1 << '\n'; }

    virtual ~Base() {
        std::cout << "~Base " << '\n';
    }
};

struct Derived: Base {
    void f() { std::cout << 2 << '\n'; }
    void v() { std::cout << 2 << '\n'; }

    int* p = new int(0);
    ~Derived() {
        std::cout << "~Derived ";
        delete p;
    }
};

void print(Base& b) {
    b.f();
    b.v();
}

int main() {

    // Virtual functions
    Derived d;
    print(d);

    // Virtual Destructors
    Base* b = new Derived();
    delete b;
}