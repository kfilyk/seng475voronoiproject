#include <iostream>
#include <CGAL/Cartesian.h>

typedef CGAL::Cartesian<double> K;
typedef Kernel::Point_2<K> Point;
typedef Kernel::Line_2<K> Line;
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
