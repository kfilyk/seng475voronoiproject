namespace voronoi_constructs {
    template <class Point>
    class Edge {
        public:
            Point _src_point;
            Point _dest_point;
            Edge(Point src, Point dest) : _src_point(src), _dest_point(dest) {}
            Point intersection_point(Edge other) {
                return Point(); // TODO: actually do something in this method
            }
            void grow(Point diff) {
                dest_point = dest_point(dest_point + diff);
            }
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
