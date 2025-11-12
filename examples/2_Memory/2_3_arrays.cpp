// 2.4. Arrays

#include <iostream>

int main() {
    int a[5];                      // Array is allocated in Stack
    for (int i = 0; i < 5; ++i) {
        std::cout << a[i] << ' ';  // UB: values are not initialized 
    }
    std::cout << std::endl;

    int b[5] = {1, 2}; // other values will be default (0)
    for (int i = 0; i < 5; ++i) {
        std::cout << b[i] << ' ';
    }
    std::cout << std::endl;

    int c[5] = {1, 2, 3, 4, 5};
    std::cout << c[-1] << ' ' << c[5] << std::endl; // UB
    std::cout << std::endl;

    // Segmentation Fault
    if (false) {
        std::cout << c[10000000] << std::endl; 
    }

    // Stack Overflow
    if (false) {
        // int d[10'000'000]; 
    }

    static int e[10'000'000]; // No Stack Overflow because of Local Static Variable

    int f[5] = {0, 1, 2, 3, 4};
    std::cout << *(f + 2) << std::endl; // f[2] == *(f + 2)
    std::cout << std::endl;

    int* p = f + 3;
    std::cout << p[-1] << std::endl;
    std::cout << std::endl;

    // CE: Not supported operations for arrays
    if (false) {
        int a[5] = {};
        int b[2] = {};
        // a = b;
        // a += 1;
        // ++a;
    }
}