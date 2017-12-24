#include "SampleTower.h"
#include "gameEngine\Configs.h"
#include "utils\logs\Logs.h"
#include "input\InputController.h"
#include "models\ModelBank.h"

// Similar to IntelligentTower

SampleTower::SampleTower(Level* level, float x, float y, float z)
	: Tower(level, ModelBank::Models::sampleTowerModel, Configs::SAMPLE_TOWER_LIFE, Configs::SAMPLE_TOWER_DAMAGE, Configs::SAMPLE_TOWER_ARMOR, x, y, z, 1.0f, 2.0f, 1.0f){
}

SampleTower::~SampleTower(){
}

bool SampleTower::hit(unsigned short dmg) {
	short rdmg = dmg;
	rdmg -= armor >> 1;
	life -= rdmg;

	if (life <= 0) {
		die();
		// false is dead
		return false;
	}

	Logs::print("Sample tower life remaining: ", true, false);
	Logs::printG(life);
	Logs::print(", max life: ", false, false);
	Logs::printG(Configs::SAMPLE_TOWER_LIFE);
	Logs::println(".", false, true);

	return true;
}

void SampleTower::update() {
	if (!isAlive())
		return;
	Destructible::update();
	generateProjectile();
	updateProjectiles();
	removeProjectiles();
}

void SampleTower::generateProjectile() {
	if (generationTimer == nullptr) {
		generationTimer = new Timer(2000);
		generationTimer->start();
		return;
	}

	if (generationTimer->isStopped()) {
		Entity* closestAtFirst = level->getClosestEnemyInBox(position.x, position.y, position.z);
		if (closestAtFirst == nullptr) {
			return;
		}

		glm::vec3 projInitDir = glm::normalize(closestAtFirst->getPosition() - position);

		Entity* projectile = new SampleTowerProjectile(level, position.x, position.y + 1.0f, position.z, projInitDir, closestAtFirst->getPosition());

		projectiles->push_back(projectile);
		GameMemory::addToProjectiles(projectile->getModel(), projectile);

		generationTimer->reset();
		generationTimer->start();
	}

}