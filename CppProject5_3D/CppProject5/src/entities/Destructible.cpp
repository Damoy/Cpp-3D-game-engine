#include "Destructible.h"
#include "utils\logs\Logs.h"

Destructible::Destructible(unsigned short live, unsigned short arm)
	: life(live), armor(arm), alive(true){

}

Destructible::~Destructible() {

}

void Destructible::die() {
	if (!alive) return;
	alive = false;
}

bool Destructible::hit(unsigned short dmg) {
	if (!alive) return false;
	dmg -= armor;
	life -= dmg;
	checkState();
	return alive;
}

void Destructible::checkState() {
	if (life <= 0) {
		die();
	}
}

void Destructible::update() {
	checkState();
}

unsigned short Destructible::getArmor() const { return armor; }
unsigned short Destructible::getLife() const { return life; }
bool Destructible::isAlive() const { return alive; }



