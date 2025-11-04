// 3.5.2. Static methods. Singletone.

#include <iostream>

struct S {
    static int x;     // Can't define in struct's scope
    static void f();
};

int S::x = 5;
void S::f() {
    std::cout << "Hello" << std::endl;
}


class Singletone {                                      // Singletone: Only inctance for whole program
  public:
    static Singletone& getObject();

  private:
    static Singletone* ptr;

    Singletone() {}
    Singletone(const Singletone&) = delete;             // Singltone s(other) - is forbidden
    Singletone& operator=(const Singletone&) = delete;  // s = other_s - is forbidden 
};

Singletone* Singletone::ptr = nullptr;
Singletone& Singletone::getObject() {
    if (ptr == nullptr) {
        ptr = new Singletone();
    }
    return *ptr;
}


int main() {
    std::cout << S::x << std::endl;
    S::f();

    S a;
    S b;

    a.x = 100;
    std::cout << a.x << ' ' << b.x << std::endl;
    std::cout << std::endl;

    Singletone& s1 = Singletone::getObject();
    Singletone& s2 = Singletone::getObject();
    std::cout << (&s1 == &s2) << std::endl;
}