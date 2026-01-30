PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = ArrayReduce2.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

ArrayReduce2.o : ArrayReduce2.cpp
	$(CC) $(CPPFLAGS) -c ArrayReduce2.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
