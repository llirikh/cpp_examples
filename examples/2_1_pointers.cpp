// II Compound types

// 2.1. Pointers

#include <iostream>

void wrong_swap(int x, int y) {
    int tmp = x;
    x = y;
    y = tmp;
}

void c_style_swap(int* x, int* y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

int main() {
    int x = 0;
    int* p = &x;
    std::cout << &x << std::endl; // &: T -> T*  -- Get address
    std::cout << *p << std::endl; // *: T* -> T  -- Dereferencing
    std::cout  << std::endl;

    int a = 2131, b = 2354;
    int* a_ptr = &a;
    int* b_ptr = &b;
    std::cout << a_ptr << std::endl;
    std::cout << a_ptr + 1 << std::endl; // +(T*, int) -> T*  -- p + sizeof T
    std::cout << b_ptr << std::endl;
    std::cout << std::endl;

    int var1 = 0;
    int* ptr = &var1;
    {
        int var2 = 5;
        ptr = &var2;
    }
    std::cout << *ptr << std::endl; // UB, but probably 5
    std::cout << std::endl;

    a = 0;
    b = 1;
    wrong_swap(a, b);
    std::cout << a << ' ' << b << std::endl;
    std::cout << std::endl;

    a = 0;
    b = 1;
    c_style_swap(&a, &b);
    std::cout << a << ' ' << b << std::endl;
    std::cout << std::endl;


    return 0;
}