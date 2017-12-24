#pragma once

#include "Projectile.h"
#include "world\Level.h"

/*
	The towers projectiles.
	Here, similar to Projectile.
*/
class TowerProjectile : public Projectile{
public:
	TowerProjectile(Level* level, TexturedModel* model, unsigned short life, unsigned short damage, unsigned short armor, float x, float y, float z, float size, float speed);
	~TowerProjectile();
	
	virtual void update();
};

