#include "voronoi_constructs/point.hpp"

namespace voronoi_constructs {
    class Arc {
        public:
            Arc(const Point focus, Ray left_ray = Ray(), Ray right_ray = Ray())
                : _focus(focus), _left_ray(left_ray), _right_ray(right_ray) {}
            bool operator<(const Arc other) {
                return focus_is_less(other);
            }
            bool operator==(const Arc other) {
                return !(*this < other) && !(other < *this);
            }
            Point::Coord compute_y(Point::Coord x, Point::Coord directrix) {
                return (((x - _focus.x()) * (x - _focus.x()))/(2*(_focus.y() - directrix))) + ((_focus.y() + directrix)/2);
            }
            Point::Coord tangent_slope(Point::Coord x, Point::Coord directrix) {
                return (x - _focus.x())/(_focus.y() - directrix);
            }
            bool focus_is_less(Arc other) {
                return _focus.x() < other.x();
            }
            Ray get_left_ray() {
                return Ray(_left_ray);
            }
            Ray get_right_ray() {
                return Ray(_right_ray);
            }
            Point get_focus() {
                return Point(_focus);
            }
            void set_left_ray(Ray left_ray) {
                _left_ray(left_ray);
            }
            void set_right_ray(Ray right_ray) {
                _right_ray(right_ray);
            }
        private:
            Point _focus;
            Ray _left_ray;
            Ray _right_ray;
    }
}