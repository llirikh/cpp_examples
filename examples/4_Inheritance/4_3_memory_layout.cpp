// 4.3. Memory layout, contructors and destructors in case of inheritance

#include <iostream>

struct Type {
    Type(int val) { std::cout << "Type" << val << ' '; }
    ~Type() { std::cout<< "~Type" << ' '; }
};

struct Base {
    Type x;
    Base(int x): x(x) {
        std::cout << "Base" << ' ';
    }
    ~Base() {
        std::cout << "~Base" << ' ';
    }
};

struct Derived: Base {
    Type y;
    Derived(int y): Base(0), y(y) {
        std::cout << "Derived" << ' ';
    }
    ~Derived() {
        std::cout << "~Derived" << ' ';
    }
};

int main() {
    Derived d(1);            // Type0 Base Type1 Derived
    std::cout << std::endl;
    return 0;                // ~Derived ~Type ~Base ~Type
}