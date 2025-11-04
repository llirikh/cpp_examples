// 3.5.3. Explicit methods, contextual conversion

#include <iostream>

struct Latitude {
    double value;

    explicit Latitude(double value): value(value) {}
    explicit operator double() const {
        return value;
    }
};

struct Longitude {
    double value;

    explicit Longitude(double value): value(value) {}
    explicit operator double() const {
        return value;
    }
};

Latitude operator""_lat(long double value) {   // Literal operator
    return Latitude(value);
}

Longitude operator""_lon(long double value) {  // Literal operator
    return Longitude(value);
}

void f(Latitude lat, Longitude lon) {
    std::cout << static_cast<double>(lat);  // No implicit conversion  Latitude -> double
    std::cout << ' ';
    std::cout << static_cast<double>(lon);  // No implicit conversion  Longitude -> double
    std::cout << std::endl;
}

int main() {
    f(Latitude(24.56), Longitude(56.23));  // No implicit conversion  double -> Latitude/Longitude
    f(24.56_lat, 56.23_lon);
}