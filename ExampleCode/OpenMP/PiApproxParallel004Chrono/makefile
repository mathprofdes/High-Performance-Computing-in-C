PROG = prog
CC = g++
CPPFLAGS = -g -Wall -fopenmp
LINKFLAGS = -fopenmp
OBJS = PiApproxParallel004Chrono.o

$(PROG) : $(OBJS)
	$(CC) $(LINKFLAGS) -o $(PROG) $(OBJS)

PiApproxParallel004Chrono.o : PiApproxParallel004Chrono.cpp
	$(CC) $(CPPFLAGS) -c PiApproxParallel004Chrono.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
