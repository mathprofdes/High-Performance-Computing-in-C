PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = StructDT5.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

StructDT5.o : StructDT5.cpp
	$(CC) $(CPPFLAGS) -c StructDT5.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
