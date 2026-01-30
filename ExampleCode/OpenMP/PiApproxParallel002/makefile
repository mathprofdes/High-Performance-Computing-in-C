PROG = prog
CC = g++
CPPFLAGS = -g -Wall -fopenmp
LINKFLAGS = -fopenmp
OBJS = PiApproxParallel002.o

$(PROG) : $(OBJS)
	$(CC) $(LINKFLAGS) -o $(PROG) $(OBJS)

PiApproxParallel002.o : PiApproxParallel002.cpp
	$(CC) $(CPPFLAGS) -c PiApproxParallel002.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
