PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = Files003.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

Files003.o : Files003.cpp
	$(CC) $(CPPFLAGS) -c Files003.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
