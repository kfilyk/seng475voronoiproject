#include "voronoi_constructs/arc.hpp"
#include "voronoi_constructs/ray.hpp"
#include "voronoi_constructs/voronoi_graph.hpp"

namespace voronoi_constructs {
    template<class Point>
    class Beachline {
        using ArcsContainer arcs_container = boost::container::flat_set<Arc, Arc.focus_is_less>;
        public:
            Beachline() {}
            std::vector<Arc> get_arcs_at_position(Point::Coord x, Point::Coord sweepline) {
                arcs_container.insert(Arc(Point(x, sweepline)));
                ArcContainer::iterator pointer_to_position_on_beachline = arcs_container.insert(x);
                Arc left_arc = *(pointer_to_position_on_beachline - 1);
                Arc right_arc = *(pointer_to_position_on_beachline + 1);
                arcs_container.remove(pointer_to_position_on_beachline);
                Point::Coord left_arc_y = left_arc.compute_y(x, sweepline);
                Point::Coord right_arc_y = right_arc.compute_y(x, sweepline);
                if (left_arc_y > right_arc_y) {
                    return std::vector<Arc>(left_arc);
                } else if (left_arc_y < right_arc_y) {
                    return std::vector<Arc>(right_arc);
                } else {
                    return std::vector<Arc>{left_arc, right_arc};
                }
            }
            void add_site(Point point) {
                std::vector<Arc> arcs = get_arcs_at_position(point.x(), point.y());
                const Point::Coord left_side_tangent = arcs[0].tangent_slope(point.x());
                const Point::Coord right_side_tangent = arcs.size() > 1 ?
                    arcs[1].tangent_slope(point.x())
                    : Point::Coord(left_side_tangent);
                Ray left_ray = Ray(point, left_side_tangent, Ray::Direction.LEFT);
                Ray right_ray = Ray(point, right_side_tangent, Ray::Direction.RIGHT);
                Arc new_arc = Arc(point, left_ray, right_ray);
                arcs_container.insert(new_arc);
            }
            void process_ray_intersections(VoronoiGraph* voronoi_graph) {
                std::vector<Edge> completed_edges;
                std::vector<Point> new_vertices;
                ArcsContainer::iterator arcs_iter = arcs_container.begin();
                std::vector<Ray> left_rays;
                std::vector<Ray> right_rays;
                for (auto arc : arcs_iter) {
                    left_rays.push_back(arc.left_ray);
                    right_rays.push_back(arc.right_ray);
                }
                for (auto left_ray : left_rays) {
                    for (auto right_ray : right_rays) {
                        Point intersection = left_ray.intersect(right_ray);
                        if (intersection) {
                            completed_edges.push_back(Edge(left_ray.source, intersection));
                            completed_edges.push_back(Edge(right_ray.source, intersection));
                            new_vertices.push_back(intersection);
                            Arc disappearing_arc = get_arcs_at_position(intersection.x());
                            arcs_container.remove(arcs_container.find(disappearing_arc));
                            //TODO: create new ray extending from the intersection point, and add copies of this ray to the left and right arcs that flanked the disappearing arc
                        }
                    }
                }
                voronoi_graph.add_edges(completed_edges);
                voronoi_graph.add_vertices(new_vertices);
            }
        private:
            ArcsContainer arcs_container;
    };
    
}
