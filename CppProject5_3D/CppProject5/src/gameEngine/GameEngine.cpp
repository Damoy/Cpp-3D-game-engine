#include <cstdlib> // rand

#include "GameEngine.h"
#include "GameMemory.h"
#include "entities\towers\SampleTower.h"
#include "utils\logs\Logs.h"
#include "models\ModelBank.h"


// to glfwInit and glewInit before everything
void* GameEngine::initWindowReturnType = GameEngine::initWindow();

void* GameEngine::initWindow() {
	WindowManager::initManager();
	WindowManager::createWindow();
	WindowManager::activateVSync();

	return nullptr;
}

GameEngine::GameEngine(){

}

GameEngine::~GameEngine(){
	cleanUp();
	Logs::println("GameEngine cleaned up.");
	deleteMemory();
	Logs::println("GameEngine memory released.");
}


void GameEngine::start(){
	Logs::println("Game started.");
	initWorld();
	Logs::println("World initialized.");
	mainGameloop();
}

void GameEngine::initWorld() {
	// get a reference to the player singleton
	mainPlayer = Player::getInstance();

	// creates a world
	gameWorld = new World();
	// creates a projection matrix
	glm::mat4 projectionMatrix = WindowManager::generateProjectionMatrix();

	// initializes the input controller
	InputController::init(WindowManager::getWindow(), mainPlayer, gameWorld, projectionMatrix);
	// create a main renderer
	renderer = new MainRenderer(WindowManager::getWindow(), gameWorld, mainPlayer, projectionMatrix);

	deltaTime = 0.0f;
	lastFrame = 0.0f;
	Logs::println("World initialized.");
}

void GameEngine::mainGameloop(){

	// main loop
	// while the window is not closed
	while (!WindowManager::shouldClose()) {

		/* ------- Camera update ------- */
		// computes the time variation for the input controller
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		/* ------- Controls area ------- */
		InputController::update(deltaTime);

		/* ------- Update area ------- */
		updateWorld();

		/* ------- Rendering area ------- */
		renderer->render();

		/* ------- Checks if new potential events happened ------- */
		InputController::checkEvents();

	}

	/* --- Cleaning area --- */
	cleanUp();
}


void GameEngine::updateWorld() const {
	gameWorld->update();
}

void GameEngine::cleanUp() const{
	// cleans the renderers
	renderer->cleanUp();
	// cleans the window manager
	WindowManager::cleanUp();
}

void GameEngine::deleteMemory() {
	if (renderer != nullptr) {
		delete renderer;
		renderer = nullptr;
	}

	if (gameWorld != nullptr) {
		delete gameWorld;
		gameWorld = nullptr;
	}
}
