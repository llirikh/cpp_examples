#include "polygon.hpp"

#include <cmath>
#include <unordered_set>

Polygon::Polygon(const std::vector<Point>& points) {
    vertex_.insert(vertex_.end(), points.begin(), points.end());
}

Polygon::Polygon(std::initializer_list<Point> list) {
    vertex_.insert(vertex_.end(), list.begin(), list.end());
}

double Polygon::perimeter() const {
    double perimeter = 0;
    for (size_t i = 0; i!= vertex_.size(); ++i) {
        size_t j = (i + 1) % vertex_.size();
        perimeter += distance(vertex_[i], vertex_[j]);
    }
    return perimeter;
}

double Polygon::area() const {
    double area = 0.0;
    for (size_t i = 0; i != vertex_.size(); ++i) {
        size_t j = (i + 1) % vertex_.size();
        area += vertex_[i] ^ vertex_[j];
    }
    return std::fabs(area / 2.0);
}

bool Polygon::operator==(const Shape& rhs) const {
    auto ptr_polygon = dynamic_cast<const Polygon*>(&rhs);
    if (ptr_polygon == nullptr) {
        return false;
    }

    if (vertex_.size() != ptr_polygon->vertex_.size()) {
        return false;
    }

    std::unordered_set<Point> set_lhs(vertex_.begin(), vertex_.end());
    std::unordered_set<Point> set_rhs(
        ptr_polygon->vertex_.begin(), ptr_polygon->vertex_.end()
    );

    return set_lhs == set_rhs;
}

bool Polygon::operator!=(const Shape& rhs) const {
    return !(*this == rhs);
}

// bool Polygon::isCongruentTo(const Shape& other) const { }

// bool Polygon::isSimilarTo(const Shape& other) const { }

// bool Polygon::containsPoint(const Point& point) const { }

void Polygon::rotate(const Point& pivot, double degrees) {
    for (auto& point: vertex_) {
        point -= pivot;
        point.rotate(degrees);
        point += pivot;
    }
}

void Polygon::reflect(const Point& pivot) {
    for (auto& point: vertex_) {
        point.reflect(pivot);
    }
}