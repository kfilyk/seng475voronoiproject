namespace voronoi_constructs {
    template<class T>
    class Point {
        public:
            using CoordType = T;
            Point() : _x(0), _y(0) {}
            Point(CoordType x, CoordType y) : _x(x), _y(y) {}
            CoordType x() {
                return CoordType(_x);
            }
            CoordType y() {
                return CoordType(_y);
            }
            CoordType squared_distance_from(Point origin) {
                Point::CoordType origin_x(origin.x());
                Point::CoordType origin_y(origin.y());
                return ((_x - origin_x)*(_x - origin_x)) + ((_y - origin_y)*(_y - origin_y));
            }
            bool x_is_less(Point other) {
                return x() < other.x();
            }
            bool operator==(Point other) {
                return (x() == other.x()) && (y() == other.y());
            }
        private:
            CoordType _x;
            CoordType _y;
    };
    namespace point_comparators {
        template<class T>
        class y_is_less {
            public:
                bool operator()(T left, T right) {
                    return left.y() < right.y();
                }
        };
        template<class T>
        class y_is_greater {
            public:
                bool operator()(T left, T right) {
                    return left.y() > right.y();
                }
        };
        template<class T>
        class x_is_less {
            public:
                bool operator()(T left, T right) {
                    return left.x() < right.x();
                }
        };
        template<class T>
        class ptr_x_is_less {
            public:
                bool operator()(T* left, T* right) {
                    return (left->x()) < (right ->x());
                }
        };
    }
}