PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = Files004.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

Files004.o : Files004.cpp
	$(CC) $(CPPFLAGS) -c Files004.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
