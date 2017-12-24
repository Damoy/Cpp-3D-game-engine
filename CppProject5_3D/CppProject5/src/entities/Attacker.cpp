#pragma once
#include "Attacker.h"


Attacker::Attacker(unsigned short dmg)
	: damage(dmg){
}

unsigned short Attacker::getDamage() const {
	return damage;
}