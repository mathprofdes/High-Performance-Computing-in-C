PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = StructDT.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

StructDT.o : StructDT.cpp
	$(CC) $(CPPFLAGS) -c StructDT.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
