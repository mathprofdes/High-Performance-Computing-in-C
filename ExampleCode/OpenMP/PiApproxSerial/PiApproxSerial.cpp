#include <iostream>
#include <cmath>

using namespace std;

int main(int argc, char *argv[]) {
	int n;
	double piapprox = 0;
	const double PI25DT = 3.141592653589793238462643;

	cout << "Input number of rectangles: ";
	cin >> n;

	double h = 1.0 / (double) n;

	for (int i = 0; i < n; i++) {
		double x = h * ((double) i + 0.5);
		piapprox += (4.0 / (1.0 + x * x));
	}
	piapprox = h * piapprox;

	printf("Sequential pi is approximately %.16f, Error is %.16f\n", piapprox,
			fabs(piapprox - PI25DT));
}
