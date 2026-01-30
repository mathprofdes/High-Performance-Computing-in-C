#include <math.h> 
#include <mpi.h>
#include <iostream>

using namespace std;

double localApprox(int, int, int);

int main(int argc, char *argv[]) {
	int commsz, rank, n;
	double piapprox = 0, local_piapprox = 0;
	const double PI25DT = 3.141592653589793238462643;
	double starttime, endtime;

	/* Start up MPI */
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &commsz);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0) {
		cout << "Input number of rectangles: ";
		cin >> n;

		starttime = MPI_Wtime();
	}

	// Send data to all processes.
	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
	// Calculate the processor's portion of pi.
	local_piapprox = localApprox(n, rank, commsz);

	// Reduce the values to a final answer.
	MPI_Reduce(&local_piapprox, &piapprox, 1, MPI_DOUBLE, MPI_SUM, 0,
	MPI_COMM_WORLD);

	if (rank == 0) {
		endtime = MPI_Wtime();

		printf("Parallel pi is approximately %.16f, Error is %.16f\n", piapprox,
				fabs(piapprox - PI25DT));
		printf("Time %.6f sec.\n", endtime - starttime);
	}

	MPI_Finalize();
	return 0;
}

double localApprox(int n, int rank, int sz) {
	double h = 1.0 / (double) n;
	double piapprox = 0;

	int start = rank * (n / sz);
	int end = (rank + 1) * (n / sz);
	if (rank == sz - 1)
		end = n;

	for (int i = start; i < end; i++) {
		double x = h * ((double) i + 0.5);
		piapprox += (4.0 / (1.0 + x * x));
	}

	return h * piapprox;
}

