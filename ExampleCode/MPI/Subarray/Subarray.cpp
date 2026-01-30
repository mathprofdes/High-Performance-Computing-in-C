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

	int count = 4;
	double *source, *target;
	int sizes[2] = { 4, 4 }, subsizes[2] = { 2, 2 }, starts[2] = { 1, 1 };
	source = new double[sizes[0] * sizes[1]];
	target = new double[subsizes[0] * subsizes[1]];

	for (int i = 0; i < sizes[0] * sizes[1]; i++)
		source[i] = i + .5;

	MPI_Datatype subarraytype;
	if (rank == 0) {
		for (int i = 0; i < sizes[0]; i++) {
			for (int j = 0; j < sizes[1]; j++)
				cout << source[i * sizes[1] + j] << " ";
			cout << endl;
		}

		MPI_Type_create_subarray(2, sizes, subsizes, starts, MPI_ORDER_C,
		MPI_DOUBLE, &subarraytype);
		MPI_Type_commit(&subarraytype);
		MPI_Send(source, 1, subarraytype, 1, 0, MPI_COMM_WORLD);
	} else if (rank == 1) {
		MPI_Status recv_status;
		int recv_count;
		MPI_Recv(target, count, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &recv_status);
		MPI_Get_count(&recv_status, MPI_DOUBLE, &recv_count);

		for (int i = 0; i < subsizes[0]; i++) {
			for (int j = 0; j < subsizes[1]; j++)
				cout << target[i * subsizes[1] + j] << " ";
			cout << endl;
		}
	}

	if (rank == 0) {
		MPI_Aint true_lb, true_extent;
		// Get starting offset and extent in bytes.
		MPI_Type_get_true_extent(subarraytype, &true_lb, &true_extent);
		printf("Lower Bound = %ld, Extent = %ld\n", true_lb, true_extent);
		// Calculate starting offset and extent in bytes.
		MPI_Aint comp_lb = (starts[0] * sizes[1] + starts[1]) * sizeof(double);
		MPI_Aint comp_extent = ((starts[0] + subsizes[0] - 1) * sizes[1]
				+ starts[1] + subsizes[1]) * sizeof(double) - comp_lb;
		printf("Computing Lower Bound = %ld Extent = %ld\n", comp_lb,
				comp_extent);
		MPI_Type_free(&subarraytype);
	}

	if (rank == 1) {
		printf("Data Received:");
		for (int i = 0; i < count; i++)
			printf(" %6.3f", target[i]);
		printf("\n");
		int icnt = 0;
		// Check data transfer.
		for (int i = starts[0]; i < starts[0] + subsizes[0]; i++) {
			for (int j = starts[1]; j < starts[1] + subsizes[1]; j++) {
				printf("(%d, %d)\n", i, j);
				int isrc = i * sizes[1] + j;
				if (source[isrc] != target[icnt])
					printf("Target location error (%d, %d)->%d %e s/b %e\n", i,
							j, icnt, target[icnt], source[isrc]);
				icnt++;
			}
		}
	}

	if (rank == 0)
		printf("Finished\n");

	MPI_Finalize();

	return 0;
}
