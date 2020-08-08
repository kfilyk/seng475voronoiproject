#include "constructs/voronoi_event.hpp"

using namespace voronoi_constructs;

namespace voronoi_controllers {
    template <class Point>
    class EventsController {
        public:
            Beachline beachline;
            EventsController() : beachline() {}
            void handle_event(VoronoiEvent<Point> event) {
                //TODO: invoke the processing of the event
            }
    };
}