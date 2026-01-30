#include <math.h> 
#include <mpi.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char *argv[]) {
	int commsz, rank, n;
	double *A = NULL, *localA = NULL;

	/* Start up MPI */
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &commsz);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	// Set the seed of the RNG.  Use different seeds per process.
	srand(time(0) + rank);

	if (rank == 0) {
		cout << "Input n, number of array entries will be n*commsz: ";
		cin >> n;
		n = n * commsz;
		A = new double[n];
	}

	// Send size of array to all processes.
	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
	localA = new double[n / commsz];

	// Populate array with random values, and print.
	if (rank == 0) {
		for (int i = 0; i < n; i++)
			A[i] = rand() % 10;

		cout << "Process: " << rank << ": ";
		for (int i = 0; i < n; i++)
			cout << A[i] << " ";
		cout << "\n";
	}

	// Scatter array to all processes.  Note that if the process rank is not 0
	// then A is NULL,
	MPI_Scatter(A, n / commsz, MPI_DOUBLE, localA, n / commsz, MPI_DOUBLE, 0,
	MPI_COMM_WORLD);

	for (int i = 0; i < n / commsz; i++)
		localA[i] = rank * localA[i];

	// Gather the local arrays into A.
	MPI_Gather(localA, n / commsz, MPI_DOUBLE, A, n / commsz, MPI_DOUBLE, 0,
	MPI_COMM_WORLD);

	if (rank == 0) {
		cout << "Process: " << rank << ": ";
		for (int i = 0; i < n; i++)
			cout << A[i] << " ";
		cout << "\n";
		delete[] A;
	}

	MPI_Finalize();

	return 0;
}
