#include "TowerProjectile.h"



TowerProjectile::TowerProjectile(Level* level, TexturedModel* model, unsigned short life, unsigned short damage, unsigned short armor, float x, float y, float z, float size, float speed)
	: Projectile(level, model, life, damage, armor, x, y, z, size, size, size, speed){
}

TowerProjectile::~TowerProjectile(){
}

void TowerProjectile::update() {
	Projectile::update();
}

