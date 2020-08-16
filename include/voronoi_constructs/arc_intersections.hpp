#include <set>
namespace voronoi_constructs {
    template<class Point>
    struct DisappearingArc {
        Arc<Point>* arc;
        std::size_t num_arc_intersections;
        DisappearingArc(Arc<Point>* arc, num_arc_intersections) : arc(arc), num_arc_intersections(num_arc_intersections) {}
    };
    // all the intersections that a particular arc will theoretically experience
    template<class Point>
    struct ArcIntersections {
        using ArcIntersectionsSet = std::set<ArcIntersections, arc_intersections_comparator::arc_focus_is_less>;
        using ArcIntersectionsPtrSet = std::set<ArcIntersections*, arc_intersections_comparator::ptr_arc_focus_is_less>;
        // precondition: intercepts_map has nonzero number of items
        ArcIntersections(Arc<Point>* arc, ArcsVerticalInterceptsMap intercepts_map, DisappearingArcsMap<Point>* disappearing_arcs_map) : arc(arc), disappearing_arc(nullptr), left_intersection(nullptr), right_intersection(nullptr) {
            if (intercepts_map.size() > 0) {
                Point focus = arc.get_focus();
                Point::CoordType x = focus.x();
                Point::CoordType sweepline_y = focus.y();
                ArcsVerticalInterceptsMap::iterator vertical_intercepts_iter = intercepts_map.begin();
                Arc<Point>* first_intercepting_arc = vertical_intercepts_iter -> second;
                if (first_intercepting_arc->y() < 0) {
                    first_intercepting_arc = new Arc(Point(x, Point::CoordType(0)));
                    disappearing_arc(nullptr, 0);
                } else {
                    DisappearingArcsMap<Point>* disappearing_arc_ptr = disappearing_arcs_map->find(first_intercepting_arc);
                    if (disappearing_arc_ptr == disappearing_arcs_map->end()) {
                        (*(disappearing_arcs_map))[first_intercepting_arc] = new DisappearingArc(first_intercepting_arc, 1);
                    } else {
                        ++(disappearing_arc_ptr->num_arc_intersections);
                    }
                }
                Point::CoordType t1 = first_intercepting_arc->tangent_slope(x, sweepline_y);
                Point::CoordType b1 = first_intercepting_arc->compute_y(x, sweepline_y);
                Point::CoordType t2 = nullptr;
                Point::CoordType b2 = nullptr;
                Point::CoordType intersection_point = nullptr;
                Point::CoordType intersect_x = nullptr;
                Point::CoordType intersect_y = nullptr;
                Arc* intercepting_arc = nullptr;

                // intermediary container for the purpose of sorting the intersection points according to x,
                // for assignment as left and right intercepts flanking the new arc
                std::map<Point, Arc<Point>*, point_comparators::ptr_x_is_less<Point>> intersections;
                while (vertical_intercepts_iter++ != intercepts_map.end()) {
                    intercepting_arc = vertical_intercepts_iter->second;
                    t2 = intercepting_arc->tangent_slope(x, sweepline_y);
                    b2 = intercepting_arc->compute_y(x, sweepline_y);
                    intersect_x = (b2-b1)/(t1-t2);
                    intersect_y = b1 + (intersect_x * (t1-t2));
                    intersections.insert(Point(intersect_x, intersect_y), intercepting_arc);
                }
                Point arc_focus = arc->get_focus();
                intersections.insert(arc_focus);
                ArcIntersectionsSet::iterator iter = intersections.find(arc_focus);
                if (iter != intersections.begin()) { // there's no intersection to the left
                    left_intersection = (iter - 1)->first;
                }
                if (iter != (intersections.end() - 1)) { // there's no intersection to the right
                    right_intersection = (iter + 1)->first;
                }
                for (auto bachelor_point : arc->bachelor_points) {
                    if (iter != intersections.begin()) {
                        bachelor_point.participating_beachline_arcs.insert((iter - 1)->second);
                    }
                    if (iter != (intersections.end() - 1)) {
                        bachelor_point.participating_beachline_arcs.insert((iter + 1)->second);
                    }
                }
            }
        }
        ArcIntersections(Arc<Point>* arc, Point* left_intersection, Point* right_intersection) : arc(arc), disappearing_arc(nullptr), left_intersection(left_intersection), right_intersection(right_intersection) {}
        Arc* arc;
        DisappearingArc disappearing_arc;
        Point* left_intersection;
        Point* right_intersection;
    };
    template <class Point>
    struct Intersection {
        Point point;
        ArcIntersections* arc_intersections;
        Intersection(Point point, ArcIntersections* arc_intersections) : point(point), arc_intersections(arc_intersections) {}
    };
    namespace arc_intersections_comparator {
        template<class Point>
        class arc_focus_is_less {
            public:
                bool operator()(const ArcIntersections<Point> left, const ArcIntersections<Point> right) {
                    return point_comparators::x_is_less<Point>(left.arc_focus(), right.arc_focus());
                }
        };
        template<class Point>
        class ptr_arc_focus_is_less {
            public:
                bool operator()(const ArcIntersections<Point>* left, const ArcIntersections<Point>* right) {
                    return point_comparators::x_is_less<Point>(left->arc_focus(), right->arc_focus());
                }
        };
    }
}