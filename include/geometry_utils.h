#include "shape.h"

double cross2D(const Point2D& a, const Point2D& b, const Point2D& c);

bool point_lies_on_segment(const Point2D& seg1, 
                           const Point2D& seg2, 
                           const Point2D& p);

int orient(const Point2D& a, const Point2D& b, const Point2D& c);

bool segments_intersect(const Point2D& seg_11, const Point2D& seg_12,
                        const Point2D& seg_21, const Point2D& seg_22);