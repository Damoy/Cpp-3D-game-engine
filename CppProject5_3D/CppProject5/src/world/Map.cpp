#include <iostream>

#include "Map.h"
#include "gameEngine\Configs.h"

const float Map::TILE_SIZE = 1.0f;

Map::Map(const char* texturePath, float x, float z, unsigned short size, unsigned short nbVertices){

	rows = static_cast<unsigned short>(size / Map::TILE_SIZE);
	cols = static_cast<unsigned short>(size / Map::TILE_SIZE);

	Logs::print("Map, rows: ", true, false);
	Logs::printG(rows);
	Logs::print(", cols: ", false, false);
	Logs::printG(cols);
	Logs::println(false, true);

	fullSize = rows * cols;
	tiles = new Tile*[fullSize];

	// generates the tiles
	for (unsigned short row = 0; row < rows; row++) {
		for (unsigned short col = 0; col < cols; col++) {
			Tile** current = &tiles[cols * row + col];
			*current = new Tile(row, col);
		}
	}

	float rotX = 0.0f;
	float rotY = 0.0f;
	float rotZ = 0.0f;

	position = glm::vec3(x, Configs::BASE_MAP_HEIGHT, z);
	rotation = glm::vec3(rotX, rotY, rotZ);

	// map model
	model = ModelLoader::getInstance()->loadMap(texturePath, size, nbVertices);
}

Map::~Map(){
	for (int e = 0; e < fullSize; e++)
		delete tiles[e];
	delete[] tiles;
	tiles = nullptr;

	delete model;
}

void Map::update() {

}

Tile* Map::getTileAt(unsigned short row, unsigned short col) const {
	if (row < 0 || row >= rows || col < 0 || col >= cols) {
		Logs::println("Get tile out of bounds !");
		throw std::runtime_error("");
	}
	return tiles[cols * row + col];
}

Tile* Map::getTileAt(float x, float z) const {
	unsigned short row = static_cast<unsigned short>(z / Map::TILE_SIZE);
	unsigned short col = static_cast<unsigned short>(x / Map::TILE_SIZE);
	return getTileAt(row, col);
}

bool Map::isTileBusy(unsigned short row, unsigned short col) const {
	Tile* tile = getTileAt(row, col);
	if (tile != nullptr)
		return tile->isBusy();
	return true;
}

bool Map::isTileBusy(float x, float z) const {
	Tile* tile = getTileAt(x, z);
	if (tile != nullptr)
		return tile->isBusy();
	return true;
}

Entity* Map::occupyTileWith(float x, float z, Entity* occupier) {
	Tile* target = getTileAt(x, z);
	return target->setOccupier(occupier);
}

Entity* Map::occupyTileWith(unsigned short row, unsigned short col, Entity* occupier) {
	Tile* target = getTileAt(row, col);
	return target->setOccupier(occupier);
}

TexturedModel* Map::getModel() const { return model; }

float Map::getX() const { return position.x; }
float Map::getY() const { return position.y; }
float Map::getZ() const { return position.z; }

float Map::getRotX() const { return rotation.x; }
float Map::getRotY() const { return rotation.y; }
float Map::getRotZ() const { return rotation.z; }

unsigned short Map::getMaxRows() const { return rows; }
unsigned short Map::getMaxCols() const { return cols; }
