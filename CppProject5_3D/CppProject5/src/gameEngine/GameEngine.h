#pragma once

#include <iostream>
#include <vector>

#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include "entities\Player.h"
#include "input\InputController.h"
#include "loaders\ModelLoader.h"
#include "renderEngine\WindowManager.h"
#include "renderEngine\MainRenderer.h"
#include "shaders\SampleShader.h"
#include "world\Map.h"
#include "world\World.h"

#include "STBI\stb_image.h"

/*
	The main GameEngine, contains the main game loop.
	Generates the MainRenderer, Player, World...
	This is the object to generate to create a game instance.
*/
class GameEngine{
private:

	// only way I found to execute a static method in a static context
	static void* initWindowReturnType;

	// the main renderer
	MainRenderer* renderer;
	// the main player
	Player* mainPlayer;

	// the main game world
	World* gameWorld;

	// used for movement calculations
	float deltaTime;
	float lastFrame;

	// initializes the world
	void initWorld();

	// the main game loop
	void mainGameloop();

	// updates the world
	void updateWorld() const;

	// clean up the engine
	void cleanUp() const;
	// used at engine destruction
	void deleteMemory();

public:

	// call the window manager,
	static void* initWindow();

	GameEngine();
	~GameEngine();

	// start the game
	void start();
};

