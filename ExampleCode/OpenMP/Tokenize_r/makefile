PROG = prog
CC = g++
CPPFLAGS = -g -Wall -fopenmp
LINKFLAGS = -fopenmp
OBJS = Tokenize_r.o

$(PROG) : $(OBJS)
	$(CC) $(LINKFLAGS) -o $(PROG) $(OBJS)

Tokenize_r.o : Tokenize_r.cpp
	$(CC) $(CPPFLAGS) -c Tokenize_r.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
