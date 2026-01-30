PROG = prog
CC = g++
CPPFLAGS = -g -Wall -fopenmp
LINKFLAGS = -fopenmp
OBJS = Collapse2.o

$(PROG) : $(OBJS)
	$(CC) $(LINKFLAGS) -o $(PROG) $(OBJS)

Collapse2.o : Collapse2.cpp
	$(CC) $(CPPFLAGS) -c Collapse2.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
