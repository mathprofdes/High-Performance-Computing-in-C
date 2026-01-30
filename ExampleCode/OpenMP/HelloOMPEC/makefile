PROG = prog
CC = g++
CPPFLAGS = -g -Wall -fopenmp
LINKFLAGS = -fopenmp
OBJS = HelloOMPEC.o

$(PROG) : $(OBJS)
	$(CC) $(LINKFLAGS) -o $(PROG) $(OBJS)

HelloOMPEC.o : HelloOMPEC.c
	$(CC) $(CPPFLAGS) -c HelloOMPEC.c

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
