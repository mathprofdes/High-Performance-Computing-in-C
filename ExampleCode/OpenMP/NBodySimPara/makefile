PROG = prog
CC = g++
CPPFLAGS = -g -Wall -fopenmp
LINKFLAGS = -fopenmp
OBJS = NBodySimPara.o particle.o tinyfiledialogs.o Vec3.o

$(PROG) : $(OBJS)
	$(CC) $(LINKFLAGS) -o $(PROG) $(OBJS)

NBodySimPara.o : NBodySimPara.cpp
	$(CC) $(CPPFLAGS) -c NBodySimPara.cpp

particle.o : particle.cpp
	$(CC) $(CPPFLAGS) -c particle.cpp

tinyfiledialogs.o : tinyfiledialogs.c
	$(CC) $(CPPFLAGS) -c tinyfiledialogs.c

Vec3.o : Vec3.cpp
	$(CC) $(CPPFLAGS) -c Vec3.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
