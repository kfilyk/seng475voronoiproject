#include <set>
namespace voronoi_constructs {
    // all the intersections that a particular arc will theoretically experience
    template<class Point>
    struct ArcIntersections {
        using ArcIntersectionsSet = std::set<ArcIntersections, arc_intersections_comparator::arc_focus_is_less>;
        // precondition: intercepts_map has nonzero number of items
        ArcIntersections(Arc<Point> arc, ArcsVerticalInterceptsMap intercepts_map) : arc(arc) {
            assert(intercepts_map.size() > 0);
            Point focus = arc.get_focus();
            Point::CoordType x = focus.x();
            Point::CoordType sweepline_y = focus.y().
            ArcsVerticalInterceptsMap::iterator vertical_intercepts_iter = intercepts_map.begin();
            Arc<Point> first_intercepting_arc = (vertical_intercepts_iter++) -> second;
            if (first_intercepting_arc.y() < 0) {
                first_intercepting_arc = Arc(Point(x, Point::CoordType(0)));
            }
            Point::CoordType t1 = first_intercepting_arc.tangent_slope(x, sweepline_y);
            Point::CoordType b1 = first_intercepting_arc.compute_y(x, sweepline_y);
            Point::CoordType t2 = nullptr;
            Point::CoordType b2 = nullptr;
            Point::CoordType* intersection_point = nullptr;
            Point::CoordType intersect_x = nullptr;
            Point::CoordType intersect_y = nullptr;
            Arc intercepting_arc = nullptr;
            std::set<Point, point_comparators::ptr_x_is_less> intersections;
            while (vertical_intercepts_iter++ != intercepts_map.end()) {
                intercepting_arc = *vertical_intercepts_iter;
                t2 = intercepting_arc.tangent_slope(x, sweepline_y);
                b2 = intercepting_arc.compute_y(x, sweepline_y);
                intersect_x = (b2-b1)/(t1-t2);
                intersect_y = b1 + (intercect_x * (t1-t2));
                intersection_point = new Point(intersect_x, intersect_y);
                intersections.insert(intersection_point);
            }
            arc_focus = new Point(arc.get_focus());
            intersections.insert(arc_focus);
            ArcIntersectionsSet::iterator iter = intersections.find(arc_focus);
            left_intersection = *(iter - 1);
            right_intersection = *(iter + 1);
        }
        Point* arc_focus;
        Point left_intersection;
        Point right_intersection;
    };
    namespace arc_intersections_comparator {
        template<class Point>
        class arc_focus_is_less {
            public:
                bool operator()(const ArcIntersections<Point> left, const ArcIntersections<Point> right) {
                    return point_comparators::x_is_less<Point>(left.arc_focus(), right.arc_focus());
                }
        };
    }
}