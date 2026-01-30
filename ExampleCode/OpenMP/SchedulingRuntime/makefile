PROG = prog
CC = g++
CPPFLAGS = -g -Wall -fopenmp
LINKFLAGS = -fopenmp
OBJS = SchedulingRuntime.o

$(PROG) : $(OBJS)
	$(CC) $(LINKFLAGS) -o $(PROG) $(OBJS)

SchedulingRuntime.o : SchedulingRuntime.cpp
	$(CC) $(CPPFLAGS) -c SchedulingRuntime.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
