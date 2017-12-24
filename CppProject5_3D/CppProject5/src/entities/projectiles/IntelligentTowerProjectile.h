#pragma once

#include "TowerProjectile.h"
#include "utils\time\Timer.h"
#include "entities\towers\Tower.h"

/*
	The IntelligentTower's projectiles.
	It has a pray, and it knows its creator.
*/
class IntelligentTowerProjectile : public TowerProjectile{
private:
	// the projectile pray
	Enemy* pray;
	// the tower source
	Tower* source;
	// used to die in certain circumstances
	Timer* deathTimer;
	Timer* sourceDeathTimer;

public:
	IntelligentTowerProjectile(Level* level, float x, float y, float z, Tower* source);
	~IntelligentTowerProjectile();
	
	void update();
};

