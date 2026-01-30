PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = VectorDT2.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

VectorDT2.o : VectorDT2.cpp
	$(CC) $(CPPFLAGS) -c VectorDT2.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
