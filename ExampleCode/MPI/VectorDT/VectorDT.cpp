#include <math.h> 
#include <mpi.h>
#include <iostream>
#include <sstream>

using namespace std;

int main(int argc, char *argv[]) {
	int commsz, rank, n = 5;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &commsz);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	double *data, *recdata;

	if (rank == 0) {
		data = new double[3 * n];
		for (int i = 0; i < 3 * n; i++)
			data[i] = i + .5;
	} else {
		recdata = new double[n];
	}

	MPI_Datatype newtype;
	MPI_Type_vector(n, 1, 3, MPI_DOUBLE, &newtype);
	MPI_Type_commit(&newtype);

	// Note: Need 4 processes.
	if (rank == 0) {
		for (int i = 1; i <= 3; i++)
			MPI_Send(&data[i - 1], 1, newtype, i, 0, MPI_COMM_WORLD);
		MPI_Type_free(&newtype);
	} else if (rank <= 3) {
		MPI_Status recv_status;
		int recv_count;
		MPI_Recv(recdata, n, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &recv_status);
		MPI_Get_count(&recv_status, MPI_DOUBLE, &recv_count);
		printf("Process  %d received %d\n", rank, recv_count);

		stringstream ss;
		ss << "Process " << rank << ": ";
		for (int i = 0; i < n; i++)
			ss << recdata[i] << " ";
		ss << endl;

		cout << ss.str();
	}

	if (rank == 0)
		printf("Finished\n");

	MPI_Finalize();
	return 0;
}

