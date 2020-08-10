#include <vector>
#include "voronoi_constructs/edge.hpp"
#include "voronoi_constructs/point.hpp"

namespace VoronoiConstructs {
    class VoronoiGraph {
        public:
            VoronoiGraph() : edges(), vertices() {}
            void add_edges(std::vector<Edge> new_edges) {
                edges.insert(edges.end(), new_edges.begin(), new_edges.end());
            }
            void add_vertices(std::vector<Point> new_vertices) {
                vertices.insert(vertices.end(), new_vertices.begin(), new_vertices.end());
            }
        private:
            std::vector<Edge> edges;
            std::vector<Point> vertices;
    };
}