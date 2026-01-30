#include <math.h> 
#include <mpi.h>
#include <iostream>

using namespace std;

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
		// Get partial sums, accumulate, and print.
		for (int dest = 1; dest < commsz; dest++) {
			MPI_Recv(&local_piapprox, 1, MPI_DOUBLE, dest, 0, MPI_COMM_WORLD,
					&status);

			piapprox += local_piapprox;
		}

		printf("Parallel pi is approximately %.16f, Error is %.16f\n", piapprox,
				fabs(piapprox - PI25DT));

	} else {
		// Calculate partial approximation.
		double h = 1.0 / (double) n;

		// Adjust for not using process 0.
		int numprocs = commsz - 1;
		int pos = rank - 1;

		int start = pos * (n / numprocs);
		int end = (pos + 1) * (n / numprocs);
		if (pos == numprocs - 1)
			end = n;

		for (int i = start; i < end; i++) {
			double x = h * ((double) i + 0.5);
			piapprox += (4.0 / (1.0 + x * x));
		}

		piapprox = h * piapprox;

		// Send result to process 0.
		MPI_Send(&piapprox, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
	}

	MPI_Finalize();
	return 0;
}

