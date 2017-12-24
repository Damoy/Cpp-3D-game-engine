#pragma once

#include "Level.h"
#include "utils\time\Timer.h"

// Similar to Level1 but unused as I got level chaining problems
class Level2 : public Level {
private:
	const static unsigned int CREATION_MILLIS_DELAY = 6000;

	TexturedModel* enemyModel;
	void generate();
	Timer* creationTimer;

	void generateMap();
	void generateInitialEnemies();
	void generateSpawns();
	void generateEnemies();

public:
	Level2();
	~Level2();

	void update();
	void updateEnemies();
	void updateCreations();
};

