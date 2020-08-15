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
#include <ray.hpp>

using namespace voronoi_constructs;
using PointType = Point<int>;
using Beachline = std::set<Arc<PointType>*, arc_comparators::focus_is_less<PointType>>;
using ArcsVerticalInterceptsMap = std::map<PointType, Arc<PointType>*, point_comparators::y_is_greater<PointType>>;
using VoronoiGraph = std::vector<Edge<PointType>>;
using PointsContainer = std::set<PointType, point_comparators::x_is_less<PointType>>;
using ArcsPtrSet = std::set<Arc<PointType>*>;
using DisappearingArcsMap = std::set<Arc<PointType>*, DisappearingArc<PointType>*>; 

Beachline beachline;
ArcIntersections<PointType>::ArcIntersectionsSet arcs_intersections_set;
VoronoiGraph voronoi_graph;
DisappearingArcsMap* disappearing_arcs_map;

PointsContainer extract_points(const std::string input_file_path) {
    PointsContainer points;
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
	for (Arc<PointType>* arc : bachelor_point->participating_beachline_arcs) {
		// unsubscribe the bachelor point from any participating arcs that may be owning it, and requires bachelor point knowledge of arcs that own it
		if (arc != nullptr) { // arc pointer is nullptr in the case that the bachelor points are associated with the intercept at the top of the window (y = 0), when processing the first new sites
			(arc->bachelor_points).erase(bachelor_point);
		}
	}
	delete bachelor_point;
}

void process_disappearing_arc(ArcIntersections<PointType> arc_intersections) {
	DisappearingArc<PointType> disappearing_arc = arc_intersections.disappearing_arc;
	if (disappearing_arc.arc != nullptr) {
		--(disappearing_arc.num_arc_intersections);
		if (disappearing_arc.num_arc_intersections <= 0) {
			beachline.erase(disappearing_arc.arc);
			delete disappearing_arc.arc;
		}
	}
}

void process_intersections() {
	for (auto arc_intersections : arcs_intersections_set) {
		Arc<PointType>* arc = arc_intersections.arc;
		BachelorPoint<PointType>::BachelorPointsPtrSet bachelor_iter = (arc->bachelor_points).begin();
		BachelorPoint<PointType>* left_intersection_bachelor_point = *bachelor_iter;
		BachelorPoint<PointType>* right_intersection_bachelor_point = *(++bachelor_iter);
		voronoi_graph.push_back(Edge<PointType>(left_intersection_bachelor_point->point, *(arc_intersections.left_intersection)));
		voronoi_graph.push_back(Edge<PointType>(right_intersection_bachelor_point->point, *(arc_intersections.right_intersection)));
		free_bachelor_point(left_intersection_bachelor_point);
		free_bachelor_point(right_intersection_bachelor_point);

		process_disappearing_arc(arc_intersections);

		BachelorPoint<PointType> new_bachelor_point_left(*(arc_intersections.left_intersection));
		BachelorPoint<PointType> new_bachelor_point_right(*(arc_intersections.right_intersection));
		(arc_intersections.arc->bachelor_points).insert(new_bachelor_point_left);
		(arc_intersections.arc->bachelor_points).insert(new_bachelor_point_right);
	}
	arcs_intersections_set.clear();
}

void add_new_arc_intersections(ArcIntersections<PointType> arc_intersections) {
	ArcIntersections<PointType>* new_arc_intersections = arcs_intersections_set.insert(arc_intersections);
	if ((new_arc_intersections != arcs_intersections_set.begin()) && (new_arc_intersections != (arcs_intersections_set.end() - 1))) {
		ArcIntersections<PointType>* left_arc_intersections = new_arc_intersections - 1;
		ArcIntersections<PointType>* right_arc_intersections = new_arc_intersections + 1;
		PointType* right_intersection_of_left_arc = left_arc_intersections->right_intersection;
		PointType* left_intersection_of_new_arc = new_arc_intersections->left_intersection;
		if (left_intersection_of_new_arc != nullptr && right_intersection_of_left_arc != nullptr) {
			if (left_intersection_of_new_arc->x_is_less(*right_intersection_of_left_arc)) {
				if (left_arc_intersections->arc->get_focus() < left_intersection_of_new_arc) {
					*(right_intersection_of_left_arc) = *(left_intersection_of_new_arc);
				} else {
					*(right_intersection_of_left_arc) = left_arc_intersections->arc->bachelor_points[0]->point;
					*(left_intersection_of_new_arc) = left_arc_intersections->arc->bachelor_points[0]->point;
				}
			}
		}
		PointType* left_intersection_of_right_arc = right_arc_intersections->left_intersection;
		PointType* right_intersection_of_new_arc = new_arc_intersections->right_intersection;
		if (left_intersection_of_right_arc != nullptr && right_intersection_of_new_arc != nullptr) {
			if (left_intersection_of_right_arc->x_is_less(*right_intersection_of_new_arc)) {
				if (right_intersection_of_new_arc < right_arc_intersections->arc->get_focus()) {
					*(left_intersection_of_right_arc) = *(right_intersection_of_new_arc);
				} else {
					*(left_intersection_of_right_arc) = right_arc_intersections->arc->bachelor_points[0]->point;
					*(new_arc_intersections) = right_arc_intersections->arc->bachelor_points[0]->point;
				}
			}
		}
	}
}

// precondition: all points in the points vector have the same y value, since they are all associated with the same sweepline position
void process_site_events(PointsContainer points) {
	PointType::CoordType sweepline_y = points.begin()->y(); 
	for (auto site_focus_point : points) {
		PointType::CoordType x = site_focus_point.x();
		ArcsVerticalInterceptsMap arcs_at_x = compute_arcs_at_x(x, sweepline_y);
		ArcsVerticalInterceptsMap::iterator arcs_at_x_iter = arcs_at_x.begin();
		PointType first_arc_intersection_point;
		Arc<PointType>* first_arc;
		if (arcs_at_x_iter == arcs_at_x.end()) {
			first_arc_intersection_point = PointType(x, 0);
			first_arc = nullptr;
		} else {
			first_arc_intersection_point = arcs_at_x_iter->first;
			first_arc = arcs_at_x_iter->second;
		}

		BachelorPoint<PointType>::BachelorPointsPtrSet bachelor_points {
			new BachelorPoint<PointType>(first_arc_intersection_point),
			new BachelorPoint<PointType>(first_arc_intersection_point)
		};

		// give the new arc knowledge of the bachelor points it owns
		Arc<PointType>* new_arc = new Arc<PointType>(site_focus_point, bachelor_points);
		ArcIntersections<PointType> arc_intersections(new_arc, arcs_at_x, disappearing_arcs_map);
		if (arc_intersections.left_intersection != nullptr && arc_intersections.right_intersection != nullptr) {
			add_new_arc_intersections(arc_intersections);
		}
		beachline.insert(new_arc);
	}
}

void process_unresolved_bachelor_points() {
	// beachline arcs will share bachelor points with neighboring arcs, so must construct a unique set of bachelor points to act on
	BachelorPoint<PointType>::BachelorPointsPtrSet bachelor_points;
	for (auto arc : beachline) {
		bachelor_points.insert(arc->bachelor_points.begin(), arc->bachelor_points.end());
	}

	for (BachelorPoint<PointType>* bachelor_point : bachelor_points) {
		PointType source_point = *bachelor_point;
		ArcsPtrSet::iterator neighboring_beachline_arcs = bachelor_point->participating_beachline_arcs.begin();
		// if the bachelor point doesn't have neighbouring arcs on the beachline, this means it is a corner case where the voronoi graph
		// consists of sites along one iteration of the sweepline, in which case it is nullptr and the code segment is ignored
		if (*neighboring_beachline_arcs != nullptr) {
			Edge<PointType> arcs_connecting_edge(*neighboring_beachline_arcs, *(neighboring_beachline_arcs + 1));
			Ray<PointType> perpendicular_ray = Ray<PointType>::perpendicular_to(arcs_connecting_edge);
			PointType dest_point = perpendicular_ray.closest_intersection_to_boundaries();
			voronoi_graph.push_back(Edge<PointType>(source_point, dest_point));
		}
	}
}

int main() {
    const std::string input_file_path = "input_file.txt";
    PointsContainer points = extract_points(input_file_path);
	std::map<PointType::CoordType, PointsContainer> sweepline_map;
	for (auto point : points) {
		PointType::CoordType sweepline_y = point.y();
		if (sweepline_map.find(sweepline_y) == sweepline_map.end()) {
			sweepline_map[sweepline_y] = PointsContainer();
		}
		sweepline_map[sweepline_y].insert(point);
	}
    for (auto key_val_pair : sweepline_map) {
        process_site_events(key_val_pair.second);
    }
	process_intersections();
	process_unresolved_bachelor_points();
}