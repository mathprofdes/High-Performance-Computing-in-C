PROG = prog
CC = g++
CPPFLAGS = -g -Wall -fopenmp
LINKFLAGS = -fopenmp
OBJS = PiApproxParallel004Wtime.o

$(PROG) : $(OBJS)
	$(CC) $(LINKFLAGS) -o $(PROG) $(OBJS)

PiApproxParallel004Wtime.o : PiApproxParallel004Wtime.cpp
	$(CC) $(CPPFLAGS) -c PiApproxParallel004Wtime.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
