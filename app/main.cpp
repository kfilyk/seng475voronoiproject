#include <stdlib.h>
#include <vector>
#include <map>
#include <string>
#include <set>
#include <fstream>
#include <point.hpp>
#include <arc.hpp>
#include <arc_intersections.hpp>
#include <edge.hpp>
#include <bachelor_point.hpp>

using namespace voronoi_constructs;
using PointType = Point<int>;
using Beachline = std::set<Arc<PointType>*, arc_comparators::focus_is_less<PointType>>;
using ArcsVerticalInterceptsMap = std::map<PointType, Arc<PointType>*, point_comparators::y_is_greater<PointType::CoordType>>;
using VoronoiGraph = std::set<Edge<PointType>, edge_comparator::has_less_distance_from_origin<PointType>>;

Beachline beachline;
ArcIntersections<PointType>::ArcIntersectionsSet arcs_intersections_set;
VoronoiGraph voronoi_graph;

PointsContainer<PointType::CoordType> extract_points(const std::string input_file_path) {
    PointsContainer<PointType::CoordType> points;
	std::string line;
	std::string token;
	std::string token2;
	size_t pos = 0;
	std::ifstream f("input_file_path");
	if (f.is_open()) {
		while(getline(f, line)) {
			while((pos = line.find(" ")) != std::string::npos) {
				token = line.substr(0, pos);
				line.erase(0, pos+1);
				token2 = line.substr(0, pos);
				PointType pt(std::stoi(token), std::stoi(token2));
				points.insert(pt);
			}
		}
	}
	return points;
}

ArcsVerticalInterceptsMap compute_arcs_at_x(PointType::CoordType x, PointType::CoordType sweepline) {
	ArcsVerticalInterceptsMap arcs_at_x;
	for (Arc<PointType>* arc : beachline) {
		PointType intercept_point = PointType(x, arc->compute_y(x, sweepline));
		arcs_at_x[intercept_point] = arc;
	}
	return arcs_at_x;
}

void free_bachelor_point(BachelorPoint<PointType>* bachelor_point) {
	for (Arc<PointType>* arc : bachelor_point->arcs) {
		// unsubscribe the bachelor point from any participating arcs that may be owning it, and requires bachelor point knowledge of arcs that own it
		(arc->bachelor_points).erase(bachelor_point);
	}
	delete bachelor_point;
}

void process_edge_intersections() {
	for (auto arc_intersections : arcs_intersections_set) {
		Arc<PointType>* arc = arc_intersections.arc;
		BachelorPoint<PointType>::BachelorPointsPtrSet bachelor_iter = (arc->bachelor_points).begin();
		BachelorPoint<PointType>* left_intersection_bachelor_point = *bachelor_iter;
		BachelorPoint<PointType>* right_intersection_bachelor_point = *(++bachelor_iter);
		std::vector<Edge<PointType>> completed_edges {
			Edge<PointType>(left_intersection_bachelor_point->point, arc_intersections.left_intersection),
			Edge<PointType>(right_intersection_bachelor_point->point, arc_intersections.right_intersection)
		};
		voronoi_graph.insert(completed_edges.begin(), completed_edges.end());
		free_bachelor_point(left_intersection_bachelor_point);
		free_bachelor_point(right_intersection_bachelor_point);
		Arc<PointType>* disappearing_arc = arc_intersections.disappearing_arc;
		if (disappearing_arc != nullptr) {
			beachline.erase(disappearing_arc);
			delete disappearing_arc;
		}
		delete arc_intersections.arc;
	}
	arcs_intersections_set.clear();
}

// precondition: all points in the points vector have the same y value, since they are all associated with the same sweepline position
void process_site_events(std::vector<PointType> points) {
	PointType::CoordType sweepline_y = points[0].y(); 
	for (auto point : points) {
		PointType::CoordType x = point.x();
		ArcsVerticalInterceptsMap arcs_at_x = compute_arcs_at_x(x, sweepline_y);
		Arc<PointType>* first_arc = (arcs_at_x.begin())->second;
		PointType first_arc_intercept = first_arc->get_focus();

		// instantiate bachelor points with knowledge of the arc they will eventually destroy (first_arc)
		BachelorPoint<PointType>::BachelorPointsPtrSet bachelor_points {
			new BachelorPoint<PointType>(first_arc_intercept, std::vector<Arc<PointType>*>{first_arc}),
			new BachelorPoint<PointType>(first_arc_intercept, std::vector<Arc<PointType>*>{first_arc})
		};

		// give the new arc knowledge of the bachelor points it owns
		Arc<PointType>* new_arc = new Arc<PointType>(point, bachelor_points);

		arcs_intersections_set.insert(ArcIntersections<PointType>(new_arc, arcs_at_x));
		for (auto kv_pair : arcs_at_x) {
			delete (kv_pair.second); // free the arc pointers in the arc intersections map
		}
		beachline.insert(new_arc);
	}
}

int main() {
    const std::string input_file_path = "input_file.txt";
    PointsContainer<PointType::CoordType> points = extract_points(input_file_path);
	std::map<PointType::CoordType, std::vector<PointType>> sweepline_map;
	for (auto point : points) {
		PointType::CoordType sweepline_y = point.y();
		if (sweepline_map.find(sweepline_y) == sweepline_map.end()) {
			sweepline_map[sweepline_y] = std::vector<PointType>();
		}
		sweepline_map[sweepline_y].push_back(point);
	}
    for (auto key_val_pair : sweepline_map) {
		if (beachline.size() > 0) {
			process_edge_intersections();
		}
        process_site_events(key_val_pair.second);
    }
}