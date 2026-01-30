#include <iostream>
#include <sstream>

#include <omp.h>

using namespace std;

int main(int argc, char *argv[]) {

	int numThreads, tid;

// Local change in number of threads. Just for this team.
#pragma omp parallel private(numThreads, tid) num_threads(5)
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

	cout << "\n----------------\n\n";

// Back to the default.
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

	cout << "\n----------------\n\n";


	// Global change in number of threads.
	omp_set_num_threads(8);

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

	cout << "\n----------------\n\n";

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
