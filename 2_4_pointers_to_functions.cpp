// 2.4. Pointers to functions

#include <iostream>
#include <algorithm>

void print(int* begin, int* end) {
    for (int* ptr = begin; ptr < end; ++ptr) {
        std::cout << *ptr << ' ';
    }
    std::cout << std::endl;
}

bool cmp(int lhs, int rhs) {
    return lhs > rhs;
}

int main() {
    int a[5] = {4, 5, 2, 5, 7};

    std::sort(a, a + 5);
    print(a, a + 5);

    std::sort(a, a + 5, &cmp);
    print(a, a + 5);

    bool (*ptr1)(int, int) = &cmp; // How to declare pointer to function
    std::sort(a, a + 5, ptr1);
    print(a, a + 5);

    bool (*ptr2)(int, int) = cmp; // Function To Pointer Conversion
    std::sort(a, a + 5, ptr2);
    print(a, a + 5);
}
