#include <iostream>
#include <omp.h>

using namespace std;

int f(int x, int z);
int g(int x);

int main() {
	int x, y, z;
	x = z = 5;
	y = 3;

	cout << "Program started..." << endl;

#pragma omp parallel
#pragma omp critical
	y = f(x, z);

	cout << x << " " << y << " " << z << endl;
	cout << "Program finished." << endl;

	return 0;
}

int f(int x, int z) {
#pragma omp critical
	z = g(x);
	return 2 * z;
}

int g(int x) {
	return 3 * x;
}

