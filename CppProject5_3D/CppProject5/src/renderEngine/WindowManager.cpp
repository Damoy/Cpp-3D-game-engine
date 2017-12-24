#include <iostream>

#include "WindowManager.h"
#include "utils\logs\Logs.h"
#include "utils\checkers\Checker.h"
#include "utils\maths\Maths.h"

GLFWwindow* WindowManager::window = nullptr;
unsigned short WindowManager::width = 0;
unsigned short WindowManager::height = 0;
char* WindowManager::title = nullptr;

void WindowManager::setup() {
	setupVersion();
	setupProfile();

	#ifdef __APPLE__
	macAdditionalSetup();
	#endif // __APPLE__

}

void WindowManager::setupVersion() {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
}

void WindowManager::setupProfile() {
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void WindowManager::macAdditionalSetup() {
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

void WindowManager::initManager() {
	glfwInit();
	Logs::println("GLFW initialised.");
	setup();
}

void WindowManager::createWindow(unsigned short width, unsigned short height, char* title) {
	setSize(width, height);
	setTitle(title);
	window = glfwCreateWindow(width, height, title, nullptr, nullptr);

	if (window == nullptr) {
		Logs::println("Failed to create GLFW Window !");
		cleanUp();
		return;
	}

	glfwMakeContextCurrent(window);
	setupFrameBufferSizeCallback();
	hideMouse();

	// needs this to work
	glewExperimental = GL_TRUE;
	glewInit();
	Logs::println("GLEW initialised.");
	Logs::println(false, false);
}

void WindowManager::createWindow() {
	createWindow(Configs::WIDTH, Configs::HEIGHT, Configs::TITLE);
}

void WindowManager::setViewport(unsigned short minW, unsigned short minH, unsigned short maxW, unsigned short maxH) {
	glViewport(minW, minH, maxW, maxH);
}

void WindowManager::setSize(unsigned short uwidth, unsigned short uheight) {
	width = uwidth;
	height = uheight;
}

void WindowManager::setTitle(char* tt) {
	title = tt;
}

void WindowManager::hideMouse() {
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

glm::mat4 WindowManager::generateProjectionMatrix() {
	return Maths::generateProjectionMatrix(Configs::FOV, Configs::ASPECT_RATIO, Configs::NEAR_PLANE, Configs::FAR_PLANE);
}

void WindowManager::frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
	setViewport(0, 0, width, height);
}

void WindowManager::setupFrameBufferSizeCallback() {
	Checker::checkWindowAlive(window);
	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
}

void WindowManager::activateVSync() {
	glfwSwapInterval(1);
}

void WindowManager::deactivateVSync() {
	glfwSwapInterval(0);
}

bool WindowManager::shouldClose() {
	return glfwWindowShouldClose(window) != 0;
}

void WindowManager::cleanUp() {
	glfwTerminate();
}

GLFWwindow* WindowManager::getWindow() {
	Checker::checkWindowAlive(window);
	return window;
}

void WindowManager::setIcon() {
	// glfwSetWindowIcon(...);
}

void WindowManager::closeWindow() {
	Checker::checkWindowAlive(window);
	glfwSetWindowShouldClose(window, true);
}