PROG = prog
CC = g++
CPPFLAGS = -g -Wall -fopenmp
LINKFLAGS = -fopenmp
OBJS = Collapse.o

$(PROG) : $(OBJS)
	$(CC) $(LINKFLAGS) -o $(PROG) $(OBJS)

Collapse.o : Collapse.cpp
	$(CC) $(CPPFLAGS) -c Collapse.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
