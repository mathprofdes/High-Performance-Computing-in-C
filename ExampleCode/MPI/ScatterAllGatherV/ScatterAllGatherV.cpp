#include <cmath>
#include <mpi.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

bool vecsEqual(double x[], double y[], int sz, double tol = 0.000001);

int main(int argc, char *argv[]) {
	int commsz, rank, rows, cols, n, iters, sendsize, lastsendsize, bufentries;
	double starttime, endtime;
	double *A = NULL, *localA = NULL;
	double *y = NULL, *lyp = NULL, *x = NULL, *xp = NULL;

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

		// Only needed for rank 0.
		A = new double[rows * cols];
		y = new double[rows];
		x = new double[cols];
	}

	// Send sizes of matrix and x vector to all processes.
	MPI_Bcast(&rows, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&cols, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&iters, 1, MPI_INT, 0, MPI_COMM_WORLD);

	xp = new double[cols];

	int counts[commsz];
	int disp[commsz];
	int vcounts[commsz];
	int vdisp[commsz];

	// Size of sending buffer for each process, note that the last
	// process has a different size then the rest.
	sendsize = cols * (rows / commsz);
	lastsendsize = sendsize + cols * (rows % commsz);

	// Size of receiving buffer for each process.
	bufentries = rows / commsz;
	if (rank == commsz - 1)
		bufentries = rows / commsz + rows % commsz;

	// Create vectors of sizes and displacements.
	for (int i = 0; i < commsz; i++) {
		counts[i] = sendsize;
		disp[i] = i * sendsize;
		vcounts[i] = sendsize / cols;
		vdisp[i] = i * sendsize / cols;
	}
	counts[commsz - 1] = lastsendsize;
	vcounts[commsz - 1] = lastsendsize / cols;

	if (rank == 0) {
		// Populate A and x with random numbers in [0, 1).
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				A[i * cols + j] = 2.0 * rand() / RAND_MAX - 1.0;

		for (int j = 0; j < cols; j++) {
			x[j] = 2.0 * rand() / RAND_MAX - 1.0;
			xp[j] = x[j];
		}

		starttime = MPI_Wtime();
		// Serial multiplication.

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

	// Scatter data and allocate local data.
	// Note that the last process has a different size then the rest.
	// Can be done in a single command across the processes since bufentries
	// represents a base size per process.
	localA = new double[cols * bufentries];
	lyp = new double[bufentries];
	MPI_Scatterv(A, counts, disp, MPI_DOUBLE, localA, bufentries * cols,
	MPI_DOUBLE, 0, MPI_COMM_WORLD);

	// Send xp = x vector to all processes.
	MPI_Bcast(xp, cols, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	// Iterate the matrix vector multiplication dynamical system.
	for (int k = 0; k < iters; k++) {
		// Multiply local rows with x vector.
		for (int i = 0; i < bufentries; i++) {
			lyp[i] = 0;
			for (int j = 0; j < cols; j++)
				lyp[i] += localA[i * cols + j] * xp[j];
		}

		// Gather back local y values into the y-parallel (yp) vector on process 0.
		// Note that the last process has a different size then the rest.
		// Can be done in a single command across the processes since bufentries
		// represents a base size per process.
		MPI_Allgatherv(lyp, bufentries, MPI_DOUBLE, xp, vcounts, vdisp,
		MPI_DOUBLE, MPI_COMM_WORLD);
	}

	if (rank == 0) {
		endtime = MPI_Wtime();
		printf("Parallel Time %.6f sec.\n", endtime - starttime);
		if (vecsEqual(y, xp, rows))
			cout << "Vectors are equal." << "\n";
		else
			cout << "Vectors are not equal." << "\n";
	}

	if (rank == 0) {
		delete[] A;
		delete[] x;
		delete[] y;
	}

	delete[] localA;
	delete[] xp;
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
