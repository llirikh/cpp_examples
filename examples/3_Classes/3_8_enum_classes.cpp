// 3.8. Enum classes

#include <iostream>

enum class E : int8_t {  // It will locate only 1 byte (not 2 byte as int)
    White = 2,
    Black = 5,
    Grey = 9
};

int main() {
    E e = E::White;
    std::cout << static_cast<int>(e) << std::endl;
}