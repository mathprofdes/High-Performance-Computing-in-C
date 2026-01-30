#include <math.h> 
#include <mpi.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char *argv[]) {
	int commsz, rank, n;
	double *A, *AllVals;

	/* Start up MPI */
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &commsz);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	// Set the seed of the RNG.  Use different seeds per process.
	srand(time(0) + rank);

	if (rank == 0) {
		cout << "Input number of array entries: ";
		cin >> n;
	}

	// Broadcast array size to all processes.
	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

	A = new double[n];
	AllVals = new double[n];

	for (int i = 0; i < n; i++)
		A[i] = rand() % 10;

	cout << "Process: " << rank << ": ";
	for (int i = 0; i < n; i++)
		cout << A[i] << " ";
	cout << "\n";

	MPI_Scan(A, AllVals, n, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
//	MPI_Exscan(A, AllVals, n, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

	cout << "Sum: Process: " << rank << ": ";
	for (int i = 0; i < n; i++)
		cout << AllVals[i] << " ";
	cout << "\n";
	cout.flush();

	delete[] A;
	delete[] AllVals;

	MPI_Finalize();

	return 0;
}
