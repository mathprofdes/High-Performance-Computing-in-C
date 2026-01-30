PROG = prog
CC = g++
CPPFLAGS = -g -Wall -fopenmp
LINKFLAGS = -fopenmp
OBJS = PiSeriesParallel.o

$(PROG) : $(OBJS)
	$(CC) $(LINKFLAGS) -o $(PROG) $(OBJS)

PiSeriesParallel.o : PiSeriesParallel.cpp
	$(CC) $(CPPFLAGS) -c PiSeriesParallel.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
