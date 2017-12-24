#pragma once

#include <vector>
#include "shaders\GUIShader.h"
#include "Renderer.h"
#include "gui\GUITexture.h"
#include "models\RawModel.h"

/*
	The GUI Renderer.
	Guis are poorly used in the game,
	but if some are added they should be rendered
	using this renderer.
*/
class GUIRenderer : public Renderer{
private:
	// the gui quad model
	RawModel* rawQuadModel;

	// references to guis textures
	GUITexture* sampleTowerGUI;
	GUITexture* intelligentTowerGUI;

	// guis references storage
	std::vector<GUITexture*>* guis;

public:
	GUIRenderer(GUIShader* shader);
	~GUIRenderer();

	// prepare the rendering
	void prepare() const;

	// render the guis
	void renderTextures(std::vector<GUITexture*>* guis) const;
	void render() const;

	// clean the renderer
	void cleanUp() const;
};

