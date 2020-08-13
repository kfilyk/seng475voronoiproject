namespace voronoi_constructs {
    template<class Point>
    class Edge {
        public:
            Point _src_point;
            Point _dest_point;
            Edge() : _src_point(0), _dest_point(0) {}
            Edge(Point src, Point dest) : _src_point(src), _dest_point(dest) {}
            Point source() {
                return Point(_src_point);
            }
            Point destination() {
                return Point(_dest_point);
            }
            Point slope() {
                return (_dest_point.x() - _src_point.x()) / (_dest_point.y() - _src_point.y());
            }
            Point middle_point() {
                return Point(
                    (_dest_point.x() + _src_point.x())/2,
                    (_dest_point.y() + _src_point.y())/2
                );
            }
            Point::CoordType squared_distance_from_origin() {
                return (_src_point * _src_point) * (_dest_point * _dest_point);
            }
    };
    namespace edge_comparator {
        template <class Point>
        class has_less_distance_from_origin {
            bool operator(const Edge<Point> left, const Edge<Point> right) {
                return left.squared_distance_from_origin() < right.squared_distance_from_origin();
            }
        };
    }
}
