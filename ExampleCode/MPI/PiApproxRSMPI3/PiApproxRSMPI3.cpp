#include <math.h> 
#include <mpi.h>
#include <iostream>

using namespace std;

double localApprox(int, int, int);

int main(int argc, char *argv[]) {
	int commsz, rank, n;
	MPI_Status status;
	double piapprox = 0, local_piapprox = 0;
	const double PI25DT = 3.141592653589793238462643;

	/* Start up MPI */
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &commsz);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0) {
		cout << "Input number of rectangles: ";
		cin >> n;

		// Send n to processes.
		for (int dest = 1; dest < commsz; dest++) {
			MPI_Send(&n, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
		}
	} else {
		// Get n from process 0.
		MPI_Recv(&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
	}

	if (rank == 0) {
		piapprox = localApprox(n, rank, commsz);

		// Get partial sums, accumulate, and print.
		for (int dest = 1; dest < commsz; dest++) {
			MPI_Recv(&local_piapprox, 1, MPI_DOUBLE, MPI_ANY_SOURCE,
			MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

			piapprox += local_piapprox;
		}

		printf("Parallel pi is approximately %.16f, Error is %.16f\n", piapprox,
				fabs(piapprox - PI25DT));
	} else {
		piapprox = localApprox(n, rank, commsz);

		// Send result to process 0.
		MPI_Send(&piapprox, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
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

