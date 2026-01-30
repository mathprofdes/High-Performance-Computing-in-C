PROG = prog
CC = g++
CPPFLAGS = -g -Wall -fopenmp
LINKFLAGS = -fopenmp
OBJS = FibTask.o

$(PROG) : $(OBJS)
	$(CC) $(LINKFLAGS) -o $(PROG) $(OBJS)

FibTask.o : FibTask.cpp
	$(CC) $(CPPFLAGS) -c FibTask.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
