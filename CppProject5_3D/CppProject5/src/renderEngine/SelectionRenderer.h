#pragma once

#include <sstream>

#include "Renderer.h"
#include "entities\graphics\Camera.h"
#include "shaders\SelectionShader.h"
#include "models\TexturedModel.h"
#include "input\InputController.h"
#include "loaders\ModelLoader.h"
#include "world\World.h"
#include "TextRenderer.h"

/*
	The player mouse map collision tile selection information rendering. (Hurgh, quite a long sentence)
	Renders the flat quad indicating where your selection is.
*/
class SelectionRenderer : public Renderer {
private:
	Camera* playerCamera;
	Light* light;
	World* world;

	// different models used according to the currentselection
	TexturedModel* currentModel;
	TexturedModel* baseSelectionModel;
	TexturedModel* sampleTowerSelectionModel;
	TexturedModel* intelligentTowerSelectionModel;

	glm::mat4 projectionMatrix;

	// prepare the rendering
	void prepare() const;
	// render the selection
	void renderSelection() const;

public:
	SelectionRenderer(SelectionShader* shader, World* world, glm::mat4 proj, Camera* playerCamera, Light* light);
	~SelectionRenderer();

	// renders
	void render() const;
	// model getter
	TexturedModel* getCurrentModel() const;
};

