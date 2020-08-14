namespace voronoi_constructs {
    template <class Point>
    class Ray {
        public:
            Ray(Point source, const Point::Coord slope) : source(source), slope(slope) {}
            static Ray perpendicular_to(Edge edge) {
                Point::CoordType perpendicular_slope = -(Point::CoordType(1)/edge.slope());
                return Ray(edge.middle_point(), perpendicular_slope);
            }
        private:
            Point source;
            Point::Coord slope;
    };
}