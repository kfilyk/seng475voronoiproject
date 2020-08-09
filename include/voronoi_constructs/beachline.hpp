namespace voronoi_constructs {
    template<class Point>
    class Beachline {
        using PointsContainer = boost::container::flat_set<BeachLineItem, BeachlineItem.IsLessThan>;
        public:
            Beachline() {}
            add(BeachlineItem item) {
                points.insert(item);
            }
        private:
            PointsContainer points;
    };
    
}
