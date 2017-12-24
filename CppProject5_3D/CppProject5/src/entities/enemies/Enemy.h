#pragma once

#include <vector>
#include "entities\Attacker.h"
#include "entities\Entity.h"
#include "entities\Destructible.h"

/*
	The enemy abstraction.
	An Enemy is an Entity that can attacked and be killed and that
	will act against a player.
*/
class Enemy : public Entity, public Destructible, public Attacker{
protected:
	// the entities hunting this enemy
	std::vector<Attacker*>* hunters;

public:
	Enemy(TexturedModel* model, float x, float y, float z, float xScale, float yScale, float zScale, unsigned short life, unsigned short dps, unsigned short arm);
	~Enemy();

	std::vector<Attacker*>* getHunters() const;

	// Does the enemy have a hunter attached to it which is not @param hunter .
	bool hasHunterNot(Attacker* hunter) const;

	// Attach a hunter
	void attachHunter(Attacker* hunter);

	// Detach one
	void detachHunter(Attacker* hunter);

	virtual void update();
};

