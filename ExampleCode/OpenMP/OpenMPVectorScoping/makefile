PROG = prog
CC = g++
CPPFLAGS = -g -Wall -fopenmp
LINKFLAGS = -fopenmp
OBJS = OpenMPVectorScoping.o

$(PROG) : $(OBJS)
	$(CC) $(LINKFLAGS) -o $(PROG) $(OBJS)

OpenMPVectorScoping.o : OpenMPVectorScoping.cpp
	$(CC) $(CPPFLAGS) -c OpenMPVectorScoping.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
