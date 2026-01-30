#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <omp.h>

using namespace std;

int main() {
	int n = 10;
	double start, stop;

	cout << "Input Array Size n (n X n): ";
	cin >> n;

	double *A = new double[n * n];
	double *B = new double[n * n];
	double *C = new double[n * n];

	printf("Initializing \n");

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			A[i * n + j] = 0;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			B[i * n + j] = 1.0 * rand() / RAND_MAX;
			C[i * n + j] = 1.0 * rand() / RAND_MAX;
		}

	printf("Adding \n");
	start = omp_get_wtime();
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			A[i * n + j] = B[i * n + j] + C[i * n + j];
	stop = omp_get_wtime();
	printf("Sequential Time (sec.) %.16f\n", stop - start);

	start = omp_get_wtime();
#pragma omp parallel for
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			A[i * n + j] = B[i * n + j] + C[i * n + j];
	stop = omp_get_wtime();
	printf("Outer Loop Parallel Time (sec.) %.16f\n", stop - start);

	start = omp_get_wtime();
#pragma omp parallel for collapse(2)
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			A[i * n + j] = B[i * n + j] + C[i * n + j];
	stop = omp_get_wtime();
	printf("Double Loop Parallel Time (sec.) %.16f\n", stop - start);

	delete[] A;
	delete[] B;
	delete[] C;

	return 0;
}
