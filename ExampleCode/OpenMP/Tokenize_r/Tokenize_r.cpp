#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <omp.h>

const int MAX_LINE = 80;

using namespace std;

void Tokenize(char *lines[], int line_count, int thread_count);

int main(int argc, char *argv[]) {
	string sonnet[] = { "How careful was I when I took my way,",
			"Each trifle under truest bars to thrust,",
			"That to my use it might unused stay",
			"From hands of falsehood, in sure wards of trust!",
			"But thou, to whom my jewels trifles are,",
			"Most worthy comfort, now my greatest grief,",
			"Thou best of dearest, and mine only care,",
			"Art left the prey of every vulgar thief.",
			"Thee have I not locked up in any chest,",
			"Save where thou art not, though I feel thou art,",
			"Within the gentle closure of my breast,",
			"From whence at pleasure thou mayst come and part,",
			"And even thence thou wilt be stol'n I fear,",
			"For truth proves thievish for a prize so dear." };

	char *lines[14];
	for (int i = 0; i < 14; i++) {
		lines[i] = new char[MAX_LINE];
		strcpy(lines[i], sonnet[i].c_str());
	}

	int numThreads;
	int line_count = 14;

	cout << "Input number of threads: ";
	cin >> numThreads;

	if (numThreads <= 0) {
#pragma omp parallel
		numThreads = omp_get_num_threads();
	}

	Tokenize(lines, line_count, numThreads);

	for (int i = 0; i < 14; i++)
		delete[] lines[i];

	return 0;
}

void Tokenize(char *lines[], int line_count, int thread_count) {
	int my_rank, i, j;
	char *my_token;

#pragma omp parallel num_threads(thread_count) \
      default(none) private(my_rank, i, j, my_token) shared(lines, line_count)
	{
		my_rank = omp_get_thread_num();
#pragma omp for schedule(static, 1)
		for (i = 0; i < line_count; i++) {
			char* saveptr;
			printf("Thread %d > line %d = %s \n", my_rank, i, lines[i]);
			j = 0;
			my_token = strtok_r(lines[i], " \t\n", &saveptr);
			while (my_token != NULL) {
				printf("Thread %d > token %d = %s\n", my_rank, j, my_token);
				my_token = strtok_r(NULL, " \t\n", &saveptr);
				j++;
			}
		}
	}
}
