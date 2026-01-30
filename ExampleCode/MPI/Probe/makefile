PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = Probe.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

Probe.o : Probe.cpp
	$(CC) $(CPPFLAGS) -c Probe.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
