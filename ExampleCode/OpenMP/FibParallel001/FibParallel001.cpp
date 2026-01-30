#include <iostream>
#include <sstream>
#include <cmath>

#include <omp.h>

double area(double, int);

using namespace std;

int main(int argc, char *argv[]) {
	int numThreads, n;

	cout << "Input n: ";
	cin >> n;

	cout << "Input number of threads: ";
	cin >> numThreads;

	if (numThreads <= 0) {
#pragma omp parallel
		numThreads = omp_get_num_threads();
	}

	long *fib = new long[n];

	fib[0] = fib[1] = 1;

#pragma omp parallel for num_threads(numThreads)
	for (int i = 2; i < n; i++)
		fib[i] = fib[i - 1] + fib[i - 2];

	for (int i = 0; i < n; i++)
		cout << fib[i] << " ";
	cout << endl;

	delete[] fib;
	return 0;
}
