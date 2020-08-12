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
    };
}
