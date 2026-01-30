#include <mpi.h>

int main(int argc, char **argv) {
	MPI_Init(&argc, &argv);
	int size;
	int rank;
	char name[MPI_MAX_PROCESSOR_NAME];
	int len;

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Get_processor_name(name, &len);

	printf("I am %d of %d on %s. \n", rank, size, name);

	MPI_Finalize();

	return 0;
}
