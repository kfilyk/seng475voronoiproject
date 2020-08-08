#include <iostream>
#include <CGAL/Cartesian.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
typedef CGAL::Cartesian<double> K;
typedef K::Point_2 Point;
using namespace std;

namespace voronoi {

	
/*
	class Cell {
		private:
			Polygon po;
			Point center;
		public:
			Cell();
			Cell(Point[] points, Point center) {
				for(int i = 0; i < sizeof(points>; i++) {
					po.pushback(points[i]);		
				}
			}
			Polygon getPoly() {
				return po;
			}		
			Point getCenter() {
				return center;
			}
	}
*/
	class SweepLine {
		int pos;
	};
}
