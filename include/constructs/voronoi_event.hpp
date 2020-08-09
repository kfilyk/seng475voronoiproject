
namespace voronoi_constructs {
    enum VoronoiEventType {
        SITE,
        EDGE_INTERSECTION
    };
    template <class Point>
    class VoronoiEvent {
        VoronoiEventType type;
        VoronoiEvent(VoronoiEventType type) : type(type) {}
    };
}