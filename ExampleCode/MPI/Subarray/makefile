PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = Subarray.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

Subarray.o : Subarray.cpp
	$(CC) $(CPPFLAGS) -c Subarray.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
