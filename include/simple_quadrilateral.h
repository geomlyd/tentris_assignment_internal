#pragma once

#include "shape.h"

class SimpleQuadrilateral: public Shape {
    public:
        SimpleQuadrilateral(Point2D p1, Point2D p2, Point2D p3, Point2D p4);

        double area() const override;
        std::vector<Point2D> points() const override;

    private:
        Point2D p1_, p2_, p3_, p4_;
        double area_;
};