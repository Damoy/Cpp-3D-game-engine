#pragma once

#include <map>
#include <vector>

#include "Renderer.h"
#include "models\RawModel.h"
#include "entities\Entity.h"
#include "shaders\EntityShader.h"

/*
	The EntityRenderer.
	The renderer the most used as it provides
	rendering for all game entities.
*/
class EntityRenderer : public Renderer{
private:

	// a reference to the main light
	Light* light;
	// the player camera
	Camera* playerCamera;

	// Prepare the renderer
	void prepare() const;
	// Prepare a textured model
	void prepareModel(TexturedModel& model) const;
	// Prepare an entity
	void prepareEntity(Entity& entity) const;

	// Render the entities
	void renderEntities() const;
	// Render an instance, pure opengl draw
	void renderInstance(RawModel& rawModel) const;
	// Render a textured model, entity vector association
	void renderMap(std::map<TexturedModel*, std::vector<Entity*>*>* map) const;
	// Render the game towers
	void renderTowers() const;
	// Render the game enemies
	void renderEnemies() const;
	// Render the game projectiles
	void renderProjectiles() const;

	// Unbinds the last bound model
	void unbindModel() const;

public:
	EntityRenderer(EntityShader* rendererShader, glm::mat4 projectionMatrix, Camera* playerCamera, Light* tmpLight);
	~EntityRenderer();

	// Render all
	void render() const;

};

