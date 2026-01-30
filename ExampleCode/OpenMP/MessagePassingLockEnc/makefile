PROG = prog
CC = g++
CPPFLAGS = -g -Wall -fopenmp
LINKFLAGS = -fopenmp
OBJS = MessagePassingLockEnc.o

$(PROG) : $(OBJS)
	$(CC) $(LINKFLAGS) -o $(PROG) $(OBJS)

MessagePassingLockEnc.o : MessagePassingLockEnc.cpp Queue.h
	$(CC) $(CPPFLAGS) -c MessagePassingLockEnc.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
