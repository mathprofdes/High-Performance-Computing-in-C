PROG = prog
CC = g++
CPPFLAGS = -g -Wall -fopenmp
LINKFLAGS = -fopenmp
OBJS = PiApproxParallelFor2.o

$(PROG) : $(OBJS)
	$(CC) $(LINKFLAGS) -o $(PROG) $(OBJS)

PiApproxParallelFor2.o : PiApproxParallelFor2.cpp
	$(CC) $(CPPFLAGS) -c PiApproxParallelFor2.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
