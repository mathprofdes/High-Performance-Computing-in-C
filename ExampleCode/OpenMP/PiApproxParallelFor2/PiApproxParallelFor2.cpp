#include <iostream>
#include <sstream>
#include <cmath>

#include <omp.h>

using namespace std;

int main(int argc, char *argv[]) {
	int numThreads, n;
	double piapprox = 0;
	const double PI25DT = 3.141592653589793238462643;

	cout << "Input number of rectangles: ";
	cin >> n;

	cout << "Input number of threads: ";
	cin >> numThreads;

	if (numThreads <= 0) {
#pragma omp parallel
		numThreads = omp_get_num_threads();
	}

	double start = omp_get_wtime();
	double h = 1.0 / (double) n;

	for (int i = 0; i < n; i++) {
		double x = h * ((double) i + 0.5);
		piapprox += (4.0 / (1.0 + x * x));
	}
	piapprox = h * piapprox;
	double stop = omp_get_wtime();

	printf("Sequential pi is approximately %.16f, Error is %.16f\n", piapprox,
			fabs(piapprox - PI25DT));
	printf("Time (sec.) %.16f\n", stop - start);

	printf("Number of threads = %d\n", numThreads);

	start = omp_get_wtime();
	double parapiapprox = 0;

#pragma omp parallel for num_threads(numThreads) reduction(+: parapiapprox)
	for (int i = 0; i < n; i++) {
		double x = h * ((double) i + 0.5);
		parapiapprox += (4.0 / (1.0 + x * x));
	}

	parapiapprox = h * parapiapprox;
	stop = omp_get_wtime();

	printf("Parallel pi is approximately %.16f, Error is %.16f\n", parapiapprox,
			fabs(parapiapprox - PI25DT));
	printf("Time (sec.) %.16f\n", stop - start);

	return 0;
}
