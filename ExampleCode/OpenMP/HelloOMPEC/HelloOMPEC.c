#include <stdio.h>
#include <stdlib.h>

#ifdef _OPENMP
#include <omp.h>
#endif

int main(int argc, char *argv[]) {

	int numThreads, tid;

#pragma omp parallel private(numThreads, tid)
	{
#ifdef _OPENMP
		tid = omp_get_thread_num();
#else
		tid = 0;
#endif
		printf("Hello World from thread number %d\n", tid);

		if (tid == 0) {
#ifdef _OPENMP
			numThreads = omp_get_num_threads();
#else
			numThreads = 1;
#endif
			printf("Number of threads is %d\n", numThreads);
		}
	}
	return 0;
}
