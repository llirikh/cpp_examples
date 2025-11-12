// 4.2. Visisbility and accesebility of field amd methods

#include <iostream>

struct Base {
    void f() { std::cout << 1 << std::endl; }
    void g(int) { std::cout << 1 << std::endl; }
    void h() { std::cout << 1 << std::endl; }
};

struct Derived : Base {
    void f() { std::cout << 2 << std::endl; }
    void g(double) { std::cout << 2 << std::endl; }
  private:
    void h(int) { std::cout << 2 << std::endl; }
};

int main() {
    Derived d;

    d.f();
    d.g(0);

 // d.h();        // CE: expected 1 arguement and h is private. Can't see Base::h() - it's overwritten by Derived::h()
    d.Base::h();
}