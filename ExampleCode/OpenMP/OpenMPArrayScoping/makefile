PROG = prog
CC = g++
CPPFLAGS = -g -Wall -fopenmp
LINKFLAGS = -fopenmp
OBJS = OpenMPArrayScoping.o

$(PROG) : $(OBJS)
	$(CC) $(LINKFLAGS) -o $(PROG) $(OBJS)

OpenMPArrayScoping.o : OpenMPArrayScoping.cpp
	$(CC) $(CPPFLAGS) -c OpenMPArrayScoping.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
