#pragma once

/*
	An attacker is an object that has damage amount
	and can attack some other objects.
*/
class Attacker {
protected:
	unsigned short damage;
public:
	Attacker(unsigned short damage);
	unsigned short getDamage() const;
};