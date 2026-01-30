PROG = prog
CC = g++
CPPFLAGS = -g -Wall -fopenmp
LINKFLAGS = -fopenmp
OBJS = NestedParallel.o

$(PROG) : $(OBJS)
	$(CC) $(LINKFLAGS) -o $(PROG) $(OBJS)

NestedParallel.o : NestedParallel.cpp
	$(CC) $(CPPFLAGS) -c NestedParallel.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
