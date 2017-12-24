#include <algorithm>

#include "GameMemory.h"
#include "utils\checkers\Checker.h"
#include "utils\logs\Logs.h"
#include "entities\projectiles\Projectile.h"

// game maps
std::map<TexturedModel*, std::vector<Entity*>*>* GameMemory::towersMap = new std::map<TexturedModel*, std::vector<Entity*>*>();
std::map<TexturedModel*, std::vector<Entity*>*>* GameMemory::projectilesMap = new std::map<TexturedModel*, std::vector<Entity*>*>();
std::map<TexturedModel*, std::vector<Entity*>*>* GameMemory::enemiesMap = new std::map<TexturedModel*, std::vector<Entity*>*>();

// game entities storage
std::vector<Entity*>* GameMemory::enemies = new std::vector<Entity*>();
std::vector<Entity*>* GameMemory::towers = new std::vector<Entity*>();
std::vector<Entity*>* GameMemory::projectiles = new std::vector<Entity*>();

// tower selection
GameMemory::TowerSelected GameMemory::currentTowerSelected = GameMemory::SAMPLE;

GameMemory::TowerSelected GameMemory::getTowerSelected() {
	return currentTowerSelected;
}

GameMemory::TowerSelected GameMemory::setTowerSelected(GameMemory::TowerSelected towerSelected) {
	currentTowerSelected = towerSelected;
	return currentTowerSelected;
}

GameMemory::TowerSelected GameMemory::setTowerSelected(unsigned short towerSelected) {
	currentTowerSelected = (towerSelected == 0 ? SAMPLE : INTELLIGENT);
	return currentTowerSelected;
}

// Yes, that's bad, but running out of time
bool GameMemory::isProjectileDead(Entity* eproj) {
	Projectile* proj = dynamic_cast<Projectile*>(eproj);
	if (proj != nullptr)
		return !proj->isAlive();
	return false;
}

bool GameMemory::isDestructibleDead(Entity* entity) {
	if (entity == nullptr)
		return false;

	Destructible* destructible = dynamic_cast<Destructible*>(entity);
	if (destructible != nullptr)
		return !destructible->isAlive();
	return false;
}

void GameMemory::eraseDeadDestructibles(std::vector<Entity*>* entities) {
	entities->erase(std::remove_if(entities->begin(), entities->end(), isDestructibleDead), entities->end());
}

std::map<TexturedModel*, std::vector<Entity*>*>* GameMemory::getTowers() {
	return towersMap;
}

std::map<TexturedModel*, std::vector<Entity*>*>*GameMemory::getProjectiles() {
	return projectilesMap;
}

std::map<TexturedModel*, std::vector<Entity*>*>* GameMemory::getEnemies() {
	return enemiesMap;
}

// Add an entry to a map if the key does not already exist, appends the vector to the
// existing one otherwise
std::map<TexturedModel*, std::vector<Entity*>*>* GameMemory::addToMap(std::map<TexturedModel*, std::vector<Entity*>*>* map, TexturedModel* model, std::vector<Entity*>* entities) {

	std::map<TexturedModel*, std::vector<Entity*>*>::iterator lookingForModel = map->find(model);

	if (lookingForModel != map->end()) {
		std::vector<Entity*>* mapEntities = (*lookingForModel).second;
		mapEntities->insert(mapEntities->end(), entities->begin(), entities->end());
	}
	else {
		(*map)[model] = entities;
	}

	return map;
}

std::map<TexturedModel*, std::vector<Entity*>*>* GameMemory::addToMap(std::map<TexturedModel*, std::vector<Entity*>*>* map, TexturedModel* givenModel, Entity* entity) {

	// checking the given data
	Checker::assertNotNull(map, "Unknown map given !");
	Checker::assertNotNull(givenModel, "Unknown model given !");
	Checker::assertNotNull(entity, "Unknown entity given !");

	std::map<TexturedModel*, std::vector<Entity*>*>::iterator it;
	it = map->find(givenModel);
	// it means it found it
	if (it != map->end()) {
		std::vector<Entity*>* mapEntities = (*it).second;
		mapEntities->push_back(entity);
		return map;
	}

	// if the model was not already present
	// we add a new entry with a new vector containing the entity and the model

	// creating a new vector
	std::vector<Entity*>* newEntitiesEntry = new std::vector<Entity*>();
	// adding the wanted entity to it
	newEntitiesEntry->push_back(entity);

	//Logs::println("Added entity to new vector.");
	// adding to the map the new entry
	// there will be another find verification, yes...
	addToMap(map, givenModel, newEntitiesEntry);

	// last verification before returning it
	Checker::assertNotNull(map, "Map unknown !!");
	return map;
}

std::map<TexturedModel*, std::vector<Entity*>*>* GameMemory::addMapToMap(std::map<TexturedModel*, std::vector<Entity*>*>* in, std::map<TexturedModel*, std::vector<Entity*>*>* from) {

	Checker::assertNotNull(in, "Map dest unknown.");
	Checker::assertNotNull(from, "Map to add unknown.");

	std::map<TexturedModel*, std::vector<Entity*>*>::iterator it;

	for(it = in->begin(); it != in->end(); it++) {
		TexturedModel* model = (*it).first;
		std::vector<Entity*>* entities = (*it).second;

		addToMap(in, model, entities);
	}

	return in;
}

std::map<TexturedModel*, std::vector<Entity*>*>* GameMemory::addToTowers(TexturedModel* towerModel, Entity* tower) {
	return addToMap(towersMap, towerModel, tower);
}

std::map<TexturedModel*, std::vector<Entity*>*>* GameMemory::addToProjectiles(TexturedModel* projectileModel, Entity* projectile) {
	return addToMap(projectilesMap, projectileModel, projectile);
}

std::map<TexturedModel*, std::vector<Entity*>*>* GameMemory::addToEnemies(TexturedModel* enemyModel, Entity* enemy) {
	return addToMap(enemiesMap, enemyModel, enemy);
}

std::map<TexturedModel*, std::vector<Entity*>*>* GameMemory::addToTowers(TexturedModel* towersModel, std::vector<Entity*>* towers) {
	return addToMap(towersMap, towersModel, towers);
}

std::map<TexturedModel*, std::vector<Entity*>*>* GameMemory::addToProjectiles(TexturedModel* projectilesModel, std::vector<Entity*>* projectiles) {
	return addToMap(projectilesMap, projectilesModel, projectiles);
}

std::map<TexturedModel*, std::vector<Entity*>*>* GameMemory::addToEnemies(TexturedModel* enemiesModel, std::vector<Entity*>* enemies) {
	return addToMap(enemiesMap, enemiesModel, enemies);
}

std::map<TexturedModel*, std::vector<Entity*>*>* GameMemory::addMapToEnemies(std::map<TexturedModel*, std::vector<Entity*>*>* newData) {
	return addMapToMap(enemiesMap, newData);
}

std::map<TexturedModel*, std::vector<Entity*>*>* GameMemory::addMapToTowers(std::map<TexturedModel*, std::vector<Entity*>*>* newData) {
	return addMapToMap(towersMap, newData);
}

std::map<TexturedModel*, std::vector<Entity*>*>* GameMemory::addMapToProjectiles(std::map<TexturedModel*, std::vector<Entity*>*>* newData) {
	return addMapToMap(projectilesMap, newData);
}

// To Logs TowerSelected
std::ostream& operator<<(std::ostream& out, const GameMemory::TowerSelected value) {
	std::map<GameMemory::TowerSelected, std::string> strings;
	if (strings.size() == 0) {
		#define INSERT_ELEMENT(p) strings[p] = #p
		INSERT_ELEMENT(GameMemory::SAMPLE);
		INSERT_ELEMENT(GameMemory::INTELLIGENT);
		INSERT_ELEMENT(GameMemory::UNKNOWN);
		#undef INSERT_ELEMENT
	}

	return out << strings[value];
}

void GameMemory::deleteTower(TexturedModel* towerModel, Entity* tower) {
	Checker::assertNotNull(towerModel, "Tower model unknown !");
	Checker::assertNotNull(tower, "Tower unknown !");

	std::map<TexturedModel*, std::vector<Entity*>*>::iterator it = towersMap->find(towerModel);
	if (it != towersMap->end()) {
		std::vector<Entity*>* entry = (*it).second;
		std::vector<Entity*>::iterator vecIT = entry->begin();

		for (vecIT = entry->begin(); vecIT != entry->end();) {
			Entity* current = (*vecIT);
			if (current == tower) {
				vecIT = entry->erase(vecIT);
				delete current;
				current = nullptr;
			}
			else {
				vecIT++;
			}
		}

	}
	else {
		Logs::println("Could not delete tower.");
	}
}

// Deprecated, seems to make the game crash
void GameMemory::clearProjectiles() {
	std::map<TexturedModel*, std::vector<Entity*>*>::iterator it;
	for (it = projectilesMap->begin(); it != projectilesMap->end(); it++) {

		std::vector<Entity*>* entryProjs = (*it).second;
		std::vector<Entity*>::iterator entryIT;

		for (entryIT = entryProjs->begin(); entryIT != entryProjs->end();) {
			if ((*entryIT) != nullptr) {
				delete (*entryIT);
				(*entryIT) = nullptr;
				entryIT = entryProjs->erase(entryIT);
			}
			else {
				entryIT++;
			}
		}
	}
}

void GameMemory::reset() {
	enemies->clear();
	towers->clear();
	projectiles->clear();

	towersMap->clear();
	projectilesMap->clear();
	enemiesMap->clear();

	currentTowerSelected = SAMPLE;
}

