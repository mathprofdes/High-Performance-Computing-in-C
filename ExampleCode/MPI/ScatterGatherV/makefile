PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = ScatterGatherV.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

ScatterGatherV.o : ScatterGatherV.cpp
	$(CC) $(CPPFLAGS) -c ScatterGatherV.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
