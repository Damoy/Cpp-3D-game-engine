#pragma once

#include "GLM\glm.hpp"
#include "GLM\gtc\type_ptr.hpp"
#include "models\TexturedModel.h"
#include "loaders\ModelLoader.h"
#include "world\Tile.h"
#include "entities\Entity.h"

/*
	The tiled map.
	Tiles are mostly used to place towers on it.
*/
class Map{
private:
	// map position and rotation
	glm::vec3 position;
	glm::vec3 rotation;

	// map size
	unsigned short size;
	// map number of vertices
	unsigned short nbVertices;
	// map number of rows and columns
	unsigned short rows;
	unsigned short cols;
	unsigned short fullSize;

	TexturedModel* model;
	// tiles
	Tile** tiles;

public:
	const static float TILE_SIZE;

	Map(const char* texturePath, float x, float z, unsigned short size, unsigned short nbVertices);
	~Map();

	TexturedModel* getModel() const;

	// position
	float getX() const;
	float getY() const;
	float getZ() const;

	// rotation
	float getRotX() const;
	float getRotY() const;
	float getRotZ() const;

	// tile info
	unsigned short getMaxRows() const;
	unsigned short getMaxCols() const;

	// tiles-related
	Tile* getTileAt(float x, float y) const;
	Tile* getTileAt(unsigned short row, unsigned short col) const;
	// Is the tile busy or free
	bool isTileBusy(float x, float y) const;
	bool isTileBusy(unsigned short row, unsigned short col) const;
	// Makes the tile busy or free
	Entity* occupyTileWith(float x, float y, Entity* occupier);
	Entity* occupyTileWith(unsigned short row, unsigned short col, Entity* occupier);

	void update();
};

