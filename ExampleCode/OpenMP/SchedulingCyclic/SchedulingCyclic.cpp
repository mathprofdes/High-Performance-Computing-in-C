#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include <omp.h>

using namespace std;

double f(int i);

int main() {
	int numThreads, n;
	double start, end;
	srand(time(0));

	cout << "Input the array size: ";
	cin >> n;

	cout << "Input number of threads: ";
	cin >> numThreads;

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
# pragma omp parallel for num_threads(numThreads) default(none) shared(A, n) schedule(static, 1)
	for (int i = 0; i < n; i++)
		A[i] = f(i);
	end = omp_get_wtime();

	printf("Time to populate parallel cyclic (1): %f sec.\n", end - start);

	start = omp_get_wtime();
# pragma omp parallel for num_threads(numThreads) default(none) shared(A, n) schedule(static, 10)
	for (int i = 0; i < n; i++)
		A[i] = f(i);
	end = omp_get_wtime();

	printf("Time to populate parallel cyclic (10): %f sec.\n", end - start);

	start = omp_get_wtime();
# pragma omp parallel for num_threads(numThreads) default(none) shared(A, n) schedule(static, 25)
	for (int i = 0; i < n; i++)
		A[i] = f(i);
	end = omp_get_wtime();

	printf("Time to populate parallel cyclic (25): %f sec.\n", end - start);

/////////////////////

	start = omp_get_wtime();
# pragma omp parallel for num_threads(numThreads) default(none) shared(A, n) schedule(dynamic, 2)
	for (int i = 0; i < n; i++)
		A[i] = f(i);
	end = omp_get_wtime();

	printf("Time to populate parallel dynamic (2): %f sec.\n", end - start);

	start = omp_get_wtime();
# pragma omp parallel for num_threads(numThreads) default(none) shared(A, n) schedule(dynamic, 10)
	for (int i = 0; i < n; i++)
		A[i] = f(i);
	end = omp_get_wtime();

	printf("Time to populate parallel dynamic (10): %f sec.\n", end - start);

/////////////////////

	start = omp_get_wtime();
# pragma omp parallel for num_threads(numThreads) default(none) shared(A, n) schedule(guided)
	for (int i = 0; i < n; i++)
		A[i] = f(i);
	end = omp_get_wtime();

	printf("Time to populate parallel guided: %f sec.\n", end - start);

/////////////////////

	start = omp_get_wtime();
# pragma omp parallel for num_threads(numThreads) default(none) shared(A, n) schedule(auto)
	for (int i = 0; i < n; i++)
		A[i] = f(i);
	end = omp_get_wtime();

	printf("Time to populate parallel auto: %f sec.\n", end - start);

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
