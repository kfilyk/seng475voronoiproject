#include "voronoi_constructs/voronoi_event.hpp"

using namespace voronoi_constructs;

namespace voronoi_controllers {
    template <class Point>
    class EventsController {
        public:
            Beachline beachline;
            EventsController() : beachline() {}
            void handle_event(VoronoiEvent<Point> event) {
                switch (event.type) {
                    case VoronoiEventType::SITE:
                        beachline.add(event.site_point);
                        break;
                    case VoronoiEventType::EDGE_INTERSECTION:
                        beachline.remove(event.site_point);
                        break;
                }
            }
    };
}