PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = ContiguousDT2.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

ContiguousDT2.o : ContiguousDT2.cpp
	$(CC) $(CPPFLAGS) -c ContiguousDT2.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
