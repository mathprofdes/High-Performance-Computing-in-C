#include <math.h> 
#include <mpi.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
	int commsz, rank, n = 5;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &commsz);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	double *source, *target;
	source = new double[n];
	target = new double[n];

	for (int i = 0; i < n; i++)
		source[i] = i + .5;

	MPI_Datatype newtype;
	MPI_Type_contiguous(n, MPI_DOUBLE, &newtype);
	MPI_Type_commit(&newtype);

	if (rank == 0) {
		for (int i = 1; i < commsz; i++)
			MPI_Send(source, 1, newtype, i, 0, MPI_COMM_WORLD);
	} else if (rank != 0) {
		MPI_Status recv_status;
		int recv_count;
		MPI_Recv(target, 1, newtype, 0, 0, MPI_COMM_WORLD, &recv_status);
		MPI_Get_count(&recv_status, MPI_DOUBLE, &recv_count);
		printf("Process  %d received %d\n", rank, recv_count);
	}

	//  Check
	if (rank != 0) {
		for (int i = 0; i < n; i++)
			if (target[i] != source[i])
				printf("Bad send/receive process %d index %d values %e != %e\n",
						rank, i, target[i], source[i]);
	}

	if (rank == 0)
		printf("Finished\n");

	MPI_Type_free(&newtype);

	MPI_Finalize();
	return 0;
}

