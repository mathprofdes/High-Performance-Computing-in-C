PROG = prog
CC = g++
CPPFLAGS = -g -Wall -fopenmp
LINKFLAGS = -fopenmp
OBJS = PiApproxParallel004.o

$(PROG) : $(OBJS)
	$(CC) $(LINKFLAGS) -o $(PROG) $(OBJS)

PiApproxParallel004.o : PiApproxParallel004.cpp
	$(CC) $(CPPFLAGS) -c PiApproxParallel004.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
