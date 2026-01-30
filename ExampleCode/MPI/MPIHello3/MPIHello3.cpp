#include <stdio.h>
#include <string.h>
#include <mpi.h>

const int MAX_STRING = 100;

int main(void) {
	char greeting[MAX_STRING]; /* String storing message */
	int comm_sz; /* Number of processes    */
	int my_rank; /* My process rank        */
	MPI_Status status;
	int count;

	/* Start up MPI */
	MPI_Init(NULL, NULL);

	/* Get the number of processes */
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

	/* Get my rank among all the processes */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	if (my_rank != 0) {
		/* Create message */
		sprintf(greeting, "Greetings from process %d of %d!", my_rank, comm_sz);
		/* Send message to process 0 */
		MPI_Send(greeting, strlen(greeting) + 1, MPI_CHAR, 0, 0,
		MPI_COMM_WORLD);
	} else {
		/* Print my message */
		printf("Greetings from process %d of %d!\n", my_rank, comm_sz);
		for (int q = 1; q < comm_sz; q++) {
			/* Receive message from process q */
			MPI_Recv(greeting, MAX_STRING, MPI_CHAR, MPI_ANY_SOURCE,
			MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			/* Print message from process q */
			printf("%s\n", greeting);
			printf("%d\n", status.MPI_SOURCE);
			printf("%d\n", status.MPI_TAG);
			MPI_Get_count(&status, MPI_CHAR, &count);
			printf("%d\n", count);
		}
	}

	/* Shut down MPI */
	MPI_Finalize();

	return 0;
} /* main */
