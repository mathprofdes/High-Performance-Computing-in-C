PROG = prog
CC = g++
CPPFLAGS = -g -Wall -fopenmp
LINKFLAGS = -fopenmp
OBJS = PiSeriesSerial.o

$(PROG) : $(OBJS)
	$(CC) $(LINKFLAGS) -o $(PROG) $(OBJS)

PiSeriesSerial.o : PiSeriesSerial.cpp
	$(CC) $(CPPFLAGS) -c PiSeriesSerial.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
