#include "UI.h"

/**
 \file UI.cpp
 \brief User interface processor for the program.

 \author    Don Spickler
 \version   1.1
 \date      8/17/2023

 */

/**
 \brief Constructor

 \param graph --- Pointer to the GraphicsEngine that this interface processor is attached.

 Simply stores the pointer of the GraphicsEngine.

 */

UI::UI(GraphicsEngine *graph) {
	ge = graph;
	mouseDown = false;
}

/**
 \brief Destructor

 No implementation needed at this point.

 */

UI::~UI() {
}

/**
 \brief The method handles the SFML event processing and calls the keyboard state processor
 method.

 This method processes all events in the current SFML event queue and calls the
 corresponding processing method.  At the end it calls the keyboard state processor
 method, outside the event loop.

 */

void UI::processEvents() {
	// Process user events
	sf::Event event;
	while (ge->pollEvent(event)) {
		// Close Window or Escape Key Pressed: exit
		if (event.type == sf::Event::Closed
				|| (event.type == sf::Event::KeyPressed
						&& event.key.code == sf::Keyboard::Escape))
			ge->close();

		// Key is pressed.
		if (event.type == sf::Event::KeyPressed)
			keyPressed(event.key);

		// Window is resized.
		if (event.type == sf::Event::Resized)
			ge->resize();

		if (event.type == sf::Event::MouseMoved)
			processMouseMoved(event.mouseMove);

		if (event.type == sf::Event::MouseButtonPressed)
			processMouseButtonPressed(event.mouseButton);

		if (event.type == sf::Event::MouseButtonReleased)
			processMouseButtonReleased(event.mouseButton);

	}

	// Process the state of the keyboard outside of event firing,
	keyboardStateProcessing();

}

/**
 \brief The method updates the theta and psi values of the spherical camera
 on a click and drag.

 \param mouseMoveEvent --- The SFML mouse move event structure.

 */

void UI::processMouseMoved(sf::Event::MouseMoveEvent mouseMoveEvent) {
	bool ctrldown = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::RControl);

	if (ge->isSphericalCameraOn() && mouseDown) {
		if (ctrldown || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
			ge->getSphericalCamera()->addR(
					(LastPosition.y - mouseMoveEvent.y) * 0.25);
		} else {
			ge->getSphericalCamera()->addTheta(
					(mouseMoveEvent.x - LastPosition.x) * degf * 10);
			ge->getSphericalCamera()->addPsi(
					(mouseMoveEvent.y - LastPosition.y) * degf * 10);
		}

		LastPosition.x = mouseMoveEvent.x;
		LastPosition.y = mouseMoveEvent.y;
	}
}

/**
 \brief On a left mouse click it will track the mouse down and tag the current position
 of the mouse as the last position the mouse was at.

 \param mouseButtonEvent --- The SFML mouse button event structure.

 */

void UI::processMouseButtonPressed(
		sf::Event::MouseButtonEvent mouseButtonEvent) {
	if (mouseButtonEvent.button == sf::Mouse::Left) {
		mouseDown = true;
		LastPosition.x = mouseButtonEvent.x;
		LastPosition.y = mouseButtonEvent.y;
	}
}

/**
 \brief If the left mouse button is released this method will track the release and
 exit any drag movement.

 \param mouseButtonEvent --- The SFML mouse button event structure.

 */

void UI::processMouseButtonReleased(
		sf::Event::MouseButtonEvent mouseButtonEvent) {
	if (mouseButtonEvent.button == sf::Mouse::Left) {
		mouseDown = false;
	}
}

/**
 \brief The function handles the keyboard input events from the user.

 \param keyevent --- The SFML key code for the key pressed.

 */

void UI::keyPressed(sf::Event::KeyEvent keyevent) {
	int key = keyevent.code;

	switch (key) {
	case sf::Keyboard::F1:
		ge->setDrawAxes(GL_TRUE);
		break;

	case sf::Keyboard::F2:
		ge->setDrawAxes(GL_FALSE);
		break;

	case sf::Keyboard::F10:
		ge->screenshot();
		break;

	case sf::Keyboard::F11:
		ge->setSphericalCameraOn();
		break;

	case sf::Keyboard::F12:
		ge->setYPRCameraOn();
		break;

	case sf::Keyboard::O:
		ge->openSimulationFile();
		break;

	case sf::Keyboard::Q:
		ge->incSimLength(-1);
		break;

	case sf::Keyboard::W:
		ge->incSimLength(1);
		break;

	case sf::Keyboard::E:
		ge->incSimLength(-10);
		break;

	case sf::Keyboard::R:
		ge->incSimLength(10);
		break;

	case sf::Keyboard::T:
		ge->incSimLength(-100);
		break;

	case sf::Keyboard::Y:
		ge->incSimLength(100);
		break;

	case sf::Keyboard::K:
		ge->resetSimLength();
		break;

	case sf::Keyboard::L:
		ge->resetSimLengthToEnd();
		break;

	case sf::Keyboard::Num1:
		ge->setColorScheme(1);
		break;

	case sf::Keyboard::Num2:
		ge->setColorScheme(2);
		break;

	case sf::Keyboard::Num3:
		ge->setColorScheme(3);
		break;

	case sf::Keyboard::Num4:
		ge->setColorScheme(4);
		break;

	case sf::Keyboard::H:
		ge->displayHelp();
		break;

	default:
		break;
	}
}

/**
 \brief Calls the respective method for key processing depending on
 which camera, spherical or yaw-pitch-roll, is currently selected.

 */

void UI::keyboardStateProcessing() {
	if (ge->isSphericalCameraOn())
		keyboardStateProcessingSphericalCamera();
	else
		keyboardStateProcessingYPRCamera();
}

/**
 \brief The method processes the keyboard state if the spherical camera is the one currently
 being used.

 */

void UI::keyboardStateProcessingSphericalCamera() {
	bool ctrldown = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::RControl);

	if (ctrldown || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			ge->getSphericalCamera()->addR(-0.1);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			ge->getSphericalCamera()->addR(0.1);
	} else {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			ge->getSphericalCamera()->addTheta(1);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			ge->getSphericalCamera()->addTheta(-1);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			ge->getSphericalCamera()->addPsi(1);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			ge->getSphericalCamera()->addPsi(-1);
	}
}

/**
 \brief The method processes the keyboard state if the yaw-pitch-roll camera is the
 one currently being used.

 */

void UI::keyboardStateProcessingYPRCamera() {
	bool ctrldown = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::RControl);
	bool shiftdown = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);

	if (shiftdown || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			ge->getYPRCamera()->moveRight(-0.1);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			ge->getYPRCamera()->moveRight(0.1);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			ge->getYPRCamera()->moveUp(0.1);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			ge->getYPRCamera()->moveUp(-0.1);
	} else if (ctrldown || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			ge->getYPRCamera()->addRoll(1);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			ge->getYPRCamera()->addRoll(-1);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			ge->getYPRCamera()->moveForward(0.1);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			ge->getYPRCamera()->moveForward(-0.1);
	} else {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			ge->getYPRCamera()->addYaw(1);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			ge->getYPRCamera()->addYaw(-1);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			ge->getYPRCamera()->addPitch(1);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			ge->getYPRCamera()->addPitch(-1);
	}
}
