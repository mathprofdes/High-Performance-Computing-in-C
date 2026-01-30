PROG = prog
CC = mpic++
CPPFLAGS = -g -Wall
OBJS = StructDT3.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

StructDT3.o : StructDT3.cpp
	$(CC) $(CPPFLAGS) -c StructDT3.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
