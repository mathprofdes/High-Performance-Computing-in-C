PROG = prog
CC = g++
CPPFLAGS = -g -Wall -fopenmp
LINKFLAGS = -fopenmp
OBJS = PiSeriesParallel3.o

$(PROG) : $(OBJS)
	$(CC) $(LINKFLAGS) -o $(PROG) $(OBJS)

PiSeriesParallel3.o : PiSeriesParallel3.cpp
	$(CC) $(CPPFLAGS) -c PiSeriesParallel3.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
