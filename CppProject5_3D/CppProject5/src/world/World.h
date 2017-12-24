#pragma once

#include "LevelFactory.h"

/*
	The world has a certain level at a certain time.
*/
class World{
private:
	// current level
	Level* currentLevel;
	// level provider
	LevelFactory* levelFactory;
	bool lastLevelInfoProvided;

public:
	World();
	~World();

	Level* getCurrentLevel() const;
	void update();
	void updateLevel();

	void checkLevel();
	void checkResetLevels();
};

