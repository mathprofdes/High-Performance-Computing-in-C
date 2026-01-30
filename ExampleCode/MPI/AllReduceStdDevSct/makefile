PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = AllReduceStdDevSct.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

AllReduceStdDevSct.o : AllReduceStdDevSct.cpp
	$(CC) $(CPPFLAGS) -c AllReduceStdDevSct.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
