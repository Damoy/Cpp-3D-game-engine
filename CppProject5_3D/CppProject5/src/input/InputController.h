#pragma once
#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include "entities\Player.h"
#include "entities\graphics\Camera.h"
#include "world\World.h"
#include "gameEngine\Configs.h"
#include "shop\Shop.h"

/*
	The InputController, controls everything about user input.
	Everything is static because we need mouse_button_callback
	to be static.
*/
class InputController{
private:
	// a reference to the main game's window
	static GLFWwindow* window;
	// the main player
	static Player* mainPlayer;
	// its camera
	static Camera* playerCamera;
	// the main world
	static World* world;
	// the player shop
	static Shop* shop;

	// did the mouse entered the window
	static bool mouseEntered;
	// is it the first time we handle the mouse
	static bool firstMouseHandling;

	// mouse position
	static float mouseX;
	static float mouseY;
	// mouse position variation
	static float mouseDX;
	static float mouseDY;
	static float rotX;
	static float rotY;

	// opengl methods required to handle the mouse

	// mouse buttons
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	// mouse position
	static void mouse_position_callback(GLFWwindow* window, double xpos, double ypos);
	static void mouse_entered_callback(GLFWwindow* window, int entered);

	// controller process

	// Handle the camera movement, takes the time variation
	static void handleCameraMovement(float dTime);
	// Handle the camera rotation, takes the time variation
	static void handleCameraRotation(float dTime);
	// Handle the player tower selection
	static void handlePlayerSelection();
	// Closes the window
	static void handleClosingWindow();

	InputController();

	// Try to create a player's tower
	static void createTower();
	// Try to remove a player's tower
	static void deleteTower();
	// 
	static unsigned short towerSelected;

public:
	// The projection matrix
	static glm::mat4 projectionMatrix;

	// initializes the controller
	static void init(GLFWwindow* window, Player* player, World* world, glm::mat4 projectionMatrix);

	// keyboad

	// Is the key pressed
	static bool isPressed(int key);

	// Is a left key pressed (A, Q, LEFT)
	static bool isKeyLeftPressed();
	// Is a right key pressed (D, RIGHT)
	static bool isKeyRightPressed();
	// Is a up key pressed (SPACE)
	static bool isKeyUpPressed();
	// Is a down key pressed (S, DOWN)
	static bool isKeyDownPressed();
	// Is a forward key pressed (W, Z, UP)
	static bool isKeyForwardPressed();
	// Is a backward key pressed (S, DOWN)
	static bool isKeyBackwardPressed();

	// mouse

	// Is a mouse button pressed
	static bool isMouseButtonPressed(int button);
	// The left one ?
	static bool isLeftMouseButtonPressed();
	// The right one ?
	static bool isRightMouseButtonPressed();
	// The middle one ?
	static bool isMiddleMouseButtonPressed();

	// Get the mouse position variation
	static float getMouseDX();
	static float getMouseDY();

	// The the mouse position
	static glm::vec2 getMousePosition();

	// Get the mouse rotation 
	static float getMouseRotX();
	static float getMouseRotY();
	
	// others

	// Check the user input, takes the time variation
	static void checkInput(float dTime);
	static void update(float dTime);
	// Checks if new events user input happened
	static void checkEvents();

};

