#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main() {
	ofstream file;
	file.open("points.txt");
	srand(time(NULL));
	r = rand()%1000;
	do {
		for(int i = 0; i < 100; i++) {
			r = rand() % 1000;
			file << ran_data;
		}
		file.close();
	}
}
