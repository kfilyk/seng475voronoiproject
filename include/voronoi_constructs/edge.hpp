namespace voronoi_constructs {
    template<class Point>
    struct Edge {
        Point source;
        Point dest;
        Edge() : source(0), dest(0) {}
        Edge(Point src, Point dest) : source(src), dest(dest) {}
        Point::CoordType slope() {
            return (dest.x() - source.x()) / (dest.y() - source.y());
        }
        Point middle_point() {
            return Point(
                (dest.x() + source.x())/2,
                (dest.y() + source.y())/2
            );
        }
    };
}
