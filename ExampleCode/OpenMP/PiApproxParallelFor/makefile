PROG = prog
CC = g++
CPPFLAGS = -g -Wall -fopenmp
LINKFLAGS = -fopenmp
OBJS = PiApproxParallelFor.o

$(PROG) : $(OBJS)
	$(CC) $(LINKFLAGS) -o $(PROG) $(OBJS)

PiApproxParallelFor.o : PiApproxParallelFor.cpp
	$(CC) $(CPPFLAGS) -c PiApproxParallelFor.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
