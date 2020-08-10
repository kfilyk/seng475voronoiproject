#include "voronoi_constructs/arc.hpp"
#include "voronoi_constructs/ray.hpp"
#include "voronoi_constructs/voronoi_graph.hpp"

namespace voronoi_constructs {
    template<class Point>
    class Beachline {
        using ArcsContainer arcs_container = boost::container::flat_set<Arc, Arc.focus_is_less>;
        public:
            Beachline() : arcs_container() {}
            std::vector<Arc*> get_arcs_at_position(Point::Coord x, Point::Coord sweepline) {
                // TODO: handle corner cases: where no arcs (or less than three arcs) are in the beachline
                arcs_container.insert(Arc(Point(x, sweepline))); // breaks algorithm if this happens to insert before existing arc at this position?
                ArcContainer::iterator pointer_to_position_on_beachline = arcs_container.find(x);
                Arc* left_arc_ptr = pointer_to_position_on_beachline - 1;
                Arc* right_arc_ptr = pointer_to_position_on_beachline + 1;
                Point::Coord left_arc_y = left_arc->compute_y(x, sweepline);
                Point::Coord right_arc_y = right_arc->compute_y(x, sweepline);
                std::vector<Arc*> result;
                if (left_arc_y > right_arc_y) {
                    result = std::vector<Arc*>(left_arc_ptr);
                    arcs_container.remove(pointer_to_position_on_beachline);
                } else if (left_arc_y < right_arc_y) {
                    result = std::vector<Arc*>(right_arc_ptr);
                    arcs_container.remove(pointer_to_position_on_beachline);
                } else { // condition where the given x coordinate occurs at an intersection point between two growing edges (ie. shared by left arc, disappearing arc, and right arc)
                    // flaw: what happens if x is at a growing edge tip? then there's only left and right arc intersection, and the disappearing arc was removed in a previous sweepline state
                    result = std::vector<Arc*>{left_arc_ptr, pointer_to_position_on_beachline, right_arc_ptr};
                }
                return result;
            }
            void add_site(Point point) {
                std::vector<Arc*> arcs_ptrs = get_arcs_at_position(point.x(), point.y());
                Arc left_arc = *(arcs_ptrs[0]);
                const Point::Coord left_side_tangent = left_arc.tangent_slope(point.x(), point.y());
                Arc right_arc = arcs_ptrs.size() > 1 ? *(arc_ptrs[1]) : Arc(left_arc);
                const Point::Coord right_side_tangent = right_arc.tangent_slope(point.x(), point.y());
                Point::Coord left_ray_source = Point(point.x(), left_arc.compute_y(point.x(), point.y()));
                Point::Coord right_ray_source = Point(point.x(), right_arc.compute_y(point.x(), point.y()));
                Ray left_ray = Ray(left_ray_source, left_side_tangent, Ray::Direction.LEFT);
                Ray right_ray = Ray(right_ray_source, right_side_tangent, Ray::Direction.RIGHT);
                Arc new_arc = Arc(point, left_ray, right_ray);
                arcs_container.insert(new_arc);
            }
            void process_ray_intersections(VoronoiGraph* voronoi_graph, Point::Coord directrix) {
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
                            std::vector<Arc*> intersecting_arcs = get_arcs_at_position(intersection, directrix);

                            // precondition: the disappearing arc is returned at index position 1 of the vector
                            assert(intersecting_arcs.size() == 3); 

                            Arc* disappearing_arc = intersecting_arcs[1];
                            Arc* left_arc_ptr = intersecting_arcs[0];
                            Arc* right_arc_ptr = intersecting_arcs[2];
                            Ray new_ray = Ray.perpendicular_to(Edge(left_arc_ptr->get_focus(), right_arc_ptr->get_focus()));
                            // add this new ray as the right ray of the left arc, and left ray of the right arc
                            left_arc_ptr -> set_right_ray(new_ray);
                            right_arc_ptr -> set_left_ray(new_ray);
                            arcs_container.remove(disappearing_arc);
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
