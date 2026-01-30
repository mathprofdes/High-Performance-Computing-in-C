#ifndef GRAPHICSENGINE_H_INCLUDED
#define GRAPHICSENGINE_H_INCLUDED

#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
#include <stdio.h>
#include <chrono>
#include <ctime>
#include <sstream>
#include <vector>

#include "LoadShaders.h"
#include "ProgramDefines.h"
#include "SphericalCamera.h"
#include "YPRCamera.h"
#include "Axes.h"
#include "Vec3.h"
#include "tinyfiledialogs.h"

/**
 \file GraphicsEngine.h
 \brief Header file for GraphicsEngine.cpp

 \author    Don Spickler
 \version   1.1
 \date      8/17/2023

 */

/**
 \class GraphicsEngine

 \brief The GraphicsEngine class is an extension of sf::RenderWindow which
 handles all of the graphics rendering in the program.

 */

class GraphicsEngine: public sf::RenderWindow {
private:
	GLenum mode;    ///< Mode, either point, line or fill.
	Axes coords;    ///< Axes Object

	GLuint program;   ///< Shader address for the pass-through shader.
	GLuint ccprogram; ///< Shader address for the constant color shader.

	GLuint simvboptr;    ///< ID for the VBO.
	GLuint simbufptr;    ///< ID for the array buffer.
	GLint vPosition = 0; ///< Position location in shader.

	GLuint ProjLoc;      ///< Location ID of the Projection matrix in the shader.
	GLuint ViewLoc;      ///< Location ID of the View matrix in the shader.
	GLuint ModelLoc;     ///< Location ID of the Model matrix in the shader.

	GLuint ccProjLoc;   ///< Location ID of the Projection matrix in the constant color shader.
	GLuint ccViewLoc;   ///< Location ID of the View matrix in the constant color shader.
	GLuint ccModelLoc;  ///< Location ID of the Model matrix in the constant color shader.
	GLuint ccColorLoc;  ///< Location ID of the color in the constant color shader.

	SphericalCamera sphcamera;  ///< Spherical Camera
	YPRCamera yprcamera;        ///< Yaw-Pitch-Roll Camera
	int CameraNumber;           ///< Camera number 1 = spherical, 2 = yaw-pitch-roll.

	glm::mat4 projection;       ///< Projection Matrix

	GLboolean drawAxes;        ///< Boolean for axes being drawn.
	GLboolean drawManyBoxes;   ///< Boolean for many boxes verses one box being drawn.
	GLboolean drawBoxes;       ///< Boolean for boxes being drawn.

	int colorscheme = 1;   ///< Color scheme number.

	vector<Vec3> simdata;  ///< Vector to hold the data for the loaded simulation.
	int numparticles = 0;  ///< Number of particles in the simulation.
	int numtimesteps = 0;  ///< Number of time-steps in the simulation.
	int simlength = 1;     ///< Number of time-steps to be displayed in the simulation.

	std::string windowtitle; ///< Title in the window titlebar.

	vector<glm::vec4> colors; ///< Array of colors to be used for the multi-color trails.

	void printOpenGLErrors();
	void print_GLM_Matrix(glm::mat4 m);

	double frand();
	double frand(double lb, double ub);

public:
	GraphicsEngine(std::string title = "OpenGL Window", GLint MajorVer = 3,
			GLint MinorVer = 3, int width = 600, int height = 600);
	~GraphicsEngine();

	void display();
	void changeMode();
	void screenshot();
	void resize();
	void setSize(unsigned int, unsigned int);
	GLfloat* getScreenBounds();

	void setDrawAxes(GLboolean b);
	GLboolean isSphericalCameraOn();
	void setSphericalCameraOn();
	GLboolean isYPRCameraOn();
	void setYPRCameraOn();

	SphericalCamera* getSphericalCamera();
	YPRCamera* getYPRCamera();

	void openSimulationFile();
	void incSimLength(int tsinc);
	void resetSimLength();
	void resetSimLengthToEnd();
	void setColorScheme(int cs);

	void setTitlebar();
	void displayHelp();
};

#endif // GRAPHICSENGINE_H_INCLUDED
