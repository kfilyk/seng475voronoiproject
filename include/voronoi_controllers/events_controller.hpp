#include "voronoi_constructs/voronoi_event.hpp"

using namespace voronoi_constructs;

namespace voronoi_controllers {
    template <class Point>
    class EventsController {
        public:
            Beachline beachline;
            VoronoiGraph voronoi_graph;
            EventsController() : beachline() {}
            void handle_event(const VoronoiEvent<Point> event) {
                beachline.add(event);
            }
    };
}