PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = Files002.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

Files002.o : Files002.cpp
	$(CC) $(CPPFLAGS) -c Files002.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
