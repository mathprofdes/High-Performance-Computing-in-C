PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = NBArrayReduce.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

NBArrayReduce.o : NBArrayReduce.cpp
	$(CC) $(CPPFLAGS) -c NBArrayReduce.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
