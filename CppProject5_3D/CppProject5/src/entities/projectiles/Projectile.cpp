#include "Projectile.h"



Projectile::Projectile(Level* lvl, TexturedModel* model, unsigned short life, unsigned short uniqueDamage, unsigned short armor, float x, float y, float z, float xScale, float yScale, float zScale, float s)
	:	Entity(model, x, y, z, xScale, yScale, zScale),
		Destructible(life, armor),
		Attacker(uniqueDamage),
		level(lvl), speed(s){
}

Projectile::~Projectile(){
}


// Entity and Destructible updates
void Projectile::update() {
	Entity::update();
	Destructible::update();
}

