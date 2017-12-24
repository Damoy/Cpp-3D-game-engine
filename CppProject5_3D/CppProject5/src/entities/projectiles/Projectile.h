#pragma once

#include "entities\Attacker.h"
#include "entities\Entity.h"
#include "entities\Destructible.h"
#include "world\Level.h"

/*
	A project projectile.
	A Projectile is an Entity, it can hit (Attacker)
	but also can be killed (Destructible)
*/
class Projectile : public Entity, public Destructible, public Attacker{
protected:
	// the projectile speed
	float speed;
	// the level instance
	Level* level;

public:
	Projectile(Level* level, TexturedModel* model, unsigned short life, unsigned short uniqueDamage, unsigned short armor, float x, float y, float z, float xScale, float yScale, float zScale, float speed);
	~Projectile();

	virtual void update();

};

