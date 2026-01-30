#include <math.h> 
#include <mpi.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char *argv[]) {
	int commsz, rank, n;
	double *A = NULL, *localA = NULL;
	double mu, sigma, localmu, localsum, sum;

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

	// Scatter array to all processes.  Note that if the process rank is not 0
	// then A is NULL,
	MPI_Scatter(A, n / commsz, MPI_DOUBLE, localA, n / commsz, MPI_DOUBLE, 0,
			MPI_COMM_WORLD);

	localmu = 0;
	int start = 0;
	int end = n / commsz;
	for (int i = start; i < end; i++)
		localmu += localA[i];
	localmu = localmu / n;

	MPI_Allreduce(&localmu, &mu, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

	// Test all reduce.
	cout << rank << ": " << mu << endl;

	localsum = 0;
	for (int i = start; i < end; i++)
		localsum += (localA[i] - mu) * (localA[i] - mu);

	MPI_Reduce(&localsum, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	if (rank == 0) {
		sigma = sqrt(1.0 / (n - 1) * sum);
		cout << "Parallel Std. Dev.: " << sigma << "\n";
		// Note that A only exists on process 0.
		delete[] A;
	}

	MPI_Finalize();

	return 0;
}
