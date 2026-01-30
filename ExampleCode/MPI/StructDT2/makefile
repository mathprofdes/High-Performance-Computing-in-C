PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = StructDT2.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

StructDT2.o : StructDT2.cpp
	$(CC) $(CPPFLAGS) -c StructDT2.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
