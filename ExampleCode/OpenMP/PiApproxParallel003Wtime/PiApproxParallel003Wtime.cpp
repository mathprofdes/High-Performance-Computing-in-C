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
	double partialsums[numThreads];
#pragma omp parallel private(tid) num_threads(numThreads)
	{
		tid = omp_get_thread_num();
		partialsums[tid] = 0;

		double h = 1.0 / (double) n;

		for (int i = tid; i < n; i += numThreads) {
			double x = h * ((double) i + 0.5);
			partialsums[tid] += (4.0 / (1.0 + x * x));
		}
	}

	double parapiapprox = 0;
	for (int i = 0; i < numThreads; i++)
		parapiapprox += partialsums[i];

	parapiapprox = h * parapiapprox;
	stop = omp_get_wtime();

	printf("Parallel pi is approximately %.16f, Error is %.16f\n", parapiapprox,
			fabs(parapiapprox - PI25DT));
	printf("Time (sec.) %.16f\n", stop - start);

	return 0;
}
