#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <omp.h>

using namespace std;

bool compareVectors(double *y, double *yp, int n, double tol);

int main() {
	int numThreads, r, c;
	double start, end;
	srand(time(0));

	cout << "Input the coefficient array size r c: ";
	cin >> r >> c;

	cout << "Input number of threads: ";
	cin >> numThreads;

	if (numThreads <= 0) {
#pragma omp parallel
		numThreads = omp_get_num_threads();
	}

	double *A = new double[r * c];
	double *x = new double[c];
	double *y = new double[r];
	double *yp = new double[r];

	// Populate A and x.
	for (int i = 0; i < r * c; i++)
		A[i] = (1.0 * rand()) / RAND_MAX;

	for (int i = 0; i < c; i++)
		x[i] = (1.0 * rand()) / RAND_MAX;

	start = omp_get_wtime();
	for (int i = 0; i < r; i++) {
		y[i] = 0.0;
		for (int j = 0; j < c; j++)
			y[i] += A[i * c + j] * x[j];
	}
	end = omp_get_wtime();
	printf("Time for y = Ax serial: %f sec.\n", end - start);

	printf("Number of threads: %d \n", numThreads);

	start = omp_get_wtime();
#pragma omp parallel for num_threads(numThreads) default(none) shared(A, x, yp, r, c)
	for (int i = 0; i < r; i++) {
		yp[i] = 0.0;
		for (int j = 0; j < c; j++)
			yp[i] += A[i * c + j] * x[j];
	}
	end = omp_get_wtime();
	printf("Time for y = Ax parallel: %f sec.\n", end - start);

	bool result = compareVectors(y, yp, r, 0.0000001);
	if (result)
		printf("Vectors are equal. \n");
	else
		printf("Vectors are not equal. \n");

	delete[] A;
	delete[] x;
	delete[] y;
	delete[] yp;

	return 0;
}

bool compareVectors(double *y, double *yp, int n, double tol) {
	bool retval = true;
	for (int i = 0; i < n; i++)
		retval = retval && (fabs(y[i] - yp[i]) < tol);

	return retval;
}

