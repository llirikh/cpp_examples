#pragma once
#include "point.hpp"
#include "line.hpp"

class Shape {
  public:
    virtual ~Shape() = default;

    virtual double perimeter() const = 0;
    virtual double area() const = 0;

    virtual bool operator==(const Shape& rhs) const  = 0;
    virtual bool operator!=(const Shape& rhs) const  = 0;
    // virtual bool isCongruentTo(const Shape& other) const = 0;
    // virtual bool isSimilarTo(const Shape& other) const = 0;
    // virtual bool containsPoint(const Point& point) const = 0;

    virtual void rotate(const Point& pivot, double angle) = 0;
    virtual void reflect(const Point& center) = 0;
    // virtual void reflect(const Line& axis) = 0;
    // virtual void scale(const Point& center, double coefficient) = 0;
};