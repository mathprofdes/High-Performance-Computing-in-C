PROG = prog
CC = g++
CPPFLAGS = -g -Wall -fopenmp
LINKFLAGS = -fopenmp
OBJS = Tokenize.o

$(PROG) : $(OBJS)
	$(CC) $(LINKFLAGS) -o $(PROG) $(OBJS)

Tokenize.o : Tokenize.cpp
	$(CC) $(CPPFLAGS) -c Tokenize.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
