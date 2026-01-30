PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = PiApproxRSMPI4.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

PiApproxRSMPI4.o : PiApproxRSMPI4.cpp
	$(CC) $(CPPFLAGS) -c PiApproxRSMPI4.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
