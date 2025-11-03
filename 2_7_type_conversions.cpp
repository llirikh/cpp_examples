// 2.7. Type conversions

#include <iostream>

void f(const int& val) {
    int& non_const_val = const_cast<int&>(val);
    non_const_val = 7;
}

int main() {
    {
        int x = 1729;
        double y = static_cast<double>(x);
        std::cout << y << std::endl;
        std::cout << std::endl;
    }

    {
        int x = 1729;
        std::cout << reinterpret_cast<double&>(x) << std::endl; // UB: bytes of double and int are different
    }

    {
        int x = 1729;
        double& y = reinterpret_cast<double&>(x);
        y = 3.14;                                  // UB: the same reason
        std::cout << x << std::endl;
        std::cout << std::endl;
    }

    if (false) {
        int x = 1729;
        int* p_int = &x;
        std::string* p_str = reinterpret_cast<std::string*>(p_int);
        std::cout << *p_str << std::endl;                              // UB: Segmentation Fault
    }

    {
        const int c = 5;
        int& cc = const_cast<int&>(c);             // UB: const_cast is for ordinary non-const types
        cc = 7;
        std::cout << c << ' ' << cc << std::endl;  // 5 7
    }

    {
        int c = 5;
        f(c);                         // c is not const ordinary, so it will be impacted by f(c) 
        std::cout << c << std::endl;
    }


}