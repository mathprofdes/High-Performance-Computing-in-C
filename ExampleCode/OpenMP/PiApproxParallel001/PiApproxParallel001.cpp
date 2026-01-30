#include <iostream>
#include <sstream>
#include <cmath>

#include <omp.h>

using namespace std;

int main(int argc, char *argv[]) {

	int numThreads, tid, n;
	double piapprox = 0;
	const double PI25DT = 3.141592653589793238462643;

	cout << "Input number of rectangles: ";
	cin >> n;

	double h = 1.0 / (double) n;

	for (int i = 0; i < n; i++) {
		double x = h * ((double) i + 0.5);
		piapprox += (4.0 / (1.0 + x * x));
	}
	piapprox = h * piapprox;

	printf("Sequential pi is approximately %.16f, Error is %.16f\n", piapprox,
			fabs(piapprox - PI25DT));

	double parapiapprox = 0;
#pragma omp parallel private(numThreads, tid)
	{
		numThreads = omp_get_num_threads();
		tid = omp_get_thread_num();

		double h = 1.0 / (double) n;

		int start = tid * (n / numThreads);
		int end = (tid + 1) * (n / numThreads);
		if (tid == numThreads - 1)
			end = n;

		for (int i = start; i < end; i++) {
			double x = h * ((double) i + 0.5);
			parapiapprox += (4.0 / (1.0 + x * x));
		}
	}

	parapiapprox = h * parapiapprox;

	printf("Parallel pi is approximately %.16f, Error is %.16f\n", parapiapprox,
			fabs(parapiapprox - PI25DT));

	return 0;
}
