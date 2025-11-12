// IV. Inheritance
// 4.1. Public, private and protected inheritance

#include <iostream>

struct Base {
  protected:
    int x = 0;

  public:
    void f() {}
};

struct Derived : Base {
    int y = 1;
    void g() {
        std::cout << x << '\n';
    }
};

int main() {
    Derived d;

    d.g();   // OK: x is protected
    // d.x;  // CE: x is protected and I try to use it not from Derived
}