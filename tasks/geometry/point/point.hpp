#pragma once

#include <functional>

struct Point {
    Point() = default;
    Point(double x, double y);
    Point(const Point& other) = default;

    Point& operator+=(const Point& other);
    Point& operator-=(const Point& other);
    Point& operator*=(double scalar);
    Point& operator/=(double scalar);

    void rotate(double degrees);
    void reflect(const Point& pivot = {0, 0});
    //void reflect(const Line& pivot);

    double x;
    double y;
};

bool operator==(const Point& lhs, const Point& rhs);
bool operator!=(const Point& lhs, const Point& rhs);

Point operator+(const Point& lhs, const Point& rhs);
Point operator-(const Point& lhs, const Point& rhs);

// Scalar multiplication
Point operator*(const Point& lhs, double rhs);
Point operator*(double lhs, const Point& rhs);

Point operator/(const Point& lhs, double rhs);

// Scalar/Dot product
double operator*(const Point& lhs, const Point& rhs);

// Cross product (double because of 2D)
double operator^(const Point& lhs, const Point& rhs);

double distance(const Point& first, const Point& second);

template<>
struct std::hash<Point> {
    std::size_t operator()(const Point& point) const noexcept;
};