#include <cmath>
#include <mpi.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

bool vecsEqual(double x[], double y[], int sz, double tol = 0.000001);

int main(int argc, char *argv[]) {
	int commsz, rank, rows, cols, padrows, n, iters;
	double starttime, endtime;
	double *A = NULL, *localA = NULL;
	double *y = NULL, *yp = NULL, *lyp = NULL, *x = NULL, *xp = NULL;
	MPI_Request request;
	MPI_Status status;

	/* Start up MPI */
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &commsz);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	// Set the seed of the RNG.  Use different seeds per process.
	srand(time(0) + rank);

	if (rank == 0) {
		// Note that for this program we allow any number of rows and pad.
		cout << "Input n, number of matrix rows and columns: ";
		cin >> n;
		cout << "Input the number of matrix vector multiplication iterations: ";
		cin >> iters;

		rows = n;
		cols = n;

		if (rows % commsz == 0)
			padrows = rows;
		else {
			int div = rows / commsz;
			padrows = (div + 1) * commsz;
		}
	}

	// Send sizes of matrix and x vector to all processes.
	MPI_Bcast(&rows, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&padrows, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&cols, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&iters, 1, MPI_INT, 0, MPI_COMM_WORLD);

	A = new double[padrows * cols];
	y = new double[padrows];
	yp = new double[padrows];
	x = new double[cols];
	xp = new double[cols];

	if (rank == 0) {
		// Populate A and x with random numbers in [0, 1).
		// Note not populating the padded rows.
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				A[i * cols + j] = 2.0 * rand() / RAND_MAX - 1.0;

		for (int j = 0; j < cols; j++) {
			x[j] = 2.0 * rand() / RAND_MAX - 1.0;
			xp[j] = x[j];
		}

		starttime = MPI_Wtime();
		// Serial multiplication. Ignoring the padded rows.

		for (int k = 0; k < iters; k++) {
			for (int i = 0; i < rows; i++) {
				y[i] = 0;
				for (int j = 0; j < cols; j++)
					y[i] += A[i * cols + j] * x[j];
			}
			// Copy y to x for the next iteration.
			for (int i = 0; i < cols; i++)
				x[i] = y[i];
		}
		endtime = MPI_Wtime();
		printf("Serial Time %.6f sec.\n", endtime - starttime);

		// Start time for parallel run.
		starttime = MPI_Wtime();
	}

	// Allocate local data.
	localA = new double[cols * padrows / commsz];
	lyp = new double[padrows / commsz];
	// Scatter the rows of A to respective process.
	MPI_Scatter(A, cols * padrows / commsz, MPI_DOUBLE, localA,
			cols * padrows / commsz, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	for (int k = 0; k < iters; k++) {
		// Send x vector to all processes.
		MPI_Bcast(xp, cols, MPI_DOUBLE, 0, MPI_COMM_WORLD);

		for (int i = 0; i < padrows / commsz; i++) {
			lyp[i] = 0;
			for (int j = 0; j < cols; j++)
				lyp[i] += localA[i * cols + j] * xp[j];
		}

		// Gather back local y values into the y-parallel (yp) vector on process 0.
		// Non-blocking form.
		MPI_Igather(lyp, padrows / commsz, MPI_DOUBLE, yp, padrows / commsz,
		MPI_DOUBLE, 0, MPI_COMM_WORLD, &request);

		// Do other work.

		// Sync. the gather.
		MPI_Wait(&request, &status);

		if (rank == 0) {
			// Copy y to x for the next iteration.
			for (int i = 0; i < cols; i++)
				xp[i] = yp[i];
		}
	}

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
	delete[] xp;
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

