#include "voronoi_constructs/voronoi_event.hpp"
#include "voronoi_controllers/events_controller.hpp"
#include <stdlib.h>
#include <vector>
#include <string>
#include <boost/container/flat_set.hpp>
#include <iostream>
#include <fstream>

using namespace voronoi_constructs;
using namespace voronoi_controllers;
using PointType = std::vector<int>;
using string = std::string;
using VoronoiEvents = std::vector<VoronoiEvent<PointType>>;
using PointsContainer = boost::container::flat_set<PointType, PointType::PointIsLessThan>
PointsContainer extract_points(const std::string input_file_path) {
    	string line;
	string token;
	ifstream f("input_file_path");
	if f.is_open() {
		while(getline(f, line)) {
			token = line.substr(0, line.find(" "));						std::cout << token <<"\n";
		}
	}
	
	return PointsContainer(); // TODO: parse the input file and add the points to the points matrix
}

VoronoiEvents build_voronoi_events(const std::string input_file_path) {
    PointsContainer input_points = extract_points(input_file_path);
    VoronoiEvents voronoi_events(input_points);
    return voronoi_events;
}

int main() {
    const std::string input_file_path = "input_file.txt";
    EventsController<PointType> events_controller;
    VoronoiEvents voronoi_events = build_voronoi_events(input_file_path);
    for (auto event : voronoi_events) {
        events_controller.handle_event(event);
    }
}
