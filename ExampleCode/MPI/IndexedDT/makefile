PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = IndexedDT.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

IndexedDT.o : IndexedDT.cpp
	$(CC) $(CPPFLAGS) -c IndexedDT.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
