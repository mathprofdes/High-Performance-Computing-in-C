PROG = prog
CC = g++
CPPFLAGS = -g -Wall -fopenmp
LINKFLAGS = -fopenmp
OBJS = MatVecMult.o

$(PROG) : $(OBJS)
	$(CC) $(LINKFLAGS) -o $(PROG) $(OBJS)

MatVecMult.o : MatVecMult.cpp
	$(CC) $(CPPFLAGS) -c MatVecMult.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
