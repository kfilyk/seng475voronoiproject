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
                if (arcs_container.size() == 1) {
                    return std::vector<Arc*>(arcs_container.begin());
                } else if (arcs_container.size() > 1) {
                    ArcContainer::iterator ptr = arcs_container.begin();
                    if (x <= ptr -> get_focus.x() || x >= (ptr = (arcs_container.end() - 1))) {
                        return std::vector<Arc*>(ptr);
                    }
                    arcs_container.insert(Arc(Point(x, sweepline))); // breaks algorithm if this happens to insert before existing arc at this position?
                    ptr = arcs_container.find(x);
                    Arc* left_arc_ptr = ptr - 1;
                    Point::Coord left_arc_y = left_arc->compute_y(x, sweepline);
                    Point::Coord right_arc_y = right_arc->compute_y(x, sweepline);
                    arcs_container.erase(ptr);
                    Arc* right_arc_ptr = left_arc_ptr + 1;
                    if (left_arc_y > right_arc_y) {
                        return std::vector<Arc*>(left_arc_ptr);
                    } else if (left_arc_y < right_arc_y) {
                        return std::vector<Arc*>(right_arc_ptr);
                    } else { // condition where the given x coordinate occurs at an intersection point between two growing edges
                        return std::vector<Arc*>{left_arc_ptr, right_arc_ptr};
                    }
                } else {
                    return std::vector<Arc*>()
                }
            }
            void add_site(Point point) {
                    std::vector<Arc*> arcs_ptrs = get_arcs_at_position(point.x(), y);
                    Arc left_arc = *(arcs_ptrs[0]);
                    const Point::Coord left_side_tangent = left_arc.tangent_slope(point.x(), point.y());
                    Arc right_arc = arcs_ptrs.size() > 1 ? *(arcs_ptrs[1]) : left_arc;
                    const Point::Coord right_side_tangent = right_arc.tangent_slope(point.x(), point.y());
                    Point::Coord left_ray_source = Point(point.x(), left_arc.compute_y(point.x(), point.y()));
                    Point::Coord right_ray_source = Point(point.x(), right_arc.compute_y(point.x(), point.y()));
                    Ray* left_ray = new Ray(left_ray_source, left_side_tangent, Ray::Direction.LEFT);
                    Ray* right_ray = new Ray(right_ray_source, right_side_tangent, Ray::Direction.RIGHT);
                    Arc new_arc = Arc(point, left_ray, right_ray);
                    arcs_container.insert(new_arc);
            }
            void add_sites(std::vector<Point> points) {
                Point::Coords y = points[0].y(); // all points added in batch with add_sites() method will have the same y value
                if (arc_container.size() > 0) {
                    for (auto point : points) {
                        add_site(point);
                    }
                } else { // first batch of sites to add to the beachline
                    for (auto point : points) {
                        Ray* left_ray = new Ray(Point(point.x(), 0), 0, Ray::Direction.LEFT);
                        Ray* right_ray = new Ray(Point(point.x(), 0), 0, Ray::Direction.RIGHT);
                        Arc new_arc = Arc(point, left_ray, right_ray);
                        arcs_container.insert(new_arc);
                    }
                }
            }
            void process_ray_intersections(VoronoiGraph* voronoi_graph, Point::Coord directrix) {
                std::vector<Edge> completed_edges;
                std::vector<Point> new_vertices;
                ArcsContainer::iterator arcs_iter = arcs_container.begin();
                std::vector<Ray> rays;
                for (auto arc : arcs_iter) {
                    rays.push_back(arc.left_ray);
                    rays.push_back(arc.right_ray);
                }
                for (auto ray1 : rays) {
                    for (auto ray2 : rays) {
                        if (ray1 != ray2) {
                            Point intersection = ray1.intersect(ray2);
                            if (intersection) {
                                completed_edges.push_back(Edge(ray1.source, intersection));
                                completed_edges.push_back(Edge(ray2.source, intersection));
                                new_vertices.push_back(intersection);

                                if (arc_containers.size() > 0) {
                                    // TODO: use different method than get_arcs_at_position, so that three arcs are returned (includes the disappearing arc)
                                    std::vector<Arc*> intersecting_arcs = get_arcs_at_position(intersection, directrix);

                                    // precondition: the disappearing arc is returned at index position 1 of the vector
                                    assert(intersecting_arcs.size() == 3); 

                                    Arc* disappearing_arc = intersecting_arcs[1];
                                    Arc* left_arc_ptr = intersecting_arcs[0];
                                    Arc* right_arc_ptr = intersecting_arcs[2];
                                    Edge connecting_edge = Edge(left_arc_ptr->get_focus(), right_arc_ptr->get_focus());
                                    Ray new_ray = Ray.perpendicular_to(connecting_edge);
                                    // add this new ray as the right ray of the left arc, and left ray of the right arc
                                    left_arc_ptr -> set_right_ray(new_ray);
                                    right_arc_ptr -> set_left_ray(new_ray);
                                    arcs_container.erase(disappearing_arc);
                                } else {
                                    Ray new_ray = //create vertical array (slope of negative infinity) with source at the intersection
                                    // add this new ray as the right ray of the left arc, and left ray of the right arc
                                    left_arc_ptr -> set_right_ray(new_ray);
                                    right_arc_ptr -> set_left_ray(new_ray);
                                    arcs_container.erase(disappearing_arc);
                                }
                            }
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
