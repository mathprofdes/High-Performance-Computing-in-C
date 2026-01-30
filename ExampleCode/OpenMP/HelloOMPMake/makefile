PROG = prog
CC = g++
CPPFLAGS = -g -Wall -fopenmp
LINKFLAGS = -fopenmp
OBJS = HelloOMP.o

$(PROG) : $(OBJS)
	$(CC) $(LINKFLAGS) -o $(PROG) $(OBJS)

HelloOMP.o : HelloOMP.c
	$(CC) $(CPPFLAGS) -c HelloOMP.c

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
