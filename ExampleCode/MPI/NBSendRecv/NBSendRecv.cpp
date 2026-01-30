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

	if (rank == 0) {
		MPI_Request request;
		for (int p = 1; p < commsz; p++) {
			double send = p;
			MPI_Isend(&send, 1, MPI_DOUBLE, p, 0, MPI_COMM_WORLD, &request);
//			MPI_Send(&send, 1, MPI_DOUBLE, p, 0, MPI_COMM_WORLD);
		}
	} else {
		double recv = 0.;
		MPI_Request request;
		MPI_Irecv(&recv, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &request);

		// Process while the receive is finishing.
		printf("Rank %d between MPI_Irecv and MPI_Wait, buffer is %f \n", rank,
				recv);

		MPI_Wait(&request, MPI_STATUS_IGNORE);

		printf("Rank %d received %f \n", rank, recv);
	}

	MPI_Finalize();

	return 0;
}
