#include <iostream>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include <omp.h>

using namespace std;

void Odd_even_serial(int a[], int n);
void Odd_even_parallel(int a[], int n, int numThreads);
void Odd_even_parallel2(int a[], int n, int numThreads);
bool Sorted(int a[], int n);
template<class T> void Swap(T &a, T &b);

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

	int *A = new int[n];
	int *B = new int[n];
	int *C = new int[n];

	// populate
	for (int i = 0; i < n; i++)
		A[i] = B[i] = C[i] = rand();

	start = omp_get_wtime();
	Odd_even_serial(A, n);
	end = omp_get_wtime();

	printf("Time to sort serial: %f sec.\n", end - start);
	printf("Sorted Test: %d \n", Sorted(A, n));

	printf("Number of threads: %d \n", numThreads);

	start = omp_get_wtime();
	Odd_even_parallel(B, n, numThreads);
	end = omp_get_wtime();

	printf("Time to sort parallel: %f sec.\n", end - start);
	printf("Sorted Test: %d \n", Sorted(B, n));

	start = omp_get_wtime();
	Odd_even_parallel2(C, n, numThreads);
	end = omp_get_wtime();

	printf("Time to sort parallel parallel for: %f sec.\n", end - start);
	printf("Sorted Test: %d \n", Sorted(C, n));

	delete[] A;
	delete[] B;
	delete[] C;

	return 0;
}

void Odd_even_serial(int a[], int n) {
	int phase, i;

	for (phase = 0; phase < n; phase++) {
		if (phase % 2 == 0)
			for (i = 1; i < n; i += 2) {
				if (a[i - 1] > a[i])
					Swap(a[i], a[i - 1]);
			}
		else
			for (i = 1; i < n - 1; i += 2) {
				if (a[i] > a[i + 1])
					Swap(a[i], a[i + 1]);
			}
	}
}

void Odd_even_parallel(int a[], int n, int numThreads) {
	int phase, i;

# pragma omp parallel num_threads(numThreads) default(none) shared(a, n) private(i, phase)
	for (phase = 0; phase < n; phase++) {
		if (phase % 2 == 0)
# pragma omp for
			for (i = 1; i < n; i += 2) {
				if (a[i - 1] > a[i])
					Swap(a[i], a[i - 1]);
			}
		else
# pragma omp for
			for (i = 1; i < n - 1; i += 2) {
				if (a[i] > a[i + 1])
					Swap(a[i], a[i + 1]);
			}
	}
}

void Odd_even_parallel2(int a[], int n, int numThreads) {
	int phase, i;

	for (phase = 0; phase < n; phase++) {
		if (phase % 2 == 0)
# pragma omp parallel for num_threads(numThreads) default(none) shared(a, n) private(i)
			for (i = 1; i < n; i += 2) {
				if (a[i - 1] > a[i])
					Swap(a[i], a[i - 1]);
			}
		else
# pragma omp parallel for num_threads(numThreads) default(none) shared(a, n) private(i)
			for (i = 1; i < n - 1; i += 2) {
				if (a[i] > a[i + 1])
					Swap(a[i], a[i + 1]);
			}
	}
}

bool Sorted(int a[], int n) {
	int i = 1;
	while (i < n && a[i] >= a[i - 1])
		i++;
	return i >= n;
}

template<class T>
void Swap(T &a, T &b) {
	T temp = a;
	a = b;
	b = temp;
}
