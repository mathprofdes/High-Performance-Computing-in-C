#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <omp.h>

using namespace std;

int fib(int n, int *fibarr);
int fibTask(int n, int *fibarr);
int fibTaskShared(int n, int *fibarr);
int fibTaskSharedBound(int n, int *fibarr);

int main() {
	int numThreads, n;
	double start, end;

	cout << "Input the max fib number: ";
	cin >> n;

	cout << "Input number of threads: ";
	cin >> numThreads;

	if (numThreads <= 0) {
#pragma omp parallel
		numThreads = omp_get_num_threads();
	}

	int *fiblist = new int[n+1];
	int *fiblistparatask = new int[n+1];
	int *fiblistparataskshared = new int[n+1];
	int *fiblistparatasksharedbound = new int[n+1];

	fiblist[0] = fiblist[1] = 1;
	start = omp_get_wtime();
	int result = fib(n, fiblist);
	end = omp_get_wtime();

	cout << "Fib number: " << result << endl;
	cout << "Fib list: ";
	for (int i = 0; i <= n; i++)
		cout << fiblist[i] << " ";
	printf("\nTime for fib serial: %f sec.\n", end - start);

	cout << "\n\n";

	fiblistparatask[0] = fiblistparatask[1] = 1;
	start = omp_get_wtime();
	result = fibTask(n, fiblistparatask);
	end = omp_get_wtime();

	cout << "Fib number (Task): " << result << endl;
	cout << "Fib list (Task): ";
	for (int i = 0; i <= n; i++)
		cout << fiblistparatask[i] << " ";
	printf("\nTime for fib parallel broken: %f sec.\n", end - start);

	cout << "\n\n";

	fiblistparataskshared[0] = fiblistparataskshared[1] = 1;
	start = omp_get_wtime();
	result = fibTaskShared(n, fiblistparataskshared);
	end = omp_get_wtime();

	cout << "Fib number (Task shared): " << result << endl;
	cout << "Fib list (Task shared): ";
	for (int i = 0; i <= n; i++)
		cout << fiblistparataskshared[i] << " ";
	printf("\nTime for fib parallel: %f sec.\n", end - start);

	cout << "\n\n";

	fiblistparatasksharedbound[0] = fiblistparatasksharedbound[1] = 1;
	start = omp_get_wtime();
	result = fibTaskSharedBound(n, fiblistparatasksharedbound);
	end = omp_get_wtime();

	cout << "Fib number (Task shared): " << result << endl;
	cout << "Fib list (Task shared): ";
	for (int i = 0; i <= n; i++)
		cout << fiblistparatasksharedbound[i] << " ";
	printf("\nTime for fib parallel: %f sec.\n", end - start);

	delete[] fiblist;
	delete[] fiblistparatask;
	delete[] fiblistparataskshared;
	delete[] fiblistparatasksharedbound;
	return 0;
}

int fib(int n, int *fibarr) {
	int i = 0;
	int j = 0;

	if (n <= 1){
		return 1;
	}

	i = fib(n - 1, fibarr);
	j = fib(n - 2, fibarr);
	fibarr[n] = i + j;

	return fibarr[n];
}

int fibTask(int n, int *fibarr) {
	int i = 0;
	int j = 0;

	if (n <= 1){
		return 1;
	}

#pragma omp task
	i = fibTask(n - 1, fibarr);
#pragma omp task
	j = fibTask(n - 2, fibarr);

	fibarr[n] = i + j;

	return fibarr[n];
}

int fibTaskShared(int n, int *fibarr) {
	int i = 0;
	int j = 0;

	if (n <= 1){
		return 1;
	}

#pragma omp task shared(i)
	i = fibTaskShared(n - 1, fibarr);
#pragma omp task shared(j)
	j = fibTaskShared(n - 2, fibarr);

//#pragma omp taskwait
	fibarr[n] = i + j;

	return fibarr[n];
}

int fibTaskSharedBound(int n, int *fibarr) {
	int i = 0;
	int j = 0;

	if (n <= 1){
		return 1;
	}

#pragma omp task shared(i) if (n > 20)
	i = fibTaskSharedBound(n - 1, fibarr);
#pragma omp task shared(j) if (n > 20)
	j = fibTaskSharedBound(n - 2, fibarr);

#pragma omp taskwait
	fibarr[n] = i + j;

	return fibarr[n];
}
