PROG = prog
CC = g++
CPPFLAGS = -g -Wall -fopenmp
LINKFLAGS = -fopenmp
OBJS = Deadlock.o

$(PROG) : $(OBJS)
	$(CC) $(LINKFLAGS) -o $(PROG) $(OBJS)

Deadlock.o : Deadlock.cpp
	$(CC) $(CPPFLAGS) -c Deadlock.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
