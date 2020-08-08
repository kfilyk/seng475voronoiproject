#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>

using namespace std;

int main() {
	ofstream file("points.txt");
	srand(time(NULL));
	int r = rand()%1000;
	for(int i = 0; i < 100; i++) {
		file << r;
		file << " ";
		r = rand() % 1000;
		file << r;
		file <<"\n";

	}
	file.close();
}
