// 1.4 Function's overloadings

#include <iostream>

int f(int x) { return x + 1; }
double f(double x) { return x + 2; }

int main() {
    std::cout << f(1) << ' ' << f(1.0) << std::endl; // >> 2 3
    std::cout << f(1.0f) << std::endl; // >> 3, float -> double (rather promotion than convertion)
}