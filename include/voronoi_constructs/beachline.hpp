
namespace voronoi_constructs {
    template<class Point>
    class Beachline {
        public:
            Beachline() : points() {}
            add(Point point) {
                points.insert(point);
            }
        private:
            bool XIsLess(Point lhs, Point rhs) {
                return lhs.x < rhs.x;
            }
            boost::container::flat_set<Point, XIsLess> points;
    };
}
