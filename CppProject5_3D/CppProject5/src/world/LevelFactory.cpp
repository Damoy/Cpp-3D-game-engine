#include "LevelFactory.h"

LevelFactory* LevelFactory::instance = nullptr;

LevelFactory::LevelFactory()
	: levelCounter(0){

	// Removed level2 because of chaining problems
	preGeneratedLevels = new std::vector<Level*>();
	Level1* level1 = new Level1();
	//Level2* level2 = new Level2();
	preGeneratedLevels->push_back(level1);
	//preGeneratedLevels->push_back(level2);
	levelsCount = static_cast<unsigned short>(preGeneratedLevels->size());
}

LevelFactory::~LevelFactory(){
	std::vector<Level*>::iterator it;

	for (it = preGeneratedLevels->begin(); it != preGeneratedLevels->end(); it++) {
		Level* level = (*it);
		if (level != nullptr) {
			delete level;
			level = nullptr;
		}
	}

	delete preGeneratedLevels;
}

LevelFactory* LevelFactory::getInstance() {
	if (instance == nullptr)
		instance = new LevelFactory();
	return instance;
}

Level* LevelFactory::getNext() {
	if (levelCounter >= levelsCount) {
		return nullptr;
	}

	Level* current = preGeneratedLevels->at(levelCounter);

	if (dynamic_cast<Level1*>(current) != nullptr) {
		Logs::println(">>> LEVEL 1 <<< ");
	}
	else if (dynamic_cast<Level2*>(current) != nullptr) {
		Logs::println(">>> LEVEL 2 <<< ");
	}

	levelCounter++;
	return current;
}

Level* LevelFactory::reset() {
	if (preGeneratedLevels == nullptr)
		return nullptr;

	std::vector<Level*>::iterator lvlIT;
	for (lvlIT = preGeneratedLevels->begin(); lvlIT != preGeneratedLevels->end(); lvlIT++) {
		delete (*lvlIT);
		(*lvlIT) = nullptr;
	}

	preGeneratedLevels->clear();
	Level1* level1 = new Level1();
	//Level2* level2 = new Level2();
	preGeneratedLevels->push_back(level1);
	//preGeneratedLevels->push_back(level2);
	levelsCount = static_cast<unsigned short>(preGeneratedLevels->size());
	return getNext();
}

bool LevelFactory::hasNext() const {
	return levelCounter < levelsCount;
}