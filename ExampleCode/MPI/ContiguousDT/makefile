PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = ContiguousDT.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

ContiguousDT.o : ContiguousDT.cpp
	$(CC) $(CPPFLAGS) -c ContiguousDT.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
