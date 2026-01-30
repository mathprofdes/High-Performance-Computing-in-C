PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = ContiguousDT3.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

ContiguousDT3.o : ContiguousDT3.cpp
	$(CC) $(CPPFLAGS) -c ContiguousDT3.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
