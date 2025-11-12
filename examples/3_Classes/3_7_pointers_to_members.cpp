// 3.7. Pointers to members.

#include <iostream>

struct S {
    std::string name;
    int age;

    void f(int add) {
        std::cout << age + add << std::endl;
    }
};

int main() {
    // Create pointer to struct's field: it's like a shift
    int S::* p = &S::age;

    S s{"Name", 34};
    s.*p = 100;
    std::cout << s.age << std::endl;

    S* ptr_s = &s;
    ptr_s->*p = 200;
    std::cout << s.age << std::endl;

    // Create pointer to struct's method: it's like a shift
    void (S::* pf)(int) = &S::f;
    (s.*pf)(1);
    (ptr_s->*pf)(2);
}