PROG = prog
CC = g++
CPPFLAGS = -g -Wall -fopenmp
LINKFLAGS = -fopenmp
OBJS = MessagePassingLock.o

$(PROG) : $(OBJS)
	$(CC) $(LINKFLAGS) -o $(PROG) $(OBJS)

MessagePassingLock.o : MessagePassingLock.cpp Queue.h
	$(CC) $(CPPFLAGS) -c MessagePassingLock.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
