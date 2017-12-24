#pragma once

#include "entities\Player.h"
#include "gameEngine\GameMemory.h"

/*
	The only simple shop !
	The player use it to buy towers.
*/
class Shop{
private:
	Shop();
	// singleton
	static Shop* instance;

	// costs information
	std::map<GameMemory::TowerSelected, unsigned int>* costs;
public:
	// get the singleton
	static Shop* getInstance();

	// A client buy a certain tower
	bool buyTower(GameMemory::TowerSelected towerType, Player* client) const;
	// A client buy a sample tower
	bool buySampleTower(Player* client) const;
	// A client buy an intelligent tower
	bool buyIntelligentTower(Player* client) const;
	// Restaures to the player the money used after buying a tower.
	void providePlayer(Player* player, GameMemory::TowerSelected tower);

};


