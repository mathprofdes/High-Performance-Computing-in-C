#include <math.h> 
#include <mpi.h>
#include <iostream>
#include <sstream>

using namespace std;

int main(int argc, char *argv[]) {
	int commsz, rank, n = 5;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &commsz);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	double *data;
	data = new double[n];

	for (int i = 0; i < n; i++)
		data[i] = i + .5;

	MPI_Datatype newtype;
	MPI_Type_contiguous(n, MPI_DOUBLE, &newtype);
	MPI_Type_commit(&newtype);

	MPI_Bcast(data, 1, newtype, 0, MPI_COMM_WORLD);

	// Output the received data.
	stringstream ss;
	ss << "Process " << rank << ": ";
	for (int i = 0; i < n; i++)
		ss << data[i] << " ";
	ss << endl;

	cout << ss.str();

	if (rank == 0)
		printf("Finished\n");

	MPI_Type_free(&newtype);

	MPI_Finalize();
	return 0;
}

