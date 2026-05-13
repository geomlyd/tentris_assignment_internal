#include "persistent_shape_container.h"
#include "triangle.h"
#include "triangle_serializer.h"


int main() {
    PersistentShapeContainer<Triangle, TriangleSerializer> triangle_container;
    triangle_container.push_back(Triangle({0, 0}, {1, 0}, {0, 1}));
    triangle_container.push_back(Triangle({0, 0}, {2, 0}, {0, 2}));

    return 0;
}
