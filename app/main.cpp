#include <stdlib.h>
#include <vector>
#include <map>
#include <string>
#include "voronoi_constructs/point.hpp"
#include "voronoi_constructs/beachline.hpp"

using namespace voronoi_constructs;

PointsContainer extract_points(const std::string input_file_path) {
    PointsContainer points;
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

int main() {
    const std::string input_file_path = "input_file.txt";
    PointsContainer points = extract_points(input_file_path);
    VoronoiGraph* voronoi_graph = new VoronoiGraph();
    Beachline beachline;
	std::map<Point::Coord, std::vector<Point>> sweepline_map;
	for (auto point : points) {
		sweepline_map[point.y()].push_back(point);
	}
    for (auto y_key_vals : sweepline_map) {
		Point::Coord y = y_key_vals -> first;
		std::vector<Point> points_at_y = y_key_vals -> second;
		// make sure all intersection events that should have occured since the previous site event are processed here, AT THE POSITION that they would have occurred before this site event loop iteration
		beachline.process_ray_intersections(voronoi_graph, y);
        beachline.add_sites(points_at_y);
    }
}
