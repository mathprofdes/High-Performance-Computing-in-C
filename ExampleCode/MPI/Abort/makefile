PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = Abort.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

Abort.o : Abort.cpp
	$(CC) $(CPPFLAGS) -c Abort.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
