#pragma once

#include "loaders\ModelLoader.h"
#include "models\TexturedModel.h"
#include "entities\Entity.h"
#include "GLM\glm.hpp"

/*
	The Tile class.
	A tile has a certain map position (row, col) and can have an occupier
*/
class Tile{

private:
	//x, y
	glm::vec2 position;
	// row, col
	glm::vec2 tilePosition;
	Entity* occupier;

public:
	Tile(unsigned short row, unsigned short col);
	~Tile();

	// getters
	glm::vec2 getPosition() const;

	float getX() const;
	float getZ() const;

	unsigned short getRow() const;
	unsigned short getCol() const;

	Entity* getOccupier() const;
	Entity* setOccupier(Entity* occupier);
	bool isBusy() const;

	virtual void update();
};

