PROG = prog
CC = g++
CPPFLAGS = -g -Wall -fopenmp
LINKFLAGS = -fopenmp
OBJS = OpenMPArrayScoping2.o

$(PROG) : $(OBJS)
	$(CC) $(LINKFLAGS) -o $(PROG) $(OBJS)

OpenMPArrayScoping2.o : OpenMPArrayScoping2.cpp
	$(CC) $(CPPFLAGS) -c OpenMPArrayScoping2.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
