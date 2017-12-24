#include "World.h"
#include "entities\Player.h"


World::World()
	: levelFactory(LevelFactory::getInstance()), lastLevelInfoProvided(false){

	currentLevel = levelFactory->getNext();
	Checker::assertNotNull(currentLevel);
}

World::~World(){
}

void World::update() {
	currentLevel->update();
	checkResetLevels();
}

void World::checkLevel() {
	if (currentLevel != nullptr) {
		if (currentLevel->isEnemyStockEmpty()){
			updateLevel();
		}
	}
}

void World::updateLevel() {
	Level* nextLevel = levelFactory->getNext();
	if (nextLevel == nullptr) {
		if (!lastLevelInfoProvided) {
			Logs::println("It was the last world's level !");
			lastLevelInfoProvided = true;
		}
		return;
	}
	currentLevel = nextLevel;
}

void World::checkResetLevels() {
	if (currentLevel != nullptr && currentLevel->isFinished()) {
		GameMemory::reset();
		Player::getInstance()->reset();
		Level* next = levelFactory->reset();

		Logs::println("-- Game Over ! --");
		Logs::println("-- World reset --");
		if (next != nullptr) {
			currentLevel = next;
		}
	}
}

Level* World::getCurrentLevel() const { return currentLevel; }