PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = NBWaitAll.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

NBWaitAll.o : NBWaitAll.cpp
	$(CC) $(CPPFLAGS) -c NBWaitAll.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
