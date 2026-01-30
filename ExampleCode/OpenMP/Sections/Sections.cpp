#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <omp.h>

using namespace std;

double f(double x);
double g(double x);

int main() {
	double y = 0;

#pragma omp parallel
#pragma omp sections
	{
#pragma omp section
		{
			int tid = omp_get_thread_num();
			printf("Rank = %d \n", tid);
		}
#pragma omp section
		{
			int tid = omp_get_thread_num();
			printf("Rank = %d \n", tid);
		}

#pragma omp section
		{
			int tid = omp_get_thread_num();
			printf("Rank = %d \n", tid);
		}
	}

	double x = 1000;
#pragma omp parallel reduction(+:y)
#pragma omp sections
	{
#pragma omp section
		{
			int tid = omp_get_thread_num();
			printf("Calculating f with thread = %d \n", tid);

			y += f(x);
		}
#pragma omp section
		{
			int tid = omp_get_thread_num();
			printf("Calculating g with thread = %d \n", tid);

			y += g(x);
		}
	}
	printf("y = %f \n", y);

	return 0;
}

double f(double x) {
	return x * x;
}

double g(double x) {
	return x * x * x;
}
