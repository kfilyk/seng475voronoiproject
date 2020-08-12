namespace voronoi_constructs {
    template<class T>
    class Point {
        public:
            using CoordType = T;
            Point(CoordType x, CoordType y) : _x(x), _y(y) {}
            CoordType x() {
                return CoordType(_x);
            }
            CoordType y() {
                return CoordType(_y);
            }
        private:
            CoordType _x;
            CoordType _y;
    };
    namespace point_comparators {
        template<class T>
        class y_is_less {
            public:
                bool operator()(Point<T> left, Point<T> right) {
                    return left.y() < right.y();
                }
        };
        template<class T>
        class y_is_greater {
            public:
                bool operator()(Point<T> left, Point<T> right) {
                    return left.y() > right.y();
                }
        };
        template<class T>
        class x_is_less {
            public:
                bool operator()(Point<T> left, Point<T> right) {
                    return left.x() < right.x();
                }
        };
        template<class T>
        class ptr_x_is_less {
            public:
                bool operator()(Point<T> left, Point<T> right) {
                    return (left -> .x()) < (right -> .x());
                }
        };
    }
    template<class T>
    using PointsContainer = std::set<Point<T>, point_comparators::y_is_less<T>>;
}