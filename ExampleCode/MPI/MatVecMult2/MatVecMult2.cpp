#include <cmath>
#include <mpi.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

bool vecsEqual(double x[], double y[], int sz, double tol = 0.000001);

int main(int argc, char *argv[]) {
	int commsz, rank, rows, cols;
	double starttime, endtime;
	double *A = NULL, *localA = NULL, *y = NULL, *yp = NULL, *lyp = NULL, *x =
	NULL;

	/* Start up MPI */
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &commsz);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	// Set the seed of the RNG.  Use different seeds per process.
	srand(time(0) + rank);

	if (rank == 0) {
		// Note that for this program we want the number of rows to evenly divide
		// the number of processes.
		cout << "Input m, number of matrix rows will be m*commsz: ";
		cin >> rows;
		cout << "Input n, number of matrix columns: ";
		cin >> cols;
		rows = rows * commsz;
	}

	// Send sizes of matrix and x vector to all processes.
	MPI_Bcast(&rows, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&cols, 1, MPI_INT, 0, MPI_COMM_WORLD);
	A = new double[rows * cols];
	y = new double[rows];
	yp = new double[rows];
	x = new double[cols];

	if (rank == 0) {
		//  Populate A and x with random numbers in [0, 1).
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				A[i * cols + j] = 1.0 * rand() / RAND_MAX;

		for (int j = 0; j < cols; j++)
			x[j] = 1.0 * rand() / RAND_MAX;

		starttime = MPI_Wtime();
		// Serial multiplication.
		for (int i = 0; i < rows; i++) {
			y[i] = 0;
			for (int j = 0; j < cols; j++)
				y[i] += A[i * cols + j] * x[j];
		}
		endtime = MPI_Wtime();
		printf("Serial Time %.6f sec.\n", endtime - starttime);

		// Start time for parallel run.
		starttime = MPI_Wtime();
	}

	// Send x vector to all processes.
	MPI_Bcast(x, cols, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	// Allocate local data.
	localA = new double[cols * rows / commsz];
	lyp = new double[rows / commsz];

	// Scatter the rows of A to respective process.
	MPI_Scatter(A, cols * rows / commsz, MPI_DOUBLE, localA,
			cols * rows / commsz, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	for (int i = 0; i < rows / commsz; i++) {
		lyp[i] = 0;
		for (int j = 0; j < cols; j++)
			lyp[i] += localA[i * cols + j] * x[j];
	}

	// Gather back local y values into the y-parallel (yp) vector on process 0.
	MPI_Gather(lyp, rows / commsz, MPI_DOUBLE, yp, rows / commsz, MPI_DOUBLE, 0,
	MPI_COMM_WORLD);

	if (rank == 0) {
		endtime = MPI_Wtime();
		printf("Parallel Time %.6f sec.\n", endtime - starttime);
		if (vecsEqual(y, yp, rows))
			cout << "Vectors are equal." << "\n";
		else
			cout << "Vectors are not equal." << "\n";
	}

	delete[] A;
	delete[] localA;
	delete[] x;
	delete[] y;
	delete[] yp;
	delete[] lyp;
	MPI_Finalize();

	return 0;
}

bool vecsEqual(double x[], double y[], int sz, double tol) {
	for (int i = 0; i < sz; i++)
		if (fabs(x[i] - y[i]) > tol)
			return false;

	return true;
}

