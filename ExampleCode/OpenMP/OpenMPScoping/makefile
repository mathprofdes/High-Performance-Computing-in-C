PROG = prog
CC = g++
CPPFLAGS = -g -Wall -fopenmp
LINKFLAGS = -fopenmp
OBJS = OpenMPScoping.o

$(PROG) : $(OBJS)
	$(CC) $(LINKFLAGS) -o $(PROG) $(OBJS)

OpenMPScoping.o : OpenMPScoping.cpp
	$(CC) $(CPPFLAGS) -c OpenMPScoping.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
