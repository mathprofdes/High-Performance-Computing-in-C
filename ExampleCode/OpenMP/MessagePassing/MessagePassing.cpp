#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <omp.h>

#include "Queue.h"

using namespace std;

void Send(Queue<int> queues[], int dest, int msg);
void Receive(Queue<int> queues[], int rank);

int main() {
	int numThreads, nummessages;

	cout << "Input the number of messages to send: ";
	cin >> nummessages;

	cout << "Input number of threads: ";
	cin >> numThreads;

	srand(time(0));

	if (numThreads <= 0) {
#pragma omp parallel
		numThreads = omp_get_num_threads();
	}

	Queue<int> messageQueues[numThreads];

#pragma omp parallel num_threads(numThreads) \
      default(none) shared(numThreads, nummessages, messageQueues)
	{
		int rank = omp_get_thread_num();

		for (int i = 0; i < nummessages; i++) {
			int dest = rand() % numThreads;
			int msg = rand() % 1000;
			Send(messageQueues, dest, msg);
			Receive(messageQueues, rank);
		}

		// Needed to prevent sends to threads that have finished.
#pragma omp barrier

		// Just a message that all threads are done with the sending loop.
//#pragma omp single
//		printf("======== All Threads done sending\n");

		// Flush the queues.
		while (!messageQueues[rank].Empty())
			Receive(messageQueues, rank);

		printf(" ***** Thread %d > finished\n", rank);
	}

	cout << "Done \n";
	return 0;
}

void Send(Queue<int> queues[], int dest, int msg) {

	printf("---------- Send dest: %d  message: %d \n", dest, msg);

#pragma omp critical
	queues[dest].Enqueue(msg);
}

void Receive(Queue<int> queues[], int rank) {
	int mesg;
	int queuesize = queues[rank].Size();

	if (queuesize == 0)
		return;
	else if (queuesize == 1)
#pragma omp critical
		mesg = queues[rank].Dequeue();
	else
//#pragma omp critical
		mesg = queues[rank].Dequeue();

	printf("Thread %d > received %d \n", rank, mesg);
}
