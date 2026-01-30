#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include <omp.h>

using namespace std;

double f(int i);

int main(int argc, char** argv) {
	int numThreads, n;
	double start, end;
	srand(time(0));

	if (argc != 3)
		exit(1);

	n = strtol(argv[1], NULL, 10);
	numThreads = strtol(argv[2], NULL, 10);

	if (numThreads <= 0) {
#pragma omp parallel
		numThreads = omp_get_num_threads();
	}

	double *A = new double[n];

	start = omp_get_wtime();
	for (int i = 0; i < n; i++)
		A[i] = f(i);
	end = omp_get_wtime();

	printf("Time to populate serial: %f sec.\n", end - start);

	printf("Number of threads: %d \n", numThreads);

	start = omp_get_wtime();
# pragma omp parallel for num_threads(numThreads) default(none) shared(A, n)
	for (int i = 0; i < n; i++)
		A[i] = f(i);
	end = omp_get_wtime();

	printf("Time to populate parallel block: %f sec.\n", end - start);

	start = omp_get_wtime();
# pragma omp parallel for num_threads(numThreads) default(none) shared(A, n) schedule(runtime)
	for (int i = 0; i < n; i++)
		A[i] = f(i);
	end = omp_get_wtime();

	printf("Time to populate parallel runtime: %f sec.\n", end - start);

	delete[] A;

	return 0;
}

double f(int n) {
	double val = 0;
	int s = n * (n + 1) / 2, e = s + n;

	for (int i = s; i < e; i++) {
		val += sin(i);
	}

	return val;
}
