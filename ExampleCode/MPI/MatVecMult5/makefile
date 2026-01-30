PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = MatVecMult5.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

MatVecMult5.o : MatVecMult5.cpp
	$(CC) $(CPPFLAGS) -c MatVecMult5.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
