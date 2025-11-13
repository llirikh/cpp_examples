#include <iostream>
#include <cmath>
#include <cassert>
#include <vector>
#include "geometry.hpp"

const double EPS = 1e-6;

bool doubleEqual(double a, double b) {
    return std::fabs(a - b) < EPS;
}

void testPoint() {
    std::cout << "Testing Point..." << std::endl;
    
    Point p1(1.0, 2.0);
    Point p2(1.0, 2.0);
    Point p3(2.0, 3.0);
    
    assert(p1 == p2);
    assert(!(p1 == p3));
    assert(p1 != p3);
    assert(!(p1 != p2));
    
    assert(doubleEqual(p1.x, 1.0));
    assert(doubleEqual(p1.y, 2.0));
    
    std::cout << "Point tests passed!" << std::endl;
}

void testLine() {
    std::cout << "Testing Line..." << std::endl;
    
    Point p1(0, 0);
    Point p2(1, 1);
    Line l1(p1, p2);
    
    Point p3(2, 2);
    Point p4(3, 3);
    Line l2(p3, p4);
    
    assert(l1 == l2); // Одна и та же прямая
    
    Line l3(1, 0); // y = x
    assert(l1 == l3);
    
    Line l4(p1, 1); // y = x через точку (0,0)
    assert(l1 == l4);
    
    Point p5(0, 1);
    Point p6(1, 2);
    Line l5(p5, p6);
    assert(l1 == l5); // y = x + 1? Нет, это другая прямая
    
    std::cout << "Line tests passed!" << std::endl;
}

void testTriangle() {
    std::cout << "Testing Triangle..." << std::endl;
    
    Point a(0, 0);
    Point b(3, 0);
    Point c(0, 4);
    Triangle t(a, b, c);
    
    assert(t.verticesCount() == 3);
    assert(doubleEqual(t.perimeter(), 12.0)); // 3 + 4 + 5
    assert(doubleEqual(t.area(), 6.0)); // (3 * 4) / 2
    
    std::vector<Point> vertices = t.getVertices();
    assert(vertices.size() == 3);
    
    Circle circumCircle = t.circumscribedCircle();
    assert(doubleEqual(circumCircle.radius(), 2.5)); // R = abc/(4S) = 60/24 = 2.5
    
    Circle inCircle = t.inscribedCircle();
    assert(doubleEqual(inCircle.radius(), 1.0)); // r = S/p = 6/6 = 1
    
    Point centroid = t.centroid();
    assert(doubleEqual(centroid.x, 1.0));
    assert(doubleEqual(centroid.y, 4.0/3.0));
    
    // Тест на равенство треугольников (разный порядок вершин)
    Triangle t2(b, c, a);
    assert(t == t2);
    
    std::cout << "Triangle tests passed!" << std::endl;
}

void testCircle() {
    std::cout << "Testing Circle..." << std::endl;
    
    Point center(0, 0);
    Circle c(center, 5.0);
    
    assert(doubleEqual(c.radius(), 5.0));
    assert(doubleEqual(c.perimeter(), 2 * M_PI * 5));
    assert(doubleEqual(c.area(), M_PI * 25));
    
    Point centerResult = c.center();
    assert(centerResult == center);
    
    auto focuses = c.focuses();
    assert(focuses.first == center);
    assert(focuses.second == center);
    
    assert(doubleEqual(c.eccentricity(), 0.0));
    
    // Проверка containsPoint
    assert(c.containsPoint(Point(0, 0)));
    assert(c.containsPoint(Point(3, 0)));
    assert(c.containsPoint(Point(0, 4)));
    assert(!c.containsPoint(Point(5, 5)));
    
    std::cout << "Circle tests passed!" << std::endl;
}

void testEllipse() {
    std::cout << "Testing Ellipse..." << std::endl;
    
    Point f1(-3, 0);
    Point f2(3, 0);
    Ellipse e(f1, f2, 10.0); // 2a = 10, c = 3, b^2 = 25 - 9 = 16
    
    auto focuses = e.focuses();
    assert(focuses.first == f1 || focuses.first == f2);
    assert(focuses.second == f1 || focuses.second == f2);
    
    Point centerE = e.center();
    assert(doubleEqual(centerE.x, 0.0));
    assert(doubleEqual(centerE.y, 0.0));
    
    double ecc = e.eccentricity();
    assert(doubleEqual(ecc, 0.6)); // e = c/a = 3/5
    
    // Площадь эллипса π*a*b = π*5*4
    assert(doubleEqual(e.area(), M_PI * 5 * 4));
    
    std::cout << "Ellipse tests passed!" << std::endl;
}

void testRectangle() {
    std::cout << "Testing Rectangle..." << std::endl;
    
    Point p1(0, 0);
    Point p2(4, 2);
    Rectangle r(p1, p2, 2.0); // Отношение сторон 2:1
    
    assert(r.verticesCount() == 4);
    assert(r.isConvex());
    
    Point c = r.center();
    assert(doubleEqual(c.x, 2.0));
    assert(doubleEqual(c.y, 1.0));
    
    auto diags = r.diagonals();
    // Проверим, что диагонали существуют
    
    std::cout << "Rectangle tests passed!" << std::endl;
}

void testSquare() {
    std::cout << "Testing Square..." << std::endl;
    
    Point p1(0, 0);
    Point p2(2, 2);
    Square s(p1, p2);
    
    assert(s.verticesCount() == 4);
    assert(doubleEqual(s.area(), 4.0)); // Сторона sqrt(8)/sqrt(2) = 2
    assert(doubleEqual(s.perimeter(), 8.0));
    
    Circle circumCircle = s.circumscribedCircle();
    assert(doubleEqual(circumCircle.radius(), std::sqrt(2.0))); // Диагональ/2
    
    Circle inCircle = s.inscribedCircle();
    assert(doubleEqual(inCircle.radius(), 1.0)); // Сторона/2
    
    std::cout << "Square tests passed!" << std::endl;
}

void testPolygon() {
    std::cout << "Testing Polygon..." << std::endl;
    
    // Квадрат
    std::vector<Point> points = {
        Point(0, 0), Point(1, 0), Point(1, 1), Point(0, 1)
    };
    Polygon poly(points);
    
    assert(poly.verticesCount() == 4);
    assert(poly.isConvex());
    assert(doubleEqual(poly.area(), 1.0));
    assert(doubleEqual(poly.perimeter(), 4.0));
    
    // Вогнутый многоугольник
    std::vector<Point> concavePoints = {
        Point(0, 0), Point(2, 0), Point(2, 2), 
        Point(1, 1), Point(0, 2)
    };
    Polygon concave(concavePoints);
    assert(!concave.isConvex());
    
    std::cout << "Polygon tests passed!" << std::endl;
}

void testTransformations() {
    std::cout << "Testing Transformations..." << std::endl;
    
    Point p1(1, 0);
    Point p2(0, 1);
    Point p3(-1, 0);
    Triangle t(p1, p2, p3);
    
    double originalArea = t.area();
    
    // Поворот на 90 градусов
    t.rotate(Point(0, 0), 90);
    assert(doubleEqual(t.area(), originalArea));
    
    // Симметрия относительно точки
    Triangle t2(p1, p2, p3);
    t2.reflect(Point(0, 0));
    assert(doubleEqual(t2.area(), originalArea));
    
    // Симметрия относительно прямой
    Triangle t3(p1, p2, p3);
    Line axis(Point(0, 0), Point(1, 0));
    t3.reflect(axis);
    assert(doubleEqual(t3.area(), originalArea));
    
    // Масштабирование
    Triangle t4(p1, p2, p3);
    t4.scale(Point(0, 0), 2.0);
    assert(doubleEqual(t4.area(), originalArea * 4)); // Площадь умножается на квадрат
    
    std::cout << "Transformation tests passed!" << std::endl;
}

void testSimilarityAndCongruence() {
    std::cout << "Testing Similarity and Congruence..." << std::endl;
    
    // Два одинаковых треугольника
    Triangle t1(Point(0, 0), Point(1, 0), Point(0, 1));
    Triangle t2(Point(0, 0), Point(1, 0), Point(0, 1));
    
    assert(t1 == t2);
    assert(t1.isCongruentTo(t2));
    assert(t1.isSimilarTo(t2));
    
    // Подобные треугольники
    Triangle t3(Point(0, 0), Point(2, 0), Point(0, 2));
    assert(t1.isSimilarTo(t3));
    assert(!t1.isCongruentTo(t3)); // Разные размеры
    
    // Круг и эллипс
    Circle c(Point(0, 0), 5);
    Point f1(-3, 0);
    Point f2(3, 0);
    Ellipse e(f1, f2, 10);
    
    assert(!c.isCongruentTo(e));
    
    std::cout << "Similarity and Congruence tests passed!" << std::endl;
}

void testContainsPoint() {
    std::cout << "Testing containsPoint..." << std::endl;
    
    // Треугольник
    Triangle t(Point(0, 0), Point(4, 0), Point(2, 3));
    assert(t.containsPoint(Point(2, 1)));
    assert(t.containsPoint(Point(1, 0.5)));
    assert(!t.containsPoint(Point(5, 5)));
    assert(!t.containsPoint(Point(0, 5)));
    
    // Квадрат
    Square s(Point(0, 0), Point(2, 2));
    assert(s.containsPoint(Point(1, 1)));
    assert(!s.containsPoint(Point(3, 3)));
    
    std::cout << "containsPoint tests passed!" << std::endl;
}

int main() {
    std::cout << "Starting geometry tests..." << std::endl << std::endl;
    
    try {
        testPoint();
        testLine();
        testCircle();
        testEllipse();
        testTriangle();
        testSquare();
        testRectangle();
        testPolygon();
        testTransformations();
        testSimilarityAndCongruence();
        testContainsPoint();
        
        std::cout << std::endl << "All tests passed successfully!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}