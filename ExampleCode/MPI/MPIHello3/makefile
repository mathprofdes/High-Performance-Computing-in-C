PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = MPIHello3.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

MPIHello3.o : MPIHello3.cpp
	$(CC) $(CPPFLAGS) -c MPIHello3.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
