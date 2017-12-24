#include "IntelligentTower.h"


IntelligentTower::IntelligentTower(Level* level, float x, float y, float z)
	: Tower(level, ModelBank::Models::intelligentTowerModel, Configs::INTELLIGENT_TOWER_LIFE, Configs::INTELLIGENT_TOWER_DAMAGE, Configs::INTELLIGENT_TOWER_ARMOR, x, y, z, 1.0f, 2.0f, 1.0f){

}

IntelligentTower::~IntelligentTower(){
}

/*
	Very simple hit method.
	Damage taken is dmg - (armor / 2).
	Yes, currently, the towers are not hit and so can't die
	(except if the user want it to), as I have no more time.
*/
bool IntelligentTower::hit(unsigned short dmg) {
	short rdmg = dmg;
	rdmg -= armor >> 1;
	life -= rdmg;

	if (life <= 0) {
		die();
		return false;
	}

	Logs::print("Intelligent tower life remaining: ", true, false);
	Logs::printG(life);
	Logs::print(", max life: ", false, false);
	Logs::printG(Configs::INTELLIGENT_TOWER_LIFE);
	Logs::println(".", false, true);

	return true;
}

/*
	Generate a projectile when it has to.
	Updates them and removes them if need to.
*/
void IntelligentTower::update() {
	generateProjectile();
	updateProjectiles();
	removeProjectiles();
}

/*
	Periodically generate a projectile;
*/
void IntelligentTower::generateProjectile() {
	if (generationTimer == nullptr) {
		generationTimer = new Timer(2000);
		generationTimer->start();
		return;
	}

	if (generationTimer->isStopped()) {
		// redo the timer if there is not close enemy
		Entity* closestAtFirst = level->getClosestEnemyInBox(position.x, position.y, position.z);
		if (closestAtFirst == nullptr) {
			generationTimer->reset();
			generationTimer->start();
			return;
		}

		// the projectile initial direction
		glm::vec3 projInitDir = closestAtFirst->getPosition() - position;

		// the new projectile
		Entity* projectile = new IntelligentTowerProjectile(level, position.x, position.y + 1.0f, position.z, this);

		// add it to the local projectiles
		projectiles->push_back(projectile);
		// add it to the game memory (mainly for rendering)
		GameMemory::addToProjectiles(projectile->getModel(), projectile);

		generationTimer->reset();
		generationTimer->start();
	}
}
