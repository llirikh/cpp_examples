// 3.2. Access Modifiers

#include <iostream>

class C {
  public:
    void f(int);
    friend void g(C, int);  // to get access to private fields of C from outter function g. Fuck friends off!

  private:
    int x = 3;
};

void C::f(int y) {
    std::cout << x + y << std::endl;
}

void g(C c, int y) {
    std::cout << c.x + y << std::endl;
}


int main() {
    C c;

    c.f(5);
    std::cout << std::endl;

    std::cout << reinterpret_cast<int&>(c) << std::endl; // UB: dirty method to get access to private variable
    std::cout << std::endl;

    g(c, 5);
    std::cout << std::endl;
}