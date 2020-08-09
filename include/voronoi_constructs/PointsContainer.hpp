#include <boost/container/flat_set.hpp>

namespace voronoi_constructs {
    using PointsContainer = boost::container::flat_set<PointType, PointIsLess>;
}