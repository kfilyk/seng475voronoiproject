namespace voronoi_constructs {
    template<class Point>
    class Beachline {
        using PointsContainer = boost::container::flat_set<Point, LessOnBeachline>;
        public:
            Beachline() {}
            add(Point point) {
                points.insert(point);
            }
        private:
            PointsContainer points;
    };
}
