PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = PiApproxRSMPI3.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

PiApproxRSMPI3.o : PiApproxRSMPI3.cpp
	$(CC) $(CPPFLAGS) -c PiApproxRSMPI3.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
