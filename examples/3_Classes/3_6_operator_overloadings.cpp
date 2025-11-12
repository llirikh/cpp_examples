// 3.6. Operator overloadings.
#include <algorithm>
#include <iostream>
#include <compare>
#include <vector>

struct Complex {
    double re = 0;
    double im = 0;

    Complex(double re): re(re) {}
    Complex(double re, double im): re(re), im(im) {}

    Complex& operator=(const Complex& other) & {  // && for only rvalue
        re = other.re;
        im = other.im;
        return *this;
    }

    Complex& operator+=(const Complex& other) {
        re += other.re;
        im += other.im;
        return *this;
    }

    // v1.0 - CE: for double + Complex. Because operator+() is member of Complex
    // Complex operator+(const Complex& other) const { 
    //     return Complex(re + other.re, im + other.im);
    // }

    // Three-way comparison (since c++20)
    std::weak_ordering operator<=>(const Complex& other) const = default;  // Will search for operator<() and operator==()
    std::weak_ordering operator<=>(double other) const {                   // OK with (double)<=>(Complex) and (Complex)<=>(double) both
        return std::weak_ordering::equivalent;                             // Need to define behaviour
    }
};

// v2.0 - Bad: It should written with operator+=()
// Complex operator+(const Complex& lhs, const Complex& rhs) {
//     return Complex(lhs.re + rhs.re, lhs.im + rhs.im);
// }

// v3.0 - Extra copy while return. No RVO.
// Complex operator+(const Complex& lhs, const Complex& rhs) {
//     Complex result = lhs;
//     return result += rhs;
// }

// v4.0 - Extra copy while return. No RVO.
// Complex operator+(Complex lhs, const Complex& rhs) {
//     return lhs += rhs;
// }

// v5.0 - Return Value Optimizarion. No extra copy.
Complex operator+(const Complex& lhs, const Complex& rhs) {
    Complex result = lhs;
    result += rhs;
    return result;
}

bool operator<(const Complex& lhs, const Complex& rhs) {
    return lhs.re < rhs.re || (lhs.re == rhs.re && lhs.im < rhs.im);
}

bool operator>(const Complex& lhs, const Complex& rhs) {
    return rhs < lhs;                                               // not !(lhs <= rhs)
}


struct UserId {
    int value = 0;

    UserId& operator++() {    // Prefix increment: ++user_id
        ++value; 
        return *this;
    }

    UserId operator++(int) {  // Postfix increment: user_id++
        UserId copy = *this;
        ++value;
        return copy;
    }
};

struct Greater {
    bool operator()(int x, int y) const {
        return x > y;
    }
};


int main() {
    Complex c(5);
    c + 3.14;      // c.operator+(3.14)
    3.14 + c;      // CE if operator+ is member of Complex (v1.0). There is no (double).operator+(Complex c)

    Complex a(0);
    Complex b(0);
    // a + b = c;     // It's not good. Need to customize operator=() only for lvalue as first arguement

    std::vector<int> v(10);
    std::sort(v.begin(), v.end(), Greater());

}