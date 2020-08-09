#include <boost/container/flat_set.hpp>

namespace voronoi_constructs {
    class Point {
        int x();
        int y();
    };
    bool LessOnBeachline(const BeachlineItem left, const BeachlineItem right) {
        return left.isLessThan(right);
    }
    using PointsContainer = boost::container::flat_set<Point, LessOnBeachline>;
}