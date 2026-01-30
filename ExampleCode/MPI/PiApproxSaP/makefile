PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = PiApproxSaP.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

PiApproxSaP.o : PiApproxSaP.cpp
	$(CC) $(CPPFLAGS) -c PiApproxSaP.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
