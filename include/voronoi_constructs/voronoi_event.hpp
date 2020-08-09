namespace voronoi_constructs {
    enum VoronoiEventType {
        SITE,
        EDGE_INTERSECTION
    };
    template <class Point>
    class VoronoiEvent {
        public:
            const VoronoiEventType type;
            const Point point;
            VoronoiEvent(const VoronoiEventType type, const Point point) : type(type), point(point) {}
    };
}