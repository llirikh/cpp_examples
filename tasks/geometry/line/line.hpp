#pragma once
#include "point.hpp"

struct Line {
    Line() = default;
    Line(double angular_coefficient, double shift);
    Line(const Point& point, double angular_coefficient);
    Line(const Point& first, const Point& second);
    Line(const Line& other) = default;
    
    ~Line() = default;
    
    double angular_coefficient;
    double shift;
};

bool operator==(const Line& lhs, const Line& rhs);
bool operator!=(const Line& lhs, const Line& rhs);

Point intersect(const Line& first, const Line& second);