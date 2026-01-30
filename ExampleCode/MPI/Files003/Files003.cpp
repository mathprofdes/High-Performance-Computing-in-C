#include <math.h> 
#include <mpi.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char *argv[]) {
	int commsz, rank;
	MPI_File file;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &commsz);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	srand(time(0) + rank);

	MPI_File_open(MPI_COMM_WORLD, "Test002.dat",
	MPI_MODE_RDWR | MPI_MODE_CREATE, MPI_INFO_NULL, &file);

	for (int i = 0; i < 5; i++) {
		int num = rand() % 1000;
		MPI_File_write_at(file, rank * 5 * sizeof(int) + i * sizeof(int), &num,
				1, MPI_INT, MPI_STATUS_IGNORE);
		cout << "Rank " << rank << " --- " << i << " --- " << num << endl;
	}

	// Make sure that all writes are done before reading.
	MPI_Barrier(MPI_COMM_WORLD);

	if (rank == 0) {
		int filecontents[5 * commsz];
		MPI_File_read_at(file, 0, filecontents, 5 * commsz, MPI_INT,
				MPI_STATUS_IGNORE);

		for (int i = 0; i < 5 * commsz; i++) {
			cout << filecontents[i] << " ";
		}
		cout << endl;
	}

	MPI_File_close(&file);

	MPI_Finalize();

	return 0;
}
