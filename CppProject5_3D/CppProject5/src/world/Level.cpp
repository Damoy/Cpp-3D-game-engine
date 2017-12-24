#include <limits>

#include "Level.h"
#include "entities\enemies\Enemy.h"
#include "entities\enemies\Asteroid.h"

Level::Level(float x, float y, float z, float w, float h, unsigned short asteroidsMax, unsigned short maxEnemies)
	: position(glm::vec3(x, y, z)), width(w), height(h), enemiesStock(asteroidsMax), end(false), maxEnemiesBeforeDeath(maxEnemies){

	modelMemory = new std::vector<TexturedModel*>();
	sampleTowers = new std::vector<Entity*>();
	levelTowers = new std::vector<Entity*>();
	asteroids = new std::vector<Entity*>();
	projectiles = new std::vector<Entity*>();
	texTowerMap = new std::map<TexturedModel*, std::vector<Entity*>*>();
	texEnemiesMap = new std::map<TexturedModel*, std::vector<Entity*>*>();
	texProjectilesMap = new std::map<TexturedModel*, std::vector<Entity*>*>();

	checkCanGenerate();
	box = new AABB(position.x, position.y, position.z, position.x + (width * 2), (position.y + height * 2), position.z + (width * 2));
}

Entity* Level::getClosestEnemyInBox(float x, float y, float z) const {
	Entity* closest = nullptr;
	// max float possible value
	float minDist = std::numeric_limits<float>::max();
	glm::vec3 pos = position;

	for (Entity* asteroid : *asteroids) {
		if (!contains(asteroid))
			continue;

		float dist = glm::distance(pos, asteroid->getPosition());

		if (dist < minDist) {
			dist = minDist;
			closest = asteroid;
		}
	}

	return closest;
}

void Level::checkCanGenerate() {
	canGenerateEnemies = enemiesStock > 0;
}

Entity* Level::getClosestEnemyInBoxNot(float x, float y, float z, Entity* not) const {
	Entity* closest = nullptr;
	// max float possible value
	float minDist = std::numeric_limits<float>::max();
	glm::vec3 pos = position;

	// same as above but we don't check the not one
	for (Entity* asteroid : *asteroids) {
		if (asteroid == not)
			continue;

		if (!contains(asteroid))
			continue;

		float dist = glm::distance(pos, asteroid->getPosition());

		if (dist < minDist) {
			dist = minDist;
			closest = asteroid;
		}
	}

	return closest;
}

Entity* Level::getRandomClosestEnemyInBox(float x, float y, float z, float dist) const {
	int asize = static_cast<int>(asteroids->size());
	int rand = Maths::irand(0, asize - 1);
	int tries = glm::abs(asize - rand);
	int istart = asize - tries;

	if (istart < 0 || istart > asize)
		istart = 0;

	for (int tryy = istart; tryy < rand; tryy++) {
		Entity* asteroid = asteroids->at(tryy);
		float distance = glm::distance(glm::vec3(x, y, z), asteroid->getPosition());
		if (distance < dist)
			return asteroid;
	}

	return nullptr;
}

bool Level::contains(Entity* entity) const {
	return box->collide(*entity->getAABB());
}

// care, nullptr
Enemy* Level::checkEnemyCollisionInBox(Entity* source) const {
	std::vector<Entity*>::iterator asteroidsIT;

	for (asteroidsIT = asteroids->begin(); asteroidsIT != asteroids->end(); asteroidsIT++) {
		if (!contains(source))
			continue;

		Entity* asteroid = (*asteroidsIT);
		if (source->collide(asteroid))
			return dynamic_cast<Enemy*>(asteroid);
	}

	return nullptr;
}

void Level::removeGameEnemies() {
	std::map<TexturedModel*, std::vector<Entity*>*>* gameEnemies = GameMemory::getEnemies();
	std::map<TexturedModel*, std::vector<Entity*>*>::iterator geIT;

	for (geIT = gameEnemies->begin(); geIT != gameEnemies->end(); geIT++) {
		std::vector<Entity*>* entryEntities = (*geIT).second;
		// removes from rendering and places where gameEnemies is get
		GameMemory::eraseDeadDestructibles(entryEntities);
	}

	// level-local data
	// delete actual objects
	std::vector<Entity*>::iterator asteroidsIT;

	for (asteroidsIT = asteroids->begin(); asteroidsIT != asteroids->end();) {
		Entity* easteroid = (*asteroidsIT);
		Asteroid* asteroid = dynamic_cast<Asteroid*>(easteroid);

		if (easteroid == nullptr || asteroid == nullptr) {
			asteroidsIT++;
			continue;
		}
		else {
			if (asteroid->isAlive()) {
				asteroidsIT++;
				continue;
			}

			asteroidsIT = asteroids->erase(asteroidsIT);
			delete easteroid;
			easteroid = nullptr;
		}

	}
}

void Level::checkEnd() {
	unsigned int numberOfEnemiesInBox = 0;

	std::map<TexturedModel*, std::vector<Entity*>*>::iterator mapIT;
	std::map<TexturedModel*, std::vector<Entity*>*>* gameEnemies = GameMemory::getEnemies();

	for (mapIT = gameEnemies->begin(); mapIT != gameEnemies->end(); mapIT++) {
		std::vector<Entity*>* entryEntities = (*mapIT).second;
		std::vector<Entity*>::iterator vecIT;

		for (vecIT = entryEntities->begin(); vecIT != entryEntities->end(); vecIT++) {
			Entity* current = (*vecIT);
			if (contains(current))
				numberOfEnemiesInBox++;
		}
	}

	if (numberOfEnemiesInBox >= maxEnemiesBeforeDeath) {
		end = true;
	}
}

Level::~Level(){
	// delete aabb
	delete box;
	box = nullptr;

	// level allocation
	delete modelMemory;
	modelMemory = nullptr;

	delete sampleTowers;
	sampleTowers = nullptr;

	delete levelTowers;
	levelTowers = nullptr;

	delete asteroids;
	asteroids = nullptr;

	delete projectiles;
	projectiles = nullptr;

	delete texTowerMap;
	texTowerMap = nullptr;

	delete texEnemiesMap;
	texEnemiesMap = nullptr;

	delete texProjectilesMap;
	texProjectilesMap = nullptr;

}

bool Level::isEnemyStockEmpty() const {
	return enemiesStock <= 0;
}

float Level::getX() const { return position.x; }
float Level::getY() const { return position.y; }
float Level::getZ() const { return position.z; }
float Level::getWidth() const { return width; }
float Level::getHeight() const { return height; }
AABB* Level::getBigBox() const { return box; }

unsigned short Level::getMaxRows() const {
	if (levelMap == nullptr)
		return 0;
	return levelMap->getMaxRows();
}

unsigned short Level::getMaxCols() const {
	if (levelMap == nullptr)
		return 0;
	return levelMap->getMaxCols();
}

bool Level::isFinished() const { return end; }
Map* Level::getMap() const { return levelMap; }
std::vector<TexturedModel*>* Level::getModelMemory() const { return modelMemory; }
std::vector<Entity*>* Level::getTowers() const { return levelTowers; }
std::map<TexturedModel*, std::vector<Entity*>*>* Level::getTexTowerMap() const { return texTowerMap; }
std::vector<Entity*>* Level::getAsteroids() const { return asteroids; }
std::map<TexturedModel*, std::vector<Entity*>*>* Level::getTexEnemiesMap() const { return texEnemiesMap; }
std::vector<Entity*>* Level::getProjectiles() const { return projectiles; }
std::map<TexturedModel*, std::vector<Entity*>*>* Level::getTexProjectilesMap() const { return texProjectilesMap; }

