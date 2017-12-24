#pragma once

#include "Level.h"
#include "utils\time\Timer.h"

/*
	The main game level.
	I would like to add more but did not have the time.
*/
class Level1 : public Level{
private:
	// Generation periodicity
	const static unsigned int CREATION_MILLIS_DELAY = 6000;

	// The enemy model
	TexturedModel* enemyModel;
	// Generate entities
	void generate();
	// The generation timer
	Timer* creationTimer;

	// Generation methods
	void generateMap();
	void generateInitialEnemies();
	void generateSpawns();
	void generateEnemies();

public:
	Level1();
	~Level1();

	// Update methods
	void update();
	void updateEnemies();
	void updateCreations();
};

