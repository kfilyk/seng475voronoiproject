
namespace voronoi_constructs {
    template <class Point>
    struct BachelorPoint {
        using BachelorPointsPtrSet = std::set<BachelorPoint*, bachelor_point_comparators::ptr_bachelor_point_is_less<Point>>;
        Point point;
        ArcsPtrSet participating_beachline_arcs;
        BachelorPoint(Point point, ArcsPtrSet arcs = ArcsPtrSet()) : point(point) {
            this->participating_beachline_arcs = arcs;
        }
        Point closest_intersection_to_boundaries() {
            y_limit_intersect_x = (y_limit_ray.source.x() - source.x())/(slope - y_limit_ray.slope);
            y_limit_intersect_y = source.y() + (intersect_x * (slope - y_limit_ray.slope));
            Point y_limit_intersection(y_limit_intersect_x, y_limit_intersect_y);

            x_limit_intersect_x = (x_limit_ray.source.x() - source.x())/(slope - x_limit_ray.slope);
            x_limit_intersect_y = source.y() + (intersect_x * (slope - x_limit_ray.slope));
            Point x_limit_intersection(x_limit_intersect_x, x_limit_intersect_y);

            x_min_intersect_x = (x_min_ray.source.x() - source.x())/(slope - x_min_ray.slope);
            x_min_intersect_y = source.y() + (intersect_x * (slope - x_min_ray.slope));
            Point x_min_intersection(x_min_intersect_x, x_min_intersect_y);

            // sort boundary intersections according to their distances to the ray's origin
            std::set<Point, less_euclidean_distance_to_point<source>> intersection_points {
                y_limit_intersection,
                x_limit_intersection,
                x_min_intersection
            };
            return *(intersection_points.begin());
        }
        Edge<Point> resolve_bachelor_point() {
            return Edge<Point>(point, closest_intersection_to_boundaries());
        }
        template <Point origin>
        static class less_euclidean_distance_to_point {
            public:
                bool operator()(Point* left, Point* right) {
                    return left.square_distance_from(origin) < right.square_distance_from(origin);
                }
        }
    };
    namespace bachelor_point_comparators {
        template<class Point>
        class ptr_bachelor_point_x_is_less {
            public:
                bool operator()(Point left, Point right) {
                    return left->x() < right->x();
                }
        };
    }
}