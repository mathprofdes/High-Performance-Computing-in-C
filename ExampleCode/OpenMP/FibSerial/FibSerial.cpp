#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

int main(int argc, char *argv[]) {
	int n;

	cout << "Input n: ";
	cin >> n;

	long *fib = new long[n];

	fib[0] = fib[1] = 1;
	for (int i = 2; i < n; i++)
		fib[i] = fib[i - 1] + fib[i - 2];

	for (int i = 0; i < n; i++)
		cout << fib[i] << " ";
	cout << endl;

	delete[] fib;

	return 0;
}
