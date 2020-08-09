
namespace voronoi_constructs {
    class Point {
        public:
            Point(int x, int y) : _x(x), _y(y) {}
            int x() {
                return _x;
            }
            int y() {
                return _y;
            }
        private:
            int _x;
            int _y;
    };
}