PROG = prog
CC = g++
CPPFLAGS = -g -Wall -fopenmp
LINKFLAGS = -fopenmp
OBJS = PiApproxParallel003Wtime.o

$(PROG) : $(OBJS)
	$(CC) $(LINKFLAGS) -o $(PROG) $(OBJS)

PiApproxParallel003Wtime.o : PiApproxParallel003Wtime.cpp
	$(CC) $(CPPFLAGS) -c PiApproxParallel003Wtime.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
