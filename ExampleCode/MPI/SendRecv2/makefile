PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = SendRecv2.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

SendRecv2.o : SendRecv2.cpp
	$(CC) $(CPPFLAGS) -c SendRecv2.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
