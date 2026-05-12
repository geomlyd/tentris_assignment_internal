#include "persistent_shape_container.h"
#include "triangle.h"
#include "simple_quadrilateral.h"

int main() {
    PersistentShapeContainer<Triangle, TriangleSerializer> triangle_container;
    triangle_container.push_back(Triangle({0, 0}, {1, 0}, {0, 1}));
    triangle_container.push_back(Triangle({0, 0}, {2, 0}, {0, 2}));

    PersistentShapeContainer<SimpleQuadrilateral, SimpleQuadrilateralSerializer> quadrilateral_container;
    quadrilateral_container.push_back(SimpleQuadrilateral({0, 0}, {1, 0}, {1, 1}, {0, 1}));
    quadrilateral_container.push_back(SimpleQuadrilateral({0, 0}, {2, 0}, {2, 2}, {0, 2}));

    return 0;
}
