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

	MPI_File_open(MPI_COMM_WORLD, "Test001.dat",
	MPI_MODE_WRONLY | MPI_MODE_CREATE, MPI_INFO_NULL, &file);

	MPI_File_write_at(file, rank * sizeof(int), &rank, 1,
	MPI_INT, MPI_STATUS_IGNORE);

	MPI_File_close(&file);

	MPI_Finalize();

	return 0;
}
