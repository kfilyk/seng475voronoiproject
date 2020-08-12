#include <vector>
namespace voronoi_constructs {
    template <class Point>
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
            std::vector<Edge<Point>> edges;
            std::vector<Point> vertices;
    };
}