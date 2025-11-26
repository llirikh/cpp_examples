#include "line.hpp"
#include "utils.hpp"

Line::Line(double angular_coefficient, double shift)
        : angular_coefficient(angular_coefficient)
        , shift(shift) {}

Line::Line(const Point& point, double angular_coefficient)
        : angular_coefficient(angular_coefficient)
        , shift(point.x - (point.y / angular_coefficient)) {}

Line::Line(const Point& first, const Point& second)
        : angular_coefficient((first.y - second.y) / (first.x - second.x))
        , shift(first.y - angular_coefficient * first.x) {}

bool operator==(const Line& lhs, const Line& rhs) {
    using utils::is_equal;
    return is_equal(lhs.angular_coefficient, rhs.angular_coefficient) &&
           is_equal(lhs.shift, rhs.shift);
}

bool operator!=(const Line& lhs, const Line& rhs) {
    return !(lhs == rhs);
}

Point intersect(const Line& first, const Line& second) {
    double x = (second.shift - first.shift) / 
               (first.angular_coefficient - second.angular_coefficient);
    double y = first.shift - first.angular_coefficient * x;
    
    return {x, y};
}