#pragma once

/*
	A Destructible object is, at it seems, an object
	that can die, so that can have two states: alive and dead.
	It also have a resistance to attackers (armor) and an amount of vitality (life).
*/
class Destructible{
public:
	Destructible(unsigned short life, unsigned short armor);
	~Destructible();

protected:
	unsigned short life;
	unsigned short armor;
	bool alive;

	virtual void checkState();

public:
	virtual bool hit(unsigned short dmg);
	virtual void die();
	virtual bool isAlive() const;
	virtual void update();

	unsigned short getArmor() const;
	unsigned short getLife() const;
};

