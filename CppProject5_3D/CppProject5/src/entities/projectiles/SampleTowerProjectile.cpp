#include <iostream>
#include <algorithm> // find_if

#include "SampleTowerProjectile.h"
#include "utils\maths\Maths.h"
#include "entities\Entity.h"
#include "entities\enemies\Asteroid.h"
#include "entities\towers\Tower.h"
#include "entities\Player.h"
#include "shop\Shop.h"

const float SampleTowerProjectile::MAX_DISTANCE = 24.0f;

// Uses pre-loaded associated model
SampleTowerProjectile::SampleTowerProjectile(Level* level, float x, float y, float z, float dirX, float dirY, float dirZ, glm::vec3 destination)
	:	TowerProjectile(level, ModelBank::Models::sampleProjectileModel, 1, 1, 0, x, y, z, 1.0f, 0.05f),
		direction(glm::normalize(glm::vec3(dirX, dirY, dirZ))),
		origin(glm::vec3(x, y, z)),
		dest(destination){
}

SampleTowerProjectile::SampleTowerProjectile(Level* level, float x, float y, float z, glm::vec3 dir, glm::vec3 destination)
	: TowerProjectile(level, ModelBank::Models::sampleProjectileModel, 1, 1, 0, x, y, z, 1.0f, 0.05f),
	direction(glm::normalize(dir)),
	origin(glm::vec3(x, y, z)),
	dest(destination){
}

SampleTowerProjectile::~SampleTowerProjectile(){
}

// the projectile itself checks its own collision
// I prefer to do that as I am running out of time :/
void SampleTowerProjectile::update() {
	if (!isAlive())
		return;

	// checks projectile alive
	TowerProjectile::update();

	// set the current direction
	direction = dest - position;
	// calculate the next position
	glm::vec3 nextPos = position + (direction * speed);
	// get the enemies
	std::map<TexturedModel*, std::vector<Entity*>*>* gameEnemies = GameMemory::getEnemies();

	// yes collision is check with old position
	Enemy* collision = level->checkEnemyCollisionInBox(this);
	// if there is indeed a collision
	if (collision != nullptr) {
		Logs::println("Projectile collided enemy !");
		// hit the collision of the damage amount
		collision->hit(getDamage());
		Logs::println("Enemy hit !");

		// inc player money
		Shop::getInstance()->providePlayer(Player::getInstance(), GameMemory::SAMPLE);

		// hit myself of the enemy damage amount
		// hit should check if dead
		hit(collision->getDamage());
		Logs::println("Projectile hit too !");
		// if I am, return
		if (!isAlive())
			return;
	}

	// no collision
	else {
		// update the distance from the origin
		distance = glm::distance(nextPos, origin);
		if (distance >= MAX_DISTANCE) {
			// if exceeded, dies
			die();
			Logs::println("Projectile died cause of origin distance.");
			return;
		}

		// checking offset distance
		float dx = dest.x;
		float dy = dest.y;
		float dz = dest.z;
		float x = position.x;
		float y = position.y;
		float z = position.z;

		float offsetX = glm::abs(dx - x);
		float offsetY = glm::abs(dy - y);
		float offsetZ = glm::abs(dz - z);

		// if enemy not reached, but is close, dies
		if (offsetX <= width && offsetY <= height && offsetZ <= width) {
			die();
		}
		else {
			// finally updating the position
			position = nextPos;
		}

	}

	// update rotation
	incRot(Configs::ROT_45_RAD, Configs::ROT_45_RAD, Configs::ROT_45_RAD);
}