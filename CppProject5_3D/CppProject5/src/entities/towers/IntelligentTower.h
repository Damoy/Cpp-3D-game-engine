#pragma once

#include "Tower.h"
#include "entities\projectiles\IntelligentTowerProjectile.h"
#include "gameEngine\Configs.h"

/*
	The more complex tower. (Yes there are only two :D..)
	It generates "intelligent" projectiles that act as "researcher head".
*/
class IntelligentTower : public Tower{
public:
	IntelligentTower(Level* level, float x, float y, float z);
	~IntelligentTower();

	bool hit(unsigned short damage);
	void update();
	void generateProjectile();
};

