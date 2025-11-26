#pragma once
#include "point.hpp"
#include "shape.hpp"

#include <vector>
#include <iostream>

class Polygon: public Shape {
  public:
    Polygon() = delete;
    Polygon(const std::vector<Point>& points);
    Polygon(std::initializer_list<Point> list);

    double perimeter() const override;
    double area() const override;

    bool operator==(const Shape& rhs) const override;
    bool operator!=(const Shape& rhs) const override;
    // bool isCongruentTo(const Shape& other) const override;
    // bool isSimilarTo(const Shape& other) const override;
    // bool containsPoint(const Point& point) const override;

    void rotate(const Point& pivot, double angle) override;
    void reflect(const Point& center) override;

    ~Polygon() override = default;

  private:
    std::vector<Point> vertex_;
};