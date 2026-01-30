#include <iostream>
#include <sstream>
#include <cmath>

#include <omp.h>

using namespace std;

int main(int argc, char *argv[]) {
	int numThreads, tid = -1;

	cout << "Input number of threads: ";
	cin >> numThreads;

	if (numThreads <= 0) {
#pragma omp parallel
		numThreads = omp_get_num_threads();
	}

	printf("tid before parallel: %d \n", tid);

#pragma omp parallel private(tid) num_threads(numThreads)
	{
		int oldtid = tid;
		tid = omp_get_thread_num();
		printf(
				"tid inside parallel region: was %d and now %d at %#0x and %#0x \n",
				oldtid, tid, &oldtid, &tid);
	}

	printf("tid after parallel: %d \n", tid);
	printf("---------------------------\n");
	printf("tid before parallel: %d \n", tid);

#pragma omp parallel num_threads(numThreads)
	{
		tid = omp_get_thread_num();
		printf("tid inside parallel region: %d \n", tid);
	}

	printf("tid after parallel: %d \n", tid);
	printf("---------------------------\n");
	printf("tid before parallel: %d \n", tid);

#pragma omp parallel shared(tid) num_threads(numThreads)
	{
		tid = omp_get_thread_num();
		printf("tid inside parallel region: %d \n", tid);
	}

	printf("tid after parallel: %d \n", tid);
	printf("---------------------------\n");

	tid = 123;
	printf("tid before parallel: %d \n", tid);

#pragma omp parallel firstprivate(tid) num_threads(numThreads)
	{
		int oldtid = tid;
		tid = omp_get_thread_num();
		printf("tid inside parallel region: was %d and now %d \n", oldtid, tid);
	}

	printf("tid after parallel: %d \n", tid);
	printf("---------------------------\n");
	printf("tid before parallel: %d \n", tid);

#pragma omp parallel default(none) private(tid) shared(numThreads) num_threads(numThreads)
	{
		int oldtid = tid;
		tid = omp_get_thread_num();
		printf(
				"tid inside parallel region: was %d and now %d total threads %d\n",
				oldtid, tid, numThreads);
	}

	printf("tid after parallel: %d \n", tid);
	printf("---------------------------\n");

	tid = 123;
	printf("tid before parallel: %d \n", tid);

#pragma omp parallel for lastprivate(tid) num_threads(numThreads)
	for (int i = 0; i < 25; i++) {
		tid = omp_get_thread_num();
		printf("Thread %d iteration %d \n", tid, i);
	}

	printf("tid after parallel: %d \n", tid);
	printf("---------------------------\n");

	return 0;
}
