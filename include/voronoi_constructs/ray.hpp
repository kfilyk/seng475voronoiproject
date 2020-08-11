#include "voronoi_constructs/point.hpp"
#include "voronoi_constructs/edge.hpp"
namespace voronoi_constructs {
    class Ray {
        public:
            enum Direction {
                LEFT,
                RIGHT
            };
            Ray(Point source = Point(), const Point::Coord slope, Direction direction) : source(source), slope(slope), direction(direction) {}
            Edge edge(Point::Coord directrix) {
                assert(slope != 0);
                if (directrix == source.y()) {
                    Point::Coord dy = directix - source.y();
                    Point::Coord dx = dy/slope;
                    Point diff(dx, dy);
                    switch (direction) {
                        case Direction.LEFT:
                            return Edge(source, source - diff);
                        case Direction.RIGHT;
                            return Edge(source, source + diff);
                    }
                } else {
                    return Edge;
                }
            }
            static Ray perpendicular_to(Edge edge) {
                assert(edge.slope() != 0);
                Point::Coord perpendicular_slope = -(1/edge.slope());
                return Ray(edge.middle_point(), perpendicular_slope);
            }
        private:
            Point source;
            Point::Coord slope;
            Direction direction;
    };
}