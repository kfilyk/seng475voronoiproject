#include "voronoi_constructs/point.hpp"

namespace voronoi_constructs {
    class Arc {
        public:
            Arc(const Point focus, Ray left_ray = Ray(), Ray right_ray = Ray())
                : focus(focus), left_ray(left_ray), right_ray(right_ray) {}
            bool operator<(const Arc other) {
                return focus_is_less(other);
            }
            bool operator==(const Arc other) {
                return !(*this < other) && !(other < *this);
            }
            Point::Coord compute_y(Point::Coord x, Point::Coord directrix) {
                return (((x - focus.x()) * (x - focus.x()))/(2*(focus.y() - directrix))) + ((focus.y() + directrix)/2);
            }
            Point::Coord tangent_slope(Point::Coord x, Point::Coord directrix) {
                return (x - focus.x())/(focus.y() - directrix);
            }
            bool focus_is_less(Arc other) {
                return focus.x() < other.x();
            }
        private:
            Point focus;
            Ray left_ray;
            Ray right_ray;
    }
}