#include <boost/container/flat_set.hpp>

namespace voronoi_constructs {
    class Point {
        using Coord = int;
        Coord x();
        Coord y();
    };
    bool x_is_less(const BeachlineItem left, const BeachlineItem right) {
        return left.isLessThan(right);
    }
    using PointsContainer = boost::container::flat_set<Point, x_is_less>;
}