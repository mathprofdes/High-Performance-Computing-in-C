#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <mpi.h>

using namespace std;

struct Data {
	char c[100];
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

	Data obj[10];
//	Data *obj = new Data[10];

	if (rank == 0) {
		for (int i = 0; i < 10; i++) {
			strcpy(obj[i].c, "  - string.");
			obj[i].c[0] = 'A' + i;
			obj[i].x[0] = 2.7 + 1.5 * i;
			obj[i].x[1] = 1.5 + 2.75 * i;
			obj[i].i = 10 + i;
		}
	}

	// Just to show garbage in the obj array at the start.
	if (rank == 1) {
		for (int i = 0; i < 10; i++)
			cout << "Process " << rank << " --- " << obj[i].c << " "
					<< obj[i].x[0] << " " << obj[i].x[1] << " " << obj[i].i
					<< endl;
	}

	MPI_Barrier(MPI_COMM_WORLD);

	MPI_Datatype structtype;
	int structlen = 3;
	int blocks[structlen];
	MPI_Datatype types[structlen];
	MPI_Aint displacements[structlen];

	MPI_Aint baseaddr;
	MPI_Aint caddr;
	MPI_Aint xaddr;
	MPI_Aint iaddr;
	MPI_Get_address(&obj[0], &baseaddr);
	MPI_Get_address(&obj[0].c, &caddr);
	MPI_Get_address(&obj[0].x, &xaddr);
	MPI_Get_address(&obj[0].i, &iaddr);

	blocks[0] = 100;
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

	MPI_Bcast(obj, 10, structtype, 0, MPI_COMM_WORLD);

	for (int i = 0; i < 10; i++)
		cout << "Process " << rank << " --- " << obj[i].c << " " << obj[i].x[0]
				<< " " << obj[i].x[1] << " " << obj[i].i << endl;

	MPI_Type_free(&structtype);

	if (rank == 0)
		printf("Finished\n");

//	delete[] obj;

	MPI_Finalize();

	return 0;
}
