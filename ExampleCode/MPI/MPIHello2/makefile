PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = MPIHello2.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

MPIHello2.o : MPIHello2.cpp
	$(CC) $(CPPFLAGS) -c MPIHello2.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
