PROG = prog
CC = g++
CPPFLAGS = -g -Wall -fopenmp
LINKFLAGS = -fopenmp
OBJS = PiApproxParallelFor3.o

$(PROG) : $(OBJS)
	$(CC) $(LINKFLAGS) -o $(PROG) $(OBJS)

PiApproxParallelFor3.o : PiApproxParallelFor3.cpp
	$(CC) $(CPPFLAGS) -c PiApproxParallelFor3.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
