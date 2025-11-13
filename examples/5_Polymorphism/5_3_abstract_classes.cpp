// 5.3. Abstract classes and pure virtual functions

#include <iostream>
#include <cmath>
#include <vector>

// Abstract Struct: it has at least one pure virtual function
struct Shape {                  
    virtual double area() const = 0;  // Pure Virtual function
    virtual ~Shape() = default;
};

double Shape::area() const {
    return 0.0;
}

struct Square: Shape {
    double a;
    Square(double a): a(a) {}

    double area() const override {
        return a * a;
    }
};

struct Circle: Shape {
    double r;
    Circle(double r): r(r) {}

    double area() const override {
        return M_PI * r * r;
    }
};

int main() {
    // Can't create instance of Shape
    // Shape shape;

    // Don't need to specify Shape
    std::vector<Shape*> shapes;
    shapes.push_back(new Square(1.5));
    shapes.push_back(new Circle(1.5));

    for (Shape* shape: shapes) {
        std::cout << shape->area() << ' ';
    }
    std::cout << '\n';

    Circle circle(1.5);
    std::cout << circle.Shape::area() << '\n';

}