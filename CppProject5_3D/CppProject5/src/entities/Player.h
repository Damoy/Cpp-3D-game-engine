#pragma once

#include <map>
#include "graphics\Camera.h"
#include "gameEngine\GameMemory.h"

/*
	The Player class.
	The Player is the user.
	In the game, there should be only one player as we
	make use of the singleton pattern.
	The main game user camera is the Player's camera.
	The Player has an amount of money, with which he can
	but towers to defend the map from enemies.
*/
class Player{
private:
	// singleton
	static Player* instance;
	// main game camera
	Camera* camera;

	// the count of player towers
	unsigned short totalTowerCount;
	// the number of asteroids that die thanks to the towers placed by the player
	unsigned int asteroidsDestroyed;
	// the player money
	int money;
	// used to know the count of towers placed
	std::map<GameMemory::TowerSelected, unsigned short>* towersCount;

	Player();
	~Player();
public:
	// get the singleton
	static Player* getInstance();

	// money setting
	int incMoney(unsigned int of);
	int incMoney();
	int decMoney(unsigned int of);
	int decMoney();

	// tower count setting
	void incTowerCount(GameMemory::TowerSelected of);
	void decTowerCount(GameMemory::TowerSelected of);

	void incAsteroidsDestroyed(unsigned int of);
	void incAsteroidsDestroyed();

	void incTotalTowerCount(unsigned short of);
	void decTotalTowerCount(unsigned short of);
	void incTotalTowerCount();
	void decTotalTowerCount();

	// getters
	unsigned short getTotalTowerCount() const;
	unsigned short getTowersCount(GameMemory::TowerSelected selectedTower) const;
	unsigned int getAsteroidsDestroyedCount() const;
	int getCurrentMoney() const;
	Camera* getCamera() const;

	// the player decides to start again from zero
	void reset();
};

