PROG = prog
CC = g++
CPPFLAGS = -g -Wall -fopenmp
LINKFLAGS = -fopenmp
OBJS = SchedulingCyclic.o

$(PROG) : $(OBJS)
	$(CC) $(LINKFLAGS) -o $(PROG) $(OBJS)

SchedulingCyclic.o : SchedulingCyclic.cpp
	$(CC) $(CPPFLAGS) -c SchedulingCyclic.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
