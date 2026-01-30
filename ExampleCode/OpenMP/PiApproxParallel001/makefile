PROG = prog
CC = g++
CPPFLAGS = -g -Wall -fopenmp
LINKFLAGS = -fopenmp
OBJS = PiApproxParallel001.o

$(PROG) : $(OBJS)
	$(CC) $(LINKFLAGS) -o $(PROG) $(OBJS)

PiApproxParallel001.o : PiApproxParallel001.cpp
	$(CC) $(CPPFLAGS) -c PiApproxParallel001.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
