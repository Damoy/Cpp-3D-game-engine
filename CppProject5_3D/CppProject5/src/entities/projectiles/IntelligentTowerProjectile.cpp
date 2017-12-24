#include "IntelligentTowerProjectile.h"
#include "utils\maths\Maths.h"
#include "entities\enemies\Asteroid.h"
#include "entities\Player.h"
#include "shop\Shop.h"

// Uses pre-loaded associated model
IntelligentTowerProjectile::IntelligentTowerProjectile(Level* level, float x, float y, float z, Tower* father)
		: TowerProjectile(level, ModelBank::Models::intelligentProjectileModel, 1, 1, 0, x, y, z, 1.0f, 0.05f),
		pray(nullptr), deathTimer(nullptr), source(father){
}

IntelligentTowerProjectile::~IntelligentTowerProjectile(){
}

void IntelligentTowerProjectile::update() {
	if (!isAlive())
		return;

	// if colliding with its source
	// should not stay here long, dies otherwise
	if (collide(source)) {
		if (sourceDeathTimer == nullptr) {
			sourceDeathTimer = new Timer(2000);
			sourceDeathTimer->start();
			return;
		}

		// dies at the timer end if it has been launched
		if (sourceDeathTimer->isStopped()) {
			delete sourceDeathTimer;
			die();
			Logs::println("Intel proj died at source death timer end");
			return;
		}
	}

	// projectiles with no goal staying at level start point
	if ((position.x >= -0.5f && position.x <= 0.5f) ||
		(position.z >= -0.5f && position.z <= 0.5f)){
		if (deathTimer == nullptr) {
			deathTimer = new Timer(2000);
			deathTimer->start();
			return;
		}

		// dies at the timer end if it has been launched
		if (deathTimer->isStopped()) {
			delete deathTimer;
			die();
			Logs::println("Intel proj died at death timer end.");
			return;
		}
	}

	// super update
	TowerProjectile::update();

	glm::vec3 dir = glm::vec3(0.0f, 0.0f, 0.0f);
	if (pray == nullptr) {
		// if the pray is null
		// get the closest enemy in the level box
		Entity* closestAsteroid = level->getClosestEnemyInBox(position.x, position.y, position.z);

		// if there is one
		if (closestAsteroid != nullptr) {
			// for hunting related
			Enemy* cclosestAsteroid = dynamic_cast<Enemy*>(closestAsteroid);

			// if the closest has already a hunter, try to found another closest
			if (cclosestAsteroid != nullptr && cclosestAsteroid->hasHunterNot(this)) {
				Enemy* anotherClosest = dynamic_cast<Enemy*>(level->getClosestEnemyInBoxNot(position.x, position.y, position.z, cclosestAsteroid));

				if (anotherClosest == nullptr || !anotherClosest->hasHunterNot(this)) {
					// get a closest enemy which is in the level area
					Enemy* randOne = dynamic_cast<Enemy*>(level->getRandomClosestEnemyInBox(position.x, position.y, position.z, (level->getWidth() * 0.5f)));
					// can't live without goal anymore :D
					if (randOne == nullptr || randOne->hasHunterNot(this) || randOne == cclosestAsteroid || randOne == anotherClosest) {
						Logs::println("Intel proj died cause no goal.");
						die();
						return;
					}
					anotherClosest = randOne;
				}

				// updating the pray
				cclosestAsteroid = anotherClosest;
			}

			// updating direction
			dir = glm::normalize((closestAsteroid->getPosition() - position));

			if (cclosestAsteroid != nullptr) {
				cclosestAsteroid->attachHunter(this);

				// detach old
				Checker::assertTrue(pray == nullptr, "Here, we expect that the pray is null.");

				// update pray
				pray = cclosestAsteroid;
			}
		}
	}

	else {
		// if the projectile has a pray,
		// it will follow it until death
		// updating direction
		dir = glm::normalize((pray->getPosition() - position));
	}

	// calculate the next position by adding to the current one
	// the glm::vec3 result of the direction and the projectile speed multiplication
	glm::vec3 nextPos = position + (dir * speed);

	// yes collision is check with old position
	Enemy* collision = level->checkEnemyCollisionInBox(this);
	// if there is indeed a collision
	if (collision != nullptr) {
		Logs::println("Projectile collided enemy !");
		// hit the collision of the damage amount
		collision->hit(getDamage());
		Logs::println("Enemy hit !");

		// inc player money
		Shop::getInstance()->providePlayer(Player::getInstance(), GameMemory::INTELLIGENT);

		// hit myself of the enemy damage amount
		// hit should check if dead
		hit(collision->getDamage());
		Logs::println("Projectile hit too !");
		// if I am, return
		if (!isAlive())
			return;
	}

	// else we update the position
	position = nextPos;
	// and make it rotate, why not ?
	incRot(Configs::ROT_45_RAD, Configs::ROT_45_RAD, Configs::ROT_45_RAD);
}