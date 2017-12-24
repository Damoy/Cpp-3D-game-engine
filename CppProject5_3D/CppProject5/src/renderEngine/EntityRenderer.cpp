#include <iostream>

#include "EntityRenderer.h"
#include "utils\maths\Maths.h"
#include "gameEngine\GameEngine.h"
#include "entities\projectiles\SampleTowerProjectile.h"


EntityRenderer::EntityRenderer(EntityShader* rendererShader, glm::mat4 projectionMatrix, Camera* cam, Light* mainLight)
	: Renderer(rendererShader), playerCamera(cam), light(mainLight){

	// before check
	std::map<TexturedModel*, std::vector<Entity*>*>::iterator it;

	// starts the shader, loads the projection matrix once and stops it
	shader->start();
	((SampleShader*)shader)->loadProjectionMatrix(projectionMatrix);
	shader->stop();
}

EntityRenderer::~EntityRenderer(){

}

void EntityRenderer::render() const {
	// starts the entity shader
	shader->start();
	// prepare the rendering
	prepare();

	// render all the entities
	renderEntities();
	// stops the entity shader
	shader->stop();
}

void EntityRenderer::prepare() const {
	// Loads the light to the shader
	((SampleShader*)shader)->loadLight(light);
	// And loads the view matrix, taken from the player camera
	((SampleShader*)shader)->loadViewMatrix(playerCamera);
}

void EntityRenderer::renderEntities() const {
	renderTowers();
	renderEnemies();
	renderProjectiles();
}

void EntityRenderer::renderTowers() const {
	renderMap(GameMemory::getTowers());
}

void EntityRenderer::renderEnemies() const {
	renderMap(GameMemory::getEnemies());
}

void EntityRenderer::renderProjectiles() const {
	renderMap(GameMemory::getProjectiles());
}

// map means std::map
void EntityRenderer::renderMap(std::map<TexturedModel*, std::vector<Entity*>*>* map) const {
	if (map == nullptr) {
		Logs::println("Map was unknown, returned.");
		return;
	}
	
	// map iterator
	std::map<TexturedModel*, std::vector<Entity*>*>::iterator mapIT;

	for (mapIT = map->begin(); mapIT != map->end(); mapIT++) {

		TexturedModel* model = (*mapIT).first;
		if (model == nullptr) {
			Logs::println("RenderMap, model null.");
			continue;
		}

		std::vector<Entity*>* entities = (*mapIT).second;

		if (entities == nullptr) {
			Logs::println("RenderMap, vector entities null.");
			continue;
		}

		std::vector<Entity*>::iterator entitiesIT;

		// prepare the entry model
		prepareModel(*model);

		// iterate entry value (entities vector)
		for (entitiesIT = entities->begin(); entitiesIT != entities->end(); entitiesIT++) {
			// get the current entity
			Entity* entity = (*entitiesIT);

			// prepare it
			prepareEntity(*entity);

			// render it with its model
			renderInstance(*model->getRawModel());

		}

		// unbind the last bounded model
		unbindModel();
	}

}

void EntityRenderer::prepareModel(TexturedModel& model) const {
	RawModel* tRawModel = model.getRawModel();
	// binds the model vao
	glBindVertexArray(tRawModel->getVaoID());
	// positions
	glEnableVertexAttribArray(0);
	// texture coords
	glEnableVertexAttribArray(1);
	// normals
	glEnableVertexAttribArray(2);
	// actives the model texture
	// glActiveTexture(GL_TEXTURE0);
	glActiveTexture(TextureLoader::getBaseModelTextureAtlas());
	// bind our texture to it
	glBindTexture(GL_TEXTURE_2D, model.getTextureID());
}

void EntityRenderer::prepareEntity(Entity& entity) const {
	// Generates an entity transformation matrix
	glm::mat4 transfoMatrix = Maths::generateTransformationMatrix4f(
		glm::vec3(entity.getX(), entity.getY(), entity.getZ()),
		glm::vec3(entity.getRotX(), entity.getRotY(), entity.getRotZ()),
		entity.getXScale(), entity.getYScale(), entity.getZScale());

	// And loads it to the shader
	((SampleShader*)shader)->loadTransformationMatrix(transfoMatrix);
}

void EntityRenderer::renderInstance(RawModel& rawModel) const {
	glDrawElements(GL_TRIANGLES, rawModel.getVerticesNumber(), GL_UNSIGNED_INT, 0);
}

void EntityRenderer::unbindModel() const {
	// disables vbos and and vao
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

