PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = NBPiApproxRSMPIBcast.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

NBPiApproxRSMPIBcast.o : NBPiApproxRSMPIBcast.cpp
	$(CC) $(CPPFLAGS) -c NBPiApproxRSMPIBcast.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
