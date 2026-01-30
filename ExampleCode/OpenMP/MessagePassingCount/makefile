PROG = prog
CC = g++
CPPFLAGS = -g -Wall -fopenmp
LINKFLAGS = -fopenmp
OBJS = MessagePassingCount.o

$(PROG) : $(OBJS)
	$(CC) $(LINKFLAGS) -o $(PROG) $(OBJS)

MessagePassingCount.o : MessagePassingCount.cpp Queue.h
	$(CC) $(CPPFLAGS) -c MessagePassingCount.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
