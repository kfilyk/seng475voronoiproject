#include <iostream>
#include <CGAL/Simple_cartesian.h>
#include "CGAL/Exact_predicates_inexact_constructions_kernel.h>"


typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_2<K> Point;
typedef Kernel::Segment_2<K> Segment;
//typedef CGAL::Polygon_2<K> Polygon;
using namespace std;

namespace voronoi {

	struct Line {
		Point p1;
		Point p2;
	};

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
