PROG = prog
CC = g++
CPPFLAGS = -g -Wall -fopenmp
LINKFLAGS = -fopenmp
OBJS = NamedCritical.o

$(PROG) : $(OBJS)
	$(CC) $(LINKFLAGS) -o $(PROG) $(OBJS)

NamedCritical.o : NamedCritical.cpp
	$(CC) $(CPPFLAGS) -c NamedCritical.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
