#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>

#include "GraphicsEngine.h"
#include "UI.h"

/**
 \mainpage Point Simulation Viewer

 \tableofcontents

 \section intro Introduction

 This program is a viewer for the N-Body Problem simulation data produced by the simulator
 that was written as an example for the high-performance computing class. It has both
 spherical camera and yaw-pitch-roll camera navigation, color scheme selection, and
 options to view portions of the simulation for a user-controlled animation. Pressing the
 H key while the program is running will display a help screen with the user options.

 \note Note that your graphics card must be able to support OpenGL version 3.3 to run this program.


 ---

 \subsection copyright Copyright

 \author    Don Spickler
 \version   1.1
 \date      8/17/2023
 \copyright 2023


 ---

 \subsection license License

 GNU Public License

 This software is provided as-is, without warranty of ANY KIND, either expressed or implied,
 including but not limited to the implied warranties of merchant ability and/or fitness for a
 particular purpose. The authors shall NOT be held liable for ANY damage to you, your computer,
 or to anyone or anything else, that may result from its use, or misuse.
 All trademarks and other registered names contained in this package are the property
 of their respective owners.  USE OF THIS SOFTWARE INDICATES THAT YOU AGREE TO THE ABOVE CONDITIONS.

 */

/**
 \file main.cpp
 \brief Main driver for the program.

 This is the main program driver that sets up the graphics engine and links it to
 the user interface processor.

 \author    Don Spickler
 \version   1.1
 \date      8/17/2023

 */

/**
 \brief The Main function, program entry point.

 \return Standard EXIT_SUCCESS return on successful run.

 The main function, responsible for initializing OpenGL and setting up
 the SFML interface for OpenGL.

 */

int main() {
	//  Program setup variables.
	std::string programTitle = "Point Simulation Viewer";
	GLint MinMajor = 3;
	GLint MinMinor = 3;
	GLint WindowWidth = 700;
	GLint WindowHeight = 500;
	bool DisplayInfo = true;

	//  Other variables
	GLint major;
	GLint minor;

// Try core context of 10.10 (too advanced) and see what card will resort to.
// For setting up OpenGL, GLEW, and check versions.
	sf::RenderWindow window(sf::VideoMode(WindowWidth, WindowHeight),
			"OpenGL Setup", sf::Style::Default,
			sf::ContextSettings(24, 8, 4, 10, 10, sf::ContextSettings::Core));

	window.setVisible(false);

	glewExperimental = true;
	if (glewInit()) {
		std::cerr << "\nUnable to initialize GLEW ... exiting. \n";
		exit(EXIT_FAILURE);
	}

	//  Get major and minor OpenGL version from graphics card.
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);

	//  Check card version to minimum required version.
	bool versionOK = true;
	if (major < MinMajor)
		versionOK = false;
	else if (major == MinMajor && minor < MinMinor)
		versionOK = false;

	if (!versionOK) {
		std::cerr << "\nGraphics card OpenGL version is " << major << "."
				<< minor << std::endl;
		std::cerr << "Program required OpenGL version is " << MinMajor << "."
				<< MinMinor << std::endl;
		std::cerr << "Exiting\n";
		exit(EXIT_FAILURE);
	}

	//  Output OpenGL version to the console window.
	if (DisplayInfo) {
		std::cout << "\n";
		std::cout << "Version  = " << glGetString(GL_VERSION) << "\n";
		std::cout << "Major    = " << major << "\n";
		std::cout << "Minor    = " << minor << "\n";
		std::cout << "Vendor   = " << glGetString(GL_VENDOR) << "\n";
		std::cout << "Renderer = " << glGetString(GL_RENDERER) << "\n";
		std::cout << "\n";
	}
	//  Close setup window and context.
	window.close();

	//  Create graphics engine and UI.
	GraphicsEngine ge(programTitle, major, minor, WindowWidth, WindowHeight);
	UI ui(&ge);

	// Start the Game/GUI loop
	while (ge.isOpen()) {
		ge.display();
		ui.processEvents();
	}

	return EXIT_SUCCESS;
}
