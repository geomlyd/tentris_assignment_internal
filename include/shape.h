#pragma once

#include <vector>
#include <fstream>

struct Point2D {
    double x;
    double y;

    bool operator==(const Point2D& other) const {
        return std::abs(x - other.x) < 1e-12 && std::abs(y - other.y) < 1e-12;}
};

class Shape {
    public:
        virtual ~Shape() = default;
        
        virtual double area() const = 0;
        
        virtual std::vector<Point2D> points() const = 0;
};