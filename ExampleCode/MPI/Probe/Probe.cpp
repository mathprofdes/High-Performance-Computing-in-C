#include <cmath>
#include <mpi.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char *argv[]) {
	int commsz, rank;

	/* Start up MPI */
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &commsz);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	// Set the seed of the RNG.  Use different seeds per process.
	srand(time(0) + rank);

	if (rank == 0) {
		MPI_Status status;
		MPI_Probe(1, 0, MPI_COMM_WORLD, &status);

		int count;
		MPI_Get_count(&status, MPI_DOUBLE, &count);
		double A[count];

		MPI_Recv(A, count, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD,
		MPI_STATUS_IGNORE);

		cout << "Receive size: " << count << endl;
		cout << "Receive data: ";
		for (int i = 0; i < count; i++)
			cout << A[i] << " ";
		cout << endl;
	} else if (rank == 1) {
		int sz = rand() % 50 + 10;
		double B[sz];

		for (int i = 0; i < sz; i++)
			B[i] = rand() % 10;

		cout << "Send size: " << sz << endl;
		cout << "Send data: ";
		for (int i = 0; i < sz; i++)
			cout << B[i] << " ";
		cout << endl;

		MPI_Send(B, sz, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
	}

	MPI_Finalize();

	return 0;
}
