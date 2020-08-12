namespace voronoi_constructs {
    template <class T>
    class Arc {
        using Point = T;
        public:
            using BachelorPointsSet = std::set<Point*, point_comparators::ptr_x_is_less<Point::CoordType>>;
            BachelorPointsSet bachelor_points;
            Arc(const Point focus, BachelorPointsSet bachelor_points = BachelorPointsSet()) : bachelor_points() {
                for (auto ptr : bachelor_points) {
                    bachelor_points.insert(ptr);
                }
            }
            Arc(const &Arc<Point> other) : bachelor_points(), _focus(other.get_focus()) {
                for (auto ptr : other.bachelor_points) {
                    bachelor_points.insert(ptr);
                }
            }
            Arc& operator=(const &Arc<Point> arc) : bachelor_points(), _focus(arc.get_focus()) {
                if (this != other) {
                    delete[] bachelor_points;
                    for (auto ptr : other.bachelor_points) {
                        bachelor_points.insert(ptr);
                    }
                }
                return *this;
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
            Point get_focus() {
                return Point(_focus);
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
    }
}