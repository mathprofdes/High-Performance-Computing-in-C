PROG = prog
CC = g++
CPPFLAGS = -g -Wall -fopenmp
LINKFLAGS = -fopenmp
OBJS = HelloOMPnumT.o

$(PROG) : $(OBJS)
	$(CC) $(LINKFLAGS) -o $(PROG) $(OBJS)

HelloOMPnumT.o : HelloOMPnumT.cpp
	$(CC) $(CPPFLAGS) -c HelloOMPnumT.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
