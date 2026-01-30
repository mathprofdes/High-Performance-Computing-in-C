PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = NBSendRecv.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

NBSendRecv.o : NBSendRecv.cpp
	$(CC) $(CPPFLAGS) -c NBSendRecv.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
