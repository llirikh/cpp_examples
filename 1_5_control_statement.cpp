// 1.5. Control Statements

#include <iostream>

int main() {
    int x = 5;
    if (x == 5) {
        std::cout << "x = 5" << std::endl;
    }
    // >> x = 5

    std::cin >> x;
    switch (x) {
        case 1:
            std::cout << "A";
        case 2:
            std::cout << "B";
        default:
            std::cout << "C";
    }
    std::cout << std::endl;
    // 1 >> ABC
    // 2 >> BC
    // 3 >> C

    std::cin >> x;
    switch (x) {
        case 1:
            std::cout << "A";
        case 2:
            std::cout << "B";
            break;
        default:
            std::cout << "C";
    }
    std::cout << std::endl;
    // 1 >> AB
    // 2 >> B
    // 3 >> C
}