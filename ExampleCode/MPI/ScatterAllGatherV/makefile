PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = ScatterAllGatherV.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

ScatterAllGatherV.o : ScatterAllGatherV.cpp
	$(CC) $(CPPFLAGS) -c ScatterAllGatherV.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
