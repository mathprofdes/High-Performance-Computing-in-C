#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <omp.h>

using namespace std;

int main() {
	int n = 10;
	double start, stop;

	cout << "Input Array Size n: ";
	cin >> n;

	double *A = new double[n];
	double *B = new double[n];
	double *C = new double[n];

	printf("Initializing \n");

	for (int i = 0; i < n; i++)
		A[i] = 0;

	for (int i = 0; i < n; i++) {
		B[i] = 1.0 * rand() / RAND_MAX;
		C[i] = 1.0 * rand() / RAND_MAX;
	}

	printf("Calculations \n");

#pragma omp parallel
	{
		start = omp_get_wtime();
#pragma omp for schedule(static) nowait
		for (int i = 0; i < n; i++)
			for (int j = 0; j <= i; j++)
				A[i] += B[j];

#pragma omp for schedule(static)
		for (int i = 0; i < n; i++)
			for (int j = n - 1; j >= i; j--)
				C[i] += A[i];
		stop = omp_get_wtime();

#pragma omp single
		printf("Nowait time first loop (sec.) %.16f\n", stop - start);

		start = omp_get_wtime();
#pragma omp for schedule(static)
		for (int i = 0; i < n; i++)
			for (int j = 0; j <= i; j++) {
				A[i] += B[j];
			}

#pragma omp for schedule(static)
		for (int i = 0; i < n; i++)
			for (int j = n - 1; j >= i; j--)
				C[i] += A[i];
		stop = omp_get_wtime();

#pragma omp single
		printf("Time for each loop sync. (sec.) %.16f\n", stop - start);
	}

	delete[] A;
	delete[] B;
	delete[] C;

	return 0;
}
