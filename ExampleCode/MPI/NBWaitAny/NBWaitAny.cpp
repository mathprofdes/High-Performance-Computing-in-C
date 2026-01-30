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

	if (rank == commsz - 1) {
		int *recv_buffer = new int[commsz - 1];
		MPI_Request *request = new MPI_Request[commsz - 1];
		MPI_Status status;

		for (int p = 0; p < commsz - 1; p++) {
			MPI_Irecv(recv_buffer + p, 1, MPI_INT, p, 0, MPI_COMM_WORLD,
					request + p);
		}

		for (int p = 0; p < commsz - 1; p++) {
			int index;
			MPI_Waitany(commsz - 1, request, &index, &status);
			if (index != status.MPI_SOURCE)
				printf("Mismatch index %d vs source %d\n", index,
						status.MPI_SOURCE);
			printf("Message from %d: %d\n", index, recv_buffer[index]);
		}
		delete[] recv_buffer;
		delete[] request;
	} else {
		MPI_Send(&rank, 1, MPI_INT, commsz - 1, 0, MPI_COMM_WORLD);
	}

	MPI_Finalize();

	return 0;
}
