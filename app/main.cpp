#include <stdlib.h>
#include <vector>
#include <string>
#include "voronoi_constructs/point.hpp"
using namespace voronoi_constructs;
using namespace voronoi_controllers;

PointsContainer extract_points(const std::string input_file_path) {
    	PointsContainer pc();
	string line;
	string token;
	string token2;
	size_t pos = 0;
	ifstream f("input_file_path");
	if f.is_open() {
		while(getline(f, line)) {
			while((pos = line.find(" ")) != string::npos) {
				token = line.substr(0, pos);	
				line.erase(0, pos+1);
				token2 = line.substr(0, pos);
				PointType pt(std::stoi(t), std::stoi(t2));
				pc.insert(pt);
			}
		}
	}
	
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
