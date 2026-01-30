PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = PiApproxRSMPI.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

PiApproxRSMPI.o : PiApproxRSMPI.cpp
	$(CC) $(CPPFLAGS) -c PiApproxRSMPI.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
