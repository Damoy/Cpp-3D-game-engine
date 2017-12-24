#pragma once

#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "GLM\glm.hpp"

#include "gameEngine\Configs.h"

/*
	The Window Manager !
	It handles all window-related functionalities such as window creation, window title setting...
*/
class WindowManager {
private:
	static GLFWwindow* window;
	static unsigned short width;
	static unsigned short height;
	static char* title;

	WindowManager();

	// setup the manager
	static void setup();
	// setup the gl version
	static void setupVersion();
	// setup the profil
	static void setupProfile();
	// setup the fbsc for the window
	static void setupFrameBufferSizeCallback();

	// may be required for mac
	static void macAdditionalSetup();

	// set the window viewport
	static void setViewport(unsigned short minW, unsigned short minH, unsigned short maxW, unsigned short maxH);
	// set the window size
	static void setSize(unsigned short width, unsigned short height);
	// set the window title
	static void setTitle(char* st);
	static void setIcon();

	// used by opengl
	static void frameBufferSizeCallback(GLFWwindow* window, int width, int height);

public:

	// initializes the manager
	static void initManager();
	// create the window
	static void createWindow(unsigned short width, unsigned short height, char* title);
	static void createWindow();

	// hide the mouse
	static void hideMouse();
	// (de)activate the Vertical synchronization
	static void activateVSync();
	static void deactivateVSync();

	// generate a projection matrix
	static glm::mat4 generateProjectionMatrix();

	// clean up the manager
	static void cleanUp();
	// should close the window
	static bool shouldClose();
	// close it
	static void closeWindow();

	static GLFWwindow* getWindow();
};

