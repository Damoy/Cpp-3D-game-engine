#include "Level2.h"
#include "entities\enemies\SampleAsteroid.h"
#include "utils\maths\Maths.h"
#include "input\InputController.h"


Level2::Level2()
	: Level(Configs::LEVEL2_X, Configs::LEVEL2_Y, Configs::LEVEL2_Z, Configs::LEVEL2_WIDTH, Configs::LEVEL2_HEIGHT, Configs::LEVEL2_ENEMIES_STOCK, Configs::LEVEL2_MAX_ASTEROIDS_BEFORE_DEATH) {

	Player::getInstance()->incMoney(Configs::LEVEL2_MONEY_BONUS);
	generateMap();
	generateInitialEnemies();
}

Level2::~Level2() {
	delete levelMap;
}

void Level2::generateMap() {
	levelMap = new Map(ModelBank::Textures::SAMPLE_MAP_TEXTURE_128x128, position.x, position.y, static_cast<unsigned short>(width), Configs::LEVEL2_MAP_VERTICES_COUNT);
}

void Level2::generateSpawns() {
	float bex1 = 100.0f;
	float bey1 = 1.0f;
	float bez1 = 100.0f;

	float bex2 = 100.0f;
	float bey2 = 1.0f;
	float bez2 = -100.0f;

	float bex3 = -100.0f;
	float bey3 = 1.0f;
	float bez3 = 100.0f;

	float bex4 = -100.0f;
	float bey4 = 1.0f;
	float bez4 = -100.0f;

	TexturedModel* spawnModel = ModelBank::Models::spawnModel;
	float spawnScale = Configs::SPAWN_SIZE;

	Entity* spawn1 = new Entity(spawnModel, bex1, bey1, bez1, spawnScale, spawnScale, spawnScale);
	Entity* spawn2 = new Entity(spawnModel, bex2, bey2, bez2, spawnScale, spawnScale, spawnScale);
	Entity* spawn3 = new Entity(spawnModel, bex3, bey3, bez3, spawnScale, spawnScale, spawnScale);
	Entity* spawn4 = new Entity(spawnModel, bex4, bey4, bez4, spawnScale, spawnScale, spawnScale);

	asteroids->push_back(spawn1);
	asteroids->push_back(spawn2);
	asteroids->push_back(spawn3);
	asteroids->push_back(spawn4);

	//GameMemory::addToEnemies(spawnModel, spawn1);
	//GameMemory::addToEnemies(spawnModel, spawn2);
	//GameMemory::addToEnemies(spawnModel, spawn3);
	//GameMemory::addToEnemies(spawnModel, spawn4);
}

void Level2::generateInitialEnemies() {
	enemyModel = ModelBank::Models::sampleAsteroidModel;
	generateSpawns();
	generateEnemies();
}

void Level2::update() {
	generate();
	levelMap->update();
	updateEnemies();
	updateCreations();
	removeGameEnemies();
	checkEnd();
}

void Level2::generate() {
	if (creationTimer == nullptr) {
		creationTimer = new Timer(CREATION_MILLIS_DELAY);
		creationTimer->start();
	}

	if (creationTimer->isStopped()) {
		generateEnemies();

		Logs::println("Level2 generated asteroids.");
		Logs::print("Asteroids left: ", true, false);
		Logs::printG(enemiesStock);
		Logs::println(false, true);

		creationTimer->reset();
		creationTimer->start();
	}
}

void Level2::generateEnemies() {
	if (!canGenerateEnemies)
		return;

	float x = getX();
	float y = getY();
	float z = getZ();

	int nbEnemiesGen = Maths::irand(4, 6);

	enemiesStock -= nbEnemiesGen;
	checkCanGenerate();

	float destX = getX() + (static_cast<unsigned short>(getWidth()) >> 1);
	float destY = 1.0f;
	float destZ = getZ() + (static_cast<unsigned short>(getWidth()) >> 1);

	// base enemy x
	int randPosSeed = Maths::irand(0, 4);

	float bex = 0.0f;
	float bey = 0.0f;
	float bez = 0.0f;
	float bes = 0.3f + Maths::frand(0.0f, 0.3f);

	if (randPosSeed == 0) {
		bex = x + 100.0f;
		bey = y + 1.0f;
		bez = z + 100.0f;
		Logs::println("First spawn.");
	}
	if (randPosSeed == 1) {
		bex = x + 100.0f;
		bey = y + 1.0f;
		bez = z - 100.0f;
		Logs::println("Second spawn.");
	}
	if (randPosSeed == 2) {
		bex = x - 100.0f;
		bey = y + 1.0f;
		bez = z + 100.0f;
		Logs::println("Third spawn.");
	}
	if (randPosSeed == 3) {
		bex = x - 100.0f;
		bey = y + 1.0f;
		bez = z - 100.0f;
		Logs::println("Fourth spawn.");
	}

	for (unsigned short i = 0; i < nbEnemiesGen; i++) {
		float ex = bex;
		float ey = bey;
		float ez = bez + (i * 1.5f);

		float wd2 = getWidth() * 0.5f;
		float randX = Maths::frand(-wd2, wd2);
		float randZ = Maths::frand(-wd2, wd2);
		float randY = Maths::frand(0.0f, 4.0f);

		float size = Maths::frand(0.5f, 1.5f);
		glm::vec3 dest = glm::vec3(destX + randX, destY + randY, randZ + destZ);
		Entity* asteroid = new SampleAsteroid(enemyModel, dest, ex, ey, ez, size);
		asteroids->push_back(asteroid);
		GameMemory::addToEnemies(enemyModel, asteroid);
	}

}


void Level2::updateEnemies() {
	std::vector<Entity*>::iterator it;

	for (it = asteroids->begin(); it != asteroids->end(); it++) {
		Entity* next = (*it);
		next->update();
	}
}

void Level2::updateCreations() {

	std::map<TexturedModel*, std::vector<Entity*>*>::iterator it;
	std::map<TexturedModel*, std::vector<Entity*>*>* towers = GameMemory::getTowers();

	for (it = towers->begin(); it != towers->end(); it++) {
		std::vector<Entity*>* entities = (*it).second;

		for (unsigned int i = 0; i < entities->size(); i++) {
			Entity* current = entities->at(i);
			current->update();
		}
	}

	// enemies
	std::map<TexturedModel*, std::vector<Entity*>*>* enemies = GameMemory::getEnemies();

	for (it = enemies->begin(); it != enemies->end(); it++) {
		std::vector<Entity*>* entities = (*it).second;

		for (unsigned int i = 0; i < entities->size(); i++) {
			Entity* current = entities->at(i);
			current->update();
		}
	}

}