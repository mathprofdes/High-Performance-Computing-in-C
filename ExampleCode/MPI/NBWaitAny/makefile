PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = NBWaitAny.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

NBWaitAny.o : NBWaitAny.cpp
	$(CC) $(CPPFLAGS) -c NBWaitAny.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
