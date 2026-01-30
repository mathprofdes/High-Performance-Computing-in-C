PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = AllReduceInPlace.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

AllReduceInPlace.o : AllReduceInPlace.cpp
	$(CC) $(CPPFLAGS) -c AllReduceInPlace.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
