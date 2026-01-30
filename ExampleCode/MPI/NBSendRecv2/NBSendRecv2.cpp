#include <math.h> 
#include <mpi.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char *argv[]) {
	int commsz, rank;

	/* Start up MPI */
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &commsz);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	// Set the seed of the RNG.  Use different seeds per process.
	srand(time(0) + rank);

	double *A = new double[100]();

	if (rank == 0) {
		for (int i = 0; i < 100; i++)
			A[i] = i;
	}

	MPI_Barrier(MPI_COMM_WORLD);

	if (rank == 0) {
		MPI_Request request;
		for (int p = 1; p < commsz; p++) {
			MPI_Isend(A, 100, MPI_DOUBLE, p, 0, MPI_COMM_WORLD, &request);
//			MPI_Send(&send, 1, MPI_DOUBLE, p, 0, MPI_COMM_WORLD);
		}

		for (int i = 0; i < 100; i++)
			A[i] = i + 1000;

	} else {
		MPI_Request request;
		MPI_Irecv(A, 100, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &request);

		// Process while the receive is finishing.
		printf("Rank %d: ", rank);
		for (int i = 0; i < 100; i++)
			cout << A[i] << " ";
		cout << endl;

		MPI_Wait(&request, MPI_STATUS_IGNORE);
	}

	MPI_Finalize();

	return 0;
}
