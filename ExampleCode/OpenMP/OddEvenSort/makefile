PROG = prog
CC = g++
CPPFLAGS = -g -Wall -fopenmp
LINKFLAGS = -fopenmp
OBJS = OddEvenSort.o

$(PROG) : $(OBJS)
	$(CC) $(LINKFLAGS) -o $(PROG) $(OBJS)

OddEvenSort.o : OddEvenSort.cpp
	$(CC) $(CPPFLAGS) -c OddEvenSort.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
