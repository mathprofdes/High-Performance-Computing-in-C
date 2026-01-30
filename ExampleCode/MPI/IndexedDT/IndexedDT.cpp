#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char **argv) {
	int commsz, rank;
	srand(time(0));

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &commsz);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (commsz < 2) {
		printf("This program needs at least two processes.\n");
		return -1;
	}

	double *source, *target;

	source = new double[25];
	target = new double[10];
	int disp[4] = { 2, 5, 10, 15 };
	int blocks[4] = { 1, 3, 4, 2 };

	for (int i = 0; i < 25; i++)
		source[i] = i + .5;

	MPI_Datatype vectype;
	if (rank == 0) {
		for (int i = 0; i < 25; i++)
			cout << source[i] << " ";
		cout << endl;

		MPI_Type_indexed(4, blocks, disp, MPI_DOUBLE, &vectype);
		MPI_Type_commit(&vectype);
		MPI_Send(source, 1, vectype, 1, 0, MPI_COMM_WORLD);
	} else if (rank == 1) {
		MPI_Status recv_status;
		int recv_count;
		MPI_Recv(target, 10, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &recv_status);
		MPI_Get_count(&recv_status, MPI_DOUBLE, &recv_count);
		printf("Process  %d received %d\n", rank, recv_count);
		for (int i = 0; i < 10; i++)
			cout << target[i] << " ";
		cout << endl;
	}

	if (rank == 0)
		printf("Finished\n");

	delete[] source;
	delete[] target;

	MPI_Finalize();

	return 0;
}
