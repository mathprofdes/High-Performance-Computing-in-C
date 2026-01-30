PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = VecGather.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

VecGather.o : VecGather.cpp
	$(CC) $(CPPFLAGS) -c VecGather.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
