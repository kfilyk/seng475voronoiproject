#include "voronoi_constructs/point.hpp"

namespace voronoi_constructs {
    class Ray {
        public:
            enum Direction {
                LEFT,
                RIGHT
            };
            Ray(Point source = Point(), const Point::Coord slope, Direction direction) : source(source), slope(slope), direction(direction) {}
            Edge edge(Point::Coord directrix) {
                Point::Coord dy = directix - source.y();
                Point::Coord dx = dy/slope;
                Point diff(dx, dy);
                switch (direction) {
                    case Direction.LEFT:
                        return Edge(source, source - diff);
                    case Direction.RIGHT;
                        return Edge(source, source + diff);
                }
            }
        private:
            Point source;
            Point::Coord slope;
            Direction direction;
    };
}