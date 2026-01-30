PROG = prog
CC = g++
CPPFLAGS = -g -Wall -fopenmp
LINKFLAGS = -fopenmp
OBJS = PiApproxParallel002Wtime.o

$(PROG) : $(OBJS)
	$(CC) $(LINKFLAGS) -o $(PROG) $(OBJS)

PiApproxParallel002Wtime.o : PiApproxParallel002Wtime.cpp
	$(CC) $(CPPFLAGS) -c PiApproxParallel002Wtime.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
