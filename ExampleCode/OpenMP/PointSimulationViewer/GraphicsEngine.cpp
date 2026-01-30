#include "GraphicsEngine.h"

/**
 \file GraphicsEngine.cpp
 \brief Main graphics driver for the program.

 This class extends sf::RenderWindow.

 \author    Don Spickler
 \version   1.1
 \date      8/17/2023

 */

/**
 \brief Constructor

 \param title --- Title to be placed in the titlebar of the graphics window.
 \param MajorVer --- The OpenGL major version that is requested.
 \param MinorVer --- The OpenGL minor version that is requested.
 \param width --- The width (in pixels) of the graphics window.
 \param height --- The height (in pixels) of the graphics window.

 Creates rendering window, loads the shaders, and sets some initial data settings.

 */

GraphicsEngine::GraphicsEngine(std::string title, GLint MajorVer,
		GLint MinorVer, int width, int height) :
		sf::RenderWindow(sf::VideoMode(width, height), title,
				sf::Style::Default,
				sf::ContextSettings(24, 8, 4, MajorVer, MinorVer,
						sf::ContextSettings::Core)) {

	//  Load the shaders
	std::string ccfrag = "#version 330 core\n"
			"uniform vec4 ConstantColor;\n"
			"out vec4 col;\n"
			"void main()\n"
			"{\n"
			"    col = ConstantColor;\n"
			"}\n";

	std::string frag = "#version 330 core\n"
			"in  vec4 color;\n"
			"out vec4 fColor;\n"
			"void main()\n"
			"{\n"
			"    fColor = color;\n"
			"}\n";

	std::string vert = "#version 330 core\n"
			"layout(location = 0) in vec4 position;\n"
			"layout(location = 1) in vec4 icolor;\n"
			"uniform mat4 Proj;\n"
			"uniform mat4 View;\n"
			"uniform mat4 Model;\n"
			"out vec4 color;\n"
			"void main()\n"
			"{\n"
			"    color = icolor;\n"
			"    gl_Position = Proj * View * Model * position;\n"
			"}\n";

	program = LoadShadersFromMemory(vert, frag);
	ccprogram = LoadShadersFromMemory(vert, ccfrag);

	if (!program || !ccprogram) {
		std::cerr << "Could not load Shader programs." << std::endl;
		exit(EXIT_FAILURE);
	}

	// Turn on the shader & get location of uniforms.
	glUseProgram(program);
	ProjLoc = glGetUniformLocation(program, "Proj");
	ViewLoc = glGetUniformLocation(program, "View");
	ModelLoc = glGetUniformLocation(program, "Model");

	glUseProgram(ccprogram);
	ccProjLoc = glGetUniformLocation(ccprogram, "Proj");
	ccViewLoc = glGetUniformLocation(ccprogram, "View");
	ccModelLoc = glGetUniformLocation(ccprogram, "Model");
	ccColorLoc = glGetUniformLocation(ccprogram, "ConstantColor");

	glGenVertexArrays(1, &simvboptr);

	// Initialize some data.
	mode = GL_FILL;
	CameraNumber = 1;
	drawAxes = GL_TRUE;
	drawManyBoxes = GL_TRUE;
	drawBoxes = GL_TRUE;

	// Set position of spherical camera
	sphcamera.setPosition(30, 30, 20);

	// Enable depth and cull face.
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	if (SetVS) {
		setVerticalSyncEnabled(true);
		setFramerateLimit(60);
	} else {
		setVerticalSyncEnabled(false);
		setFramerateLimit(0);
	}

	// Make it the active window for OpenGL calls, resize to set projection matrix.
	setActive();
	glClearColor(0, 0, 0, 1);
	windowtitle = title;

	resize();
}

/**
 \brief Destructor

 Clears the graphics card memory.

 */

GraphicsEngine::~GraphicsEngine() {
	glBindVertexArray(simvboptr);
	glDeleteBuffers(1, &simbufptr);
}

/**
 \brief The function responsible for drawing to the OpenGL frame buffer.

 This function clears the screen and draws the data streams.

 */

void GraphicsEngine::display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set view matrix via current camera.
	glm::mat4 view(1.0);
	if (CameraNumber == 1)
		view = sphcamera.lookAt();
	else if (CameraNumber == 2)
		view = yprcamera.lookAt();

	// Load view matrix to shaders.
	glUseProgram(program);
	glUniformMatrix4fv(ViewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUseProgram(ccprogram);
	glUniformMatrix4fv(ccViewLoc, 1, GL_FALSE, glm::value_ptr(view));

	// Set axes scaling.
	glm::mat4 axesscale = glm::scale(glm::mat4(1.0), glm::vec3(10, 10, 10));

	// Load matrix product to shaders.
	glUseProgram(program);
	glUniformMatrix4fv(ModelLoc, 1, GL_FALSE, glm::value_ptr(axesscale));
	if (drawAxes)
		coords.draw();

	if (simdata.size() > 0) {
		glUseProgram(ccprogram);
		glUniformMatrix4fv(ccModelLoc, 1, GL_FALSE,
				glm::value_ptr(glm::mat4(1.0)));

		glBindVertexArray(simvboptr);
		for (int i = 0; i < numparticles; i++) {
			if (colorscheme == 1) {
				glUniform4fv(ccColorLoc, 1,
						glm::value_ptr(glm::vec4(1, 1, 1, 1)));
			} else if (colorscheme == 2) {
				glUniform4fv(ccColorLoc, 1, glm::value_ptr(colors[i]));
			} else if (colorscheme == 3) {
				glUniform4fv(ccColorLoc, 1,
						glm::value_ptr(glm::vec4(0, 0, 0, 1)));
			} else {
				glUniform4fv(ccColorLoc, 1, glm::value_ptr(colors[i]));
			}

			glDrawArrays(GL_LINE_STRIP, i * numtimesteps, simlength);

		}
	}

	sf::RenderWindow::display();
	printOpenGLErrors();
}

/**
 \brief Changes the fill and line mode being used.

 */

void GraphicsEngine::changeMode() {
	if (mode == GL_FILL)
		mode = GL_LINE;
	else
		mode = GL_FILL;

	glPolygonMode(GL_FRONT_AND_BACK, mode);
}

/**
 \brief Saves a screenshot of the current display to a png file.

 */

void GraphicsEngine::screenshot() {
	const std::chrono::time_point<std::chrono::system_clock> now =
			std::chrono::system_clock::now();

	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);

	std::ostringstream oss;
	oss << "Screenshot_" << std::put_time(&tm, "%Y_%m_%d_%H_%M_%S") << "_"
			<< now.time_since_epoch().count() << ".png";
	std::string ssfilename = oss.str();

	sf::Vector2u windowSize = getSize();
	sf::Texture texture;
	texture.create(windowSize.x, windowSize.y);
	texture.update(*this);
	sf::Image img = texture.copyToImage();
	img.saveToFile(ssfilename.c_str());
}

/**
 \brief Handles the resizing events of the window.

 Sets the viewport to the entire screen and recalculates the projection matrix.
 */

void GraphicsEngine::resize() {
	glViewport(0, 0, getSize().x, getSize().y);
	projection = glm::perspective(50.0f * degf,
			(float) getSize().x / getSize().y, 0.01f, 500.0f);

	// Load projection matrix to shaders.
	glUseProgram(program);
	glUniformMatrix4fv(ProjLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUseProgram(ccprogram);
	glUniformMatrix4fv(ccProjLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

/**
 \brief Sets the size of the rendering window.

 \param width --- the width in pixels of the new size.
 \param height --- the height in pixels of the new size.

 */

void GraphicsEngine::setSize(unsigned int width, unsigned int height) {
	sf::RenderWindow::setSize(sf::Vector2u(width, height));
}

/**
 \brief Returns a pointer to the spherical camera.

 */

SphericalCamera* GraphicsEngine::getSphericalCamera() {
	return &sphcamera;
}

/**
 \brief Returns a pointer to the yaw-pitch-roll camera.

 */

YPRCamera* GraphicsEngine::getYPRCamera() {
	return &yprcamera;
}

/**
 \brief Prints all OpenGL errors to stderr.

 */

void GraphicsEngine::printOpenGLErrors() {
	GLenum errCode;
	const GLubyte *errString;

	while ((errCode = glGetError()) != GL_NO_ERROR) {
		errString = gluErrorString(errCode);
		fprintf(stderr, "OpenGL Error: %s\n", errString);
	}
}

/**
 \brief Prints the glm matrix to the console window.  Remember that glm
 matrices are column major.

 \param m --- the glm matrix to be displayed.

 */

void GraphicsEngine::print_GLM_Matrix(glm::mat4 m) {
	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 4; c++)
			printf("%7.2f", m[c][r]);

		std::cout << std::endl;
	}
	std::cout << std::endl;
}

/**
 \brief Returns true if the spherical camera is currently in use.

 \return True if the spherical camera is currently in use and false otherwise.

 */

GLboolean GraphicsEngine::isSphericalCameraOn() {
	return CameraNumber == 1;
}

/**
 \brief Turns the spherical camera on.

 */

void GraphicsEngine::setSphericalCameraOn() {
	CameraNumber = 1;
}

/**
 \brief Returns true if the yaw-pitch-roll camera is currently in use.

 \return True if the yaw-pitch-roll camera is currently in use and false otherwise.

 */

GLboolean GraphicsEngine::isYPRCameraOn() {
	return CameraNumber == 2;
}

/**
 \brief Turns the YPR camera on.

 */

void GraphicsEngine::setYPRCameraOn() {
	CameraNumber = 2;
}

/**
 \brief Sets the boolean to draw the axes or not.

 \param b --- Draws the axes if true and not if false.

 */

void GraphicsEngine::setDrawAxes(GLboolean b) {
	drawAxes = b;
}

/**
 \brief Sets the color scheme number to use.

 \param cs --- Color scheme number.

 */

void GraphicsEngine::setColorScheme(int cs) {
	colorscheme = cs;

	if (colorscheme == 1 || colorscheme == 2)
		glClearColor(0, 0, 0, 1);
	else
		glClearColor(1, 1, 1, 1);
}

/**
 \brief Opens and loads the simulation data file, loads the data to the graphics card,
 and sets the color vector for the multi-color data stream scheme.

 */

void GraphicsEngine::openSimulationFile() {
	char const *lFilterPatterns[1] = { "*.dat" };

	char *filename = tinyfd_openFileDialog("Open Simulation Data File", NULL, 1,
			lFilterPatterns, "Simulation Data File", 0);

	if (filename) {
		string filenamestr = filename;
		fstream datastream(filenamestr, ios::in | ios::binary);
		datastream.seekp(0L, ios::beg);
		Vec3 siminfo;
		datastream.read(reinterpret_cast<char*>(&siminfo), sizeof(siminfo));

		simdata.clear();
		Vec3 pt;
		datastream.read(reinterpret_cast<char*>(&pt), sizeof(pt));
		while (!datastream.eof()) {
			simdata.push_back(pt);
			datastream.read(reinterpret_cast<char*>(&pt), sizeof(pt));
		}

		datastream.close();
		numparticles = (int) (siminfo.getX() + 0.5);
		numtimesteps = (int) (siminfo.getY() + 0.5);

		GLfloat *dataarray = new GLfloat[3 * simdata.size()];

		for (int i = 0; i < numtimesteps; i++)
			for (int j = 0; j < numparticles; j++) {
				Vec3 pt = simdata[i * numparticles + j];

				int pos = j * numtimesteps + i;
				dataarray[3 * pos] = pt.getX();
				dataarray[3 * pos + 1] = pt.getY();
				dataarray[3 * pos + 2] = pt.getZ();
			}

		glBindVertexArray(simvboptr);
		glDeleteBuffers(1, &simvboptr);

		glBindVertexArray(simvboptr);
		glGenBuffers(1, &simvboptr);
		glBindBuffer(GL_ARRAY_BUFFER, simvboptr);
		glBufferData(GL_ARRAY_BUFFER, 3 * simdata.size() * sizeof(GLfloat),
		NULL, GL_STATIC_DRAW);

		glBufferSubData(GL_ARRAY_BUFFER, 0,
				3 * simdata.size() * sizeof(GLfloat), dataarray);
		glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0,
				BUFFER_OFFSET(0));

		glEnableVertexAttribArray(vPosition);
		delete[] dataarray;
	} else {
		cout << "Canceled: No file was loaded." << endl;
	}

	// Reset colors vector.
	colors.clear();
	colors.push_back(glm::vec4(1, 0, 0, 1));
	colors.push_back(glm::vec4(0, 1, 0, 1));
	colors.push_back(glm::vec4(0, 0, 1, 1));
	colors.push_back(glm::vec4(1, 1, 0, 1));
	colors.push_back(glm::vec4(1, 0, 1, 1));
	colors.push_back(glm::vec4(0, 1, 1, 1));
	colors.push_back(glm::vec4(0.5, 0, 0, 1));
	colors.push_back(glm::vec4(0, 0.5, 0, 1));
	colors.push_back(glm::vec4(0, 0, 0.5, 1));
	colors.push_back(glm::vec4(0.5, 0.5, 0, 1));
	colors.push_back(glm::vec4(0.5, 0, 0.5, 1));
	colors.push_back(glm::vec4(0, 0.5, 0.5, 1));

	while (colors.size() < numparticles)
		colors.push_back(glm::vec4(frand(), frand(), frand(), 1));

	resetSimLength();
}

/**
 \brief Returns a random double in the interval [0, 1).

 */

double GraphicsEngine::frand() {
	return 1.0 * rand() / RAND_MAX;
}

/**
 \brief Returns a random double in the interval [lb, ub).

 \param lb --- Lower bound.
 \param ub --- Upper bound.
 */

double GraphicsEngine::frand(double lb, double ub) {
	return frand() * (ub - lb) + lb;
}

/**
 \brief Increments the displayed simulation length by tsinc.

 \param tsinc --- Time-step increment.
 */

void GraphicsEngine::incSimLength(int tsinc) {
	simlength += tsinc;
	if (simlength < 1)
		simlength = 1;
	if (simlength > numtimesteps)
		simlength = numtimesteps;
	setTitlebar();
}

/**
 \brief Resets the displayed simulation to the first frame.
 */

void GraphicsEngine::resetSimLength() {
	simlength = 1;
	setTitlebar();
}

/**
 \brief Resets the displayed simulation to the last frame, hence displays the entire simulation.
 */

void GraphicsEngine::resetSimLengthToEnd() {
	simlength = numtimesteps;
	if (simlength < 1)
		simlength = 1;
	setTitlebar();
}

/**
 \brief Resets the title bar with the simulation information.
 */

void GraphicsEngine::setTitlebar() {
	char titlebar[1000];
	if (numtimesteps > 0)
		sprintf(titlebar, "%s   Frame: %d/%d   Particles: %d",
				windowtitle.c_str(), simlength, numtimesteps, numparticles);
	else
		sprintf(titlebar, "%s", windowtitle.c_str());
	setTitle(titlebar);
}

/**
 \brief Displays the help screen.
 */

void GraphicsEngine::displayHelp() {
	std::string message = "H: Display help screen.\n"
			"O: Open simulation data file.\n"
			"Esc: Ends the program.\n"
			"--------------------------\n"
			"F1: Turn axes on.\n"
			"F2: Turn axes off.\n"
			"F10: Take a screen shot.\n"
			"F11: Use spherical camera.\n"
			"F12: Use yaw-pitch-roll camera.\n"
			"--------------------------\n"
			"1: Sets the color scheme to black with white trails.\n"
			"2: Sets the color scheme to black with multi-color trails.\n"
			"3: Sets the color scheme to white with white black.\n"
			"4: Sets the color scheme to white with multi-color trails.\n"
			"--------------------------\n"
			"Q: Decrease simulation frame by 1.\n"
			"W: Increase simulation frame by 1.\n"
			"E: Decrease simulation frame by 10.\n"
			"R: Increase simulation frame by 10.\n"
			"T: Decrease simulation frame by 100.\n"
			"Y: Increase simulation frame by 100.\n"
			"K: Resets simulation to frame 1.\n"
			"L: Resets simulation to last frame.\n"
			"--------------------------\n"
			"If the spherical camera is currently selected: \n"
			"    If no modifier keys are pressed:\n"
			"        Left: Increases the theta value.\n"
			"        Right: Decreases the theta value.\n"
			"        Up: Increases the psi value.\n"
			"        Down: Decreases the psi value.\n"
			"    If the control or Z key is down:\n"
			"        Up: Decreases the radius.\n"
			"        Down: Increases the radius.\n"
			"--------------------------\n"
			"If the yaw-pitch-roll camera is currently selected: \n"
			"    If no modifier keys are pressed:\n"
			"        Left: Increases the yaw.\n"
			"        Right: Decreases the yaw.\n"
			"        Up: Increases the pitch.\n"
			"        Down: Decreases the pitch.\n"
			"    If the control or Z key is down:\n"
			"        Left: Increases the roll.\n"
			"        Right: Decreases the roll.\n"
			"        Up: Moves the camera forward.\n"
			"        Down: Moves the camera backward.\n"
			"    If the shift or S key is down:\n"
			"        Left: Moves the camera left.\n"
			"        Right: Moves the camera right.\n"
			"        Up: Moves the camera up.\n"
			"        Down: Moves the camera down.";

	int result = tinyfd_messageBox("Help", message.c_str(), "ok", "info", 0);
}

