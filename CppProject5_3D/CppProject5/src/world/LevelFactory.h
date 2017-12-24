#pragma once

#include <vector>
#include "Level1.h"
#include "Level2.h"

/*
	Factory responsible of the level generation.
	Implemented late, could be more advanced and powerful.
*/
class LevelFactory{
private:
	static LevelFactory* instance;
	LevelFactory();
	~LevelFactory();

	unsigned short levelCounter;
	unsigned short levelsCount;
	std::vector<Level*>* preGeneratedLevels;

public:
	static LevelFactory* getInstance();

	bool hasNext() const;
	// Get the next level
	Level* getNext();
	// Reset the factory
	Level* reset();
};

