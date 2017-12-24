#include <algorithm>

#include "Tower.h"
#include "entities\enemies\Enemy.h"
#include "input\InputController.h"
#include "entities\projectiles\SampleTowerProjectile.h"
#include "entities\projectiles\TowerProjectile.h"


Tower::Tower(Level* lvl, TexturedModel* model, unsigned short life, unsigned short uniqueDamage, unsigned short armor, float x, float y, float z, float xScale, float yScale, float zScale)
	:	Entity(model, x, y, z, xScale, yScale, zScale),
		Destructible(life, armor),
		Attacker(uniqueDamage),
		level(lvl){
	
	projectiles = new std::vector<Entity*>(512);
	generationTimer = nullptr;
	canUpdate = true;
}

Tower::~Tower(){
	canUpdate = false;
}

void Tower::update() {
	Entity::update();
	Destructible::update();
}

void Tower::removeProjectiles() {
	// erase the dead projectiles from the local vector
	GameMemory::eraseDeadDestructibles(projectiles);
	
	// get the game projectiles and iterator over the map to erase the dead projectiles
	std::map<TexturedModel*, std::vector<Entity*>*>* gameProjs = GameMemory::getProjectiles();
	std::map<TexturedModel*, std::vector<Entity*>*>::iterator gpIT;

	for (gpIT = gameProjs->begin(); gpIT != gameProjs->end(); gpIT++) {
		std::vector<Entity*>* entryEntities = (*gpIT).second;
		GameMemory::eraseDeadDestructibles(entryEntities);
	}

}

void Tower::updateProjectiles() {
	for (auto* proj : *projectiles) {
		if (proj != nullptr) {
			proj->update();
		}
	}
}

