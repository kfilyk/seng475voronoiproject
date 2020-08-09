#include "constructs/voronoi_event.hpp"
#include "controllers/events_controller.hpp"
#include <stdlib.h>
#include <vector>
#include <string>

using namespace voronoi_constructs;
using namespace voronoi_controllers;
using PointType = std::vector<int>;
using VoronoiEvents = std::vector<VoronoiEvent<PointType>>;

VoronoiEvents build_voronoi_events(const std::string input_file_path) {
    return VoronoiEvents(); // TODO: parse data points from the input file, add voronoi events in order to this vector, and return the reference to the vector
}

int main() {
    const std::string input_file_path = "input_file.txt";
    EventsController<PointType> events_controller;
    VoronoiEvents voronoi_events = build_voronoi_events(input_file_path);
    for (auto event : voronoi_events) {
        events_controller.handle_event(event);
    }
}