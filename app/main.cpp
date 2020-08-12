#include <stdlib.h>
#include <vector>
#include <map>
#include <string>
#include <set>
#include <point.hpp>
#include <arc.hpp>
#include <arc_intersections.hpp>
#include <edge.hpp>
#include <voronoi_graph.hpp>
#include <arc_intersections.hpp>

using namespace voronoi_constructs;
using PointType = Point<int>;
using Beachline = std::set<Arc<PointType>, arc_comparators::focus_is_less<PointType>>;
using ArcsVerticalInterceptsMap = std::map<PointType, Arc<PointType>*, point_comparators::y_is_greater<PointType::CoordType>>;

Beachline beachline;
ArcIntersections<PointType>::ArcIntersectionsSet arcs_intersections_set;
VoronoiGraph<PointType> voronoi_graph;

PointsContainer<PointType::CoordType> extract_points(const std::string input_file_path) {
    PointsContainer<PointType::CoordType> points;
	std::string line;
	std::string token;
	std::string token2;
	size_t pos = 0;
	ifstream f("input_file_path");
	if f.is_open() {
		while(getline(f, line)) {
			while((pos = line.find(" ")) != std::string::npos) {
				token = line.substr(0, pos);
				line.erase(0, pos+1);
				token2 = line.substr(0, pos);
				PointType pt(std::stoi(t), std::stoi(t2));
				points.insert(pt);
			}
		}
	}
	return points;
}

ArcsVerticalInterceptsMap compute_arcs_at_x(PointType::CoordType x, PointType::CoordType sweepline) {
	ArcsVerticalInterceptsMap arcs_at_x;
	for (auto arc : beachline) {
		Arc<PointType>* arc_ptr = new Arc(arc);
		PointType intercept_point = PointType(x, arc.compute_y(x, sweepline));
		arcs_at_x[intercept_point] = arc_ptr;
	}
	return arcs_at_x;
}

void process_edge_intersections(PointType::CoordType sweepline_y) {
	for (auto arc_intersection : arcs_intersections_set) {
		// TODO: process intersection for this arc
	}
}

// precondition: all points in the points vector have the same y value, since they are all associated with the same sweepline position
void add_sites(std::vector<PointType> points) {
	PointType::CoordType sweepline_y = points[0].y(); 
	if (beachline.size() > 0) {
		process_edge_intersections(sweepline_y);
	}
	for (auto point : points) {
		PointType::CoordType x = point.x();
		ArcsVerticalInterceptsMap arcs_at_x = compute_arcs_at_x(x, sweepline_y);
		PointType::CoordType first_arc_intercept_y = (arcs_at_x.begin()->first).y();
		Arc<PointType>::BachelorPointsSet bachelor_points{ new Point(x, first_arc_intercept_y), new Point(x, first_arc_intercept_y) };
		Arc<PointType> new_arc(point, bachelor_points);
		arcs_intersections_set.insert(ArcIntersections(new_arc, arcs_at_x));
		beachline.insert(new_arc);
	}
}

int main() {
    const std::string input_file_path = "input_file.txt";
    PointsContainer<PointType::CoordType> points = extract_points(input_file_path);
	std::map<PointType::CoordType, std::vector<PointType>> sweepline_map;
	for (auto point : points) {
		sweepline_map[point.y()].push_back(point);
	}
    for (auto key_val_pair : sweepline_map) {
		std::vector<PointType> points_at_y = key_val_pair.second;
        add_sites(points_at_y);
    }
}
