PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = MatVecMult3.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

MatVecMult3.o : MatVecMult3.cpp
	$(CC) $(CPPFLAGS) -c MatVecMult3.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
