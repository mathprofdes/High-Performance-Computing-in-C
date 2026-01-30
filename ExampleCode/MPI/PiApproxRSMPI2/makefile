PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = PiApproxRSMPI2.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

PiApproxRSMPI2.o : PiApproxRSMPI2.cpp
	$(CC) $(CPPFLAGS) -c PiApproxRSMPI2.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
