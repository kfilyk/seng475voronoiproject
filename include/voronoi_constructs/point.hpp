#include <boost/container/flat_set.hpp>

namespace voronoi_constructs {
    class Point {
        int x();
        int y();
    };
    bool LessOnBeachline(const Point leftOperand, const Point rightOperand) {
        return leftOperand.x() < rightOperand.x();
    }
    using PointsContainer = boost::container::flat_set<Point, LessOnBeachline>;
}