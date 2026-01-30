PROG = prog
CC = g++
CPPFLAGS = -g -Wall -fopenmp
LINKFLAGS = -fopenmp
OBJS = PiApproxSerial.o

$(PROG) : $(OBJS)
	$(CC) $(LINKFLAGS) -o $(PROG) $(OBJS)

PiApproxSerial.o : PiApproxSerial.cpp
	$(CC) $(CPPFLAGS) -c PiApproxSerial.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
