#include <boost/container/flat_set.hpp>

namespace voronoi_constructs {
    class Point {
        using Coord = int;
        Point(Coord x, Coord y) : x(x), y(y) {}
        Coord x();
        Coord y();
    };
    bool y_is_less(const Point left, const Point right) {
        return left.y() < right.y();
    }
    using PointsContainer = boost::container::flat_set<Point, y_is_less>;
}