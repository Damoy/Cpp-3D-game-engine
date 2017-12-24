#include <iostream>

#include "Tile.h"
#include "gameEngine\GameEngine.h"
#include "loaders\ModelLoader.h"


Tile::Tile(unsigned short row, unsigned short col){
	float x = static_cast<float>(col * Map::TILE_SIZE);
	float z = static_cast<float>(row * Map::TILE_SIZE);
	
	Logs::print("Tile, x: ", true, false);
	Logs::printG(x);
	Logs::print(", z: ", false, false);
	Logs::printG(z);
	Logs::println(false, true);

	position = glm::vec2(x, z);
	tilePosition = glm::vec2(row, col);
	occupier = nullptr;
}

Tile::~Tile(){
}

void Tile::update() {
	
}

// -- getters --
bool Tile::isBusy() const { return occupier != nullptr; }
Entity* Tile::getOccupier() const { return occupier; }
glm::vec2 Tile::getPosition() const { return position; }
float Tile::getX() const { return position.x; }
float Tile::getZ() const { return position.y; }

unsigned short Tile::getRow() const { return static_cast<unsigned short>(tilePosition.y); }
unsigned short Tile::getCol() const { return static_cast<unsigned short>(tilePosition.x); }


// -- setters --

// Returns the old occupier
Entity* Tile::setOccupier(Entity* newOccupier) {
	Entity* was = occupier;
	occupier = newOccupier;
	return was;
}