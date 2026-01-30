#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <mpi.h>

using namespace std;

struct Data {
	char c;
	double x[2];
	int i;
};

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

	Data obj;

	if (rank == 0) {
		obj.c = 'x';
		obj.x[0] = 2.7;
		obj.x[1] = 1.5;
		obj.i = 37;
	}

	MPI_Datatype structtype;
	int structlen = 3;
	int blocks[structlen];
	MPI_Datatype types[structlen];
	MPI_Aint displacements[structlen];

	MPI_Aint baseaddr;
	MPI_Aint caddr;
	MPI_Aint xaddr;
	MPI_Aint iaddr;
	MPI_Get_address(&obj, &baseaddr);
	MPI_Get_address(&obj.c, &caddr);
	MPI_Get_address(&obj.x, &xaddr);
	MPI_Get_address(&obj.i, &iaddr);

	blocks[0] = 1;
	types[0] = MPI_CHAR;
	displacements[0] = caddr - baseaddr;

	blocks[1] = 2;
	types[1] = MPI_DOUBLE;
	displacements[1] = xaddr - baseaddr;

	blocks[2] = 1;
	types[2] = MPI_INT;
	displacements[2] = iaddr - baseaddr;

	MPI_Type_create_struct(structlen, blocks, displacements, types,
			&structtype);
	MPI_Type_commit(&structtype);

	if (rank == 0) {
		MPI_Send(&obj, 1, structtype, 1, 0, MPI_COMM_WORLD);
	} else if (rank == 1) {
		cout << obj.c << " " << obj.x[0] << " " << obj.x[1] << " " << obj.i
				<< endl;

		MPI_Recv(&obj, 1, structtype, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		cout << obj.c << " " << obj.x[0] << " " << obj.x[1] << " " << obj.i
				<< endl;
	}
	MPI_Type_free(&structtype);

	if (rank == 0)
		printf("Finished\n");

	MPI_Finalize();

	return 0;
}
