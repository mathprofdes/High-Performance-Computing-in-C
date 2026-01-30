PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = Files001.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

Files001.o : Files001.cpp
	$(CC) $(CPPFLAGS) -c Files001.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
