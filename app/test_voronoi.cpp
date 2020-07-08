#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "../include/graph.hpp"
#include "CGAL/Exact_predicates_inexact_constructions_kernel.h>


using namespace std;
using namespace voronoi;
TEST_CASE("v1", "[simple]") {
	Point p1[5] = {Point(0,0), Point(4,0), Point(4,4), Point(2,2), Point(0,4)}; 
	for(int i = 0; i<5; i++) {
		CGAL::draw(p1[i]);
	}
}

