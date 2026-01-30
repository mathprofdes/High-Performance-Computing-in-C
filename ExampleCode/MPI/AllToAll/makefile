PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = AllToAll.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

AllToAll.o : AllToAll.cpp
	$(CC) $(CPPFLAGS) -c AllToAll.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
