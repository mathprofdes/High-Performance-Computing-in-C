PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = NBWaitAny2.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

NBWaitAny2.o : NBWaitAny2.cpp
	$(CC) $(CPPFLAGS) -c NBWaitAny2.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
