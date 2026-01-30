PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = Files006.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

Files006.o : Files006.cpp
	$(CC) $(CPPFLAGS) -c Files006.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
