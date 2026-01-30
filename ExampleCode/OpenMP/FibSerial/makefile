PROG = prog
CC = g++
CPPFLAGS = -g -Wall -fopenmp
LINKFLAGS = -fopenmp
OBJS = FibSerial.o

$(PROG) : $(OBJS)
	$(CC) $(LINKFLAGS) -o $(PROG) $(OBJS)

FibSerial.o : FibSerial.cpp
	$(CC) $(CPPFLAGS) -c FibSerial.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
