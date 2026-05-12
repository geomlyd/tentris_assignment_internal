#include <cassert>
#include <cmath>

#include "triangle.h"
#include "geometry_utils.h"

Triangle::Triangle(Point2D p1, Point2D p2, Point2D p3)
    : p1_(p1), p2_(p2), p3_(p3) {
    int o = orient(p1_, p2_, p3_);

    if (o == 0) {
        throw std::invalid_argument("Degenerate triangle: zero area.");
    }

    if (o < 0) {
        throw std::invalid_argument(
            "Points are not counter-clockwise ordered.");
    }

    area_ = cross2D(p1_, p2_, p3_) * 0.5;
}

double Triangle::area() const {
	return area_;
}

std::vector<Point2D> Triangle::points() const {
	return std::vector<Point2D>{p1_, p2_, p3_};
}