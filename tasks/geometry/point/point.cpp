#include "point.hpp"
#include "utils.hpp"

#include "cmath"
#include "numbers"

Point::Point(double x, double y): x(x), y(y) {}

Point& Point::operator+=(const Point& rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
}

Point& Point::operator-=(const Point& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

Point& Point::operator*=(double scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}

Point& Point::operator/=(double scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
}

void Point::rotate(double degrees) {
    double radians = degrees * (std::numbers::pi / 180.0);

    Point tmp = *this;
    x = tmp.x * std::cos(radians) - tmp.y * std::sin(radians);
    y = tmp.x * std::sin(radians) + tmp.y * std::cos(radians);
}

void Point::reflect(const Point& pivot) {
    x = 2 * pivot.x - x;
    y = 2 * pivot.y - y;
}

bool operator==(const Point& lhs, const Point& rhs) {
    using utils::is_equal;
    return is_equal(lhs.x, rhs.x) && is_equal(lhs.y, rhs.y);
}

bool operator!=(const Point& lhs, const Point& rhs) {
    return !(lhs == rhs);
}

Point operator+(const Point& lhs, const Point& rhs) {
    Point copy = lhs;
    copy += rhs;
    return copy;
}

Point operator-(const Point& lhs, const Point& rhs) {
    Point copy = lhs;
    copy -= rhs;
    return copy;
}

Point operator*(const Point& lhs, double rhs) {
    Point copy = lhs;
    copy *= rhs;
    return copy;
}

Point operator*(double lhs, const Point& rhs) {
    Point copy = rhs;
    copy *= lhs;
    return copy;
}

Point operator/(const Point& lhs, double rhs) {
    Point copy = lhs;
    copy /= rhs;
    return copy;
}

double operator*(const Point& lhs, const Point& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

double operator^(const Point& lhs, const Point& rhs) {
    return lhs.x * rhs.y - lhs.y * rhs.x;
}

double distance(const Point& first, const Point& second) {
    return std::sqrt(
        std::pow(first.x - second.x, 2) +
        std::pow(first.y - second.y, 2)
    );
}

std::size_t std::hash<Point>::operator()(const Point &point) const noexcept {
    std::size_t hash_x = std::hash<long long>{} (
        utils::quantize(point.x / utils::kEps)
    );
    std::size_t hash_y = std::hash<long long>{} (
        utils::quantize(point.x / utils::kEps)
    );
    return hash_x ^ (hash_y << 1);
};