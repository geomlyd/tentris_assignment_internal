#pragma once

#include "shape.h"

class Triangle: public Shape {
    public:
        Triangle(Point2D p1, Point2D p2, Point2D p3);

        double area() const override;
        std::vector<Point2D> points() const override;

    private:
        Point2D p1_, p2_, p3_;
        double area_;
};