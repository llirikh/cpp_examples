// 4.1. Protected inheritance

#include <iostream>

struct Granny {
    int x;
    void f() {}
};

struct Mom: protected Granny {
    int y;
    void g() {}
};

struct Son: Mom {
    int z;
    void h() {
        std::cout << x << '\n';
    }
};

int main() {
    Son s;

    s.z;    // OK: public field of Son
    s.y;    // OK: public inheritance of Mom
    s.x;    // CE: protected inheritance of Granny
    s.h();  // OK: protected inheritance of Granny
}