#include <math.h> 
#include <mpi.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char *argv[]) {
	int commsz, rank, n;
	double *A;
	double mu, sigma, localmu, localsum, sum;
	MPI_Request request;
	MPI_Status status;

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

	// Send size of array to all processes.
	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
	A = new double[n];

	// Populate array with random values, and print.
	if (rank == 0) {
		for (int i = 0; i < n; i++)
			A[i] = rand() % 10;

//		cout << "Process: " << rank << ": ";
//		for (int i = 0; i < n; i++)
//			cout << A[i] << " ";
//		cout << "\n";
	}

	// Do serial calculation for comparison.
	if (rank == 0) {
		double ssum = 0, Smu, Ssigma;
		for (int i = 0; i < n; i++)
			ssum += A[i];
		Smu = ssum / n;

		ssum = 0;
		for (int i = 0; i < n; i++)
			ssum += (A[i] - Smu) * (A[i] - Smu);

		Ssigma = sqrt(1.0 / (n - 1) * ssum);
		cout << "Serial Std. Dev.: " << Ssigma << "\n";
	}

	// Broadcast (blocking) array to all processes.
	MPI_Bcast(A, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	localmu = 0;
	int start = rank * (n / commsz);
	int end = (rank + 1) * (n / commsz);
	if (rank == commsz - 1)
		end = n;
	for (int i = start; i < end; i++)
		localmu += A[i];
	localmu = localmu / n;

	// Non-blocking allreduce, not all processes may not get the value of mu.
	// Hence the subsequent calculation of the local sum will be off.
	MPI_Iallreduce(&localmu, &mu, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD, &request);

	// Test all reduce.
	cout << rank << ": " << mu << endl;

	localsum = 0;
	for (int i = start; i < end; i++)
		localsum += (A[i] - mu) * (A[i] - mu);

	MPI_Reduce(&localsum, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	if (rank == 0) {
		sigma = sqrt(1.0 / (n - 1) * sum);
		cout << "Parallel Std. Dev.: " << sigma << "\n";
	}

	// Sync. the allreduce.
	MPI_Wait(&request, &status);

	// Test all reduce.
	cout << rank << ": " << mu << endl;

	localsum = 0;
	for (int i = start; i < end; i++)
		localsum += (A[i] - mu) * (A[i] - mu);

	MPI_Reduce(&localsum, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	if (rank == 0) {
		sigma = sqrt(1.0 / (n - 1) * sum);
		cout << "After Wait:  Parallel Std. Dev.: " << sigma << "\n";
	}

	delete[] A;

	MPI_Finalize();

	return 0;
}
