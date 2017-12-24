#pragma once

#include "Renderer.h"
#include "entities\graphics\Light.h"
#include "shaders\MapShader.h"
#include "utils\maths\Maths.h"
#include "world\Map.h"

/*
	The MapRenderer.
	Renders the maps.
*/
class MapRenderer : public Renderer{
private:
	// the map reference
	Map* map;
	// the light reference
	Light* light;
	// the player camera reference
	Camera* playerCamera;

	// the currently selected texture
	unsigned int selectedTextureID;

	// prepare the rendering
	void prepare() const;
	// render a map
	void renderMap(Map& map) const;
	void postRendering() const;

public:
	MapRenderer(MapShader* mapShader, glm::mat4 projectionMatrix, Camera* playerCamera, Map* map, Light* light);
	~MapRenderer();

	// Renders
	void render() const;
};

