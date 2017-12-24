#pragma once

#include "Enemy.h"
#include "entities\Attacker.h"
#include "entities\Destructible.h"

/*
	The asteroid abstraction.
*/
class Asteroid : public Enemy{
protected:
	// the destination of the asteroid
	glm::vec3 dest;
	// its speed
	float speed;

public:
	Asteroid(TexturedModel* model, glm::vec3 dest, float x, float y, float z, float xScale, float yScale, float zScale, unsigned short life, unsigned short dps, unsigned short arm, float speed);
	~Asteroid();

};

