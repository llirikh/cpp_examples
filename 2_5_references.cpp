// 2.5. References

#include <iostream>

void swap(int& lhs, int& rhs) {
    int tmp = lhs;
    lhs = rhs;
    rhs = tmp;
}

int& g(int& ref) {
    std::cout << ref << " -> " << ++ref << std::endl;
    return ref;
}

int& f(int& ref) {
    return ref;
}

int& dangling_ref(int& a) {
    int b = a;
    return b;
}

int main() {

    {
        int x = 5;
        int& y = x;                                   // Reference need to be initialized by lvalue, otherwise CE

        int z = 0;
        y = z;

        std::cout << x << ' ' << y << std::endl;
    }

    {
        int x = 5;
        int y = 9;
        swap(x, y);
        std::cout << x << ' ' << y << std::endl;
        std::cout << std::endl;
    }

    {
        int x = 0;
        g(x) = 6;
        std::cout << x << std::endl;
        std::cout << std::endl;
    }

    {
        int x = 3;

        int& a = f(x);                                        // No copy
        int b = f(x);                                         // Copy of x : Lvalue-to-rvalue conversion

        ++b;
        std::cout << x << ' ' << a << ' ' << b << std::endl;
        std::cout << std::endl;
    }

    // Dangling Reference
    if (false) {
        int x = 0;
        int y = dangling_ref(x);
        std::cout << y;               // Segmentation Fault : Was returned reference to the local variable
    }

    {
        int a[5] = {};
        int (&b)[5] = a;                  // Reference to array

        b[0] = 100;
        std::cout << a[0] << std::endl;
    }

}