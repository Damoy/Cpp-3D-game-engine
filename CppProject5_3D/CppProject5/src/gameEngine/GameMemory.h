#pragma once

#include <map>
#include <vector>
#include <string>
#include "entities\Entity.h"
#include "models\TexturedModel.h"

/*
	The GameMemory is an important class.
	It contains data to be renderer and to share between classes.
*/
class GameMemory{
public:

	// to get trace of the player tower selected
	typedef enum TowerSelected {
		SAMPLE = 0, INTELLIGENT = 1, UNKNOWN = 2
	}  TowerSelected;

	// for logging the tower selected
	friend std::ostream& operator<<(std::ostream& out, const TowerSelected value);

private:
	GameMemory();

	// the model - towers association
	static std::map<TexturedModel*, std::vector<Entity*>*>* towersMap;
	// the model - projectiles association
	static std::map<TexturedModel*, std::vector<Entity*>*>* projectilesMap;
	// the model - enemies association
	static std::map<TexturedModel*, std::vector<Entity*>*>* enemiesMap;

	// the game enemiess
	static std::vector<Entity*>* enemies;
	// the game towers
	static std::vector<Entity*>* towers;
	// the game projectiles
	static std::vector<Entity*>* projectiles;

	// tower selection
	static TowerSelected currentTowerSelected;

public:
	// Delete a tower of the memory
	static void deleteTower(TexturedModel* towerModel, Entity* tower);
	// Clear the projectiles
	static void clearProjectiles();

	// Get the current player's tower selected
	static TowerSelected getTowerSelected();
	// Set the current player's tower
	static TowerSelected setTowerSelected(TowerSelected towerSelected);
	static TowerSelected setTowerSelected(unsigned short towerSelected);

	// yes, it should be typed but I prefer not to, to facilitate
	// entities rendering
	// is the projectile dead
	static bool isProjectileDead(Entity* projectile);
	// is the destructible dead
	static bool isDestructibleDead(Entity* entity);
	// erase the dead entities
	static void eraseDeadDestructibles(std::vector<Entity*>* entities);

	// Getters of game entities
	static std::map<TexturedModel*, std::vector<Entity*>*>* getTowers();
	static std::map<TexturedModel*, std::vector<Entity*>*>* getProjectiles();
	static std::map<TexturedModel*, std::vector<Entity*>*>* getEnemies();

	// Add a tower to the memory
	static std::map<TexturedModel*, std::vector<Entity*>*>* addToTowers(TexturedModel* towerModel, Entity* tower);

	// Add a projectile to the memory
	static std::map<TexturedModel*, std::vector<Entity*>*>* addToProjectiles(TexturedModel* projectileModel, Entity* projectile);

	// Add an enemy to the memory
	static std::map<TexturedModel*, std::vector<Entity*>*>* addToEnemies(TexturedModel* enemyModel, Entity* enemy);

	// Add towers to the memory
	static std::map<TexturedModel*, std::vector<Entity*>*>* addToTowers(TexturedModel* towersModel, std::vector<Entity*>* towers);

	// Add projectiles to the memory
	static std::map<TexturedModel*, std::vector<Entity*>*>* addToProjectiles(TexturedModel* projectilesModel, std::vector<Entity*>* projectiles);

	// Add enemies to the memory
	static std::map<TexturedModel*, std::vector<Entity*>*>* addToEnemies(TexturedModel* enemiesModel, std::vector<Entity*>* enemies);

	// Shared methods to add to a map object
	static std::map<TexturedModel*, std::vector<Entity*>*>* addToMap(std::map<TexturedModel*, std::vector<Entity*>*>* map, TexturedModel* givenModel, Entity* entity);

	static std::map<TexturedModel*, std::vector<Entity*>*>* addToMap(std::map<TexturedModel*, std::vector<Entity*>*>* map, TexturedModel* model, std::vector<Entity*>* entities);

	static std::map<TexturedModel*, std::vector<Entity*>*>* addMapToMap(std::map<TexturedModel*, std::vector<Entity*>*>* in, std::map<TexturedModel*, std::vector<Entity*>*>* from);

	static std::map<TexturedModel*, std::vector<Entity*>*>* addMapToEnemies(std::map<TexturedModel*, std::vector<Entity*>*>* newData);

	static std::map<TexturedModel*, std::vector<Entity*>*>* addMapToTowers(std::map<TexturedModel*, std::vector<Entity*>*>* newData);

	static std::map<TexturedModel*, std::vector<Entity*>*>* addMapToProjectiles(std::map<TexturedModel*, std::vector<Entity*>*>* newData);

	// Reset the memory
	static void reset();

};

