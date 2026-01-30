PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = VectorDT.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

VectorDT.o : VectorDT.cpp
	$(CC) $(CPPFLAGS) -c VectorDT.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
