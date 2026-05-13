#include <cassert>
#include <cmath>

#include "geometry_utils.h"
#include "simple_quadrilateral.h"


SimpleQuadrilateral::SimpleQuadrilateral(Point2D p1, Point2D p2, 
                                         Point2D p3, Point2D p4)
    : p1_(p1), p2_(p2), p3_(p3), p4_(p4) {
    if (p1_ == p2_ || p2_ == p3_ || p3_ == p4_ || p4_ == p1_) {
        throw std::invalid_argument(
            "Repeated consecutive vertices in quadrilateral.");
    }

    //is it a simple quadrilateral?
    if (segments_intersect(p1_, p2_, p3_, p4_) ||
        segments_intersect(p2_, p3_, p4_, p1_)) {
        throw std::invalid_argument(
            "Quadrilateral is not simple: edges intersect.");
    }

    double signed_area =
        p1_.x * p2_.y - p2_.x * p1_.y +
        p2_.x * p3_.y - p3_.x * p2_.y +
        p3_.x * p4_.y - p4_.x * p3_.y +
        p4_.x * p1_.y - p1_.x * p4_.y;
    
    if (std::abs(signed_area) < 1e-12) {
        throw std::invalid_argument("Degenerate quadrilateral: zero area.");
    }

    if (signed_area < 0) {
        throw std::invalid_argument(
            "Points are not counter-clockwise ordered.");
    }

    area_ = signed_area / 2;
}

double SimpleQuadrilateral::area() const {
    return area_;
}

std::vector<Point2D> SimpleQuadrilateral::points() const {
	return std::vector<Point2D>{p1_, p2_, p3_, p4_};
}