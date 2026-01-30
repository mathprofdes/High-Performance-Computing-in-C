PROG = PointSimulationViewer
CC = g++
CPPFLAGS = -g -Wall
LINKFLAGS = -lGL -lGLU -lGLEW -lsfml-window -lsfml-graphics -lsfml-system
OBJS = Axes.o GraphicsEngine.o LoadShaders.o PointSimulationViewer.o SphericalCamera.o tinyfiledialogs.o UI.o Vec3.o YPRCamera.o
CPPFILES = Axes.cpp GraphicsEngine.cpp LoadShaders.cpp PointSimulationViewer.cpp SphericalCamera.cpp tinyfiledialogs.c UI.cpp Vec3.cpp YPRCamera.cpp

$(PROG) : $(OBJS) $(CPPFILES)
	$(CC) *.cpp *.c $(LINKFLAGS) -o $(PROG)

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
