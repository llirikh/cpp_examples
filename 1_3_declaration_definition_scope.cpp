// 1.3 Declarations, definitions and scopes

#include <iostream>
#include <vector>

namespace N {
    int x = 5;
}

namespace N1 {
    int y = 10;
}

int main() {
    std::cout << N::x << std::endl; // >> 5, N::x - qualified-id

    using N::x;
    std::cout << x << std::endl; // >> 5, x - unqualified-id

    using namespace N1;
    std::cout << y << std::endl; // >> 10

    using vi = std::vector<int>;
    vi vect;
    vect.push_back(1);
    std::cout << vect.size() << std::endl; // >> 1

    int z = z;
    std::cout << z << std::endl; // UB
}