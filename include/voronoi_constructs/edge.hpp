namespace voronoi_constructs {
    template <class Point>
    class Edge {
        public:
            Point src_point;
            Point dest_point;
            Edge(std::vector<int> unit_vector): unit_vector(unit_vector), src_point(0, 0), dest_point(0, 0) {}
            Edge(std::vector<int> unit_vector, Point src, Point dest) : unit_vector(unit_vector), src_point(src), dest_point(dest) {}
            Point intersection_point(Edge other) {
                return Point(); // TODO: actually do something in this method
            }
            void grow(Point diff) {
                dest_point = dest_point(dest_point + diff);
            }
            Point get_src() {
                return src_point;
            }
            Point get_dest() {
                return dest_point;
            }
    };
}
