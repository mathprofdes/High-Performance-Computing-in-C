PROG = prog
CC = g++
CPPFLAGS = -g -Wall -fopenmp
LINKFLAGS = -fopenmp
OBJS = PiApproxParallel003Chrono.o

$(PROG) : $(OBJS)
	$(CC) $(LINKFLAGS) -o $(PROG) $(OBJS)

PiApproxParallel003Chrono.o : PiApproxParallel003Chrono.cpp
	$(CC) $(CPPFLAGS) -c PiApproxParallel003Chrono.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
