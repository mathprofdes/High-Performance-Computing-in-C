PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = MatVecMult2.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

MatVecMult2.o : MatVecMult2.cpp
	$(CC) $(CPPFLAGS) -c MatVecMult2.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
