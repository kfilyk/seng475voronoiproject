#include <stdlib.h>
#include <vector>
#include <string>
#include "voronoi_constructs/point.hpp"
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
    Beachline beachline;
    for (auto point : points) {
        beachline.add(BeachlineItem(BeachlineItemType.ARC, point));
    }
}
