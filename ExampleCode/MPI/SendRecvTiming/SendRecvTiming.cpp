#include <cmath>
#include <mpi.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char *argv[]) {
	int commsz, rank;
	double starttime, endtime;

	/* Start up MPI */
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &commsz);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int sz = 100000;
	double A[sz];

	if (rank == 0)
		starttime = MPI_Wtime();

	if (rank == 0)
		for (int i = 0; i < sz; i++)
			for (int j = 1; j < commsz; j++)
				MPI_Send(&A[i], 1, MPI_DOUBLE, j, 0, MPI_COMM_WORLD);
	else
		for (int i = 0; i < sz; i++)
			MPI_Recv(&A[i], 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, NULL);

	if (rank == 0) {
		endtime = MPI_Wtime();
		printf("One element at a time - Time %.6f sec.\n", endtime - starttime);
	}

	// Sync processes.
	MPI_Barrier(MPI_COMM_WORLD);

	if (rank == 0)
		starttime = MPI_Wtime();

	if (rank == 0)
		for (int j = 1; j < commsz; j++)
			MPI_Send(A, sz, MPI_DOUBLE, j, 0, MPI_COMM_WORLD);
	else
		MPI_Recv(A, sz, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, NULL);

	if (rank == 0) {
		endtime = MPI_Wtime();
		printf("Entire array at once - Time %.6f sec.\n", endtime - starttime);
	}

	MPI_Finalize();
	return 0;
}
