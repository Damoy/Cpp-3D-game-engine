#pragma once

#include "GLM\glm.hpp" // distance

#include "TowerProjectile.h"
#include "world\Level.h"

/*
	The SampleTower's projectiles.
	It knows its origin (apparition point),
	has a direction, destination and the current distance
	from the origin.
*/
class SampleTowerProjectile : public TowerProjectile{
private:
	// bound to not exceed
	const static float MAX_DISTANCE;
	glm::vec3 origin;
	glm::vec3 direction;
	float distance;
	glm::vec3 dest;

public:
	SampleTowerProjectile(Level* level, float x, float y, float z, float dirX, float dirY, float dirZ, glm::vec3 dest);
	SampleTowerProjectile(Level* level, float x, float y, float z, glm::vec3 direction, glm::vec3 dest);
	~SampleTowerProjectile();

	void update();
};

