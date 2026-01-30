#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

int main(int argc, char *argv[]) {
	int n;
	double factor = 1, sum = 0;
	double piapprox = 0;
	const double PI25DT = 3.141592653589793238462643;

	cout << "Input n: ";
	cin >> n;

	for (int k = 0; k < n; k++){
		sum += factor/(2*k+1);
		factor *= -1;
	}
	piapprox = 4 * sum;

	printf("Sequential pi is approximately %.16f, Error is %.16f\n", piapprox,
			fabs(piapprox - PI25DT));

	return 0;
}
