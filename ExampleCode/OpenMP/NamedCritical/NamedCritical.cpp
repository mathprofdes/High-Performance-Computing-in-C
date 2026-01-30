#include <iostream>
#include <omp.h>

using namespace std;

int f(int x, int z);
int g(int x);

int main() {
	int x, y, z;
	int numThreads = 0;
	x = z = 5;
	y = 3;

	cout << "Program started..." << endl;

#pragma omp parallel
	numThreads = omp_get_num_threads();

	if (numThreads > 4)
		numThreads = 4;

#pragma omp parallel num_threads(numThreads) private(x, y)
	{
		x = omp_get_thread_num();

#pragma omp critical(one)
		y = f(x, z);

		printf("%d %d %d \n", x, y, z);
	}

	cout << "Program finished." << endl;

	return 0;
}

int f(int x, int z) {
#pragma omp critical(two)
	z = g(x);
	return 2 * z;
}

int g(int x) {
	return 3 * x;
}

