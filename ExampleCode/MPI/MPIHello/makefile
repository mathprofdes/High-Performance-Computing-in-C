PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = MPIHello.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

MPIHello.o : MPIHello.cpp
	$(CC) $(CPPFLAGS) -c MPIHello.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
