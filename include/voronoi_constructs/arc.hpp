namespace voronoi_constructs {
    template <class Point>
    class Arc {
        public:
            BachelorPoint<Point>::BachelorPointsPtrSet bachelor_points;
            Arc(const Point focus, BachelorPointsPtrSet bachelor_points = BachelorPointsPtrSet()) : bachelor_points() {
                add_bachelor_points(bachelor_points);
            }
            Arc(const &Arc<Point> other) : bachelor_points(), _focus(other.get_focus()) {
                add_bachelor_points(bachelor_points);
            }
            Arc& operator=(const &Arc<Point> arc) : bachelor_points(), _focus(arc.get_focus()) {
                if (this != other) {
                    delete[] bachelor_points;
                    add_bachelor_points(bachelor_points);
                }
                return *this;
            }
            Point get_focus() {
                return Point(_focus);
            }
            void add_bachelor_points(BachelorPointsPtrSet bachelor_points) {
                for (auto bachelor_point_ptr : bachelor_points) {
                    bachelor_points.insert(bachelor_point_ptr);
                    // give each bachelor point knowledge of which arc owns it, so that they can be used as the source point 
                    // in completed edges formed in edge intersection events (since intersection events should only have knowledge of
                    // participating arcs, and are agnostic to bachelor points)
                    (bachelor_point_ptr->participating_beachline_arcs).push_back(this);
                }
            }
            bool operator<(const Arc<Point> other) {
                return focus_is_less(other);
            }
            bool operator==(const Arc<Point> other) {
                return !(*this < other) && !(other < *this);
            }
            Point::CoordType compute_y(Point::CoordType x, Point::CoordType directrix) {
                return (((x - _focus.x()) * (x - _focus.x()))/(2*(_focus.y() - directrix))) + ((_focus.y() + directrix)/2);
            }
            Point::CoordType tangent_slope(Point::CoordType x, Point::CoordType directrix) {
                return (x - _focus.x())/(_focus.y() - directrix);
            }
            bool focus_is_less(const Arc<Point> other) {
                return _focus.x() < other._focus.x();
            }
        private:
            Point _focus;
    };
    namespace arc_comparators {
        template <class Point>
        class focus_is_less {
            public:
                bool operator()(const Arc<Point> left, const Arc<Point> right) {
                    return point_comparators::x_is_less<Point>(left.focus(), right.focus());
                }
        };
        template <class Point>
        class ptr_focus_is_less {
            public:
                bool operator()(const Arc<Point>* left, const Arc<Point>* right) {
                    return point_comparators::x_is_less<Point>(left->focus(), right->focus());
                }
        };
    }
}