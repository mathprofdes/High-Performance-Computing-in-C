PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = NBAllReduceStdDevSct.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

NBAllReduceStdDevSct.o : NBAllReduceStdDevSct.cpp
	$(CC) $(CPPFLAGS) -c NBAllReduceStdDevSct.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
