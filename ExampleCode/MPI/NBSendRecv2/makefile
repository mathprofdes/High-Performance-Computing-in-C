PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = NBSendRecv2.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

NBSendRecv2.o : NBSendRecv2.cpp
	$(CC) $(CPPFLAGS) -c NBSendRecv2.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
