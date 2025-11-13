// 5.1. More complicated examples with virtual functions

#include <iostream>

struct Base {
    virtual void f() const { std::cout << 1 << '\n'; }
    virtual void g() const { std::cout << 1 << '\n'; }

    virtual void h() final { std::cout << 1 << '\n'; }
};

struct Derived: Base {
    void f() { std::cout << 2 << '\n'; }
    // void g() override { std::cout << 2 << '\n'; }  // CE: there's no function with the same signature in Base
    // void h() { std::cout << 1 << '\n'; }           // CE: can't override final function Base::h()
};


struct Granny {
    virtual void f() { std::cout << 1 << '\n'; }
    virtual void g() { std::cout << 2 << '\n'; }
};

struct Mom: Granny {
    void f() override { std::cout << 2 << '\n'; }

  private:
    void g() override { std::cout << 2 << '\n'; }
};

struct Son: Mom {
    void f() final { std::cout << 3 << '\n'; }
    void g() final { std::cout << 3 << '\n'; }
};


int main() {

    // For virtual fucntions it's needed to have the same signature
    Derived d;
    Base& b = d;
    b.f();
    std::cout << std::endl;


    // Son doesn't exist, so Son::f() doesn't exist too
    Mom m;
    Granny& g = m;
    g.f();

    // Virtuality is run-time abstraction
    int x;
    std::cin >> x;
    
    Granny* g_or_m = (x % 2 == 0) ? new Granny() : new Mom();
    g_or_m->f();

    // No matter if function is private, becuse of accesebility is compile-time abstraction
    g.g();

}