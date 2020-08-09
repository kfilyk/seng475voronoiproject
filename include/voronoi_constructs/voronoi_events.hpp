#include <vector>
#include "voronoi_constructs/voronoi_event.hpp"
namespace voronoi_constructs {
    template<class PointsContainer>
    class VoronoiEvents {
        public:
            std::vector<VoronoiEvent<PointsContainer::value_type>> events;
            VoronoiEvents(const PointsContainer points) {
                AddSiteEvents(points);
                AddEdgeIntersectionEvents();
            }
        private:
            AddSiteEvent(const PointsContainer points) {
                for (auto point : points) {
                    events.push_back(
                        VoronoiEvent(VoronoiEventType::SITE, point)
                    );
                }
            }
            AddEdgeIntersectionEvents(const PointsContainer points) {
                // for every combination of x coords on the beach line, add a site intersection event for the point (x, y) where the sweep line y position (directrix of the growing args for the two points)
                // is associated with an intersection of the two arcs at position x along the beach line.
            }
    };
}