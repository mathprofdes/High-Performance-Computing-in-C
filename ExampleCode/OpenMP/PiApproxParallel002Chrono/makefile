PROG = prog
CC = g++
CPPFLAGS = -g -Wall -fopenmp
LINKFLAGS = -fopenmp
OBJS = PiApproxParallel002Chrono.o

$(PROG) : $(OBJS)
	$(CC) $(LINKFLAGS) -o $(PROG) $(OBJS)

PiApproxParallel002Chrono.o : PiApproxParallel002Chrono.cpp
	$(CC) $(CPPFLAGS) -c PiApproxParallel002Chrono.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
