PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = PiApproxSerial.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

PiApproxSerial.o : PiApproxSerial.cpp
	$(CC) $(CPPFLAGS) -c PiApproxSerial.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
