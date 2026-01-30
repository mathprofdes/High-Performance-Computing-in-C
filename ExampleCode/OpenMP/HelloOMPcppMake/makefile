PROG = prog
CC = g++
CPPFLAGS = -g -Wall -fopenmp
LINKFLAGS = -fopenmp
OBJS = HelloOMPcpp.o

$(PROG) : $(OBJS)
	$(CC) $(LINKFLAGS) -o $(PROG) $(OBJS)

HelloOMPcpp.o : HelloOMPcpp.cpp
	$(CC) $(CPPFLAGS) -c HelloOMPcpp.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
