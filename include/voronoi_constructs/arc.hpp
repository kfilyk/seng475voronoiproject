#include "voronoi_constructs/point.hpp"

namespace voronoi_constructs {
    class Arc {
        public:
            Arc(const Point focus)
                : focus(focus) {}
            bool operator<(const Arc other) {
                return LessOnBeachline(*this, other);
            }
            bool operator==(const Arc other) {
                return !(*this < other) && !(other < *this);
            }
            Point::Coord compute_y(Point::Coord x, Point::Coord directrix) {
                return (((x - focus.x()) * (x - focus.x()))/(2*(focus.y() - directrix))) + ((focus.y() + directrix)/2);
            }
            bool focus_is_less(Arc other) {
                return focus.x() < other.x();
            }
        private:
            Point focus;
    }
}