#include <cmath>
#include <mpi.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char *argv[]) {
	int commsz, rank;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &commsz);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int rankval = rank;
	int mes = 0;

	MPI_Sendrecv_replace(&rankval, 1, MPI_DOUBLE, (rank + 1) % commsz, 0,
			(rank - 1 + commsz) % commsz, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

	cout << "Process: " << rank << "  Received: " << rankval << endl;

	MPI_Finalize();

	return 0;
}
