PROG = prog
CC = g++
CPPFLAGS = -g -Wall -fopenmp
LINKFLAGS = -fopenmp
OBJS = FibParallel001.o

$(PROG) : $(OBJS)
	$(CC) $(LINKFLAGS) -o $(PROG) $(OBJS)

FibParallel001.o : FibParallel001.cpp
	$(CC) $(CPPFLAGS) -c FibParallel001.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
