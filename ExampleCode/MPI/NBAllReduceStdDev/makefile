PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = NBAllReduceStdDev.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

NBAllReduceStdDev.o : NBAllReduceStdDev.cpp
	$(CC) $(CPPFLAGS) -c NBAllReduceStdDev.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
