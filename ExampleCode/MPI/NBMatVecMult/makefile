PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = NBMatVecMult.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

NBMatVecMult.o : NBMatVecMult.cpp
	$(CC) $(CPPFLAGS) -c NBMatVecMult.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
