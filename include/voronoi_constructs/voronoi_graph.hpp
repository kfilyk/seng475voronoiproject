#include <vector>
#include <edge.hpp>
namespace voronoi_constructs {
    template <class Point>
    class VoronoiGraph {
        using EdgesPtrContainer = std::vector<Edge<Point>*>;
        struct Vertex {
            Point* point;
            EdgesPtrContainer edges;
            Vertex(Point* point) : point(point), edges() {}
            void add_edge(Edge<Point>* edge) {
                edges.push_back(edge);
            }
        }
        using VertexContainer = std::map<Point*, Vertex>;
        EdgesPtrContainer edges;
        VertexContainer vertices;
        VoronoiGraph() : edges(), vertices() {}
        void add(Edge<Point> edge) {
            Edge<Point>* edge_ptr = new Edge<Point>(edge);
            edges.push_back(edge_ptr);

            // find the vertex that aligns with the source point of the edge, and add the edge pointer to it. If it doesn't exist yet in the 
            // graph, then first add the new vertex instance with the pointer to the source point.
            VertexContainer::iterator vertex_iter = vertices.find(edge_ptr->source);
            if (vertex_iter == vertices.end()) {
                vertices.insert(Vertex(edge_ptr->source));
                vertex_iter = vertices.find(edge_ptr->source);
            }
            vertex_iter->add_edge(edge_ptr);

            // find the vertex that aligns with the destination point of the edge, and add the edge pointer to it. If it doesn't exist yet in the 
            // graph, then first add the new vertex instance with the pointer to the destination point.
            vertex_iter = vertices.find(edge_ptr->dest);
            if (vertex_iter == vertices.end()) {
                vertices.insert(Vertex(edge_ptr->dest));
                vertex_iter = vertices.find(edge_ptr->dest);
            }
            vertex_iter->add_edge(edge_ptr);
        }
    };
}