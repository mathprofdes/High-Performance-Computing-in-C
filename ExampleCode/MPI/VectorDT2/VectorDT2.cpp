#include <math.h> 
#include <mpi.h>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char *argv[]) {
	int commsz, rank, n, m;

	srand(time(0));

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &commsz);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	m = 5;
	n = commsz;

	int *data, *col;

	if (rank == 0) {
		data = new int[m * n];
		for (int i = 0; i < m * n; i++)
			data[i] = rand() % 10;

		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++)
				cout << data[i * n + j] << " ";
			cout << endl;
		}
	}

	col = new int[m];

	MPI_Datatype newtype;
	MPI_Type_vector(m, 1, n, MPI_INT, &newtype);
	MPI_Type_commit(&newtype);

	if (rank == 0) {
		for (int i = 0; i <= 3; i++)
			MPI_Send(&data[i], 1, newtype, i, 0, MPI_COMM_WORLD);
		MPI_Type_free(&newtype);
	}

	MPI_Status recv_status;
	int recv_count;
	MPI_Recv(col, m, MPI_INT, 0, 0, MPI_COMM_WORLD, &recv_status);
	MPI_Get_count(&recv_status, MPI_INT, &recv_count);
	printf("Process  %d received %d\n", rank, recv_count);

	cout << "Process " << rank << ": ";
	for (int i = 0; i < m; i++)
		cout << col[i] << " ";
	cout << endl;

	if (rank == 0)
		printf("Finished\n");

	MPI_Finalize();
	return 0;
}

