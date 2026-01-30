PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = MatVecMult4.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

MatVecMult4.o : MatVecMult4.cpp
	$(CC) $(CPPFLAGS) -c MatVecMult4.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
