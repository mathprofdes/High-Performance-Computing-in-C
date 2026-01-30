PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = SendRecvTiming.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

SendRecvTiming.o : SendRecvTiming.cpp
	$(CC) $(CPPFLAGS) -c SendRecvTiming.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
