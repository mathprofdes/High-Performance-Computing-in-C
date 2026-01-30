#include <iostream>
#include <sstream>
#include <cmath>
#include <vector>

#include <omp.h>

using namespace std;

int main(int argc, char *argv[]) {
	int numThreads = 10;
	vector<int> A(10);
	//int A[10];
	for (int i = 0; i < 10; i++)
		A[i] = -3;

// Program crash in parallel region.
//	printf("Test #1 \n");
//	printf("Before Parallel \n");
//	for (int i = 0; i < 10; i++) {
//		printf("A[%d] = %d \n", i, A[i]);
//	}
//
//	printf("In Parallel \n");
//
//#pragma omp parallel private(A) num_threads(numThreads)
//	{
//		int tid = omp_get_thread_num();
//		int oldval = A[tid];
//		A[tid] = 2 * tid;
//		printf("Old A[%d] = %d  and  New A[%d] = %d \n", tid, oldval, tid,
//				A[tid]);
//	}
//
//	printf("After Parallel \n");
//
//	for (int i = 0; i < 10; i++) {
//		printf("A[%d] = %d \n", i, A[i]);
//	}

	printf("\n\n");
	printf("Test #2 \n");
	printf("Before Parallel \n");
	for (int i = 0; i < 10; i++) {
		printf("A[%d] = %d \n", i, A[i]);
	}

	printf("In Parallel \n");

#pragma omp parallel firstprivate(A) num_threads(numThreads)
	{
		int tid = omp_get_thread_num();
		int oldval = A[tid];
		A[tid] = 2 * tid;
		printf("Old A[%d] = %d  and  New A[%d] = %d \n", tid, oldval, tid,
				A[tid]);
	}

	printf("After Parallel \n");

	for (int i = 0; i < 10; i++) {
		printf("A[%d] = %d \n", i, A[i]);
	}

	printf("\n\n");
	printf("Test #3 \n");
	printf("Before Parallel \n");
	for (int i = 0; i < 10; i++) {
		printf("A[%d] = %d \n", i, A[i]);
	}

	printf("In Parallel \n");

#pragma omp parallel shared(A) num_threads(numThreads)
	{
		int tid = omp_get_thread_num();
		int oldval = A[tid];
		A[tid] = 3 * tid;
		printf("Old A[%d] = %d  and  New A[%d] = %d \n", tid, oldval, tid,
				A[tid]);
	}

	printf("After Parallel \n");

	for (int i = 0; i < 10; i++) {
		printf("A[%d] = %d \n", i, A[i]);
	}

	return 0;
}
