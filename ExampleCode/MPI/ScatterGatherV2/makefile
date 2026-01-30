PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = ScatterGatherV2.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

ScatterGatherV2.o : ScatterGatherV2.cpp
	$(CC) $(CPPFLAGS) -c ScatterGatherV2.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
