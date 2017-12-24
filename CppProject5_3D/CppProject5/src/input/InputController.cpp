#include <iostream>

#include "InputController.h"
#include "renderEngine\WindowManager.h"
#include "utils\checkers\Checker.h"
#include "models\ModelBank.h"
#include "input\MouseTransformer.h"
#include "entities\towers\SampleTower.h"
#include "entities\towers\IntelligentTower.h"

#include "GLM\gtc\matrix_transform.hpp"

// Static attributes initialisation
GLFWwindow* InputController::window = nullptr;
Player* InputController::mainPlayer = nullptr;
Camera* InputController::playerCamera = nullptr;
World* InputController::world = nullptr;
Shop* InputController::shop = nullptr;

glm::mat4 InputController::projectionMatrix = glm::mat4();
float InputController::mouseX = Configs::WIDTH / 2.0f;
float InputController::mouseY = Configs::HEIGHT / 2.0f;
float InputController::mouseDX = 0.0f;
float InputController::mouseDY = 0.0f;
float InputController::rotX = 0.0f;
float InputController::rotY = 0.0f;
bool InputController::mouseEntered = true;
bool InputController::firstMouseHandling = true;
unsigned short InputController::towerSelected = 0;


void InputController::init(GLFWwindow* win, Player* player, World* wow, glm::mat4 proj) {
	Checker::assertNotNull(win, "Window unknown !");
	Checker::assertNotNull(player, "Player unknown !");
	Checker::assertNotNull(wow, "World unknown !");
	Checker::assertNotNull(player->getCamera(), "Player camera unknown !");

	window = win;
	mainPlayer = player;
	playerCamera = mainPlayer->getCamera();
	world = wow;
	projectionMatrix = proj;
	shop = Shop::getInstance();

	// Set the functions glfw will call
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, mouse_position_callback);
	glfwSetCursorEnterCallback(window, mouse_entered_callback);
}

void InputController::checkInput(float dTime) {
	handleCameraMovement(dTime);
	handleCameraRotation(dTime);
	handlePlayerSelection();
	handleClosingWindow();
}

void InputController::checkEvents() {
	glfwPollEvents();
}

void InputController::handleClosingWindow() {
	if (isPressed(GLFW_KEY_ESCAPE)) {
		WindowManager::closeWindow();
	}
}

void InputController::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	// Left click try to create a tower
	if (isLeftMouseButtonPressed()) {
		Logs::println("Mouse left button.");
		createTower();
	}

	// Middle click try to remove one
	if (isMiddleMouseButtonPressed()) {
		Logs::println("Mouse middle button.");
		deleteTower();
	}

	if (isRightMouseButtonPressed()) {
		Logs::println("Mouse right button.");
	}
}

void InputController::createTower() {
	// get the curren tlevel
	Level* level = world->getCurrentLevel();
	// GET THE MOUSE LEVEL COLLISION POINT
	glm::vec3 collisionPoint = MouseTransformer::getCollisionPointOnLevelMap(level, playerCamera, projectionMatrix);

	// if there is not, return
	if (MouseTransformer::isNull(collisionPoint))
		return;

	// player needs to buy the tower before use
	if (mainPlayer->getCurrentMoney() <= 0) {
		Logs::println("Not enough money !");
		return;
	}

	// position to select the tile
	Map* levelMap = level->getMap();
	float x = collisionPoint.x;
	float y = collisionPoint.y + 1.0f;
	float z = collisionPoint.z;

	// check bounds
	float minX = level->getX();
	float minY = level->getY();
	float minZ = level->getZ();
	float maxX = minX + level->getWidth();
	float maxZ = minZ + level->getWidth();

	// if out of bound return
	if (x < minX || x > maxX)
		return;
	if (z < minZ || z > maxZ)
		return;

	if (y < 1.0f) y = 1.0f;
	if (y > 1.0f) y = 1.0f;

	// get the tile at the position
	Tile* selected = levelMap->getTileAt(x, z);
	// is the tile already busy
	bool canSetEntity = !(selected->isBusy());

	// the selected tile, tiled coordinates
	unsigned short srow = selected->getRow();
	unsigned short scol = selected->getCol();
	// if out of bounds return
	if (srow >= level->getMaxRows() - 1|| scol >= level->getMaxCols() - 1)
		return;

	Logs::print("Tile selected, row: ", true, false);
	Logs::printG(srow);
	Logs::print(", col: ", false, false);
	Logs::printG(scol);
	Logs::println(false, true);

	// if the tile is busy return
	if (!canSetEntity) {
		Logs::println("Tile busy.");
		return;
	}

	// tower position
	float ex = static_cast<float>(srow * Map::TILE_SIZE + Map::TILE_SIZE);
	float ez = static_cast<float>(scol * Map::TILE_SIZE + Map::TILE_SIZE);

	// get the current tower type selected
	GameMemory::TowerSelected selection = GameMemory::getTowerSelected();

	// the player try to buy a tower in the shop and store into his inventory
	bool towerBought = shop->buyTower(selection, mainPlayer);
	// if he did not have enough money return
	if (!towerBought)
		return;

	Tower* newTower;

	// if the player tower stock is empty return
	unsigned int towerCount = mainPlayer->getTowersCount(selection);
	// does not have enough towers !
	if (towerCount <= 0) {
		Logs::println("Player tower stock is empty, try to select another tower !");
		return;
	}

	// generates a tower according to the current type selected
	// (type selection can be changed with C and V keywords)
	if (selection == GameMemory::SAMPLE) {
		newTower = new SampleTower(level, ex, y, ez);
	}
	else if (selection == GameMemory::INTELLIGENT) {
		newTower = new IntelligentTower(level, ex, y, ez);
	}
	else {
		newTower = new SampleTower(level, ex, y, ez);
	}

	// occupy the tile
	selected->setOccupier(newTower);

	// adding to game memory
	GameMemory::addToTowers(newTower->getModel(), newTower);

	// placing a tower diminutes the player storage
	mainPlayer->decTowerCount(selection);
}

void InputController::deleteTower() {
	Level* level = world->getCurrentLevel();
	glm::vec3 collisionPoint = MouseTransformer::getCollisionPointOnLevelMap(level, playerCamera, projectionMatrix);

	if (MouseTransformer::isNull(collisionPoint))
		return;

	Map* levelMap = level->getMap();
	float x = collisionPoint.x;
	float y = collisionPoint.y + 1.0f;
	float z = collisionPoint.z;

	// check bounds
	float minX = level->getX();
	float minY = level->getY();
	float minZ = level->getZ();
	float maxX = minX + level->getWidth();
	float maxZ = minZ + level->getWidth();

	if (x < minX || x > maxX)
		return;
	if (z < minZ || z > maxZ)
		return;

	if (y < 1.0f) y = 1.0f;
	if (y > 1.0f) y = 1.0f;

	Tile* selected = levelMap->getTileAt(x, z);
	bool busy = (selected->isBusy());
	if (!busy)
		return;

	unsigned short srow = selected->getRow();
	unsigned short scol = selected->getCol();
	if (srow >= level->getMaxRows() - 1 || scol >= level->getMaxCols() - 1)
		return;

	Logs::print("Tile selected, row: ", true, false);
	Logs::printG(srow);
	Logs::print(", col: ", false, false);
	Logs::printG(scol);
	Logs::println(false, true);

	float ex = static_cast<float>(srow * Map::TILE_SIZE + Map::TILE_SIZE);
	float ez = static_cast<float>(scol * Map::TILE_SIZE + Map::TILE_SIZE);

	// get occupier
	Entity* occupier = selected->getOccupier();
	// if the tile selected does not have tower on it, return
	if (occupier == nullptr)
		return;

	// free the occupied tile
	selected->setOccupier(nullptr);

	// check what was the tower's type
	SampleTower* sampleTow = dynamic_cast<SampleTower*>(occupier);
	IntelligentTower* intelligentTow = dynamic_cast<IntelligentTower*>(occupier);

	if (sampleTow != nullptr) {
		// recuperate the tower placing cost
		mainPlayer->incMoney(Configs::SAMPLE_TOWER_PRICE);
		Logs::print("Sample tower destroyed, gained ", true, false);
		Logs::printG(Configs::SAMPLE_TOWER_PRICE);
		Logs::println(" dollars.", false, true);

		// removing from game memory
		GameMemory::deleteTower(occupier->getModel(), occupier);
		//GameMemory::clearProjectiles();
	}

	if (intelligentTow != nullptr) {
		mainPlayer->incMoney(Configs::INTELLIGENT_TOWER_PRICE);
		Logs::print("Intelligent tower destroyed, gained ", true, false);
		Logs::printG(Configs::INTELLIGENT_TOWER_PRICE);
		Logs::println(" dollars.", false, true);

		// removing from game memory
		GameMemory::deleteTower(occupier->getModel(), occupier);
		//GameMemory::clearProjectiles();
	}

}

void InputController::mouse_position_callback(GLFWwindow* window, double xpos, double ypos) {
	float fxpos = static_cast<float>(xpos);
	float fypos = static_cast<float>(ypos);

	if (firstMouseHandling){
		mouseX = fxpos;
		mouseY = fypos;
		firstMouseHandling = false;
	}

	float xOffset = fxpos - mouseX;
	// reversed since y-coords go from bottom to top
	float yOffset = mouseY - fypos;

	mouseX = fxpos;
	mouseY = fypos;

	if(isRightMouseButtonPressed())
		playerCamera->processMouseMovement(xOffset, yOffset);
}

void InputController::mouse_entered_callback(GLFWwindow* window, int entered) {
	mouseEntered = entered != 0;
}

void InputController::update(float dTime) {
	checkInput(dTime);
}

bool InputController::isMouseButtonPressed(int button) {
	return glfwGetMouseButton(window, button) == GLFW_PRESS;
}

bool InputController::isLeftMouseButtonPressed() {
	return isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT);
}

bool InputController::isRightMouseButtonPressed() {
	return isMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT);
}

bool InputController::isMiddleMouseButtonPressed() {
	return isMouseButtonPressed(GLFW_MOUSE_BUTTON_MIDDLE);
}

void InputController::handleCameraMovement(float dTime) {

	// Handles the camera movement according to the input

	if (isKeyLeftPressed()) {
		playerCamera->processKeyboard(Camera::LEFT, dTime);
	}

	if (isKeyRightPressed()) {
		playerCamera->processKeyboard(Camera::RIGHT, dTime);
	}

	if (isKeyForwardPressed()) {
		playerCamera->processKeyboard(Camera::FORWARD, dTime);
	}

	if (isKeyBackwardPressed()) {
		playerCamera->processKeyboard(Camera::BACKWARD, dTime);
	}

	if (isKeyDownPressed()) {
		playerCamera->processKeyboard(Camera::DOWN, dTime);
	}

	if (isKeyUpPressed()) {
		playerCamera->processKeyboard(Camera::UP, dTime);
	}
}

void InputController::handleCameraRotation(float dTime) {
	// Rotates the camera
	if (InputController::isRightMouseButtonPressed()) {
		float rotX = getMouseRotX() * Configs::BASE_MOUSE_SENS;
		float rotY = getMouseRotY() * Configs::BASE_MOUSE_SENS;

		playerCamera->rotate(rotX, rotY);
	}
}

// Changes the camera tower selection
void InputController::handlePlayerSelection() {
	if (isPressed(GLFW_KEY_C)){
		towerSelected = 0;
	}

	if (isPressed(GLFW_KEY_V)) {
		towerSelected = 1;
	}

	GameMemory::setTowerSelected(towerSelected);
}

bool InputController::isPressed(int key) {
	return glfwGetKey(window, key) == GLFW_PRESS;
}

bool InputController::isKeyLeftPressed() {
	return isPressed(GLFW_KEY_LEFT) || isPressed(GLFW_KEY_Q) || isPressed(GLFW_KEY_A);
}

bool InputController::isKeyRightPressed() {
	return isPressed(GLFW_KEY_RIGHT) || isPressed(GLFW_KEY_D);
}

bool InputController::isKeyUpPressed() {
	return isPressed(GLFW_KEY_SPACE);
}

bool InputController::isKeyDownPressed() {
	return isPressed(GLFW_KEY_LEFT_CONTROL);
}

bool InputController::isKeyForwardPressed() {
	return isPressed(GLFW_KEY_UP) || isPressed(GLFW_KEY_W) || isPressed(GLFW_KEY_Z);
}

bool InputController::isKeyBackwardPressed() {
	return isPressed(GLFW_KEY_DOWN) || isPressed(GLFW_KEY_S);
}

// getters
float InputController::getMouseDX() { return mouseDX; }
float InputController::getMouseDY() { return mouseDY; }
float InputController::getMouseRotX() { return rotX; }
float InputController::getMouseRotY() { return rotY; }
glm::vec2 InputController::getMousePosition() { return glm::vec2(mouseX, mouseY); }
