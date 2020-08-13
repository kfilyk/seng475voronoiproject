
namespace voronoi_constructs {
    template <class Point>
    struct BachelorPoint {
        using BachelorPointsPtrSet = std::set<BachelorPoint*, bachelor_point_comparators::ptr_bachelor_point_is_less<Point>>;
        Point point;
        std::set<Arc<Point>*> arcs;
        BachelorPoint(Point point, std::vector<Arc<Point>*> arcs) : point(point) {
            this->arcs = arcs;
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