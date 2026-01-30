PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = AllReduceStdDev.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

AllReduceStdDev.o : AllReduceStdDev.cpp
	$(CC) $(CPPFLAGS) -c AllReduceStdDev.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
