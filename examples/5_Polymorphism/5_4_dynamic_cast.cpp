// 5.4.  RTTI and dynamic cast

#include <iostream>

struct Base {
    int x = 0;
    virtual void f() {};
    virtual ~Base() = default;
};

struct Derived: Base {
    int y = 1;
    void f() override {};
};

int main() {
    Derived d;
    Base& b = d;

    // RTTI: Run-Time Type Information 
    Derived* ptr_d = dynamic_cast<Derived*>(&b);  // Works only with Polymorhic Classes 
    if (ptr_d) {                                  // If b is not originally Derived than nullptr
        std::cout << ptr_d->y << '\n';
    }

    std::cout << typeid(b).name() << std::endl << system("c++filt -t 7Derived") << '\n';
}