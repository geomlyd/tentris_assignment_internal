#include <doctest/doctest.h>
#include <cassert>
#include <iostream>

#include "shape.h"
#include "geometry_utils.h"

TEST_CASE("orient identifies vectors as (counter-)clockwise or colinear") {

    SUBCASE("counterclockwise_1") {
        Point2D a{0.0, 0.0}, b{1.0, 0.0}, c{0.0, 1.0};
        CHECK(orient(a, b, c) > 0);
    }

    SUBCASE("counterclockwise_2") {
        Point2D a{2.0, 1.0}, b{3, 4}, c{1.5, 1.4};
        CHECK(orient(a, b, c) > 0);
    }

    SUBCASE("clockwise_1") {
        Point2D a{0.0, 0.0}, b{1.0, 0.0}, c{0.0, 1.0};
        CHECK(orient(a, c, b) < 0);
    }

    SUBCASE("clockwise_2") {
        Point2D a{-2.0, 1.0}, b{-3.0, 0.5}, c{-1.0, -5.0};
        CHECK(orient(a, c, b) < 0);
    }

    Point2D a{-1.0, 0.0}, b{0.3, 0.0}, c{2.0, 0.0};
    
    //verify all permutations/possible colinearity cases
    SUBCASE("collinear") {
        CHECK(orient(a, b, c) == 0);
        CHECK(orient(a, c, b) == 0);
        CHECK(orient(b, a, c) == 0);
        CHECK(orient(b, c, a) == 0);
        CHECK(orient(c, a, b) == 0);
        CHECK(orient(c, b, a) == 0);
    }    
}

TEST_CASE("point_lies_on_segment detects points correctly") {
    Point2D a{1.5, 1.2};
    Point2D b{2.0, 2.0};

    SUBCASE("point strictly inside segment") {
        Point2D p{1.6, 1.36};
        CHECK(point_lies_on_segment(a, b, p));
    }

    SUBCASE("point coincides with endpoint") {
        CHECK(point_lies_on_segment(a, b, a));
        CHECK(point_lies_on_segment(a, b, b));
    }

    SUBCASE("point outside segment but collinear") {
        Point2D p1{2.5, 2.8}, p2{0.0, -1.2};
        assert(std::abs(
            p1.y - (b.y - a.y)/(b.x - a.x)*(p1.x - a.x) - a.y) < 1e-12);
        CHECK_FALSE(point_lies_on_segment(a, b, p1));
        assert(std::abs(
            p2.y - (b.y - a.y)/(b.x - a.x)*(p2.x - a.x) - a.y) < 1e-12);        
        CHECK_FALSE(point_lies_on_segment(a, b, p2));
    }

    SUBCASE("point non-collinear") {
        Point2D p1{4.0, 1.5}, p2{1.75, 1.75};
        CHECK_FALSE(point_lies_on_segment(a, b, p1));
        CHECK_FALSE(point_lies_on_segment(a, b, p2));
    }
}

TEST_CASE("segments_intersect handles intersection cases") {
    SUBCASE("proper crossing intersection") {
        Point2D a1{0.0, 0.0}, a2{2.0, 2.0};

        Point2D b1{0.0, 2.0}, b2{2.0, 0.0};

        CHECK(segments_intersect(a1, a2, b1, b2));
    }

    SUBCASE("parallel non-intersecting") {
        Point2D a1{0.0, 0.0}, a2{1.0, 0.0};

        Point2D b1{0.0, 1.0}, b2{1.0, 1.0};

        CHECK_FALSE(segments_intersect(a2, a1, b1, b2));
    }

    SUBCASE("touching at endpoint") {
        Point2D a1{0.0, 0.0}, a2{1.0, 1.0};

        Point2D b1{1.0, 1.0}, b2{2.0, 0.0};

        Point2D c1{0.5, 0.5}, c2{0.0, 3.0};

        CHECK(segments_intersect(a2, a1, b2, b1));
        CHECK(segments_intersect(a2, a1, c1, c2));
    }

    SUBCASE("collinear overlapping") {
        Point2D a1{0.0, 0.0}, a2{3.0, 0.0};

        Point2D b1{1.0, 0.0}, b2{2.0, 0.0};

        CHECK(segments_intersect(a1, a2, b1, b2));
    }

    SUBCASE("collinear disjoint") {
        Point2D a1{0.0, 0.0}, a2{1.0, 0.0};

        Point2D b1{2.0, 0.0}, b2{3.0, 0.0};

        CHECK_FALSE(segments_intersect(a1, a2, b1, b2));
    }
}