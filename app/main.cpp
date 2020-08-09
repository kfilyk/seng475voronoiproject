#include <stdlib.h>
#include <vector>
#include <string>
#include "voronoi_constructs/point.hpp"

using namespace voronoi_constructs;
using namespace voronoi_controllers;

PointsContainer extract_points(const std::string input_file_path) {
    return PointsContainer(); // TODO: parse the input file and add the points to the points matrix
}

int main() {
    const std::string input_file_path = "input_file.txt";
    PointsContainer points = extract_points(input_file_path);
    Beachline beachline;
    for (auto point : points) {
        beachline.add(BeachlineItem(BeachlineItemType.ARC, point));
    }
}