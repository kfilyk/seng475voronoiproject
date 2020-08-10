#include "voronoi_constructs/point.hpp"

namespace voronoi_constructs {
    enum BeachlineItemType {
        ARC,
        EDGE
    }
    bool operator<(Point p1, Point p2) {
        return p1.x() < p2.x();
    }
    bool operator<(Edge e1, Edge e2) {
        return (e1.src.x() < e2.src.x()) && (e1.dest.x() < e2.dest.x());
    }
    bool operator<(Point p, Edge e) {
        return (p.x() < e.src.x()) && (p.x() < e.dest.x());
    }
    bool operator<(Edge e, Point p) {
        return (e.src.x() < p.x()) && (e.dest.x() < p.x());
    }
    class BeachlineItem {
        public:
            BeachlineItem(Point point) {
                type = BeachlineItemType.ARC;
                _focus = point;
            }
            BeachlineItem(Edge edge) {
                type = BeachlineItemType.EDGE;
                _edge = edge;
            }
            bool IsLessThan(BeachlineItem other) {
                if (type == BeachlineItemType.ARC && other.type == BeachlineItemType.ARC) {
                    return _focus < other._focus;
                } else if (type == BeachlineItemType.ARC && other.type == BeachlineItemType.EDGE) {
                    return _focus < other._edge;
                } else if (type == BeachlineItemType.EDGE && other.type == BeachlineItemType.ARC) {
                    return _edge < other._focus;
                } else if (type == BeachlineItemType.EDGE && other.type == BeachlineItemType.EDGE) {
                    return _edge < other._edge;
                } else {
                    return false;
                }
            }
        private:
            Point _focus;
            Edge _edge;
    }
}