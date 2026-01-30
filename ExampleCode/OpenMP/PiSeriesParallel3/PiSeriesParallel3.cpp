#include <iostream>
#include <sstream>
#include <cmath>

#include <omp.h>

using namespace std;

int main(int argc, char *argv[]) {
	int numThreads, n;
	double factor = 1, sum = 0;
	double piapprox = 0;
	const double PI25DT = 3.141592653589793238462643;

	cout << "Input n: ";
	cin >> n;

	cout << "Input number of threads: ";
	cin >> numThreads;

	if (numThreads <= 0) {
#pragma omp parallel
		numThreads = omp_get_num_threads();
	}

	for (int k = 0; k < n; k++) {
		sum += factor / (2 * k + 1);
		factor *= -1;
	}
	piapprox = 4 * sum;

	printf("Sequential pi is approximately %.16f, Error is %.16f\n", piapprox,
			fabs(piapprox - PI25DT));

	double parapiapprox = 0;
	sum = 0;
#pragma omp parallel for num_threads(numThreads) reduction(+: sum) private(factor)
	for (int k = 0; k < n; k++) {
		factor = (k % 2 == 0) ? 1 : -1;
		sum += factor / (2 * k + 1);
	}
	parapiapprox = 4 * sum;

	printf("Parallel pi is approximately %.16f, Error is %.16f\n", parapiapprox,
			fabs(parapiapprox - PI25DT));

	return 0;
}
