#include <doctest/doctest.h>
#include <stdexcept>

#include "simple_quadrilateral.h"

TEST_CASE("Vertex repetition in SimpleQuadrilateral raises exception") {
    Point2D p1{0.0, 0.0};
    Point2D p2{1.0, 0.0};
    Point2D p3{1.0, 1.0};
    Point2D p4{1.0, 1.0};

    CHECK_THROWS_AS(SimpleQuadrilateral(p1, p2, p3, p4), 
                    std::invalid_argument);
    CHECK_THROWS_AS(SimpleQuadrilateral(p1, p2, p3, p1), 
                    std::invalid_argument);                    
}

TEST_CASE("Self-intersecting SimpleQuadrilateral raises exception") {
    //assuming boundary-ordered interpretation, this self-intersects
    Point2D p1{0.0, 0.0};
    Point2D p2{2.0, 2.0};
    Point2D p3{0.0, 2.0};
    Point2D p4{2.0, 0.0};

    CHECK_THROWS_AS(SimpleQuadrilateral(p1, p2, p3, p4), 
                    std::invalid_argument);
}

TEST_CASE("Degenerate SimpleQuadrilateral raises exception") {
    Point2D p1{0.0, 0.0};
    Point2D p2{1.0, 0.0};
    Point2D p3{2.0, 0.0};
    Point2D p4{3.0, 0.0};

    CHECK_THROWS_AS(SimpleQuadrilateral(p1, p2, p3, p4), 
                    std::invalid_argument);
}

TEST_CASE(
    "Clockwise ordering of SimpleQuadrilateral vertices raises exception") {
    Point2D p1{0.0, 0.0};
    Point2D p2{0.0, 2.0};
    Point2D p3{2.0, 2.0};
    Point2D p4{2.0, 0.0};

    CHECK_THROWS_AS(SimpleQuadrilateral(p1, p2, p3, p4), 
                    std::invalid_argument);
}

TEST_CASE("SimpleQuadrilateral area is correct for rectangle") {
    Point2D p1{0.0, 0.0};
    Point2D p2{3.0, 0.0};
    Point2D p3{3.0, 2.0};
    Point2D p4{0.0, 2.0};

    SimpleQuadrilateral q(p1, p2, p3, p4);

    CHECK(q.area() == doctest::Approx(6.0));
}

TEST_CASE("SimpleQuadrilateral area is correct even if effectively triangle") {
    //a "semi-degenerate" quadrilateral should be acceptable
    Point2D p1{2.0, 2.0};
    Point2D p2{3.5, 2.0};
    Point2D p3{3.0, 3.0};
    Point2D p4{0.5, 2.0};

    SimpleQuadrilateral q(p1, p2, p3, p4);

    CHECK(q.area() == doctest::Approx(1.5));
}

TEST_CASE("SimpleQuadrilateral area is correct in a general case") {
    Point2D p1{0.0, 0.0};
    Point2D p2{1.0, 1.5};
    Point2D p3{0.5, 3.0};
    Point2D p4{0.0, 1.0};

    SimpleQuadrilateral q(p1, p2, p3, p4);
    //compute expected area by e.g. plotting on paper
    CHECK(q.area() == doctest::Approx(1.375));
}