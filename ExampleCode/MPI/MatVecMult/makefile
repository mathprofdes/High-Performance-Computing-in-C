PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = MatVecMult.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

MatVecMult.o : MatVecMult.cpp
	$(CC) $(CPPFLAGS) -c MatVecMult.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
