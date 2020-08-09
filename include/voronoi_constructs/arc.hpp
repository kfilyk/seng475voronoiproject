#include "voronoi_constructs/point.hpp"

namespace voronoi_constructs {
    class Arc {
        public:
            Arc(const Point focus, const Edge left_edge, const Edge right_edge, const Point::Coord sweepline_y) : focus(focus), left_edge(left_edge), right_edge(right_edge), directrix(sweepline_y - focus.x()) {}
            bool operator<(const Arc other) {
                return LessOnBeachline(*this, other);
            }
            bool operator==(const Arc other) {
                return !(*this < other) && !(other < *this);
            }
            Point ComputeIntersection(Arc other) {
                //TODO: figure out how to comput the intersection(s) between two parabola arcs
            }
        private:
            Point focus;
            Edge left_edge;
            Edge right_edge;
    }
}