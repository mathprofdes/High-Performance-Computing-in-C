PROG = prog
CC = g++
CPPFLAGS = -g -Wall -fopenmp
LINKFLAGS = -fopenmp
OBJS = PiApproxParallel003.o

$(PROG) : $(OBJS)
	$(CC) $(LINKFLAGS) -o $(PROG) $(OBJS)

PiApproxParallel003.o : PiApproxParallel003.cpp
	$(CC) $(CPPFLAGS) -c PiApproxParallel003.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
