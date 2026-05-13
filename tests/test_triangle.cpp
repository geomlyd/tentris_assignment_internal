#include <doctest/doctest.h>

#include <stdexcept>
#include <vector>

#include "triangle.h"

TEST_CASE("Degenerate triangle raises exception") {
    Point2D p1{0.0, 0.0};
    Point2D p2{1.0, 1.0};
    Point2D p3{2.0, 2.0};

    CHECK_THROWS_AS(
        Triangle(p1, p2, p3),
        std::invalid_argument
    );
}

TEST_CASE("Triangle sides in clockwise order raises exception") {
    Point2D p1{0.0, 0.0};
    Point2D p2{0.0, 1.0};
    Point2D p3{1.0, 0.0};

    CHECK_THROWS_AS(
        Triangle(p1, p2, p3),
        std::invalid_argument
    );
}

TEST_CASE("Triangle area for obtuse triangle") {
    Point2D p1{-3.0, -1.0};
    Point2D p2{-6.0, -2.0};
    Point2D p3{-1.0, -2.0};
    

    Triangle t(p1, p2, p3);

    CHECK(t.area() == doctest::Approx(2.5));
}

TEST_CASE("Triangle area for acute triangle") {
    Point2D p1{1.0, 3.0};
    Point2D p3{4.0, 4.0};
    Point2D p2{4.0, 2.5};
    
    Triangle t(p1, p2, p3);

    CHECK(t.area() == doctest::Approx(2.25));
}

TEST_CASE("Triangle points are recoverable") {
    Point2D p1{2.0, 3.0};
    Point2D p2{5.0, 7.0};
    Point2D p3{1.0, 9.0};

    Triangle t(p1, p2, p3);

    auto pts = t.points();

    REQUIRE(pts.size() == 3);

    CHECK(pts[0].x == doctest::Approx(2.0));
    CHECK(pts[0].y == doctest::Approx(3.0));

    CHECK(pts[1].x == doctest::Approx(5.0));
    CHECK(pts[1].y == doctest::Approx(7.0));

    CHECK(pts[2].x == doctest::Approx(1.0));
    CHECK(pts[2].y == doctest::Approx(9.0));
}