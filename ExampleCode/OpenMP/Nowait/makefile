PROG = prog
CC = g++
CPPFLAGS = -g -Wall -fopenmp
LINKFLAGS = -fopenmp
OBJS = nowait.o

$(PROG) : $(OBJS)
	$(CC) $(LINKFLAGS) -o $(PROG) $(OBJS)

nowait.o : nowait.cpp
	$(CC) $(CPPFLAGS) -c nowait.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
