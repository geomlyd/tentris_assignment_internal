#include "shape.h"

double cross2D(const Point2D& a, const Point2D& b, const Point2D& c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool point_lies_on_segment(const Point2D& seg1, 
                           const Point2D& seg2, 
                           const Point2D& p) {
    return std::min(seg1.x, seg2.x) <= p.x && 
           p.x <= std::max(seg1.x, seg2.x) &&
           std::min(seg1.y, seg2.y) <= p.y && 
           p.y <= std::max(seg1.y, seg2.y) &&
           std::abs(cross2D(seg1, seg2, p)) < 1e-12;
}

int orient(const Point2D& a, const Point2D& b, const Point2D& c) {
    double v = cross2D(a, b, c);
    if(std::abs(v) < 1e-12) {
        return 0;
    }
    return (v > 0) ? 1 : -1;
}

bool segments_intersect(const Point2D& seg_11, const Point2D& seg_12,
                        const Point2D& seg_21, const Point2D& seg_22) {
    int o1 = orient(seg_11, seg_12, seg_21);
    int o2 = orient(seg_11, seg_12, seg_22);
    int o3 = orient(seg_21, seg_22, seg_11);
    int o4 = orient(seg_21, seg_22, seg_12);

    //segments intersect without endpoint involvement
    if (o1 != o2 && o3 != o4) {
        return true;
    }

    //segments intersect with endpoint involvement
    if (o1 == 0 && point_lies_on_segment(seg_11, seg_12, seg_21)) {
        return true;
    }
    if (o2 == 0 && point_lies_on_segment(seg_11, seg_12, seg_22)) {
        return true;
    }
    if (o3 == 0 && point_lies_on_segment(seg_21, seg_22, seg_11)) {
        return true;
    }
    if (o4 == 0 && point_lies_on_segment(seg_21, seg_22, seg_12)) {
        return true;
    }

    return false;
}