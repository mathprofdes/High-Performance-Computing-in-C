PROG = prog
CC = g++
CPPFLAGS = -g -Wall -fopenmp
LINKFLAGS = -fopenmp
OBJS = PiSeriesParallel2.o

$(PROG) : $(OBJS)
	$(CC) $(LINKFLAGS) -o $(PROG) $(OBJS)

PiSeriesParallel2.o : PiSeriesParallel2.cpp
	$(CC) $(CPPFLAGS) -c PiSeriesParallel2.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
