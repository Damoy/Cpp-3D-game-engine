#include <algorithm>
#include "Enemy.h"
#include "utils\checkers\Checker.h"


Enemy::Enemy(TexturedModel* model, float x, float y, float z, float xScale, float yScale, float zScale, unsigned short life, unsigned short dps, unsigned short arm)
	: Entity(model, x, y, z, xScale, yScale, zScale),
	Destructible(life, arm),
	Attacker(dps){
	hunters = new std::vector<Attacker*>();
}

Enemy::~Enemy(){
	if (hunters != nullptr) {
		delete hunters;
		hunters = nullptr;
	}
}

void Enemy::update() {
	Entity::update();
}

std::vector<Attacker*>* Enemy::getHunters() const {
	return hunters;
}

void Enemy::attachHunter(Attacker* hunter) {
	Checker::assertNotNull(hunter);
	Checker::assertNotNull(hunters); // should not happen but..

	std::vector<Attacker*>::iterator it = find(hunters->begin(), hunters->end(), hunter);
	if (it == hunters->end()) {
		hunters->push_back(hunter);
	}
}

// remove a hunter if he belongs to the hunters
void Enemy::detachHunter(Attacker* hunter) {
	Checker::assertNotNull(hunter);
	Checker::assertNotNull(hunters); // should not happen but..

	std::vector<Attacker*>::iterator it = find(hunters->begin(), hunters->end(), hunter);
	if (it != hunters->end()) {
		hunters->erase(it);
	}
}

bool Enemy::hasHunterNot(Attacker* thisOne) const {
	Checker::assertNotNull(thisOne);
	std::vector<Attacker*>::iterator it;

	bool hasHunterNotSource = false;
	for (it = hunters->begin(); it != hunters->end(); it++) {
		hasHunterNotSource = (*it) != nullptr && (*it) != thisOne;

		if (hasHunterNotSource)
			break;
	}

	return hasHunterNotSource;
}
