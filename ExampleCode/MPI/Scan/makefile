PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = Scan.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

Scan.o : Scan.cpp
	$(CC) $(CPPFLAGS) -c Scan.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
