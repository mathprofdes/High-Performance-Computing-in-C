/*
 * g++ -fopenmp -g -Wall HelloOMPcpp.cpp
 */

#include <iostream>
#include <sstream>

#include <omp.h>

using namespace std;

int main(int argc, char *argv[]) {

	int numThreads, tid;

#pragma omp parallel private(numThreads, tid)
	{
		tid = omp_get_thread_num();
		cout << "Hello World from thread number " << tid << endl;

		if (tid == 0) {
			numThreads = omp_get_num_threads();
			cout << "Number of threads is " << numThreads << endl;
		}
	}

	cout << "\n---------------------\n";
	stringstream ss2;
	numThreads = omp_get_num_threads();
	ss2 << "Number of threads is " << numThreads;
	cout << ss2.str();
	cout << "\n---------------------\n\n";

#pragma omp parallel private(numThreads, tid)
	{
		stringstream ss;
		tid = omp_get_thread_num();
		ss << "Hello World from thread number " << tid << endl;
		cout << ss.str();

		if (tid == 0) {
			numThreads = omp_get_num_threads();
			ss.str("");
			ss << "Number of threads is " << numThreads << endl;
			cout << ss.str();
		}
	}

	return 0;
}
