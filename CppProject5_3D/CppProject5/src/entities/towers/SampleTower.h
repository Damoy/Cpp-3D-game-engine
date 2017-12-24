#pragma once

#include "Tower.h"
#include "entities\projectiles\SampleTowerProjectile.h"
#include "utils\time\Timer.h"

/*
	The simpler tower. (Yes there are only two :D..)
	It generates sample projectiles that move to their initial destination
	until death.
*/
class SampleTower : public Tower{
public:
	SampleTower(Level* level, float x, float y, float z);
	~SampleTower();

	bool hit(unsigned short dmg);
	void update();
	void generateProjectile();
};


