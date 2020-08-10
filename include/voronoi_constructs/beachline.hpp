#include "voronoi_constructs/arc.hpp"

namespace voronoi_constructs {
    template<class Point>
    class Beachline {
        using ArcsContainer arcs_container = boost::container::flat_set<Arc, Arc.focus_is_less>;
        public:
            Beachline() {}
            std::vector<Arc> get_arcs_at_position(Point::Coord x, Point::Coord sweepline) {
                arcs_container.insert(Arc(Point(x, sweepline)));
                ArcContainer::iterator pointer_to_position_on_beachline = arcs_container.insert(x);
                Arc left_arc = *(pointer_to_position_on_beachline - 1);
                Arc right_arc = *(pointer_to_position_on_beachline + 1);
                arcs_container.remove(pointer_to_position_on_beachline);
                Point::Coord left_arc_y = left_arc.compute_y(x, sweepline);
                Point::Coord right_arc_y = right_arc.compute_y(x, sweepline);
                if (left_arc_y > right_arc_y) {
                    return std::vector<Arc>(left_arc);
                } else if (left_arc_y < right_arc_y) {
                    return std::vector<Arc>(right_arc);
                } else {
                    return std::vector<Arc>{left_arc, right_arc};
                }
            }
            void add_site(Point point) {
                arcs_container.insert(Arc(point));
            }
        private:
            ArcsContainer arcs_container;
    };
    
}
