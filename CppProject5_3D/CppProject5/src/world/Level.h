#pragma once

#include <map>
#include <vector>
#include "GLM\glm.hpp"
#include "entities\enemies\Enemy.h"
#include "gameEngine\GameMemory.h"
#include "loaders\ModelLoader.h"
#include "models\ModelBank.h"
#include "world\Map.h"

/*
	The main Level class.
	Should be used as an abstract class even if it
	does not have virtual pure methods.
	A level has a world position, size.
	It contains a map and entities, it is the unit
	responsible of updating them.
	It has a box that allows to know what entitities are close the level center.

*/
class Level{
protected:
	// can the level generate enemies
	bool canGenerateEnemies;
	// is the level ended
	bool end;

	// level sizes
	float width;
	float height;

	// the level stock of enemies
	short enemiesStock;
	// the amount of enemies present in the level box
	// before game over and level game / /level restart
	unsigned short maxEnemiesBeforeDeath;

	// the position
	glm::vec3 position;
	// the level map
	Map* levelMap;
	// the level "big box"
	AABB* box;

	// tower storage
	std::map<TexturedModel*, std::vector<Entity*>*>* texTowerMap;
	// enemy storage
	std::map<TexturedModel*, std::vector<Entity*>*>* texEnemiesMap;
	// projectiles storage
	std::map<TexturedModel*, std::vector<Entity*>*>* texProjectilesMap;

	// entities storages, towers, asteroids...
	std::vector<Entity*>* levelTowers;
	std::vector<Entity*>* sampleTowers;
	std::vector<TexturedModel*>* modelMemory;

	std::vector<Entity*>* asteroids;
	std::vector<Entity*>* projectiles;

	void checkCanGenerate();

	// Generate the level map
	virtual void generateMap() = 0;
	// Generate the level initial enemies
	virtual void generateInitialEnemies() = 0;

public:
	Level(float x, float y, float z, float w, float h, unsigned short asteroidsStock, unsigned short maxEnemiesBeforeDeath);
	~Level();

	// Get an enemy that collides with the source and that is in the level big box
	Enemy* checkEnemyCollisionInBox(Entity* source) const;

	// Get the first closest enemy and in the level box
	Entity* getClosestEnemyInBox(float x, float y, float z) const;
	// Get the first closest enemy which is not @param not and in the level box
	Entity* getClosestEnemyInBoxNot(float x, float y, float z, Entity* not) const;
	// Get a random of the closest enemies of a certain position and with a distance limit
	Entity* getRandomClosestEnemyInBox(float x, float y, float z, float dist) const;

	// Is the level finished
	bool isFinished() const;
	// Is the enemy stock empty
	bool isEnemyStockEmpty() const;
	// Does the level contains a certain entity
	bool contains(Entity* entity) const;

	// Updates the level
	virtual void update() = 0;

	// Remove dead enemies
	virtual void removeGameEnemies();
	// Check level end state
	virtual void checkEnd();

	// getters
	std::vector<TexturedModel*>* getModelMemory() const;
	std::vector<Entity*>* getTowers() const;
	std::map<TexturedModel*, std::vector<Entity*>*>* getTexTowerMap() const;

	std::vector<Entity*>* getAsteroids() const;
	std::map<TexturedModel*, std::vector<Entity*>*>* getTexEnemiesMap() const;

	std::vector<Entity*>* getProjectiles() const;
	std::map<TexturedModel*, std::vector<Entity*>*>* getTexProjectilesMap() const;

	Map* getMap() const;

	float getX() const;
	float getY() const;
	float getZ() const;

	float getWidth() const;
	float getHeight() const;
	AABB* getBigBox() const;
	unsigned short getMaxRows() const;
	unsigned short getMaxCols() const;

};

