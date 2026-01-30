PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = Files005.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

Files005.o : Files005.cpp
	$(CC) $(CPPFLAGS) -c Files005.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
