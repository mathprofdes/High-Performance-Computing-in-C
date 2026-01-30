#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <omp.h>

using namespace std;

void paraFct();

int main() {
	//omp_set_max_active_levels(2);

#pragma omp parallel num_threads(5)
	{
		int rank = omp_get_thread_num();

		if (rank == 0)
			printf("Main Threads = %d \n", omp_get_num_threads());

		paraFct();
	}

	return 0;
}

void paraFct(){
#pragma omp parallel num_threads(7)
	{
		int rank = omp_get_thread_num();

		if (rank == 0)
			printf("Function Threads = %d \n", omp_get_num_threads());
	}
}
