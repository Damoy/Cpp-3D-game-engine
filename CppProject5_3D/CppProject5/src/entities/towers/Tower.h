#pragma once

#include <vector>
#include "entities\Entity.h"
#include "entities\projectiles\TowerProjectile.h"
#include "utils\time\Timer.h"

/*
	A Tower is an Entity, is destructible and can attack.
	Currently, a tower is the only entity the user can place on the map.
	A tower should generate projectiles that have a certain behavior.
*/
class Tower : public Entity, public Destructible, public Attacker {
protected:
	// the level instance
	Level* level;
	// the timer used for projectile generation
	Timer* generationTimer;
	// the projectiles
	std::vector<Entity*>* projectiles;
	bool canUpdate;

public:
	Tower(Level* level, TexturedModel* model, unsigned short life, unsigned short uniqueDamage, unsigned short armor, float x, float y, float z, float xScale, float yScale, float zScale);
	~Tower();

	// remove dead projectiles from local vector
	void removeProjectiles();

	virtual bool hit(unsigned short dmg) = 0;
	virtual void generateProjectile() = 0;
	virtual void updateProjectiles();
	virtual void update();

};

