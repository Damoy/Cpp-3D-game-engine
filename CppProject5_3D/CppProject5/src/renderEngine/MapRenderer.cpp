#include "MapRenderer.h"



MapRenderer::MapRenderer(MapShader* ms, glm::mat4 projectionMatrix, Camera* cam, Map* m, Light* l)
	: Renderer(ms), map(m), playerCamera(cam), light(l){

	// starts the shader, loads the projection matrix and stops the shader
	shader->start();
	((SampleShader*)shader)->loadProjectionMatrix(projectionMatrix);
	shader->stop();
}

MapRenderer::~MapRenderer(){
}

void MapRenderer::renderMap(Map& map) const {
	TexturedModel* texModel = map.getModel();
	RawModel* tRawModel = texModel->getRawModel();

	glBindVertexArray(tRawModel->getVaoID());
	// positions
	glEnableVertexAttribArray(0);
	// texture coords
	glEnableVertexAttribArray(1);
	// normals
	glEnableVertexAttribArray(2);

	// Generates the map transformation matrix and loads it
	glm::mat4 transfoMatrix = Maths::generateTransformationMatrix4f(
		glm::vec3(map.getX(), map.getY(), map.getZ()), map.getRotX(), map.getRotY(), map.getRotZ(), 1.0f);

	// loads the light
	((SampleShader*)shader)->loadLight(light);
	((SampleShader*)shader)->loadTransformationMatrix(transfoMatrix);

	// activate one GL texture
	// sampler2D uses this
	glActiveTexture(GL_TEXTURE0);
	// bind our texture to it
	glBindTexture(GL_TEXTURE_2D, texModel->getTextureID());
	if (tRawModel->indexed()) {
		glDrawElements(GL_TRIANGLES, tRawModel->getVerticesNumber(), GL_UNSIGNED_INT, 0);
	}
	else {
		glDrawArrays(GL_TRIANGLES, 0, tRawModel->getVerticesNumber());
	}

	// disables vbos and and vao
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}

void MapRenderer::render() const {
	// starts the map shader
	shader->start();
	// prepare the rendering
	prepare();
	// render the map
	renderMap(*map);
	postRendering();
	shader->stop();
}

void MapRenderer::prepare() const {
	// loads the camera view matrix
	((SampleShader*)shader)->loadViewMatrix(playerCamera);
	// disable the cullface to see map from below
	glDisable(GL_CULL_FACE);
}

void MapRenderer::postRendering() const {
	// post rendering
	glEnable(GL_CULL_FACE);
}